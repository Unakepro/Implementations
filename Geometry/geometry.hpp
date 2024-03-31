#ifndef GEOMETRY
#define GEOMETRY

#include <iostream>
#include <vector>


struct Point {
	double x = 0.0;
	double y = 0.0;

	Point(double x_c = 0, double y_c = 0);

	bool operator==(const Point&) const;
	bool operator!=(const Point&) const;
	
	friend std::ostream& operator<<(std::ostream&, const Point&);
};

class Line {
	double slope = 0.0; 
	double intercept = 0.0;

public:
	Line(double slope = 1, double intercept = 1);
    Line(const Point& p1, const Point& p2);

    Line(double slope, const Point& p);

	double neg_reciprocal() const;
	double get_slope() const;
	

	bool operator==(const Line&) const;
	bool operator!=(const Line&) const;

private:
	
	double calc_slope(const Point& p1, const Point& p2) const;
	double calc_intercept(double slope, const Point& p) const;

	friend std::ostream& operator<<(std::ostream&, const Line&);
};


class Shape {

protected:
	virtual double perimeter() const = 0;
	virtual double area() const = 0;
	virtual int verticesCount() const = 0;
	virtual const std::vector<Point> getVertices() const = 0;	
	
public:
	bool operator==(const Shape& another) const;

};

class Polygon: public Shape {
protected:	
	std::vector<Point> vertices;	

public:
	Polygon(std::vector<Point> ver);
	Polygon(std::initializer_list<Point> lst);

	bool isConvex() const;

	int verticesCount() const override;
	const std::vector<Point> getVertices() const override;

	double perimeter() const override;
	double area() const override;

};


class Ellipse: public Shape {
protected:	
	double x_c = 0.0;
	double y_c = 0.0;

	double k_a = 0.0;
	double k_b = 0.0;



public:
	Ellipse(const Point& f1, const Point& f2, double rsum);

	Point center() const;

	std::pair<Point, Point> focuses() const;	
	std::pair<Line, Line> directrices() const;
	
	double eccentricity() const;
	double perimeter() const override;
	double area() const override;
	
	int verticesCount() const override;
	const std::vector<Point> getVertices() const override;

	friend std::ostream& operator<<(std::ostream&, const Ellipse&);

};


class Circle: public Ellipse {
public:
	Circle(const Point& center, double radius);
	double radius();

};

class Rectangle: public Polygon {
public:
	Rectangle(const Point& a, const Point& c);

	Point center() const;
	std::pair<Line, Line> diagonals() const;

};

class Square: public Rectangle {
public:
	Square(const Point& a, const Point& c);
	
	Circle circumscribedCircle() const;
	Circle inscribedCircle() const;

};


class Triangle: public Polygon {
public:
	Triangle(const Point& p1, const Point& p2, const Point& p3);
	
	double sideBA() const;
	double sideCB() const;
	double sideCA() const;
	
	Circle inscribedCircle() const;
	
	Point centroid() const;
	Point incenter() const;
	Point orthocenter() const;

};


#endif