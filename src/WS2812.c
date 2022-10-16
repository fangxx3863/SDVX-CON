#include "stc.h"
#include "WS2812.h"
#include <intrins.h>

u8 WS2812_Buffer[WSCOUNT][3];
void WS2812_write_date()
{
		u8 i,j,k,a;
		for(k=0;k<WSCOUNT;k++)
		{
				for(j=0;j<3;j++)
				{
						switch(j)
						{
							case 0:a=WS2812_Buffer[k][1];break;
							case 1:a=WS2812_Buffer[k][0];break;
							case 2:a=WS2812_Buffer[k][2];break;
						}
						for(i=0;i<8;i++)
						{
							WS2812_DI=1;
							
#if WSCASE==0
_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
WS2812_DI=(a&0x80);	
_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
a<<=1;
#elif WSCASE==1							
_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
WS2812_DI=(a&0x80);	
_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
a<<=1;
#elif WSCASE==2	
_nop_();_nop_();_nop_();_nop_();
WS2812_DI=(a&0x80);	
_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
a<<=1;
#elif WSCASE==3	
_nop_();_nop_();
WS2812_DI=(a&0x80);	
_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
a<<=1;	
#elif WSCASE==4
WS2812_DI=(a&0x80);	
_nop_();_nop_();_nop_();_nop_();
a<<=1;
#elif WSCASE==5
WS2812_DI=(a&0x80);	
_nop_();_nop_();
a<<=1;
#elif WSCASE==6
WS2812_DI=(a&0x80);	
_nop_();
a<<=1;
#elif WSCASE==7
WS2812_DI=(a&0x80);	
a<<=1;
#endif
							
							WS2812_DI=0;
						}
						WS2812_DI=0;
				}
		}
}
void WS2812_Ser()
{
		static u8 count=0;
		count++;
		switch(count)
		{
			case 1:WS2812_DI=0;break;
			case 50:EA=0;WS2812_write_date();EA=1;break;
			case 51:WS2812_DI=0;break;
		}
		count%=60;
}				