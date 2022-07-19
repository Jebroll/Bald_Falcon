/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2022,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             zf_device_imu963ra
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ3184284598)
* @version          查看doc内version文件 版本说明
* @Software         ADS v1.5.2
* @Target core      TC264
* @Taobao           https://seekfree.taobao.com/
* @date             2022-05-04
* @note             接线定义：
*                   ------------------------------------
*                                                   模块管脚            单片机管脚
*                   // 硬件 SPI 引脚
*                   SCL/SPC             查看 zf_device_imu963ra.h 中 IMU963RA_SPC_PIN 宏定义
*                   SDA/DSI             查看 zf_device_imu963ra.h 中 IMU963RA_SDI_PIN 宏定义
*                   SA0/SDO             查看 zf_device_imu963ra.h 中 IMU963RA_SDO_PIN 宏定义
*                   CS                  查看 zf_device_imu963ra.h 中 IMU963RA_CS_PIN  宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                                                   其余引脚悬空
*
*                   // 软件 IIC 引脚
*                   SCL/SPC             查看 SEEKFREE_IIC.h 中 SEEKFREE_SCL 宏定义
*                   SDA/DSI             查看 SEEKFREE_IIC.h 中 SEEKFREE_SDA 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                                                   其余引脚悬空
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_stm_systick.h"
#include "zf_gpio.h"
#include "zf_spi.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_IMU963RA.h"
 
int16 imu963ra_gyro_x, imu963ra_gyro_y, imu963ra_gyro_z;
int16 imu963ra_acc_x,  imu963ra_acc_y,  imu963ra_acc_z;
int16 imu963ra_mag_x,  imu963ra_mag_y,  imu963ra_mag_z;

#if IMU963RA_USE_SOFT_IIC
#define imu963ra_write_acc_gyro_register(reg,data)       simiic_write_reg(IMU963RA_DEV_ADDR, reg, data)
#define imu963ra_read_acc_gyro_register(reg)             simiic_read_reg (IMU963RA_DEV_ADDR, reg, SIMIIC)
#define imu963ra_read_acc_gyro_registers(reg,data,len)   simiic_read_regs(IMU963RA_DEV_ADDR, reg, data, len, SIMIIC)
#else

