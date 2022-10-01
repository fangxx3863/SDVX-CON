/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序             */
/*---------------------------------------------------------------------*/

/*************  功能说明    **************

基于STC8H8K64U实现的SDVX手台

下载时, 设置IRC工作频率为 24MHz.

******************************************/

#include "stc.h"
#include "usb.h"
#include "usb_req_class.h"
#include "timer.h"
#include "WS2812.h"
#include <stdlib.h> //包含rand()随机函数的头文件

#define EX2 0x10
#define EX3 0x20
#define EX4 0x40

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

// RGB颗粒结构
typedef struct {
	unsigned char r;					// 红色值
	unsigned char g;				    // 绿色值
	unsigned char b;					// 蓝色值
} Pixel;

Pixel preset_color[16] = {
    {255,20,147},   // 粉色
    {0,255,127},    // 绿色
    {123,104,238},  // 蓝色
    {255,140,0},    // 橙色
};

void sys_init();

void ws2812_allot()
{
    u8 i,j;
    for(i=0;i<WSCOUNT;i++)
        for(j=0;j<3;j++)
        {
            if(j==1)
            WS2812_BUffer[i][j]=50;
            else
            WS2812_BUffer[i][j]=0;
        }
}

u8 r,g,b;
u32 cnt = 0, loop = 0;
u8 last_key,key;
void lighting_effect_1(){
    int g_step = -2, r_step = -4, b_step = 3;
    u8 i,j,k;
    key = ~P1;
    if (last_key != key && loop > 300) {
        loop = 0;
        for (i=0; i<8; i++) {
            if (i > 2) {k = i - 1;} else {k = i;}
            if (key & (1 << i)) {
                cnt %= 0x300;
                
                r_step = r == 0?1:(r == 0xff?-1:r_step);
                r += (cnt / 0x100) != 0?0:r_step;

                g_step = g == 0?1:(g == 0xff?-1:g_step);
                g += (cnt / 0x100) != 1?0:g_step;
                
                b_step = b == 0?1:(b == 0xff?-1:b_step);
                b += (cnt / 0x100) != 2?0:b_step;
                
                WS2812_BUffer[k][0] = r;
                WS2812_BUffer[k][1] = g;
                WS2812_BUffer[k][2] = b;

                cnt++;
            }else {
                WS2812_BUffer[k][0] = 0;
                WS2812_BUffer[k][1] = 0;
                WS2812_BUffer[k][2] = 0;
            }
        }
        last_key = ~P1;
    }
    
}

void lighting_effect_2(mode){
    u8 i,j,k;
    key = ~P1;
    if (last_key != key && loop > 300) {
        loop = 0;
        for (i=0; i<8; i++) {
            if (i > 2) {k = i - 1;} else {k = i;}
            if (key & (1 << i)) {
                WS2812_BUffer[k][0] = preset_color[mode].r;
                WS2812_BUffer[k][1] = preset_color[mode].g;
                WS2812_BUffer[k][2] = preset_color[mode].b;
            }else {
                WS2812_BUffer[k][0] = 0;
                WS2812_BUffer[k][1] = 0;
                WS2812_BUffer[k][2] = 0;
            }
        }
        last_key = ~P1;
    }
    
}

int g_step = 50, r_step = -50, b_step = 50;
u16 fx2_loop = 0;
void lighting_effect_3(){
    u8 i;
    fx2_loop++;
    if (fx2_loop > 2800) {
        fx2_loop = 0;
        cnt %= 0x300;
        for (i=0;i<7;i++) {
            r_step = r == 0?1:(r == 0xff?-1:r_step);
            r += (cnt / 0x100) != 0?0:r_step;

            g_step = g == 0?1:(g == 0xff?-1:g_step);
            g += (cnt / 0x100) != 1?0:g_step;
            
            b_step = b == 0?1:(b == 0xff?-1:b_step);
            b += (cnt / 0x100) != 2?0:b_step;
            
            WS2812_BUffer[i][0] = r;
            WS2812_BUffer[i][1] = g;
            WS2812_BUffer[i][2] = b;

            cnt++;
        }
    }
}

u8 lighting_effect = 0;
u8 last_ls = 0;
u8 ls = 0;
void main()
{
    sys_init();
    usb_init();
    timer_init();
    
    while (1)
    {
        EC_Loop(1000);      // 编码器计时
        usb_class_in();     // USB数据发送
        ls = !P35;
        if ((ls != last_ls) && loop > 600) {
            lighting_effect++;
            loop = 0;
            last_ls = ls;
        }
        if (lighting_effect >= 14) lighting_effect = 0;
        // 选择灯效
        if (lighting_effect == 0) lighting_effect_1();
        if (lighting_effect == 2) lighting_effect_2(0);
        if (lighting_effect == 4) lighting_effect_2(1);
        if (lighting_effect == 6) lighting_effect_2(2);
        if (lighting_effect == 8) lighting_effect_2(3);
        if (lighting_effect == 10) lighting_effect_3();
        
        WS2812_Ser();   // WS2812数据发送
        loop++;
    }
}

void sys_init()
{
	P_SW2 |= 0x80;  // 扩展寄存器(XFR)访问使能

    P3M0 &= ~0x03;  // 设置USB口高阻输入
    P3M1 |= 0x03;

    P3M1 &= 0<<4; // P34推挽
    P3M0 |= 1<<4;

    P3M1 &= 0<<5; // P35准双向
    P3M0 &= 1<<5;
    
    IRC48MCR = 0x80;
    while (!(IRC48MCR & 0x01));
    
    USBCLK = 0x00;
    USBCON = 0x90;

    IE1  = 0;   // 外中断1标志位
    IE0  = 0;   // 外中断0标志位
    EX1 = 1;    // 使能外中断1
    EX0 = 1;    // 使能外中断0


    IT0 = 1;        //INT0 下降沿中断
    IT1 = 1;        //INT1 下降沿中断
    INTCLKO = EX2;  //使能 INT2 下降沿中断
    INTCLKO |= EX3; //使能 INT3 下降沿中断


    EA = 1;     //允许总中断

}
