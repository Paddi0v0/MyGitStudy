
#include "lks32mc07x_lib.h" // Device header
#include "delay.h"
#define I2C I2C0
static uint8_t addr = 0x24;                                              // 地址设置为0x24时 接收主机发送的数据 地址为0x25时 向主机发送数据
static uint8_t state = 0;                                                // 0 无动作 1接收 2发送 3 设定当前地址
static __attribute__((at(0x7c00))) volatile const uint8_t romdata[1024]; // 固定romdata[511]为0 用来区分rom内数据是否完整
static volatile uint8_t romdatabuffer[512];                              // 缓冲区 收到的数据会先存到这里
static uint16_t romdatap = 0;                                            // 缓冲区指针 0-511循环
static uint16_t RxCnt = 0;                                               // 接收到的数据计数
void eraseSector(uint32_t addr)
{
    SYS_WR_PROTECT = 0x7a83; /* 开启写使能*/
    SYS_FLSE = 0x8fca;
    FLASH_CFG |= BIT31;
    FLASH_ADDR = addr;
    FLASH_ERASE = 0x7654dcba;
    FLASH_CFG &= ~BIT31;
    SYS_FLSE = 0;
}
void programSector(uint32_t* flashadd2,uint32_t* startaddr )
{
    int16_t i;
    FLASH_CFG |= BIT27;
    SYS_WR_PROTECT = 0x7a83; /* 开启写使能*/
    SYS_FLSP = 0x8F35;
    for(i=0;i<128;i++)
    {
        if(*startaddr != *flashadd2) // 只有数据不一样的时候才需要进行写操作
        {
            FLASH_ADDR = (uint32_t)flashadd2;
            FLASH_WDATA = *startaddr;
        }
        startaddr ++;
        flashadd2 ++;
    }
    SYS_FLSP = 0;
    FLASH_CFG &= ~BIT27;
}
/*******************************************************************************
 函数名称：    void RomDataInit(void)
 功能描述：    数据初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/04/17      V1.0         yangzj            创建
 *******************************************************************************/
void RomDataInit(void) // 上电初始化buffer
{
        __disable_irq();
    if (romdata[511] != 0) // 检查数据是否发生变换
    {
        if (romdata[1023] != 0) // 将所有的数据设置为0
        {
            for (int16_t i = 0; i < 512; i++)
            {
                romdatabuffer[i] = 0xff;
            }
            romdatabuffer[511] = 0;
        }
        else
        {
            eraseSector((uint32_t)romdata);
            programSector((uint32_t*)romdata,(uint32_t*)(romdata+512));
        }
    }
    for (int16_t i = 0; i < 512; i++)
    {
        romdatabuffer[i] = romdata[i];
    }
        __enable_irq();
}
/*******************************************************************************
 函数名称：    void RomDataSave(void)
 功能描述：    写数据到flash中
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/04/17      V1.0         yangzj            创建
 *******************************************************************************/
void RomDataSave(void)
{
    uint16_t flg = 0;
    uint32_t *p = (uint32_t *)((u32)romdatabuffer);
    uint32_t *p1 = (uint32_t *)(romdata);
    for (int16_t i = 0; i < 128; i++)
    {
        if (p[i] != p1[i])
        {
            flg = 1;
        }
    }
    if (flg == 1) // 检查数据是否需要保存
    {
        // 写两遍 先写入到第二个扇区，然后再写入到第一个扇区
        // 如果再写入的过程中发生断电或复位等情况，至少有一个扇区的数据是正常的
        
        // 触发保存时，需要临时关掉i2c
        I2C->CFG &= ~BIT0;
        __disable_irq();
        romdatabuffer[511] = 0;
        eraseSector((uint32_t)romdata + 512);
        programSector((uint32_t*)(romdata+512),(uint32_t*)romdatabuffer);
        eraseSector((uint32_t)romdata);
        programSector((uint32_t*)(romdata),(uint32_t*)romdatabuffer);
        I2C->CFG |= BIT0;
        __enable_irq();
    }
}
/*******************************************************************************
 函数名称：    void I2C_IRQHandler(void)
 功能描述：    I2C中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        yangzj        创建
 *******************************************************************************/
void I2C0_IRQHandler(void)
{
    if (I2C->SCR & BIT3) // 收到地址
    {
        uint8_t data;
        data = I2C->DATA;
        if ((data & 0xfe) == addr)
        {
            if (data & 1) // 向主机发送数据
            {
                state = 2;
                I2C->DATA = romdatabuffer[romdatap]; // 向主机发送时需要提前准备好数据
                romdatap = (romdatap + 1) & 511;
                I2C->SCR = BIT2 | BIT4;
            }
            else // 接收主机发过来的数据
            {
                state = 3;
                I2C->SCR = BIT4;
            }
        }
        else
        {
            I2C->SCR = 0;
            state = 0;
        }
    }
    else
    {
        if (I2C->SCR & BIT0)
        {
            if (state == 1) // 接收主机发过来的数据
            {
                RxCnt ++;
                romdatabuffer[romdatap] = I2C->DATA;
                romdatap = (romdatap + 1) & 511;
                I2C->SCR = BIT4;
            }
            else if (state == 2) // 向主机返回数据
            {
                I2C->DATA = romdatabuffer[romdatap];
                romdatap = (romdatap + 1) & 511;
                I2C->SCR = BIT2;
            }
            else if (state == 3) // 接收主机发过来的地址
            {
                romdatap = I2C->DATA;
                romdatap = romdatap*2; // 地址范围0-255 映射到0-512
                I2C->SCR = BIT4;
                state = 1;
                RxCnt = 0;
            }
            else
            {
                I2C->SCR = 0;
            }
        }
        else if (I2C->SCR & BIT5) // 发生stop事件 传输完成
        {
            I2C->SCR = 0;
            if (state == 1)
            {
                if(RxCnt > 1) // 至少收到了一个数据再触发保存逻辑
                {
                    RomDataSave();
                }
            }
            state = 0;
        }
        else
        {
            I2C->SCR = 0;
        }
    }
}
