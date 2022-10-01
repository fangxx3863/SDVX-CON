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
#include "usb.h"
#include "usb_desc.h"
#include "usb_req_std.h"
#include "usb_req_class.h"

void usb_req_std()
{
    switch (Setup.bRequest)
    {
    case GET_STATUS:
        usb_get_status();
        break;
    case CLEAR_FEATURE:
        usb_clear_feature();
        break;
    case SET_FEATURE:
        usb_set_feature();
        break;
    case SET_ADDRESS:
        usb_set_address();
        break;
    case GET_DESCRIPTOR:
        usb_get_descriptor();
        break;
    case SET_DESCRIPTOR:
        usb_set_descriptor();
        break;
    case GET_CONFIGURATION:
        usb_get_configuration();
        break;
    case SET_CONFIGURATION:
        usb_set_configuration();
        break;
    case GET_INTERFACE:
        usb_get_interface();
        break;
    case SET_INTERFACE:
        usb_set_interface();
        break;
    case SYNCH_FRAME:
        usb_synch_frame();
        break;
    default:
        usb_setup_stall();
        return;
    }
}

void usb_get_status()
{
    BYTE ep;
    
    if (((Setup.bmRequestType & DIRECT_MASK) != IN_DIRECT) ||
        (Setup.wValueH != 0) ||
        (Setup.wValueL != 0) ||
        (Setup.wLength != 2))
    {
        usb_setup_stall();
        return;
    }
    
    switch (Setup.bmRequestType & RECIPIENT_MASK)
    {
    case DEVICE_RECIPIENT:
        if ((Setup.wIndexH != 0) ||
            (Setup.wIndexL != 0))
        {
            usb_setup_stall();
            return;
        }
        else
        {
            Ep0State.pData = PACKET0;
            Ep0State.wSize = 2;
        }
        break;
    case INTERFACE_RECIPIENT:
        if ((DeviceState != DEVSTATE_CONFIGURED) ||
            (Setup.wIndexH != 0) ||
            (Setup.wIndexL != 0))
        {
            usb_setup_stall();
            return;
        }
        else
        {
            Ep0State.pData = PACKET0;
            Ep0State.wSize = 2;
        }
        break;
    case ENDPOINT_RECIPIENT:
        if ((DeviceState != DEVSTATE_CONFIGURED) ||
            (Setup.wIndexH != 0))
        {
            usb_setup_stall();
            return;
        }
        else
        {
            ep = Setup.wIndexL & 0x0f;
            switch (Setup.wIndexL)
            {
#ifdef EN_EP1IN
            case EP1_IN:
#endif
#ifdef EN_EP2IN
            case EP2_IN:
#endif
#ifdef EN_EP3IN
            case EP3_IN:
#endif
#ifdef EN_EP4IN
            case EP4_IN:
#endif
#ifdef EN_EP5IN
            case EP5_IN:
#endif
#if (defined(EN_EP1IN) || defined(EN_EP2IN) || defined(EN_EP3IN) || defined(EN_EP4IN) || defined(EN_EP5IN))
                if (InEpState & (1 << ep))
                {
                    Ep0State.pData = PACKET1;
                    Ep0State.wSize = 2;
                }
                else
                {
                    Ep0State.pData = PACKET0;
                    Ep0State.wSize = 2;
                }
                break;
#endif
#ifdef EN_EP1OUT
            case EP1_OUT:
#endif
#ifdef EN_EP2OUT
            case EP2_OUT:
#endif
#ifdef EN_EP3OUT
            case EP3_OUT:
#endif
#ifdef EN_EP4OUT
            case EP4_OUT:
#endif
#ifdef EN_EP5OUT
            case EP5_OUT:
#endif
#if (defined(EN_EP1OUT) || defined(EN_EP2OUT) || defined(EN_EP3OUT) || defined(EN_EP4OUT) || defined(EN_EP5OUT))
                if (OutEpState & (1 << ep))
                {
                    Ep0State.pData = PACKET1;
                    Ep0State.wSize = 2;
                }
                else
                {
                    Ep0State.pData = PACKET0;
                    Ep0State.wSize = 2;
                }
                break;
#endif
            default:
                usb_setup_stall();
                return;
            }
        }
        break;
    default:
        usb_setup_stall();
        return;
    }

    usb_setup_in();
}

