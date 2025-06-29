/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： i2c_driver.c
 * 文件标识：
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： YangZJ
 * 完成日期： 220826
 *
 *******************************************************************************/
#include "i2c_driver.h"
// 库函数接口
void i2c_DriverInit(I2C_TypeDef *I2Cx, DMA_RegTypeDef *DMA_CHx, u32 BaudRate, u8 ADDR); // I2C驱动库初始化
void i2c_DriverMasterRx(u8 addr, u8 *data, u8 len);                                     // 主模式接收
void i2c_DriverMasterTx(u8 addr, u8 *data, u8 len);                                     // 主模式发送
void i2c_DriverMasterSetRxCallback(void (*fun)(u8));                                    // 主模式接收完成回调设置
void i2c_DriverMasterSetTxCallback(void (*fun)(u8));                                    // 主模式发送完成回调设置
void i2c_DriverMasterWait(void);                                                        // 主模式等待发送完成
void i2c_DriverSlaveSetRxCallback(void (*fun)(void));                                   // 从模式接收完成回调设置
void i2c_DriverSlaveSetTxCallback(void (*fun)(void));                                   // 从模式发送完成回调设置
void i2c_DriverSlaveSetTxData(u8 *data, u8 len);                                        // 从模式设置待发送的数据
void i2c_DriverSlaveGetRxData(u8 *data, u8 len);                                        // 从模式读取刚接收的数据

// I2C驱动库变量
static void i2c_DriverVoidFunctionU8(u8 state); // 空回调函数
static void i2c_DriverVoidFunctionVoid(void);   // 空回调函数

static void (*i2c_DriverMasterRxData)(u8 state) = i2c_DriverVoidFunctionU8; // 主模式接收完成回调函数指针
static void (*i2c_DriverMasterTxData)(u8 state) = i2c_DriverVoidFunctionU8; // 主模式发送完成回调函数指针
static void (*i2c_DriverSlaveRxData)(void) = i2c_DriverVoidFunctionVoid;    // 从模式接收完成回调函数指针
static void (*i2c_DriverSlaveTxData)(void) = i2c_DriverVoidFunctionVoid;    // 从模式接收完成回调函数指针
static I2C_TypeDef *i2c_Driver_I2Cx;                                        // I2C寄存器指针
static DMA_RegTypeDef *i2c_Driver_DMA_CHx;                                  // DMA通道寄存器指针
static u8 i2c_Driver_Slave_Rx_Data[64] = {0};                               // 从模式接收数据缓冲
static u8 i2c_Driver_Slave_Tx_Data[64] = {0};                               // 从模式发送数据缓冲
static u8 i2c_Driver_Slave_Addr;                                            // 从模式本机地址
static u8 i2c_Driver_Slave_Flg = 0;                                         // 1 发送  2 接收
static u8 i2c_Driver_Master_Flg = 0;                                        // 1 发送  2 接收
static volatile u8 i2c_Driver_Run_Flg = 1;                                  // 1 忙碌  2 空闲
static volatile u8 i2c_DriverNeedSize;                                      // i2c还需要发送或接受的数据，用于处理数据超过32位的情况
static volatile u8 i2c_DriverContinuousModeFlg;                             // 1 连续模式  0 普通模式

