#include "gui.h"
#include "OLED_Animation.h"
#include "OLED_Driver.h"

#include "main.h"
#include "gpio.h"
#include "sys.h"
#include "math.h"

float RandMind[3][MINDMAX],MovMind[2][MINDMAX];
float MindStep_X[MINDMAX],MindStep_Y[MINDMAX];
u8 MindNum = 5;
u8 CircleNum = 1;
u8 SnowflakeNum = 1;
u8 MeteoNum = 1;
u8 PlanetNum = 1;

	

OLED_STATUS OLED_MovMind(u8 Index)
{
	if(MovMind[0][Index]<=3)
	{	
		MovMind[0][Index] = 4;
		return OLED_IDLE;
	}
	else if(MovMind[0][Index]>=OLED_WIDTH-2)
	{
		MovMind[0][Index] = OLED_WIDTH-3;
		return OLED_IDLE;
	}
	else if(MovMind[1][Index]<=0)
	{
		MovMind[1][Index] = 1;
		return OLED_IDLE;
	}
	else if(MovMind[1][Index]>=OLED_HEIGHT-2)
	{
		MovMind[1][Index] = OLED_HEIGHT-3;
		return OLED_IDLE;
	}
	else
	{
		MovMind[0][Index] += MindStep_X[Index];
		MovMind[1][Index] += MindStep_Y[Index];
	}
  return OLED_BUSY;
}

u16 GetMindDistanceSquare(u16 x0,u16 y0,u16 x1,u16 y1)
{
	return ((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1));
}

void Motion_MindInit(void)
{
	static float DistanceX,DistanceY;
	int i;
	for(i=0;i<MINDMAX;i++)
	{
		RandMind[0][i] = rand()%(OLED_WIDTH-4)+4;
		__ASM("NOP");
		RandMind[1][i] = rand()%OLED_HEIGHT;
		__ASM("NOP");
//		RandMind[2][i] = oled.RandomColor();
		__ASM("NOP");
		MovMind[0][i] = rand()%(OLED_WIDTH-4)+4;
		__ASM("NOP");
		MovMind[1][i] = rand()%OLED_HEIGHT;
		DistanceX = RandMind[0][i] - MovMind[0][i];
		DistanceY = RandMind[1][i] - MovMind[1][i];
		if(DistanceX<0&&DistanceY>=0)
		{
			if(-DistanceX>DistanceY)
			{
				MindStep_X[i]=-1;
				MindStep_Y[i]=-DistanceY/DistanceX;
			}
			else
			{
				MindStep_X[i]=DistanceX/DistanceY;;
				MindStep_Y[i]=1;
			}
		}
		else if(DistanceX>=0&&DistanceY<0)
		{
			if(DistanceX>-DistanceY)
			{
				MindStep_X[i]=1;
				MindStep_Y[i]=DistanceY/DistanceX;
			}
			else
			{
				MindStep_X[i]=-DistanceX/DistanceY;;
				MindStep_Y[i]=-1;
			}
		}
		else if(DistanceX>=0&&DistanceY>=0)
		{
			if(DistanceX>DistanceY)
			{
				MindStep_X[i]=1;
				MindStep_Y[i]=DistanceY/DistanceX;
			}
			else
			{
				MindStep_X[i]=DistanceX/DistanceY;;
				MindStep_Y[i]=1;
			}
		}
		else if(DistanceX<0&&DistanceY<0)
		{
			if(-DistanceX>-DistanceY)
			{
				MindStep_X[i]=-1;
				MindStep_Y[i]=-DistanceY/DistanceX; 
			}
			else
			{
				MindStep_X[i]=-DistanceX/DistanceY;;
				MindStep_Y[i]=-1;
			}
		}
	}
	MindNum = 5;
}


