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
#include "util.h"

//DWORD reverse4(DWORD d)
//{   
//    DWORD ret;
//    
//    ((BYTE *)&ret)[0] = ((BYTE *)&d)[3];
//    ((BYTE *)&ret)[1] = ((BYTE *)&d)[2];
//    ((BYTE *)&ret)[2] = ((BYTE *)&d)[1];
//    ((BYTE *)&ret)[3] = ((BYTE *)&d)[0];
//
//    return ret;
//}
   
WORD reverse2(WORD w)
{
    WORD ret;
    
    ((BYTE *)&ret)[0] = ((BYTE *)&w)[1];
    ((BYTE *)&ret)[1] = ((BYTE *)&w)[0];

    return ret;
}
