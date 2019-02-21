/// problem : 2314. (алгоритмы) Сортировка массива слиянием

#include <iostream>
#include <time.h>

using namespace std;

// прототипы функций
void merge_t(int*, int, int);
void mergeRec(int*, int, int);
int N;

int main() {
	cin >> N; // количество входных элементов
	// если пригодится для отладки, генератор случайных чисел
	// srand(time(NULL)); // инициализатор генератора
	// rand()%99 + 1: сгенерирует случайное число от 1 до 99.

	int* A = new int[N];
	for (int i = 0; i < N; i++) {
		cin >> A[i]; // заполнение массива
	}
	mergeRec(A, 0, N-1); // вызов сортировки

        for (int i = 0; i < N; i++) {
		cout << A[i] << " "; // печать
	}
	delete[] A; // освободили память
	return 0;
}

void mergeRec(int* A, int left, int right) {
	// рекурсивный вызов разделения, затем вызов слияния
	// необходимо реализовать
    if((right < left) || (left == right)) return;
    int mid = (left + right) / 2;
    mergeRec(A, left, mid);
    mergeRec(A, mid + 1, right);
    merge_t(A, left, right);
}

void merge_t(int *A, int left, int right){
	// процедура для слияния A[left .. mid] и A[mid+1 .. right];
	// необходимо реализовать
	int id_c = 0;
    int crr[right - left + 1];
    int mid = ((left + right) >> 1);
    int id_l = left;
    int id_r = mid + 1;
    while((id_l <= mid) && (id_r <= right)){
        if(A[id_l] < A[id_r]){
            crr[id_c] = A[id_l];
            id_l++;
            id_c++;
        }
        else {
            crr[id_c++] = A[id_r++];
        }
    }
    while(id_l <= mid){
        crr[id_c] = A[id_l];
        id_c++;
        id_l++;
    }
    while(id_r <= right){
        crr[id_c++] = A[id_r++];
    }
    for(int i = 0; i < id_c; i++){
        A[left + i] = crr[i];
    }
};
