//problem : 2289. (рекурсия) Степень числа
#include <iostream>
using namespace std;

double Power(double, int);

int main(){
	double X;
	int N;
	cin >> X >> N;
	cout << Power(X, N);
	return 0;
}

double Power(double x, int n){
	if(n == 0) return 1;
	if(n < 0) return 1. / Power(x, -n);
	if(n % 2 == 0){
		double a = Power(x, n / 2);
		return a * a;
	}
	return x * Power(x, n - 1);
} 
