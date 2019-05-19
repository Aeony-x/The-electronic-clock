#include <reg52.h>
#include "ds18b20.h"
#include "delay.h"

uint i,j,temp;
uchar high,low;
float f_temp;
char a,d2,d1,d0; 

sbit DQ=P2^2;       //����DS18B20���������Ŷ�


//-----------------------���²��֣���ʼ������--------------------
void Temp_init()
{
	DQ=0;  //�������ߣ�������λ�ź�
	i=80;
	while(i>0)
		i--;  //��ʱ480~960us
	DQ=1;  //��������
	i=4;
	while(i>0)
		i--;  //��ʱ15~60us
	while(DQ);  //�ȴ�����Ӧ������
	i=70;
	while(i>0)
		i--;  //��ʱ����480us
}
//------------------���²��֣�д����-------------------------------
void DS18B20_Write_Byte(uchar dat)  //д1���ֽ�
{
bit testb;
for(j=8;j>0;j--)
{
	testb=dat&0x01;
	dat=dat>>1;
  if(testb)  //д1
  {
	   DQ=0;  //�������ߣ�����дʱ��϶
	   i++;  //��ʱ����1us
	   DQ=1;  //��������
	   i=8;while(i>0)i--;  //��ʱ����60us����DS18B20����
  }
  else    //д0
  {
	   DQ=0;  //�������ߣ�����дʱ��϶
	   i=8;while(i>0)i--;  //��������60us����DS18B20����
	   DQ=1;  //��������
	   i++;i++;
  }
} 
}
//------------------���²��֣�������-------------------------------
uchar DS18B20_Read_Byte()  //��1���ֽ�
{
bit b;  //�����Ž��յ���1���ֽ�
uchar i_b;
uchar rdbyte;
for(j=8;j>0;j--)
{
	  DQ=0;  //�������ߣ�������ʱ϶
	  i++;  //��ʱ����1us
	  DQ=1;  //�ͷ�����
	  i++;i++;  //��һ��ʱ���������ͷ�
	  b=DQ;  //��ȡ����
	  i=8;
	while(i>0)
		i--;  //��ʱ����60us
  i_b=b;
  rdbyte=(i_b<<7)|(rdbyte>>1);  //����ȡ����һλֵ����7λ����Ŷ�ȡ�����ݱ���rdbyte����1λ
}
return rdbyte;
}
//----------------------�¶Ȼ�ȡ����---------------------------
void Temp_get()
{ 
	Temp_init();  //��ʼ������λ����ȡӦ���ź�
	DS18B20_Write_Byte(0xcc);  //����ROM
	DS18B20_Write_Byte(0x44);  //��ʼ�¶�ת��
	delay_ms(1000);  //�ȴ��¶�ת�����
	Temp_init();  //��DS18B20��λ
	DS18B20_Write_Byte(0xcc);  //����ROM
	DS18B20_Write_Byte(0xbe);  //���ݴ���
	low=DS18B20_Read_Byte();  //��ȡ��8λ
	high=DS18B20_Read_Byte();  //��ȡ��8λ
	temp=high;
	temp<<=8;
	temp=temp|low;  //����ȡ�ĵ�8λ�͸�8λ�ϲ�
	f_temp=temp*0.0625;  //�¶��ڼĴ�����Ϊ12λ �ֱ���λ0.0625��
	temp=f_temp*10+0.5;  //��ȷ��ʮ��λ����������
	d2=temp/100;  //��ʾ���ݣ�ʮλ
	d1=temp%100/10;  //��ʾ���ݣ���λ
	d0=temp%10;  //��ʾ���ݣ�ʮ��λ

}