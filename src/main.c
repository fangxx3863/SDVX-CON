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

下载时, 设置IRC工作频率为 24MHz - 40Mhz 之间.

******************************************/

// 导入头文件
#include "stc.h"
#include "usb.h"
#include "usb_req_class.h"
#include "timer.h"
#include "light.h"

// 定义中断位
#define EX2         0x10
#define EX3         0x20
#define EX4         0x40
#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

// 定义全局变量
u32 loop = 0;

void sys_init();
void main() {
    // 静态定义变量
    static u8 lighting_effect = 0;
    static u8 last_ls = 0;
    static u8 ls = 0;

    // 系统初始化
    sys_init();
    usb_init();
    timer_init();

    // 主循环
    while (1) {
        EC_Loop(800);       // 编码器计时
        usb_class_in();     // USB数据发送

        // 灯效切换检测
        ls = !P35;
        if ((ls != last_ls) && loop > 800) {
            lighting_effect++;
            loop = 0;
            last_ls = ls;
        }if (lighting_effect >= 14) lighting_effect = 0;

        // 选择灯效
        switch (lighting_effect) {
        case 0:
            lighting_effect_1();
            break;
        case 2:
            lighting_effect_2(0);
            break;
        case 4:
            lighting_effect_2(1);
            break;
        case 6:
            lighting_effect_2(2);
            break;
        case 8:
            lighting_effect_2(3);
            break;
        case 10:
            lighting_effect_3();
            break;
        
        default:
            lighting_clear();
            break;
        }

        WS2812_Transmit();   // WS2812数据发送
        loop++;         // 循环计数
    }
}

void sys_init() {
    P_SW2 |= 0x80;  // 扩展寄存器(XFR)访问使能

    P3M0 &= ~0x03;  // 设置USB口高阻输入
    P3M1 |= 0x03;

    P3M1 &= 0<<4;   // 设置P34推挽
    P3M0 |= 1<<4;

    P3M1 &= 0<<5;   // 设置P35准双向
    P3M0 &= 1<<5;
    
    IRC48MCR = 0x80;    // 设置内部震荡控制器
    while (!(IRC48MCR & 0x01));
    
    USBCLK = 0xC0;      // USB时钟设置
    USBCON = 0x90;      // USB控制设置

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
