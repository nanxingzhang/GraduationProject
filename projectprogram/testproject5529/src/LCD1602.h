#ifndef __LCD1602_H__
#define __LCD1602_H__

void delay_nns(unsigned char m);
void Delay_Ms(unsigned int n);
void Write1602_Com(unsigned char commd);
void Write1602_Data(unsigned char dat);
void Check_Busy();
void LCD1602_Init(void);
void LCD_SET_CURSOR(unsigned char line,unsigned char column);
void Print(char *str,unsigned char n);

extern char lcd_buff0[16];
extern char lcd_buff1[16];

#endif
