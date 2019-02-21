// problem : 2288. (рекурсия) Число сочетаний
// solution_2. If I cout C(n,k), then I remeber result
//             and in the next time - I just use remembered result.
#include <iostream>
using namespace std;

int arr[110][110];

int Combin(int n, int k){

	if(k == 0) return 1;
	if(n == k) return 1;
	if(arr[n][k] != 0) return arr[n][k];
	arr[n][k] = Combin(n - 1, k) + Combin(n - 1, k - 1);
	return arr[n][k];
} 

int main(){
	int N, K;
	cin >> N >> K;
	cout << Combin(N, K);
	return 0;
}
