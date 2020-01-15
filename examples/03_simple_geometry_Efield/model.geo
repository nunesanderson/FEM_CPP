mesh=0.05;
Point(1) = {1, 1, 0, mesh};
//+
Point(2) = {2, 1, 0, mesh};
//+
Point(3) = {1, 2, 0, mesh};
//+
Point(4) = {2, 2, 0, mesh};
//+
Line(1) = {3, 4};
//+
Line(2) = {4, 2};
//+
Line(3) = {2, 1};
//+
Line(4) = {1, 3};
//+
Curve Loop(1) = {1, 2, 3, 4};
//+
Plane Surface(1) = {1};
//+
Physical Surface(1) = {1};
//+
Physical Curve(2) = {4};
//+
Physical Curve(3) = {2};
//+
Physical Curve(4) = {3, 1};
