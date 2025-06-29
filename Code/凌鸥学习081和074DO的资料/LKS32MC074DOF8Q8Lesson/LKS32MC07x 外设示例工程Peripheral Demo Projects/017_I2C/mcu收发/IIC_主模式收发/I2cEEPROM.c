#include "lks32mc07x_lib.h"
#define I2C I2C0
uint8_t *txdata; 
uint8_t txdatap = 0;
uint8_t *rxdata; 
uint8_t rxdatap = 0;
volatile uint8_t state = 0; // 0 无动作 1接收 2发送
volatile uint8_t nackflg = 0; // 0 通信正常 1 发生nack事件
void i2c_tx(u8 taddr, u8 *data, u8 len)
{
    nackflg = 0;
    while(state != 0);
    I2C->SCR = 0;
    txdata = data;
    txdatap = len;
    state = 2;
    I2C->DATA = taddr;
    I2C->MSCR = 1;								// 触发I2C发送数据
}

void i2c_rx(u8 taddr, u8 *data, u8 len)
{
    nackflg = 0;
    while(state != 0);
    I2C->SCR = 0;
    rxdata = data;
    rxdatap = len;
    state = 1;
    I2C->DATA = taddr | 1;
	I2C->MSCR = 1;								// 触发I2C发送数据
}
void WriteData(u8 taddr, u16 data)
{
    int i;
    uint8_t txdata[3];
    txdata[0] = taddr;
    txdata[1] = data>>8;
    txdata[2] = data;
    for(i=0;i<10;i++) // 如果收到nack 则最多尝试发送10次
    {
        i2c_tx(0x24,txdata,3);
        while(state != 0); // 等待发送完成
        if(nackflg == 0)
        {
            return;
        }
    }
    return;
}
u16 ReadData(u8 taddr)
{
    uint8_t txdata[2];
    int i;
    uint16_t val;
    for(i=0;i<10;i++) // 如果收到nack 则最多尝试发送10次
    {
        txdata[0] = taddr;
        i2c_tx(0x24,txdata,1);
        i2c_rx(0x24,txdata,2);
        while(state != 0); // 等待发送完成
        if(nackflg == 0)// 收到ack响应
        {
            val = ((uint16_t)(txdata[0])<<8) | txdata[1];
            return val;
        }
    }
    return 0;
}
void I2C0_IRQHandler(void)
{
    if(I2C->SCR & BIT1)
    {
        nackflg = 1;
    }
    if(I2C->SCR & BIT5)
    {
        state = 0;
        I2C->SCR = 0;
    }
    else if(state == 1)
    {
        if(I2C->SCR & BIT3)
        {
            I2C->SCR = 0;
        }
        else
        {
            I2C->DATA = 0xff;
            *rxdata = I2C->DATA;
            rxdatap--;
            if(rxdatap!=0)
            {
                rxdata++;
                I2C->SCR = BIT4;
            }
            else
            {
                I2C->SCR = 0;
            }
        }
    }
    else if(state == 2)
    {
        if(txdatap!=0)
        {
            I2C->DATA = *txdata;
            txdata++;
            txdatap--;
            I2C->SCR = BIT2;
        }
        else
        {
            I2C->SCR = 0;
        }
    }
    else
    {
        I2C->SCR = 0;
    }
}
