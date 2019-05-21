//: TMA3Question3.cpp

/*
 Description: Point Class, Shape Class, Circle Class, Square Class & Triangle Class
 Date: May 13, 2019
 Author: Hisham Aziz
 Version: 1.0
*/

/* 
 DOCUMENTATION
 
 Program Purpose:
 	Point Class: Point class to hold x and y values of a point. Overloaded
	the << operator to print point values and the + and – operators
	to add and subtract point coordinates. Suitable constructors added

	**Helper**
	Struct Bounding Box used to house two points that will be used to describe
	geometrically a rectangle that encloses a shape object. Geometrically only
	a minimum point and a maximum point is required to describe any rectangle

	Shape Class:  Base class Shape which will form the basis of our shapes.
	The Shape class contains functions to calculate area and circumference of 
	the shape, plus provide the coordinates (Points) of	a rectangle that encloses 
	the shape (a bounding box). These have been marked virtual where required to
	facillitate being effectively overridden by the derived classes as necessary. 
	Contains a display() function that will display the name of the class plus all stored
	information about the class (including area, circumference, and bounding box).

	Derived Classes:
	Circle(Point center, double r): Creates a circle with the Point center as the center
	and with a radius of r. Program ensures that radius is positive and non zero. If 
	these requirements are not met the program exits with exit code 1. 
	Functions area() and circumference() are overidden.

	Square(Point p1, Point p2, Point p3, Point p4): Creates an instance of Square class with
	four vertices described by the Point variables. Constructor tests to see if the points are such
	that any given point is equidistant from two of the other points and is the correct distance from
	the fourth point. 


 Main Method is used to test the functionality of this program 

 Compile (assuming Cygwin is running): g++ -o TMA3Question3 TMA3Question3.cpp
 Execution (assuming Cygwin is running): ./TMA2Question3
 
 Notes: in Cygwin, main must return type int
*/

/*
 TEST PLAN
 
 Actual Results
 	Out of 5 tests the difference between inline and non line was 2 seconds (4 times)
 	and was 1 second (on one attempt)

 */

# define M_PI           3.14159265358979323846  /* pi */
#include <iostream>
#include <math.h>
using namespace std;


/*
Class declaration and function implementation for Text Class
 */
class Point{
	double x_coord;
	double y_coord;
public:
	Point(): x_coord(0.0), y_coord(0.0){}
	Point(double x, double y) : x_coord(x), y_coord(y) {}

	const Point operator+(const Point& other) const {
		return Point(x_coord + other.x_coord, y_coord + other.y_coord);
	}

	const Point operator-(const Point& other) const {
		return Point(x_coord - other.x_coord, y_coord - other.y_coord);
	}

	friend ostream& operator<<(ostream& os, const Point& p);

	
	double get_x(){
		return x_coord;
	}

	double get_y(){
		return y_coord;
	}

};

struct Bounding_Box{
		Point min;
		Point max;
};

ostream& operator<<(ostream& os, const Point& p) {
	os << p.x_coord << ", " << p.y_coord;
	return os;
}
/*
	The main method. Used here to test the functionality of the Text Class
 */

class Shape{
protected: 
	string type;
	Bounding_Box box;
	//Distance Square Function Made Protected so that it can be used by
	//all derived classes
	double dis_sq(Point p1, Point p2){
		return (p2.get_x() - p1.get_x()) * (p2.get_x() - p1.get_x()) + 
			(p2.get_y() - p1.get_y()) * (p2.get_y() - p1.get_y());
	}

public:
	Shape(): type("Generic"){}

	virtual const double area(){
		return 0.0;
	}	

	virtual const double circumference(){
		return 0.0;
	}

	void display(){
		cout << "Type: " << type << endl;
		cout << "Area: " << area() << endl;
		cout << "Circumference: " << circumference() << endl;
		cout << "Bounding Box Coordinates: Min: ("
			<< box.min << ") Max: (" << box.max << ")" << endl;
	}
// private:
// 	set_bounding(){
// 		box.max	= Point(0,0);
// 	}


};

class Circle: public Shape{
	Point center;
	double radius; // need to ensure this is positive and > 0
public:	
	Circle(Point c, double r): Shape(), center(c), radius(r){
		if (radius <= 0){
			exit(1);
		}
		type = "Circle";
		set_bounding();
	}

	const double area(){
		return radius * radius * M_PI;
	}

	const double circumference(){
		return 2 * radius * M_PI;
	}

private:
	set_bounding(){		
		box.min = center - Point(radius, radius);
		box.max = center + Point(radius, radius);
	}
};

/*
	The derived class Square: derived from Shape
	Constructor takes four points but only initializes the object
	if the four points forms a sqaure. Invalid arguments result in 
	exit(1) from whereever the code is run with an appropriate message
	to standard output. 
*/

class Square: public Shape{
	Point v1, v2, v3, v4;
public:
	Square(Point p1, Point p2, Point p3, Point p4):
		Shape(), v1(p1), v2(p2), v3(p3), v4(p4)
	{
		if (!is_square()){
			cout << "Not a square" << endl;
			exit(1);
		}
		type = "Square";
		set_bounding();
	}

	const double area(){
		double v1_v2 = dis_sq(v1, v2);
		double v1_v3 = dis_sq(v1, v3);
		double v1_v4 = dis_sq(v1, v4);
		double v2_v3 = dis_sq(v2, v3);
		double v3_v4 = dis_sq(v3, v4);
		double v2_v4 = dis_sq(v2, v4);

		//If v1 is adjacent to v2 and v3 then v1-->v2 == v1-->v3 = (X)
		//And (X) + (X) = v1-->v4 = v2-->v3
		if(v1_v2 == v1_v3){
			return v1_v2;
		}

		// Since we have already confirmed that this is a square that
		// means that v1 is adjacent to v4
		else{
			return v1_v4;
		}
	}

