#include "equation.h"

Equation::Equation(){};
Equation::~Equation(){};         

void Equation::elliptic(int i, Object &obj, Numerical &numer)
{
    int ii,j;
    double s[3],dl;
    double f = 0;

    for (int j = 0; j < 4; ++j)
    {
        ii = obj.cell[i].connection[j];
        
        if (ii > -1) 
        {   
            dl = 0;
            s[0] = obj.cell[i].x_c[0]-obj.cell[i].x_cs[j][0]; 
            s[1] = obj.cell[i].x_c[1]-obj.cell[i].x_cs[j][1];
            s[2] = obj.cell[i].x_c[2]-obj.cell[i].x_cs[j][2];
            dl =  sqrt(s[0]*s[0]+s[1]*s[1]+s[2]*s[2]);

            s[0] = obj.cell[ii].x_c[0]-obj.cell[i].x_cs[j][0]; 
            s[1] = obj.cell[ii].x_c[1]-obj.cell[i].x_cs[j][1];
            s[2] = obj.cell[ii].x_c[2]-obj.cell[i].x_cs[j][2];
            dl +=  sqrt(s[0]*s[0]+s[1]*s[1]+s[2]*s[2]);

            f += obj.cell[i].surface[j]*(obj.cell[ii].U-obj.cell[i].U)/(dl);
        }       
    }

obj.cell[i].U_new = 2.*obj.cell[i].U-obj.cell[i].U_old + obj.cell[i].v*obj.cell[i].v*(numer.dt*numer.dt*f/obj.cell[i].volume-numer.dt*obj.cell[i].beta*(obj.cell[i].U-obj.cell[i].U_old));

if (obj.cell[i].source > 0)
{
    obj.cell[i].U_new += obj.cell[i].source*sin(obj.cell[i].omega*numer.time)*numer.dt;  
}
}

void Equation::renormal(int i, Object &obj, Numerical &numer)
{   
    obj.cell[i].U_old = obj.cell[i].U;
    obj.cell[i].U = obj.cell[i].U_new;
};
