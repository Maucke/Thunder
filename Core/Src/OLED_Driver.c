#include "OLED_Driver.h"
#include "ASCII_Font.h"
#include "stm32f407xx.h"

//u16 OLED_GRAM

void ResetLGDP4216(void)
{GPIOA->BSRR=2<<16;HAL_Delay(100);GPIOA->BSRR=2;HAL_Delay(100);}

void GammaSet() {
   SendCommand(LUT_R);                                       // 27. Red Lookup Set.
                                                             //
   WriteData(0x00);                                          //  1
   WriteData(0x01);                                          //  2
   WriteData(0x02);                                          //  3
   WriteData(0x03);                                          //  4
   WriteData(0x04);                                          //  5
                                                             // 
   WriteData(0x05);                                          //  6
   WriteData(0x07);                                          //  7
   WriteData(0x08);                                          //  8
   WriteData(0x09);                                          //  9
   WriteData(0x0A);                                          // 10
                                                             // 
   WriteData(0x0C);                                          // 11
   WriteData(0x0D);                                          // 12
   WriteData(0x0F);                                          // 13
   WriteData(0x10);                                          // 14
   WriteData(0x12);                                          // 15
                                                             //
   WriteData(0x13);                                          // 16
   WriteData(0x15);                                          // 17
   WriteData(0x16);                                          // 18
   WriteData(0x18);                                          // 19
   WriteData(0x1A);                                          // 20
                                                             // 
   WriteData(0x1B);                                          // 21
   WriteData(0x1D);                                          // 22
   WriteData(0x1F);                                          // 23
   WriteData(0x21);                                          // 24
   WriteData(0x22);                                          // 25
                                                             //
   WriteData(0x24);                                          // 26
   WriteData(0x26);                                          // 27
   WriteData(0x28);                                          // 28
   WriteData(0x2A);                                          // 29
   WriteData(0x2C);                                          // 30
                                                             //
   WriteData(0x2E);                                          // 31
   WriteData(0x30);                                          // 32
   WriteData(0x33);                                          // 33
   WriteData(0x35);                                          // 34
   WriteData(0x37);                                          // 35
                                                             //
   WriteData(0x3A);                                          // 36
   WriteData(0x3C);                                          // 37
   WriteData(0x3E);                                          // 38
   WriteData(0x40);                                          // 39
   WriteData(0x43);                                          // 40
                                                             //
   WriteData(0x45);                                          // 41
   WriteData(0x47);                                          // 42
   WriteData(0x4A);                                          // 43
   WriteData(0x4C);                                          // 44
   WriteData(0x4F);                                          // 45
                                                             //
   WriteData(0x51);                                          // 46
   WriteData(0x53);                                          // 47
   WriteData(0x56);                                          // 48
   WriteData(0x58);                                          // 49
   WriteData(0x5B);                                          // 50
                                                             //
   WriteData(0x5D);                                          // 51
   WriteData(0x60);                                          // 52
   WriteData(0x62);                                          // 53
   WriteData(0x66);                                          // 54
   WriteData(0x68);                                          // 55
                                                             // 
   WriteData(0x6B);                                          // 56
   WriteData(0x6D);                                          // 57
   WriteData(0x70);                                          // 58
   WriteData(0x72);                                          // 59
   WriteData(0x75);                                          // 60
                                                             //
   WriteData(0x78);                                          // 61
   WriteData(0x7A);                                          // 62
   WriteData(0x7D);                                          // 63
   WriteData(0x7F);                                          // 64
//...........................................................//
   SendCommand(LUT_G);                                       // 28. Green Lookup Set. 
                                                             //
   WriteData(0x00);                                          //  1
   WriteData(0x02);                                          //  2
   WriteData(0x04);                                          //  3
   WriteData(0x06);                                          //  4
   WriteData(0x08);                                          //  5
                                                             //
   WriteData(0x0A);                                          //  6
   WriteData(0x0C);                                          //  7
   WriteData(0x0E);                                          //  8
   WriteData(0x10);                                          //  9
   WriteData(0x12);                                          // 10
                                                             //
   WriteData(0x14);                                          // 11 
   WriteData(0x16);                                          // 12 
   WriteData(0x18);                                          // 13 
   WriteData(0x1A);                                          // 14 
   WriteData(0x1C);                                          // 15
                                                             //
   WriteData(0x1E);                                          // 16
   WriteData(0x20);                                          // 17
   WriteData(0x22);                                          // 18
   WriteData(0x24);                                          // 19
   WriteData(0x26);                                          // 20
                                                             //
   WriteData(0x28);                                          // 21
   WriteData(0x2A);                                          // 22
   WriteData(0x2C);                                          // 23
   WriteData(0x2E);                                          // 24
   WriteData(0x30);                                          // 25
                                                             //
   WriteData(0x32);                                          // 26
   WriteData(0x34);                                          // 27
   WriteData(0x36);                                          // 28
   WriteData(0x38);                                          // 29
   WriteData(0x3A);                                          // 30
                                                             //
   WriteData(0x3C);                                          // 31
   WriteData(0x3E);                                          // 32
   WriteData(0x41);                                          // 33
   WriteData(0x43);                                          // 34
   WriteData(0x45);                                          // 35
                                                             //
   WriteData(0x47);                                          // 36
   WriteData(0x49);                                          // 37
   WriteData(0x4B);                                          // 38
   WriteData(0x4D);                                          // 39
   WriteData(0x4F);                                          // 40
                                                             //
   WriteData(0x51);                                          // 41
   WriteData(0x53);                                          // 42
   WriteData(0x55);                                          // 43
   WriteData(0x57);                                          // 44
   WriteData(0x59);                                          // 45
                                                             //
   WriteData(0x5B);                                          // 51
   WriteData(0x5D);                                          // 52
   WriteData(0x5F);                                          // 53
   WriteData(0x61);                                          // 54
   WriteData(0x63);                                          // 50
                                                             //
   WriteData(0x65);                                          // 51
   WriteData(0x67);                                          // 52
   WriteData(0x69);                                          // 53
   WriteData(0x6B);                                          // 54
   WriteData(0x6D);                                          // 55
                                                             // 
   WriteData(0x6F);                                          // 56
   WriteData(0x71);                                          // 57
   WriteData(0x73);                                          // 58
   WriteData(0x75);                                          // 59
   WriteData(0x77);                                          // 60
                                                             // 
   WriteData(0x79);                                          // 61
   WriteData(0x7B);                                          // 62
   WriteData(0x7D);                                          // 63
   WriteData(0x7F);                                          // 64
//...........................................................//
   SendCommand(LUT_B);                                       // 29. Blue Lookup Set. 
                                                             //
   WriteData(0x00);                                          //  1
   WriteData(0x02);                                          //  2
   WriteData(0x03);                                          //  3
   WriteData(0x05);                                          //  4
   WriteData(0x07);                                          //  5
                                                             //
   WriteData(0x09);                                          //  6
   WriteData(0x0B);                                          //  7
   WriteData(0x0D);                                          //  8
   WriteData(0x0E);                                          //  9
   WriteData(0x10);                                          // 10
                                                             //  
   WriteData(0x12);                                          // 11 
   WriteData(0x14);                                          // 12
   WriteData(0x16);                                          // 13
   WriteData(0x18);                                          // 14
   WriteData(0x1A);                                          // 15
                                                             // 
   WriteData(0x1C);                                          // 16
   WriteData(0x1E);                                          // 17
   WriteData(0x20);                                          // 18
   WriteData(0x22);                                          // 19
   WriteData(0x24);                                          // 20
                                                             //
   WriteData(0x26);                                          // 21
   WriteData(0x28);                                          // 22
   WriteData(0x2A);                                          // 23
   WriteData(0x2C);                                          // 24
   WriteData(0x2D);                                          // 25
                                                             //
   WriteData(0x2F);                                          // 26
   WriteData(0x31);                                          // 27
   WriteData(0x33);                                          // 28
   WriteData(0x35);                                          // 29
   WriteData(0x37);                                          // 30
                                                             //
   WriteData(0x39);                                          // 31
   WriteData(0x3B);                                          // 32
   WriteData(0x3E);                                          // 33
   WriteData(0x40);                                          // 34
   WriteData(0x42);                                          // 35
                                                             //
   WriteData(0x44);                                          // 36
   WriteData(0x46);                                          // 37
   WriteData(0x48);                                          // 38
   WriteData(0x4A);                                          // 39
   WriteData(0x4C);                                          // 40
                                                             //
   WriteData(0x4E);                                          // 41
   WriteData(0x50);                                          // 42
   WriteData(0x53);                                          // 43
   WriteData(0x55);                                          // 44
   WriteData(0x57);                                          // 45
                                                             //
   WriteData(0x59);                                          // 46
   WriteData(0x5B);                                          // 47
   WriteData(0x5D);                                          // 48
   WriteData(0x5F);                                          // 49
   WriteData(0x61);                                          // 50
                                                             //
   WriteData(0x63);                                          // 51
   WriteData(0x65);                                          // 52
   WriteData(0x67);                                          // 53
   WriteData(0x6A);                                          // 54
   WriteData(0x6C);                                          // 55
                                                             //
   WriteData(0x6E);                                          // 56
   WriteData(0x70);                                          // 57
   WriteData(0x73);                                          // 58
   WriteData(0x75);                                          // 59
   WriteData(0x77);                                          // 60
                                                             //
   WriteData(0x79);                                          // 61
   WriteData(0x7B);                                          // 62
   WriteData(0x7D);                                          // 63
   WriteData(0x7F);                                          // 64
}

