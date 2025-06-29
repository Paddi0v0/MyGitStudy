#include "lks32mc07x_lib.h"
uint8_t writetable[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
uint8_t readtable[10] = {0};
uint8_t writetable1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
uint8_t readtable1[10] = {0};
/**
 * @brief  延时函数
 * @param  cnt: 延时时间
 */
void SoftDelay(u32 cnt);
/**
 * @brief  单字节写
 * @param  flashaddr: 写入地址
 * @param  data: 写入数据
 */
void eeprom_write_one(uint16_t flashaddr, uint8_t data);
/**
 * @brief  多字节写
 * @param  flashaddr: 写入地址
 * @param  data: 写入数据
 * @param  len: 写入长度
 */
void eeprom_write(uint16_t flashaddr, uint8_t *data, uint32_t len);
/**
 * @brief  单字节读
 * @param  flashaddr: 读取地址
 * @return 读取数据
 */
uint8_t eeprom_read_one(uint16_t flashaddr);
/**
 * @brief  多字节读
 * @param  flashaddr: 读取地址
 * @param  data: 读取数据
 * @param  len: 读取长度
 */
void eeprom_read(uint16_t flashaddr, uint8_t *data, uint32_t len);
/**
 * @brief  主函数
 */
int main(void)
{
    SYS_ModuleClockCmd(SYS_Module_GPIO, ENABLE);
    GPIO0->PIE |= BIT3 | BIT4;
    GPIO0->POE |= BIT3 | BIT4;
    GPIO0->PODE |= BIT4; // sda使用开漏输出，scl使用推挽输出（scl如果使用开漏输输出，则容易收到干扰）

    for (;;)
    {
        uint16_t i;
        // 单字节写入
        for (i = 0; i < 10; i++)
        {
            eeprom_write_one(i, writetable[i]);
            SoftDelay(0xffff); // 写入完成后需要等待大约10ms左右
        }
        for (i = 0; i < 10; i++)
        {
            readtable[i] = eeprom_read_one(i);
        }
        SoftDelay(0xfffff);

        // 多字节写入
        eeprom_write(0x200, writetable1, 10); // 多字节写入
        SoftDelay(0xffff);                    // 写入完成后需要等待大约10ms左右
        eeprom_read(0x200, readtable1, 10);
        SoftDelay(0xfffff);
    }
}
// 定义IIC引脚
#define SCL_IO GPIO0, GPIO_Pin_3
#define SDA_IO GPIO0, GPIO_Pin_4
// 定义IIC地址
#define ADDR 0xa0

// IIC函数
static void iicdelay(void);
static void start(void);          // 产生IIC起始信号
static void stop(void);           // 产生IIC停止信号
static uint8_t waitAck(void);     // 等待应答信号到来
static void ack(void);            // 产生ACK应答
static void nack(void);           // 不产生ACK应答
static void send(uint8_t txd);    // IIC发送一个字节
static uint8_t read(uint8_t ack); // 读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint32_t softiic_errflg = 0;

/**
 * @brief 单字节写
 * @param flashaddr: 写入地址
 * @param data: 写入数据
 */
void eeprom_write_one(uint16_t flashaddr, uint8_t data)
{
    uint8_t ack;
    start();
    send(ADDR);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return;
    }
    send(flashaddr >> 8);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return;
    }
    send(flashaddr & 0xff);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return;
    }
    send(data);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return;
    }
    stop();
}
/**
 * @brief 多字节写
 * @param flashaddr: 写入地址
 * @param data: 写入数据
 * @param len: 写入长度
 */
void eeprom_write(uint16_t flashaddr, uint8_t *data, uint32_t len)
{
    uint8_t ack;
    start();
    send(ADDR);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return;
    }
    send(flashaddr >> 8);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return;
    }
    send(flashaddr & 0xff);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return;
    }
    uint32_t i;
    for (i = 0; i < len; i++)
    {
        send(data[i]);
        ack = waitAck();
        if (ack == 1)
        {
            softiic_errflg++;
            stop();
            return;
        }
    }
    stop();
}
/**
 * @brief 单字节读
 * @param flashaddr: 读取地址
 * @return 读取数据
 */
uint8_t eeprom_read_one(uint16_t flashaddr)
{
    uint8_t ack;
    uint8_t rev = 0;
    start();
    send(ADDR);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return rev;
    }
    send(flashaddr >> 8);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return rev;
    }
    send(flashaddr & 0xff);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return rev;
    }
    start();
    send(ADDR | 1);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return rev;
    }
    rev = read(0);
    stop();
    return rev;
}
/**
 * @brief 多字节读
 * @param flashaddr: 读取地址
 * @param data: 读取数据
 * @param len: 读取长度
 */
