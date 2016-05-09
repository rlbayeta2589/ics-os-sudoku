
#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"


#define start '1'
#define instructions '2'
#define highscores '3'
#define quit '4'

#define YELLOW 54
#define PALE_YELLOW 62
#define ROYAL_BLUE 1
#define DARK_BLUE 8
#define GRAY 56
#define WHITE 63

void erase(); //basically covers an area with a black rectangle


int main(){
	char keypress;  
	set_graphics(VGA_640X480X16);
	StartPage();

	do{
		keypress=(char)getch();

		if(keypress==start){
			erase(1,1,640,480); //change page
			DifficultyPage();	//print page
			clrscr();			//remove keypress
		}

		if(keypress==instructions){
			erase(1,1,640,480); //change page
			InstructionsPage();	//print page
			clrscr();			//remove key
			keypress=(char)getch();
			if(keypress=='1'){
				erase(1,1,640,480); //change page
				StartPage();
			}
		}

		if(keypress==highscores){

		}

		if(keypress==quit){
			clrscr();
			break;
		}

	}while(keypress!=quit);
	

}

//lightsout.exe
void erase(int x, int y, int w, int h){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,100);
}

//display instructions
InstructionsPage(){
	write_text("Instructions",100,10,WHITE,0);
	write_text("The user will pick the difficulty of the game",40,80,WHITE,0);
	write_text("Choices of difficulty levels are: Easy, Medium, and Hard.",40,120,WHITE,0);
	write_text("Random puzzle of picked difficulty will be loaded.",40,160,WHITE,0);
	write_text("The user can input numbers by pressing the desired number",40,200,WHITE,0);
	write_text("in the keyboard (1-9).",40,240,WHITE,0);
	write_text("The user can navigate by using the arrow keys.",40,280,WHITE,0);


	write_text("1 - To Go Back To Menu",40,360,WHITE,0);
}


//display difficulty picking
DifficultyPage(){
	//difficulty options
	write_text("1 - Easy",40,40,WHITE,0); 
	write_text("2 - Medium",80,80,WHITE,0);
	write_text("3 - Hard",120,120,WHITE,0);
	write_text("4 - Back",200,160,WHITE,0);
}

//display homepage
StartPage(){	
	write_text("SUDOKU!",20,20,WHITE,1);

	write_text("1 - Start",40,40,WHITE,0); 
	write_text("2 - Instructions",80,80,WHITE,0);
	write_text("3 - High Scores",120,120,WHITE,0);
	write_text("4 - Quit",200,160,WHITE,0);
}