void InitLGDP4216(void)
{
	ResetLGDP4216();

	SendCommand(Stand_by);				//Stand By OFF
	WriteData(0x00);
	
	SendCommand(DISPLAY2);				//DISPLAY 2 (IF_Mode)
	WriteData(0x01);
	
	SendCommand(DISPLAY3);				//DISPLAY 3
	WriteData(0x03);
	
	SendCommand(Panel_Type);			//Scan Direction
	WriteData(0x01);
	
//	SendCommand(Discharge_R);			//Red Discharge Time Set.
//	WriteData(0x07);					 
//	
//	SendCommand(Discharge_G);			//Green Discharge Time Set.
//	WriteData(0x07);					 
//	
//	SendCommand(Discharge_B);           //Blue Discharge Time Set.
//	WriteData(0x07);                     
//	
//	SendCommand(R_Peak_TIME);			//Red Precharge Peak Time Set.
//	WriteData(0x05);					   
//	
//	SendCommand(G_Peak_TIME);           //Green Precharge Peak Time Set.
//	WriteData(0x0A);                     
//	
//	SendCommand(B_Peak_TIME);           //Blue Precharge Peak Time Set.
//	WriteData(0x0A);                     
//	
	SendCommand(SCAN_TIME);				//Scan to Scan Gap Set.
	WriteData(0x00);                                             
	
	SendCommand(BP_MODE);				//Dummy Scan Enable/Disable.
	WriteData(0x00);
	
	GammaSet();
	
	SendCommand(LUT_BYPASS);			//Lookup Table Enable/Disable.
	WriteData(0x01); 
//	
//	SendCommand(Dotcurrent_R);			//Red Dot Current Set.
//	WriteData(0x0E);                                             
//	
//	SendCommand(Dotcurrent_G);			//Green Dot Current Set.
//	WriteData(0x08);                                          
//	
//	SendCommand(Dotcurrent_B);			//Blue Dot Current Set.
//	WriteData(0x0C);                                           
//	
//	SendCommand(Peak_current_R);		//Red Peak Current Set.
//	WriteData(0x07);      
//	                       
//	SendCommand(Peak_current_G);		//Green Peak Current Set.
//	WriteData(0x07);
//	
//	SendCommand(Peak_current_B);		//Blue Peak Current Set.
//	WriteData(0x07);  
	
	SendCommand(Gray_Level);			//0 Gray Floating / Zener Level Discharge.
	WriteData(0x00);
	
	SendCommand(Scan_Volatage);			//Scan Regulator Volatage Setting.
	WriteData(0x01);  
	
	SendCommand(Scan_CONTROL); 			//scan regulator halt.
	WriteData(0x37);
	
	SendCommand(AD_X);					//Display X Start Address Set.
	WriteData(0x00);                                         
	
	SendCommand(AD_Y);					//Display Y Start Address Set.
	WriteData(0x00);                      
	
	SendCommand(GPO);					//DC-DC ON (If you use..)
	WriteData(0x00);       
	
	SendCommand(DISPLAY1);				//Display ON / OFF.
	WriteData(0x80);  
}
//--------------------------------------------------------------//

