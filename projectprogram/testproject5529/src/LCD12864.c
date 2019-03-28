/*
 * LCD12864.c
 *
 *  Created on: 2015-6-23
 *      Author: Administrator
 */

#include <msp430f5529.h>
#include <math.h>
#include <stdio.h>
/*注意！*/
#define P_six
//#define P_eight

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

#define CPU_F ((double)16000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define Delay_Nms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

char tab_SPI1[16];
char tab_SPI2[16];
char tab_SPI3[16];
char tab_SPI4[16];





/*12864基础应用指令*/
#define CLEAR_SCREEN        0x01                    //清屏指令：清屏且AC值为00H
#define AC_INIT                0x02                    //将AC设置为00H。且游标移到原点位置
#define CURSE_ADD        0x06                    //设定游标移到方向及图像整体移动方向（默认游标右移，图像整体不动）
#define FUN_MODE        0x30                    //工作模式：8位基本指令集
#define DISPLAY_ON        0x0c                    //显示开,显示游标，且游标位置反白
#define DISPLAY_OFF        0x08                    //显示关
#define CURSE_DIR        0x14                    //游标向右移动:AC=AC+1
#define SET_CG_AC        0x40                    //设置AC，范围为：00H~3FH
#define SET_DD_AC        0x80
/*12864扩展应用指令*/
#define SP_MODE      0x34	// 8位数据，基本指令操作
#define GRAPON    0x36	// 扩充指令，图形显示开
#define	gdbas     0x80
//*******************************************************************
//     12864 画图、打点
//

#define LCD_DataIn    P3DIR=0x00    //数据口方向设置为输入
#define LCD_DataOut   P3DIR=0xff    //数据口方向设置为输出
#define LCD2MCU_Data  P3IN
#define MCU2LCD_Data  P3OUT

#ifdef P_eight
#define LCD_CMDOut    P8DIR |= (BIT1+BIT2);P7DIR |=BIT0     //P3口的低三位设置为输出
#define LCD_RS_H      P8OUT|=BIT1      //8.1高
#define LCD_RS_L      P8OUT&=~BIT1     //P8.1低
#define LCD_RW_H      P8OUT|=BIT2      //P8.2高
#define LCD_RW_L      P8OUT&=~BIT2     //P8.2低
#define LCD_EN_H      P7OUT|=BIT0      //7.0高
#define LCD_EN_L      P7OUT&=~BIT0     //P7.0
#endif

#ifdef P_six
#define LCD_CMDOut    P6DIR|=0x70      //P6口 0111 0000三位设置为输出
#define LCD_RS_H      P6OUT|=BIT6      //P6.6高
#define LCD_RS_L      P6OUT&=~BIT6     //P6.6低
#define LCD_RW_H      P6OUT|=BIT5      //P6.5高
#define LCD_RW_L      P6OUT&=~BIT5     //P6.5低
#define LCD_EN_H      P6OUT|=BIT4      //P6.4高
#define LCD_EN_L      P6OUT&=~BIT4     //P6.4低
#endif


