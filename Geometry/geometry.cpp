#include <iostream>
#include <vector>
#include <cmath> 
#include "geometry.hpp"

Point::Point(double x_c, double y_c): x(x_c), y(y_c) {}

Line::Line(double slope, double intercept): slope(slope), intercept(intercept) {}
	
Line::Line(const Point& p1, const Point& p2) {
	slope = calc_slope(p1, p2);
	intercept = calc_intercept(slope, p1);
}	


Line::Line(double slope, const Point& p): slope(slope) {
	intercept = calc_intercept(slope, p);
}

double Line::neg_reciprocal() const {
	return -1/slope;
}

double Line::get_slope() const {
	if(slope > 30000 || slope < -30000) {
		throw std::logic_error("To wide ranges of slope");
	}
	return slope;
}
	
double Line::calc_slope(const Point& p1, const Point& p2) const {
	return (p2.y-p1.y) / (p2.x - p1.x);

}

double Line::calc_intercept(double slope, const Point& p) const {
	return p.y-(p.x*slope);	
}

bool Shape::operator==(const Shape& another) const {
	return getVertices() == another.getVertices();
}

Polygon::Polygon(std::vector<Point> ver): vertices(ver) {} 
Polygon::Polygon(std::initializer_list<Point> lst) {
	vertices.insert(vertices.end(), lst.begin(), lst.end());
}

bool Polygon::isConvex() const {
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

int Polygon::verticesCount() const {
	return vertices.size();
}

const std::vector<Point> Polygon::getVertices() const {
	return vertices;
}

double Polygon::perimeter() const {
	double sum = 0;
	for(int i = 0; i < verticesCount()-1; ++i) {
		sum += sqrt((pow(vertices[i+1].x - vertices[i].x, 2)) + (pow(vertices[i+1].y - vertices[i].y, 2)));
	}

	sum += sqrt((pow(vertices[verticesCount()-1].x - vertices[0].x, 2)) + (pow(vertices[verticesCount()-1].y - vertices[0].y, 2)));
	return sum;
}

double Polygon::area() const {
	double area = 0;
	for(int i = 0; i < verticesCount()-1; ++i) {
		area += (vertices[i].x * vertices[i+1].y) -  (vertices[i+1].x * vertices[i].y);
	}

	area += (vertices[verticesCount()-1].x * vertices[0].y) -  (vertices[0].x * vertices[verticesCount()-1].y);
	area *= 0.5;

	return abs(area);
}

Ellipse::Ellipse(const Point& f1, const Point& f2, double rsum) {
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

Point Ellipse::center() const {
	return Point(x_c, y_c);
}

std::pair<Point, Point> Ellipse::focuses() const {
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

double Ellipse::eccentricity() const {
	double c = sqrt(pow(k_a, 2) - pow(k_b, 2));
	return c/k_a;
}

std::pair<Line, Line> Ellipse::directrices() const {
	Line ln1(1, center().x + -k_a/eccentricity());
	Line ln2(1, center().x + k_a/eccentricity()); 

	return std::pair<Line, Line>(ln1, ln2);
}

double Ellipse::perimeter() const {
	return 4 * k_a * std::ellint_2(eccentricity(), M_PI_2);
}

double Ellipse::area() const {
	return M_PI*k_a*k_b;
}

int Ellipse::verticesCount() const {
	return 0;
}

const std::vector<Point> Ellipse::getVertices() const {
	return std::vector<Point>();
}


Circle::Circle(const Point& center, double radius): Ellipse(center, center, radius*2) {}

double Circle::radius() {
	return k_a;
}

Rectangle::Rectangle(const Point& a, const Point& c): Polygon({a, Point(c.x, a.y), c, Point(a.x, c.y)}) {}

Point Rectangle::center() const {
	return Point((vertices[0].x+vertices[2].x)/2, (vertices[0].y+vertices[2].y)/2);
}

std::pair<Line, Line> Rectangle::diagonals() const {
	return std::pair<Line, Line>(Line(vertices[0],vertices[2]), Line(vertices[1], vertices[3]));
}


Square::Square(const Point& a, const Point& c): Rectangle(a, c) {}

Circle Square::circumscribedCircle() const {
	double AB = sqrt(pow(vertices[1].x-vertices[0].x, 2) + pow(vertices[1].y-vertices[0].y, 2));
	return Circle(center(), AB/sqrt(2));
}


Circle Square::inscribedCircle() const {
	double AB = sqrt(pow(vertices[1].x-vertices[0].x, 2) + pow(vertices[1].y-vertices[0].y, 2));
	return Circle(center(), AB/2); 
}


Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3): Polygon{p1, p2, p3} {} 


double Triangle::sideBA() const {
	return sqrt(pow(vertices[0].x-vertices[1].x, 2)+pow(vertices[0].y-vertices[1].y, 2));
}


double Triangle::sideCB() const {
	return sqrt(pow(vertices[1].x-vertices[2].x, 2)+pow(vertices[1].y-vertices[2].y, 2));
}

double Triangle::sideCA() const {
	return sqrt(pow(vertices[0].x-vertices[2].x, 2)+pow(vertices[0].y-vertices[2].
	y, 2));
}

Circle Triangle::inscribedCircle() const {
	return Circle(incenter(), area()/(perimeter()*0.5)); 
}


Point Triangle::centroid() const {
	double x;
	double y;

	x = (vertices[0].x + vertices[1].x + vertices[2].x)/3;
	y = (vertices[0].y + vertices[1].y + vertices[2].y)/3;

	return Point(x, y);
}


Point Triangle::incenter() const {
	double BA;
	double CB;
	double CA;

	BA = sideBA();
	CB = sideCB();
	CA = sideCA();

	return Point((vertices[0].x*CB+vertices[1].x*CA+vertices[2].x*BA)/(BA+CB+CA), (vertices[0].y*CB+vertices[1].y*CA+vertices[2].y*BA)/(BA+CB+CA));

}	


Point Triangle::orthocenter() const {
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


bool Point::operator==(const Point& obj) const {
	return x == obj.x && y == obj.y;
}

bool Point::operator!=(const Point& obj) const {
	return !(*this == obj);
}

bool Line::operator==(const Line& obj) const {
	return slope == obj.slope && intercept == obj.intercept;
}

bool Line::operator!=(const Line& obj) const {
	return !(*this == obj);
}

std::ostream& operator<<(std::ostream& out, const Point& obj) {
	out << obj.x << ' ' << obj.y << std::endl;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Line& obj) {
	out << obj.slope << ' ' << obj.intercept << std::endl;
	return out;
}