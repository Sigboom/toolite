/*************************************************************************
	> File Name: 10_third_find.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 六  7/28 15:02:08 2018
 ************************************************************************/

#include <stdio.h>
#include <math.h>

#define EPS 1e-6

double f(double, double, double, double);
double three_point_find(double, double, double);

int main() {
    double a, b, c;
    while (scanf("%lf%lf%lf", &a, &b, &c)) {
        printf("%lf\n", three_point_find(a, b, c));
    }
    return 0;
}

double f(double x, double a, double b, double c) {
    return a * x * x + b * x + c;
}

double three_point_find(double a, double b, double c) {
    double head = -10000, tail = 10000, m1, m2;
    if (a > 0) {
        a = -a;
        b = -b;
        c = -c;
    }
    while (fabs(tail - head) > EPS) {
        m1 = (tail - head) / 3 + head;
        m2 = (tail - head) / 3 * 2 + head;
        if (f(m1, a, b, c) < f(m2, a, b, c)) {
            head = m1;
        } else {
            tail = m2;
        }
    }
    return head;
}
