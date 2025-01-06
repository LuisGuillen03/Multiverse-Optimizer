#include "MVO.h"
#include "initialization.h"
#include "RouletteWheelSelection.h"

MVO::MVO() 
{
	srand(time(NULL));
}
MVO::~MVO()
{

}


void Sort(float Inflation_rates[], float* Universes[],int N) // BubbleSort Optimized
{
	bool swapped;
	for (int i = 0; i < N - 1; i++)
	{
		swapped = false;
		for (int j = 0; j < N - 1 - i; j++)
		{
			if (Inflation_rates[j] > Inflation_rates[j + 1])
			{
				swap(Inflation_rates[j], Inflation_rates[j + 1]);
				swap(Universes[j], Universes[j + 1]);
				swapped = true;
			}
		}

		// IF no two elements were swapped by inner loop, then break
		if (swapped == false)
		{
			break;
		}
	}
}

void MVO::Calculate(float* Best_universe_Inflation_rate, float*& Best_Universe, float*& Convergence_curve, int N, int Max_time, float lb[], float ub[], int dim, float(*fobj)(float[],int),bool N_of_boundaries)
{
	initialization initialization;
	RouletteWheelSelection RWS;
	float** Universes = new float* [N]; // Create the bidimensional array for Universes and later Sorted_Universes
	float** sorted_Universes = new float* [N];
	for (int i = 0; i < N; i++) {
		Universes[i] = new float[dim];
		sorted_Universes[i] = new float[dim];
	}
	initialization.initiali(Universes, N, dim, lb, ub,N_of_boundaries); //Initialize the positions of universes
	//Minimumand maximum of Wormhole Existence Probability(min and max in Eq.(3.3) in the original paper
	float WEP_Max = 1;
	float WEP_Min = 0.2f;

	//Iteration(time) counter
	int Time = 1;
	while (Time < Max_time + 1)
	{
		float WEP = WEP_Min + Time * ((WEP_Max - WEP_Min) / Max_time); //Eq. (3.3) in the paper
		float TDR = 1 - ((pow(Time, 1.6)) / (pow(Max_time, 1.6))); // Travelling Distance Rate (Formula): Eq. (3.4) in the paper
		float* Inflation_rates = new float[N]; //Inflation rates (I) (fitness values)

		for (int i = 0; i < N; i++) {
			//Boundary checking (to bring back the universes inside search space if they go beyoud the boundaries
			for (int j = 0; j < dim; j++) {
				if (N_of_boundaries == false)
				{
					if (Universes[i][j] > ub[0] || Universes[i][j] < lb[0])
					{
						float randomN = (float)rand() / (float)RAND_MAX;
						Universes[i][j] = randomN * ((ub[0] - lb[0]) + lb[0]);
					}
				}
				else
				{
					if (Universes[i][j] > ub[j] || Universes[i][j] < lb[j])
					{
						float randomN = (float)rand() / (float)RAND_MAX;
						Universes[i][j] = randomN * ((ub[j] - lb[j]) + lb[j]);
					}
				}
			}
			// Calculate the inflation rate (fitness) of universes
			Inflation_rates[i] = fobj(Universes[i],dim);
			//Elitism
			if (Inflation_rates[i] < *Best_universe_Inflation_rate)
			{
				*Best_universe_Inflation_rate = Inflation_rates[i];
				for (int k=0;k<dim;k++)
				{
					Best_Universe[k] = Universes[i][k];
				}
			}

		}

		float components_Sum = 0; //the sum of all components for the normalization

		for (int i = 0; i < N; i++)
		{
			components_Sum += pow(Inflation_rates[i], 2);
		}
		
		Sort(Inflation_rates, Universes,N); // Sort inflation rates also the universes based on the inflation rate of this

		sorted_Universes = Universes;

		float* normalized_sorted_Inflation_rates = new float[N];

		for (int i = 0; i < N; i++)
		{
			normalized_sorted_Inflation_rates[i] = Inflation_rates[i] / sqrt(components_Sum); //Normalized inflation rates (NI in Eq. (3.1) in the paper)
		}

		//Update the Position of universes
		int Black_hole_index, White_hole_index;
		for (int i = 1; i < N; i++) //Starting from 1 since the 0 one is the elite
		{
			Black_hole_index = i;
			for (int j = 1; j < dim; j++)
			{
				float r1 = (float)rand() / (float)RAND_MAX;
				if (r1 < normalized_sorted_Inflation_rates[i])
				{
					White_hole_index = RWS.choice(Inflation_rates, N); //For maximization problem -sorted_Inflation_rates should be written as sorted_Inflation_rates (at RWS erase *weights *-1)
					if (White_hole_index == -1)
					{
						White_hole_index = 1;
					}
					Universes[Black_hole_index][j] = sorted_Universes[White_hole_index][j];
				}
				else
				{

				}
				float r2 = (float)rand() / (float)RAND_MAX;
				if (N_of_boundaries == false)
				{
					if (r2 < WEP)
					{
						float r3 = (float)rand() / (float)RAND_MAX;
						if (r3 < 0.5)
						{
							Universes[i][j] = Best_Universe[j] + TDR * ((ub[0] - lb[0]) * ((float)rand() / (float)RAND_MAX) + lb[0]);
						}
						else
						{
							Universes[i][j] = Best_Universe[j] - TDR * ((ub[0] - lb[0]) * ((float)rand() / (float)RAND_MAX) + lb[0]);
						}
					}
				}

				else
				{
					if (r2 < WEP)
					{
						float r3 = (float)rand() / (float)RAND_MAX;
						if (r3 < 0.5)
						{
							Universes[i][j] = Best_Universe[j] + TDR * ((ub[j] - lb[j]) * ((float)rand() / (float)RAND_MAX) + lb[j]);
						}
						else
						{
							Universes[i][j] = Best_Universe[j] - TDR * ((ub[j] - lb[j]) * ((float)rand() / (float)RAND_MAX) + lb[j]);
						}
					}
				}

			}
			Convergence_curve = Best_universe_Inflation_rate;
			if (Time % 50 == 0)
			{
				cout << "At iteration " << Time << " the best universes fitness is " << *Best_universe_Inflation_rate <<endl;
			}
			Time++;
		}
	}
}


