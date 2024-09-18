#include <stdio.h>
#include <math.h>
int roundToInteger(float number){
	int result=(int)(number + 0.5);
	return result;
}
float roundToTenths(float number){
	float result2=floor(number * 10 + 0.5) / 10;
	return result2;
}
float roundToHundreths(float number){
	float result3=floor(number * 100 + 0.5) / 100;
	return result3;
}
float roundToThousandths(float number){
	float result4=floor(number * 1000 + 0.5) / 1000;
	return result4;
}
int main(){
	double i;
	printf("Enter a number: ");
	scanf("%lf",&i);
	int res1=roundToInteger(i);
	float res2=roundToTenths(i);
	float res3=roundToHundreths(i);
	float res4=roundToThousandths(i);
	printf("Original: %.4lf\n",i);
	printf("Rounded to the nearest integer: %d\n",res1);
	printf("Rounded to the nearest tenth: %.1f\n",res2);
	printf("Rounded to the nearest hundredth: %.2f\n",res3);
	printf("Rounded to the nearest thousandth: %.3f\n",res4);
	return 0;
}
	