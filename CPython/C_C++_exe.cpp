/*************************************************************************
	> File Name: C_C++_exe.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  8/10 22:13:26 2019
 ************************************************************************/

#include<iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << add(a, b) << endl;
    cout << "---end---" << endl;
    return 0;
}
