#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define N_ITERATIONS 10000

int main(){
	srand(time(NULL));
	int strategy_1=0;
	int strategy_2=0;
	for(int i=0; i<N_ITERATIONS;i++){
		int car_door=rand()%3+1;
		int selected_door=rand()%3+1;
		int opened_door=0;
		int unopened_door=0;
		if(car_door!=selected_door){
			opened_door=6-car_door-selected_door;
			unopened_door=car_door;
		}
		else{
			bool heads=rand()%2==0;
			if(car_door==1){
				opened_door=heads?2:3;
			}else if(car_door==2){
				opened_door=heads?1:3;
			}else{
				opened_door=heads?1:2;
			}
			unopened_door=6-car_door-opened_door;
				
		}
		if(car_door==selected_door){
			strategy_1++;
		}
		else if(car_door==unopened_door){
			strategy_2++;
		}
	}
	double win_ratio_1=(double) strategy_1/N_ITERATIONS;
	double win_ratio_2=(double) strategy_2/N_ITERATIONS;
	printf("win ratio for strategy 1: %.3lf\n", win_ratio_1);
	printf("win ratio for strategy 2: %.3lf\n", win_ratio_2);
	return EXIT_SUCCESS;
}