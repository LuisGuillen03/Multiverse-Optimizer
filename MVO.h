#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

class MVO
{
public:
	MVO();
	~MVO();
	void Calculate(float*, float*&, float*&,int, int, float[], float[], int, float(*)(float[],int),bool);
};


