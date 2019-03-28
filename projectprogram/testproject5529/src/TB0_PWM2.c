/*
 * TB_PWM.c
 *
 *  Created on: 2015��11��20��
 *      Author: yumin
 */
#include "msp430f5529.h"

#define TB02_SET 	P7SEL |= BIT4; P7DIR |= BIT4		//P7.4
#define TB02_OFF 	P7SEL &= ~BIT4						//P7.4
/*************TB0*******************/

/*****************************************************************************************
* ��       �ƣ�    TB0_PWM_Init()
* ��       �ܣ�    TB0��ʱ����ΪPWM�������ĳ�ʼ�����ú���
* ��ڲ�����   Clk:ʱ��Դ 'S'=SMCLK;   'A'=ACLK ;   'E'=TACLK(�ⲿ����)�� 'e'= TACLK(TACLKȡ��)
         Div:ʱ�ӷ�Ƶϵ��: 1/2/4/8
		 Mode1:ͨ��1�����ģʽ 'F'��Ϊ��ǰPWM��ģʽ7����'B'�ͺ�PWM��ģʽ3��
* ���ڲ�����   1��ʾ���óɹ���0��ʾ������������ʧ�ܡ�
* ˵       �� : �ڵ���PWM��غ���֮ǰ����Ҫ���øú�������TA��ģʽ��ʱ��Դ��
* ��       �� : TB0_PWM_Init('A',1,'B')TAʱ����ΪACLK,ͨ��1�ͺ�PWM���
         TB0_PWM_Init('S',1,'F')TAʱ����ΪSMCLK,ͨ��1��ǰPWM���
 ****************************************************************************************/
char TB0_PWM_Init(char Clk,char Div,char Mode1)
{
  TB0CTL =0;												// �����ǰ����

  switch(Mode1)												//Ϊ��ʱ��ѡ�����ģʽ
  {
  case 'F': case 'f':										//��ͨPWM
	  TB0CTL |=MC_1; break;									//����ʱ��Ϊ������
  case 'B':case 'b':
	  TB0CTL |=MC_1; break;									//����ʱ��Ϊ������
  default : return(0);										//��������������ò������󣬷���0
  }

  switch(Clk)  												//Ϊ��ʱ��TAѡ��ʱ��Դ
  {
    case 'A': case 'a':  	TB0CTL|=TASSEL_1; break;   		//ACLK
    case 'S': case 's': 	TB0CTL|=TASSEL_2; break;  		//SMCLK
    case 'E':            	TB0CTL|=TASSEL_0; break;  		//�ⲿ����(TACLK)
    case 'e':          		TB0CTL|=TASSEL_3; break;   		//�ⲿ����(TACLKȡ��)
    default :  return(0);  									//���ò������󣬷���0
  }
  switch(Div) 												//Ϊ��ʱ��TAѡ���Ƶϵ��
  {
    case 1:   TB0CTL|=ID_0; break;   						//1
    case 2:   TB0CTL|=ID_1; break;   						//2
    case 4:   TB0CTL|=ID_2; break;  						//4
    case 8:   TB0CTL|=ID_3; break;                          //8
    default :  return(0);  									//���ò������󣬷���0
  }
  switch(Mode1)										 		//����PWMͨ��1�����ģʽ��
  {
     case 'F':	case 'f':
              TB0CCTL2 =OUTMOD_7;
              TB02_SET;
              break;
     case 'B':	case 'b':
              TB0CCTL2 =OUTMOD_3;
              TB02_SET;
              break;
     default :  return(0); 							        //���ò������󣬷���0
  }
  return(1);
}
/*****************************************************************************************
* ��       �ƣ�TB0_PWM_SetPeriod()
* ��       �ܣ�����PWM������������
* ��ڲ�����Period:����(0~65535) ʱ�Ӹ���
* ���ڲ�����1�����óɹ�     0������ʧ��
* ˵       �� :
* ��       �� : TB0_PWM_SetPeriod(500)����PWM��������Ϊ500��ʱ������
 ****************************************************************************************/
char TB0_PWM_SetPeriod(unsigned int Period)
{
	if (Period>65535)	return(0);
	 TB0CCR0 = Period;
	return(1);
}

/*****************************************************************************************
* ��    �ƣ�TB0_PWM_SetPermill()
* ��    �ܣ�����PWM�����ռ�ձ�(һ��ʱ�Ӹ���)
* ��ڲ�����Duty: PWM�ߵ�ƽ��Чʱ��(0~65535)
* ���ڲ�����1���óɹ���0����ʧ��
* ˵    ��: PWM�ߵ�ƽ��Чʱ��ΪDuty��ʱ������
* ��    ��: TB0_PWM_SetPermill(50)����PWM�����ߵ�ƽ��Чʱ��Ϊ50��ʱ������
 ****************************************************************************************/
char TB0_PWM_SetPermill(unsigned int Duty)
{
	unsigned char Mod;
	Mod = (TB0CCTL2 & 0x00e0)>>5; //��ȡ���ģʽ��OUTMOD0λ��5-7λ
	switch(Mod)			          //����ģʽ�趨TACCRx
		{
		case 7: TB0CCR2=Duty;          break;
		case 3: TB0CCR2=TB0CCR0-Duty;  break;
		default: return(0);
		}
	return (1);
}

