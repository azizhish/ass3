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
	Point(double x, double y) : x_coord(x), y_coord(y) {}

	const Point operator+(const Point& other) const {
		return Point(x_coord + other.x_coord, y_coord + other.y_coord);
	}
	friend ostream& operator<<(ostream& os, const Point& p);

	void const print(){
		cout << "x: " << x_coord << ", y: " << y_coord << endl;
	}

};

ostream& operator<<(ostream& os, const Point& p) {
	os << p.x_coord << ", " << p.y_coord;
	return os;
}
/*
	The main method. Used here to test the functionality of the Text Class
 */

int main(int argc, char const *argv[])
{
	Point p(1.0, 2.5);
	Point q(2.0, 3.5);
	Point temp = p + q;
	temp.print();
	cout << temp;
	return 0;
}
