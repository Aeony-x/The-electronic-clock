#include "delay.h"

void delay_ms(uint z)      //延时z毫秒 
{
uint x,y;
for(x=z;x>0;x--)
  for(y=115;y>0;y--);
}

//在系统晶振为12Mhz时延时计算式为（8*x+10）us
void delay(uint x) 
{
	while(--x);
}