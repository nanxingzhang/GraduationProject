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
#define FreqHz 200                                 //����(Hz)
#define Duty   60								   //ռ�ձ�(%)

#define Period SMCLK/FreqHz                        //һ��ģʽ������       ת���ɼ���ֵ
#define Bright Period*Duty/100                     //һ��ģʽ��ռ�ձ�   ת���ɼ���ֵ

#define DeadPeriod SMCLK/FreqHz/2                  //����ģʽ������       ת���ɼ���ֵ
#define DeadBright DeadPeriod*Duty/100             //����ģʽ��ռ�ձ�   ת���ɼ���ֵ

unsigned int one_Percent = Period/100;             //ռ�ձ�1%����        ת���ɼ���ֵ
unsigned int ten_Percent = Period/10;              //ռ�ձ�10%����     ת���ɼ���ֵ
unsigned int max_Percent = Period;             	   //ռ�ձ����ֵ           ת���ɼ���ֵ
unsigned int min_Percent = 0;					   //ռ�ձ���Сֵ           ת���ɼ���ֵ

/*---------------------------------------------------------------------*/
float ADC_Value=0;					  //ADC����ֵ
/*-----------------------------------------------------Ƶ�ʣ�ռ�ձȣ���λ�������*/
extern unsigned int cap_count,cap1value,cap2value;
extern unsigned int cap_flag,cap_finish,uptime,downtime,addtime;
float freq=0,phase=0,duty=0;
/*--------------------------------------------------------------------*/

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;			//Stop watchdog timer
    UCS_init();                 		//ʱ�ӳ�ʼ��							ok
	KEY_SIG_init();             		//��������,LED��ʼ��(P2.1,P1.1,P1.0,P4.7) ok
//	Lcd12864_Init();						//LCD12864���г�ʼ��(P6.6,P6.5,P6.4,P3；P6.6,P6.5,P6.4)	ok
//	LCD1602_Init();                     //LCD1602���г�ʼ��(P6.6,P6.5,P6.4,P3)	 ok
//	DAC8571_Init();                     //DAC8571��ʼ��(P8.1,P8.2) 				  ok
//	ADC12_init();              			//Ƭ��ADC��ʼ��							 ok
//	ADS1118_Init();                     //ADS1118��ʼ��(P4.0,P4.1,P4.2,P4.3)	       ok
//	TA0_Init();							//��ʱ��A0��ʼ��							ok
//	TA1_Init();							//��ʱ��A1��ʼ��							ok
//	TA2_Init();							//��ʱ��A2��ʼ��							ok
//	TB0_Init();							//��ʱ��B0��ʼ��							ok


/*-------------------------------------------------------------------PWM������*/

//	TA1_PWM_Init('S',1,'B');       					//TA1.1PWM��ʼ�� -->P2.0   ok
//	TA1_PWM_SetPeriod(Period);
//	TA1_PWM_SetPermill(Bright);						//�ͺ�PWM

//	TB0_PWM_Init('S',1,'F');	   					//TB0.2PWM��ʼ�� -->P7.4   ok
//	TB0_PWM_SetPeriod(Period);
//	TB0_PWM_SetPermill(Bright);						//��ǰPWM

//	TA0_PWM_Init('S',1,'D','D');  					//TA0.1PWM��ʼ�� -->P1.2   ok
//	TA0_PWM_SetPeriod(DeadPeriod);					//TA0.2PWM��ʼ�� -->P1.3
//	TA0_PWM_SetPermill(1,DeadBright);               //����������

//	TA2_PWM_Init('S',1,'F','B');  					//TA2.1PWM��ʼ�� -->P2.4   ok
//	TA2_PWM_SetPeriod(Period);    					//TA2.2PWM��ʼ�� -->P2.5
//	TA2_PWM_SetPermill(1,Bright);                   //��ǰPWM
//	TA2_PWM_SetPermill(2,Bright);					//�ͺ�PWM

    _enable_interrupts();		//ʹ�����ж�

	while(1)
	{
/*-----------------------------------------------------Ƶ�ʣ�ռ�ձȣ���λ���㷽��һ*/
//	cap_count=0;
//	while(cap_count<2);							//�ȴ��ڶ��β���
//	freq  = SMCLK/1.0/cap1value;				//����Ƶ��
//	phase = 360.0*cap2value/cap1value;			//������λ
/*-----------------------------------------------------Ƶ�ʣ�ռ�ձȣ���λ���㷽����*/
//	cap_finish=0;
//	while(!cap_finish);                 		//�ȴ����в������
//	duty  = uptime*100.0;
//	duty  = duty/(uptime+downtime);				//ռ�ձ�
//	freq  = SMCLK/1.0/(uptime+downtime);		//Ƶ��
//	phase = 360.0*addtime/(uptime+downtime);	//��λ��


/*-----------------------------------------------------------ADC&DAC���*/
//	DAC8571_OUT(1.11);                          //����DAC8571
//	ADC_Value = ADS1118(4,1);                   //����ADS1118
//	sprintf(LCD_BUF_1,"%.3f",ADC_Value);        //��ʾADC

/*--------------------------------------------------------LCD12864��ʾ���*/
//	lcd12864_disp_str(1, 1, tab_SPI1);
//	lcd12864_disp_str(1, 2, tab_SPI2);
//	lcd12864_disp_str(1, 3, tab_SPI3);
//	lcd12864_disp_str(1, 4, tab_SPI4);

/*---------------------------------------------------------LCD1602��ʾ���*/
//	LCD_SET_CURSOR(1,1);
//	Print(lcd_buff0,16);
//
//	LCD_SET_CURSOR(2,1);
//	Print(lcd_buff0,16);

/*-----------------------------------------------------Lcd12864spi��ʾ���*/
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

