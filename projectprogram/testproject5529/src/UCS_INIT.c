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

/*void SetVcoreUp (unsigned int level)
{
  // Open PMM registers for write
  PMMCTL0_H = PMMPW_H;
  // Set SVS/SVM high side new level
  SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
  // Set SVM low side to new level
  SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
  // Wait till SVM is settled
  while ((PMMIFG & SVSMLDLYIFG) == 0);
  // Clear already set flags
  PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
  // Set VCore to new level
  PMMCTL0_L = PMMCOREV0 * level;
  // Wait till new level reached
  if ((PMMIFG & SVMLIFG))
    while ((PMMIFG & SVMLVLRIFG) == 0);
  // Set SVS/SVM low side to new level
  SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
  // Lock PMM registers for write access
  PMMCTL0_H = 0x00;
}
void UCS_init(void) {

	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	  P1SEL |= BIT0;P1DIR |= BIT0;	//����ACLK��
	  P2SEL |= BIT2;P2DIR |= BIT2;	//����SMCLK��
	  P7SEL |= BIT7;P7DIR |= BIT7;	//����MCLK��
	  P5SEL |= BIT2+BIT3;
	  UCSCTL6 &= ~XT2OFF;          	//��XT2
	  SetVcoreUp(3);
	  __bis_SR_register(SCG0);
	  UCSCTL0 =0;
	  UCSCTL1 = DCORSEL_7;                    //DCOƵ�ʷ�Χ��28.2MHZ����
	  UCSCTL2 = FLLD_0+24;		//D=16��N=1
	  UCSCTL3 = SELREF_5 + FLLREFDIV_2;    //n=8,FLLREFCLKʱ��ԴΪXT2CLK��
	  UCSCTL4=SELM_3+SELS_4+SELA_2;
	  __bic_SR_register(SCG0);
	  __delay_cycles(8192);
	  do
	  {
	  	UCSCTL7 &=~(XT2OFFG+DCOFFG+XT1LFOFFG);//���3��ʱ�Ӵ����־
	  	SFRIFG1&=~(OFIFG);//���ʱ�Ӵ����־λ
	  }while(SFRIFG1 & OFIFG);	//�����ʱ�Ӵ���
}*/



