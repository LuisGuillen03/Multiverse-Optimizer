#include "initialization.h"

initialization::initialization()
{
	srand(time(NULL));
}
initialization::~initialization()
{

}

void initialization::initiali(float* Universes [], int N, int dim, float lb[], float ub[],bool N_of_boundaries)
{
	if (N_of_boundaries==false) //If the boundaries of all variables are equal and user enter a signle, number for both ub and lb
		
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				float randomN = (float)rand() / (float)RAND_MAX;
				Universes[i][j] = randomN * ((ub[0] - lb[0]) + lb[0]);
			}
		}
	}
	
	else // If each variable has a different lb and ub
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				float randomN = (float)rand() / (float)RAND_MAX;
				Universes[i][j] = randomN * ((ub[j] - lb[j]) + lb[j]);
			}
		}
	}

}


