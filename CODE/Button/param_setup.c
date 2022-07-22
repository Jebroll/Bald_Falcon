#include "param_setup.h"

uint8 Configuration_complete_flag = 0;

void LBalance_Angle_Seting(void)
{
/**************************LBalance_Angle Seting****************************/
    Servo_Control(Max_Angle);
    lcd_showstr(20 , 3,"LBalance_Angle:");
    lcd_showfloat(59 ,4, Balance_Param.Balance_Angle.left, 1, 2);
    while(!key3_f.single_click)
    {
        if (key1_f.single_click)
        {
            Balance_Param.Balance_Angle.left += 0.02;
            key1_f.single_click = 0;
            lcd_showfloat(59 ,4, Balance_Param.Balance_Angle.left, 1, 2);
        }
        if (key2_f.single_click)
        {
            Balance_Param.Balance_Angle.left -= 0.02;
            key2_f.single_click = 0;
            lcd_showfloat(59 ,4, Balance_Param.Balance_Angle.left, 1, 2);
        }
    }
    key3_f.single_click = 0;
    lcd_clear(WHITE);
 /**************************LBalance_Angle Seting****************************/
}

void MBalance_Angle_Seting(void)
{
/**************************MBalance_Angle Seting****************************/
    Servo_Control(Mid_Angle);
    lcd_showstr(20 , 3,"MBalance_Angle:");
    lcd_showfloat(59 ,4, Balance_Param.Balance_Angle.mid, 1, 2);
    while(!key3_f.single_click)
    {
        if (key1_f.single_click)
        {
            Balance_Param.Balance_Angle.mid += 0.02;
            key1_f.single_click = 0;
            lcd_showfloat(59 ,4, Balance_Param.Balance_Angle.mid, 1, 2);
        }
        if (key2_f.single_click)
        {
            Balance_Param.Balance_Angle.mid -= 0.02;
            key2_f.single_click = 0;
            lcd_showfloat(59 ,4, Balance_Param.Balance_Angle.mid, 1, 2);
        }
    }
    key3_f.single_click = 0;
    lcd_clear(WHITE);
/**************************MBalance_Angle Seting****************************/
}

void RBalance_Angle_Seting(void)
{
/**************************RBalance_Angle Seting****************************/
    Servo_Control(Min_Angle);
    lcd_showstr(20 , 3,"RBalance_Angle:");
    lcd_showfloat(59 ,4, Balance_Param.Balance_Angle.right, 1, 2);
    while(!key3_f.single_click)
    {
       if (key1_f.single_click)
       {
           Balance_Param.Balance_Angle.right += 0.02;
           key1_f.single_click = 0;
           lcd_showfloat(59 ,4, Balance_Param.Balance_Angle.right, 1, 2);
       }
       if (key2_f.single_click)
       {
           Balance_Param.Balance_Angle.right -= 0.02;
           key2_f.single_click = 0;
           lcd_showfloat(59 ,4, Balance_Param.Balance_Angle.right, 1, 2);
       }
    }
    key3_f.single_click = 0;
    lcd_clear(WHITE);
/**************************RBalance_Angle Seting****************************/
}
void Speed_Correction_Seting(void)
{
/****************************Speed_Correction Seting*****************************/
   lcd_showstr(12 , 3,"LSpeed_Correction:");
   lcd_showfloat(59 ,4, Balance_Param.Speed_Correction.left, 1, 3);
   while(!key3_f.single_click)
   {
       if (key1_f.single_click)
       {
           Balance_Param.Speed_Correction.left += 0.002;
           key1_f.single_click = 0;
           lcd_showfloat(59 ,4, Balance_Param.Speed_Correction.left, 1, 3);
       }
       if (key2_f.single_click)
       {
           Balance_Param.Speed_Correction.left -= 0.002;
           key2_f.single_click = 0;
           lcd_showfloat(59 ,4, Balance_Param.Speed_Correction.left, 1, 3);
       }
   }
   key3_f.single_click = 0;
   lcd_clear(WHITE);

   lcd_showstr(12 , 3,"RSpeed_Correction:");
       lcd_showfloat(59 ,4, Balance_Param.Speed_Correction.right, 1, 3);
       while(!key3_f.single_click)
       {
           if (key1_f.single_click)
           {
               Balance_Param.Speed_Correction.right += 0.002;
               key1_f.single_click = 0;
               lcd_showfloat(59 ,4, Balance_Param.Speed_Correction.right, 1, 3);
           }
           if (key2_f.single_click)
           {
               Balance_Param.Speed_Correction.right -= 0.002;
               key2_f.single_click = 0;
               lcd_showfloat(59 ,4, Balance_Param.Speed_Correction.right, 1, 3);
           }
       }
       key3_f.single_click = 0;
       lcd_clear(WHITE);
/****************************Speed_Correction Seting*****************************/
}
void Speed_Setup_Seting(void)
{
/****************************Speed_Setup Seting*****************************/
    lcd_showstr(20 , 3,"Speed_Setup:");
    lcd_showfloat(59 ,4, Speed_Param.Speed_Setup, 3, 2);
    while(!key3_f.single_click)
    {
      if (key1_f.single_click)
      {
          Speed_Param.Speed_Setup += 10;
          key1_f.single_click = 0;
          lcd_showfloat(59 ,4, Speed_Param.Speed_Setup, 3, 0);
      }
      if (key2_f.single_click)
      {
          Speed_Param.Speed_Setup -= 10;
          key2_f.single_click = 0;
          lcd_showfloat(59 ,4, Speed_Param.Speed_Setup, 3, 0);
      }
    }
    key3_f.single_click = 0;
    lcd_clear(WHITE);
 /****************************Speed_Setup Seting*****************************/
}

