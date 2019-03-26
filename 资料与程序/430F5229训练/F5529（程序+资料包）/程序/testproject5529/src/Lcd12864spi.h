/*
 * LCD12864_SPI.h
 *
 *  Created on: 2015-11-19
 *      Author: yumin
 */
#ifndef LCD12864_SPI_H_
#define LCD12864_SPI_H_

void lcd12864spi_init(void);
void lcd12864spi_clrddram(void);
void set_coord(unsigned char x, unsigned char y);
void lcd12864_show_str(char* string, unsigned char num);

extern char LCD_BUF_1[16];
extern char LCD_BUF_2[16];
extern char LCD_BUF_3[16];
extern char LCD_BUF_4[16];

#endif /* LCD12864_SPI_H_ */
