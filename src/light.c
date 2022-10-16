#include "stc.h"
#include "WS2812.h"
#include "light.h"

// 预设颜色
Pixel preset_color[16] = {
    {255,20,147},   // 粉色
    {0,255,127},    // 绿色
    {10,10,205},    // 蓝色
    {255,140,0},    // 橙色
};

// 点亮测试
void ws2812_allot() {
    u8 i,j;
    for(i=0;i<WSCOUNT;i++)
        for(j=0;j<3;j++) {
            if (j==1) WS2812_Buffer[i][j]=50;
            else WS2812_Buffer[i][j]=0;
        }
}

// 清空颜色
void lighting_clear() {
    u8 i;
    for(i=0;i<WSCOUNT;i++) {
        WS2812_Buffer[i][0] = 0;
        WS2812_Buffer[i][1] = 0;
        WS2812_Buffer[i][2] = 0;
    }
}

// 随按键改变颜色
void lighting_effect_1() {
    static u8 r,g,b;
    static u32 cnt = 0;
    static u32 fx_loop = 0;
    static u8 last_key,key;
    int g_step = 5, r_step = 4, b_step = -3;
    u8 i,k;
    key = ~P1;
    fx_loop++;
    if (last_key != key && fx_loop > 300) {
        fx_loop = 0;
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
                
                WS2812_Buffer[k][0] = r;
                WS2812_Buffer[k][1] = g;
                WS2812_Buffer[k][2] = b;
                cnt++;
            }else {
                WS2812_Buffer[k][0] = 0;
                WS2812_Buffer[k][1] = 0;
                WS2812_Buffer[k][2] = 0;
            }
        }
        last_key = ~P1;
    }
    
}

// 按下按键固定显示某种颜色
void lighting_effect_2(u8 mode) {
    u8 i,k;
    static u8 last_key,key;
    static u32 fx1_loop = 0;
    key = ~P1;
    fx1_loop++;
    if (last_key != key && fx1_loop > 300) {
        fx1_loop = 0;
        for (i=0; i<8; i++) {
            if (i > 2) {k = i - 1;} else {k = i;}
            if (key & (1 << i)) {
                WS2812_Buffer[k][0] = preset_color[mode].r;
                WS2812_Buffer[k][1] = preset_color[mode].g;
                WS2812_Buffer[k][2] = preset_color[mode].b;
            }else {
                WS2812_Buffer[k][0] = 0;
                WS2812_Buffer[k][1] = 0;
                WS2812_Buffer[k][2] = 0;
            }
        }
        last_key = ~P1;
    }
    
}

// 全部渐变颜色效果
void lighting_effect_3() {
    u8 i;
    static u8 r,g,b;
    static u32 cnt = 0;
    static u16 fx2_loop = 0;
    static int g_step = 1, r_step = 1, b_step = -1;
    fx2_loop++;
    if (fx2_loop > 500) {
        fx2_loop = 0;
        cnt %= 0x300;
        for (i=0;i<7;i++) {
            r_step = r == 0?1:(r == 0xff?-1:r_step);
            r += (cnt / 0x100) != 0?0:r_step;
            g_step = g == 0?1:(g == 0xff?-1:g_step);
            g += (cnt / 0x100) != 1?0:g_step;
            b_step = b == 0?1:(b == 0xff?-1:b_step);
            b += (cnt / 0x100) != 2?0:b_step;
            
            WS2812_Buffer[i][0] = r;
            WS2812_Buffer[i][1] = g;
            WS2812_Buffer[i][2] = b;
            cnt++;
        }
    }
}

