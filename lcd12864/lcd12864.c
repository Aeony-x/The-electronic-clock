#include <reg52.h>
#include "lcd12864.h"
#include "delay.h"

#define LCD12864_DATA P0

//********************************************************************************************************************************
//申请空间
//********************************************************************************************************************************
uchar code line2[]="    ℃";

//********************************************************************************************************************************
//IO设置
//********************************************************************************************************************************
sbit LCD12864_RS = P3^5;      //定义lcd数据命令选择端
sbit LCD12864_RW = P3^6;      //定义lcd读写选择端
sbit LCD12864_EN = P3^4;      //定义lcd使能端
sbit LCD12864_PSB = P3^7;      //定义并串选择端

//********************************************************************************************************************************
//写指令
//********************************************************************************************************************************
void Write_Cmd(uchar cmd)
{
	LCD12864_RS = 0;
	LCD12864_RW = 0;	
	LCD12864_EN = 0;
	LCD12864_DATA = cmd;
	delay_ms(1);
	LCD12864_EN = 1;
	delay_ms(1);
	LCD12864_EN = 0; 
}

//*******************************************************************************************************************************
//写数据
//*******************************************************************************************************************************
void Write_Data(uchar dat)
{
	LCD12864_RS = 1;	
	LCD12864_EN = 0;
	LCD12864_RW = 0;	
	LCD12864_DATA = dat;
	delay_ms(1);
	LCD12864_EN = 1;
	delay_ms(1);
	LCD12864_EN = 0; 
}

//******************************************************************************************************************************
//用户界面数据显示
//******************************************************************************************************************************
void Show_temp()
{
	Write_Cmd(0x88);  //显示温度
	
	Write_Data(0x30+d2);
	Write_Data(0x30+d1);
	Write_Data(0x2e);  //写入“.”号
	Write_Data(0x30+d0);
} 
//******************************************************************************************************************************
//初始化
//******************************************************************************************************************************
void LCD12864_Init()
{
	delay_ms(20);          //等待液晶输入电源稳定
	
//LCD12864_PSB = 1;         //选定lcd与单片机并行连接
	LCD12864_RW = 0;        //因为我们不需要从lcd模块读数据，所以可直接将此端口清零，便于之后利用矩阵键盘
	
	Write_Cmd(0x30);           //选择功能：8位数据基本指令操作
	Write_Cmd(0x0c);          //整体显示开，不显示光标
	Write_Cmd(0x01);          //lcd清屏
	Write_Cmd(0x06);
 	
}
//******************************************************************************************************************************
//写显示行数
//******************************************************************************************************************************
void Show_data()
{
	Write_Cmd(0x88);          //设置第二行起始位
	for(a=0;a<6;a++)             //写入第二行数据
	{
		Write_Data(line2[a]);
	}

}

void LCD12864_Write_word(uchar *str)
{
	while(*str != '\0')	
	{
		Write_Data(*str++);   
	}
		*str = 0;
}





