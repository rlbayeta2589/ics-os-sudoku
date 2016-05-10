
#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

#define SIZE 9

int board[SIZE][SIZE];

void readFile(char *filename){

	char str[SIZE];
	int count = 0, i=0, x=0;
	FILE *fp;
	fp = fopen(filename, "r");
	
	if(fp!=NULL){
		
		while(!feof(fp)){

			fgets(str, SIZE+1 ,fp);

			str[SIZE] = '\0';

			printf("%s", str);

				for(i=0 ; i<SIZE ; i++){
					printf("%c", str[i]);
					board[count/SIZE][count%SIZE] = atoi(str[i]);
					count++;
				}
		}

		//printf("%d\n", count);
		fclose(fp);
	}
}


void main(){

	int i, j;

	readFile("easy/easy1.txt");

/*	for (i = 0; i < SIZE; i++){
		for (j = 0; j < SIZE; j++){
			printf("..%d..", board[i][j]);
		}
		printf("\n");
	}*/

}