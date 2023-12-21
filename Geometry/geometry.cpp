#include <iostream>
#include <vector>
#include <cmath> 
#include "geometry.hpp"



int main() {
	Point p1(-3, -2);
	Point p2(-1, 4);
	Point p3(6, 1);
	Point p4(3, 10);
	Point p5(-4, 9);

	Line ln1(1, 0);
	Line ln2(1, 0);

	std::cout << (p1==p2) << std::endl;
	std::cout << (ln1==ln2) << std::endl;


	Polygon pl1{p1, p2, p3, p4, p5};

	std::cout << "Number of vertices " << pl1.verticesCount() << std::endl;
	std::cout << "Perimeter is " << pl1.perimeter() << std::endl;
	std::cout << "Area is " << pl1.area() << std::endl;
	std::cout << "Is convex: " << pl1.isConvex() << std::endl;
	
	for(auto p: pl1.getVertices()) {
		std::cout << p << '\t' << std::endl;	
	}

	Point fc1(3, 0);
	Point fc2(-3, 0);


	Ellipse el1(fc1, fc2, 10);
	std::cout << "Elipse center is: " << el1.center() << std::endl;
	std::cout << "Elipse focues are: " << '\n'; 
	std::cout << ' ' <<el1.focuses().first  << el1.focuses().second << std::endl; 	
	
	std::cout << "Eccentricity is: " << el1.eccentricity() << std::endl;
	std::cout << "Elipse directrices are: " << '\n'; 
	std::cout << el1.directrices().first << el1.directrices().second << std::endl; 	
	std::cout << "Elipse area is: " << el1.area() << std::endl;	
	std::cout << "Elipse perimeter is: " << el1.perimeter() << std::endl;	
	std::cout << "Elipse vertices count is: " << el1.verticesCount() << std::endl;




	Point cc(0, 0);
	Circle cl1(cc, 5);

	std::cout << '\n';	
	std::cout << "Circle area is: " << cl1.area() << std::endl;
	std::cout << "Circle perimeter is: " << cl1.perimeter() << std::endl;
	std::cout << "Circle radius is: " << cl1.radius() << '\n' << std::endl;


	Point pa(0, 0);
	Point pc(4, 3);

	Rectangle rec1(pa, pc);
	std::cout << "Center of rectange is: " << rec1.center() << std::endl;
	std::cout << "Diagonals are: " << rec1.diagonals().first << ' ' <<
	rec1.diagonals().second << std::endl;

	Triangle tr1(p1, p2, p3);
	
	std::cout << '\n';
	std::cout << "Perimeter of trianle is " << tr1.perimeter() << std::endl;
	std::cout << "Area of triangle is " << tr1.area() << std::endl;
	std::cout << "Centroid of triangle is " << tr1.centroid() << std::endl;

	std::cout << "Orthocenter of triangle is " << tr1.orthocenter() << '\n' << std::endl;
	
	Shape& obj1 = tr1;
	Shape& obj2 = tr1;
	Shape& obj3 = rec1; 
	std::cout << "Comparing figures: " << std::endl;
	
	std::cout << "Triangles: " << std::endl;
	std::cout << (obj1==obj2) << std::endl;
	
	std::cout << "Triangle and rectangle: " << std::endl;
	std::cout << (obj1==obj3) << std::endl;

}
