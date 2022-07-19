#ifndef MY_IMAG_PROCESS_H
#define MY_IMAG_PROCESS_H

#include "MY_Common.h"
#include "zf_stm_systick.h"
#include "SEEKFREE_18TFT.h"
#include "attitude_algorithm.h"
#include "Draw_Line.h"

#define Cut_Imag_X                 94
#define Cut_Imag_Y                 60

#define Binary_Imag_X              94
#define Binary_Imag_Y              60

#define Border_Imag_X              94
#define Border_Imag_Y              60

#define Queue_Size                 2
#define Stack_Size                 4

#define A                          0
#define B                          1
#define C                          2
#define D                          3
#define E                          4
#define F                          5
#define G                          6
#define H                          7
#define I                          8
#define J                          9
#define L                          10

enum error_type
{
  error_normal,
  A_point_error,
  B_point_error,
  C_point_to_border,
  D_point_to_border,
  E_point_error,
  F_point_error,
  G_point_to_border,
  H_point_to_border,
  I_point_to_border,
  J_point_to_border,
  L_point_to_border
};

enum road_type
{
  start,
  road_normal,
  before_crossing_road1,
  before_crossing_road2,
  before_crossing_road3,
  before_crossing_road4,
  in_crossing_road1,
  in_crossing_road2,
  in_crossing_road3,
  in_crossing_road4,
  //三岔路
  before_right_three_way_road,
  in_right_three_way_road,
  before_left_three_way_road,
  in_left_three_way_road,
  //右环岛
  right_round_about_status1,
  right_round_about_status1_5,
  right_round_about_status2,
  right_round_about_status3,
  right_round_about_status4,
  right_round_about_status5,
  right_round_about_status6,
  right_round_about_status7,
  right_round_about_status8,
  right_round_about_status8_5,
  right_round_about_status9,
  right_round_about_status10,
  right_round_about_status11,
  right_round_about_status12,
  right_round_about_status13,
  //左环岛
  left_round_about_status1,
  left_round_about_status1_5,
  left_round_about_status2,
  left_round_about_status3,
  left_round_about_status4,
  left_round_about_status5,
  left_round_about_status6,
  left_round_about_status7,
  left_round_about_status8,
  left_round_about_status8_5,
  left_round_about_status9,
  left_round_about_status10,
  left_round_about_status11,
  left_round_about_status12,
  left_round_about_status13,
  stop
};

enum three_way_status
{
  three_way_normal,
  enter_right_three_way,
  exit_right_three_way,
  enter_left_three_way,
  exit_left_three_way
};

enum round_road_status
{
  round_road_normal,
  round_road_finishs
};

//十字路口的状态
enum crossing_road_status
{
  crossing_road_normal,
  first_crossing_road_way_out,
  second_crossing_road_way_in,
  second_crossing_road_way_out
};

typedef struct _otsu_filter_
{
        Uint16 OTSUThreshold;
}OTSU_FLITER;

typedef struct _total_image_
{
        ARRAY special_point[11];//分别为A,B,C,D,E,F,G,H,I,J,K
        Uint8 road_type;
        Uint8 error;
        Uint8 middle_line_pointer;
        Uint8 left_white_line;
        Uint8 right_white_line;
        Uint8 white_line;
        Uint8 three_way_status;
        Uint8 crossing_road_status;
        Uint8 round_road_status;
        Uint8 left_border_line[90];
        Uint8 right_border_line[90];
        Uint8 middle_border_line[90];
        Uint8 left_line_cnt;
        Uint8 right_line_cnt;
        Uint8 middle_line_cnt;
        Int8 OUTPUT_ERROR;
}TOTAL_IMAGE;

//判断C,D点的队列
typedef struct _c_d_queue_
{
        ARRAY data[Queue_Size];
        Int8  front;
        Int8  rear;
}C_D_QUEUE;

//判断E,F点的栈
typedef struct _e_f_stack_
{
        ARRAY data[Stack_Size];
        Int8  top;
}E_F_STACK;

extern Uint8    Cut_Image[Cut_Imag_Y][Cut_Imag_X];
extern Uint8    Binary_Image[Binary_Imag_Y][Binary_Imag_X];
extern const Uint8 HARF_ROAD_WIDTH[60];
extern OTSU_FLITER OTSU_Struct;
extern TOTAL_IMAGE Total_Image;

/* ***********************队列相关函数*********************************** */
void Queue_Init(C_D_QUEUE *Q);
void Enter_Queue(C_D_QUEUE *Q, Uint8 data_x, Uint8 data_y);
void Pop_Queue(C_D_QUEUE *Q, ARRAY *data_out);
/* ********************************************************************** */

/* ************************栈相关函数************************************ */
void Stack_Init(E_F_STACK *S);
void Enter_Stack(E_F_STACK *S, Uint8 data_x, Uint8 data_y);
void Pop_Stack(E_F_STACK *S, ARRAY *data_out);
Uint8 Stack_Full(E_F_STACK *S);
Uint8 Stack_Length(E_F_STACK *S);
/* ********************************************************************** */

/* **************************全局初始化*********************************** */
void Global_Init(void);
/* ********************************************************************** */

void Image_Cut(Uint8 *Imag_In, Uint8 *Imag_Out);
void OTSU_Filter(Uint8 *Image_In, Uint8 *Image_Out, Uint8 Image_x, Uint8 Image_y);
void Edge_Extraction(Uint8 *Image_In, Uint8 Image_x, Uint8 Image_y);
void Re_Edge_Extraction(Uint8 *Image_In, Uint8 Image_x, Uint8 Image_y);

#endif
