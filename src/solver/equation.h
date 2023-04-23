#pragma once
#include <iostream>
#include <cmath>
#include "../object.h"
#include "../numerical.h"
using namespace std; 

class Equation
{	
public:
	Equation();
	~Equation();
protected:
	void elliptic(int i,Object &obj, Numerical &numer);
	void renormal(int i, Object &obj, Numerical &numer);
private:
};
