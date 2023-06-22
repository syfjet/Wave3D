#pragma once
#include <iostream>
#include <vector>
#include <array>
using namespace std; 

class Object
{
public:
	class Node
	{
	public:
		int n_node = 0;
		int part = 0;
		array<double,3> coordinate;	
		vector<int> connection;	
	protected:
	private:				
	}; 

	class Segment
	{
	public:
		int n_segment = 0;
		int cell = 0;
		int part = 0;
		array<int,3> index_node;	
		int type = 0;
	protected:
	private:					
	};  

	class Cell
	{
	public:
		int n_cell = 0;
		int part = 0;
		array<int,4> index_node;	
		array<int,4> connection = {-1,-1,-1,-1};
			
		double U_old = 0;
		double U = 0;
		double U_new = 0;
		double v = 0;
		double beta = 0;

		double source = 0;
		double omega = 0;
		
		double volume = 0;
		array<array<double,3>,4>  x_cs;
		array<double,3> x_c;
		array<double,6> edge;
		array<double,4> surface;
		double full_surface;	
	};
	vector<Node> node;			
	vector<Segment> segment;	
	vector<Cell> cell;

};


 