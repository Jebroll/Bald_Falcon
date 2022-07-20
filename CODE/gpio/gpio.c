#include "gpio.h"

void Led_Ctrl(uint8 num, GPIO_STATUS_enum status)
{
    switch (num)
    {
        case 1: gpio_set(LED1,  status); break;
        case 2: gpio_set(LED2,  status); break;
        case 3: gpio_set(LED3,  status); break;
        case 4: gpio_set(LED4,  status); break;
        case 5: gpio_set(LED5, !status); break;
        case 6: gpio_set(LED6, !status); break;
        default: break;
    }
}

void Buzzer_Ctrl(GPIO_STATUS_enum status)
{
    gpio_set(BUZZER, status);
}

void Led_Init(void)
{
    gpio_init(LED6, GPO, 1, OPENDRAIN);//LED6_Init
    gpio_init(LED5, GPO, 1, OPENDRAIN);//LED5_Init
    gpio_init(LED4, GPO, 0, PUSHPULL);//LED4_Init
    gpio_init(LED3, GPO, 0, PUSHPULL);//LED3_Init
    gpio_init(LED2, GPO, 0, PUSHPULL);//LED2_Init
    gpio_init(LED1, GPO, 0, PUSHPULL);//LED1_Init
}

void Buzzer_Init(void)
{
    gpio_init(BUZZER, GPO, 0, PUSHPULL);//Buzzer_Init
}

void Gpio_Init(void)
{
    Buzzer_Init();
    Led_Init();
}
