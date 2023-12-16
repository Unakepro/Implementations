#include <iostream>
#include <vector>
<<<<<<< HEAD
=======
#include <cmath> 


struct Point {
	double x;
	double y;

	Point(double x_c = 0, double y_c = 0): x(x_c), y(y_c) {}

	bool operator==(const Point&);
	bool operator!=(const Point&);

};

class Line {
	double slope; 
	double intercept;

public:
	Line(double slope = 1, double intercept = 1): slope(slope), intercept(intercept) {}
	Line(const Point& p1, const Point& p2): slope(calc_slope(p1, p2)), intercept(calc_intercept(slope, p1)) {}
	Line(double slope, const Point& p): slope(slope), intercept(calc_intercept(slope, p)) {}


	double neg_reciprocal() {
		

		return -1/slope;
	}

	double get_slope() {
		return slope;
	}
	

	bool operator==(const Line&);
	bool operator!=(const Line&);

private:
	
	double calc_slope(const Point& p1, const Point& p2) {
		return (p2.y-p1.y) / (p2.x - p1.x);
	
	}

	double calc_intercept(double slope, const Point& p) {
		return p.y-(p.x*slope);	
	}


	friend std::ostream& operator<<(std::ostream&, const Line&);
};


class Shape {

protected:
	virtual double perimeter() = 0;
	virtual double area() = 0;
	virtual int verticesCount() = 0;
	virtual const std::vector<Point> getVertices() = 0;	
	

};

class Polygon: public Shape {
protected:	
	std::vector<Point> vertices;	

public:

	Polygon(std::vector<Point> ver): vertices(ver) {} 
	
	Polygon(std::initializer_list<Point> lst) {
		vertices.insert(vertices.end(), lst.begin(), lst.end());
	}
	

	bool isConvex() {
		int size = verticesCount();
		bool sign = true;		

		int vert; 

		
		vert = ((vertices[size-1].x - vertices[size-2].x) * (vertices[0].y - vertices[size-1].y)) -
		((vertices[size-1].y - vertices[size-2].y) * (vertices[0].x - vertices[size-1].x)); 
		
		sign = vert > 0 ? true: false;

		vert = ((vertices[0].x - vertices[size-1].x) * (vertices[1].y - vertices[0].y)) -
		((vertices[0].y - vertices[size-1].y) * (vertices[1].x - vertices[0].x));
		
		for(int i = 0; i < size-2; ++i) {
		

			if(!((vert > 0 && sign == true) || (vert < 0 && sign == false))) {
				return false;
			}

			vert = ((vertices[i+1].x - vertices[i].x) * (vertices[i+2].y - vertices[i+1].y)) -
		 	((vertices[i+1].y - vertices[i].y) * (vertices[i+2].x - vertices[i+1].x));
	
		
		}	
	
		return true;
	}


	int verticesCount() override {
		return vertices.size();
	}
	
	const std::vector<Point> getVertices() override {
		return vertices;
	}


	double perimeter() override {
		double sum = 0;
		for(int i = 0; i < verticesCount()-1; ++i) {
			sum += sqrt((pow(vertices[i+1].x - vertices[i].x, 2)) + (pow(vertices[i+1].y - vertices[i].y, 2)));
		}

		sum += sqrt((pow(vertices[verticesCount()-1].x - vertices[0].x, 2)) + (pow(vertices[verticesCount()-1].y - vertices[0].y, 2)));
		return sum;
	}
	
	double area() override {
		double area = 0;
		for(int i = 0; i < verticesCount()-1; ++i) {
			area += (vertices[i].x * vertices[i+1].y) -  (vertices[i+1].x * vertices[i].y);
		}
	
		area += (vertices[verticesCount()-1].x * vertices[0].y) -  (vertices[0].x * vertices[verticesCount()-1].y);
		area *= 0.5;
	
		return abs(area);
	}


};


class Ellipse: public Shape {
protected:	
	double x_c;
	double y_c;

