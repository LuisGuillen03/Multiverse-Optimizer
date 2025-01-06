#include "MVO.h"
#include "Get_Functions_details.h"
#include "RouletteWheelSelection.h"
#include <functional>
#include "main.h"
using namespace std;

int  main()
{
	int Universes_No = 60; //Number of search agents (universes)
	int Function_Number = 17; //Name of the test function that can be from F1 to F23(Table 1, 2, 3 in the paper)
	int Max_iteration = 100000; // Maximum number of iterations
	Get_Functions_details GFD;
	MVO MVO;
	int dim; //dim = number of your variables
	float* ub = NULL; //lb = [lb1, lb2, ..., lbn] where lbn is the lower bound of variable n
	float* lb = NULL; //ub = [ub1, ub2, ..., ubn] where ubn is the upper bound of variable n
	float(*fobj)(float [],int)=NULL;
	bool N_of_boundaries =NULL; // Because in C++ we cant get the size of a dinamyc array... this variable is going to says us If the boundaries of all variables are equal or not
	GFD.Details(2, lb, ub, &dim, fobj,&N_of_boundaries);
	float Best_universe_Inflation_rate = INFINITY;
	float* Best_Universe=new float[dim];
	float* Convergence_curve=new float[500];
	MVO.Calculate(&Best_universe_Inflation_rate,Best_Universe,Convergence_curve,Universes_No,Max_iteration,lb,ub,dim,fobj,N_of_boundaries);
	float suma = 0;
	for (int i = 0; i < dim; i++) 
	{
		cout << "Best No for Dimension " << i + 1 << "= " << Best_Universe[i] << endl;
	}
	return 0;
}