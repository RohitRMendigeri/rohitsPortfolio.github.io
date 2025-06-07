#include <bits/stdc++.h>
using namespace std;

int power(int x, unsigned int y, unsigned int m) {
    if (y == 0)
        return 1;

    int p = power(x, y / 2, m) % m;
    p = (1LL * p * p) % m;

    if (y % 2 == 0)
        return p;
    else
        return (1LL * x * p) % m;
}

void modInverse(int a, int m) {
    if (__gcd(a, m) != 1)
        cout << "Inverse doesn't exist";
    else
        cout << "Modular multiplicative inverse is "
             << power(a, m - 2, m);
}

int main() {
    int a = 3, m = 11;
    modInverse(a, m);
    return 0;
}
