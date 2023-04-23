#include "boundary.h"

Boundary::Boundary(){};
Boundary::~Boundary(){};	

void Boundary::boundary(int i, Object &obj, Numerical &numer)
{
	if (obj.segment[i].type > 0)
	{
		if (obj.segment[i].type  == 1)
		{
			obj.cell[obj.segment[i].cell].U_old = sin(1000.*numer.time);
			obj.cell[obj.segment[i].cell].U = obj.cell[obj.segment[i].cell].U_old;
			obj.cell[obj.segment[i].cell].U_new = obj.cell[obj.segment[i].cell].U;
		}
		if (obj.segment[i].type  == 2)
		{
			obj.cell[obj.segment[i].cell].beta = 0;  
		}		
		if (obj.segment[i].type  == 3){}				
	}
};
