/*
 * DAC8571.c
 *
 *  Created on: 2015-7-8
 *      Author: Administrator
 */
#include <msp430f5529.h>

#define VREF 2.997

#define SCL_H P8OUT |= BIT1 //IIC
#define SDA_H P8OUT |=BIT2 ;  //IIC
#define SCL_L P8OUT &= ~BIT1 ; //IIC
#define SDA_L P8OUT &= ~BIT2 ;  //IIC
#define SDA_DIRIN  P8DIR &= ~BIT2
#define SDA_DIROUT P8DIR |= BIT2
#define SDA_IN  P8IN&=BIT2

#define CPU_F ((double)16000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define Delay_Nms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

#define uint  unsigned int
#define uchar unsigned char

uint i, n;
uchar ack=0;

void DAC8571_Init(void)
{
	P8DIR |=BIT1+BIT2;//P8_2 SDA   P8_1  SCL
}

void IIC_START(void)
{
	SCL_H;					 //SCL
    delay_us( 200);
    SDA_H;
	delay_us( 200);
	SDA_L;					  //SCL
	delay_us( 200);
 }

void IIC_OVER( void )
{
	SCL_L;
 	SDA_H ;
 	delay_us(400);
}

void IIC_STOP(void)
{
	SCL_L;
	SDA_L;
	delay_us( 400);
	SCL_H;
	delay_us( 100);
	SDA_H;
	delay_us( 400);
}

uchar IIC_TR(uint dat )
{
	uchar ack=0;
	SDA_DIROUT;
 	for( i=0; i<8; i++ )
	{
 		n = 7-i;
		SCL_L;
		delay_us( 200);
		if( (( dat & (1 << n) ) >> n) )
		{
			SDA_H;
		}
		else
			SDA_L;
		delay_us( 200);
		SCL_H;
		delay_us( 200);
	}
	SCL_L;
	SDA_DIRIN;
	delay_us( 200);
	ack = SDA_IN;
	delay_us( 200);
	SCL_H;
	delay_us( 200);
	return ack;
 }

uchar DAC_Init(void)
{
	uchar ack=0;
	IIC_START();   //IIC
	ack=IIC_TR( 0x98 );//发送地址
	if( ack != 0 )
	{
		return ack;
	}
	IIC_OVER();
	IIC_TR( 0x10 );//控制寄存器Write temporary register and load DAC with data
	if( ack != 0 )
	{
		return ack;
	}
	IIC_OVER();
	return 0;
}


void DAC8571_OUT( float num )
{
	uchar ack=0,error=0;
	uint dat = 0x98;
	uint dat0, dat1;
	if( (num - VREF) > 0.0 )
	{
		error=1;
	}
	DAC_Init();
	dat = ( uint )( ( num/VREF )*65535 );
	dat1 = ( ( dat & 0xff00 ) >> 8 );
	ack =IIC_TR( dat1 );
	if( ack != 0 )
	{
		error=1;
	}
	IIC_OVER();
	dat0 = ( dat & 0x00ff );
	ack =IIC_TR( dat0 );
	if( ack != 0 )
	{
		error=1;
	}
	IIC_STOP();

	while(error==1);    //判断是否正确输出
}


