#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "object.h"
#include "numerical.h"
#include "read_input_file.h"
#include "solver.h"

using namespace std;
int main()
{
	
	Object obj;
	Numerical numer;

	Read_input_file *read_file = new Read_input_file;
 	read_file->read("gas.inp",obj,numer); 
 	delete read_file;

	Solver solve;
	solve.wave(obj,numer);

 	// delete solve;
 	// delete numer; 
  	// delete obj; 
	return 0;		
} 
