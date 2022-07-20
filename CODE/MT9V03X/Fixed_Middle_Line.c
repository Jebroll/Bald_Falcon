#include "Fixed_Middle_Line.h"

BORDER_SATCK middle_line_stack;
BORDER_SATCK left_border_stack;
BORDER_SATCK right_border_stack;
ARRAY last_A_point, last_B_point;
ARRAY last_C_point, last_D_point;
ARRAY last_G_point, last_H_point;
ARRAY last_I_point, last_Top_point;
ARRAY last_L_point, last_J_point;
/* *************************栈相关函数************************************** */
void Border_Stack_Init(BORDER_SATCK *S)
{
    S->top = -1;
}

void Border_Enter_Stack(BORDER_SATCK *S, Uint8 data_x, Uint8 data_y)
{
    S->top++;
    S->data[S->top].x =  data_x;
    S->data[S->top].y =  data_y;
}

void Border_Pop_Stack(BORDER_SATCK *S, ARRAY *data_out)
{
    (*data_out).x = S->data[S->top].x;
    (*data_out).y = S->data[S->top].y;
    S->top--;
}

Uint8 Border_Stack_length(BORDER_SATCK *S)
{
    return (S->top+1);
}

Int8 Border_Stack_Get_Pointer(BORDER_SATCK *S)
{
    return (S->top);
}

void Border_Stack_Change_Pointer(BORDER_SATCK *S, Int8 pointer)
{
    S->top = pointer;
}
/* ************************************************************************* */

/* *************************从栈底往栈顶取*********************************** */
void Border_Pop_Stack_From_Bottom(BORDER_SATCK *S, ARRAY *data_out)
{
    (*data_out).x = S->data[S->top].x;
    (*data_out).y = S->data[S->top].y;
    S->top++;
}
/* ************************************************************************* */

/*
 * @Brief 补全边界图像
 * @param 道路类型
 * */
