/*
 * UCS_INIT.c
 *
 *  Created on: 2015年7月7日
 *      Author: yumin
 *
 *系统默认：ACLK使用REFOCLK=32.768KHz,MCLK和SMCLK使用DCOCLKDIV=1.048576MHz
 *本程序    ：ACLK使用X1晶振=32.768KHz,MCLK使用X2晶振=4MHz，SMCLK使用DCOCLKDIV=15.99MHz
 */
#include <msp430F5529.h>

void UCS_init(void)
{
/************************************************测量时钟频率*/

//	P1SEL |= BIT0; //ACLK
//	P1DIR |= BIT0;
//	P2SEL |= BIT2; //SMCLK
//	P2DIR |= BIT2;
//	P7SEL |= BIT7; //MCLK
//	P7DIR |= BIT7;

/*******************************************打开XT1，2外部晶振*/
	P5SEL |= BIT4|BIT5;
	UCSCTL6 |= XCAP_3;
	UCSCTL6 &= ~XT1OFF;//打开XT1，否则XT1LFOFFG可能报错

	P5SEL |= BIT2|BIT3;
	UCSCTL6 &= ~XT2OFF;//打开XT2，否则XT2OFFG可能报错

	__bis_SR_register(SCG0);//该语法为固定格式，意为将括号内的变量置位，SCG0与系统工作模式有关，此时MCLK暂停工作
/***************************************************配置DCO*/
		UCSCTL0 = 0x00;   //先清零，FLL运行时，该寄存器系统会自动配置，不用管
		UCSCTL1 = DCORSEL_6;//调节范围约为 ~ MHZ（设置DCO的频率范围，之后设置的DCO时钟要在这个范围内，否则会出错）
		UCSCTL2 = FLLD_1 | 243;//FLLD=1,FLLN=243,则频率为2*（243+1）*32.768=15.99MHZ
		                       //DCOCLK = D*(N+1)*(REFCLK/n)
		                       //DCOCLKDIV = (N+1)*(REFCLK/n)

	__bic_SR_register(SCG0);
	__delay_cycles(782000);//系统自带的精确延时，单位us

/************************************************等待晶振起振*/
	while (SFRIFG1 & OFIFG)
	{
			UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
			SFRIFG1 &= ~OFIFG;
	}

    UCSCTL4=(UCSCTL4&(~(SELA_7|SELS_7|SELM_7)))|SELA_0|SELS_5|SELM_3;
       //(UCSCTL4&(~(SELA_7|SELS_7|SELM_7)))先把SELA,SELS,SELM清零，然后设置各个时钟的来源
       //ACLK->X1COK(32.768KHz),SMCLK->X2CLK(4MHz),MCLK->DCOCLK(15.99MHZ)
}