	double k_a;
	double k_b;



public:
	Ellipse(const Point& f1, const Point& f2, double rsum) {
		double a;
		double b;
		double c;

	
		x_c = 0.5*(f1.x+f2.x);
		y_c = 0.5*(f1.y+f2.y);

		a = 0.5*rsum;
		c = 0.5*sqrt(pow(f2.x-f1.x, 2) + pow(f2.y-f1.y, 2));


		b = sqrt(pow(a, 2) - pow(c, 2)); 

		k_a = a;
		k_b = b;
	}

	Point center() {
		return Point(x_c, y_c);
	}

	std::pair<Point, Point> focuses() {
		Point f1;
		Point f2;
		double c;
	

		c = sqrt(pow(k_a, 2) - pow(k_b, 2));

		f1.x = x_c + c;
		f1.y = y_c;
			
		f2.x = x_c - c;
		f2.y = y_c;
	
		return std::pair<Point, Point>(f1, f2);	
	}

	double perimeter() override {
	
	}
	
	double area() override {

	}

	int verticesCount() override {
	
	}

	const std::vector<Point> getVertices() override {
		
	}


	friend std::ostream& operator<<(std::ostream&, const Ellipse&);

};


class Triangle: public Polygon {
	
public:

	Triangle(const Point& p1, const Point& p2, const Point& p3): Polygon{p1, p2, p3} {} 
	

	Point centroid() {
		double x;
		double y;

		x = (vertices[0].x + vertices[1].x + vertices[2].x)/3;
		y = (vertices[0].y + vertices[1].y + vertices[2].y)/3;

		return Point(x, y);
	}	


	Point orthocenter() {
		Line side1(vertices[0], vertices[1]);
		Line side2(vertices[1], vertices[2]);

		double b1;
		double b2;

		b1 = vertices[2].y - (vertices[2].x*side1.neg_reciprocal());
		b2 = vertices[0].y - (vertices[0].x*side2.neg_reciprocal());

		Point ort;

		ort.x = (b2-b1)/(side1.neg_reciprocal()-side2.neg_reciprocal()); 
		ort.y = side1.neg_reciprocal() * ort.x + b1;
		
		return ort;
	}

};


bool Point::operator==(const Point& obj) {
	return x == obj.x && y == obj.y;
}

bool Point::operator!=(const Point& obj) {
	return !(*this == obj);
}

bool Line::operator==(const Line& obj) {
	return slope == obj.slope && intercept == obj.intercept;
}

bool Line::operator!=(const Line& obj) {
	return !(*this == obj);
}

<<<<<<< HEAD
>>>>>>> 300b056 (added area/perimeter/isConvex)
=======
std::ostream& operator<<(std::ostream& out, const Point& obj) {
	out << obj.x << ' ' << obj.y << std::endl;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Line& obj) {
	out << obj.slope << ' ' << obj.intercept << std::endl;
	return out;
}
>>>>>>> 6afce01 (added centroid and ort center for triangle)


int main() {
	Point p1(-3, -2);
	Point p2(-1, 4);
	Point p3(6, 1);
	Point p4(3, 10);
	Point p5(-4, 9);
<<<<<<< HEAD

	Line ln1(1, 0);
	Line ln2(1, 0);
=======
>>>>>>> 300b056 (added area/perimeter/isConvex)

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
<<<<<<< HEAD
<<<<<<< HEAD
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

=======
		std::cout << p.x << ' ' << p.y << '\t' << std::endl;	
	}

>>>>>>> 300b056 (added area/perimeter/isConvex)
=======
		std::cout << p << '\t' << std::endl;	
	}

	Point fc1(3, 0);
	Point fc2(-3, 0);


	Ellipse el1(fc1, fc2, 10);
	std::cout << "Elipse center is: " << el1.center() << std::endl;
	std::cout << "Elipse focues are: " << '\n'; 
	std::cout << ' ' <<el1.focuses().first  << el1.focuses().second << std::endl; 	


	Triangle tr1(p1, p2, p3);
	std::cout << "Perimeter of trianle is " << tr1.perimeter() << std::endl;
	std::cout << "Area of triangle is " << tr1.area() << std::endl;
	std::cout << "Centroid of triangle is " << tr1.centroid() << std::endl;

	std::cout << "Orthocenter of triangle is " << tr1.orthocenter() << std::endl;
	
	
>>>>>>> 6afce01 (added centroid and ort center for triangle)
}
