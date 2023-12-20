#include <iostream>

using namespace std;

int factorial(int n){
    if(n == 0){
        return 1;
    }
    else {
        return n * factorial(n-1);
    }
}

int gcd(int a, int b){
    if(b == 0){
        return a;
    }
    else{
        return gcd(b, a%b);
    }
}

int main(){

    cout << factorial(5);

    return 0;
}