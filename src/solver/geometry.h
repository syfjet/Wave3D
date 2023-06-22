#pragma once
#include <iostream>
#include <cmath>
#include <array>
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
		void geometry_different_point(array<array<double,3>,4> &x,array<array<double,3>,4> &a,array<array<double,3>,4> &b,array<array<double,3>,4> &c);
		void geometry_cell_center_surface(int i, array<array<double,3>,4> &x, Object &obj);
		void geometry_cell_edge(int i,array<array<double,3>,4> &a,array<array<double,3>,4> &b, array<array<double,3>,4> &c, Object &obj);
		void geometry_cell_surface(int i,Object &obj);
		void geometry_volume(int i,array<array<double,3>,4> &a,array<array<double,3>,4> &b,array<array<double,3>,4> &c, Object &obj);
}; 

 
 
