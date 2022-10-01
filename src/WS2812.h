#ifndef WS2812
#define WS2812
/*******单片机主频=晶振频率/分频系数
WSCASE=1 30 29 28 27 26 25 24 
WSCASE=2 24 23 22 21 20 19
WSCASE=3 19 18 17 16 15
WSCASE=4 15 14 13 12
WSCASE=5 12 11
WSCASE=6 11 10
WSCASE=7 10  9  8
*/
#define WSCASE 1    //查表修改频率
#define WSCOUNT 7
sbit WS2812_DI = P3^4;
//sbit WS2812_DI=P5^5;
extern void WS2812_Ser();
extern u8 WS2812_BUffer[WSCOUNT][3];
#endif