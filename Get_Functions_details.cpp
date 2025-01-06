#include "Get_Functions_details.h"

Get_Functions_details::Get_Functions_details()
{
	
}
Get_Functions_details::~Get_Functions_details()
{

}

float fun1(float Universe[],int dim)
{
	float sum=0;
	for (int i = 0; i < dim; i++)
	{
		sum += Universe[i];
	}
	return sum;
}

float fun2(float Universe[], int dim)
{
	float sum = 0;
	for (int i = 0; i < dim; i++)
	{
		sum += pow(Universe[i], 2);
	}
	return sum;
}


void Get_Functions_details::Details(int F,float*& lb, float*& ub, int* dim, float(*&fobj)(float [],int),bool* N_of_boundaries)
{
	switch (F)
	{
	case 1:
		*N_of_boundaries = true; // If the boundaries of all variables are **NOT equal**... N_of_bounds = true
		lb = new float[3];
		lb[0] = 1.0f;
		lb[1] = 20.0f;
		lb[2] = 10.0f;
		ub = new float[3];
		ub[0] = 10.0f;
		ub[1] = 100.0f;
		ub[2] = 50.0f;
		*dim = 3;
		fobj = &fun1;
		break;
	case 2:
		*N_of_boundaries = false; // If the boundaries of all variables are equal... N_of_bounds = false
		lb = new float[1]; // c
		lb[0] = -5.12f;
		ub = new float[1];
		ub[0] = 5.12f;
		*dim = 20;
		fobj = &fun2;
		break;
	}
}


