#include "button.h"


struct Button key1, key2, key3, key4;

Button_Flag_Typedef key1_f, key2_f, key3_f, key4_f;


/****************Read Button API******************/
uint8 read_button1_GPIO(void)//按键一读取API
{
    return gpio_get(KEY1);
}

uint8 read_button2_GPIO(void)//按键一读取API
{
    return gpio_get(KEY2);
}

uint8 read_button3_GPIO(void)//按键一读取API
{
    return gpio_get(KEY3);
}

uint8 read_button4_GPIO(void)//按键一读取API
{
    return gpio_get(KEY4);
}
/****************Read Button API******************/


/****************Button Callback******************/
void button1_callback(void *button)//按键回调函数
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct Button *)button);

    switch(btn_event_val)
    {
     case PRESS_DOWN:
         printf("---> key1 press down! <---\r\n");
      break;

     case PRESS_UP:
         printf("***> key1 press up! <***\r\n");
      break;

     case PRESS_REPEAT:
         printf("---> key1 press repeat! <---\r\n");
      break;

     case SINGLE_CLICK:
//         printf("---> key1 single click! <---\r\n");
         key1_f.single_click = 1;
      break;

     case DOUBLE_CLICK:
         printf("***> key1 double click! <***\r\n");
      break;

     case LONG_PRESS_START:
         printf("---> key1 long press start! <---\r\n");
      break;

     case LONG_PRESS_HOLD:
         printf("***> key1 long press hold! <***\r\n");
      break;
    }
}

void button2_callback(void *button)//按键回调函数
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct Button *)button);

    switch(btn_event_val)
    {
     case PRESS_DOWN:
         printf("---> key2 press down! <---\r\n");
      break;

     case PRESS_UP:
         printf("***> key2 press up! <***\r\n");
      break;

     case PRESS_REPEAT:
         printf("---> key2 press repeat! <---\r\n");
      break;

     case SINGLE_CLICK:
//         printf("---> key2 single click! <---\r\n");
         key2_f.single_click = 1;
      break;

     case DOUBLE_CLICK:
         printf("***> key2 double click! <***\r\n");
      break;

     case LONG_PRESS_START:
         printf("---> key2 long press start! <---\r\n");
      break;

     case LONG_PRESS_HOLD:
         printf("***> key2 long press hold! <***\r\n");
      break;
    }
}

void button3_callback(void *button)//按键回调函数
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct Button *)button);

    switch(btn_event_val)
    {
     case PRESS_DOWN:
         printf("---> key3 press down! <---\r\n");
      break;

     case PRESS_UP:
         printf("***> key3 press up! <***\r\n");
      break;

     case PRESS_REPEAT:
         printf("---> key3 press repeat! <---\r\n");
      break;

     case SINGLE_CLICK:
//         printf("---> key3 single click! <---\r\n");
         key3_f.single_click = 1;
      break;

     case DOUBLE_CLICK:
         printf("***> key3 double click! <***\r\n");
      break;

     case LONG_PRESS_START:
         printf("---> key3 long press start! <---\r\n");
      break;

     case LONG_PRESS_HOLD:
         printf("***> key3 long press hold! <***\r\n");
      break;
    }
}

void button4_callback(void *button)//按键回调函数
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct Button *)button);

    switch(btn_event_val)
    {
     case PRESS_DOWN:
         printf("---> key4 press down! <---\r\n");
      break;

     case PRESS_UP:
         printf("***> key4 press up! <***\r\n");
      break;

     case PRESS_REPEAT:
         printf("---> key4 press repeat! <---\r\n");
      break;

     case SINGLE_CLICK:
//         printf("---> key4 single click! <---\r\n");
         key4_f.single_click = 1;
      break;

     case DOUBLE_CLICK:
         printf("***> key4 double click! <***\r\n");
      break;

     case LONG_PRESS_START:
         printf("---> key4 long press start! <---\r\n");
      break;

     case LONG_PRESS_HOLD:
         printf("***> key4 long press hold! <***\r\n");
      break;
    }
}
/****************Button Callback******************/
/****************Buttons Init******************/
void Button1_Init(void)
{
    gpio_init(KEY1,GPI,0,PULLUP);
    button_init(&key1, read_button1_GPIO, 0, 1);
    button_attach(&key1, SINGLE_CLICK, button1_callback);
    button_attach(&key1, DOUBLE_CLICK, button1_callback);
    button_attach(&key1, LONG_PRESS_START, button1_callback);
    button_start(&key1);
}

void Button2_Init(void)
{
    gpio_init(KEY2,GPI,0,PULLUP);
    button_init(&key2, read_button2_GPIO, 0, 2);
    button_attach(&key2, SINGLE_CLICK, button2_callback);
    button_attach(&key2, DOUBLE_CLICK, button2_callback);
    button_attach(&key2, LONG_PRESS_START, button2_callback);
    button_start(&key2);
}

void Button3_Init(void)
{
    gpio_init(KEY3,GPI,0,PULLUP);
    button_init(&key3, read_button3_GPIO, 0, 3);
    button_attach(&key3, SINGLE_CLICK, button3_callback);
    button_attach(&key3, DOUBLE_CLICK, button3_callback);
    button_attach(&key3, LONG_PRESS_START, button3_callback);
    button_start(&key3);
}

void Button4_Init(void)
{
    gpio_init(KEY4,GPI,0,PULLUP);
    button_init(&key4, read_button4_GPIO, 0, 4);
    button_attach(&key4, SINGLE_CLICK, button4_callback);
    button_attach(&key4, DOUBLE_CLICK, button4_callback);
    button_attach(&key4, LONG_PRESS_START, button4_callback);
    button_start(&key4);
}

void Button_Flag_Init(void)
{
    key1_f.single_click = 0;
    key2_f.single_click = 0;
    key3_f.single_click = 0;
    key4_f.single_click = 0;

    key1_f.double_click = 0;
    key2_f.double_click = 0;
    key3_f.double_click = 0;
    key4_f.double_click = 0;

    key1_f.LONG_PRESS_START = 0;
    key2_f.LONG_PRESS_START = 0;
    key3_f.LONG_PRESS_START = 0;
    key4_f.LONG_PRESS_START = 0;
}

void Buttons_Init(void)
{
    Button1_Init();
    Button2_Init();
    Button3_Init();
    Button4_Init();

    Button_Flag_Init();
}
/****************Buttons Init******************/


