// problem : 2288. (рекурсия) Число сочетаний
#include <iostream>
using namespace std;

int Combin(int, int);

int main(){
	int N, K;
	cin >> N >> K;
	cout << Combin(N, K);
	return 0;
}

int Combin(int n, int k){

	if(k == 0) return 1;
	if(n == k) return 1;
	return Combin(n - 1, k) + Combin(n - 1, k - 1);

} 
