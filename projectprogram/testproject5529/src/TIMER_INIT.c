/*
 * TIMER_INIT.c
 *
 *  Created on: 2015年11月20日
 *      Author: yumin
 *
 *      定时器可以使用比较模式，即作为定时计数使用，也可以使用捕获模式，测量脉宽
 *
 *      捕获模式下本程序使用两种方法计算频率，周期，占空比
 */
#include <msp430F5529.h>

#define CAP_MODE 1           //TA0定时器使用模式              0：比较（定时）模式     ；   1：捕获模式

#define SMCLK  4000000
#define mS     5             //定时器使用SMCLK，1分频下，最大可设定16ms，改变时钟源与分频数可以定时更久
#define count  mS*SMCLK/1000

void CAP1_deal();
void CAP2_deal();
void CAP3_deal();
void CAP4_deal();

/*-----------------------------------------------------频率，占空比，相位计算相关*/
unsigned int cap_count=0,
		     cap1value,cap2value;

unsigned int cap_flag=0,cap_finish=0,
             uptime=0,downtime=0,addtime=0;
/*--------------------------------------------------------------------*/
void TA0_Init(void)
{
#if CAP_MODE

//	P1DIR &=~ BIT2;
//	P1SEL |= BIT2;           //P1.2  CAPTURE1
//	P1DIR &=~ BIT3;
//	P1SEL |= BIT3;           //P1.3  CAPTURE2

	P1DIR &=~ BIT4;
	P1SEL |= BIT4;           //P1.4  CAPTURE3
	P1DIR &=~ BIT5;
	P1SEL |= BIT5;           //P1.5  CAPTURE4

//	TA0CCTL1 = CM_2 | CCIS_0 | SCS | CAP | CCIE;
//	TA0CCTL2 = CM_2 | CCIS_0 | SCS | CAP | CCIE;

	TA0CCTL3 = CM_2 | CCIS_0 | SCS | CAP | CCIE;
	TA0CCTL4 = CM_2 | CCIS_0 | SCS | CAP | CCIE;
	//允许捕获比较模块提出中断请求,下降沿捕获,同步捕获,工作在捕获模式
	TA0CTL    =  TACLR | TASSEL_2 | ID_0 | MC_2;
	//定时器清零,选择时钟SMCLK,1分频,连续计数模式

#else

	TA0CCTL0 |= CCIE;       //比较功能0(定时计数)开启CCIFG位中断
    TA0CCR0   = count;      //置入终值
//	TA0CCTL1 |= CCIE;		//比较功能1开启中断
//	TA0CCR1   = 10;		    //置入要比较的数值
//	TA0CCTL2 |= CCIE;		//比较功能2开启中断
//	TA0CCR2   = 100;		//置入要比较的数值
//	TA0CCTL3 |= CCIE;		//比较功能3开启中断
//	TA0CCR3   = 1000;		//置入要比较的数值
//	TA0CCTL4 |= CCIE;		//比较功能4开启中断
//	TA0CCR4   = 10000;		//置入要比较的数值

	TA0CTL    = TACLR | TASSEL_2 | MC_1 | TAIE;
	//计数器清零，选择SCLK作为时钟，选用増计数模式，开启中断
#endif
}

void TA1_Init(void)
{
	TA1CCTL0 |= CCIE;       //比较功能0(定时计数)开启CCIFG位中断
    TA1CCR0   = count;      //置入终值
//	TA1CCTL1 |= CCIE;		//比较功能1开启中断
//	TA1CCR1   = 10;		    //置入要比较的数值
//	TA1CCTL2 |= CCIE;		//比较功能2开启中断
//	TA1CCR2   = 100;		//置入要比较的数值
//	TA1CCTL3 |= CCIE;		//比较功能3开启中断
//	TA1CCR3   = 1000;		//置入要比较的数值
//	TA1CCTL4 |= CCIE;		//比较功能4开启中断
//	TA1CCR4   = 10000;		//置入要比较的数值

	TA1CTL    = TACLR | TASSEL_2 | MC_1 | TAIE;
	//计数器清零，选择SCLK作为时钟，选用増计数模式，开启中断
}

void TA2_Init(void)
{
	TA2CCTL0 |= CCIE;       //比较功能0(定时计数)开启CCIFG位中断
    TA2CCR0   = count;      //置入终值
//	TA2CCTL1 |= CCIE;		//比较功能1开启中断
//	TA2CCR1   = 10;		    //置入要比较的数值
//	TA2CCTL2 |= CCIE;		//比较功能2开启中断
//	TA2CCR2   = 100;		//置入要比较的数值
//	TA2CCTL3 |= CCIE;		//比较功能3开启中断
//	TA2CCR3   = 1000;		//置入要比较的数值
//	TA2CCTL4 |= CCIE;		//比较功能4开启中断
//	TA2CCR4   = 10000;		//置入要比较的数值

	TA2CTL    = TACLR | TASSEL_2 | MC_1 | TAIE;
	//计数器清零，选择SCLK作为时钟，选用増计数模式，开启中断
}

