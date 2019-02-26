#include"test.c"
#include<stdio.h>
int main(){
	printf("sdgsg");
	char* arr = m_malloc(sizeof(char) * 10);
	*arr = '1';
	*(arr + 1) = '2';
	arr[2] = '3';
	arr[3] = '5';
	printf("%s", arr);
	m_free(arr);
}
