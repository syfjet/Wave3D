//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {1, 0, 0, 1.0};
//+
Point(3) = {1, 1, 0, 1.0};
//+
Point(4) = {0, 1, 0, 1.0};
//+
Line(1) = {4, 4};
//+
Line(2) = {4, 3};
//+
Line(3) = {3, 2};
//+
Line(4) = {2, 1};
//+
Line(5) = {1, 4};
//+
Curve Loop(1) = {5, 2, 3, 4};
//+
Plane Surface(1) = {1};
//+
Transfinite Curve {5, 4, 3, 2} = 4 Using Progression 1;
