#ifndef _LCD12864_H_
#define _LCD12864_H_

#include "typedef.h"
//**********************************************************************************************************************************************************
//º¯ÊýÉùÃ÷
//**********************************************************************************************************************************************************
	 extern void Write_Cmd(uchar cmd);
	 extern void Write_Data(uchar dat);
	 extern void face_dis();
	 extern void LCD12864_Init();
	 extern void Show_temp();
	 extern char a,d2,d1,d0; 
	 extern void Show_data();
	 extern void LCD12864_Write_word(uchar *str);

		
	
#endif