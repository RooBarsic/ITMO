/// problem : 2300. (тренировка) Умножение полиномов

#include <iostream>

using namespace std;

void MultPoly(int *, int *, int, int, int *);
void printres(int *, int *, int, int, int *);

int main() {
   int pA, pB;
   int *A, *B, *C;
   cin >> pA >> pB;
   A = new int[pA+1];
   B = new int[pB+1];
   C = new int[pA+pB+1];
   int k;
   for (int i=0; i<=pA; i++) {
      cin >> k;
      A[i] = k;
   }
   for (int i=0; i<=pB; i++) {
      cin >> k;
      B[i] = k;
   }

   for (int i=0; i<=pA+pB; i++) {
      C[i] = 0;
   }
   MultPoly(A, B, pA, pB, C);
   printres(A, B, pA, pB, C);
   return 0;
}


void MultPoly(int *A, int *B, int pA, int pB, int *C) {
// ЭТО ФУНКЦИЯ, КОТОРУЮ ВЫ ДОЛЖНЫ НАПИСАТЬ
// A и B - полиномы - сомножители
// pA и pB - их порядки
// С - полином-результат
    for(int i = 0; i <= pA; i++){      /// проходимся по каждому члену первого полинома, через i
        for(int j = 0; j <= pB; j++){  /// проходимся по каждому члену второго полинома, через j
            C[i + j] += A[i] * B[j];   /// произведение iтого члена первого полинома на jтый член второго полинома -> i+jтый член
        }                                /// результируюшего полинома, приэтом коэффициенты умножаются
    }
}

void printres(int *A, int *B, int pA, int pB, int *C) {
   cout << "C = ";
   if (pA+pB > 1) {
      if (C[0]!=1) {
         cout << C[0] << "*x^";
      } else {
         cout << "x^";
      }
      cout << pA+pB;
      for (int i=1; i<=pA+pB-2; i++) {
         cout << " + ";
         if (C[i]!=1) {
            cout << C[i] << "*x^";
         } else {
            cout << "x^";
         }
         cout << pA+pB-i;
      }
      cout << " + " << C[pA+pB-1] << "*x" << " + " << C[pA+pB] << endl;
   }
   else{
      if(pA+pB==0)
         cout << C[0] << endl;
      if(pA+pB==1)
         cout << C[0]<<"*x" << "+" << C[1] << endl;
   }
}