void eeprom_read(uint16_t flashaddr, uint8_t *data, uint32_t len)
{
    uint8_t ack;
    start();
    send(ADDR);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return;
    }
    send(flashaddr >> 8);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return;
    }
    send(flashaddr & 0xff);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return;
    }
    start();
    send(ADDR | 1);
    ack = waitAck();
    if (ack == 1)
    {
        softiic_errflg++;
        stop();
        return;
    }
    uint32_t i;
    for (i = 0; i < len - 1; i++)
    {
        data[i] = read(1);
    }
    data[len - 1] = read(0); // 最后一次读取需要返回nack
    stop();
    return;
}
/**
 * @brief  gpio输出低电平
 * @param  gpiox: GPIOx
 * @param  pinx: GPIO_Pin_x
 */
static void gpio_out0(GPIO_TypeDef *gpiox, uint16_t pinx)
{
    gpiox->BRR = pinx;
}
/**
 * @brief  gpio输出高电平
 * @param  gpiox: GPIOx
 * @param  pinx: GPIO_Pin_x
 */
static void gpio_out1(GPIO_TypeDef *gpiox, uint16_t pinx)
{
    gpiox->BSRR = pinx;
}
/**
 * @brief  gpio读取电平
 * @param  gpiox: GPIOx
 * @param  pinx: GPIO_Pin_x
 * @return 电平
 */
static uint16_t gpio_read(GPIO_TypeDef *gpiox, uint16_t pinx)
{
    return gpiox->PDI & pinx;
}
/**
 * @brief  产生IIC起始信号
 */
static void start(void)
{
    gpio_out1(SCL_IO);
    gpio_out1(SDA_IO);
    iicdelay();
    gpio_out0(SDA_IO);
    iicdelay();
    gpio_out0(SCL_IO);
}
/**
 * @brief  产生IIC停止信号
 */
static void stop(void)
{
    gpio_out0(SCL_IO);
    gpio_out0(SDA_IO); // STOP:when CLK is high DATA change form low to high
    iicdelay();
    gpio_out1(SCL_IO);
    gpio_out1(SDA_IO);
    iicdelay();
}
/**
 * @brief  等待应答信号到来
 * @return 1，接收应答失败
 *        0，接收应答成功
 */
static uint8_t waitAck(void)
{
    uint8_t ucErrTime = 0;
    gpio_out1(SDA_IO); // SDA设置为输入
    gpio_out1(SDA_IO);
    iicdelay();
    gpio_out1(SCL_IO);
    iicdelay();
    while (gpio_read(SDA_IO))
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            stop();
            return 1;
        }
    }
    gpio_out0(SCL_IO); // 时钟输出0
    return 0;
}
/**
 * @brief  产生ACK应答
 */
static void ack(void)
{
    gpio_out0(SCL_IO);
    gpio_out1(SDA_IO);
    gpio_out0(SDA_IO);
    iicdelay();
    gpio_out1(SCL_IO);
    iicdelay();
    gpio_out0(SCL_IO);
}
/**
 * @brief  不产生ACK应答
 */
static void nack(void)
{
    gpio_out0(SCL_IO);
    gpio_out1(SDA_IO);
    gpio_out1(SDA_IO);
    iicdelay();
    gpio_out1(SCL_IO);
    iicdelay();
    gpio_out0(SCL_IO);
}
/**
 * @brief  IIC发送一个字节
 * @param  txd: 发送的字节
 */
static void send(uint8_t txd)
{
    uint8_t t;
    gpio_out1(SDA_IO);
    gpio_out0(SCL_IO); // 拉低时钟开始数据传输
    for (t = 0; t < 8; t++)
    {
        if (((txd & 0x80) >> 7))
        {
            gpio_out1(SDA_IO);
        }
        else
        {
            gpio_out0(SDA_IO);
        }
        txd <<= 1;
        iicdelay(); // 对TEA5767这三个延时都是必须的
        gpio_out1(SCL_IO);
        iicdelay();
        gpio_out0(SCL_IO);
        //        iicdelay(4);
    }
}
/**
 * @brief  读1个字节，ack=1时，发送ACK，ack=0，发送nACK
 * @param  ack: 1，发送ACK
 *            0，发送nACK
 * @return 读取的数据
 */
static uint8_t read(uint8_t tack)
{
    unsigned char i, receive = 0;
    gpio_out1(SDA_IO); // SDA设置为输入
    for (i = 0; i < 8; i++)
    {
        gpio_out0(SCL_IO);
        iicdelay();
        gpio_out1(SCL_IO);
        receive <<= 1;
        if (gpio_read(SDA_IO))
            receive++;
        iicdelay();
    }
    if (!tack)
    {
        nack(); // 发送nACK
    }
    else
    {
        ack(); // 发送ACK
    }
    return receive;
}
/**
 * @brief  延时函数
 * @param  cnt: 延时时间
 */
static void iicdelay(void)
{
    uint32_t cnt = 100;
    for (; cnt > 0; cnt--)
    {
        __NOP();
    }
}
