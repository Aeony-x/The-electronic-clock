#include <reg52.h>
#include "ds18b20.h"
#include "delay.h"

uint i,j,temp;
uchar high,low;
float f_temp;
char a,d2,d1,d0; 

sbit DQ=P2^2;       //定义DS18B20数据线引脚端


//-----------------------获温部分：初始化函数--------------------
void Temp_init()
{
	DQ=0;  //拉低总线，产生复位信号
	i=80;
	while(i>0)
		i--;  //延时480~960us
	DQ=1;  //拉高总线
	i=4;
	while(i>0)
		i--;  //延时15~60us
	while(DQ);  //等待产生应答脉冲
	i=70;
	while(i>0)
		i--;  //延时至少480us
}
//------------------获温部分：写函数-------------------------------
void DS18B20_Write_Byte(uchar dat)  //写1个字节
{
bit testb;
for(j=8;j>0;j--)
{
	testb=dat&0x01;
	dat=dat>>1;
  if(testb)  //写1
  {
	   DQ=0;  //拉低总线，产生写时间隙
	   i++;  //延时大于1us
	   DQ=1;  //拉高总线
	   i=8;while(i>0)i--;  //延时至少60us，供DS18B20采样
  }
  else    //写0
  {
	   DQ=0;  //拉低总线，产生写时间隙
	   i=8;while(i>0)i--;  //保持至少60us，供DS18B20采样
	   DQ=1;  //拉高总线
	   i++;i++;
  }
} 
}
//------------------获温部分：读函数-------------------------------
uchar DS18B20_Read_Byte()  //读1个字节
{
bit b;  //定义存放接收到的1个字节
uchar i_b;
uchar rdbyte;
for(j=8;j>0;j--)
{
	  DQ=0;  //拉低总线，产生读时隙
	  i++;  //延时大于1us
	  DQ=1;  //释放总线
	  i++;i++;  //给一定时间让总线释放
	  b=DQ;  //读取数据
	  i=8;
	while(i>0)
		i--;  //延时至少60us
  i_b=b;
  rdbyte=(i_b<<7)|(rdbyte>>1);  //将读取到得一位值左移7位，存放读取的数据变量rdbyte右移1位
}
return rdbyte;
}
//----------------------温度获取函数---------------------------
void Temp_get()
{ 
	Temp_init();  //初始化，复位并获取应答信号
	DS18B20_Write_Byte(0xcc);  //跳过ROM
	DS18B20_Write_Byte(0x44);  //开始温度转换
	delay_ms(1000);  //等待温度转换完成
	Temp_init();  //将DS18B20复位
	DS18B20_Write_Byte(0xcc);  //跳过ROM
	DS18B20_Write_Byte(0xbe);  //读暂存器
	low=DS18B20_Read_Byte();  //读取低8位
	high=DS18B20_Read_Byte();  //读取高8位
	temp=high;
	temp<<=8;
	temp=temp|low;  //将读取的低8位和高8位合并
	f_temp=temp*0.0625;  //温度在寄存器中为12位 分辨率位0.0625°
	temp=f_temp*10+0.5;  //精确到十分位，四舍五入
	d2=temp/100;  //显示数据：十位
	d1=temp%100/10;  //显示数据：个位
	d0=temp%10;  //显示数据：十分位

}