/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/*---------------------------------------------------------------------*/

#include "stc.h"
#include "usb.h"
#include "usb_req_class.h"

#define EX2 0x10
#define EX3 0x20
#define EX4 0x40

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

BYTE bHidIdle;
BYTE keyMap[8] = {0x07, 0x09, 0x00, 0x0d, 0x0e, 0x06, 0x10, 0x28};

sbit LED_NUM        = P6^7;
sbit LED_CAPS       = P6^6;
sbit LED_SCROLL     = P6^5;

u32 EC1_LOOP = 0;
u32 EC2_LOOP = 0;
int EC1_Path = 0;
int EC2_Path = 0;

void usb_req_class()
{
    switch (Setup.bRequest)
    {
    case GET_REPORT:
        usb_get_report();
        break;
    case SET_REPORT:
        usb_set_report();
        break;
    case GET_IDLE:
        usb_get_idle();
        break;
    case SET_IDLE:
        usb_set_idle();
        break;
    case GET_PROTOCOL:
        usb_get_protocol();
        break;
    case SET_PROTOCOL:
        usb_set_protocol();
        break;
    default:
        usb_setup_stall();
        return;
    }
}

void usb_get_report()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (IN_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT)))
    {
        usb_setup_stall();
        return;
    }

    Ep0State.pData = UsbBuffer;
    Ep0State.wSize = Setup.wLength;

    usb_setup_in();
}

void usb_set_report()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (OUT_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT)))
    {
        usb_setup_stall();
        return;
    }

    Ep0State.pData = UsbBuffer;
    Ep0State.wSize = Setup.wLength;

    usb_setup_out();
}

void usb_get_idle()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (IN_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT)))
    {
        usb_setup_stall();
        return;
    }

    Ep0State.pData = &bHidIdle;
    Ep0State.wSize = 1;

    usb_setup_in();
}

void usb_set_idle()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (OUT_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT)))
    {
        usb_setup_stall();
        return;
    }

    bHidIdle = Setup.wValueH;

    usb_setup_status();
}

void usb_get_protocol()
{
    usb_setup_stall();
}

void usb_set_protocol()
{
    usb_setup_stall();
}

void usb_class_out()
{
    BYTE led;
    
    if (usb_bulk_intr_out(UsbBuffer, 1) == 1)
    {
        P4M0 &= ~0x01;
        P4M1 &= ~0x01;
        P6M0 &= ~0xe0;
        P6M1 &= ~0xe0;
        P40 = 0;
        
        led = UsbBuffer[0];
        LED_NUM = !(led & 0x01);
        LED_CAPS = !(led & 0x02);
        LED_SCROLL = !(led & 0x04);
    }
}

void usb_class_in()
{
    BYTE key[16];
    BYTE i;
    BYTE p;
    
    if (DeviceState != DEVSTATE_CONFIGURED)
        return;

    if (!UsbInBusy)
    {
        // 清空所有键值
        for (i=0; i<16; i++) {
            key[i] = 0;
        }
        
        

        // 扫描按键
        for (i=0; i<8; i++) {
            if (~P1 & (1 << i)) {
                for (p=0; p<14; p++) {
                    if (key[p+2] == 0x00) {
                        key[p+2] = keyMap[i];
                        break;
                    }
                }
            } else {
                for (p=0; p<14; p++) {
                    if (keyMap[i] && key[i+2] == keyMap[i]) {
                        key[i+2] = 0x00;
                        break;
                    }
                }
            }
        }

        // 左编码器
        if (EC1_Path == -1) {
            for (p=0; p<14; p++) {
                if (key[p+2] == 0x00) {
                    key[p+2] = 0x14;
                    // EC1_Path = 0;
                    break;
                }
            }
        }else if (EC1_Path == 1) {
            for (p=0; p<14; p++) {
                if (key[p+2] == 0x00) {
                    key[p+2] = 0x1A;
                    // EC1_Path = 0;
                    break;
                }
            }
        }

        // 右编码器
        if (EC2_Path == -1) {
            for (p=0; p<14; p++) {
                if (key[p+2] == 0x00) {
                    key[p+2] = 0x12;
                    // EC2_Path = 0;
                    break;
                }
            }
        }else if (EC2_Path == 1) {
            for (p=0; p<14; p++) {
                if (key[p+2] == 0x00) {
                    key[p+2] = 0x13;
                    // EC2_Path = 0;
                    break;
                }
            }
        }

        IE2 &= ~0x80;   //EUSB = 0;
        UsbInBusy = 1;
        usb_write_reg(INDEX, 1);
        for (i=0; i<16; i++)
        {
            usb_write_reg(FIFO1, key[i]);
        }
        usb_write_reg(INCSR1, INIPRDY);
        IE2 |= 0x80;    //EUSB = 1;
    }
}

void EC_Loop(u32 LOOP) {
    EC1_LOOP++;
    EC2_LOOP++;
    if (EC1_LOOP >= LOOP) {EC1_Path = 0; EC1_LOOP = 0;}
    if (EC2_LOOP >= LOOP) {EC2_Path = 0; EC2_LOOP = 0;}
}



/********************* INT0中断函数 *************************/
void INT0_int (void) interrupt 0      //进中断时已经清除标志
{
    if (P33) {EC1_LOOP = 0; EC1_Path = 1;} else EC1_Path = -1; EC1_LOOP = 0;
}

/********************* INT1中断函数 *************************/
void INT1_int (void) interrupt 2      //进中断时已经清除标志
{
    // if (P32) {EC1_LOOP = 0; EC1_Path = -1;} else EC1_Path = 1; EC1_LOOP = 0; // 取消注释旋钮报文2倍
}

/********************* INT2中断函数 *************************/
void INT2_int (void) interrupt 10     //进中断时已经清除标志
{
    if (P37) {EC2_LOOP = 0; EC2_Path = 1;} else EC2_Path = -1; EC2_LOOP = 0;
}

/********************* INT3中断函数 *************************/
void INT3_int (void) interrupt 11     //进中断时已经清除标志
{
    // if (P36) {EC2_LOOP = 0; EC2_Path = -1;} else EC2_Path = 1; EC2_LOOP = 0; // 取消注释旋钮报文2倍
}