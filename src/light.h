// RGB颗粒结构
typedef struct {
	unsigned char r;					// 红色值
	unsigned char g;				    // 绿色值
	unsigned char b;					// 蓝色值
} Pixel;

void ws2812_allot();
void lighting_effect_1();
void lighting_effect_2(u8 mode);
void lighting_effect_3();