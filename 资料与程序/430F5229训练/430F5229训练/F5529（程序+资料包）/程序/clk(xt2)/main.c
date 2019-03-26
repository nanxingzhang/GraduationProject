#include<MSP430F5529.h>
/*XT2配时钟*/
void SetVcoreUp (unsigned int level)
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
void main(void) {

	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	  P1SEL |= BIT0;P1DIR |= BIT0;	//测量ACLK用
	  P2SEL |= BIT2;P2DIR |= BIT2;	//测量SMCLK用
	  P7SEL |= BIT7;P7DIR |= BIT7;	//测量MCLK用
	  P5SEL |= BIT2+BIT3;
	  UCSCTL6 &= ~XT2OFF;          	//打开XT2
	  SetVcoreUp(3);
	  __bis_SR_register(SCG0);
	  UCSCTL0 =0;
	  UCSCTL1 = DCORSEL_7;                    //DCO频率范围在28.2MHZ以下
	  UCSCTL2 = FLLD_0+24;		//D=16，N=1
	  UCSCTL3 = SELREF_5 + FLLREFDIV_2;    //n=8,FLLREFCLK时钟源为XT2CLK；
	  UCSCTL4=SELM_3+SELS_4+SELA_2;
	  __bic_SR_register(SCG0);
	  __delay_cycles(8192);
	  do
	  {
	  	UCSCTL7 &=~(XT2OFFG+DCOFFG+XT1LFOFFG);//清除3种时钟错误标志
	  	SFRIFG1&=~(OFIFG);//清除时钟错误标志位
	  }while(SFRIFG1 & OFIFG);	//如果有时钟错误
}