void Motion_Mind(void)
{
	static float DistanceX,DistanceY;
	int i,j;
	for(i=0;i<MindNum;i++)
	{
		if(OLED_MovMind(i) == OLED_IDLE)
		{
			RandMind[0][i] = rand()%(OLED_WIDTH-4)+4;
			__ASM("NOP");
			RandMind[1][i] = rand()%OLED_HEIGHT;
//			RandMind[2][i] = oled.RandomColor();
			
			DistanceX = RandMind[0][i] - MovMind[0][i];
			DistanceY = RandMind[1][i] - MovMind[1][i];
			if(DistanceX<0&&DistanceY>=0)
			{
				if(-DistanceX>DistanceY)
				{
					MindStep_X[i]=-1;
					MindStep_Y[i]=-DistanceY/DistanceX;
				}
				else
				{
					MindStep_X[i]=DistanceX/DistanceY;;
					MindStep_Y[i]=1;
				}
			}
			else if(DistanceX>=0&&DistanceY<0)
			{
				if(DistanceX>-DistanceY)
				{
					MindStep_X[i]=1;
					MindStep_Y[i]=DistanceY/DistanceX;
				}
				else
				{
					MindStep_X[i]=-DistanceX/DistanceY;;
					MindStep_Y[i]=-1;
				}
			}
			else if(DistanceX>=0&&DistanceY>=0)
			{
				if(DistanceX>DistanceY)
				{
					MindStep_X[i]=1;
					MindStep_Y[i]=DistanceY/DistanceX;
				}
				else
				{
					MindStep_X[i]=DistanceX/DistanceY;;
					MindStep_Y[i]=1;
				}
			}
			else if(DistanceX<0&&DistanceY<0)
			{
				if(-DistanceX>-DistanceY)
				{
					MindStep_X[i]=-1;
					MindStep_Y[i]=-DistanceY/DistanceX;
				}
				else
				{
					MindStep_X[i]=-DistanceX/DistanceY;;
					MindStep_Y[i]=-1;
				}
			}
			if(MindNum<MINDMAX )
			{
				MindNum++;
			}
		}
	}
	
	for(i=0;i<MindNum;i++)
	{
		for(j=0;j<MindNum;j++)
		{
//			Temp = GetMindDistanceSquare(MovMind[0][i],MovMind[1][i],MovMind[0][j],MovMind[1][j]);
			if((MovMind[0][i]-MovMind[0][j])*(MovMind[0][i]-MovMind[0][j])+(MovMind[1][i]-MovMind[1][j])*(MovMind[1][i]-MovMind[1][j])<900)
			{
				GUI_AA_DrawLine(MovMind[0][j],MovMind[1][j],MovMind[0][i],MovMind[1][i]);
			}
		}
	}
	
	for(i=0;i<MindNum;i++)
		GUI_AA_FillCircle(MovMind[0][i],MovMind[1][i],2);
}

u16 FucCircle[4][CIRCLEMAX];

OLED_STATUS OLED_FucCircle(u8 Index,int Size)
{
	static float Motion[CIRCLEMAX]={0};
	if(Motion[Index]<FucCircle[0][Index]%6+16)
	{
		if(Size-Motion[Index]<0)
		{
			Motion[Index] = 0;
			return OLED_IDLE;
		}
		GUI_AA_FillCircle(FucCircle[0][Index],FucCircle[1][Index],Size-Motion[Index]);
		GUI_DrawCircle(FucCircle[0][Index],FucCircle[1][Index],Size+Motion[Index]);
		Motion[Index]+=0.4f;
		return OLED_BUSY;
	}
	else
	{
		Motion[Index] = 0;
		return OLED_IDLE;
	}
}
void Motion_CircleInit(void)
{
	int i;
	for(i=0;i<CIRCLEMAX;i++)
	{
		FucCircle[0][i] = rand()%(OLED_WIDTH-12)+6;
		__ASM("NOP");
		FucCircle[1][i] = rand()%OLED_HEIGHT;
		__ASM("NOP");
			FucCircle[2][i] = rand()%10+2;
		__ASM("NOP");
//			FucCircle[3][i] = oled.RandomColor();
	}
	CircleNum=1;
}

