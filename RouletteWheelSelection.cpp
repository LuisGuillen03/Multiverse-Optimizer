#include "RouletteWheelSelection.h"

RouletteWheelSelection::RouletteWheelSelection()
{
	srand(time(NULL));
}

RouletteWheelSelection::~RouletteWheelSelection()
{

}

int RouletteWheelSelection::choice(float weights[],int N)
{
	float* accumulation=new float[N];
	accumulation[0] = weights[0]*-1;
	for (int i = 1; i < N; i++)
	{
		accumulation[i] = accumulation[i-1]+(weights[i]*-1);
	}

	float p= ((float)rand() / (float)RAND_MAX)*accumulation[sizeof(weights)-1];
	int chosen_index = -1;
	for (int i = 0; i < N; i++)
	{
		if (accumulation[i] > p)
		{
			chosen_index = i;
		}
	}
	return chosen_index;
}
