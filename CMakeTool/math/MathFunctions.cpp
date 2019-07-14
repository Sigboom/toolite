/*************************************************************************
	> File Name: MathFunction.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 日  7/14 12:37:53 2019
 ************************************************************************/

double power(double base, int exp) {
	int result = 1;

	for (int i = 0; i < exp; ++i) result *= base;

	return result;
}