void Motion_Circle(void)
{
	int i;
	for(i=0;i<CircleNum;i++)
	{
		if(OLED_FucCircle(i,FucCircle[2][i]) == OLED_IDLE)
		{
			FucCircle[0][i] = rand()%(OLED_WIDTH-12)+6;
			__ASM("NOP");
			FucCircle[1][i] = rand()%OLED_HEIGHT;
			__ASM("NOP");
			FucCircle[2][i] = rand()%10+2;
		__ASM("NOP");
//			FucCircle[3][i] = oled.RandomColor();

			if(CircleNum<CIRCLEMAX )
			{
				CircleNum++;
			}
		}
	}
}

u16 MovSnowflake[5][STARMAX];

OLED_STATUS OLED_MovSnowflake(u8 Index)
{
	 int32   dx;						// 直线x轴差值变量
    int32   dy;          			// 直线y轴差值变量
    int8    dx_sym;					// x轴增长方向，为-1时减值方向，为1时增值方向
    int8    dy_sym;					// y轴增长方向，为-1时减值方向，为1时增值方向
    int32   dx_x2;					// dx*2值变量，用于加快运算速度
    int32   dy_x2;					// dy*2值变量，用于加快运算速度
   static int32   di[STARMAX];						// 决策变量
//   if(Mo150vSnowflake[1][Index]==0)
	dx = MovSnowflake[3][Index] - MovSnowflake[0][Index] ;			// 求取两点之间的差值
	 
   dy = (OLED_HEIGHT-1) - MovSnowflake[1][Index];
	
		if(MovSnowflake[1][Index]>=OLED_HEIGHT||MovSnowflake[0][Index]>=OLED_WIDTH)
			return OLED_IDLE;
	
   /* 判断增长方向，或是否为水平线、垂直线、点 */
   if(dx>0)							// 判断x轴方向
   {  dx_sym = 1;					// dx>0，设置dx_sym=1
   }
   else
   {  if(dx<0)
      {  dx_sym = -1;				// dx<0，设置dx_sym=-1
      }
      else
      {  // dx==0，画垂直线，或一点
				
					 MovSnowflake[1][Index]+=1;
      	 return OLED_BUSY;
      }
   }
   
   if(dy>0)							// 判断y轴方向
   {  dy_sym = 1;					// dy>0，设置dy_sym=1
   }
   else
   {  if(dy<0)
      {  dy_sym = -1;				// dy<0，设置dy_sym=-1
      }
      else
      {  // dy==0，画水平线，或一点
				
					 MovSnowflake[0][Index]+=1;
      	 return OLED_BUSY;
      }
   }
    
   /* 将dx、dy取绝对值 */
   dx = dx_sym * dx;
   dy = dy_sym * dy;
 
   /* 计算2倍的dx及dy值 */
   dx_x2 = dx*2;
   dy_x2 = dy*2;
   
   /* 使用Bresenham法进行画直线 */
   if(dx>=dy)						// 对于dx>=dy，则使用x轴为基准
   {
			di[Index] = dy_x2 - dx;

         MovSnowflake[0][Index] += dx_sym;
         if(di[Index]<0)
         {  di[Index] += dy_x2;			// 计算出下一步的决策值
         }
         else
         {  di[Index] += dy_x2 - dx_x2;
            MovSnowflake[1][Index] += dy_sym;
         }
   }
   else								// 对于dx<dy，则使用y轴为基准
   {  
		 di[Index] = dx_x2 - dy;

         MovSnowflake[1][Index] += dy_sym;
         if(di[Index]<0)
         {  di[Index] += dx_x2;
         }
         else
         {  di[Index] += dx_x2 - dy_x2;
            MovSnowflake[0][Index] += dx_sym;
         }
   } 
  return OLED_BUSY;
}

void Motion_SnowflakeInit(void)
{
	int i;
	for(i=0;i<STARMAX;i++)
	{
			MovSnowflake[0][i] = rand()%(OLED_WIDTH-12)+6;
			MovSnowflake[1][i] = 1;
			MovSnowflake[3][i] = MovSnowflake[0][i]+32;
			__ASM("NOP");
			MovSnowflake[2][i] = rand()%5;
//			MovSnowflake[4][i] = oled.RandomColor();
	}
	SnowflakeNum = 5;
}

