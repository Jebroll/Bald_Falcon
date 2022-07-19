#ifndef DRAW_LINE_H
#define DRAW_LINE_H

#include "MY_Common.h"
#include "SEEKFREE_18TFT.h"
#include "Fixed_Middle_Line.h"
#include "zf_stm_systick.h"

void LCD_Draw_Cross_Point(Uint8 point_x, Uint8 point_y, Uint16 color);
void Draw_Straight_Line(Uint8 *imag_out, Uint8 first_point_x, Uint8 first_point_y, Uint8 second_point_x, Uint8 second_point_y, Uint8 Imag_x);
Uint8 Draw_Ray_Line(Uint8 *imag_out, Uint8 first_point_x, Uint8 first_point_y, Uint8 second_point_x, Uint8 second_point_y, Uint8 Imag_x);
void Calculate_Boder_Line_Slope(Uint8 first_point_x, Uint8 first_point_y, Uint8 second_point_x, Uint8 second_point_y, ARRAY start_point, float *slope, float *intercept);
void Fixed_Middle_Line_With_Slope(float slope, float intercept, ARRAY start_point, Uint8 *output_x, Uint8 *output_y);
void LCD_Draw_Middle_Line(Uint8 stack_length, Uint16 color);
void LCD_Draw_Propect_Line(Uint8 propect_y, Uint16 color);
float Calculate_Slope(ARRAY first_point, ARRAY second_point);
void Fitting_Middle_Line_With_Border(Uint8* middle_line, Uint8 first_x, Uint8 second_x, Uint8 first_y, Uint8 second_y, Uint8 start_x, Uint8 start_y, Uint8 *last_x, Uint8 *last_y);

void Draw_Curve(Uint8 *imag_out, Uint8 first_point_x, Uint8 first_point_y, Uint8 second_point_x, Uint8 second_point_y, Uint8 Imag_x);

#endif
