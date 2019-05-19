#include <reg52.h>
#include "delay.h"
#include "typedef.h"
#include "ds18b20.h"	
#include "lcd12864.h"
#include "ds1302.h"
#include <string.h>

//**********************************************************************************************************************************
//IO设置
//**********************************************************************************************************************************
sbit key_1 = P3^0;
sbit key_2 = P3^1;
sbit key_3 = P3^2;
sbit key_4 = P3^3;


//**********************************************************************************************************************************
uchar year,month,day,week,hour,minute,second;//定义时间映射全局变量


//**********************************************************************************************************************************
//申请空间
//**********************************************************************************************************************************
uchar time[]="--:--:--";//显示时分秒字符串
uchar date[]="-------(-)";//显示年月日(周)字符串

//**********************************************************************************************************************************
//主函数
//**********************************************************************************************************************************
void main()
{	
	uchar i;

    LCD12864_Init();    //lcd初始化    
	Show_data();
	Ds1302_Init();//DS1302初始化
	while(1)
	{ 		
			Ds1302_Read_Time();
		
			Write_Cmd(0x98);
		    LCD12864_Write_word("[set]      [dis]");
		
			Write_Cmd(0x80);//第一行第一列开始显示
		for(i=0;i<strlen(time);i++)
			{
				Write_Data(time[i]);
			}
				Write_Cmd(0x90); //第二行第一列开始显示
		for(i=0;i<strlen(date);i++)
			{
				Write_Data(date[i]);
			}
				Temp_get();  //获取温度 
				Show_temp();  //显示温度    
	}
}