void Motion_Snowflake(void)
{
	int i,j;
//	GUI_AA_DrawLine(MovSnowflake[0][0],MovSnowflake[1][i],MovSnowflake[3][i],95,15);
	for(i=0;i<SnowflakeNum;i++)
	{
		for(j=0;j<MovSnowflake[4][i]%5+1;j++)
		{
			if(OLED_MovSnowflake(i) == OLED_IDLE)
			{
				MovSnowflake[0][i] = rand()%(OLED_WIDTH-12)+6;
				MovSnowflake[1][i] = 1;
				MovSnowflake[3][i] = MovSnowflake[0][i]+32;
				__ASM("NOP");
				MovSnowflake[2][i] = rand()%5;
//				MovSnowflake[4][i] = oled.RandomColor();
				if(SnowflakeNum<STARMAX )
				{
					SnowflakeNum++;
				}
			}
		}
		switch(MovSnowflake[2][i])
		{
			case 0:GUI_AA_FillCircle(MovSnowflake[0][i],MovSnowflake[1][i],1);break;
			case 1:GUI_AA_FillCircle(MovSnowflake[0][i],MovSnowflake[1][i],1);
							Draw_Point(MovSnowflake[0][i],MovSnowflake[1][i],0);break;
			case 2:Draw_Point(MovSnowflake[0][i],MovSnowflake[1][i],MovSnowflake[4][i]);break;
			case 3:Draw_Point(MovSnowflake[0][i],MovSnowflake[1][i],MovSnowflake[4][i]);Draw_Point(MovSnowflake[0][i]+1,MovSnowflake[1][i]+1,MovSnowflake[4][i]);break;
			case 4:Draw_Point(MovSnowflake[0][i],MovSnowflake[1][i],MovSnowflake[4][i]);Draw_Point(MovSnowflake[0][i],MovSnowflake[1][i]+1,MovSnowflake[4][i]);Draw_Point(MovSnowflake[0][i]+1,MovSnowflake[1][i],MovSnowflake[4][i]);break;
		}
	}
}

float MovmeteorStep = 60;
u16 Movmeteor[6][METEORMAX];
float MovmeteorStep_X;
float Movmeteor_X[METEORMAX];

OLED_STATUS OLED_Movmeteor(u8 Index)
{
	Movmeteor[1][Index] ++;
	Movmeteor_X[Index] += MovmeteorStep_X;
	if(Movmeteor[1][Index]>OLED_HEIGHT)
		return OLED_IDLE;
	else
		return OLED_BUSY;
}

void Motion_MovmeteorInit(void)
{
	int i;
	for(i=0;i<METEORMAX;i++)
	{
			Movmeteor[0][i] = rand()%OLED_WIDTH;
			Movmeteor_X[i] = Movmeteor[0][i];
			Movmeteor[1][i] = 0;
			Movmeteor[2][i] = rand()%5+1;//Speed
			Movmeteor[3][i] = rand()%5;//Type
			Movmeteor[4][i] = rand()%15;;//LineColor
//			Movmeteor[5][i] = oled.RandomColor();
	}
	MeteoNum = 5;
	MovmeteorStep_X = MovmeteorStep / OLED_HEIGHT;
}