void usb_clear_feature()
{
    BYTE ep;
    
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (OUT_DIRECT | STANDARD_REQUEST | ENDPOINT_RECIPIENT)) ||
        (Setup.wIndexH != 0) ||
        (Setup.wValueH != 0) ||
        (Setup.wValueL != ENDPOINT_HALT) ||
        (Setup.wLength != 0))
    {
        usb_setup_stall();
        return;
    }
    
    ep = Setup.wIndexL & 0x0f;
    switch (Setup.wIndexL)
    {
#ifdef EN_EP1IN
    case EP1_IN:
#endif
#ifdef EN_EP2IN
    case EP2_IN:
#endif
#ifdef EN_EP3IN
    case EP3_IN:
#endif
#ifdef EN_EP4IN
    case EP4_IN:
#endif
#ifdef EN_EP5IN
    case EP5_IN:
#endif
#if (defined(EN_EP1IN) || defined(EN_EP2IN) || defined(EN_EP3IN) || defined(EN_EP4IN) || defined(EN_EP5IN))
        InEpState &= ~(1 << ep);
        usb_write_reg(INDEX, ep);
        usb_write_reg(INCSR1, INCLRDT);
        usb_write_reg(INDEX, 0);
        break;
#endif
#ifdef EN_EP1OUT
    case EP1_OUT:
#endif
#ifdef EN_EP2OUT
    case EP2_OUT:
#endif
#ifdef EN_EP3OUT
    case EP3_OUT:
#endif
#ifdef EN_EP4OUT
    case EP4_OUT:
#endif
#ifdef EN_EP5OUT
    case EP5_OUT:
#endif
#if (defined(EN_EP1OUT) || defined(EN_EP2OUT) || defined(EN_EP3OUT) || defined(EN_EP4OUT) || defined(EN_EP5OUT))
        OutEpState &= ~(1 << ep);
        usb_write_reg(INDEX, ep);
        usb_write_reg(OUTCSR1, OUTCLRDT);
        usb_write_reg(INDEX, 0);
        break;
#endif
    default:
        usb_setup_stall();
        return;
    }

    usb_setup_status();
}

void usb_set_feature()
{
    BYTE ep;
    
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (OUT_DIRECT | STANDARD_REQUEST | ENDPOINT_RECIPIENT)) ||
        (Setup.wIndexH != 0) ||
        (Setup.wValueH != 0) ||
        (Setup.wValueL != ENDPOINT_HALT) ||
        (Setup.wLength != 0))
    {
        usb_setup_stall();
        return;
    }
    
    ep = Setup.wIndexL & 0x0f;
    switch (Setup.wIndexL)
    {
#ifdef EN_EP1IN
    case EP1_IN:
#endif
#ifdef EN_EP2IN
    case EP2_IN:
#endif
#ifdef EN_EP3IN
    case EP3_IN:
#endif
#ifdef EN_EP4IN
    case EP4_IN:
#endif
#ifdef EN_EP5IN
    case EP5_IN:
#endif
#if (defined(EN_EP1IN) || defined(EN_EP2IN) || defined(EN_EP3IN) || defined(EN_EP4IN) || defined(EN_EP5IN))
        InEpState |= (1 << ep);
        usb_write_reg(INDEX, ep);
        usb_write_reg(INCSR1, INSDSTL);
        usb_write_reg(INDEX, 0);
        break;
#endif
#ifdef EN_EP1OUT
    case EP1_OUT:
#endif
#ifdef EN_EP2OUT
    case EP2_OUT:
#endif
#ifdef EN_EP3OUT
    case EP3_OUT:
#endif
#ifdef EN_EP4OUT
    case EP4_OUT:
#endif
#ifdef EN_EP5OUT
    case EP5_OUT:
#endif
#if (defined(EN_EP1OUT) || defined(EN_EP2OUT) || defined(EN_EP3OUT) || defined(EN_EP4OUT) || defined(EN_EP5OUT))
        OutEpState |= (1 << ep);
        usb_write_reg(INDEX, ep);
        usb_write_reg(OUTCSR1, OUTSDSTL);
        usb_write_reg(INDEX, 0);
        break;
#endif
    default:
        usb_setup_stall();
        return;
    }

    usb_setup_status();
}