/*******************************************
函数名称：Write_Cmd
功    能：向液晶中写控制命令
参    数：cmd--控制命令
返回值  ：无
********************************************/
void Write_Cmd(uchar cmd)
{
    uchar lcdtemp = 0;

    LCD_RS_L;
    LCD_RW_H;
    LCD_DataIn;
    do                       //判忙
    {
        LCD_EN_H;
//       	_NOP();
       	lcdtemp = LCD2MCU_Data;
       	LCD_EN_L;

    }
    while(lcdtemp & 0x80);

    LCD_DataOut;
    LCD_RW_L;
    MCU2LCD_Data = cmd;
    LCD_EN_H;
//    __delay_cycles(8);
    LCD_EN_L;
}
/*******************************************
函数名称：Write_Data
功    能：向液晶中写显示数据
参    数：dat--显示数据
返回值  ：无
********************************************/
void  Write_Data(uchar dat)
{
    uchar lcdtemp = 0;

    LCD_RS_L;
    LCD_RW_H;
    LCD_DataIn;
    do                       //判忙
    {
        LCD_EN_H;
//        _NOP();
        lcdtemp = LCD2MCU_Data;
        LCD_EN_L;
    }
    while(lcdtemp & 0x80);

    LCD_DataOut;
    LCD_RS_H;
    LCD_RW_L;

    MCU2LCD_Data = dat;
    LCD_EN_H;
//    __delay_cycles(8);
    LCD_EN_L;
}
/*******************************************
//        读数据
********************************************/
uchar read_data()
{
    uint readvalue;
    uchar lcdtemp = 0;
    LCD_DataOut;
    MCU2LCD_Data |=0xff;
    LCD_RS_L;
        LCD_RW_H;
        LCD_DataIn;
        do                       //判忙
        {
            LCD_EN_H;
//            _NOP();
            lcdtemp = LCD2MCU_Data;
            LCD_EN_L;
        }
        while(lcdtemp & 0x80);

    LCD_RS_H;
    LCD_RW_H;
    LCD_DataIn;
    LCD_EN_L;

    LCD_EN_H;
    readvalue=LCD2MCU_Data;
//    Delay_Nms(1);
    LCD_EN_L;
    return readvalue;

}
/********************************************************/
//名    称：LCD_SetXY()**************************
//功    能：定位函数,设置DDRAM的显示坐标***********************
//入口参数：列/x取值范围(byte)：1～8,行/y取值范围(byte)**************
 /*************************************/
void LCD_SetXY(uchar X, uchar Y)
{
   switch(Y) {
		case 1: Write_Cmd(0x7F + X);break;
		case 2: Write_Cmd(0x8F + X);break;
		case 3: Write_Cmd(0x87 + X);break;
		case 4: Write_Cmd(0x97 + X);break;
                default:break;
	    }
}
//*******************************************************
//* 名    称：disp_char()
//* 功    能：在指定的位置显示某个字符
//* 入口参数：列/x取值范围(byte)：1～8,行/y取值范围(byte)
//* 返回参数：void
/********************************/
void disp_char(uchar X, uchar Y, uchar wdata)
{
    LCD_SetXY(X, Y);
    Write_Data(wdata);
}

//***************************************************************
//* 函数功能：在指定的位置显示字符串
//* 名    称：lcd12864_disp_str()
//* 功    能：在屏幕上显示一个字符串
//* 入口参数：列/x取值范围(byte)：1～8,行/y取值范围(byte)：1～4,Str---字符串的首地址
//* 返回参数：void
/******************************************************************/
void lcd12864_disp_str(uchar X, uchar Y, char*Str)
{
    uchar temp;
    LCD_SetXY(X, Y);
    temp = *Str;
    while(temp != 0)
    {
        Write_Data(temp);
        temp = *(++Str);
    }
}

