#include "out.h"

Out::Out(){};
Out::~Out(){};       

void Out::out_print(Object &obj, Numerical &numer)
{
    if (numer.step%numer.consol_print_step == 0)
    {
        cout << " Step= " << numer.step << " time= " << numer.time << " dt= " << numer.dt << " Progress= " << numer.time/numer.time_end*100.0 << "%"<< "\n";
    }
}
 
void Out::out_paraview(Object &obj, Numerical &numer)
{
    if (numer.step%numer.consol_print_outfile == 0)
    {
        ofstream out;
        out.open("results/"+to_string(numer.step)+".vtu");
        if (out.is_open())
        {
            out << "<VTKFile type='UnstructuredGrid' version='0.1' byte_order='BigEndian'>"<<"\n";
            out << "<UnstructuredGrid>"<<"\n";
            out << "<Piece NumberOfPoints='"<<obj.node.size()<<"' NumberOfCells='"<<obj.cell.size()<<"'>"<<"\n";
            out << "<Points>"<<"\n";
            out << "<DataArray type='Float64' NumberOfComponents='3' Format='ascii'>"<<"\n";
 
            for (int i = 0;i<obj.node.size();++i)
            {
                out << obj.node[i].coordinate[0]<< " " <<obj.node[i].coordinate[1]<< " " <<obj.node[i].coordinate[2]<<"\n";
            }
            out << "</DataArray>"<<"\n";
            out << "</Points>"<<"\n";
            out << "<CellData Scalars='scalars'>"<<"\n";

            out << "<DataArray type='Float64' Name='U_r' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << obj.cell[i].U<<"\n";
            }   
            out << "</DataArray>"<<"\n";

            out << "<DataArray type='Float64' Name='Parts' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
             out << obj.cell[i].part<<"\n";
            }    
            out << "</DataArray>"<<"\n";

            // out << "<DataArray type='Float64' Name='Source' format='ascii'>"<<"\n";
            // for (int i = 0;i<obj.cell.size();++i)
            // {
            //  out << obj.cell[i].source <<"\n";
            // }    
            // out << "</DataArray>"<<"\n";

             

            out << "</CellData>"<<"\n"; 

            out << "<Cells>"<<"\n";     
            out << "<DataArray type='Int32' Name='connectivity' format='ascii'>"<<"\n";     
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << obj.cell[i].index_node[0]<< " "<< obj.cell[i].index_node[1]<< " " << obj.cell[i].index_node[2]<< " " << obj.cell[i].index_node[3]<< " "  <<"\n";
            }   
            out << "</DataArray>"<<"\n";
            out << "<DataArray type='Int32' Name='offsets' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << 4*(i+1) <<"\n";
            }   
            out << "</DataArray>"<<"\n";
            out << "<DataArray type='Int32' Name='types' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << 10 <<"\n";
            }   
            out << "</DataArray>"<<"\n";    
            out << "</Cells>"<<"\n";
            out << "</Piece>"<<"\n";
            out << "</UnstructuredGrid>"<<"\n"; 
            out << "</VTKFile>"<<"\n";                  
        }
        out.close();
    }
};
