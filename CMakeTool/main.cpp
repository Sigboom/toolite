/*************************************************************************
	> File Name: main.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 日  7/14 11:22:31 2019
 ************************************************************************/

#include <iostream>
#include "config.h"

#ifdef HAVE_POW
	#include <cmath>
#else
	#include "math/MathFunctions.h"
#endif

using namespace std;

int main(int argc, char **argv) {
	if (argc < 3) {
		cout << argv[0] << " Version " << power_VERSION_MAJOR \
			<< "." << power_VERSION_MINOR << endl;
		cout << "Usage: " << argv[0] << " base exponent" << endl;
		return 1;
	}

	double base = atof(argv[1]);
	int exponent = atoi(argv[2]);
#ifdef HAVE_POW
	cout << "using standard pow function" << endl;
	double result = pow(base, exponent);
#else
	cout << "using my power function" << endl;
	double result = power(base, exponent);
#endif
	cout << base << " ^ " << exponent << " = " << result << endl;
	return 0;
}
