# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <math.h>
  typedef unsigned long long ull;
  ull pows2[70];
  void fil() {
    pows2[0] = 1ll;
    for (int i = 1; i <= 63; ++i)
        pows2[i] = pows2[i - 1] * 2ll;
  }
  ull mul_mod(ull a, ull b, ull mod){
	  ull res = 0;
	  while(b > 0){
		  if(b & 1 > 0) res = (res + a) % mod;
		  a = (a * 2ll) % mod;
		  b >>= 1;
	  }
	  return res;
  }
  ull pow_mod(ull a, ull b, ull mod){
	  ull res = 1;
	  while(b > 0){
		  if(b & 1 > 0) res = mul_mod(res, a, mod);
		  a = mul_mod(a, a, mod);
		  b >>= 1;
	  }
	  return res;
  }
  
  int miller_rabin_test(ull p){
	  if(p == 1) return 0;
	  ull s = 0, d = p - 1;
	  while(d % 2 == 0){
		  d = (d >> 1);
		  s++;
	  }
	  srand(time(NULL));
	  for(int i = 1; i <= 5; i++){
		  ull a = ((rand() * rand()) % p);
		  if(a == 0) a++;
		  
		  int flag1 = 0, flag2 = 0;
		  if(pow_mod(a % p, d, p) == 1) flag1 = 1;
		  if(flag1 == 0){
			  for(int r = 0; r < s; r++){
				  if(pow_mod(a % p, pows2[r] * d, p) == p - 1) flag2 = 1;
			  }
		  }
		  if(!flag1 && !flag2) return 0;
	  }
	  return 1;
  }
  
  int is_prime(ull n){
	  if((miller_rabin_test(n) == 0)) return 0;
	  return 1;
  }
  int main(){
	  ull n;
	  fil();
	  scanf("%llu", &n);
	  if(is_prime(n) == 1) printf("YES");
	  else printf("NO");
	  return 0;
  }
