#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "object.h"
#include "numerical.h"
#include "reader/read_input_file.h"
#include "solver/solver.h"

using namespace std;
int main()
{
string name_file;

	Object obj;
	Numerical numer;

	Read_input_file *read_file = new Read_input_file;
	cin >> name_file;
 	read_file->read(name_file,obj,numer); 
 	delete read_file;

	Solver solve;
	solve.wave(obj,numer);

	return 0;		
} 
