/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <string.h>
#include "main.h"
#include <stdio.h>
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA2_Stream2;
    hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA2_Stream7;
    hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
	return 1;
}


DEVICE_CMD Device_Cmd;
DEVICE_MSG Device_Msg;
DEVICE_STR Device_Str;
const char *Week[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

void ConvertData(void)
{
	if(Device_Msg.cputemp)
	sprintf(Device_Str.cputemp,"%02d.%1d$ ",Device_Msg.cputemp/10,Device_Msg.cputemp%10);
	if(Device_Msg.cpuclock)
	sprintf(Device_Str.cpuclock,"%dMhz ",Device_Msg.cpuclock);
	sprintf(Device_Str.cpuload,"%02.1f%%  ",(double)Device_Msg.cpuload/10);
	if(Device_Msg.cpufan)
	sprintf(Device_Str.cpufan,"%dRpm ",Device_Msg.cpufan);
	
	if(Device_Msg.gputemp)
	sprintf(Device_Str.gputemp,"%02d.%1d$ ",Device_Msg.gputemp/10,Device_Msg.gputemp%10);
	if(Device_Msg.gpuclock)
	sprintf(Device_Str.gpuclock,"%dMhz ",Device_Msg.gpuclock);
	sprintf(Device_Str.gpuload,"%02.1f%%  ",(double)Device_Msg.gpuload/10);
	if(Device_Msg.gpufan)
	sprintf(Device_Str.gpufan,"%dRpm ",Device_Msg.gpufan);
	
	if(Device_Msg.maintemp)
	sprintf(Device_Str.maintemp,"%03.1f$ ",(double)Device_Msg.maintemp/10);
	if(Device_Msg.mainfan)
	sprintf(Device_Str.mainfan,"%dRpm ",Device_Msg.mainfan);
	
	sprintf(Device_Str.ramload,"%02.1f%% ",(double)Device_Msg.ramload/10);
	
	if(Device_Msg.ramusrdata)
	sprintf(Device_Str.ramusrdata,"%d",Device_Msg.ramusrdata);
	
	if(Device_Msg.cpufan)	
	sprintf(Device_Str.ncpufan,"%04d",Device_Msg.cpufan);
	if(Device_Msg.cpuclock)
	sprintf(Device_Str.ncpuclock,"%04d",Device_Msg.cpuclock);
	if(Device_Msg.gpufan)
	sprintf(Device_Str.ngpufan,"%04d",Device_Msg.gpufan);
	if(Device_Msg.gputemp)
	sprintf(Device_Str.ngputemp,"%02d.%1d",Device_Msg.gputemp/10,Device_Msg.gputemp%10);
	
	
	if(Device_Msg.cputemp)
		sprintf(Device_Str.vcputemp,"%03d#",Device_Msg.cputemp);	
	if(Device_Msg.gputemp)
		sprintf(Device_Str.vgputemp,"%03d#",Device_Msg.gputemp);	
	
		
		sprintf(Device_Str.vhour,"%02d",Device_Msg.uarthour);	
		sprintf(Device_Str.vmin,"%02d",Device_Msg.uartminute);	
		sprintf(Device_Str.vsec,"%02d",Device_Msg.uartsecond);	
		sprintf(Device_Str.date,"%s. %02d-%02d",Week[Device_Msg.uartweek],Device_Msg.uartmonth,Device_Msg.uartday);	
}

void InitData(void)
{
	sprintf(Device_Str.cputemp,"--.-$ ");
	sprintf(Device_Str.cpuclock,"----Mhz ");
	sprintf(Device_Str.cpuload,"--.-%%  ");
	sprintf(Device_Str.cpufan,"----Rpm ");
	
	sprintf(Device_Str.gputemp,"--.-$ ");
	sprintf(Device_Str.gpuclock,"----Mhz ");
	sprintf(Device_Str.gpuload,"--.-%%  ");
	sprintf(Device_Str.gpufan,"----Rpm ");
	
	sprintf(Device_Str.maintemp,"--.-$ ");
	sprintf(Device_Str.mainfan,"----Rpm ");
	
	sprintf(Device_Str.ramload,"--.-%% ");
	sprintf(Device_Str.ramusrdata,"----");
	
	sprintf(Device_Str.ngputemp,"--.-");	
	sprintf(Device_Str.ncpuclock,"----");	
	sprintf(Device_Str.ngpufan,"----");	
	sprintf(Device_Str.ncpufan,"----");	
	
	
	sprintf(Device_Str.vhour,"--");	
	sprintf(Device_Str.vmin,"--");	
	sprintf(Device_Str.vsec,"--");	
	sprintf(Device_Str.date,"--Unkown--");	

	memset(&Device_Msg,0,sizeof(Device_Msg));
}

void Judge_Mode()
{
//	static u8 normalcount=6,gamecount=6;
//	if(Device_Msg.gpuload>800)
//	{
//		gamecount ++;
//		if(gamecount>=10)
//		{
//			gamecount = 10;Display_Mode = MODE_GAME;
//			normalcount = 0;
//		}
//	}
//	else if(Device_Msg.gpuload<200)
//	{
//		normalcount ++;
//		if(normalcount>=10)
//		{
//			normalcount = 10;
//			gamecount = 0;
//		}
//	}
	Display_Mode = MODE_NORMAL;
}

uint8_t Uart_Recv1_Buf[Uart_Max_Length] = {0};
uint16_t Uart_Recv1_Length = 0;
uint8_t Uart_Overflow1_Flag = False;

u8 ReponseID[]={0xFF,0x55,'O','K',0x06,'N','e','b','u','l','a'};

void AnalysisComputermsg(uint8_t *Buf)
{
	if(Buf[0] == 0xFF &&Buf[1] == 0x55)
	{
		if(Buf[4] == 0x2)
		{
			switch (MAKEWORD(Buf[3], Buf[2]))
			{
			case CPU_Temp:
				Device_Msg.cputemp = MAKEWORD(Buf[6],Buf[5]);
				break;
			case CPU_Clock:
				Device_Msg.cpuclock = MAKEWORD(Buf[6],Buf[5]);
				break;
			case CPU_Load:
				Device_Msg.cpuload = MAKEWORD(Buf[6],Buf[5]);
				break;
			case CPU_Fan:
				Device_Msg.cpufan = MAKEWORD(Buf[6],Buf[5]);
				break;
			case CPU_POWER:
				Device_Msg.cpupower = MAKEWORD(Buf[6],Buf[5]);
				break;

			case GPU_Temp:
				Device_Msg.gputemp = MAKEWORD(Buf[6],Buf[5]);
				break;
			case GPU_Clock:
				Device_Msg.gpuclock = MAKEWORD(Buf[6],Buf[5]);
				break;
			case GPU_Load:
				Device_Msg.gpuload = MAKEWORD(Buf[6],Buf[5]);
				break;
			case GPU_Fan:
				Device_Msg.gpufan = MAKEWORD(Buf[6],Buf[5]);
				break;


			case Main_Temp:
				Device_Msg.maintemp = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Main_Fan:
				Device_Msg.mainfan = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Main_Vol:
				Device_Msg.mainvoltage = MAKEWORD(Buf[6],Buf[5]);
				break;

			case RAM_Load:
				Device_Msg.ramload = MAKEWORD(Buf[6],Buf[5]);
				break;
			case RAM_Data:
				Device_Msg.ramusrdata = MAKEWORD(Buf[6],Buf[5]);
				break;

			case HDD_Load:
				Device_Msg.hddload = MAKEWORD(Buf[6],Buf[5]);
				break;
			case HDD_Temp:
				Device_Msg.hddtemp = MAKEWORD(Buf[6],Buf[5]);
				break;

			case Uart_Year:
				Device_Msg.uartyear = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Uart_Month:
				Device_Msg.uartmonth = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Uart_Day:
				Device_Msg.uartday = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Uart_Week:
				Device_Msg.uartweek = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Uart_Hour:
				Device_Msg.uarthour = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Uart_Minute:
				Device_Msg.uartminute = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Uart_Second:
				Device_Msg.uartsecond = MAKEWORD(Buf[6],Buf[5]);
				break;
			case End_Frame_ADDR:
				if(MAKEWORD(Buf[6],Buf[5]) == 0x5A5A)
				{
					ConvertData();		
					Uart_Overflow1_Flag = True;
					if(Device_Cmd.commandmode == 1) 
					{
						Judge_Mode();
					}
				}break;
			case 0x3F3F:
				ReponseID[2] = (Buf[5] & 0x5A) | (Buf[6] & 0xA5);
				ReponseID[3] = (Buf[5] ^ 0x57) | (Buf[6] & 0x57);
				HAL_UART_Transmit_IT(&huart1,ReponseID,11);break;
			}
		}
	}
}

u8 SaveFlag = False;

void AnalysisCommand(uint8_t *Buf)
{
	if(Buf[0] == 0xFF &&Buf[1] == 0x55)
	{
		if(Buf[4] == 0x2)
		{
			switch (MAKEWORD(Buf[3], Buf[2]))
			{
				case Command_Mode:
//					if(Device_Cmd.commandmode != MAKEWORD(Buf[6],Buf[5]))
//					{
						Device_Cmd.commandmode = MAKEWORD(Buf[6],Buf[5]); 
						if(Device_Cmd.commandmode==3) Display_Mode = Device_Cmd.commandmode;
						else if(Device_Cmd.commandmode!=1) Display_Mode = MODE_NORMAL;
//					}
				break;
				case Command_Motion:
					if(Device_Cmd.commandmotion != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandmotion = MAKEWORD(Buf[6],Buf[5]);
						SaveFlag = True;
					}break;
				case Command_Style:
					if(Device_Cmd.commandstyle != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandstyle = MAKEWORD(Buf[6],Buf[5]);
					}break;
				case Command_Speed:
					if(Device_Cmd.commandspeed != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandspeed = MAKEWORD(Buf[6],Buf[5]);
						SaveFlag = True;
					}break;
				case Command_Brightness:
					if(Device_Cmd.commandbrightness != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandbrightness = MAKEWORD(Buf[6],Buf[5]);
						SaveFlag = True;
					}break;
				case Command_Set:
					if(Device_Cmd.commandset != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandset = MAKEWORD(Buf[6],Buf[5]);
						SaveFlag = True;
					}break;
				case Command_RGBMode:
					if(Device_Cmd.commandrgbmode != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandrgbmode = MAKEWORD(Buf[6],Buf[5]);
						SaveFlag = True;
					}break;
				case Command_RGBBrightness:
					if(Device_Cmd.commandrgbbrightness != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandrgbbrightness = MAKEWORD(Buf[6],Buf[5]);
						SaveFlag = True;
					}break;
				case Command_RGBColor:
					if(Device_Cmd.commandrgbcolor != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandrgbcolor = MAKEWORD(Buf[6],Buf[5]);
						SaveFlag = True;
					}break;
			}
		}
	}
}

void AnalysisComputername(uint8_t *Buf)
{
	u8 i;
	if(Buf[0] == 0xFF &&Buf[1] == 0x55)
	{
		if(Buf[4] > 0x2)
		{
			switch (MAKEWORD(Buf[3], Buf[2]))
			{
			case 0x101:for(i=0;i<Buf[4];i++) Device_Msg.cpuname[i] = Buf[i + 5];break;
			case 0x102:for(i=0;i<Buf[4];i++) Device_Msg.gpuname[i] = Buf[i + 5];break;
			case 0x103:for(i=0;i<Buf[4];i++) Device_Msg.mainname[i] = Buf[i + 5];break;
			}
		}
	}
}


void ClearFFT(void)
{
	int i;
	for(i=0;i<Uart_FFT_Length;i++) 
		Device_Msg.fft[i] = 0;
}


void AnalysisFFT(uint8_t *Buf)
{
	u16 i;
	if(Buf[0] == 0xFF &&Buf[1] == 0x55)
	{
		if(Buf[4] >= 0x2)
		{
			switch (MAKEWORD(Buf[3], Buf[2]))
			{
				case FFT_Data:for(i=0;i<Buf[4];i++) Device_Msg.fft[i] = Buf[i + 5];
				if(Device_Cmd.commandmode == 1) 
					Display_Mode = MODE_MUSIC;
					break;
				case Left_Vol:
					Device_Msg.leftvol = MAKEWORD(Buf[6],Buf[5]);break;
				case Right_Vol:
					Device_Msg.rightvol = MAKEWORD(Buf[6],Buf[5]);break;
			}
			Uart_Overflow1_Flag = True;
		}
	}
}



/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