//-------------------------------------------------------------------------------------------------------------------
// @brief       IMU963RA 写寄存器 内部调用
// @param       reg             寄存器地址
// @param       data            数据
// @return      void
//-------------------------------------------------------------------------------------------------------------------
static void imu963ra_write_acc_gyro_register(uint8 reg, uint8 data)
{
    uint8 dat[2];
    
    dat[0] = reg | IMU963RA_SPI_W;
    dat[1] = data;
    
    spi_mosi(IMU963RA_SPI,IMU963RA_CS_PIN,dat,dat,2,1);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       IMU963RA 读寄存器 内部调用
// @param       reg             寄存器地址
// @return      uint8           数据
//-------------------------------------------------------------------------------------------------------------------
static uint8 imu963ra_read_acc_gyro_register(uint8 reg)
{
    uint8 dat[2];

    dat[0] = reg | IMU963RA_SPI_R;
    dat[1] = 0;
    
    spi_mosi(IMU963RA_SPI,IMU963RA_CS_PIN,dat,dat,2,1);
        
    return dat[1];
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       IMU963RA 读数据 内部调用
// @param       reg             寄存器地址
// @param       data            数据缓冲区
// @param       len             数据长度
// @return      void
//-------------------------------------------------------------------------------------------------------------------
static void imu963ra_read_acc_gyro_registers(uint8 *data, uint32 len)
{
    spi_mosi(IMU963RA_SPI, IMU963RA_CS_PIN, data, data, len, 1);
}
#endif

//-------------------------------------------------------------------------------------------------------------------
// @brief       IMU963RA作为IIC主机向磁力计写数据，内部调用
// @param       void
// @return      void
// Sample usage:                内部调用，用户无需关心
//-------------------------------------------------------------------------------------------------------------------
void imu963ra_write_mag_register(uint8 addr, uint8 reg, uint8 data)
{
    addr = addr << 1;
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x00);    // 从机0配置清除
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_ADD, addr | 0);   // 设置地磁计地址（注意这里需要设置8位的I2C地址） 0x2C
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_SUBADD, reg);     // 需要写入的寄存器地址
    imu963ra_write_acc_gyro_register(IMU963RA_DATAWRITE_SLV0, data); // 需要写入的数据
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x4C);  // 仅在第一个周期启用通讯 开启上拉 I2C主机使能
    
    //等待通讯成功
    while(0 == (0x80 & imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER)))
    {
        systick_delay_ms(STM0, 2);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       IMU963RA作为IIC主机向磁力计读数据，内部调用
// @param       void
// @return      void
// Sample usage:                内部调用，用户无需关心
//-------------------------------------------------------------------------------------------------------------------
uint8 imu963ra_read_mag_register(uint8 addr, uint8 reg)
{
    addr = addr << 1;
    
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_ADD, addr | 1);   // 设置地磁计地址（注意这里需要设置8位的I2C地址） 0x2C
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_SUBADD, reg);     // 需要读取的寄存器地址
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x01);    
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x4C);  // 仅在第一个周期启用通讯 开启上拉 I2C主机使能
    
    //等待通讯成功
    while(0 == (0x01 & imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER)))
    {
        systick_delay_ms(STM0, 2);
    }
    
    return (imu963ra_read_acc_gyro_register(IMU963RA_SENSOR_HUB_1)); // 返回读取到的数据
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       IMU963RA作为IIC主机向磁力计自动写数据，内部调用
// @param       void
// @return      void
// Sample usage:                内部调用，用户无需关心
//-------------------------------------------------------------------------------------------------------------------
void imu963ra_connect_mag(uint8 addr, uint8 reg)
{
    addr = addr << 1;
    
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_ADD, addr | 1);   // 设置地磁计地址（注意这里需要设置8位的I2C地址） 0x2C
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_SUBADD, reg);     // 需要读取的寄存器地址
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x06);    
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x6C);  // 仅在第一个周期启用通讯 开启上拉 I2C主机使能
}   