void Fixed_Border_Line(Uint8 road_type)
{
    static Uint8 top_x_store;
    switch(road_type)
    {
        /* ****************************************十字路口状态******************************************************* */
        case before_crossing_road1:
        case before_crossing_road3:
            Draw_Straight_Line(Binary_Image[0], Total_Image.special_point[C].x, Total_Image.special_point[C].y, \
                                                Total_Image.special_point[G].x, Total_Image.special_point[G].y, Border_Imag_X);
            Draw_Straight_Line(Binary_Image[0], Total_Image.special_point[D].x, Total_Image.special_point[D].y, \
                                                Total_Image.special_point[H].x, Total_Image.special_point[H].y, Border_Imag_X);
            last_C_point.x = Total_Image.special_point[C].x;
            last_D_point.x = Total_Image.special_point[D].x;
            last_G_point.x = Total_Image.special_point[G].x;
            last_H_point.x = Total_Image.special_point[H].x;
            last_G_point.y = Total_Image.special_point[G].y;
            last_H_point.y = Total_Image.special_point[H].y;
            break;
        case before_crossing_road2:
            Draw_Straight_Line(Binary_Image[0], Total_Image.special_point[C].x, Total_Image.special_point[C].y, \
                                                            Total_Image.special_point[G].x+10, Total_Image.special_point[G].y-6, Border_Imag_X);
            Draw_Straight_Line(Binary_Image[0], Total_Image.special_point[D].x, Total_Image.special_point[D].y, \
                                                Total_Image.special_point[H].x, Total_Image.special_point[H].y, Border_Imag_X);
            break;
        case before_crossing_road4:
            Draw_Straight_Line(Binary_Image[0], Total_Image.special_point[C].x, Total_Image.special_point[C].y, \
                                                Total_Image.special_point[G].x+10, Total_Image.special_point[G].y-6, Border_Imag_X);
            Draw_Straight_Line(Binary_Image[0], Total_Image.special_point[D].x, Total_Image.special_point[D].y, \
                                                Total_Image.special_point[H].x, Total_Image.special_point[H].y, Border_Imag_X);
            break;
        case in_crossing_road2:
            Draw_Straight_Line(Binary_Image[0], 27, 59, 43, 16, Border_Imag_X);
            Draw_Straight_Line(Binary_Image[0], 61, 59, 57, 16, Border_Imag_X);
            break;
        case in_crossing_road4:
            Draw_Straight_Line(Binary_Image[0], 27, 59, 42, 16, Border_Imag_X);
            Draw_Straight_Line(Binary_Image[0], 61, 59, 56, 16, Border_Imag_X);
            break;
        case in_crossing_road3:
            Draw_Straight_Line(Binary_Image[0], 28, 59, 38, 16, Border_Imag_X);
            Draw_Straight_Line(Binary_Image[0], 62, 59, 53, 16, Border_Imag_X);
            break;
        case in_crossing_road1:
            Draw_Straight_Line(Binary_Image[0], 28, 59, 38, 16, Border_Imag_X);
            Draw_Straight_Line(Binary_Image[0], 62, 59, 52, 16, Border_Imag_X);
            break;
        /* ******************************************************************************************************** */

        /* ****************************************三岔路状态******************************************************* */
        case before_right_three_way_road:
            Draw_Straight_Line(Binary_Image[0], Total_Image.special_point[C].x+5, Total_Image.special_point[C].y+5, \
                                                55, 10, Border_Imag_X);
            last_C_point.x = Total_Image.special_point[C].x;
            break;
        case in_right_three_way_road:
            Draw_Straight_Line(Binary_Image[0], last_C_point.x+5, 59, 55, 10, Border_Imag_X);
            break;
        case before_left_three_way_road:
            Draw_Straight_Line(Binary_Image[0], Total_Image.special_point[D].x, Total_Image.special_point[D].y, \
                                                Total_Image.special_point[I].x, Total_Image.special_point[I].y, Border_Imag_X);
            last_D_point.x = Total_Image.special_point[D].x;
            last_I_point.x = Total_Image.special_point[I].x;
            last_I_point.y = Total_Image.special_point[I].y;
            break;
        case in_left_three_way_road:
            Draw_Straight_Line(Binary_Image[0], last_D_point.x, 59, last_I_point.x, last_I_point.y, Border_Imag_X);
            break;
        /* ******************************************************************************************************** */

        /* ******************************************右环岛状态******************************************************* */
//        case right_round_about_status1:
//            Draw_Ray_Line(Border_Image[0], Total_Image.special_point[B].x,Total_Image.special_point[B].y, \
//                                           Total_Image.special_point[D].x,Total_Image.special_point[D].y, Border_Imag_X);
//            last_B_point.x = Total_Image.special_point[B].x;
//            last_B_point.y = Total_Image.special_point[B].y;
//            last_D_point.x = Total_Image.special_point[D].x;
//            last_D_point.y = Total_Image.special_point[D].y;
//            break;
//        case right_round_about_status1_5:
//        case right_round_about_status2:
//        case right_round_about_status3:
//            Draw_Ray_Line(Border_Image[0], last_B_point.x,last_B_point.y, \
//                                           last_D_point.x,last_D_point.y, Border_Imag_X);
//            break;
//        case right_round_about_status4:
//            Draw_Straight_Line(Border_Image[0], 0, 59, Total_Image.special_point[L].x, Total_Image.special_point[L].y, Border_Imag_X);
//            break;
//        case right_round_about_status5:
//            Draw_Ray_Line(Border_Image[0], 0, 59, Total_Image.special_point[L].x, Total_Image.special_point[L].y, Border_Imag_X);
//            last_L_point.x = Total_Image.special_point[L].x;
//            last_L_point.y = Total_Image.special_point[L].y;
//            break;
//        case right_round_about_status6:
//            Draw_Ray_Line(Border_Image[0], 0, 59, last_L_point.x, last_L_point.y, Border_Imag_X);
//            break;
//        case right_round_about_status8:
//            Draw_Ray_Line(Border_Image[0], Total_Image.special_point[A].x, Total_Image.special_point[A].y, \
//                                           Total_Image.special_point[C].x, Total_Image.special_point[C].y, Border_Imag_X);
//            last_A_point.x = Total_Image.special_point[A].x;
//            last_A_point.y = Total_Image.special_point[A].y;
//            last_C_point.x = Total_Image.special_point[C].x;
//            last_C_point.y = Total_Image.special_point[C].y;
//            break;
//        case right_round_about_status8_5:
//        case right_round_about_status9:
//            Draw_Ray_Line(Border_Image[0], last_A_point.x, last_A_point.y, last_C_point.x, last_C_point.y, Border_Imag_X);
//            break;
//        case right_round_about_status11:
//            Draw_Ray_Line(Border_Image[0], Total_Image.special_point[B].x, Total_Image.special_point[B].y, \
//                                           Total_Image.special_point[L].x, Total_Image.special_point[L].y, Border_Imag_X);
//            last_B_point.x = Total_Image.special_point[B].x;
//            last_B_point.y = Total_Image.special_point[B].y;
//            last_L_point.x = Total_Image.special_point[L].x;
//            last_L_point.y = Total_Image.special_point[L].y;
//            break;
//        case right_round_about_status12:
//            Draw_Ray_Line(Border_Image[0], last_B_point.x, last_B_point.y, last_L_point.x, last_L_point.y, Border_Imag_X);
//            break;
        /* ******************************************************************************************************** */

        /* ******************************************左环岛状态******************************************************* */
        case left_round_about_status1:
            top_x_store = Draw_Ray_Line(Binary_Image[0], Total_Image.special_point[A].x,Total_Image.special_point[A].y, \
                                           Total_Image.special_point[C].x,Total_Image.special_point[C].y, Binary_Imag_X);
            last_A_point.x = Total_Image.special_point[A].x;
            last_A_point.y = Total_Image.special_point[A].y;
            last_C_point.x = Total_Image.special_point[C].x;
            last_C_point.y = Total_Image.special_point[C].y;
            break;
        case left_round_about_status1_5:
        case left_round_about_status2:
            Draw_Straight_Line(Binary_Image[0], last_C_point.x,59, top_x_store,0, Binary_Imag_X);
            break;
        case left_round_about_status3:
            Draw_Straight_Line(Binary_Image[0], last_C_point.x,59, top_x_store-5,0, Binary_Imag_X);
            break;
        case left_round_about_status4:
        case left_round_about_status5:
            Draw_Curve(Binary_Image[0], Total_Image.special_point[B].x-8, Total_Image.special_point[B].y, 43, 21, Binary_Imag_X);
            last_B_point.x = Total_Image.special_point[B].x;
            last_B_point.y = Total_Image.special_point[B].y;
            break;
        case left_round_about_status6:
            Draw_Curve(Binary_Image[0], last_B_point.x-19, last_B_point.y, 38, 21, Binary_Imag_X);
            break;
        case left_round_about_status8:
            Draw_Curve(Binary_Image[0], Total_Image.special_point[D].x, Total_Image.special_point[D].y, \
                                                            18, 9, Binary_Imag_X);
            last_D_point.x = Total_Image.special_point[D].x;
            last_D_point.y = Total_Image.special_point[D].y;
            break;
        case left_round_about_status8_5:
        case left_round_about_status9:
            Draw_Curve(Binary_Image[0], last_D_point.x, 59, 18, 9, Binary_Imag_X);
            break;
        case left_round_about_status10:
            Draw_Straight_Line(Binary_Image[0], 21, 59, 3, 30, Binary_Imag_X);
            break;
        case left_round_about_status11:
            Draw_Straight_Line(Binary_Image[0], 19, 59, 35, 30, Binary_Imag_X);
//            Draw_Straight_Line(Binary_Image[0], Total_Image.special_point[A].x, Total_Image.special_point[A].y, \
//                                           Total_Image.special_point[J].x, Total_Image.special_point[J].y, Binary_Imag_X);
//            last_A_point.x = Total_Image.special_point[A].x;
//            last_A_point.y = Total_Image.special_point[A].y;
//            last_J_point.x = Total_Image.special_point[J].x;
//            last_J_point.y = Total_Image.special_point[J].y;
            break;
        case left_round_about_status12:
            Draw_Straight_Line(Binary_Image[0], last_A_point.x, last_A_point.y, last_J_point.x, last_J_point.y, Binary_Imag_X);
            break;
        /* ******************************************************************************************************** */
        default:
            break;
    }
}

