#include"MSP430f5529.h"

#define SCLK_H P6OUT |= BIT5;	//时钟置高
#define SCLK_L P6OUT &=~BIT5;	//时钟置低
                                //串行数据引脚定义在SID函数中，如有必要请转至SID()函数修改
//************指令集宏定义*************************************
// 基本指令
#define    ext8      0x34	// 8位数据，扩充指令操作
#define    clr       0x01	// DDRAM填满"20H",复位其AC
#define    cursor_1  0x06	// 光标的移动方向->正
#define    texton    0x0c	// 整体显示ON,  游标OFF, 游标位置反白允许OFF
#define    textoff   0x08	// 整体显示OFF, 游标OFF, 游标位置反白允许OFF
#define    ddbas     0x80	// 设定DDRAM 地址,第一行80H~87H,第二行90H~97H
#define    cgbas     0x40	// CGRAM基地址，范围：cgbas～cabas+64；每一位地址包括2字节

// 扩充指令
#define    bas8      0x30	// 8位数据，基本指令操作
#define    grapon    0x36	// 扩充指令，图形显示开
//************************************************************

char LCD_BUF_1[16]={"yumin"};
char LCD_BUF_2[16]={"12345"};
char LCD_BUF_3[16]={"YUMIN"};
char LCD_BUF_4[16]={"俞敏："};

//********************************************************************************
//* 名    称：lcdio()
//* 功    能：时钟引脚，数据引脚配置
//* 入口参数
//* 重要说明：与SID()函数同步修改
//********************************************************************************
void lcdio(void)
{
	P6DIR |= (BIT5+BIT6);
}

//********************************************************************************
//* 名    称：SID()
//* 功    能：串行数据输出
//* 入口参数：SID(0x00)---置低,         SID(0x01)---置高
//* 重要说明：此函数把 ---GPIO66---引脚作为串行数据输出，如需变动，需修改GPIO引脚寄存器
//********************************************************************************
void SID(unsigned char data)
{
	if((data&0x80)>>7==1)
		P6OUT|=BIT6;
	else
		P6OUT&=~BIT6;
}

void delaynms(unsigned int di)                       //粗略延时 ，可能需要修改
{
	unsigned int da,db;
	for(da=0;da<di;da++)
	for(db=0;db<10;db++);
}

void sendbyte(unsigned char bbyte)      //发送一个字节
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SID(bbyte);                    //取出最高位
		SCLK_H;
		SCLK_L;
		bbyte<<=1;                     //左移
	}
}

//********************************************************************************
//* 名    称：write()
//* 功    能：向液晶模块写指令或数据
//* 入口参数：start---0:写指令,1:写数据                  ddata---指令或数据
//* 返回参数：
//********************************************************************************
void write(unsigned char start, unsigned char ddata) //写指令或数据
{
	unsigned char start_data,Hdata,Ldata;

	if(start==0)  start_data=0xf8;	 //写指令
	  else        start_data=0xfa;   //写数据

	Hdata=ddata&0xf0;	  			 //取高四位
	Ldata=(ddata<<4)&0xf0;			 //取低四位
	sendbyte(start_data);	 		 //发送起始信号
//	delaynms(5); 					 //延时是必须的
	sendbyte(Hdata);				 //发送高四位
//	delaynms(1); 					 //延时是必须的
	sendbyte(Ldata);				 //发送低四位
//	delaynms(1); 					 //延时是必须的
}

void lcd12864spi_init(void)	   		 //初始化LCD
{
	lcdio();

	write(0,bas8);      		     //8 位数据，基本指令集
	write(0,texton);    		     //显示打开，光标关，反白关
	write(0,clr);       		     //清屏，将DDRAM的地址计数器归零
}

//********************************************************************************
//* 名    称：clrddram()
//* 功    能：清屏
//* 入口参数：
//* 返回参数：void
//********************************************************************************
void lcd12864spi_clrddram(void)
{
    write(0,clr);
    write(0,ext8);
    write(0,bas8);
}

//********************************************************************************
//* 名    称：set_coord()
//* 功    能：设置DDRAM的显示坐标
//* 入口参数：x取值范围：1～8,  y取值范围1～4
//* 返回参数：void
//********************************************************************************
void set_coord(unsigned char x, unsigned char y)
{
	   switch(y)
	   {
			case 1: write(0,0x7F + x);break;
			case 2: write(0,0x8F + x);break;
			case 3: write(0,0x87 + x);break;
			case 4: write(0,0x97 + x);break;
	        default:break;
	   }
}

//********************************************************************************
//* 名    称：lcd12864_show_str()
//* 功    能：在屏幕上显示一个字符串
//* 入口参数：string---字符串的首地址,num---显示字符串的个数
//* 返回参数：void
//********************************************************************************
void lcd12864_show_str(char* string, unsigned char num)
{
    while(num--)
    {
        write(1,*string++);//向12864液晶模块传输数据
    }
}

