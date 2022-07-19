#include "MY_Common.h"

Uint8 Border_Image[Border_Imag_Y][Border_Imag_X];

/*
 * @brief 取绝对值函数
 * @param 无
 * */
Uint8 ABS(Int16 dat)
{
    return (dat>0?dat:(-dat));
}

Uint8 My_Sqrt(Uint16 x)
{
    Uint8 ans = 0, p = 0x80;
    while(p!=0)
    {
        ans += p;
        if (ans*ans>x)
        {
            ans-=p;
        }
        p = (Uint8)(p/2);
    }
    return ans;
}

//gpio_init(P21_4, GPO, 0, PUSHPULL);
//systick_delay_ms(STM0, 1000);