/*
 * @Brief 补全中心线图像
 * @param 输入图像地址
 * @param 输入图像宽度
 * @param 输入图像高度
 * */
void Fixed_Middle_Line(Uint8 road_type, Uint8 Image_x, Uint8 Image_y)
{
    if (road_type == road_normal || road_type == right_round_about_status7 || road_type == right_round_about_status10 || road_type == left_round_about_status7)
    {
        if (Total_Image.left_line_cnt < Total_Image.right_line_cnt)
        {
            if (Total_Image.right_line_cnt - Total_Image.left_line_cnt > 49)
            {
                for (Uint8 i = 0; i < 41; i++)
                {
                    Total_Image.middle_border_line[i] = Total_Image.right_border_line[i] - HARF_ROAD_WIDTH[i]/2;
                }
                Total_Image.middle_line_cnt = 41;
            }
            else
            {
                for (Uint8 i = 0; i < Total_Image.left_line_cnt; i++)
                {
                    Total_Image.middle_border_line[i] = (Total_Image.left_border_line[i]+Total_Image.right_border_line[i])/2;
                }
                Total_Image.middle_line_cnt = Total_Image.left_line_cnt;
            }
//            if (Total_Image.left_line_cnt < 10)
//            {
//                for (Uint8 i = 0; i < 41; i++)
//                {
//                    Total_Image.middle_border_line[i] = Total_Image.right_border_line[i] - HARF_ROAD_WIDTH[i]/2;
//                }
//                Total_Image.middle_line_cnt = 41;
//            }
//            else
//            {
//                for (Uint8 i = 0; i < Total_Image.left_line_cnt; i++)
//                {
//                    Total_Image.middle_border_line[i] = (Total_Image.left_border_line[i]+Total_Image.right_border_line[i])/2;
//                }
//                Total_Image.middle_line_cnt = Total_Image.left_line_cnt;
//            }

        }
        else
        {
            if (Total_Image.left_line_cnt - Total_Image.right_line_cnt > 49)
            {
                for (Uint8 i = 0; i < 41; i++)
                {
                    Total_Image.middle_border_line[i] = Total_Image.left_border_line[i] + HARF_ROAD_WIDTH[i]/2;
                }
                Total_Image.middle_line_cnt = 41;
            }
            else
            {
                for (Uint8 i = 0; i < Total_Image.right_line_cnt; i++)
                {
                    Total_Image.middle_border_line[i] = (Total_Image.left_border_line[i]+Total_Image.right_border_line[i])/2;
                }
                Total_Image.middle_line_cnt = Total_Image.right_line_cnt;
            }
//            if (Total_Image.right_line_cnt < 10)
//            {
//                for (Uint8 i = 0; i < 41; i++)
//                {
//                    Total_Image.middle_border_line[i] = Total_Image.left_border_line[i] + HARF_ROAD_WIDTH[i]/2;
//                }
//                Total_Image.middle_line_cnt = 41;
//            }
//            else
//            {
//                for (Uint8 i = 0; i < Total_Image.right_line_cnt; i++)
//                {
//                    Total_Image.middle_border_line[i] = (Total_Image.left_border_line[i]+Total_Image.right_border_line[i])/2;
//                }
//                Total_Image.middle_line_cnt = Total_Image.right_line_cnt;
//            }
        }
    }
    else
    {
        Re_Edge_Extraction(Binary_Image[0], Border_Imag_X, Border_Imag_Y);
        if (Total_Image.left_line_cnt < Total_Image.right_line_cnt)
        {
            if (Total_Image.right_line_cnt - Total_Image.left_line_cnt > 49)
            {
                for (Uint8 i = 0; i < 41; i++)
                {
                    Total_Image.middle_border_line[i] = Total_Image.right_border_line[i] - HARF_ROAD_WIDTH[i]/2;
                }
                Total_Image.middle_line_cnt = 41;
            }
            else
            {
                for (Uint8 i = 0; i < Total_Image.left_line_cnt; i++)
                {
                    Total_Image.middle_border_line[i] = (Total_Image.left_border_line[i]+Total_Image.right_border_line[i])/2;
                }
                Total_Image.middle_line_cnt = Total_Image.left_line_cnt;
            }
//            if (Total_Image.left_line_cnt < 10)
//            {
//                for (Uint8 i = 0; i < 41; i++)
//                {
//                    Total_Image.middle_border_line[i] = Total_Image.right_border_line[i] - HARF_ROAD_WIDTH[i]/2;
//                }
//                Total_Image.middle_line_cnt = 41;
//            }
//            else
//            {
//                for (Uint8 i = 0; i < Total_Image.left_line_cnt; i++)
//                {
//                    Total_Image.middle_border_line[i] = (Total_Image.left_border_line[i]+Total_Image.right_border_line[i])/2;
//                }
//                Total_Image.middle_line_cnt = Total_Image.left_line_cnt;
//            }

        }
        else
        {
            if (Total_Image.left_line_cnt - Total_Image.right_line_cnt > 49)
            {
                for (Uint8 i = 0; i < 41; i++)
                {
                    Total_Image.middle_border_line[i] = Total_Image.left_border_line[i] + HARF_ROAD_WIDTH[i]/2;
                }
                Total_Image.middle_line_cnt = 41;
            }
            else
            {
                for (Uint8 i = 0; i < Total_Image.right_line_cnt; i++)
                {
                    Total_Image.middle_border_line[i] = (Total_Image.left_border_line[i]+Total_Image.right_border_line[i])/2;
                }
                Total_Image.middle_line_cnt = Total_Image.right_line_cnt;
            }
//            if (Total_Image.right_line_cnt < 10)
//            {
//                for (Uint8 i = 0; i < 41; i++)
//                {
//                    Total_Image.middle_border_line[i] = Total_Image.left_border_line[i] + HARF_ROAD_WIDTH[i]/2;
//                }
//                Total_Image.middle_line_cnt = 41;
//            }
//            else
//            {
//                for (Uint8 i = 0; i < Total_Image.right_line_cnt; i++)
//                {
//                    Total_Image.middle_border_line[i] = (Total_Image.left_border_line[i]+Total_Image.right_border_line[i])/2;
//                }
//                Total_Image.middle_line_cnt = Total_Image.right_line_cnt;
//            }
        }
    }
}

