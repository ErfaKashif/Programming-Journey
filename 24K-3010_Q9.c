#include<stdio.h>
#include<string.h>
int main(){
	int choice=0,i=0,j=0,collected=0,current_row=0,current_column=0;
	char choice2;
	char move;
	char game[5][5]={{' ',' ','I','X',' '},{' ','X',' ',' ',' '},{'I',' ','X','X',' '},{' ',' ',' ','I','X'},{' ','X',' ',' ','P'}};
	printf("The game consists of a 5x5 grid.\ni. Each cell can contain:\nii.An empty space (' ').\niii. An item ('I') that the player can collect.\niv. An obstacle ('X') that the player cannot pass through.\nv. The player's position, represented by 'P'\n.");
	printf("\nDo you wish to set your own grid or play with the predefined grid\nEnter Y or N\n");
	scanf("%c", &choice2);
	getchar();
	if(choice2=='Y' || choice2=='y'){
			for (i = 0; i <5; i++) {
            printf("\nEnter for row %d (5 characters, e.g. ' I I '): \n", i + 1);
            fgets(game[i], 6, stdin);
            getchar();
        }
	}
	for(i=0;i<5;i++){
			for(j=0;j<5;j++){
				if(game[i][j]=='P'){
					current_row=i;
					current_column=j;
						break;
					}
				}
				if(game[current_row][current_column]=='P'){
					break;
				}
		}
		printf("1.Play\n2.Quit\n");
		scanf("%d",&choice);
		
	do{
		
		if(choice==1){
			printf("\nYour position is\n");
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){
					printf("%c ",game[i][j]);
				}
				printf("\n");
			}
			printf("\nEnter your move\n1.W=Up\n2.S=Down\n3.D=Right\n4.A=Left\n");
			scanf(" %c", &move);
			i=current_row;
			j=current_column;
			if(move=='W'){
				i--;
			}
			else if(move=='S'){
				i++;
			}
			else if(move=='D'){
				j++;
			}
			else if(move=='A'){
				j--;
			}
			else{
				printf("Invalid move");
			}
			if(i>=0 && i<5 && j<5 && j>=0 && game[i][j]!='X'){
				game[current_row][current_column]=' ';
				if(game[i][j]=='I'){
					collected++;
				}
				game[i][j]='P';
				current_row=i;
				current_column=j;
			}
			else{
				printf("\nInvalid move\nPlease try again\n");
			}
			printf("\n1. Continue playing\n2. Quit\n");
        	scanf("%d", &choice);
		}
	}while(choice!=0);
	printf("\nItems collected:%d",collected);
	return 0;
}
