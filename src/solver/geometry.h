#pragma once
#include <iostream>
#include <cmath>
#include "../object.h"

using namespace std; 
class Geometry
{	
	public:
		Geometry();
		~Geometry();
		void G3(int i, Object &obj);
	protected:

	private:
		void geometry_different_point(double (&x)[4][3],double (&a)[4][3],double (&b)[4][3],double (&c)[4][3]);
		void geometry_cell_center_surface(int i, double(&x)[4][3], Object &obj);
		void geometry_cell_edge(int i,double(&a)[4][3],double(&b)[4][3],double(&c)[4][3], Object &obj);
		void geometry_cell_surface(int i,Object &obj);
		void geometry_volume(int i,double(&a)[4][3],double(&b)[4][3],double(&c)[4][3], Object &obj);
}; 

 
 
