/*************************************************************************
	> File Name: Hello.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  8/10 21:50:18 2019
 ************************************************************************/

#include<iostream>
using namespace std;

extern "C" {
    int hello() {
        cout << "Hello World!" << endl;
    return 0;
    }
}
