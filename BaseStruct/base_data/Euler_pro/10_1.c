/*************************************************************************
    > File Name: 10.c
    > Author: ma6174 
    > Mail: ma6174@163.com 
    > Created Time: 日  4/ 1 10:38:46 2018 
************************************************************************/
#include <stdio.h> 
#include <math.h> 
#include <inttypes.h> 
#define MAX 2000000 
int is_prime(int n) {
    for (int i = 2; i <= sqrt(n); ++i) {
	    if(!(n % i)) {
	        return 0;
	    }
    }
    return 1;
}
int main() {
    int64_t sum = 0;
    for (int i = 2; i < MAX; ++i) {
        if(is_prime(i)){
            sum += i;
        }
    }
    printf("%"PRId64"\n", sum);
    return 0;
}
