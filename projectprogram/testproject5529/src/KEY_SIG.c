#include "MSP430F5529.h"

void KEY_IODect(void);
void P11_Onclick(void);
void P21_Onclick(void);
void WDT_init(void);
/*------------------------------------------------------调节PWM占空比使用*/
extern unsigned int one_Percent;
extern unsigned int ten_Percent;
extern unsigned int max_Percent;
extern unsigned int min_Percent;
/*-----------------------------------------------------------------*/

void KEY_SIG_init(void)
{
	P1DIR |=  BIT0;				        //设定P1.0为输出
	P1OUT |=  BIT0;						//设定P1.0初值，测试使用

	P4DIR |=  BIT7;						//设定P4.7为输出
	P4OUT &=~ BIT7;						//设定P4.7初值，测试使用

	//-----配合机械按键，启用内部上拉电阻-----
	P1DIR &=~ BIT1;				        //设定P1.1为输出
	P1REN |=  BIT1;				        //启用P1.1内部上下拉电阻
	P1OUT |=  BIT1;			            //将电阻设置为上拉

	P2DIR &=~ BIT1;				        //设定P2.1为输出
	P2REN |=  BIT1;				        //启用P2.1内部上下拉电阻
	P2OUT |=  BIT1;			            //将电阻设置为上拉

	WDT_init();
}

/******************************************************************************************************
 * 名       称：WDT_init()
 * 功       能：设定WDT定时中断为16ms，开启WDT定时中断使能
 * 入口参数：无
 * 出口参数：无
 * 说       明：WDT定时中断的时钟源选择ACLK，
 * 范       例：无
 ******************************************************************************************************/
void WDT_init(void)
{
	//-----设定WDT为16ms中断-----
   WDTCTL  = WDT_ADLY_16;
	//-----WDT中断使能-----
   SFRIE1 |= WDTIE;
}

/******************************************************************************************************
 * 名       称：WDT_ISR()
 * 功       能：响应WDT定时中断服务
 * 入口参数：无
 * 出口参数：无
 * 说       明：WDT定时中断独占中断向量，所以无需进一步判断中断事件，也无需人工清除标志位。
 *                  所以，在WDT定时中断服务子函数中，直接调用WDT事件处理函数就可以了。
 * 范       例：无
 ******************************************************************************************************/
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	//-----启用Port1事件检测函数-----
	KEY_IODect();		//检测通过，则会调用事件处理函数
}

/******************************************************************************************************
 * 名       称：P1_IODect()
 * 功       能：判断是否有键被按下，哪个键被按下，并调用相应IO的中断事件处理函数
 * 入口参数：无
 * 出口参数：无
 * 说       明：必须用最近两次扫描的结果，才知道按键是否被按下
 * 范       例：无
 ******************************************************************************************************/
void KEY_IODect(void)
{
	static unsigned char KEY11_Now=0, KEY21_Now=0;	//变量值出函数时需保留
	unsigned char        KEY11_Past=0,KEY21_Past=0;

	KEY11_Past=KEY11_Now;
	KEY21_Past=KEY21_Now;

	//-----查询IO的输入寄存器-----
	if((P1IN&BIT1)!=0) 	KEY11_Now=1;
	    else 			KEY11_Now=0;

	if((P2IN&BIT1)!=0) 	KEY21_Now=1;
		else 		    KEY21_Now=0;

	//-----前一次高电平、后一次低电平，说明按键按下-----
	if((KEY11_Past==1)&&(KEY11_Now==0)) P11_Onclick();
	if((KEY21_Past==1)&&(KEY21_Now==0)) P21_Onclick();
}


/******************************************************************************************************
 * 名       称：Px.x_Onclick()
 * 功       能：Px.x的中断事件处理函数，即当Px.x键被按下后，下一步干什么
 * 入口参数：无
 * 出口参数：无
 * 说       明：使用事件处理函数的形式，可以增强代码的移植性和可读性
 * 范       例：无
 ******************************************************************************************************/
void P11_Onclick(void)					//P1.1的事件处理函数
{
	P1OUT ^= BIT0;					//测试使用
	P4OUT ^= BIT7;					//测试使用

//	TA1CCR1 += ten_Percent;         //调节PWM占空比
//	if(TA1CCR1>=max_Percent) TA1CCR1=min_Percent;
//
//	TB0CCR2 += ten_Percent;			//调节PWM占空比
//	if(TB0CCR2>=max_Percent) TB0CCR2=min_Percent;
}

void P21_Onclick()					//P2.1的事件处理函数
{
	P1OUT ^= BIT0;					//测试使用
	P4OUT ^= BIT7;					//测试使用

//	TA1CCR1 -= ten_Percent;			//调节PWM占空比
//	if(TA1CCR1<=min_Percent) TA1CCR1=max_Percent;
//
//	TB0CCR2 -= ten_Percent;			//调节PWM占空比
//	if(TB0CCR2<=min_Percent) TB0CCR2=max_Percent;
}
