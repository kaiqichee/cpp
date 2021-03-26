/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Kaiqi Chee
 * Version : 1.0
 * Date    : September 3, 2020
 * Description : Computes the square root of one or two command-line arguments.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iomanip>
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

double sqrt(double num, double epsilon = 0.0000001){
	if (num == 0 || num == 1){
		return num;
	}

	if (num < 0){
		return numeric_limits<double>::quiet_NaN();
	}

	double last_guess = num;
	double next_guess = (last_guess + (num/last_guess))/2;

	while (abs(last_guess - next_guess) > epsilon){
		last_guess = next_guess;
		next_guess = (last_guess + (num/last_guess))/2;
	}

	return next_guess;

}
int main(int argc, char *argv[]){
	double m,n;
	istringstream iss;

	if (argc < 2 || argc > 3){
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}

	iss.str(argv[1]);
	if ( !(iss >> m) ) {
		cerr << "Error: Value argument must be a double." << endl;
		return 1;
	}

	if (argc == 2){
		cout << fixed << setprecision(8) << sqrt(m) << endl;
	}

	if (argc == 3){
		iss.clear();
		iss.str(argv[2]);
		if ( !(iss >> n) || (n < 0) || (n == 0) ){
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
			}

		cout << fixed << setprecision(8) << sqrt(m,n) << endl;
	}
	return 0;

}



