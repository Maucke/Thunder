/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCDConf_1375_C8_C320x240.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*                   General configuration of LCD
*
**********************************************************************
*/

#define LCD_XSIZE          (160)		/* 320 -> 400 */
#define LCD_YSIZE          (128)		/* 240 */
#define LCD_CONTROLLER     (-1)		/* 9320 -> 5420 */
#define LCD_BITSPERPIXEL   (16)
#define LCD_FIXEDPALETTE   (565)
#define LCD_SWAP_RB        (1)		   //������ɫ����
//#define LCD_SWAP_XY        (1)
//LCD_MIRROR_X
#define LCD_INIT_CONTROLLER()  LCD_hard_Init();
 
#endif /* LCDCONF_H */

 
