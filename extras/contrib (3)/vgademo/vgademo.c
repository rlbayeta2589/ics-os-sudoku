/*
 * VGA Demo for ics-os
 * coded by Joseph Anthony C. Hermocilla
 */ 

#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

#define LARGE_FONT 1
#define SMALL_FONT 0


int max_colors=255;
int width=320;
int height=200;



//Fills a rectangle
void fill_rect(int x, int y, int w, int h, int color){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,color);
}

void random_rects(){
   int i=0;
   int r,g,b;
   int x,y,w,h,color;

   while(!kb_ready()){ 
      srand(time());
      /*
      r=rand()%max_colors;
      g=rand()%max_colors;
      b=rand()%max_colors;
      write_palette(r,g,b,color);
      */
      x=rand()%width;
      y=rand()%height;
      w=rand()%50;
      h=rand()%50;
      color=rand()%max_colors;
      fill_rect(x,y,w,h,color);
      delay(10);
   }
}

void show_charset(){
   char code[10];
   int i=0,x=10,y=10;
   for (i=0;i<256;i++){
      write_char(i,x,y,YELLOW,SMALL_FONT);
      x+=9;
      if (x > (width-30)){
        y+=9;
        x=10;
      }
   }
   write_text("Press any key to continue",40,100,YELLOW,LARGE_FONT);
   getch();
}

/**
 * To print a number, we use sprintf
 */
void print_number(){
   int age=28;
   char str[10];
   sprintf(str,"age=%d",age);
   write_text(str,50,height-10,RED,SMALL_FONT);
   getch();
}

void show_time(){
   char str[20];
   dex32_datetime time;
   while(!kb_ready()){
      get_date_time(&time);
      //erase background
      fill_rect(200,height-50,60,20,BLACK);
      sprintf(str,"%d:%d:%d",time.hour,time.min,time.sec);
      write_text(str,200,height-50,GREEN,LARGE_FONT);
      delay(10);
   }

}


void hires(){
   set_graphics(VGA_640X480X16);
   write_text("640x480 16 colors",10,150,YELLOW,LARGE_FONT);
   getch();
   max_colors=16;
   width=640;
   height=480;
   show_time();
   show_charset();
   print_number();
   random_rects();
}

void lores(){
   set_graphics(VGA_320X200X256);
   write_text("320x200 256 colors",10,150,YELLOW,SMALL_FONT);
   getch();
   max_colors=256;
   width=320;
   height=200;
   show_time();
   show_charset();
   print_number();
   random_rects();
}


int main() 
{
   hires();
   lores();
   set_graphics(VGA_TEXT80X25X16);
   clrscr();

}
