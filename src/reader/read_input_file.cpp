#include "read_input_file.h"
Read_input_file::Read_input_file(){};
Read_input_file::~Read_input_file(){};		 

void Read_input_file::read(string input_file,Object &obj, Numerical &numer)
{
	string line,text;

	ifstream in (input_file,ios::in);
	if (in.is_open())
	{	
		while (getline(in,line))
		{
			if (regex_replace(line, regex(" "), "") == "#START_INPUT#")
			{
				cout<< line <<endl;
			}

			if (regex_replace(line, regex(" "), "") == "MESH")
			{	
				in >> Read_input_file::mesh_file; 	
				in >> text;
				Read_input_file::error(text, "MESH");

				Read_input_file::read_mesh(obj);
 
				Construction_mesh::node_connection(obj); 
				Construction_mesh::cell_connection(obj); 
				Construction_mesh::bound_construct(obj); 
			}

			if (regex_replace(line, regex(" "), "")  == "METRIC")
			{	
				in >> numer.metric;
				in >> text;
				Read_input_file::error(text, "METRIC"); 			
				for (int i = 0; i < obj.node.size(); ++i)
				{
					obj.node[i].coordinate[0] = obj.node[i].coordinate[0]*numer.metric;
					obj.node[i].coordinate[1] = obj.node[i].coordinate[1]*numer.metric;	
					obj.node[i].coordinate[2] = obj.node[i].coordinate[2]*numer.metric; 	
				}	
			}

			if (regex_replace(line, regex(" "), "")  == "TIME")
			{
				in >> text >> text >> text >> text;
				in >> numer.consol_print_step >> numer.consol_print_outfile >> numer.time_end >> numer.dt;
				in >> text;
				Read_input_file::error(text, "TIME"); 
			}

			if (regex_replace(line, regex(" "), "")  == "BOUNDARY")
			{	
				int number_boundary;
				vector <int> number;
				vector <string> type_boundary;
				
				in >> text;
				in >> number_boundary;
				for (int i = 0; i < number_boundary; ++i)
				{	
					in >> text;
					number.push_back(stoi(text));
					in >> text;
					type_boundary.push_back(text);
				}

				Read_input_file::boundary_init(obj,number,type_boundary);			
			}			
			if (regex_replace(line, regex(" "), "")  == "INITIAL")
			{	
				int num = 0;
				vector <int> parts;
				vector <double> v;
				vector <double> beta;

				in >> text;
				in >> num;
				in >> text >> text >> text;
				for (int i = 0; i<num; ++i)
				{
					in >> text;
					parts.push_back(stoi(regex_replace(text, regex(" "), "")));

					in >> text;
					v.push_back(stod(regex_replace(text, regex(" "), "")));

					in >> text;
					beta.push_back(stod(regex_replace(text, regex(" "), "")));
				}
				Read_input_file::cell_init(obj,parts,v,beta);
			}
			if (regex_replace(line, regex(" "), "")  == "SOURCE")
			{	
				vector <int> parts;
				vector <double> v;
				vector <double> beta;

				in >> text;
				if (regex_replace(text, regex(" "), "") == "num")
				{	
					int num = 0;
					in >> num;
					for(int k = 0; k < num; ++k)
					{

						in >> text;
						if (regex_replace(text, regex(" "), "") == "volume_ellipse")
						{	
							double xc = 0, yc = 0, zc = 0;
							double x0 = 0, y0 = 0, z0 = 0, r1 = 0, r2 = 0, r3 = 0, source = 0, omega = 0;
							in >> text >> text >> text >> text >> text >> text >> text >> text;
							in >> x0 >> y0 >> z0 >> r1 >> r2 >> r3 >> source >> omega;

							for (int i = 0; i < obj.cell.size(); ++i)
							{
								xc = 0.25*(obj.node[obj.cell[i].index_node[0]].coordinate[0]+obj.node[obj.cell[i].index_node[1]].coordinate[0]+obj.node[obj.cell[i].index_node[2]].coordinate[0]+obj.node[obj.cell[i].index_node[3]].coordinate[0]);
	                			yc = 0.25*(obj.node[obj.cell[i].index_node[0]].coordinate[1]+obj.node[obj.cell[i].index_node[1]].coordinate[1]+obj.node[obj.cell[i].index_node[2]].coordinate[1]+obj.node[obj.cell[i].index_node[3]].coordinate[1]);
	                			zc = 0.25*(obj.node[obj.cell[i].index_node[0]].coordinate[2]+obj.node[obj.cell[i].index_node[1]].coordinate[2]+obj.node[obj.cell[i].index_node[2]].coordinate[2]+obj.node[obj.cell[i].index_node[3]].coordinate[2]);

	  							if (pow(r2*r3*(xc-x0),2)+pow(r1*r3*(yc-y0),2)+pow(r1*r2*(zc-z0),2) <= pow(r1*r2*r3,2))
	  							{
	  								obj.cell[i].source = source;
	  								obj.cell[i].omega = omega;
	  							}
							}		
						}
						if (regex_replace(text, regex(" "), "") == "volume_rectangle")
						{

							double xc = 0, yc = 0, zc = 0;
							double x0 = 0, y0 = 0, z0 = 0, x = 0, y = 0, z = 0, source = 0, omega = 0;
							in >> text >> text >> text >> text >> text >> text >> text >> text;
							in >> x0 >> y0 >> z0 >> x >> y >> z >> source >> omega;
 
							for (int i = 0; i < obj.cell.size(); ++i)
							{
								xc = 0.25*(obj.node[obj.cell[i].index_node[0]].coordinate[0]+obj.node[obj.cell[i].index_node[1]].coordinate[0]+obj.node[obj.cell[i].index_node[2]].coordinate[0]+obj.node[obj.cell[i].index_node[3]].coordinate[0]);
	                			yc = 0.25*(obj.node[obj.cell[i].index_node[0]].coordinate[1]+obj.node[obj.cell[i].index_node[1]].coordinate[1]+obj.node[obj.cell[i].index_node[2]].coordinate[1]+obj.node[obj.cell[i].index_node[3]].coordinate[1]);
	                			zc = 0.25*(obj.node[obj.cell[i].index_node[0]].coordinate[2]+obj.node[obj.cell[i].index_node[1]].coordinate[2]+obj.node[obj.cell[i].index_node[2]].coordinate[2]+obj.node[obj.cell[i].index_node[3]].coordinate[2]);

	  							if ((xc >= x0) &&  (xc <= x) && (yc <= y) && (zc <= z))
	  							{
	  								obj.cell[i].source = source;
	  								obj.cell[i].omega = omega;
	  							}
							}	
						}
						if (regex_replace(text, regex(" "), "") == "part")
						{
							double source = 0;
							double xc = 0, yc = 0, zc = 0, omega = 0;

							int part = 0;
							in >> part >> source >> omega;

							for (int i = 0; i < obj.cell.size(); ++i)
							{
								xc = 0.25*(obj.node[obj.cell[i].index_node[0]].coordinate[0]+obj.node[obj.cell[i].index_node[1]].coordinate[0]+obj.node[obj.cell[i].index_node[2]].coordinate[0]+obj.node[obj.cell[i].index_node[3]].coordinate[0]);
	                			yc = 0.25*(obj.node[obj.cell[i].index_node[0]].coordinate[1]+obj.node[obj.cell[i].index_node[1]].coordinate[1]+obj.node[obj.cell[i].index_node[2]].coordinate[1]+obj.node[obj.cell[i].index_node[3]].coordinate[1]);
	                			zc = 0.25*(obj.node[obj.cell[i].index_node[0]].coordinate[2]+obj.node[obj.cell[i].index_node[1]].coordinate[2]+obj.node[obj.cell[i].index_node[2]].coordinate[2]+obj.node[obj.cell[i].index_node[3]].coordinate[2]);

	  							if (obj.cell[i].part == part)
	  							{
	  								obj.cell[i].source = source;
	  								obj.cell[i].omega = omega;
	  							}
							}	
						}
					}
				}
				else
				{
					Read_input_file::error(text, "SOURCE_num"); 
				} 
			}
 		}
	}
}