void Draw_Point(u16 x,u16 y,u16 Color)
{
//	SendCommand(MXSTART);
//	WriteData(x);
//	SendCommand(MXEND);
//	WriteData(x);
//	SendCommand(MYSTART);
//	WriteData(y);
//	SendCommand(MYEND);
//	WriteData(y);
	if(x>OLED_WIDTH||y>OLED_HEIGHT)
		return;
	SendCommand(AD_X);
	WriteData(x);
	SendCommand(AD_Y);
	WriteData(y);
	SendCommand(DISP_DATA);
	WriteData(Color);
}

u16 Read_Point(u16 x,u16 y)
{
//	SendCommand(MXSTART);
//	WriteData(x);
//	SendCommand(MXEND);
//	WriteData(x);
//	SendCommand(MYSTART);
//	WriteData(y);
//	SendCommand(MYEND);
//	WriteData(y);
	if(x>OLED_WIDTH||y>OLED_HEIGHT)
		return 0;
	SendCommand(AD_X);
	WriteData(x);
	SendCommand(AD_Y);
	WriteData(y);
	SendCommand(DISP_DATA);
	return ReadData();
}

void Fill_Screen(u16 Color)
{
//	SendCommand(MXSTART);
//	WriteData(0);
//	SendCommand(MXEND);
//	WriteData(159);
//	SendCommand(MYSTART);
//	WriteData(0);
//	SendCommand(MYEND);
//	WriteData(127);
	SendCommand(AD_X);
	WriteData(0);
	SendCommand(AD_Y);
	WriteData(0);
	SendCommand(DISP_DATA);
	for(u16 i=0;i<0x5000;i++)
		WriteData(Color);
}

u16 absl(int Value)
{
	if(Value>=0)
		return Value;
	else
		return -Value;
}

void OLED_Fill(u16 x1,u16 y1,u16 x2,u16 y2,u16 Color)
{
	
	if(x2>OLED_WIDTH||y2>OLED_HEIGHT)
		return;
	if(x1>OLED_WIDTH||y1>OLED_HEIGHT)
		return;
	
	for(u16 i=y1;i<=	y2;i++)
	{
		SendCommand(AD_X);
		WriteData(x1);
		SendCommand(AD_Y);
		WriteData(i);
		SendCommand(DISP_DATA);
		for(u16 j=x1;j<=x2;j++)
			WriteData(Color);
	}
}