//-------------------------------------------------------------------------------------------------------------------
// @brief       IMU963RA 六轴自检 内部调用
// @param       void
// @return      uint8           1-自检失败 0-自检成功
//-------------------------------------------------------------------------------------------------------------------
static uint8 imu963ra_acc_gyro_self_check (void)
{
    uint8 dat = 0;
//    uint16 timeout_count = 0;

    while(0x6B != dat)                                          // 判断 ID 是否正确
    {
//        if(timeout_count++ > IMU963RA_TIMEOUT_COUNT)
//            return 1;
        dat = imu963ra_read_acc_gyro_register(IMU963RA_WHO_AM_I);
        systick_delay_ms(STM0, 1);
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       IMU963RA 磁力计自检 内部调用
// @param       void
// @return      uint8           1-自检失败 0-自检成功
//-------------------------------------------------------------------------------------------------------------------
static uint8 imu963ra_mag_self_check (void)
{
    uint8 dat = 0;
//    uint16 timeout_count = 0;

    while(0xff != dat)                                              // 判断 ID 是否正确
    {
//        if(timeout_count++ > IMU963RA_TIMEOUT_COUNT)
//            return 1;
        dat = imu963ra_read_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CHIP_ID);
        systick_delay_ms(STM0, 1);
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       获取 IMU963RA 加速度计数据
// @param       void
// @return      void
// Sample usage:                执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void imu963ra_get_acc (void)
{
    struct
    {
        uint8 reg;
        uint8 dat[6];
    }buf;

#if IMU963RA_USE_SOFT_IIC
    imu963ra_read_acc_gyro_registers(IMU963RA_OUTX_L_A, &buf.dat[0], 7);
#else
    buf.reg = IMU963RA_OUTX_L_A | IMU963RA_SPI_R;
    imu963ra_read_acc_gyro_registers(&buf.reg, 7);
#endif
   
    imu963ra_acc_x = (int16)(((uint16)buf.dat[1]<<8 | buf.dat[0]));
    imu963ra_acc_y = (int16)(((uint16)buf.dat[3]<<8 | buf.dat[2]));
    imu963ra_acc_z = (int16)(((uint16)buf.dat[5]<<8 | buf.dat[4]));
}


//-------------------------------------------------------------------------------------------------------------------
// @brief       获取IMU963RA陀螺仪数据
// @param       void
// @return      void
// Sample usage:                执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void imu963ra_get_gyro (void)
{
    struct
    {
        uint8 reg;
        uint8 dat[6];
    }buf;

#if IMU963RA_USE_SOFT_IIC
    imu963ra_read_acc_gyro_registers(IMU963RA_OUTX_L_G, &buf.dat[0], 6);
#else
    buf.reg = IMU963RA_OUTX_L_G | IMU963RA_SPI_R;
    imu963ra_read_acc_gyro_registers(&buf.reg, 7);
#endif
    
    imu963ra_gyro_x = (int16)(((uint16)buf.dat[1]<<8 | buf.dat[0]));
    imu963ra_gyro_y = (int16)(((uint16)buf.dat[3]<<8 | buf.dat[2]));
    imu963ra_gyro_z = (int16)(((uint16)buf.dat[5]<<8 | buf.dat[4]));
}


//-------------------------------------------------------------------------------------------------------------------
// @brief       获取 IMU963RA 磁力计数据
// @param       void
// @return      void
// Sample usage:                执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void imu963ra_get_mag (void)
{
    uint8 temp_status;
    struct
    {
        uint8 reg;
        uint8 dat[6];
    }buf;

    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x40);
    temp_status = imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER);
    if(0x01 & temp_status)
    {
        
    #if IMU963RA_USE_SOFT_IIC
        imu963ra_read_acc_gyro_registers(IMU963RA_SENSOR_HUB_1, &buf.dat[0], 6);
    #else
        buf.reg = IMU963RA_SENSOR_HUB_1 | IMU963RA_SPI_R;
        imu963ra_read_acc_gyro_registers(&buf.reg, 7);
    #endif
        
        imu963ra_mag_x = (int16)(((uint16)buf.dat[1]<<8 | buf.dat[0]));
        imu963ra_mag_y = (int16)(((uint16)buf.dat[3]<<8 | buf.dat[2]));
        imu963ra_mag_z = (int16)(((uint16)buf.dat[5]<<8 | buf.dat[4]));
    }
    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       初始化 IMU963RA
// @param       void
// @return      uint8           1-初始化失败 0-初始化成功
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 imu963ra_init (void)
{

    systick_delay_ms(STM0, 10);                                                // 上电延时

#if IMU963RA_USE_SOFT_IIC
    simiic_delay_set(IMU963RA_SOFT_IIC_DELAY);
    simiic_init();
#else
    spi_init(IMU963RA_SPI, IMU963RA_SPC_PIN, IMU963RA_SDI_PIN, IMU963RA_SDO_PIN, IMU963RA_CS_PIN, 0, 10*1000*1000);//硬件SPI初始化

#endif
    
    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);    // 关闭HUB寄存器访问
    imu963ra_write_acc_gyro_register(IMU963RA_CTRL3_C, 0x01);            // 复位设备
    systick_delay_ms(STM0, 2);
    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);    // 关闭HUB寄存器访问
    imu963ra_acc_gyro_self_check();                                     // 六轴自检


    imu963ra_write_acc_gyro_register(IMU963RA_INT1_CTRL, 0x03);         // 开启陀螺仪 加速度数据就绪中断
    imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x4C);          // 设置加速度计量程±8G以及数据输出速率104hz 以及加速度信息从第一级滤波器输出
    //IMU963RA_CTRL1_XL寄存器
    //设置为:0x40 加速度量程为:±2G       获取到的加速度计数据 除以16393，可以转化为带物理单位的数据，单位：g(m/s^2)
    //设置为:0x48 加速度量程为:±4G      获取到的加速度计数据 除以8197， 可以转化为带物理单位的数据，单位：g(m/s^2)
    //设置为:0x4C 加速度量程为:±8G      获取到的加速度计数据 除以4098， 可以转化为带物理单位的数据，单位：g(m/s^2)
    //设置为:0x44 加速度量程为:±16G     获取到的加速度计数据 除以2049， 可以转化为带物理单位的数据，单位：g(m/s^2)

    imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x6C);           // 设置陀螺仪计量程±2000dps以及数据输出速率416hz
    //ICM20602_GYRO_CONFIG寄存器
    //设置为:0x62 陀螺仪量程为:±125dps  获取到的陀螺仪数据除以228.6，   可以转化为带物理单位的数据，单位为：°/s
    //设置为:0x60 陀螺仪量程为:±250dps   获取到的陀螺仪数据除以114.3，   可以转化为带物理单位的数据，单位为：°/s
    //设置为:0x64 陀螺仪量程为:±500dps  获取到的陀螺仪数据除以57.1，    可以转化为带物理单位的数据，单位为：°/s
    //设置为:0x68 陀螺仪量程为:±1000dps 获取到的陀螺仪数据除以28.6，    可以转化为带物理单位的数据，单位为：°/s
    //设置为:0x6C 陀螺仪量程为:±2000dps 获取到的陀螺仪数据除以14.3，    可以转化为带物理单位的数据，单位为：°/s
    //设置为:0x61 陀螺仪量程为:±4000dps 获取到的陀螺仪数据除以7.1，     可以转化为带物理单位的数据，单位为：°/s

    imu963ra_write_acc_gyro_register(IMU963RA_CTRL3_C, 0x44);            // 使能陀螺仪数字低通滤波器
    imu963ra_write_acc_gyro_register(IMU963RA_CTRL4_C, 0x02);            // 使能数字低通滤波器
    imu963ra_write_acc_gyro_register(IMU963RA_CTRL5_C, 0x00);            // 加速度计与陀螺仪四舍五入
    imu963ra_write_acc_gyro_register(IMU963RA_CTRL6_C, 0x00);            // 开启加速度计高性能模式 陀螺仪低通滤波 133hz
    imu963ra_write_acc_gyro_register(IMU963RA_CTRL7_G, 0x00);            // 开启陀螺仪高性能模式 关闭高通滤波
    imu963ra_write_acc_gyro_register(IMU963RA_CTRL9_XL, 0x01);           // 关闭I3C接口

    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x40);    // 开启HUB寄存器访问 用于配置地磁计
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x80);      // 复位I2C主机
    systick_delay_ms(STM0, 2);
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x00);      // 清除复位标志
    systick_delay_ms(STM0, 2);
    
    imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL2, 0x80);    // 复位连接的外设
    systick_delay_ms(STM0, 2);
    imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL2, 0x00);
    systick_delay_ms(STM0, 2);
    imu963ra_mag_self_check();                                                      //磁力计自检

    imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL1, 0x19);    // 输出速率100hz 连续模式
    //IMU963RA_MAG_ADDR寄存器
    //设置为:0x19 磁力计量程为:8G     获取到的加速度计数据 除以3000， 可以转化为带物理单位的数据，单位：G(高斯)
    //设置为:0x09 磁力计量程为:2G     获取到的加速度计数据 除以12000，可以转化为带物理单位的数据，单位：G(高斯)

    imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_FBR, 0x01);
    imu963ra_connect_mag(IMU963RA_MAG_ADDR, IMU963RA_MAG_OUTX_L);
    
    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);                            // 关闭HUB寄存器访问

    systick_delay_ms(STM0, 20); // 等待磁力计获取数据

    return 0;
}