	const double circumference(){
		double v1_v2 = dis_sq(v1, v2);
		double v1_v3 = dis_sq(v1, v3);
		double v1_v4 = dis_sq(v1, v4);
		double v2_v3 = dis_sq(v2, v3);
		double v3_v4 = dis_sq(v3, v4);
		double v2_v4 = dis_sq(v2, v4);

		//If v1 is adjacent to v2 and v3 then v1-->v2 == v1-->v3 = (X)
		//And (X) + (X) = v1-->v4 = v2-->v3
		if(v1_v2 == v1_v3){
			return sqrt(v1_v2) * 4;
		}

		// Since we have already confirmed that this is a square that
		// means that v1 is adjacent to v4
		else{
			return sqrt(v1_v4) * 4;
		}
	}


private:

	void set_bounding(){
		Point min_p = min_point();
		Point max_p = max_point();
		box.min = min_p;
		box.max = max_p;
	}

	

	//Basis is that a point in a sqaure is equidistant from two other points
	//And the remaining point forms a diagonal/side of a right angle triangle
	bool is_square(){
		double v1_v2 = dis_sq(v1, v2);
		double v1_v3 = dis_sq(v1, v3);
		double v1_v4 = dis_sq(v1, v4);
		double v2_v3 = dis_sq(v2, v3);
		double v3_v4 = dis_sq(v3, v4);
		double v2_v4 = dis_sq(v2, v4);

		//If v1 is adjacent to v2 and v3 then v1-->v2 == v1-->v3 = (X)
		//And (X) + (X) = v1-->v4 = v2-->v3
		if(v1_v2 == v1_v3){
			return (v1_v4 == v2_v3) && (v1_v4 == 2 * v1_v2);
		}

		//Case 2, v1 is next to v3 and v4 and accross from v2
		if(v1_v4 == v1_v3){
			return (v1_v2 == v3_v4) && (v1_v2 == 2 * v1_v4);
		}

		//The only remaining case
		if (v1_v4 == v1_v2){
			return (v1_v3 == v2_v4) && (v1_v3 == 2 * v1_v4);
		}

		//V1 is not equidistant from any two points from within 
		//V2, V3 or V4, hence the points cannot form a square
		return false;
	}

	Point min_point(){
		double x, y;
		x = min(v1.get_x(), v2.get_x());
		x = min(x, v3.get_x());
		x = min(x, v4.get_x());
		y = min(v1.get_y(), v2.get_y());
		y = min(y, v3.get_y());
		y = min(y, v4.get_y());
		return Point(x,y);
	}

	Point max_point(){
		double x, y;
		x = max(v1.get_x(), v2.get_x());
		x = max(x, v3.get_x());
		x = max(x, v4.get_x());
		y = max(v1.get_y(), v2.get_y());
		y = max(y, v3.get_y());
		y = max(y, v4.get_y());
		return Point(x,y);
	}
};

class Triangle : public Shape{
	Point v1, v2, v3;
public:
	Triangle(Point p1, Point p2, Point p3):
		Shape(), v1(p1), v2(p2), v3(p3)
	{
		if (!is_triangle()){
			cout << "Not a triangle" << endl;
			exit(1);
		}
		type = "Triangle";
		set_bounding();
	}

	// Formula: Area = | 0.5(x1(y2-y3) + x2(y3-y1) + x3(y1-y2)) |
	const double area(){
		double x1, x2, x3, y1, y2, y3;
		x1 = v1.get_x(); x2 = v2.get_x(); x3 = v3.get_x();
		y1 = v1.get_y(); y2 = v2.get_y(); y3 = v3.get_y();
		return abs(0.5 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
	}

	const double circumference(){
		return sqrt(dis_sq(v1, v2)) + sqrt(dis_sq(v1, v3)) + sqrt(dis_sq(v2, v3));
	}

private:
	bool is_triangle(){
		double v1_v2 = sqrt(dis_sq(v1, v2));
		double v1_v3 = sqrt(dis_sq(v1, v3));
		double v2_v3 = sqrt(dis_sq(v2, v3));

		if ((v1_v2 + v1_v3 <= v2_v3) || (v1_v2 + v2_v3 <= v1_v3) || (v2_v3 + v1_v3 <= v1_v2))
			return false;
		else
			return true;
	}

	void set_bounding(){
		Point min_p = min_point();
		Point max_p = max_point();
		box.min = min_p;
		box.max = max_p;
	}

	Point min_point(){
		double x, y;
		x = min(v1.get_x(), v2.get_x());
		x = min(x, v3.get_x());
		
		y = min(v1.get_y(), v2.get_y());
		y = min(y, v3.get_y());
		
		return Point(x,y);
	}

	Point max_point(){
		double x, y;
		x = max(v1.get_x(), v2.get_x());
		x = max(x, v3.get_x());
		
		y = max(v1.get_y(), v2.get_y());
		y = max(y, v3.get_y());
		
		return Point(x,y);
	}
	
};




int main(int argc, char const *argv[])
{
	// Circle with Radius 23
	Circle* c = new Circle(Point(0.0, 0), 23.0);
	c->display();

	// Square with side length 25
	Square s(Point(-5.0,-5.0), Point(-5.0, 20), Point(20, -5), Point(20, 20));
	s.display();

	Triangle* t = new Triangle(Point(0,0), Point(0,10), Point(0,-20));
	t->display();
}
