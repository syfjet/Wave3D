#pragma once
#include <iostream>
#include <cmath>
#include "object.h"
#include "numerical.h"
using namespace std; 

class Boundary
{	
public:
	Boundary();
	~Boundary();
protected:
	void boundary(int i, Object &obj, Numerical &numer);
private:
};
