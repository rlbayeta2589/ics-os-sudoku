#include "mouse.h"

//Mouse.inc by SANiK
//License: Use as you wish, except to cause damage
unsigned char mouse_cycle=0;     //unsigned char
signed char mouse_byte[3];    //signed char
signed char mouse_x=0;         //signed char
signed char mouse_y=0;         //signed char


//Mouse functions
void mouse_irq() // (not used but just there)
{
  DWORD flags;

  switch(mouse_cycle)
  {
    case 0:
      mouse_byte[0]=inportb(0x60);
      mouse_cycle++;
      break;
    case 1:
      mouse_byte[1]=inportb(0x60);
      mouse_cycle++;
      break;
    case 2:
      mouse_byte[2]=inportb(0x60);
      mouse_x=mouse_byte[1];
      mouse_y=mouse_byte[2];
      mouse_cycle=0;
      break;
  }
  //ok enable other interrupts
//  outportb(0xA0,0x20);
//  outportb(0x20,0x20);
}

inline void mouse_wait(unsigned char  a_type) //unsigned char
{
  unsigned int _time_out=100000; //unsigned int
  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((inportb(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((inportb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

inline void mouse_write(unsigned char a_write) //unsigned char
{
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  outportb(0x64, 0xD4);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  outportb(0x60, a_write);
}

unsigned char mouse_read()
{
  //Get's response from mouse
  mouse_wait(0);
  return inportb(0x60);
}

void installmouse()
{
  unsigned char _status;  //unsigned char

  //Enable the auxiliary mouse device
  mouse_wait(1);
  outportb(0x64, 0xA8);
 
  //Enable the interrupts
  mouse_wait(1);
  outportb(0x64, 0x20);
  mouse_wait(0);
  _status=(inportb(0x60) | 2);
  mouse_wait(1);
  outportb(0x64, 0x60);
  mouse_wait(1);
  outportb(0x60, _status);
 
  //Tell the mouse to use default settings
  mouse_write(0xF6);
  mouse_read();  //Acknowledge
 
  //Enable the mouse
  mouse_write(0xF4);
  mouse_read();  //Acknowledge
 
  //set the  handler,mousewrapper (in irqwrap.asm), IRQ12
  setinterruptvector(0x2C,dex_idtbase,0x8E,mousewrapper,SYS_CODE_SEL);


  printf("MOUSE successfully installed!!!");
}

void get_mouse_pos(signed char *x,signed char *y){
   *x=mouse_x;
   *y=mouse_y;
}

void init_mouse()
{
   int mouse_devid;
   devmgr_char_desc mymouse;
   memset(&mymouse,0,sizeof(mymouse));
   mymouse.hdr.size = sizeof(mymouse);
   mymouse.hdr.type = DEVMGR_CHAR;
   strcpy(mymouse.hdr.name,"mouse");
   strcpy(mymouse.hdr.description,"Default mouse driver 1.00");
   mymouse.init_device = installmouse;
   mymouse.ready_put = mouse_write;
   mymouse.ready_get = mouse_read;
   mymouse.get_char = mouse_write;
   mymouse.put_char = mouse_read;
   mymouse.hdr.sendmessage = 0;
   mymouse.set_callback_handler=0;
   mymouse.get_callback_handler=0;
   mouse_devid=devmgr_register((devmgr_char_desc *)&mymouse);
   memset(&mouse_busywait,0,sizeof(mouse_busywait));
   irq_addhandler(mouse_devid,12,mouse_irq);
}

