#include <stdio.h>
int fact(int n){
	int carpim=1;
	for(int i=1; i<=n;i++){
		carpim*=i;
	}
	return carpim;
}
	
	
int main(){
	int n,r;
	printf("Enter n and r: ");
	scanf("%d %d",&n,&r);
	int c = fact(n);
	int d = fact(r);
	int e = fact(n-r);
	printf("%d\n",c/(d*e));
	return 0;
}
	
	
	