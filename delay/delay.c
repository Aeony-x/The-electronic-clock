#include "delay.h"

void delay_ms(uint z)      //��ʱz���� 
{
uint x,y;
for(x=z;x>0;x--)
  for(y=115;y>0;y--);
}

//��ϵͳ����Ϊ12Mhzʱ��ʱ����ʽΪ��8*x+10��us
void delay(uint x) 
{
	while(--x);
}