/*
 * @Brief 计算中心线曲率,输出偏差
 * @param 中线数组的长度
 * @param 前瞻点的位置
 * */
Uint8 Output_Error(Uint8 stack_length, Uint8 prospect)
{
    ARRAY data1, data2, data3;

    if (Total_Image.three_way_status == enter_right_three_way)
    {
        prospect = prospect + 3;
    }
    if (prospect < stack_length)
    {
        data1.x = Total_Image.middle_border_line[prospect-1];
        data2.x = Total_Image.middle_border_line[prospect];
        data3.x = Total_Image.middle_border_line[prospect+1];
        data1.x = (data1.x + data2.x+data3.x)/3;
        data2.y = (58-prospect);
        if (data1.x > 46) Total_Image.OUTPUT_ERROR = (data1.x - 46)*1.2;
        else Total_Image.OUTPUT_ERROR = -(46 - data1.x)*1.2;
    }
    else
    {
        data1.x = Total_Image.middle_border_line[stack_length];
        data2.x = Total_Image.middle_border_line[stack_length-1];
        data3.x = Total_Image.middle_border_line[stack_length-2];
        data1.x = (data1.x + data2.x+data3.x)/3;
        data2.y = (58-stack_length-1);
        if (data1.x > 46) Total_Image.OUTPUT_ERROR = (data1.x - 46)*1.2;
        else Total_Image.OUTPUT_ERROR = -(46 - data1.x)*1.2;
    }

    if (Total_Image.road_type == left_round_about_status1_5 || Total_Image.road_type == left_round_about_status2 || Total_Image.road_type == left_round_about_status3)
    {
        Total_Image.OUTPUT_ERROR = Total_Image.OUTPUT_ERROR - 3;
    }

    return data2.y;
}
