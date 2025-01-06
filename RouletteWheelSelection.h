#pragma once
#include <iostream>
#include <numbers>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class RouletteWheelSelection
{
public:
	RouletteWheelSelection();
	~RouletteWheelSelection();
	int choice(float[],int dim);
};