void TB0_Init(void)
{
	TB0CCTL0 |= CCIE;       //比较功能0(定时计数)开启CCIFG位中断
    TB0CCR0   = count;      //置入终值
//	TB0CCTL1 |= CCIE;		//比较功能1开启中断
//	TB0CCR1   = 10;		    //置入要比较的数值
//	TB0CCTL2 |= CCIE;		//比较功能2开启中断
//	TB0CCR2   = 100;		//置入要比较的数值
//	TB0CCTL3 |= CCIE;		//比较功能3开启中断
//	TB0CCR3   = 1000;		//置入要比较的数值
//	TB0CCTL4 |= CCIE;		//比较功能4开启中断
//	TB0CCR4   = 10000;		//置入要比较的数值

	TB0CTL    = TBCLR | TBSSEL_2 | MC_1 | TBIE;
	//计数器清零，选择SCLK作为时钟，选用増计数模式，开启中断
}




#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{

	//TA0CCR0 CCIFG0置位, TAIFG置位
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{

	//TA1CCR0 CCIFG0置位, TAIFG置位
}

#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMER2_A0_ISR(void)
{

	//TA2CCR0 CCIFG0置位, TAIFG置位
}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMER0_B0_ISR(void)
{

	//TB0CCR0 CCIFG0置位, TBIFG置位
}




#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{
#if CAP_MODE

	  switch(__even_in_range(TA0IV,14))
	  {
	    case  0: break;                          // No interrupt
	    case  2: //CAP1_deal();
		         break;                          // CCR1
	    case  4: //CAP2_deal();
		         break;                          // CCR2
	    case  6: CAP3_deal();
	    	     break;                          // CCR3
	    case  8: CAP4_deal();
	    	     break;                          // CCR4
	    case 10: break;                          // CCR5
	    case 12: break;                          // CCR6
	    case 14: break;                          // overflow
	    default: break;
	  }

#else

	switch(__even_in_range(TA0IV,14))
	// 这句话的意思是：只有在TA0IV的值是在0--14内的偶数时才会执行switch函数内的语句。
	{
		case 2:
		break;   //TA0CCR1 CCIFG1置位
		case 4:  ;
		break;   //TA0CCR2 CCIFG2置位
		case 6:  ;
		break;   //TA0CCR3 CCIFG3置位
		case 8:  ;
		break;   //TA0CCR4 CCIFG4置位
		case 14:
		break;   //TAIFG置位
		default: break;
	}
#endif
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void)
{
	switch(__even_in_range(TA1IV,14))
	// 这句话的意思是：只有在TA1IV的值是在0--14内的偶数时才会执行switch函数内的语句。
	{
		case 2:
		break;   //TA1CCR1 CCIFG1置位
		case 4:  ;
		break;   //TA1CCR2 CCIFG2置位
		case 6:  ;
		break;   //TA1CCR3 CCIFG3置位
		case 8:  ;
		break;   //TA1CCR4 CCIFG4置位
		case 14:
		break;   //TAIFG置位
		default: break;
	}
}

#pragma vector=TIMER2_A1_VECTOR
__interrupt void TIMER2_A1_ISR(void)
{
	switch(__even_in_range(TA2IV,14))
	// 这句话的意思是：只有在TA2IV的值是在0--14内的偶数时才会执行switch函数内的语句。
	{
		case 2:
		break;   //TA2CCR1 CCIFG1置位
		case 4:  ;
		break;   //TA2CCR2 CCIFG2置位
		case 6:  ;
		break;   //TA2CCR3 CCIFG3置位
		case 8:  ;
		break;   //TA2CCR4 CCIFG4置位
		case 14:
		break;   //TAIFG置位
		default: break;
	}
}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void)
{
	switch(__even_in_range(TB0IV,14))
	// 这句话的意思是：只有在TB0IV的值是在0--14内的偶数时才会执行switch函数内的语句。
	{
		case 2:
		break;   //TB0CCR1 CCIFG1置位
		case 4:  ;
		break;   //TB0CCR2 CCIFG2置位
		case 6:  ;
		break;   //TB0CCR3 CCIFG3置位
		case 8:  ;
		break;   //TB0CCR4 CCIFG4置位
		case 14:
		break;   //TBIFG置位
		default: break;
	}
}

void CAP1_deal()
{
//	TA0CCTL1 &= ~CCIFG;     //读取相应中断硬件自动清零
	if(cap_count == 0) TA0R=0;
	if(cap_count == 1) cap1value=TA0R;
	cap_count ++;
	if(cap_count >= 2) cap_count = 2;
}

void CAP2_deal()
{
//	TA0CCTL2 &= ~CCIFG;     //读取相应中断硬件自动清零
	if(cap_count==1)   cap2value=TA0R;
}

void CAP3_deal()
{
//	TA0CCTL3&=~CCIFG;    //读取相应中断硬件自动清零
	cap_flag++;
	if(cap_flag==1)
	  {
	   TA0CCTL3 |= CM_1;
	   TA0R=0;
	  }
	if(cap_flag==2)
	  {
	   downtime=TA0R;
	   TA0CCTL3 |= CM_2;
	   TA0R=0;
	  }
	if(cap_flag==3)
	  {
	   uptime=TA0R;
	   cap_flag=0;
	   cap_finish=1;
	  }

}

void CAP4_deal()
{
//	TA0CCTL4&=~CCIFG;    //读取相应中断硬件自动清零
	if(cap_flag==1)
	  {
	   addtime=TA0R;
	  }
}