void usb_set_address()
{
    BYTE addr;
    
    if ((Setup.bmRequestType != (OUT_DIRECT | STANDARD_REQUEST | DEVICE_RECIPIENT)) ||
        (Setup.wIndexH != 0) ||
        (Setup.wIndexL != 0) ||
        (Setup.wValueH != 0) ||
        (Setup.wValueL >= 0x80) ||
        (Setup.wLength != 0))
    {
        usb_setup_stall();
        return;
    }
    
    addr = Setup.wValueL;
    usb_write_reg(FADDR, addr);
    if (addr != 0)
    {
        DeviceState = DEVSTATE_ADDRESS;
    }
    else
    {
        DeviceState = DEVSTATE_DEFAULT;
    }

    usb_setup_status();
}

void usb_get_descriptor()
{
    if ((Setup.bmRequestType & DIRECT_MASK) != IN_DIRECT)
    {
        usb_setup_stall();
        return;
    }
    
    switch (Setup.wValueH)
    {
    case DESC_DEVICE:
        Ep0State.pData = DEVICEDESC;
        Ep0State.wSize = sizeof(DEVICEDESC);
        break;
    case DESC_CONFIGURATION:
        Ep0State.pData = CONFIGDESC;
        Ep0State.wSize = sizeof(CONFIGDESC);
        break;
    case DESC_STRING:
        switch (Setup.wValueL)
        {
        case 0:
            Ep0State.pData = LANGIDDESC;
            Ep0State.wSize = sizeof(LANGIDDESC);
            break;
        case 1:
            Ep0State.pData = MANUFACTDESC;
            Ep0State.wSize = sizeof(MANUFACTDESC);
            break;
        case 2:
            Ep0State.pData = PRODUCTDESC;
            Ep0State.wSize = sizeof(PRODUCTDESC);
            break;
        default:
            usb_setup_stall();
            return;
        }
        break;
    case DESC_HIDREPORT:
        Ep0State.pData = HIDREPORTDESC;
        Ep0State.wSize = sizeof(HIDREPORTDESC);
        break;
    default:
        usb_setup_stall();
        return;
    }
    
    if (Ep0State.wSize > Setup.wLength)
    {
        Ep0State.wSize = Setup.wLength;
    }

    usb_setup_in();
}

void usb_set_descriptor()
{
    usb_setup_stall();
}

void usb_get_configuration()
{
    if ((Setup.bmRequestType != (IN_DIRECT | STANDARD_REQUEST | DEVICE_RECIPIENT)) ||
        (Setup.wValueH != 0) ||
        (Setup.wValueL != 0) ||
        (Setup.wIndexH != 0) ||
        (Setup.wIndexL != 0) ||
        (Setup.wLength != 1))
    {
        usb_setup_stall();
        return;
    }
    
    if (DeviceState == DEVSTATE_CONFIGURED)
    {
        Ep0State.pData = PACKET1;
        Ep0State.wSize = 1;
    }
    else
    {
        Ep0State.pData = PACKET0;
        Ep0State.wSize = 1;
    }

    usb_setup_in();
}

