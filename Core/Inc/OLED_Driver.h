#ifndef __OLED_DRIVER_H
#define __OLED_DRIVER_H

#include "stm32f4xx_hal.h"
#include "sys.h"

#define OLED_RST PAout(1)

#define DISPLAY1		0x00
#define DISPLAY2		0x01
#define DISPLAY3		0x02
#define Panel_Type		0x03
#define Panel_Type2		0x04
#define DISP_DATA		0x05
#define AD_X			0x06
#define AD_Y			0x07
#define MXSTART			0x08
#define MXEND			0x09
#define MYSTART			0x0A
#define MYEND			0x0B
#define PCDR			0x0D
#define SS_TIME1		0x10
#define SS_TIME2		0x11
#define SS_TIME3		0x12
#define SS_TIME4		0x13
#define SS_Pattern1		0x14
#define SS_Pattern2		0x15
#define SS_Pattern3		0x16
#define SS_Pattern4		0x17
#define SS_Pattern5		0x18
#define SS_Pattern6		0x19
#define SS_Pattern7		0x1A
#define SS_Pattern8		0x1B
#define SS_X_Limit0		0x1C
#define SS_X_Limit1		0x1D
#define SS_Y_Limit0		0x1E
#define SS_Y_Limit1		0x1F
#define Discharge_R		0x20
#define Discharge_G		0x21
#define Discharge_B		0x22
#define R_Peak_TIME		0x23
#define G_Peak_TIME		0x24
#define B_Peak_TIME		0x25
#define SCAN_TIME		0x26
#define BP_MODE			0x27
#define FLM_LINE		0x28
#define LUT_R			0x40
#define LUT_G			0x41
#define LUT_B			0x42
#define LUT_BYPASS		0x43
#define Dotcurrent_R	0x50
#define Dotcurrent_G	0x51
#define Dotcurrent_B	0x52
#define Peak_current_R	0x53
#define Peak_current_G	0x54
#define Peak_current_B	0x55
#define BP2_Current		0x56
#define Gray_Level		0x5A
#define Scan_Volatage	0x60
#define Scan_CONTROL	0x61
#define Stand_by		0xA0
#define GPO				0xA1
#define TEST_MODE		0xA2
#define FOSC_TEST		0xA3
#define OFF_SET			0xA4
#define OFF_GRAY		0xA5

#define Use_LUT 1

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable 	无符号8位整型变量  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable		有符号8位整型变量  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable 	无符号16位整型变量 */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable 		有符号16位整型变量 */
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable 	无符号32位整型变量 */
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable 		有符号32位整型变量 */
typedef float          fp32;                    /* single precision floating point variable (32bits) 单精度浮点数（32位长度） */
typedef double         fp64;    

#define OLED_WIDTH   159
#define OLED_HEIGHT  127
void ResetLGDP4216(void);

inline void SendCommand(u16 Cmd){(*(volatile u16*)0x60000000) = Cmd;}
inline void WriteData(u16 Data){(*(volatile u16*)0x60020000) = Data;}
inline u16 ReadData(void){return (*(volatile u16*)0x60020000);}

#define PI 3.14159f
#define OCX 80
#define OCY 64
void OLED_Fill(u16 x1,u16 y1,u16 x2,u16 y2,u16 Color);
void InitLGDP4216(void);
void Fill_Screen(u16 Color);
void Draw_Point(u16 x,u16 y,u16 Color);
u16 Read_Point(u16 x,u16 y);
#endif
