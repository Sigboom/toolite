/*************************************************************************
	> File Name: lucas.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 二  3/12 10:14:24 2019
 ************************************************************************/

#include <iostream>
#define N 20000
#define P 10007

using std::cin;

//C++求C(n, m) mod 10007    版本二 要求p z在100000左右
long f[N];
void init(int p) {
    f[0] = 1;
    for (int i=1; i<=p; ++i) f[i] = f[i-1] * i % p;
} 

long pow_mod(long a, long x, int p) {
    long ret = 1;
    while (x)
        {
        if (x & 1)  ret = ret * a % p;
        a = a * a % p;
        x >>= 1;
    }
    return ret;
}
  
long Lucas(long n, long k, int p) {
     long ret = 1;
     while (n && k) {
        long nn = n % p, kk = k % p;
        if (nn < kk) return 0;  //inv (f[kk]) = f[kk] ^ (p - 2) % p
        ret = ret * f[nn] * pow_mod (f[kk] * f[nn-kk] % p, p - 2, p) % p;
        n /= p, k /= p;
     }
     return ret;
}

int main() {
    init (P);
    int n, m;
    cin >> n >> m;
    printf ("%ld\n", Lucas (n, m, P));
    return 0;
}
