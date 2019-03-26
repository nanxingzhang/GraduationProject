/*
 * TB_PWM.c
 *
 *  Created on: 2015年11月20日
 *      Author: yumin
 */
#include "msp430f5529.h"

#define TB02_SET 	P7SEL |= BIT4; P7DIR |= BIT4		//P7.4
#define TB02_OFF 	P7SEL &= ~BIT4						//P7.4
/*************TB0*******************/

/*****************************************************************************************
* 名       称：    TB0_PWM_Init()
* 功       能：    TB0定时器作为PWM发生器的初始化设置函数
* 入口参数：   Clk:时钟源 'S'=SMCLK;   'A'=ACLK ;   'E'=TACLK(外部输入)； 'e'= TACLK(TACLK取反)
         Div:时钟分频系数: 1/2/4/8
		 Mode1:通道1的输出模式 'F'设为超前PWM（模式7），'B'滞后PWM（模式3）
* 出口参数：   1表示设置成功，0表示参数错误，设置失败。
* 说       明 : 在调用PWM相关函数之前，需要调用该函数设置TA的模式和时钟源。
* 范       例 : TB0_PWM_Init('A',1,'B')TA时钟设为ACLK,通道1滞后PWM输出
         TB0_PWM_Init('S',1,'F')TA时钟设为SMCLK,通道1超前PWM输出
 ****************************************************************************************/
char TB0_PWM_Init(char Clk,char Div,char Mode1)
{
  TB0CTL =0;												// 清除以前设置

  switch(Mode1)												//为定时器选择计数模式
  {
  case 'F': case 'f':										//普通PWM
	  TB0CTL |=MC_1; break;									//主定时器为增计数
  case 'B':case 'b':
	  TB0CTL |=MC_1; break;									//主定时器为增计数
  default : return(0);										//其他情况都是设置参数有误，返回0
  }

  switch(Clk)  												//为定时器TA选择时钟源
  {
    case 'A': case 'a':  	TB0CTL|=TASSEL_1; break;   		//ACLK
    case 'S': case 's': 	TB0CTL|=TASSEL_2; break;  		//SMCLK
    case 'E':            	TB0CTL|=TASSEL_0; break;  		//外部输入(TACLK)
    case 'e':          		TB0CTL|=TASSEL_3; break;   		//外部输入(TACLK取反)
    default :  return(0);  									//设置参数有误，返回0
  }
  switch(Div) 												//为定时器TA选择分频系数
  {
    case 1:   TB0CTL|=ID_0; break;   						//1
    case 2:   TB0CTL|=ID_1; break;   						//2
    case 4:   TB0CTL|=ID_2; break;  						//4
    case 8:   TB0CTL|=ID_3; break;                          //8
    default :  return(0);  									//设置参数有误，返回0
  }
  switch(Mode1)										 		//设置PWM通道1的输出模式。
  {
     case 'F':	case 'f':
              TB0CCTL2 =OUTMOD_7;
              TB02_SET;
              break;
     case 'B':	case 'b':
              TB0CCTL2 =OUTMOD_3;
              TB02_SET;
              break;
     default :  return(0); 							        //设置参数有误，返回0
  }
  return(1);
}
/*****************************************************************************************
* 名       称：TB0_PWM_SetPeriod()
* 功       能：设置PWM发生器的周期
* 入口参数：Period:周期(0~65535) 时钟个数
* 出口参数：1：设置成功     0：设置失败
* 说       明 :
* 范       例 : TB0_PWM_SetPeriod(500)设置PWM方波周期为500个时钟周期
 ****************************************************************************************/
char TB0_PWM_SetPeriod(unsigned int Period)
{
	if (Period>65535)	return(0);
	 TB0CCR0 = Period;
	return(1);
}

/*****************************************************************************************
* 名    称：TB0_PWM_SetPermill()
* 功    能：设置PWM输出的占空比(一个时钟个数)
* 入口参数：Duty: PWM高电平有效时间(0~65535)
* 出口参数：1设置成功，0设置失败
* 说    明: PWM高电平有效时间为Duty个时钟周期
* 范    例: TB0_PWM_SetPermill(50)设置PWM方波高电平有效时间为50个时钟周期
 ****************************************************************************************/
char TB0_PWM_SetPermill(unsigned int Duty)
{
	unsigned char Mod;
	Mod = (TB0CCTL2 & 0x00e0)>>5; //读取输出模式，OUTMOD0位于5-7位
	switch(Mod)			          //根据模式设定TACCRx
		{
		case 7: TB0CCR2=Duty;          break;
		case 3: TB0CCR2=TB0CCR0-Duty;  break;
		default: return(0);
		}
	return (1);
}


