//: TMA3Question1.cpp

/*
 Description: Class to read a file and store in string
 Date: April 06, 2019
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

 Compile (assuming Cygwin is running): g++ -o TMA2Question3 TMA2Question3.cpp
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
#include <ctime>
#include <fstream>
using namespace std;


/*
Class declaration and function implementation for Text Class
 */
class DoubleCalculation{
	static const int limit = 10000;
	double first[limit];
	double second[limit];
public:
	DoubleCalculation(){}

	void calculation(){
		int k; 
		double temp;
		double incrementer = 0.0;
		for (int i = 0; i <limit; i++){
			temp = 100.00 + incrementer;
			first[i] = temp;
			k = limit - i - 1;
			second[k] = temp;
			incrementer++;
		}
		// Now calulate the multiplication of each correponding
		// element in the arrays and display to cout
		for (int i = 0; i < limit; i++){
			cout << multiply(first[i], second[i]) << endl;
		}
	}

	inline multiply (double d1, double d2){
		return d1 * d2;
	}
};

/*
	The main method. Used here to test the functionality of the Text Class
 */

int main(int argc, char const *argv[])
{
	const time_t start_time = time(NULL);
	DoubleCalculation calc = DoubleCalculation();
	calc.calculation();
	time_t elapsed_time = time(NULL);
	cout << "******** SEPERATOR *************" << endl;
	cout << "The program took " << difftime(elapsed_time, start_time) 
	<< " seconds" <<endl;
}
