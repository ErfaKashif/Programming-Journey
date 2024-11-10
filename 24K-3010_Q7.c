#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
void wordsearch_grid(char wordsearch[6][5]) {
	srand(time(NULL)); 
	int i=0,j=0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j <5; j++) {
        	//using rand function to generate a random no. between o to 26 and adding it to the ASCII value of A so that it represents an uppercase english alphabet
			wordsearch[i][j] = 'A' + rand() % 26;
        
        }
	}
			int digit;
        	printf("\nEnter the 5 digits of your roll no.\n");
        		for(j=0;j<5;j++){
        			scanf("\n%d", &digit);
        			if(digit>=0 && digit<=9){
        			//converting the digit 0 to character 0 by adding the digit to the ASCII value of 0
        			wordsearch[5][j]='0'+digit;
				}
				else{
					printf("Invalid input!\n Please enter again\n");
					i--;
				}
			}
		
	for(i=0;i<6;i++){
		for(j=0;j<5;j++){
			printf("%c\t", wordsearch[i][j]);
		}
	printf("\n");	
	}	
    
}
int find_word(char word[], char wordsearch[6][5], int length){
	int i=0,j=0,k=0;
	//left to right
		for(i=0;i<6;i++){
			k=0;
		for(j=0;j<5;j++){
			if(word[k]==wordsearch[i][j]){
					k++;
		}
		if(k==length){
			return 1;
		}
}
}
	//from right to left
	for(i=0;i<6;i++){
		k=0;
		for(j=4;j>=0;j--){
			if(word[k]==wordsearch[i][j]){
					k++;
		}
		if(k==length){
			return 1;
		}
		}
	}
	//for top to bottom
	for(i=0;i<5;i++){
		k=0;
		for(j=0;j<6;j++){
			if(word[k]==wordsearch[j][i]){
				k++;
		}
		if(k==length){
			return 1;
		}
		}
	}
	//from bottom to top
	for(i=0;i<5;i++){
		k=0;
		for(j=5;j>=0;j--){
			if(word[k]==wordsearch[j][i]){
				k++;
			}
		if(k==length){
			return 1;
			
		}
	}
}
	return 0;
	}
int main(){
	char wordsearch[6][5];
	wordsearch_grid(wordsearch);
	char word[25];
	int i=0,j=0,k=0,score=0,choice=0,flag;
	do{
	printf("\nEnter your choice:\n1.Enter word\n2.End\n");
	scanf("%d", &choice);
	if(choice==1){
	printf("Enter the word\n");
	scanf("%s", &word);
	int length=strlen(word);
	int result=find_word(word,wordsearch,length);
	if(result==1){
		score++;
		printf("Yipee word found");
	}
	else{
		score--;
		printf("\nOops word not found\n");
	}
	printf("\nYour score is:%d", score);
	}
}while(choice==1);
	return 0;
}
