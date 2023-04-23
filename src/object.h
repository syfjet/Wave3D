#pragma once
#include <iostream>
#include <vector>
using namespace std; 

class Object{
public:
	class Node
	{
	public:
		int n_node = 0;
		int part = 0;
		vector<double> coordinate;	
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
		vector<int> index_node;	
		int type = 0;
	protected:
	private:					
	};  

	class Cell
	{
	public:
		int n_cell = 0;
		int part = 0;
		int index_node[4];	
		int connection[4] = {-1,-1,-1,-1};
			
		double U_old = 0;
		double U = 0;
		double U_new = 0;
		double v = 0;
		double beta = 0;

		double source = 0;
		double omega = 0;
		
		double volume = 0;
		double x_cs[4][3];
		double x_c[3];
		double edge[6];
		double surface[4];
		double full_surface;	
	};
	vector<Node> node;			
	vector<Segment> segment;	
	vector<Cell> cell;

};


 