/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 濡傛灉瑕佸湪绋嬪簭涓娇鐢ㄦ浠ｇ爜,璇峰湪绋嬪簭涓敞鏄庝娇鐢ㄤ簡STC鐨勮祫鏂欏強绋嬪簭        */
/*---------------------------------------------------------------------*/

#include "stc.h"
#include "usb_desc.h"

char code DEVICEDESC[18] =
{
    0x12,                   //bLength(18);
    0x01,                   //bDescriptorType(Device);
    0x00,0x02,              //bcdUSB(2.00);
    0x00,                   //bDeviceClass(0);
    0x00,                   //bDeviceSubClass0);
    0x00,                   //bDeviceProtocol(0);
    0x40,                   //bMaxPacketSize0(64);
    0xbf,0x34,              //idVendor(34bf);
    0x03,0xff,              //idProduct(ff03);
    0x00,0x01,              //bcdDevice(1.00);
    0x01,                   //iManufacturer(1);
    0x02,                   //iProduct(2);
    0x00,                   //iSerialNumber(0);
    0x01,                   //bNumConfigurations(1);
};

char code CONFIGDESC[41] =
{
    0x09,                   //bLength(9);
    0x02,                   //bDescriptorType(Configuration);
    0x29,0x00,              //wTotalLength(41);
    0x01,                   //bNumInterfaces(1);
    0x01,                   //bConfigurationValue(1);
    0x00,                   //iConfiguration(0);
    0x80,                   //bmAttributes(BUSPower);
    0x96,                   //MaxPower(300mA);

    0x09,                   //bLength(9);
    0x04,                   //bDescriptorType(Interface);
    0x00,                   //bInterfaceNumber(0);
    0x00,                   //bAlternateSetting(0);
    0x02,                   //bNumEndpoints(2);
    0x03,                   //bInterfaceClass(HID);
    0x01,                   //bInterfaceSubClass(HID[0x00],Boot[0x01]);
    0x01,                   //bInterfaceProtocol(Keyboard);
    0x00,                   //iInterface(0);

    0x09,                   //bLength(9);
    0x21,                   //bDescriptorType(HID);
    0x01,0x01,              //bcdHID(1.01);
    0x00,                   //bCountryCode(0);
    0x01,                   //bNumDescriptors(1);
    0x22,                   //bDescriptorType(HID Report);
    0x41,0x00,              //wDescriptorLength(65);

    0x07,                   //bLength(7);
    0x05,                   //bDescriptorType(Endpoint);
    0x81,                   //bEndpointAddress(EndPoint1 as IN);
    0x03,                   //bmAttributes(Interrupt);
    0x10,0x00,              //wMaxPacketSize(16);
    0x01,                   //bInterval(1ms);

    0x07,                   //bLength(7);
    0x05,                   //bDescriptorType(Endpoint);
    0x01,                   //bEndpointAddress(EndPoint1 as OUT);
    0x03,                   //bmAttributes(Interrupt);
    0x01,0x00,              //wMaxPacketSize(1);
    0x0a,                   //bInterval(10ms);
};

/*
Input Report:
0   Modifierkeys (D0:LCtrl D1:LShift D2:LAlt D3:LGui D4:RCtrl D5:RShift D6:RAlt D7:RGui)
1	Reserved
2	Keycode 1
3	Keycode 2
4	Keycode 3
5	Keycode 4
6	Keycode 5
7	Keycode 6
Output Report:
0   LEDs (D0:NumLock D1:CapLock D2:ScrollLock)
*/
char code HIDREPORTDESC[65] =
{
    0x05,0x01,              //USAGE_PAGE(Generic Desktop);
    0x09,0x06,              //USAGE(Keyboard);
    0xa1,0x01,              //COLLECTION(Application);
    0x05,0x07,              //  USAGE_PAGE(Keyboard);
    0x19,0xe0,              //  USAGE_MINIMUM(224);
    0x29,0xe7,              //  USAGE_MAXIMUM(255);
    0x15,0x00,              //  LOGICAL_MINIMUM(0);
    0x25,0x01,              //  LOGICAL_MAXIMUM(1);
    0x75,0x01,              //  REPORT_SIZE(1);
    0x95,0x08,              //  REPORT_COUNT(8);
    0x81,0x02,              //  INPUT(Data,Variable,Absolute);
    
    0x75,0x08,              //  REPORT_SIZE(8);
    0x95,0x01,              //  REPORT_COUNT(1);
    0x81,0x01,              //  INPUT(Constant);
    
    0x19,0x00,              //  USAGE_MINIMUM(0);
    0x29,0x65,              //  USAGE_MAXIMUM(101);
    0x15,0x00,              //  LOGICAL_MINIMUM(0);
    0x25,0x65,              //  LOGICAL_MAXIMUM(101);
    0x75,0x08,              //  REPORT_SIZE(8);
    0x95,0x0E,              //  REPORT_COUNT(14);
    0x81,0x00,              //  INPUT(Data,Array);
    
    0x05,0x08,              //  USAGE_PAGE(LEDs);
    0x19,0x01,              //  USAGE_MINIMUM(1);
    0x29,0x03,              //  USAGE_MAXIMUM(3);
    0x15,0x00,              //  LOGICAL_MINIMUM(0);
    0x25,0x01,              //  LOGICAL_MAXIMUM(1);
    0x75,0x01,              //  REPORT_SIZE(1);
    0x95,0x03,              //  REPORT_COUNT(3);
    0x91,0x02,              //  OUTPUT(Data,Variable,Absolute);
    
    0x75,0x05,              //  REPORT_SIZE(5);
    0x95,0x01,              //  REPORT_COUNT(1);
    0x91,0x01,              //  OUTPUT(Constant);
    
    0xc0,                   //END_COLLECTION;
};

char code LANGIDDESC[4] =
{
    0x04,0x03,
    0x09,0x04,
};

char code MANUFACTDESC[8] =
{
    0x08,0x03,
    'S',0,
    'T',0,
    'C',0,
};

char code PRODUCTDESC[34] =
{
    0x22,0x03,
    'S',0,
    'T',0,
    'C',0,
    ' ',0,
    'U',0,
    'S',0,
    'B',0,
    ' ',0,
    'K',0,
    'e',0,
    'y',0,
    'b',0,
    'o',0,
    'a',0,
    'r',0,
    'd',0,
};

char code PACKET0[2] = 
{
    0, 0,
};

char code PACKET1[2] = 
{
    1, 0,
};

