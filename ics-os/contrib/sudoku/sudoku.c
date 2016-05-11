
#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"


#define start 1
#define instructions 2
#define highscores 3
#define quit 4

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define SPACE ' '

#define YELLOW 54
#define PALE_YELLOW 62
#define ROYAL_BLUE 1
#define DARK_BLUE 8
#define GRAY 56
#define GREEN 2
#define WHITE 63

void erase(); //basically covers an area with a black rectangle


int main(){
	char keypress, temp[10]; 
	int choice = 0;
	set_graphics(VGA_320X200X256);
	
	erase(1,1,400,200); //change page
	Controls();


	do{
		choice = StartPage();

		switch(choice){
			case start : 
				DifficultyPage();	//print page
				DrawBoard();
				break;
			case instructions :
				InstructionsPage();	//print page
				break;
			case highscores :
				break;
		}

	}while(choice!=quit);


//---------------------------------------------//	
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}

//lightsout.exe
void erase(int x, int y, int width, int height){
    int i, j;
    for (i = y; i < (y+height); i++){
        for(j = x; j < (x+width); j++){
            write_pixel(j, i, 100);
        }
    }
}

DrawBoard(){

	erase(1,1,400,200); //change page

	int i,j;

	for (i = 60; i <= 240; i++){
        for(j = 30; j <= 165; j++){


        	if(i%20==0 || j%15==0){
        		write_pixel(i, j, GRAY);
        	}else{
        		write_pixel(i, j, WHITE);
        	}
        	
        	if(i==120 || i==180){
        		write_pixel(i-1, j, GRAY);
        		write_pixel(i+1, j, GRAY);
        	}

        	if(j==75 || j==120){
        		write_pixel(i, j-1, GRAY);
        		write_pixel(i, j+1, GRAY);
        	}

        }
    }

    getch();
}

//display instructions
InstructionsPage(){
	erase(1,1,400,200); //change page

	write_text("Instructions",100,10,GREEN,0);
	write_text("The user will pick the difficulty",10,30,WHITE,0);
	write_text("of the game",90,40,WHITE,0);
	getch();
	write_text("Choices of difficulty levels are:",10,60,WHITE,0);
	getch();
	write_text("Easy",50,75,WHITE,0);
	getch();
	write_text("Medium",130,75,WHITE,0);
	getch();
	write_text("Hard",220,75,WHITE,0);
	getch();
	write_text("Random puzzle of picked difficulty",10,95,WHITE,0);
	write_text("will be loaded",90,115,WHITE,0);
	getch();
	write_text("Navigate using 'W' 'A' 'S' 'D' keys",8,140,WHITE,0);
	getch();
	write_text("Input answers using keys (1-9)",10,160,WHITE,0);
	getch();

	write_text(">> BACK",10,180,WHITE,0);
	while((char)getch()!=SPACE){}
}


//display difficulty picking
DifficultyPage(){
	//difficulty options
	erase(1,1,400,200); //change page

	write_text("1 - Easy",40,40,WHITE,0); 
	write_text("2 - Medium",80,80,WHITE,0);
	write_text("3 - Hard",120,120,WHITE,0);
	write_text("4 - Back",200,160,WHITE,0);

	while((char)getch()!=SPACE){}
}

Controls(){

	write_text("Controls :",40,40,WHITE,0); 
	write_text("/\\",145,30,WHITE,0); 
	write_text("||",145,45,WHITE,0); 
	write_text("W",150,60,WHITE,0); 
	write_text("S",150,75,WHITE,0); 
	write_text("<== A",80,75,WHITE,0);
	write_text("D ==>",180,75,WHITE,0);
	write_text("||",145,90,WHITE,0);
	write_text("\\/",145,105,WHITE,0);
	write_text("i___SPACE___i",100,120,WHITE,0);
	write_text("SELECT",130,140,WHITE,0);

	write_text("Select to continue . . .",70,180,WHITE,0);

	while((char)getch()!=SPACE){}
}

//display homepage
int StartPage(){

	erase(1,1,400,200); //change page

	char key, temp[10];
	int i,j, choice=1, xcoord=150, ycoord=80;

	for (i = 0; i < 400; i++){
        for(j = 0; j < 200; j++){
        	if(i==20 || i==180) write_pixel(j, i, YELLOW);
        	if(j==20 || i==380) write_pixel(j, i, YELLOW);
        }
    }

	write_text("SUDOKU!",45,50,WHITE,1);

	write_text("Start",180,80,WHITE,0); 
	write_text("Instructions",180,100,WHITE,0);
	write_text("High Scores",180,120,WHITE,0);
	write_text("Quit",180,140,WHITE,0);

	write_text(">>",150,80,WHITE,0); 

	do{
		key = (char) getch();

		switch(key){
			case UP:
			case LEFT:
				choice--;
				erase(xcoord,ycoord,30,20);
				ycoord-=20;
				break;
			case DOWN:
			case RIGHT:
				choice++;
				erase(xcoord,ycoord,30,20);
				ycoord+=20;
				break;
		}

		if(choice==-1){
			choice=4;
			ycoord=140;
		}else if(choice==5){
			choice=1;
			ycoord=80;
		}

		write_text(">>",xcoord,ycoord,WHITE,0); 

	}while(key!=SPACE);

	return choice;
}


