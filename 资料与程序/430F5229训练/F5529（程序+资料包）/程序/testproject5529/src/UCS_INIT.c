/*
 * UCS_INIT.c
 *
 *  Created on: 2015��7��7��
 *      Author: yumin
 *
 *ϵͳĬ�ϣ�ACLKʹ��REFOCLK=32.768KHz,MCLK��SMCLKʹ��DCOCLKDIV=1.048576MHz
 *������    ��ACLKʹ��X1����=32.768KHz,MCLKʹ��X2����=4MHz��SMCLKʹ��DCOCLKDIV=15.99MHz
 */
#include <msp430F5529.h>

void UCS_init(void)
{
/************************************************����ʱ��Ƶ��*/

//	P1SEL |= BIT0; //ACLK
//	P1DIR |= BIT0;
//	P2SEL |= BIT2; //SMCLK
//	P2DIR |= BIT2;
//	P7SEL |= BIT7; //MCLK
//	P7DIR |= BIT7;

/*******************************************��XT1��2�ⲿ����*/
	P5SEL |= BIT4|BIT5;
	UCSCTL6 |= XCAP_3;
	UCSCTL6 &= ~XT1OFF;//��XT1������XT1LFOFFG���ܱ���

	P5SEL |= BIT2|BIT3;
	UCSCTL6 &= ~XT2OFF;//��XT2������XT2OFFG���ܱ���

	__bis_SR_register(SCG0);//���﷨Ϊ�̶���ʽ����Ϊ�������ڵı�����λ��SCG0��ϵͳ����ģʽ�йأ���ʱMCLK��ͣ����
/***************************************************����DCO*/
		UCSCTL0 = 0x00;   //�����㣬FLL����ʱ���üĴ���ϵͳ���Զ����ã����ù�
		UCSCTL1 = DCORSEL_6;//���ڷ�ΧԼΪ ~ MHZ������DCO��Ƶ�ʷ�Χ��֮�����õ�DCOʱ��Ҫ�������Χ�ڣ���������
		UCSCTL2 = FLLD_1 | 243;//FLLD=1,FLLN=243,��Ƶ��Ϊ2*��243+1��*32.768=15.99MHZ
		                       //DCOCLK = D*(N+1)*(REFCLK/n)
		                       //DCOCLKDIV = (N+1)*(REFCLK/n)

	__bic_SR_register(SCG0);
	__delay_cycles(782000);//ϵͳ�Դ��ľ�ȷ��ʱ����λus

/************************************************�ȴ���������*/
	while (SFRIFG1 & OFIFG)
	{
			UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
			SFRIFG1 &= ~OFIFG;
	}

    UCSCTL4=(UCSCTL4&(~(SELA_7|SELS_7|SELM_7)))|SELA_0|SELS_5|SELM_3;
       //(UCSCTL4&(~(SELA_7|SELS_7|SELM_7)))�Ȱ�SELA,SELS,SELM���㣬Ȼ�����ø���ʱ�ӵ���Դ
       //ACLK->X1COK(32.768KHz),SMCLK->X2CLK(4MHz),MCLK->DCOCLK(15.99MHZ)
}

