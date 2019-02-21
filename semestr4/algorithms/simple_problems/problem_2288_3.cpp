// problem : 2288. (рекурсия) Число сочетаний
// solution_3. 
// Lets imagine that C(k+1,n) = X*C(k,n)
// Then 
//           n!                      n!
//  ---------------------- = X * -------------- 
//  (k + 1)! * (n - k - 1)        k! * (n - k)!
// So X = (n - k) / (k + 1)
#include <iostream>
using namespace std;

int Combin(int n, int k){

	if(k == 0) return 1;
	if(n == k) return 1;
	int ans = Combin(n, k - 1);
	ans = (ans * (n - (k - 1))) / k;
	return ans;
} 

int main(){
	int N, K;
	cin >> N >> K;
	cout << Combin(N, K);
	return 0;
}