void usb_set_configuration()
{
    if ((DeviceState == DEVSTATE_DEFAULT) ||
        (Setup.bmRequestType != (OUT_DIRECT | STANDARD_REQUEST | DEVICE_RECIPIENT)) ||
        (Setup.wValueH != 0) ||
        (Setup.wIndexH != 0) ||
        (Setup.wIndexL != 0) ||
        (Setup.wLength != 0))
    {
        usb_setup_stall();
        return;
    }
    
    if (Setup.wValueL == 1)
    {
        DeviceState = DEVSTATE_CONFIGURED;
        InEpState = 0x00;
        OutEpState = 0x00;
#ifdef EN_EP1IN
        usb_write_reg(INDEX, 1);
        usb_write_reg(INCSR2, INMODEIN);
        usb_write_reg(INMAXP, EP1IN_SIZE / 8);
#endif
#ifdef EN_EP2IN
        usb_write_reg(INDEX, 2);
        usb_write_reg(INCSR2, INMODEIN);
        usb_write_reg(INMAXP, EP2IN_SIZE / 8);
#endif
#ifdef EN_EP3IN
        usb_write_reg(INDEX, 3);
        usb_write_reg(INCSR2, INMODEIN);
        usb_write_reg(INMAXP, EP3IN_SIZE / 8);
#endif
#ifdef EN_EP4IN
        usb_write_reg(INDEX, 4);
        usb_write_reg(INCSR2, INMODEIN);
        usb_write_reg(INMAXP, EP4IN_SIZE / 8);
#endif
#ifdef EN_EP5IN
        usb_write_reg(INDEX, 5);
        usb_write_reg(INCSR2, INMODEIN);
        usb_write_reg(INMAXP, EP5IN_SIZE / 8);
#endif
#ifdef EN_EP1OUT
        usb_write_reg(INDEX, 1);
        usb_write_reg(INCSR2, INMODEOUT);
        usb_write_reg(OUTMAXP, EP1OUT_SIZE / 8);
#endif
#ifdef EN_EP2OUT
        usb_write_reg(INDEX, 2);
        usb_write_reg(INCSR2, INMODEOUT);
        usb_write_reg(OUTMAXP, EP2OUT_SIZE / 8);
#endif
#ifdef EN_EP3OUT
        usb_write_reg(INDEX, 3);
        usb_write_reg(INCSR2, INMODEOUT);
        usb_write_reg(OUTMAXP, EP3OUT_SIZE / 8);
#endif
#ifdef EN_EP4OUT
        usb_write_reg(INDEX, 4);
        usb_write_reg(INCSR2, INMODEOUT);
        usb_write_reg(OUTMAXP, EP4OUT_SIZE / 8);
#endif
#ifdef EN_EP5OUT
        usb_write_reg(INDEX, 5);
        usb_write_reg(INCSR2, INMODEOUT);
        usb_write_reg(OUTMAXP, EP5OUT_SIZE / 8);
#endif
        usb_write_reg(INDEX, 0);
    }
    else
    {
        DeviceState = DEVSTATE_ADDRESS;
        InEpState = 0xff;
        OutEpState = 0xff;
    }

    usb_setup_status();
}

void usb_get_interface()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (IN_DIRECT | STANDARD_REQUEST | INTERFACE_RECIPIENT)) ||
        (Setup.wValueH != 0) ||
        (Setup.wIndexH != 0) ||
        (Setup.wLength != 1))
    {
        usb_setup_stall();
        return;
    }
    
    Ep0State.pData = PACKET0;
    Ep0State.wSize = 1;
    
    usb_setup_in();
}

void usb_set_interface()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (OUT_DIRECT | STANDARD_REQUEST | INTERFACE_RECIPIENT)) ||
        (Setup.wValueH != 0) ||
        (Setup.wIndexH != 0) ||
        (Setup.wLength != 0))
    {
        usb_setup_stall();
        return;
    }

    usb_setup_status();
}

void usb_synch_frame()
{
    usb_setup_stall();
}
