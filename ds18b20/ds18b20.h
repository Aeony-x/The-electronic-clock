#ifndef _DS18B20_H_
#define _DS18B20_H_
	
#include "typedef.h"

//**********************************************************************************************************************************************************
//��������
//**********************************************************************************************************************************************************
	extern void Temp_init();
	extern void DS18B20_Write_Byte(uchar dat);
	extern uchar DS18B20_Read_Byte();
	extern void Temp_get();
		
	
#endif	