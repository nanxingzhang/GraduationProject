#include <msp430F5529.h>
#include <stdio.h>
#include "UCS_INIT.h"
#include "TIMER_INIT.h"
#include "KEY_SIG.h"
#include "LCD12864.h"
#include "LCD1602.h"
#include "Lcd12864spi.h"
#include "ADC12_INIT.h"
#include "ADS1118.h"
#include "DAC8571.h"
#include "TA1_PWM1.h"
#include "TB0_PWM2.h"
#include "TA0_PWM.h"
#include "TA2_PWM.h"


#define CPU_F ((double)16000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define Delay_Nms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

#define SMCLK  4000000
#define FreqHz 200                                 //周期(Hz)
#define Duty   60								   //占空比(%)

#define Period SMCLK/FreqHz                        //一般模式下周期       转换成计数值
#define Bright Period*Duty/100                     //一般模式下占空比   转换成计数值

#define DeadPeriod SMCLK/FreqHz/2                  //死区模式下周期       转换成计数值
#define DeadBright DeadPeriod*Duty/100             //死区模式下占空比   转换成计数值

unsigned int one_Percent = Period/100;             //占空比1%步进        转换成计数值
unsigned int ten_Percent = Period/10;              //占空比10%步进     转换成计数值
unsigned int max_Percent = Period;             	   //占空比最大值           转换成计数值
unsigned int min_Percent = 0;					   //占空比最小值           转换成计数值

/*---------------------------------------------------------------------*/
float ADC_Value=0;					  //ADC采样值
/*-----------------------------------------------------频率，占空比，相位计算相关*/
extern unsigned int cap_count,cap1value,cap2value;
extern unsigned int cap_flag,cap_finish,uptime,downtime,addtime;
float freq=0,phase=0,duty=0;
/*--------------------------------------------------------------------*/

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;			//Stop watchdog timer
    UCS_init();                 		//时钟初始化							ok
	KEY_SIG_init();             		//独立按键,LED初始化(P2.1,P1.1,P1.0,P4.7) ok
	lcd12864spi_init();         		//LCD串行初始化(P6.6,P6.5)				ok
	Ini_Lcd12864();						//LCD12864并行初始化(P6.6,P6.5,P6.4,P3)	ok
//	LCD1602_Init();                     //LCD1602并行初始化(P6.6,P6.5,P6.4,P3)	ok
//	DAC8571_Init();                     //DAC8571初始化(P8.1,P8.2) 			ok
//	ADC12_init();              			//片内ADC初始化							ok
	ADS1118_Init();                     //ADS1118初始化(P4.0,P4.1,P4.2,P4.3)	ok
//	TA0_Init();							//定时器A0初始化							ok
//	TA1_Init();							//定时器A1初始化							ok
//	TA2_Init();							//定时器A2初始化							ok
//	TB0_Init();							//定时器B0初始化							ok


/*-------------------------------------------------------------------PWM输出相关*/

//	TA1_PWM_Init('S',1,'B');       					//TA1.1PWM初始化 -->P2.0   ok
//	TA1_PWM_SetPeriod(Period);
//	TA1_PWM_SetPermill(Bright);						//滞后PWM

//	TB0_PWM_Init('S',1,'F');	   					//TB0.2PWM初始化 -->P7.4   ok
//	TB0_PWM_SetPeriod(Period);
//	TB0_PWM_SetPermill(Bright);						//超前PWM

//	TA0_PWM_Init('S',1,'D','D');  					//TA0.1PWM初始化 -->P1.2   ok
//	TA0_PWM_SetPeriod(DeadPeriod);					//TA0.2PWM初始化 -->P1.3
//	TA0_PWM_SetPermill(1,DeadBright);               //互补带死区

//	TA2_PWM_Init('S',1,'F','B');  					//TA2.1PWM初始化 -->P2.4   ok
//	TA2_PWM_SetPeriod(Period);    					//TA2.2PWM初始化 -->P2.5
//	TA2_PWM_SetPermill(1,Bright);                   //超前PWM
//	TA2_PWM_SetPermill(2,Bright);					//滞后PWM

    _enable_interrupts();		//使能总中断

	while(1)
	{
/*-----------------------------------------------------频率，占空比，相位计算方法一*/
//	cap_count=0;
//	while(cap_count<2);							//等待第二次捕获
//	freq  = SMCLK/1.0/cap1value;				//计算频率
//	phase = 360.0*cap2value/cap1value;			//计算相位
/*-----------------------------------------------------频率，占空比，相位计算方法二*/
//	cap_finish=0;
//	while(!cap_finish);                 		//等待所有捕获完成
//	duty  = uptime*100.0;
//	duty  = duty/(uptime+downtime);				//占空比
//	freq  = SMCLK/1.0/(uptime+downtime);		//频率
//	phase = 360.0*addtime/(uptime+downtime);	//相位差


/*-----------------------------------------------------------ADC&DAC相关*/
//	DAC8571_OUT(1.11);                          //测试DAC8571
//	ADC_Value = ADS1118(4,1);                   //测试ADS1118
//	sprintf(LCD_BUF_1,"%.3f",ADC_Value);        //显示ADC

/*--------------------------------------------------------LCD12864显示相关*/
//	lcd12864_disp_str(1, 1, tab_SPI1);
//	lcd12864_disp_str(1, 2, tab_SPI2);
//	lcd12864_disp_str(1, 3, tab_SPI3);
//	lcd12864_disp_str(1, 4, tab_SPI4);

/*---------------------------------------------------------LCD1602显示相关*/
//	LCD_SET_CURSOR(1,1);
//	Print(lcd_buff0,16);
//
//	LCD_SET_CURSOR(2,1);
//	Print(lcd_buff0,16);

/*-----------------------------------------------------Lcd12864spi显示相关*/
//
//	set_coord(1,2);
//	lcd12864_show_str(LCD_BUF_2,5);
//
//	set_coord(1,3);
//	lcd12864_show_str(LCD_BUF_3,5);
//
//	set_coord(1,4);
//	lcd12864_show_str(LCD_BUF_4,5);

/*--------------------------------------------------------------------*/

	Delay_Nms(10);
	}
}

