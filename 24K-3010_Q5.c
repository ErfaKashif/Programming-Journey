#include<stdio.h>
void horizontal(int *num, int count){
	int i=0,j=0;
	printf("Horixontal Histogram:\n");
	for(i=0;i<count;i++){
		printf("\n%d:\t",num[i]);
	for(j=0;j<num[i];j++){
		printf("*");
	}
	printf("\n");
}
}
void verticle(int *num,int count){
	int i=0,j=0,k=0;
	int max=-1;
	int n=count;
	for(i=0;i<count;i++){
		if(num[i]>max){
			max=num[i];
		}
	}
	printf("\nVertical Histogram");
	for(i=max;i>0;i--){
		for(j=0;j<count;j++){
			if(num[j]>=i){
				printf("*");
			}
			else{
				printf(" ");
			}
		}
		printf("\n");
	}

	for(i=0;i<count;i++){
		printf("%d",num[i]);
	}
	
}
int main(){
	int n=0,i=0;
	printf("Enter the number of value\n");
	scanf("%d", &n);
	int num[n];
	printf("\nEnter the values\n");
	for(i=0;i<n;i++){
		scanf("\n%d", &num[i]);
	}
	horizontal(num,n);
	verticle(num,n);
	return 0;
}
