#pragma once
#include <iostream>
#include <vector>
using namespace std;


class Get_Functions_details
{
public:
	Get_Functions_details();
	~Get_Functions_details();
	void Details(int, float*&, float*&, int*, float(*&)(float [],int), bool*);
};