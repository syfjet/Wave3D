#pragma once
#include <iostream>
#include <fstream>
#include "object.h"
#include "geometry.h"
#include "numerical.h"
#include "equation.h"
#include "boundary.h"
#include "out.h"
#include <omp.h>
using namespace std; 
; 

class Solver: public Geometry, Equation, Boundary, Out
{	
public:
	Solver();
	~Solver();

	void wave(Object &obj, Numerical &numer);

protected:
private:

};