//********************************************************
//* 名    称：GUI_Point()
//* 功    能：在液晶屏上指定坐标处打一个点，或者清除这个点
//* 入口参数：y--行数(0~63)，x--列数(0~127), color=1该点填充,color=0，该点清除
//* 返回参数：void
//********************************************************
void GUI_Point(unsigned char x,unsigned char y,unsigned char color)
{
  unsigned char x_Dyte,x_byte; //定义列地址的字节位，及在字节中的哪1 位
  unsigned char y_Dyte,y_byte; //定义为上下两个屏(取值为0，1)，行地址(取值为0~31)
  unsigned char GDRAM_hbit,GDRAM_lbit;

  Write_Cmd(0x36); //扩展指令命令
/***X,Y 坐标互换，即普通的X,Y 坐标***/
  x_Dyte=x/16; //计算在16 个字节中的哪一个
  x_byte=x&0x0f; //计算在该字节中的哪一位
  y_Dyte=y/32; //0 为上半屏，1 为下半屏
  y_byte=y&0x1f; //计算在0~31 当中的哪一行
  Write_Cmd(0x80+y_byte); //设定行地址(y 坐标),即是垂直地址
  Write_Cmd(0x80+x_Dyte+8*y_Dyte); //设定列地址(x 坐标)，并通过8*y_Dyte 选定上下屏，即是水平地址
  read_data(); //预读取数据
  GDRAM_hbit=read_data(); //读取当前显示高8 位数据
  GDRAM_lbit=read_data(); //读取当前显示低8 位数据
//  Delay_Nms(1);
  Write_Cmd(0x80+y_byte); //设定行地址(y 坐标)
  Write_Cmd(0x80+x_Dyte+8*y_Dyte); //设定列地址(x 坐标)，并通过8*y_Dyte 选定上下屏
//  Delay_Nms(1);
 if(x_byte<8) //判断其在高8 位，还是在低8 位
 {
   if(color==1)
   {
   Write_Data(GDRAM_hbit|(0x01<<(7-x_byte))); //置位GDRAM 区高8 位数据中相应的点
   }
   else
    Write_Data(GDRAM_hbit&(~(0x01<<(7-x_byte)))); //清除GDRAM 区高8 位数据中相应的点

   Write_Data(GDRAM_lbit); //显示GDRAM 区低8 位数据
 }
 else
  {
  Write_Data(GDRAM_hbit);         //写高8位数据
  if(color==1)
   Write_Data(GDRAM_lbit|(0x01<<(15-x_byte))); //置位GDRAM 区高8 位数据中相应的点
  else
   Write_Data(GDRAM_lbit&(~(0x01<<(15-x_byte))));//清除GDRAM区高8位数据中相应的点
  }
  Write_Cmd(0x30); //恢复到基本指令集
}
//********************************************************
//* 名    称：GUI_Fill_GDRAM()
//* 功    能：将GDRAM中填充数据lcd_data
//* 入口参数：：dat 为填充的数据,取值为0或1
//* 返回参数：void
//********************************************************
void GUI_Fill_GDRAM(unsigned char dat)
{
 uchar i,j,k;

 uchar bGDRAMAddrX = 0x80; //GDRAM 水平地址
 uchar bGDRAMAddrY = 0x80; //GDRAM 垂直地址
 for(i=0;i<2;i++)
 {
 for(j=0;j<32;j++)
  {
  for(k=0;k<8;k++)
   {
    Write_Cmd(0x34); //设置为8 位MPU 接口，扩充指令集,绘图模式关
    Write_Cmd(bGDRAMAddrY+j); //垂直地址Y
    Write_Cmd(bGDRAMAddrX+k); //水平地址X
    Write_Data(dat*0xff);
    Write_Data(dat*0xff);
     }
   }
  bGDRAMAddrX = 0x88;
 }
  Write_Cmd(0x36); //打开绘图模式
  Write_Cmd(0x30); //恢复基本指令集，关闭绘图模式
}
//********************************************************************************
//* 名    称：clrgdram()
//* 功    能：将GDRAM中的数据全部置为0
//* 入口参数：
//* 返回参数：void
//********************************************************************************
void clrgdram()
{
	GUI_Fill_GDRAM(0);
}
//********************************************************************************
//* 名    称：clrddram()
//* 功    能：清屏
//* 入口参数：
//* 返回参数：void
//********************************************************************************
void clrddram()
{
	 Write_Cmd(0x01);
//	 Write_Cmd(0x34);
//	 Write_Cmd(0x30);
}
//++++
//********************************************************
//
/*********************************************************/
/******************画水平线*********************/
void LCD_Draw_Line_x( uchar X0, uchar X1, uchar Y, uchar Color )
{
    uchar Temp ;
    if( X0 > X1 )
    {
        Temp = X1 ;
        X1 = X0 ;
        X0 = Temp ;
    }
    for( ; X0 <= X1 ; X0++ )
    GUI_Point( X0, Y, Color );
}
//*************画垂直线  第x列  从第y0行画到第y1行  颜色 color **************************/
void LCD_Draw_Line_Y( uchar X, uchar Y0, uchar Y1, uchar Color )
{
    uchar Temp ;
    if( Y0 > Y1 )
    {
        Temp = Y1 ;
        Y1 = Y0 ;
        Y0 = Temp ;
    }
    for(; Y0 <= Y1 ; Y0++)
    GUI_Point( X, Y0, Color);
}
//**************画斜线(x,y)到(end x,end y)***********************/
void LCD_Draw_Line( uchar StartX, uchar StartY, uchar EndX, uchar EndY, uchar Color )
{
    int distance;      /*根据屏幕大小改变变量类型(如改为int型)*/
    int delta_x, delta_y ;
    int incx, incy ;
do{
    delta_x = EndX - StartX ;
    delta_y = EndY - StartY ;
    if( delta_x > 0 )
    {
        incx = 1;
    }
    else if( delta_x == 0 )
    {
       incx = 0;
    }
    else
    {
        incx = -1 ;
    }
    if( delta_y > 0 )
    {
        incy = 1 ;
    }
    else if(delta_y == 0 )
    {
       incy = 0 ;
    }
    else
    {
        incy = -1 ;
    }
    delta_x = incx * delta_x ;
    delta_y = incy * delta_y ;

    if( delta_x > delta_y )
   {
     distance = delta_x ;
     StartX+=incx;
     StartY+=incy;
   }
   else
   {
     distance = delta_y;
     StartX+=incx;
     StartY+=incy;
   }
   GUI_Point( StartX, StartY, Color );
}while(distance!=0);
}
/*******************************************
//  sin函数
********************************************/
void fsin2()
{
 	float x,y;
 	uchar x1,y1;
 	for(x=0;x<(4*3.14159);x+=0.1)
  	{
   	y=1*sin(3*x);
   	x1=10*x;
   	y1=31-(10*y+0.5);			  //对y值进行四舍五入
   	GUI_Point(x1,y1,1);
  	}
}
/*******************************************
函数名称：Ini_Lcd
功    能：初始化液晶模块
参    数：无
返回值  ：无
********************************************/
void Lcd12864_Init(void)
{
    LCD_CMDOut;    //液晶控制端口设置为输出
    Write_Cmd(0x30);   //基本指令集
    Write_Cmd(0x02);   // 地址归位
	Write_Cmd(0x0c);   //整体显示打开,游标关闭
	Write_Cmd(0x01);   //清除显示
	Write_Cmd(0x06);   //游标右移
	Write_Cmd(0x80);   //设定显示的起始地址
	Write_Cmd(0x01);	//清屏
	GUI_Fill_GDRAM(0);//* 功    能：将GDRAM中的数据全部置为0
}
/****************************************
//        画圆
*****************************************/
/*void GUI_Circle(uchar x0,uchar y0,uchar r,uchar color)
{
  char a,b;
  char di;
  if(r>31 ||r==0) return; //参数过滤，次液晶显示的最大圆半径为31
  a=0;
  b=r;
  di=3-2*r; //判断下个点位置的标志
  while(a<=b)
  {
   GUI_Point(x0-b,y0-a,color); //3
   GUI_Point(x0+b,y0-a,color); //0
   GUI_Point(x0-a,y0+b,color); //1
   GUI_Point(x0-b,y0-a,color); //7
   GUI_Point(x0-a,y0-b,color); //2
   GUI_Point(x0+b,y0+a,color); //4
   GUI_Point(x0+a,y0-b,color); //5
   GUI_Point(x0+a,y0+b,color); //6
   GUI_Point(x0-b,y0+a,color);
   a++;
   if(di<0) di+=4*a+6;
   else
   {
    di +=10+4*(a-b);
    b--;
   }
  GUI_Point(x0+a,y0+b,color);
  }
}
*/

void Picture_shows(unsigned char *picture) {
	uchar i,j,k;

	 uchar AddrX = 0x80; //GDRAM 水平地址
	 uchar AddrY = 0x80; //GDRAM 垂直地址
	 for(i=0;i<2;i++)
	 {
	 for(j=0;j<32;j++)
	  {
	  for(k=0;k<8;k++)
	   {
	    Write_Cmd(0x34); //设置为8 位MPU 接口，扩充指令集,绘图模式关
	    Write_Cmd(AddrY+j); //垂直地址Y
	    Write_Cmd(AddrX+k); //水平地址X
	    Write_Data(picture[16*j+k*2]);
	    Write_Data(picture[16*j+k*2+1]);
	     }
	   }
	  AddrX = 0x88;
	 }
	  Write_Cmd(0x36); //打开绘图模式
	  Write_Cmd(0x30); //恢复基本指令集，关闭绘图模式
}

