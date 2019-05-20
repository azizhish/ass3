//: TMA3Question3.cpp

/*
 Description: Point Class
 Date: May 13, 2019
 Author: Hisham Aziz
 Version: 1.0
*/

/* 
 DOCUMENTATION
 
 Program Purpose:
 	To define a class Text with multiple constructors (1) With no argument, the 
 	default constructor (2) One String argument, filename/filepath. The Text
 	Object will read from this file upon initialization and store the text from
 	this file in a private member variable
 	Public Function: void contents(): prints to standard output the contents of
 	member variable i.e. the contents of the filename passed via Constructor 2

 Main Method is used to test the functionality of this program 

 Compile (assuming Cygwin is running): g++ -o TMA3Question3 TMA3Question3.cpp
 Execution (assuming Cygwin is running): ./TMA2Question3
 
 Notes: in Cygwin, main must return type int
 
 Classes: Text Class

 Variables:
 	text: instance of the Text Class
*/

/*
 TEST PLAN
 
 Actual Results
 	Out of 5 tests the difference between inline and non line was 2 seconds (4 times)
 	and was 1 second (on one attempt)

 */

#include <iostream>
using namespace std;


/*
Class declaration and function implementation for Text Class
 */
class Point{
	double x_coord;
	double y_coord;
public:
	Point(){}
	Point(double x, double y) : x_coord(x), y_coord(y) {}

	const Point operator+(const Point& other) const {
		return Point(x_coord + other.x_coord, y_coord + other.y_coord);
	}
	friend ostream& operator<<(ostream& os, const Point& p);

	void const print(){
		cout << "x: " << x_coord << ", y: " << y_coord << endl;
	}

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
public:
	Shape(): type("Generic"){}

	virtual double area(){
		return 0.0;
	}

	

	virtual double circumference(){
		return 1.0;
	}

	void display(){
		cout << "Type: " << type << endl;
		cout << "Area: " << area() << endl;
		cout << "Circumference: " << circumference() << endl;
		cout << "Bounding Box Coordinates: Min: "
			<< box.min << " Max: " << box.max << endl;
	}

};

class Circle: public Shape{
	Point center;
	double radius; // need to ensure this is positive and > 0
public:	
	Circle(Point c, double r): Shape(), center(c), radius(r){
		// assure(radius>0);
		type = "Circle";
	}

	double area(){
		return radius * radius * 3.14;
	}

	double circumference(){
		return 2 * radius * 3.14;
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
			cout << "Not a sqaure" << endl;
			exit(1);
		}
		type = "Square";
	}


private:

	void set_bounding(){
		Point min_p = min_point();
		Point max_p = max_point();
		box.min = min_p;
		box.max = max_p;
	}

	double dis_sq(Point p1, Point p2){
		return (p2.get_x() - p1.get_x()) * (p2.get_x() - p1.get_x()) + 
			(p2.get_y() - p1.get_y()) * (p2.get_y() - p1.get_y());
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




int main(int argc, char const *argv[])
{
	Square s(Point(1,0), Point(0, 0), Point(0,1), Point(1,1));
	s.display();
	return 0;
}
