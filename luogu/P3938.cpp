#include <iostream>

int m;
long long fib[60];

int main() {
    scanf("%d", &m);
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i <= 60; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    
    return 0;
} 
