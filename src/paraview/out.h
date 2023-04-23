#pragma once
#include <iostream>
#include <fstream>
#include "../object.h"
#include "../numerical.h"
using namespace std; 

class Out
{	
public:
	Out();
	~Out();
protected:
	void out_print(Object &obj, Numerical &numer);
	void out_paraview(Object &obj, Numerical &numer);
private:
};