void Motion_Movmeteor(void)
{
	int i,j;
	for(i=0;i<MeteoNum;i++)
	{
		for(j=0;j<Movmeteor[2][i];j++)
		{
			if(OLED_Movmeteor(i) == OLED_IDLE)
			{
				Movmeteor[0][i] = rand()%OLED_WIDTH;
				Movmeteor_X[i] = Movmeteor[0][i];
				Movmeteor[1][i] = 0;
				Movmeteor[2][i] = rand()%5+1;//Speed
				Movmeteor[3][i] = rand()%4;//Type
				Movmeteor[4][i] = rand()%15;;//LineColor
//				Movmeteor[5][i] = oled.RandomColor();
				if(MeteoNum<METEORMAX )
				{
					MeteoNum++;
				}
			}
		}
		if(Movmeteor[4][i]>1)
		{
			Movmeteor[4][i]--;
			GUI_AA_DrawLine(Movmeteor[0][i],0,Movmeteor_X[i],Movmeteor[1][i]);
		}
		else if((Movmeteor[1][i]-(Movmeteor[2][i]*3))>0)
			GUI_AA_DrawLine((Movmeteor[1][i]-(Movmeteor[2][i]*3))*MovmeteorStep_X+Movmeteor[0][i],Movmeteor[1][i]-(Movmeteor[2][i]*3),Movmeteor_X[i],Movmeteor[1][i]);
		switch(Movmeteor[3][i])
		{
			case 0:Draw_Point(Movmeteor_X[i],Movmeteor[1][i],Movmeteor[5][i]);break;
			case 1:Draw_Point(Movmeteor_X[i]+1,Movmeteor[1][i],Movmeteor[5][i]);Draw_Point(Movmeteor_X[i],Movmeteor[1][i]+1,Movmeteor[5][i]);break;
			case 2:GUI_AA_FillCircle(Movmeteor_X[i],Movmeteor[1][i],1);break;
			case 3:GUI_DrawCircle(Movmeteor_X[i],Movmeteor[1][i],1);Draw_Point(Movmeteor_X[i],Movmeteor[1][i],0);break;
		}
	}
}

double MovPlanet[7][PLANETMAX];

OLED_STATUS OLED_Planet(u8 Index){
	MovPlanet[4][Index]+= MovPlanet[2][Index];
	if(MovPlanet[4][Index]>=360)
	{
		MovPlanet[4][Index] = 0;
		MovPlanet[3][Index]++;
		if(MovPlanet[3][Index]>=64)
			return OLED_IDLE;
	}
	return OLED_BUSY;
}

void Motion_PlanetInit(void){
	
	int i;
	for(i=0;i<PLANETMAX;i++)
	{
			MovPlanet[0][i] = rand()%4+1;	//行星大小
				__ASM("NOP");
			//MovPlanet[1][i] = RandomColor();		//行星颜色			
				__ASM("NOP");					
			MovPlanet[2][i] = (rand()%20+10)/5;	//行星转速
				__ASM("NOP");
			MovPlanet[3][i] = rand()%60+4;	//行星运行轨道
				__ASM("NOP");
			MovPlanet[4][i] = 0;	//行星运行角度
	}
	PlanetNum = 5;
}