/*
    I2C驱动库   初始化
    输入参数
                I2Cx        指向I2C模块的指针
                DMA_CHx     指向DMA某一个通道的指针
                BaudRate    作为主机发送的波特率
                ADDR        作为从机的地址，7位,0-127
*/
void i2c_DriverInit(I2C_TypeDef *I2Cx, DMA_RegTypeDef *DMA_CHx, u32 BaudRate, u8 ADDR)
{
    ADDR = ADDR & 0x7f;
    i2c_Driver_I2Cx = I2Cx;
    i2c_Driver_DMA_CHx = DMA_CHx;
    i2c_Driver_Slave_Addr = (u8)(ADDR << 1);
    SYS_ModuleClockCmd(SYS_Module_I2C0, ENABLE);
    SYS_SoftResetModule(SYS_Module_I2C0);

    SYS_WR_PROTECT = 0x7A83; // 解除系统寄存器写保护
    SYS_CLK_DIV0 = ((u32)48000000 + ((BaudRate * 17) >> 1)) / (BaudRate * 17) - 1;
    SYS_WR_PROTECT = 0; // 解除系统寄存器写保护

    i2c_Driver_I2Cx->ADDR = ADDR | BIT8;
    i2c_Driver_I2Cx->CFG = 0xf3;
    i2c_Driver_I2Cx->BCR = BIT5 | BIT7;
    DMA0_CTRL = 0x01; // DMA模块使能
    i2c_Driver_DMA_CHx->REN = BIT14;
    i2c_Driver_DMA_CHx->CTMS = 32;
    i2c_Driver_Run_Flg = 0;
}
/*
    I2C驱动库   主模式发送数据
    输入参数
                addr     从机的地址
                data     待发送的数据所存在的地址
                len      发送数据的长度
*/
void i2c_DriverMasterTx(u8 addr, u8 *data, u8 len)
{
    if (i2c_Driver_Run_Flg == 1)
    {
    }
    else
    {
        i2c_Driver_Run_Flg = 1;
        while (i2c_Driver_I2Cx->MSCR & BIT3)
            ; // 等待I2C空闲

        i2c_Driver_I2Cx->SCR = 0;
        len = (len) ? len : 1;                                                  // 输入限制，1-32
        len = (len > 32) ? 32 : len;                                            // 输入限制，1-32
        i2c_Driver_I2Cx->ADDR = (i2c_Driver_I2Cx->ADDR & 0x80) | (addr & 0x7f); // 从设备地址
        i2c_Driver_I2Cx->SCR = BIT2;                                            // I2C传输方向
        i2c_Driver_DMA_CHx->CCR = 0;                                            // I2C传输数据长度
        i2c_Driver_DMA_CHx->CTMS = len;                                         // DMA搬运的数据长度，实际传输数据长度为I2C->BSIZE+1
        i2c_Driver_DMA_CHx->SADR = (u32)data;                                   // DMA源地址
        i2c_Driver_DMA_CHx->DADR = (u32) & (i2c_Driver_I2Cx->DATA);             // DMA目的地址
        i2c_Driver_DMA_CHx->REN = BIT15;
        i2c_Driver_DMA_CHx->CCR = BIT6 | BIT1 | BIT0;                           // 配置DMA传输方向并使能DMA
        do
        {
            while (i2c_Driver_I2Cx->MSCR & BIT3) // 等待I2C空闲
            {
            }
            i2c_Driver_I2Cx->MSCR = 1;                  // 触发I2C发送数据
            while ((i2c_Driver_I2Cx->MSCR & BIT3) == 0) // 等待I2C的start信号
            {
            }
        } while ((i2c_Driver_I2Cx->MSCR & BIT2) == 0); // 如果没有抢到总线，则重新争抢总线
        i2c_Driver_Master_Flg = 1;
        i2c_Driver_Run_Flg = 0;
    }
}
/*
    I2C驱动库   主模式接收数据
    输入参数
                addr     从机的地址
                data     待接收的数据所存在的地址
                len      接收数据的长度
*/
void i2c_DriverMasterRx(u8 addr, u8 *data, u8 len)
{
    if (i2c_Driver_Run_Flg == 1)
    {
    }
    else
    {
        i2c_Driver_Run_Flg = 1;
        if (i2c_DriverContinuousModeFlg == 1)
        {
        }
        else
        {
            while (i2c_Driver_I2Cx->MSCR & BIT3)
                ; // 等待I2C空闲
        }
        i2c_Driver_I2Cx->SCR = 0;
        len = (len) ? len : 1; // 输入限制，1-32
        if (len > 32)
        {
            i2c_DriverNeedSize = len - 32;
            len = 32; // 输入限制，1-32
        }
        else
        {
            i2c_DriverNeedSize = 0;
            len = len; // 输入限制，1-32
        }
        i2c_Driver_I2Cx->ADDR = (i2c_Driver_I2Cx->ADDR & 0x80) | (addr & 0x7f); // 从设备地址
        i2c_Driver_I2Cx->SCR = BIT4;                                            // I2C传输方向
        i2c_Driver_DMA_CHx->CCR = 0;                                            // I2C传输数据长度
        i2c_Driver_DMA_CHx->CTMS = len;                                         // DMA搬运的数据长度，实际传输数据长度为I2C->BSIZE+1
        i2c_Driver_DMA_CHx->SADR = (u32) & (i2c_Driver_I2Cx->DATA);             // DMA源地址
        i2c_Driver_DMA_CHx->DADR = (u32)data;                                   // DMA目的地址
        i2c_Driver_DMA_CHx->REN = BIT14;
        i2c_Driver_DMA_CHx->CCR = BIT4 | BIT1 | BIT0;                           // 配置DMA传输方向并使能DMA
        if (i2c_DriverContinuousModeFlg == 1)
        {
        }
        else
        {
            do
            {
                while (i2c_Driver_I2Cx->MSCR & BIT3) // 等待I2C空闲
                {
                }
                i2c_Driver_I2Cx->MSCR = BIT0;               // 触发I2C发送数据
                while ((i2c_Driver_I2Cx->MSCR & BIT3) == 0) // 等待I2C的start信号
                {
                }
            } while ((i2c_Driver_I2Cx->MSCR & BIT2) == 0); // 如果没有抢到总线，则重新争抢总线
        }
        i2c_Driver_Master_Flg = 2;
        i2c_Driver_Run_Flg = 0;
    }
}
/*
    I2C驱动库 主模式等待发送完成
*/
void i2c_DriverMasterWait(void)
{
    while (i2c_Driver_I2Cx->MSCR & BIT3)
        ; // 等待I2C空闲
}
/*
    I2C驱动库   设置从模式发送出数据后的回调函数
    输入参数
                fun     接收完成后需要执行的回调函数，默认空函数，可以不设置
*/
void i2c_DriverSlaveSetRxCallback(void (*fun)(void))
{
    i2c_DriverSlaveRxData = fun;
}
/*
    I2C驱动库   设置从模式发送完数据后的回调函数
    输入参数
                fun     发送完成后需要执行的回调函数，默认空函数，可以不设置
*/
void i2c_DriverSlaveSetTxCallback(void (*fun)(void))
{
    i2c_DriverSlaveTxData = fun;
}
/*
    I2C驱动库   设置从模式待发送的数据
    输入参数
                data    原数据地址
                len     原数据长度
*/
void i2c_DriverSlaveSetTxData(u8 *data, u8 len)
{
    u8 i;
    for (i = 0; i < len; i++)
    {
        i2c_Driver_Slave_Tx_Data[i] = data[i];
    }
}
/*
    I2C驱动库   读取从模式接收到的数据
    输入参数
                data    原数据地址
                len     原数据长度
*/
void i2c_DriverSlaveGetRxData(u8 *data, u8 len)
{
    u8 i;
    for (i = 0; i < len; i++)
    {
        data[i] = i2c_Driver_Slave_Rx_Data[i];
    }
}

