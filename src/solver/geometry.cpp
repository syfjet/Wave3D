#include "geometry.h"

Geometry::Geometry(){};
Geometry::~Geometry(){};         

void Geometry::G3(int i, Object &obj)
{   
    array<array<double,3>,4> a;
    array<array<double,3>,4> b;
    array<array<double,3>,4> c;
    array<array<double,3>,4> x;

 

    for (int k = 0; k < x.size(); ++k)
    {
        x[k][0] = obj.node[obj.cell[i].index_node[k]].coordinate[0];
        x[k][1] = obj.node[obj.cell[i].index_node[k]].coordinate[1];
        x[k][2] = obj.node[obj.cell[i].index_node[k]].coordinate[2];
    }
    
    Geometry::geometry_different_point(x,a,b,c);
    Geometry::geometry_cell_center_surface(i,x,obj);
    Geometry::geometry_cell_edge(i,a,b,c,obj);
    Geometry::geometry_cell_surface(i,obj);
    Geometry::geometry_volume(i,a,b,c,obj);
}

void Geometry::geometry_different_point(array<array<double,3>,4> &x,array<array<double,3>,4> &a,array<array<double,3>,4> &b,array<array<double,3>,4> &c)
{
    for (int k = 0; k < 3; ++k)
    {
        a[0][k] = x[1][k]-x[0][k];
        b[0][k] = x[2][k]-x[0][k];
        c[0][k] = x[3][k]-x[0][k];

        a[1][k] = x[0][k]-x[1][k];
        b[1][k] = x[2][k]-x[1][k];
        c[1][k] = x[3][k]-x[1][k];

        a[2][k] = x[0][k]-x[2][k];
        b[2][k] = x[1][k]-x[2][k];
        c[2][k] = x[3][k]-x[2][k];

        a[3][k] = x[0][k]-x[3][k];
        b[3][k] = x[1][k]-x[3][k];
        c[3][k] = x[2][k]-x[3][k];
    }
}

void Geometry::geometry_cell_center_surface(int i, array<array<double,3>,4> &x, Object &obj)
{
    for (int k = 0; k < 3; ++k)
    {
        obj.cell[i].x_c[k] = 0.25*(x[0][k]+x[1][k]+x[2][k]+x[3][k]); 

        obj.cell[i].x_cs[0][k] = 0.333*(x[0][k]+x[1][k]+x[2][k]);
        obj.cell[i].x_cs[1][k] = 0.333*(x[0][k]+x[1][k]+x[3][k]); 
        obj.cell[i].x_cs[2][k] = 0.333*(x[0][k]+x[2][k]+x[3][k]); 
        obj.cell[i].x_cs[3][k] = 0.333*(x[1][k]+x[2][k]+x[3][k]); 
    }
}

void Geometry::geometry_cell_edge(int i,array<array<double,3>,4> &a,array<array<double,3>,4> &b, array<array<double,3>,4> &c, Object &obj)
{
    obj.cell[i].edge[0] = sqrt(a[0][0]*a[0][0]+a[0][1]*a[0][1]+a[0][2]*a[0][2]);
    obj.cell[i].edge[1] = sqrt(b[1][0]*b[1][0]+b[1][1]*b[1][1]+b[1][2]*b[1][2]);
    obj.cell[i].edge[2] = sqrt(a[2][0]*a[2][0]+a[2][1]*a[2][1]+a[2][2]*a[2][2]);
    obj.cell[i].edge[3] = sqrt(c[0][0]*c[0][0]+c[0][1]*c[0][1]+c[0][2]*c[0][2]);
    obj.cell[i].edge[4] = sqrt(c[1][0]*c[1][0]+c[1][1]*c[1][1]+c[1][2]*c[1][2]);
    obj.cell[i].edge[5] = sqrt(c[2][0]*c[2][0]+c[2][1]*c[2][1]+c[2][2]*c[2][2]);
}

void Geometry::geometry_volume(int i,array<array<double,3>,4> &a,array<array<double,3>,4> &b,array<array<double,3>,4> &c, Object &obj)
{
    obj.cell[i].volume = abs(b[0][0]*(a[0][1]*c[0][2]-a[0][2]*c[0][1])-b[0][1]*(a[0][0]*c[0][2]-a[0][2]*c[0][0])+b[0][2]*(a[0][0]*c[0][1]-a[0][1]*c[0][0]))/6.0;    
}                           

void Geometry::geometry_cell_surface(int i,Object &obj)
{
    double p,ab,bc,ca;

    ab = obj.cell[i].edge[0];
    bc = obj.cell[i].edge[1];
    ca = obj.cell[i].edge[2];
    p = 0.5*(ab+bc+ca);
    obj.cell[i].surface[0] = sqrt(p*(p-ab)*(p-bc)*(p-ca));

    ab = obj.cell[i].edge[0];
    bc = obj.cell[i].edge[3];
    ca = obj.cell[i].edge[4];
    p = 0.5*(ab+bc+ca);
    obj.cell[i].surface[1] = sqrt(p*(p-ab)*(p-bc)*(p-ca));  

    ab = obj.cell[i].edge[2];
    bc = obj.cell[i].edge[5];
    ca = obj.cell[i].edge[3];
    p = 0.5*(ab+bc+ca);
    obj.cell[i].surface[2] = sqrt(p*(p-ab)*(p-bc)*(p-ca));      

    ab = obj.cell[i].edge[1];
    bc = obj.cell[i].edge[5];
    ca = obj.cell[i].edge[4];
    p = 0.5*(ab+bc+ca);
    obj.cell[i].surface[3] = sqrt(p*(p-ab)*(p-bc)*(p-ca));      

    obj.cell[i].full_surface = obj.cell[i].surface[0]+obj.cell[i].surface[1]+obj.cell[i].surface[2]+obj.cell[i].surface[3]; 
};