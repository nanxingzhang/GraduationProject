#ifndef __ADS1118_H__
#define __ADS1118_H__


#define uint  unsigned int
#define uchar unsigned char

void ADS1118_Init();
float ADS1118(uchar port, uchar scale);

#endif
