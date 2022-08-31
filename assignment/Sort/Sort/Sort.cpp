#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>


void printArray(int* array, int len)
{
	int len = sizeof(array) / sizeof(array[0]);
	for (int i = 0; i < len; i++) {
		printf("\t%d", array[i]);
	}
	printf("\n\n");
}
 
int* copyArray(int* array, int len)
{
	int* newArray = (int*)malloc(sizeof(int) * len);
	memcpy(newArray, array, sizeof(int) * len);
	//for (int i = 0; i < len; i++) {
	//	printf("\t%d", newArray[i]);
	//}printf("\n");
	return newArray;
}

void insertSort(int* array, int len)		//插入排序
{
	int* newArray = (int*)malloc(sizeof(int) * len);
	memcpy(newArray, array, sizeof(int) * len);
	for (int i = 1; i < len; i++) {				//从第二个位置开始与前面的比较
		for (int j = 0; j < i; j++) {
			if (newArray[i] < newArray[j]) {	//小就把前面的往后覆盖
				int temp = newArray[i];
				for (int k = i - 1; k >= j; k--) {		
					newArray[k + 1] = newArray[k];	//倒着覆盖
				}
				newArray[j] = temp;
			}
		}
		printArray(newArray, len);
	}
}

void shellSort(int* array, int len)		//希尔排序
{
	int* newArray = (int*)malloc(sizeof(int) * len);
	memcpy(newArray, array, sizeof(int) * len);
	int step[3] = { 5, 3, 1 };
	for (int num = 0; num < 3; num++) {			//跨度从大到小
		printf("ster: %d\n", step[num]);
		for (int i = 0; i < len; i++) {			//从第一个数开始跨
			for (int j = i + step[num]; j < len; j += step[num]) {		//j、k用来把分组以后的数组进行排序
				for (int k = i; k < j; k += step[num]) {				
					if (newArray[j] < newArray[k]) {
						int temp = newArray[j];
						for (int l = j - step[num]; l >= k; l -= step[num]) {		//覆盖
							newArray[l + step[num]] = newArray[l];
						}
						newArray[k] = temp;
					}
				}
			}printArray(newArray, len);
		}
	}
}

int main(int argc, char* argv[])
{
	int array[10] = { 5, 2, 7, 3, 91, 6, 4, 16, 8, 19};
	int len = sizeof(array)/sizeof(array[0]);
	insertSort(array, len);
	shellSort(array, len);




	//int* cpArray = copyArray(array, len);
	//int* copyArray = (int*)malloc(sizeof(int) * len);
	//
	//memcpy(copyArray, array, sizeof(array));
	
	//for (int i = 0; i < len; i++) {
	//	printf("%d ", copyArray[i]);
	//}printf("\n");

	//printArray(copyArray, len);
	
	return 0;
}