void Read_input_file::boundary_init(Object &obj,vector <int>& number,vector <string>& type_boundary)
{	

 	for (int i = 0; i < obj.segment.size();++i)
 	{	
 		for (int j = 0; j < number.size();++j)
 		{
 			if (obj.segment[i].part == number[j])
 			{
				if (type_boundary[j] == "source")
					obj.segment[i].type = 1;
				else if (type_boundary[j] == "absorp")
					obj.segment[i].type = 2;
				else if (type_boundary[j] == "reflect")	
					obj.segment[i].type = 3;
				else
					obj.segment[i].type = 0;
		 		break;	
 			}
 		}
 	}
}

void Read_input_file::cell_init(Object &obj,vector <int>& parts,vector <double>& v, vector <double>& beta)
{	

 	for (int i = 0; i < obj.cell.size();++i)
 	{	
 		for (int j = 0; j < parts.size();++j)
 		{
 			if (obj.cell[i].part == parts[j] && parts[j] > 0 )
 			{
				obj.cell[i].v = v[j];
				obj.cell[i].beta = beta[j];
 			}
 		}
 	}
}

void Read_input_file::error(string text, string text_)
{
	if (text == "END_"+text_)
	{
		cout << "Complete read "+text_ << endl;
	}
	else
	{
		cout<< "Error read "+text_+"! Program stop." << endl;
		exit(0);
	}
}