void Motion_Planet(void){
	
	int i,j;
//	GUI_AA_DrawLine(MovSnowflake[0][0],MovSnowflake[1][i],MovSnowflake[3][i],95,15);
	for(i=0;i<PlanetNum;i++)
	{
		if(OLED_Planet(i) == OLED_IDLE)
		{
			MovPlanet[0][i] = rand()%4+1;	//行星大小
				__ASM("NOP");
			//MovPlanet[1][i] = RandomColor();		//行星颜色		
				__ASM("NOP");										
			MovPlanet[2][i] = (rand()%20+10)/5;	//行星转速
				__ASM("NOP");
			MovPlanet[3][i] = rand()%60+4;	//行星运行轨道
				__ASM("NOP");
			MovPlanet[4][i] = 0;	//行星运行角度
			
			MovPlanet[5][i] = 0;	//行星X
			MovPlanet[6][i] = 0;	//行星Y
			
			if(PlanetNum<PLANETMAX )
			{
				PlanetNum++;
			}
		}
		MovPlanet[5][i] = OCX+(MovPlanet[3][i]*cos(MovPlanet[4][i]*PI/180));
		MovPlanet[6][i] = OCY+(MovPlanet[3][i]*sin(MovPlanet[4][i]*PI/180));
		
		GUI_DrawCircle(OCX,OCY,MovPlanet[3][i]);
		
	}
	
	
	for(i=0;i<PlanetNum;i++)
	{
		for(j=0;j<PlanetNum;j++)
		{
//			Temp = GetMindDistanceSquare(MovMind[0][i],MovMind[1][i],MovMind[0][j],MovMind[1][j]);
			if((MovPlanet[5][i]-MovPlanet[5][j])*(MovPlanet[5][i]-MovPlanet[5][j])+(MovPlanet[6][i]-MovPlanet[6][j])*(MovPlanet[6][i]-MovPlanet[6][j])<1600)
			{
				if(MovPlanet[0][i]==1||MovPlanet[0][j]==1)
					;
				else
					GUI_AA_DrawLine(MovPlanet[5][j],MovPlanet[6][j],MovPlanet[5][i],MovPlanet[6][i]);
			}
		}
	}
	
//	for(i=0;i<PlanetNum-1;i++)
//	{
//		GUI_AA_DrawLine(OCX+(MovPlanet[3][i]*cos(MovPlanet[4][i]*PI/180)),OCY+(MovPlanet[3][i]*sin(MovPlanet[4][i]*PI/180)),OCX+(MovPlanet[3][i+1]*cos(MovPlanet[4][i+1]*PI/180)),OCY+(MovPlanet[3][i+1]*sin(MovPlanet[4][i+1]*PI/180)));
//	}
//	GUI_AA_DrawLine(OCX+(MovPlanet[3][0]*cos(MovPlanet[4][0]*PI/180)),OCY+(MovPlanet[3][0]*sin(MovPlanet[4][0]*PI/180)),OCX+(MovPlanet[3][PlanetNum-1]*cos(MovPlanet[4][PlanetNum-1]*PI/180)),OCY+(MovPlanet[3][PlanetNum-1]*sin(MovPlanet[4][PlanetNum-1]*PI/180)));
	
	for(i=0;i<PlanetNum;i++)
	{
		GUI_AA_FillCircle(MovPlanet[5][i],MovPlanet[6][i],MovPlanet[0][i]);
	}
	
}


void OLED_AllMotion_Init(void)
{
	Motion_MindInit();
	Motion_CircleInit();
	Motion_SnowflakeInit();
	Motion_MovmeteorInit();
	Motion_PlanetInit();
}

void OLED_CustormMotion(u8 Channel)
{
	switch(Channel)
	{
	case 0:Motion_Mind();break;
	case 1:Motion_Movmeteor();break;
	case 2:Motion_Snowflake();break;
	case 3:Motion_Planet();break;
	}
}

void OLED_AllMotion(u8 Type,u16 Speed)
{
//	static int SwitchLst = -1;
	static u32 Count = 0;
	static u8 NowMotion = 0;
	static u16 SpeedSave = 0;
	Speed++;
	if(SpeedSave!=Speed)
	{
		SpeedSave = Speed;Count = 0;
	}
	Count++;

//	if(SwitchFlag)
//	{
//		OLED_AllMotion_Init();
//		SwitchFlag = False;
//	}
	if((Type&0xf) == 0)
		return;
	
	switch(Count/(5000-Speed*40))
	{
		case 0:
		if(Type&8){
 CircleNum = 1;
 SnowflakeNum = 5;
 MeteoNum = 5;NowMotion=0; }else {Count=(5000-Speed*40);}   break;
		case 1:
		if(Type&4){ 
 MindNum = 5;
 CircleNum = 1;
 SnowflakeNum = 5;NowMotion=1;}else {Count=(5000-Speed*40)*2;}   break;
		case 2:
		if(Type&2){
 MindNum = 5;
 CircleNum = 1;
 MeteoNum = 5; NowMotion=2;}else {Count=(5000-Speed*40)*3;}   break;
		case 3:
		if(Type&1){
 MindNum = 5;
 MeteoNum = 5;
 SnowflakeNum = 5; NowMotion=3;}else {Count=0;}   break;
		default:Count=0;break;
	}OLED_CustormMotion(NowMotion);
}



