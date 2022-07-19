#ifndef MY_COMMON_H
#define MY_COMMON_H

#include "string.h"

#define Border_Imag_X              94
#define Border_Imag_Y              60

//数据类型声明
typedef unsigned char       Uint8;   //  8 bits
typedef unsigned short int  Uint16;  // 16 bits
typedef unsigned long int   Uint32;  // 32 bits
typedef unsigned long long  Uint64;  // 64 bits

typedef char                Int8;    //  8 bits
typedef short int           Int16;   // 16 bits
typedef long  int           Int32;   // 32 bits
typedef long  long          Int64;   // 64 bits

typedef volatile Int8       Vint8;   //  8 bits
typedef volatile Int16      Vint16;  // 16 bits
typedef volatile Int32      Vint32;  // 32 bits
typedef volatile Int64      Vint64;  // 64 bits

typedef volatile Uint8      Vuint8;  //  8 bits
typedef volatile Uint16     Vuint16; // 16 bits
typedef volatile Uint32     Vuint32; // 32 bits
typedef volatile Uint64     Vuint64; // 64 bits

typedef struct _array_
{
        Uint8 x;
        Uint8 y;
}ARRAY;

extern Uint8    Border_Image[Border_Imag_Y][Border_Imag_X];

#define AT_ITCM_SECTION_INIT(var) __attribute__((section("ITCM_NonCacheable.init"))) var//定义将代码放在ITCM的方式

Uint8 ABS(Int16 dat);//求绝对值函数
Uint8 My_Sqrt(Uint16 x);

#endif