void Read_input_file::read_mesh(Object &obj)
{	
	string line;
	double _node;
	int _segment,_cell;
	int n_node,n_segment,n_cell;

	ifstream in (Read_input_file::mesh_file,ios::in);
	if (in.is_open())
	{	
		while (getline(in,line))
		{	
			if (regex_replace(line, regex(" "), "") == "Vertices")
			{
				Object::Node node_;
				in >> n_node;
				obj.node.reserve(n_node);
				for (int i = 0; i < n_node; ++i)
				{
					obj.node.push_back(node_);
					obj.node[i].n_node = n_node;
					for (int j = 0; j < 4; ++j)
					{	
						in >> _node;
						if (j < 3){obj.node[i].coordinate.push_back(_node);}
						if (j == 3){obj.node[i].part = _node;}
					}
				}
				cout<<"Vertices end"<<endl;
			}

			if (regex_replace(line, regex(" "), "")  == "Triangles")
			{	
				Object::Segment segment_;
				in >> n_segment;	
				obj.segment.reserve(n_segment);
				for (int i = 0; i < n_segment; ++i)
 				{
 			 		obj.segment.push_back(segment_);
 			 		obj.segment[i].n_segment = n_segment;
 					for (int j = 0; j < 4; ++j)
 					{	
 					 	in >> _segment;
 					 	if (j < 3){obj.segment[i].index_node.push_back(_segment-1);}
 					 	if (j == 3){obj.segment[i].part = _segment;}
 					}
				}
				cout<<"Triangles end"<<endl;
			}

			if (regex_replace(line, regex(" "), "")  == "Tetrahedra")
			{	
				Object::Cell cell_;
				in >> n_cell;	
				obj.cell.reserve(n_cell);
				

				for (int i = 0; i < n_cell; ++i)
 				{	

 					obj.cell.push_back(cell_);
 					obj.cell[i].n_cell = n_cell;
 					 					
 					for (int j = 0; j < 5; ++j)
 					{	
 					 	in >> _cell;
 					 	if (j < 4){obj.cell[i].index_node[j] = _cell-1;}
 					 	if (j == 4){obj.cell[i].part = _cell;}
 					}	
				}

				cout<<"Tetrahedra end"<<endl;
			}
 		}
	}
};