void Bicycle_Configuration(void)
{
#if 1
//    Buzzer_Ctrl(ON);
//    systick_delay_ms(STM0, 300);
//    Buzzer_Ctrl(OFF);
//    systick_delay_ms(STM0, 300);
//    Buzzer_Ctrl(ON);
//    systick_delay_ms(STM0, 100);
//    Buzzer_Ctrl(OFF);
//    systick_delay_ms(STM0, 100);
//    Buzzer_Ctrl(ON);
//    systick_delay_ms(STM0, 100);
//    Buzzer_Ctrl(OFF);
//    systick_delay_ms(STM0, 100);
//    pit_interrupt_ms(CCU6_1, PIT_CH0, 5);//开启定时器中断控制电机舵机
//    LBalance_Angle = flash_read(0, LBalance_Angle_page, float);
//    MBalance_Angle = flash_read(0, MBalance_Angle_page, float);
//    RBalance_Angle = flash_read(0, RBalance_Angle_page, float);
//
//    Speed_Setup = flash_read(1, Speed_Setup_page, float);
//    Speed_Correction = flash_read(1, Speed_Correction_page, float);

    lcd_showstr(20 , 2,"Bicycle");
    lcd_showstr(20 , 3,"Configuration:");
    lcd_showstr(20 , 4,"Press key4 ");
    lcd_showstr(20 , 5,"to skip:");
    while(!key3_f.single_click)
    {
        if (key4_f.single_click) break;
    }
    key3_f.single_click = 0;
    lcd_clear(WHITE);

    if (!key4_f.single_click)
    {
        Speed_Setup_Seting();
        Speed_Correction_Seting();
//        LBalance_Angle_Seting();
//        MBalance_Angle_Seting();
//        RBalance_Angle_Seting();

        Servo_Control(Mid_Angle);
    }
    else
    {
        key4_f.single_click = 0;
    }
//    Buzzer_Ctrl(ON);
//    systick_delay_ms(STM0, 500);
//    Buzzer_Ctrl(OFF);
    systick_delay_ms(STM0, 1000);
    systick_delay_ms(STM0, 1000);
#endif
    Configuration_complete_flag = 1;
//    Head_Angle_Setup = 125;//调试用
}
