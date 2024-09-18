#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 10
void reverse(int array[], int size){
	for(int i=0;i<size/2;i++){
		int temp=array[i];
		array[i]=array[size-1-i];
		array[size-1-i]=temp;
	}
}
	

void random_fill_array(int array[]){
	int filled[ARRAY_SIZE]={0};
	int random_number;
	for(int i=0;i<ARRAY_SIZE;i++){
		do{
			random_number=rand()%ARRAY_SIZE;
		}while(filled[random_number]);
		array[i]=random_number;
		filled[random_number]++;
	}
}
int main(){
	int my_array[ARRAY_SIZE];
	srand(0);
	random_fill_array(my_array);
	printf("ORIGINAL ARRAY:");
	for(int i=0;i<ARRAY_SIZE;printf(" %d",my_array[i++]));
	printf("\n");
	reverse(my_array,ARRAY_SIZE);
	
	printf("REVERSE ARRAY:");
	for(int i=0;i<ARRAY_SIZE;printf(" %d",my_array[i++]));
	printf("\n");
	
	
	
	
	return EXIT_SUCCESS;
}