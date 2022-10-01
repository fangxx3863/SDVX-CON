#ifndef __USB_H__
#define __USB_H__

#define USBBASE                 0
#define FADDR                   (USBBASE + 0)
#define UPDATE                  0x80
#define POWER                   (USBBASE + 1)
#define ISOUD                   0x80
#define USBRST                  0x08
#define USBRSU                  0x04
#define USBSUS                  0x02
#define ENSUS                   0x01
#define INTRIN1                 (USBBASE + 2)
#define EP5INIF                 0x20
#define EP4INIF                 0x10
#define EP3INIF                 0x08
#define EP2INIF                 0x04
#define EP1INIF                 0x02
#define EP0IF                   0x01
#define INTROUT1                (USBBASE + 4)
#define EP5OUTIF                0x20
#define EP4OUTIF                0x10
#define EP3OUTIF                0x08
#define EP2OUTIF                0x04
#define EP1OUTIF                0x02
#define INTRUSB                 (USBBASE + 6)
#define SOFIF                   0x08
#define RSTIF                   0x04
#define RSUIF                   0x02
#define SUSIF                   0x01
#define INTRIN1E                (USBBASE + 7)
#define EP5INIE                 0x20
#define EP4INIE                 0x10
#define EP3INIE                 0x08
#define EP2INIE                 0x04
#define EP1INIE                 0x02
#define EP0IE                   0x01
#define INTROUT1E               (USBBASE + 9)
#define EP5OUTIE                0x20
#define EP4OUTIE                0x10
#define EP3OUTIE                0x08
#define EP2OUTIE                0x04
#define EP1OUTIE                0x02
#define INTRUSBE                (USBBASE + 11)
#define SOFIE                   0x08
#define RSTIE                   0x04
#define RSUIE                   0x02
#define SUSIE                   0x01
#define FRAME1                  (USBBASE + 12)
#define FRAME2                  (USBBASE + 13)
#define INDEX                   (USBBASE + 14)
#define INMAXP                  (USBBASE + 16)
#define CSR0                    (USBBASE + 17)
#define SSUEND                  0x80
#define SOPRDY                  0x40
#define SDSTL                   0x20
#define SUEND                   0x10
#define DATEND                  0x08
#define STSTL                   0x04
#define IPRDY                   0x02
#define OPRDY                   0x01
#define INCSR1                  (USBBASE + 17)
#define INCLRDT                 0x40
#define INSTSTL                 0x20
#define INSDSTL                 0x10
#define INFLUSH                 0x08
#define INUNDRUN                0x04
#define INFIFONE                0x02
#define INIPRDY                 0x01
#define INCSR2                  (USBBASE + 18)
#define INAUTOSET               0x80
#define INISO                   0x40
#define INMODEIN                0x20
#define INMODEOUT               0x00
#define INENDMA                 0x10
#define INFCDT                  0x08
#define OUTMAXP                 (USBBASE + 19)
#define OUTCSR1                 (USBBASE + 20)
#define OUTCLRDT                0x80
#define OUTSTSTL                0x40
#define OUTSDSTL                0x20
#define OUTFLUSH                0x10
#define OUTDATERR               0x08
#define OUTOVRRUN               0x04
#define OUTFIFOFUL              0x02
#define OUTOPRDY                0x01
#define OUTCSR2                 (USBBASE + 21)
#define OUTAUTOCLR              0x80
#define OUTISO                  0x40
#define OUTENDMA                0x20
#define OUTDMAMD                0x10
#define COUNT0                  (USBBASE + 22)
#define OUTCOUNT1               (USBBASE + 22)
#define OUTCOUNT2               (USBBASE + 23)
#define FIFO0                   (USBBASE + 32)
#define FIFO1                   (USBBASE + 33)
#define FIFO2                   (USBBASE + 34)
#define FIFO3                   (USBBASE + 35)
#define FIFO4                   (USBBASE + 36)
#define FIFO5                   (USBBASE + 37)
#define UTRKCTL                 (USBBASE + 48)
#define UTRKSTS                 (USBBASE + 49)

#define DESC_DEVICE             0x01
#define DESC_CONFIGURATION      0x02
#define DESC_STRING             0x03

#define IN_DIRECT               0x80                //device to host
#define OUT_DIRECT              0x00                //host to device
#define DIRECT_MASK             0x80

#define STANDARD_REQUEST        0x00
#define CLASS_REQUEST           0x20
#define VENDOR_REQUEST          0x40
#define REQUEST_MASK            0x60

#define DEVICE_RECIPIENT        0x00
#define INTERFACE_RECIPIENT     0x01
#define ENDPOINT_RECIPIENT      0x02
#define RECIPIENT_MASK          0x0f

#define DEVICE_REMOTE_WAKEUP    0x01
#define ENDPOINT_HALT           0x00

#define EP1_IN                  0x81
#define EP1_OUT                 0x01
#define EP2_IN                  0x82
#define EP2_OUT                 0x02
#define EP3_IN                  0x83
#define EP3_OUT                 0x03
#define EP4_IN                  0x84
#define EP4_OUT                 0x04
#define EP5_IN                  0x85
#define EP5_OUT                 0x05

#define DEVSTATE_ATTACHED       0
#define DEVSTATE_POWERED        1
#define DEVSTATE_DEFAULT        2
#define DEVSTATE_ADDRESS        3
#define DEVSTATE_CONFIGURED     4
#define DEVSTATE_SUSPENDED      5

#define EPSTATE_IDLE            0
#define EPSTATE_HALT            1
#define EPSTATE_STATUS          2
#define EPSTATE_DATAIN          3
#define EPSTATE_DATAOUT         4
#define EPSTATE_STALL           5

typedef struct
{
    BYTE    bmRequestType;
    BYTE    bRequest;
    BYTE    wValueL;
    BYTE    wValueH;
    BYTE    wIndexL;
    BYTE    wIndexH;
    WORD    wLength;
}SETUP;

typedef struct
{
    BYTE    bState;
    WORD    wSize;
    BYTE    *pData;
}EPSTATE;

void usb_init();
BYTE usb_read_reg(BYTE addr);
void usb_write_reg(BYTE addr, BYTE dat);
BYTE usb_read_fifo(BYTE fifo, BYTE *pdat);
void usb_write_fifo(BYTE fifo, BYTE *pdat, BYTE cnt);

void usb_setup_stall();
void usb_setup_in();
void usb_setup_out();
void usb_setup_status();

void usb_ctrl_in();
void usb_ctrl_out();
void usb_bulk_intr_in(BYTE *pData, BYTE bSize, BYTE ep);
BYTE usb_bulk_intr_out(BYTE *pData, BYTE ep);

void usb_resume();
void usb_reset();
void usb_suspend();
void usb_setup();
void usb_in_ep1();
void usb_in_ep2();
void usb_in_ep3();
void usb_in_ep4();
void usb_in_ep5();
void usb_out_ep1();
void usb_out_ep2();
void usb_out_ep3();
void usb_out_ep4();
void usb_out_ep5();


extern BYTE DeviceState;
extern SETUP Setup;
extern EPSTATE Ep0State;
extern BYTE InEpState;
extern BYTE OutEpState;

extern BOOL UsbInBusy;

extern BYTE xdata UsbBuffer[256];

#endif
