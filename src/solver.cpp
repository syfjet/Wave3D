#include "solver.h"

Solver::Solver(){};
Solver::~Solver(){};		 

void Solver::wave(Object &obj, Numerical &numer)
{
	int i;
	for (int i = 0;i < obj.cell.size(); ++i)
	{
		Geometry::G3(i,obj);
	}

	while (numer.time < numer.time_end)
	{
		#pragma omp parallel private(i) shared (obj,numer) 
		{


			#pragma omp for schedule(dynamic)
			for (int i = 0;i < obj.cell.size(); ++i)
			{
				Equation::elliptic(i,obj,numer);
			}

			#pragma omp for schedule(dynamic)
			for (int i = 0;i < obj.segment.size(); ++i)
			{
				Boundary::boundary(i,obj,numer);
			}

			#pragma omp for schedule(dynamic)
			for (int i = 0;i < obj.cell.size(); ++i)
			{
				Equation::renormal(i,obj,numer);
			}
		}  
		#pragma omp single
		{
		 	Out::out_print(obj,numer);
			Out::out_paraview(obj,numer);
			numer.time += numer.dt;
			numer.step += 1;			
		}
	}
};
