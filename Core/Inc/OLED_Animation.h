#ifndef __OLED_ANIMATION_H
#define __OLED_ANIMATION_H

#include "stm32f4xx_hal.h"
#include "stdlib.h"
#include "sys.h"

#define MINDMAX 20
#define CIRCLEMAX 8
#define STARMAX 25
#define METEORMAX 20
#define DEFLINEMAX 30
#define PLANETMAX 5
typedef enum
{
  OLED_OK       = 0x00U,
  OLED_ERROR    = 0x01U,
  OLED_BUSY     = 0x02U,
  OLED_IDLE     = 0x03U,
} OLED_STATUS;


void Motion_MindInit(void);
void Motion_Mind(void);
void Motion_CircleInit(void);
void Motion_Circle(void);
void Motion_SnowflakeInit(void);
void Motion_Snowflake(void);
void Motion_MovmeteorInit(void);
void Motion_Movmeteor(void);
void Motion_PlanetInit(void);
void Motion_Planet(void);
void OLED_AllMotion_Init(void);
void OLED_CustormMotion(u8 Channel);
void OLED_AllMotion(u8 Type,u16 Speed);

OLED_STATUS OLED_MovMind(u8 Index);
OLED_STATUS OLED_FucCircle(u8 Index,int Size);
OLED_STATUS OLED_MovSnowflake(u8 Index);
OLED_STATUS OLED_Movmeteor(u8 Index);
OLED_STATUS OLED_Planet(u8 Index);

  
#endif
