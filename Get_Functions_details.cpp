#include "Get_Functions_details.h"
#define Pi 3.141592653589793238462643383279502884L

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

float fun2(float Universe[], int dim) //SPHERE FUNCTION
{
	float sum = 0;
	for (int i = 0; i < dim; i++)
	{
		sum += pow(Universe[i], 2);
	}
	return sum;
}

float fun3(float Universe[], int dim) // ACKLEY FUNCTION
{
	float sum1 = 0;
	float sum2 = 0;
	float c = 2 * Pi, a = 20, b = 0.2;

	for (int i = 0; i < dim; i++)
	{
		sum1 += pow(Universe[i], 2);
		sum2 += cos(c* Universe[i]);
	}

	return (-a*exp(-b*sqrt(sum1/dim)))+(-exp(sum2/dim))+a+exp(1);
}

float fun4(float Universe[], int dim) // GRIEWANK FUNCTION
{
	float sum = 0;
	float prod = 1;
	for (int i = 0; i < dim; i++)
	{
		sum += (pow(Universe[i], 2)/4000);
		prod *= cos(Universe[i] / sqrt(i+1));
	}
	return sum-prod+1;
}

float fun5(float Universe[], int dim) // RASTRIGIN FUNCTION
{
	float sum = 0;
	for (int i = 0; i < dim; i++)
	{
		sum += (pow(Universe[i], 2)) - (10*cos(2*Pi* Universe[i]));
	}
	return ((10*dim) + sum);
}

float fun6(float Universe[], int dim) // ROTATED HYPER-ELLIPSOID FUNCTION
{
	float outer = 0;
	for (int i = 0; i < dim; i++)
	{
		float inner = 0;
		for (int j = 0; j < i; j++)
		{
			inner += pow(Universe[j], 2);
		}
		outer += inner;
	}
	return outer;
}

float fun7(float Universe[], int dim)  // DIXON-PRICE FUNCTION
{
	float sum = 0;
	for (int i = 1; i < dim; i++)
	{
		sum += i * (2 * pow(Universe[i], 2) * pow(Universe[i - 1], 2));
	}
	return pow(Universe[0] - 1, 2)+sum;
}

float fun8(float Universe[], int dim) // SUM SQUARES FUNCTION
{
	float sum = 0;
	for (int i = 0; i < dim; i++)
	{
		sum += (i+1)* pow(Universe[i], 2);
	}
	return sum;
}

float fun9(float Universe[], int dim) // TRID FUNCTION
{
	float sum1 = pow(Universe[0]-1,2);
	float sum2 = 0;

	for (int i = 1; i < dim; i++)
	{
		sum1 += pow(Universe[1] - 1,2);
		sum2 += Universe[i]*Universe[i-1];
	}
	return sum1 - sum2;
}

float fun10(float Universe[], int dim) // ROSENBROCK FUNCTION
{
	float sum = 0;
	for (int i = 0; i < dim-1; i++)
	{
		sum += 100 *(pow((Universe[i + 1] - Universe[i]), 2)) + pow(Universe[i]-1,2);
	}
	return sum;
}

float fun11(float Universe[], int dim) // LEVY FUNCTION
{
	float* w=new float[dim];
	for (int i = 0; i < dim; i++)
	{
		w[i] = 1 + ((Universe[i]-1))/4;
	}

	float term1 = pow(sin(Pi*w[0]),2);
	float term3 = pow((w[dim-1]-1),2) * (1+pow(sin(2*Pi*w[dim-1]),2));

	float sum = 0;

	for (int i = 0; i < dim-1; i++)
	{
		sum += pow(w[i]-1,2) * (1+10*(pow(sin((Pi*w[i])+1),2)));
	}
	return term1 + sum + term3;
}

float fun12(float Universe[], int dim)
{
	float mes1 = 0;
	float mes2 = 0;
	float mes3 = 0;
	float mes4 = 0;
	float mes5 = 0;
	float mes6 = 0;
	float sum = 0;
	for (int i = 0; i < dim; i++)
	{
		mes1 = 150 * Universe[i] + (1 - Universe[i]) * 130;
		mes2 = 170 * Universe[i] + (1 - Universe[i]) * mes1;
		mes3 = 160 * Universe[i] + (1 - Universe[i]) * mes2;
		mes4 = 180 * Universe[i] + (1 - Universe[i]) * mes3;
		mes5 = 140 * Universe[i] + (1 - Universe[i]) * mes4;
		mes6 = 130 * Universe[i] + (1 - Universe[i]) * mes5;
	}

	sum = abs(170 - mes1) + abs(160 - mes2) + abs(180 - mes3) + abs(140 - mes4) + abs(130 - mes5) + abs(140 - mes6);
	sum = sum / 6;
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
		lb = new float[1]; 
		lb[0] = -5.12f;
		ub = new float[1];
		ub[0] = 5.12f;
		*dim = 20;
		fobj = &fun2;
		break;
	case 3:
		*N_of_boundaries = false;
		lb = new float[1];
		lb[0] = -32.768f;
		ub = new float[1];
		ub[0] = 32.768f;
		*dim = 10;
		fobj = &fun3;
		break;
	case 4:
		*N_of_boundaries = false;
		lb = new float[1]; 
		lb[0] = -600.0f;
		ub = new float[1];
		ub[0] = 600.0f;
		*dim = 10;
		fobj = &fun4;
		break;
	case 5:
		*N_of_boundaries = false;
		lb = new float[1];
		lb[0] = -5.12f;
		ub = new float[1];
		ub[0] = 5.12f;
		*dim = 20;
		fobj = &fun5;
		break;
	case 6:
		*N_of_boundaries = false;
		lb = new float[1];
		lb[0] = -65.536f;
		ub = new float[1];
		ub[0] = 65.536f;
		*dim = 10;
		fobj = &fun6;
		break;
	case 7:
		*N_of_boundaries = false;
		lb = new float[1];
		lb[0] = -10.0f;
		ub = new float[1];
		ub[0] = 10.0f;
		*dim = 10;
		fobj = &fun7;
		break;	
	case 8:
		*N_of_boundaries = false;
		lb = new float[1];
		lb[0] = -10.0f;
		ub = new float[1];
		ub[0] = 10.0f;
		*dim = 10;
		fobj = &fun8;
		break;
	case 9:
		*N_of_boundaries = false;
		*dim = 10;
		lb = new float[1];
		lb[0] = -1 * (pow(*dim,2));
		ub = new float[1];
		ub[0] = (pow(*dim, 2));
		fobj = &fun9;
		break;
	case 10:
		*N_of_boundaries = false;
		lb = new float[1];
		lb[0] = -2.048f;
		ub = new float[1];
		ub[0] = 2.048f;
		*dim = 20;
		fobj = &fun10;
		break;
	case 11:
		*N_of_boundaries = false;
		lb = new float[1];
		lb[0] = -10.0f;
		ub = new float[1];
		ub[0] = 10.0f;
		*dim = 20;
		fobj = &fun11;
		break;	
	case 12:
		*N_of_boundaries = false;
		lb = new float[1];
		lb[0] = 0;
		ub = new float[1];
		ub[0] = 1;
		*dim = 1;
		fobj = &fun12;
		break;
	}

}