/*
    I2C驱动库   设置主模式接收完成回调函数
    输入参数
                fun    发送完成后需要执行的回调函数，默认空函数，可以不设置
*/
void i2c_DriverMasterSetRxCallback(void (*fun)(u8))
{
    i2c_DriverMasterRxData = fun;
}
/*
    I2C驱动库   设置主模式发送完成回调函数
    输入参数
                fun    发送完成后需要执行的回调函数，默认空函数，可以不设置
*/
void i2c_DriverMasterSetTxCallback(void (*fun)(u8))
{
    i2c_DriverMasterTxData = fun;
}

static void i2c_DriverSlaveTx(void)
{
    i2c_Driver_DMA_CHx->CCR = 0;    // I2C传输数据长度
    i2c_Driver_DMA_CHx->CTMS = 255; // DMA搬运的数据长度，实际传输数据长度为I2C->BSIZE+1
    if (i2c_DriverContinuousModeFlg)
    {
        i2c_Driver_DMA_CHx->SADR = (u32)i2c_Driver_Slave_Tx_Data + 32; // DMA源地址
    }
    else
    {
        i2c_Driver_DMA_CHx->SADR = (u32)i2c_Driver_Slave_Tx_Data; // DMA源地址
    }
    i2c_Driver_DMA_CHx->DADR = (u32) & (i2c_Driver_I2Cx->DATA); // DMA目的地址
    i2c_Driver_DMA_CHx->REN = BIT15;
    i2c_Driver_DMA_CHx->CCR = BIT6 | BIT1 | BIT0;               // 配置DMA传输方向并使能DMA
    i2c_Driver_DMA_CHx->REN |= BIT15;
}
static void i2c_DriverSlaveRx(void)
{
    i2c_Driver_DMA_CHx->CCR = 0;                                // 关闭DMA
    i2c_Driver_DMA_CHx->CTMS = 255;                             // DMA搬运的数据长度，实际传输数据长度为I2C->BSIZE+1
    i2c_Driver_DMA_CHx->SADR = (u32) & (i2c_Driver_I2Cx->DATA); // DMA源地址
    i2c_Driver_DMA_CHx->DADR = (u32)i2c_Driver_Slave_Rx_Data;   // DMA目的地址
    i2c_Driver_DMA_CHx->REN = BIT14;
    i2c_Driver_DMA_CHx->CCR = BIT4 | BIT1 | BIT0;               // 配置DMA传输方向并使能DMA
}
u32 callbackstate = 0;
void I2C0_IRQHandler(void);
u8 flg;
void I2C0_IRQHandler(void)
{
    u8 i2c_stop_flg = 0;
    u32 scr = 0;

    if (flg == 1)
    {
        flg = 0;
        GPIO_SetBits(GPIO0, GPIO_Pin_5);
    }
    else
    {
        flg = 1;
        GPIO_ResetBits(GPIO0, GPIO_Pin_5);
    }
    if (i2c_Driver_I2Cx->SCR & BIT1)
    {
        if (i2c_Driver_I2Cx->SCR & BIT3)
        {
            if (i2c_Driver_Master_Flg == 1) // 主模式发送
            {
                callbackstate = 1;
            }
            else if (i2c_Driver_Master_Flg == 2) // 主模式接收
            {
                callbackstate = 2;
            }
            i2c_Driver_Master_Flg = 0;
        }
    }
    if (i2c_Driver_I2Cx->SCR & BIT0)
    {

        if (i2c_Driver_I2Cx->MSCR & BIT2)
        {
            if (i2c_Driver_Master_Flg == 1)
            {
                callbackstate = 3;
            }
            else if (i2c_Driver_Master_Flg == 2)
            {
                if (i2c_DriverNeedSize != 0)
                {
                    i2c_DriverContinuousModeFlg = 1;
                    i2c_DriverMasterRx(0, (u8 *)i2c_Driver_DMA_CHx->DADR, i2c_DriverNeedSize);
                    i2c_DriverContinuousModeFlg = 0;
                    return;
                }
                callbackstate = 4;
            }
            i2c_Driver_Master_Flg = 0;
        }
        else
        {

            if ((i2c_Driver_I2Cx->SCR & (BIT5 | BIT3)) == 0)
            {
                i2c_DriverContinuousModeFlg = 1;
                i2c_DriverSlaveTx();
                i2c_DriverContinuousModeFlg = 0;
                scr = BIT4 | BIT2; // I2C传输方向
            }
        }
    }
    if ((i2c_Driver_I2Cx->MSCR & BIT2) == 0)
    {
        if (i2c_Driver_I2Cx->SCR & BIT3)
        {
            if ((i2c_Driver_I2Cx->DATA & 0xfe) == i2c_Driver_Slave_Addr)
            {
                if (i2c_Driver_I2Cx->DATA & BIT0)
                {
                    i2c_DriverSlaveTx();
                    scr = BIT4 | BIT2; // I2C传输方向
                    i2c_Driver_Slave_Flg = 1;
                }
                else
                {
                    i2c_DriverSlaveRx();
                    scr = BIT4; // I2C传输方向
                    i2c_Driver_Slave_Flg = 2;
                }
            }
        }
    }
    if (i2c_Driver_I2Cx->SCR & BIT5)
    {
        i2c_stop_flg = 1;
        if (i2c_Driver_Slave_Flg == 1)
        {
            i2c_Driver_Slave_Flg = 0;
            callbackstate = 5;
        }
        else if (i2c_Driver_Slave_Flg == 2)
        {
            i2c_Driver_Slave_Flg = 0;
            callbackstate = 6;
        }
    }
    i2c_Driver_I2Cx->SCR = scr;
    if (i2c_stop_flg == 1)
    {
        switch (callbackstate)
        {
        case 0:
            break;
        case 1:
            callbackstate = 0;
            i2c_DriverMasterTxData(0);
            break;
        case 2:
            callbackstate = 0;
            i2c_DriverMasterRxData(0);
            break;
        case 3:
            callbackstate = 0;
            i2c_DriverMasterTxData(1);
            break;
        case 4:
            callbackstate = 0;
            i2c_DriverMasterRxData(1);
            break;
        case 5:
            callbackstate = 0;
            i2c_DriverSlaveTxData();
            break;
        case 6:
            callbackstate = 0;
            i2c_DriverSlaveRxData();
            break;
        default:
            callbackstate = 0;
            break;
        }
    }
}
static void i2c_DriverVoidFunctionU8(u8 state)
{
    if (state)
    {
    }
}
static void i2c_DriverVoidFunctionVoid(void)
{
}
