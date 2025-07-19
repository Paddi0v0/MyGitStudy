# 60 【从零开始实现stm32无刷电机FOC】【实践】【7.2/7 完整代码编写】

> 置顶 朴人 已于 2025-02-27 22:58:09 修改 阅读量2.2w 收藏 400 点赞数 122
> 文章链接：https://blog.csdn.net/qq570437459/article/details/142188261

**目录**

[TOC]



本节使用stm32cubemx配置外设，生成keil工程，【使用keil V6编译器】，代码适配本文的 [硬件电路板](https://www.goofish.com/item?id=839277963299) （可参考上节的硬件设计内容）。

-  [点击查看本文开源的完整FOC工程https://gitee.com/best_pureer/stm32_foc](https://gitee.com/best_pureer/stm32_foc) 

-  [配套硬件：点此前往查看](https://item.taobao.com/item.htm?id=839302894720) 

## stm32cubemx配置

### 芯片选择

选择stm32f103c8t6后，点击Start Project。
 ![在这里插入图片描述](./assets/60_1.png)

### 工程配置

切换到Projeck Manager页面，设定好项目名称、项目路径，选择生成keil工程。
 ![在这里插入图片描述](./assets/60_2.png)

### stm32基础配置

-  **配置时钟** 

这里选择晶振：
 ![在这里插入图片描述](./assets/60_3.png)

切换到Clock Configuration页面，首先选择PLLCLK，再HCLK输入72，再点击确认会自动生成72MHz的主频。
 ![在这里插入图片描述](./assets/60_4.png)

-  **SWD接口配置** 

用于烧录和调试程序
 ![在这里插入图片描述](./assets/60_5.png)

-  **串口配置** 

用于打印一些调试信息，选择串口2，因为串口1会被定时器1的pwm通道占用
 ![在这里插入图片描述](./assets/60_6.png)

-  **LED灯配置** 

 ![在这里插入图片描述](./assets/60_7.png)

-  **CMSIS-DSP数学库配置** 

第一步：
 ![在这里插入图片描述](./assets/60_8.png)

第二步：
 ![在这里插入图片描述](./assets/60_9.png)

### SPI的配置

用于读取MT6701，这里的SPI波特率不要设置太高，因为stm32f103c8t6的计算能力有限，角度读的太快算不过来。
从MT6701的数据手册中可以看到，应该在CLK的每2个脉冲时读取DO的数据，而且CLK空闲电平是低电平，因此设置CPOL为Low，CPHA为2个边沿。
由于D13先发送，因此是先高位传输，即MSB大端传输方式。
 ![在这里插入图片描述](./assets/60_10.png)

这里将SPI的模式设置为全双工Full-Duplex Master，而不设置为只读取模式Receive Only Master。虽然单片机的SPI只需要读取MT6701的数据，无需SPI写入数据，但是实测设置为只读取模式时，貌似是每读完1个字节进一次读取完成中断，而我们想要的是每读完3个字节进一次读取完成中断，全双工模式能做到这个效果。
注意不要使用硬件片选NSS（对应芯片CSN读取使能引脚），因为硬件片选NSS是单片机disable对应SPI外设后才会拉低。 ![在这里插入图片描述](./assets/60_11.png)

这里选择手动操作SPI的片选引脚，设置片选信号所在引脚为GPIO输出模式，操作逻辑是：每次在SPI读取MT6701前拉低该引脚，在刚进入读取完成中断时拉高该引脚。
 ![在这里插入图片描述](./assets/60_12.png)

后续使用DMA读取SPI数据，全双工模式下，接收和发送DMA均需要打开：
 ![在这里插入图片描述](./assets/60_13.png)

### 定时器的配置

-  **用于电机速度计算的定时器** 

首先勾选时钟来自内部时钟源，再创建一个宏定义，用于速度计算间隔。motor_speed_calc_freq是FOC代码里手动设置的宏，speed_calc_freq这个宏给cubemx用，这样就将cubemx的参数与FOC代码里的宏绑定到了一起，好处就是FOC代码与cubemx独立开，FOC代码用于其他厂商单片机不用改太多的代码。
 ![在这里插入图片描述](./assets/60_14.png)

首先设置分频为72-1，72MHz的时钟分频下来后每1us定时器计数加1。定时器计数容量为N时，定时器溢出中断频率是1秒/N微妙=1000000/N赫兹，我们想要定时器溢出中断频率等于motor_speed_calc_freq，那么需要1000000/N=motor_speed_calc_freq，因此这里的计数容量设置为N=1000000/motor_speed_calc_freq。
由于cubemx是不认识motor_speed_calc_freq的，因此这里选择No check不检查参数类型。
 ![在这里插入图片描述](./assets/60_15.png)

开启定时器中断函数，用于计算电机速度：
 ![在这里插入图片描述](./assets/60_16.png)

-  **用于产生电机PWM的高级定时器** 

高级定时器的使用非常关键，非常重要，对于外设配置项的说明请查看 [前文定时器章节](https://blog.csdn.net/qq570437459/article/details/140227714) 。
stm32f103c8t6只有一个高级定时器：TIM1。
首先选择时钟源，然后开启3个PWM正通道，由于本文使用的集成驱动芯片DRV8313自带互补PWM功能，因此不开启PWM负通道。
这里注意不勾选Activate-Break-Input，这个只是帮你配置刹车引脚的GPIO参数，刹车功能依然是有效的。不勾选的原因是经过我的各种尝试，触发刹车后，依然进不去刹车中断函数TIM1 break interrupt，所以选择自己配置刹车引脚GPIO为外部中断。
 ![在这里插入图片描述](./assets/60_17.png)

手动设置刹车引脚为外部中断，这里不设置也没事，本文代码是因为想要触发刹车后串口打印一下告知刹车被触发了：
 ![在这里插入图片描述](./assets/60_18.png)

开启外部中断函数：
 ![在这里插入图片描述](./assets/60_19.png)

回到高级定时器的配置，再次提醒对于外设配置项的说明请查看 [前文定时器章节](https://blog.csdn.net/qq570437459/article/details/140227714) 。

- PWM的频率是非常高的，我设置的20KHz（对应中心对齐模式下的10KHz），因此不进行预分频。

- 计数方式选择中心对齐方式3。

- 计数容量定义了一个cubemx宏，与FOC代码里的宏进行绑定，这样做可以使得FOC代码独立在各种平台上使用，勾选No check不检查数值类型。数值计算过程：定时器计数不分频情况下，每 $\frac{1}{72*1000000}
  $ 秒计数加1，计数容量为N时，计数溢出时间为 $\frac{N}{72000000}
  $ ，则计数溢出频率为 $\frac{72000000}{N}
  $ ，而我们设定的计数溢出频率=motor_pwm_freq，即 $\frac{72000000}{N}=motor\_pwm\_freq
  $ ，因此计数容量 $N=\frac{72000000}{motor\_pwm\_freq}
  $ 。

- 重复计数器设置为4，即每5个定时器溢出产生1个更新事件，更新事件会触发ADC采样，本文FOC代码是放在ADC采样完成中断里计算的，这样FOC代码的计算频率等于20KHz/5=4KHz，这个频率不要太快，因为stm32f103c8t6的算力有限，计算一次FOC代码大约需要120us。

- 输出触发事件来源选择更新事件，自动触发ADC采样。

- BRK State刹车功能可以开启，也可以关闭，建议验证FOC算法阶段先关闭，本文 [配套硬件](https://www.goofish.com/item?id=839277963299) 有刹车引脚LED灯提示。对应DRV8313的Fault引脚信号，刹车电平选择Low低电平。

- 3个PWM Generation Channel的配置项都相同，默认值刚好是我们想要配置的值。关键项是Mode选择PWM mode 1，因为DRV8313内部是NMOS，所以CH Polarity有效电平是高电平。
   ![在这里插入图片描述](./assets/60_20.png)

### ADC的配置

ADC的使用非常关键，非常重要，对于外设配置项的说明请查看 [前文ADC章节](https://blog.csdn.net/qq570437459/article/details/140229184) 。
使用双ADC同步采样两条电机相线上采样电阻放大后的电压差，首先给ADC1和ADC2分配通道，IN0对应PA0引脚，IN0对应PA1引脚，ADC1是主ADC。
 ![在这里插入图片描述](./assets/60_21.png)

两个ADC都分配好通道后，将两个ADC的ADC_Regular_ConversionMode设置为Disable将ADC_Injected_ConversionMode设置为Enable，主ADC的模式下拉框里才会出现注入式同步采样的选项，由于只有注入式采样才能绑定到高级定时器的触发事件，因此选择注入式同步采样。
 ![在这里插入图片描述](./assets/60_22.png)

接下来配置ADC选项：

- 同步采样模式下，一定要开启Continuous连续转换模式。

- 关闭常规采样，打开注入采样。

- 每个ADC只采集一个通道，因此Number Of Conversions设置为1，ADC1的Rank序列中的Channel通道选择通道0，ADC2的Rank序列中的Channel通道选择通道1，采样时间可以设置大一点，我们代码中限制PWM占空比最高为90%即可留出充足的时间给ADC采样。

- 外部触发源选择定时器1的触发事件。
   ![在这里插入图片描述](./assets/60_23.png)

   ![在这里插入图片描述](./assets/60_24.png)

  开启ADC采样完成中断，FOC代码会放在这个中断函数里进行：
   ![在这里插入图片描述](./assets/60_25.png)

### 中断优先级的配置

读取磁编码器SPI的DMA中断优先级设置到最优先，电机角度获取一定要及时准确。
接下来速度计算的定时器中断和运行FOC代码的ADC中断其次，速度计算和FOC代码必须尽量优先。
连到刹车引脚的外部中断优先级放到最低即可，刹车功能在刹车引脚有效时被硬件触发，和中断无关，这个外部中断只是为了串口打印几句消息告知触发刹车了。
 ![在这里插入图片描述](./assets/60_26.png)

### 生成工程

至此，stm32cubemx相关配置已经完毕，接下来生成keil工程，这里勾选了 `Generate peripheral initialization as a pair of '.c/.h' files per peripheral` ，方便功能模块分离。
 ![在这里插入图片描述](./assets/60_27.png)

此时keil工程编译是无法通过的，编译器可能没选到verison 6，而且两个宏 `motor_speed_calc_freq` 和 `motor_pwm_freq` 我们还没写到代码里。
首先选择编译器为version 6，如果没有出现version 6，你需要下载最新keil版本。
 ![在这里插入图片描述](./assets/60_28.png)

接下来我会使用vscode进行代码编辑，keil用来编译工程和烧录调试代码。
接下来定义 `motor_speed_calc_freq` 和 `motor_pwm_freq` 。

- 首先在Drivers文件夹下创建motor文件夹，这个文件夹专门用来放置电机FOC驱动代码。

- 然后motor文件夹下创建conf.h，这个文件专门用来放置FOC代码相关的工程配置，将Drivers文件夹添加到头文件路径中。

- 最后在main.h文件的用户代码区把conf.h文件include进来即可将工程编译通过。
   ![在这里插入图片描述](./assets/60_29.png)

   ![在这里插入图片描述](./assets/60_30.png)

   ![在这里插入图片描述](./assets/60_31.png)

在 `Src/usart.c` 中定义fputc，方便后续使用printf函数：

```c
//usart.c
/* USER CODE BEGIN 1 */
#include <stdio.h>
int fputc(int c, FILE *stream)
{
  uint8_t ch[] = {(uint8_t)c};
  HAL_UART_Transmit(&huart2, ch, 1, HAL_MAX_DELAY);
  return c;
}
/* USER CODE END 1 */
```

在Inc文件夹下创建一个全局宏定义文件 `global_def.h` ，方便调用：

```c
//global_def.h
#pragma once
#ifndef PI
#define PI 3.14159265358979
#endif
#define deg2rad(a) (PI * (a) / 180)
#define rad2deg(a) (180 * (a) / PI)
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
```

由于本文使用的daplink是低成本版本，为了保证传输稳定性，下载程序的频率选择为1MHz。

## 工程代码编写

在stm32hal库中，应用逻辑的代码实现变得非常方便，基本规律就是：外设读取+读取完成中断。

### FOC代码结构搭建

根据本文硬件情况补充FOC代码里的 `conf.h` ：

```c
#pragma once

// 电机物理参数：
#define POLE_PAIRS 7 // 极对数

// 电路参数：
#define R_SHUNT 0.02           // 电流采样电阻，欧姆
#define OP_GAIN 50             // 运放放大倍数
#define MAX_CURRENT 2          // 最大q轴电流，安培A
#define ADC_REFERENCE_VOLT 3.3 // 电流采样adc参考电压，伏
#define ADC_BITS 12            // ADC精度，bit

// 单片机配置参数：
#define motor_pwm_freq 20000      // 驱动桥pwm频率，Hz
#define motor_speed_calc_freq 930 // 电机速度计算频率，Hz

// 软件参数：
#define position_cycle 6 * 3.14159265358979 // 电机多圈周期，等于正半周期+负半周期
```

在 `Drivers/motor` 文件夹下创建 `motor_runtime_param.c` 和 `motor_runtime_param.h` ，用于放置电机运行过程中的各种参数。
关于转子角度和电机角度的区别， [前文位置控制](https://blog.csdn.net/qq570437459/article/details/138872078) 说明了一部分，后面内容有代码上的讲解。

```c
//motor_runtime_param.c
#include "motor_runtime_param.h"

float motor_i_u;
float motor_i_v;
float motor_i_d;
float motor_i_q;
float motor_speed;
float motor_logic_angle;
float encoder_angle;
float rotor_zero_angle;
```

```c
//motor_runtime_param.h
#pragma once
#include "conf.h"
#define rotor_phy_angle (encoder_angle - rotor_zero_angle)     // 转子物理角度
#define rotor_logic_angle rotor_phy_angle *POLE_PAIRS          // 转子多圈角度
extern float motor_i_u;
extern float motor_i_v;
extern float motor_i_d;
extern float motor_i_q;
extern float motor_speed;
extern float motor_logic_angle; // 电机多圈角度
extern float encoder_angle;     // 编码器直接读出的角度
extern float rotor_zero_angle;  // 转子d轴与线圈d轴重合时的编码器角度
```

在 `Drivers/motor` 文件夹下创建 `foc.c` 和 `foc.h` ，准备用于放置FOC代码。
添加好头文件路径：
 ![在这里插入图片描述](./assets/60_32.png)

添加好C文件：
 ![在这里插入图片描述](./assets/60_33.png)

### 电机编码器角度读取

从MT6701数据手册可知，SPI数据一共有3个字节：
 ![在这里插入图片描述](./assets/60_34.png)

采用DMA方式SPI读取3个字节，再取前14位组合成角度值，这里我不使用4bit的Status信息，也不进行crc校验，这不影响角度读取，你可自行运用这些数据提高程序健壮性。
在 `Src/spi.c` 中的USER CODE区域实现读取成功的回调函数，还要实现读取失败的回调函数，每次进入读取完毕函数后立即关闭SPI片选引脚，并且在即将退出回调函数的时候打开SPI片选引脚并启动下一次读取。

```c
//spi.c
/* USER CODE BEGIN 1 */
#include <stdio.h>
#include "motor/motor_runtime_param.h"
#include "motor/foc.h"	
#include "arm_math.h"
uint8_t mt6701_rx_data[3];
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  if (hspi->Instance == SPI1)
  {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    int angle_raw = (mt6701_rx_data[1] >> 2) | (mt6701_rx_data[0] << 6);
    encoder_angle = 2 * 3.1415926 * angle_raw / ((1 << 14) - 1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive_DMA(&hspi1, mt6701_rx_data, mt6701_rx_data, 3);
    return;
  }
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  printf("HAL_SPI_ErrorCallback:%d\n", hspi->ErrorCode);
  if (hspi->Instance == SPI1)
  {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive_DMA(&hspi1, mt6701_rx_data, mt6701_rx_data, 3);
  }
  return;
}
/* USER CODE END 1 */
```

在main函数的while(1)之前调用一次DMA方式的SPI读取，即可自动连续获取角度值，然后在while(1)里面打印一下角度验证一下代码，手动旋转一下电机，结果会在 $0$ 到 $2\pi$ 弧度值之间变化：

```c
//main.c
//......
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "motor/motor_runtime_param.h"
#include "motor/foc.h"
#include "global_def.h"
/* USER CODE END Includes */
//......
/* USER CODE BEGIN 2 */
extern uint8_t mt6701_rx_data[3];
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
HAL_SPI_TransmitReceive_DMA(&hspi1, mt6701_rx_data, mt6701_rx_data, 3);
HAL_Delay(100);//延时一会，让角度变量被赋值，不然角度会是0
/* USER CODE END 2 */
//......
while(1)
{
//......
	/* USER CODE BEGIN 3 */
    printf("%f\n", encoder_angle);
    HAL_Delay(100);
//......
```

在此再提醒：读取角度的SPI中断优先级一定要最高，否则片选信号可能没有及时关闭，导致角度读取无法接续。

### PWM产生

开启PWM输出：

```c
//main.c
//......
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  /* USER CODE END 2 */
//......
```

自己定义一个函数 `set_pwm_duty` ，方便设置PWM占空比。 `htim1.Instance->ARR` 是定时器计数容量。
有两个细节：

- 限制占空比最高为90%，留出一个电流稳定的时段，有利于减少电机抖动以及给后续ADC采样提供稳定电流时段。原因是：占空比接近100%时，会出现mos关闭后瞬间开启的情况，而且此时是电流通过，导致电流非常不稳定；不必要限制最低占空比，因为q轴为0时，由于SVPWM中的000矢量和111矢量两个零力矩矢量平分了一个PWM周期，因此FOC控制力矩最低情况的PWM占空比就是50%。
   ![在这里插入图片描述](./assets/60_35.png)

- 操作3个通道时关闭了中断，防止通道不同步。

```c
//main.c
/* USER CODE BEGIN 0 */
void set_pwm_duty(float d_u, float d_v, float d_w)
{
  d_u = min(d_u, 0.9);
  d_v = min(d_v, 0.9);
  d_w = min(d_w, 0.9);
  __disable_irq();
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, d_u * htim1.Instance->ARR);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, d_v * htim1.Instance->ARR);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, d_w * htim1.Instance->ARR);
  __enable_irq();
}
/* USER CODE END 0 */
```

### FOC开环代码编写

FOC开环就是实现一下SVPWM代码，输入目标d轴q轴强度和旋转的目标转子位置，输出电机相线pwm占空比， [前文](https://blog.csdn.net/qq570437459/article/details/138871835) 已经实现了SVPWM纯C语言代码，这里将其放到单片机中，也就是要将纯C的数学函数换做CMSIS-DSP里的函数：

```c
//foc.c
#include "foc.h"
#include "arm_math.h"
#include "motor_runtime_param.h"
#include <stdbool.h>
#define rad60 deg2rad(60)
#define SQRT3 1.73205080756887729353
#define deg2rad(a) (PI * (a) / 180)
#define rad2deg(a) (180 * (a) / PI)
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

static void svpwm(float phi, float d, float q, float *d_u, float *d_v, float *d_w)
{
    d = min(d, 1);
    d = max(d, -1);
    q = min(q, 1);
    q = max(q, -1);
    const int v[6][3] = {{1, 0, 0}, {1, 1, 0}, {0, 1, 0}, {0, 1, 1}, {0, 0, 1}, {1, 0, 1}};
    const int K_to_sector[] = {4, 6, 5, 5, 3, 1, 2, 2};
    float sin_phi = arm_sin_f32(phi);
    float cos_phi = arm_cos_f32(phi);
    float alpha = 0;
    float beta = 0;
    arm_inv_park_f32(d, q, &alpha, &beta, sin_phi, cos_phi);

    bool A = beta > 0;
    bool B = fabs(beta) > SQRT3 * fabs(alpha);
    bool C = alpha > 0;

    int K = 4 * A + 2 * B + C;
    int sector = K_to_sector[K];

    float t_m = arm_sin_f32(sector * rad60) * alpha - arm_cos_f32(sector * rad60) * beta;
    float t_n = beta * arm_cos_f32(sector * rad60 - rad60) - alpha * arm_sin_f32(sector * rad60 - rad60);
    float t_0 = 1 - t_m - t_n;

    *d_u = t_m * v[sector - 1][0] + t_n * v[sector % 6][0] + t_0 / 2;
    *d_v = t_m * v[sector - 1][1] + t_n * v[sector % 6][1] + t_0 / 2;
    *d_w = t_m * v[sector - 1][2] + t_n * v[sector % 6][2] + t_0 / 2;
}
```

我将svpwm函数封装一层，命名为 `foc_forward` ，传入参数是d轴强度、q轴强度、转子角度，后续闭环计算完毕后也能输入到该函数，得到电机相线pwm占空比。这里创建了一个和 `set_pwm_duty` 同名的weak类型函数，这样做是为了提高FOC代码的独立解耦性，编译的时候如果有同名函数，带weak的不会被编译进去。

```c
//foc.c
//......
__attribute__((weak)) void set_pwm_duty(float d_u, float d_v, float d_w)
{
    while (1)
        ;
}
void foc_forward(float d, float q, float rotor_rad)
{
    float d_u = 0;
    float d_v = 0;
    float d_w = 0;
    svpwm(rotor_rad, d, q, &d_u, &d_v, &d_w);
    set_pwm_duty(d_u, d_v, d_w);
}
//......
```

```c
//foc.h
#pragma once

float cycle_diff(float diff, float cycle);
void foc_forward(float d, float q, float rotor_rad);
```

测试一下FOC开环控制，设定d轴强度为0、q轴强度为0.5（不要太高，开环发热）、目标转子在0~360度之间循环转动，此时电机应该就转起来了，由于是开环，电机转起来会抖，而且会发热，不要长时间转。

```c
//main.c
//......
while(1)
{
//......
	/* USER CODE BEGIN 3 */
    for (size_t i = 0; i < 360; i += 20)
    {
      HAL_Delay(2);
      foc_forward(0, 0.5, deg2rad(i));
    }
//......
```

### 确定电机正负旋转方向

默认情况下，手动逆时针转动电机，MT6701磁编码器的角度是递增的，因此将逆时针旋转设定为角度增加的旋转正方向。有些编码器角度增加的旋转方向是逆时针，这并不唯一。
继续使用上述FOC开环测试代码，传入的q轴是正数，如果电机逆时针转，那么相线顺序是正确的，否则将电机相线取两相对调即可得到正确的相线顺序。
得到正确的相线顺序后，就可以认为UVW三相线分别对应PWM通道123。

### 电机旋转速度计算

众所周知， $旋转速度=\frac{\Delta \theta}{\Delta t}=\Delta \theta*频率
$ ，速度计算频率我们已经设定了宏定义 `motor_speed_calc_freq` ，所以在速度定时器中断里的计算过程是：

$$
(上次编码器角度-这次编码器角度)*motor\_speed\_calc\_freq
$$

但是代码不能直接这么写，因为：

- 编码器角度位于 $0$ 到 $2\pi$ 之间，359度到1度实际旋转了2度，但是差值是358度，因此计算差值的时候要把差值转换到 $-\pi$ 到 $\pi$ 之间。

- 算出来的速度需要进行滤波才能给外部用。

下面这个函数能将无符号数映射到一个周期内的有符号数。算角度差值的时候经常会用到，将其放在FOC代码中：

```c
//foc.c
//......
float cycle_diff(float diff, float cycle)
{
    if (diff > (cycle / 2))
        diff -= cycle;
    else if (diff < (-cycle / 2))
        diff += cycle;
    return diff;
}
//......
```

```c
//foc.h
#pragma once
//......
float cycle_diff(float diff, float cycle);
//......
```

再实现滤波函数，这里使用低通滤波，也可以自行更换为卡尔曼滤波等等。
先创建文件用于放置滤波代码，注意别忘了在keil里加入头文件路径和C文件，这里keil里就不演示了。
 ![在这里插入图片描述](./assets/60_36.png)

再实现低通滤波函数：

```c
//filter.c
float low_pass_filter(float input, float last_output, float alpha)
{
    return alpha * input + (1.0 - alpha) * last_output;
}
```

在 `Src/tim.c` 实现最终的速度计算代码：

```c
//tim.c
#include "global_def.h"
#include "motor/motor_runtime_param.h"
#include "motor/foc.h"
#include "algorithm/filter.h"
#include "arm_math.h"
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM3)
  {
    static float encoder_angle_last = 0;
    
    /******encoder_angle_last默认值是0，不能用于计算，需要赋初值*********/
    static int once = 1;
    if (once)
    {
      once = !once;
      encoder_angle_last = encoder_angle;
    }
    /***************/
    
    float diff_angle = cycle_diff(encoder_angle - encoder_angle_last, 2 * PI);
    encoder_angle_last = encoder_angle;
    float _motor_speed = diff_angle * motor_speed_calc_freq;
    float filter_alpha_speed = 0.1;//低通滤波参数，如果希望保留更多的细节，可以增加alpha的值
    motor_speed = low_pass_filter(_motor_speed, motor_speed, filter_alpha_speed);
  }
}
```

在main.c中开启速度计算定时器：

```c
//......
HAL_TIM_Base_Start_IT(&htim3);
/* USER CODE END 2 */
//......
```

测试一下速度计算是否有效，继续使用FOC开环测试代码，不要转太长时间，开环控制会发热：

```c
//main.c
//......
while(1)
{
//......
	/* USER CODE BEGIN 3 */
    for (size_t i = 0; i < 360; i += 20)
    {
      HAL_Delay(2);
      foc_forward(0, 0.5, deg2rad(i));
      printf("%f\n", motor_speed);
    }
//......
```

### 多圈逻辑角度

从MT6701编码器是 $0$ 到 $2\pi$ 周期变化的，只有单圈，但我们想要多圈角度时，需要自行将每次的角度差值累计起来，即累计(当前角度-上次角度)。
逻辑角度是手动累计的，因此更新及时性是取决与放在哪里累计的。如果放在SPI读取角度中断里，那么和编码器角度一样的更新及时；如果放在其他中断里，比如速度计算定时器中断、ADC采样完成中断，按照本文设置，则逻辑角度更新速度等于速度计算频率=930Hz，ADC中断=4KHz。更新及时性超过SPI读取角度中断频率是没有意义的。本文选择放在SPI读取角度中断里累计。
这里对逻辑角度进行了周期操作，全周期是position_cycle，比如position_cycle设置为720度、当前逻辑角度是358度，再转3度后，逻辑角度就等于-359度了。如果你的逻辑角度是非常非常多圈，并且你自信电机实际旋转需求不会超出浮点数可表达的最大值，可以不需要周期操作，直接累加即可。
补充SPI读取角度中断：

```c
//spi.c
//......
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  if (hspi->Instance == SPI1)
  {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    int angle_raw = (mt6701_rx_data[1] >> 2) | (mt6701_rx_data[0] << 6);
    encoder_angle = 2 * 3.1415926 * angle_raw / ((1 << 14) - 1);

    static float encoder_angle_last = 0;
    /****encoder_angle_last默认值是0，不能用于计算，要先赋值一次****/
    static int once = 1;
    if (once)
    {
      once = !once;
      encoder_angle_last = encoder_angle;
    }
    /*************/
    float _encoder_angle = encoder_angle;
    // 角度差值，用于累计多圈逻辑角度
    float diff_angle = cycle_diff(_encoder_angle - encoder_angle_last, 2 * PI);
    encoder_angle_last = _encoder_angle;
    // 实现周期操作，将motor_logic_angle转到周期内
    motor_logic_angle = cycle_diff(motor_logic_angle + diff_angle, position_cycle);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive_DMA(&hspi1, mt6701_rx_data, mt6701_rx_data, 3);
    return;
  }
}
//......
```

在主函数里打印一下逻辑角度，用手转动电机几圈，看看逻辑角度是否有效：

```c
//main.c
//......
while(1)
{
printf("%f\n", motor_logic_angle);
/* USER CODE END WHILE */
//......
```

从角度结果可以看到逻辑角度具有多圈周期性：
 ![在这里插入图片描述](./assets/60_37.png)

### 电流采样

电机相线上的电流采样电阻两端电压经过放大器放大后，输入单片机ADC口。
本文会将正式的FOC实时计算代码放在ADC采样完成中断里（大部分驱动代码都会这么做，当然放在角度读取完成中断里也是可行的），因此无论是否读取ADC值，这个中断函数必须要开放实现的。
进行ADC采样之前，先校准，然后开始采样。由于ADC采样绑定了高级定时器的输出事件，后续的ADC采样会自动被高级定时器触发。

```c
//main.c
//......
  HAL_ADCEx_Calibration_Start(&hadc1);
  HAL_ADCEx_Calibration_Start(&hadc2);
  HAL_ADCEx_InjectedStart_IT(&hadc1);
  HAL_ADCEx_InjectedStart(&hadc2);
  /* USER CODE END 2 */
//......
```

在ADC采样完成中断函数里读取ADC值，INA199放大器系列的ADC值会在1.65V上下变动，1.65V代表采样电阻两端电压为0V，大于1.65V代表采样电阻两端电压为正数，小于1.65V代表采样电阻两端电压为负数，相线电流等于 $\frac{ADC值-1.65V}{放大倍数}\div采样电阻值
$ 。
这里最好验证一下ADC值的正负以及是否正好对应PWM通道123，先假设PWM通道1对应ADC1，PWM通道2对应ADC2，则假设U相电流等于ADC1计算得到的电流，V相电流等于ADC2计算得到的电流，W相电流根据基尔霍夫电流总和为0的定律等于： $-(U相电流+V相电流)$ ：

```c
//adc.c
//......
#include "motor/motor_runtime_param.h"
#include "motor/foc.h"
#include "algorithm/filter.h"
#include "global_def.h"
#include "arm_math.h"
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1)
  {
    float u_1 = ADC_REFERENCE_VOLT * ((float)HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_1) / ((1 << ADC_BITS) - 1) - 0.5);
    float u_2 = ADC_REFERENCE_VOLT * ((float)HAL_ADCEx_InjectedGetValue(&hadc2, ADC_INJECTED_RANK_1) / ((1 << ADC_BITS) - 1) - 0.5);
    float i_1= u_1 / R_SHUNT / OP_GAIN;
    float i_2 = u_2 / R_SHUNT / OP_GAIN;
	motor_i_u = i_1;
    motor_i_v = i_2;
  }
}
```

如果3个PWM通道正对应ADC1和ADC2，那么打开PWM通道1，关闭PWM通道2、3的时候，ADC1这条路会得到一个对应的正电流值，如下图所示：

按照这个思想验证一下：

```c
//main.c
//......
  /* USER CODE BEGIN WHILE */
  set_pwm_duty(0.5, 0, 0);
  HAL_Delay(300);
  printf("%f,%f,%f\n", motor_i_u, motor_i_v, -(motor_i_u + motor_i_v));

  set_pwm_duty(0, 0.5, 0);
  HAL_Delay(300);
  printf("%f,%f,%f\n", motor_i_u, motor_i_v, -(motor_i_u + motor_i_v));

  set_pwm_duty(0, 0, 0.5);
  HAL_Delay(300);
  printf("%f,%f,%f\n", motor_i_u, motor_i_v, -(motor_i_u + motor_i_v));
  set_pwm_duty(0, 0, 0);
  while (1)
  {
//......
```

如果得到类似下图的结果，三个电流正值都差不多，也是分别出现在第1、2、3个，那么说明ADC1和ADC2正对应PWM通道1和2，而且正负方向也是正确的，否则就需要调整 `motor_i_u = i_1;` 和 `motor_i_v = i_2;` 代码，重新排列正确的对应关系。
 ![在这里插入图片描述](./assets/60_38.png)

再根据3个相电流换算到d轴和q轴电流，即clark变换和park变换，理论部分请参考 [前文电流控制](https://blog.csdn.net/qq570437459/article/details/138872078) ，然后进行滤波操作。如果你不想使用力矩环，d轴和q轴电流无需计算。ADC中断代码补充为：

```c
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1)
  {
    float u_1 = ADC_REFERENCE_VOLT * ((float)HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_1) / ((1 << ADC_BITS) - 1) - 0.5);
    float u_2 = ADC_REFERENCE_VOLT * ((float)HAL_ADCEx_InjectedGetValue(&hadc2, ADC_INJECTED_RANK_1) / ((1 << ADC_BITS) - 1) - 0.5);
    float i_1 = u_1 / R_SHUNT / OP_GAIN;
    float i_2 = u_2 / R_SHUNT / OP_GAIN;
    motor_i_u = i_1;
    motor_i_v = i_2;

    float i_alpha = 0;
    float i_beta = 0;
    arm_clarke_f32(motor_i_u, motor_i_v, &i_alpha, &i_beta);
    float sin_value = arm_sin_f32(rotor_logic_angle);
    float cos_value = arm_cos_f32(rotor_logic_angle);
    float _motor_i_d = 0;
    float _motor_i_q = 0;
    arm_park_f32(i_alpha, i_beta, &_motor_i_d, &_motor_i_q, sin_value, cos_value);
    float filter_alpha_i_d = 0.1;
    float filter_alpha_i_q = 0.1;
    motor_i_d = low_pass_filter(_motor_i_d, motor_i_d, filter_alpha_i_d);
    motor_i_q = low_pass_filter(_motor_i_q, motor_i_q, filter_alpha_i_q);
  }
}
```

### 极对数

前文理论部分一直使用的是简单模型，即转子看成一根直的磁铁，实际电机的转子磁铁排布可能如下图，这是本文使用的电机示意图，一共有14个（7对）磁极，即极对数为7。
 ![在这里插入图片描述](./assets/60_39.png)

极对数为7的电机完成7次相线换相周期后，电机才会旋转一圈。也就是说用于FOC计算的转子逻辑角度=极对数*转子物理角度。

### 转子角度确定

注意这里称为【转子】角度。
FOC模型是建立在电机转子基础上的，d轴q轴相关计算是按照转子角度计算的，而我们能直接获取的是磁编码器角度，也就是电机外壳角度，因为磁铁粘在电机外壳上，磁编码器感应磁铁角度。
确定转子初始角度的其中一个简单方法是：电机上电后，控制相线形成磁场，将转子吸引到转子零度的位置，也就是基础矢量1的位置。这样不管转子起始在哪个角度，都可以强行让转子到零度，记录此时的编码器角度，以后转子的物理角度都以该角度为转子零度，即转子物理角度等于编码器角度减去该角度。
用代码实现这个方法：

```c
//main.c
//......
  set_pwm_duty(0.5, 0, 0);              // 生成SVPWM模型中的基础矢量1，即对应转子零度位置
  HAL_Delay(400);                       // 保持一会，转子吸引过来需要时间
  rotor_zero_angle = encoder_angle;
  set_pwm_duty(0, 0, 0);                // 松开电机
  HAL_Delay(10);
  /* USER CODE END 2 */
//......
```

前面在 `motor_runtime_param.h` 里设置的宏定义帮我们完成了转子物理角度和转子逻辑角度的计算： `#define rotor_phy_angle (encoder_angle - rotor_zero_angle) // 转子物理角度` 和 `#define rotor_logic_angle rotor_phy_angle *POLE_PAIRS //转子逻辑角度` 

---

## 闭环控制

这个部分编写位置环、速度环、电流环代码。FOC闭环控制代码将放在ADC采样中断中进行。

### 控制函数接口定义

控制函数接口要符合人的直觉，让人可以直观地调用，先定义函数接口，再逐步补充这些函数：

```c
//foc.h
//......
void lib_position_control(float rad);
void lib_speed_control(float speed);
void lib_torque_control(float torque_norm_d, float torque_norm_q);
void lib_position_speed_torque_control(float position, float max_speed, float max_torque_norm);
//......
```

先这么放着，后面会补充内容：

```c
//foc.c
//......
void lib_position_control(float rad)
{
}

void lib_speed_control(float speed)
{
}

void lib_torque_control(float torque_norm_d, float torque_norm_q)
{
}

void lib_speed_torque_control(float speed_rad, float max_torque_norm)
{
}

void lib_position_speed_torque_control(float position_rad, float max_speed_rad, float max_torque_norm)
{
}
//......
```

力矩控制包括d轴和q轴强度。
上述定义的接口意思是实时计算一次电机相线pwm输出占空比，这是FOC核心算法，因此需要不断调用上述接口以及时更新输出占空比。
为了让后续功能性的代码更加容易编写，再对这个接口封装一层。这里创建了一个结构体变量，用于方便后续程序上的使用，你也可以不封装上述接口，直接反复调用上述接口也是可以的。

```c
//foc.h
//......
typedef enum
{
    control_type_null,                  // 不进行控制
    control_type_position,              // 位置控制
    control_type_speed,                 // 速度控制
    control_type_torque,                // 力矩控制
    control_type_position_speed_torque, // 位置-速度-力矩控制
} motor_control_type;

typedef struct
{
    motor_control_type type;
    float position;        // 目标角度，单位rad
    float speed;           // 目标速度，单位rad/s
    float torque_norm_d;   // 目标d轴强度，0~1
    float torque_norm_q;   // 目标q轴强度，0~1
    float max_speed;       // 串级控制时的最大速度，单位rad/s
    float max_torque_norm; // 串级控制时的最大q轴力矩，0~1
} motor_control_context_t;

extern motor_control_context_t motor_control_context;
//......
```

有了这个封装后的结构体变量后，就可以在ADC中断里不断扫描这个结构体变量从而不断调用对应的FOC控制函数接口，在主代码里对这个结构体变量赋值即可。

```c
//adc.c
//......
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1)
  {
    float u_1 = ADC_REFERENCE_VOLT * ((float)HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_1) / ((1 << ADC_BITS) - 1) - 0.5);
    float u_2 = ADC_REFERENCE_VOLT * ((float)HAL_ADCEx_InjectedGetValue(&hadc2, ADC_INJECTED_RANK_1) / ((1 << ADC_BITS) - 1) - 0.5);
    float i_1 = u_1 / R_SHUNT / OP_GAIN;
    float i_2 = u_2 / R_SHUNT / OP_GAIN;
    motor_i_u = i_1;
    motor_i_v = i_2;

    float i_alpha = 0;
    float i_beta = 0;
    arm_clarke_f32(motor_i_u, motor_i_v, &i_alpha, &i_beta);
    float sin_value = arm_sin_f32(rotor_logic_angle);
    float cos_value = arm_cos_f32(rotor_logic_angle);
    float _motor_i_d = 0;
    float _motor_i_q = 0;
    arm_park_f32(i_alpha, i_beta, &_motor_i_d, &_motor_i_q, sin_value, cos_value);
    float filter_alpha_i_d = 0.1;
    float filter_alpha_i_q = 0.1;
    motor_i_d = low_pass_filter(_motor_i_d, motor_i_d, filter_alpha_i_d);
    motor_i_q = low_pass_filter(_motor_i_q, motor_i_q, filter_alpha_i_q);

    switch (motor_control_context.type)
    {
    case control_type_position:
      lib_position_control(motor_control_context.position);
      break;
    case control_type_speed:
      lib_speed_control(motor_control_context.speed);
      break;
    case control_type_torque:
      lib_torque_control(motor_control_context.torque_norm_d, motor_control_context.torque_norm_q);
      break;
    case control_type_position_speed_torque:
      lib_position_speed_torque_control(motor_control_context.position, motor_control_context.max_speed, motor_control_context.max_torque_norm);
      break;
    default:
      break;
    }
  }
}
//......
```

以位置控制为例，目标位置是90度，封装接口后的调用方式就变为：

```c
//main.c
//......
  /* USER CODE BEGIN WHILE */
  motor_control_context.position = deg2rad(90);
  motor_control_context.type = control_type_position;
  while (1)
  {
//......
```

### CMSIS-DSP提供的PID控制器

CMSIS-DSP数学库中提供了一个PID控制器，变量类型是 `arm_pid_instance_f32` ，将其用在我们的闭环控制中。使用方法是先调用arm_pid_init_f32配置PID系数，在闭环控制时使用 `arm_pid_f32` 计算输出PID输出值。该部分可以参考 [前文CMSIS-DSP](https://blog.csdn.net/qq570437459/article/details/140478449) 。
设计一个函数，给位置环、速度环、电流环分别创建pid控制器：

```c
//foc.c
//......
static arm_pid_instance_f32 pid_position;
static arm_pid_instance_f32 pid_speed;
static arm_pid_instance_f32 pid_torque_d;
static arm_pid_instance_f32 pid_torque_q;
void set_motor_pid(
    float position_p, float position_i, float position_d,
    float speed_p, float speed_i, float speed_d,
    float torque_d_p, float torque_d_i, float torque_d_d,
    float torque_q_p, float torque_q_i, float torque_q_d)
{
    pid_position.Kp = position_p;
    pid_position.Ki = position_i;
    pid_position.Kd = position_d;

    pid_speed.Kp = speed_p;
    pid_speed.Ki = speed_i;
    pid_speed.Kd = speed_d;

    pid_torque_d.Kp = torque_d_p;
    pid_torque_d.Ki = torque_d_i;
    pid_torque_d.Kd = torque_d_d;

    pid_torque_q.Kp = torque_q_p;
    pid_torque_q.Ki = torque_q_i;
    pid_torque_q.Kd = torque_q_d;
    arm_pid_init_f32(&pid_position, false);//false代表清空内部增量数据
    arm_pid_init_f32(&pid_speed, false);
    arm_pid_init_f32(&pid_torque_d, false);
    arm_pid_init_f32(&pid_torque_q, false);
}
//......
```

```c
//foc.h
//......
void set_motor_pid(
    float position_p, float position_i, float position_d,
    float speed_p, float speed_i, float speed_d,
    float torque_d_p, float torque_d_i, float torque_d_d,
    float torque_q_p, float torque_q_i, float torque_q_d);
//......
```

在main.c中配置pid系数，先设置为0，后续调参过程中会反复修改这里的参数。

```c
//main.c
//......
  /* USER CODE BEGIN 2 */
  set_motor_pid(
      0, 0, 0,
      0, 0, 0,
      0, 0, 0,
      0, 0, 0);
//......
```

### 位置控制

位置环的角度差值注意要使用 `cycle_diff` 函数进行周期化，因为角度是有周期的，这里使用逻辑角度以便可以多圈控制。
差值到底是 `rad - motor_logic_angle` 还是 `motor_logic_angle - rad` 呢？你可以这样想，如果真实角度 `motor_logic_angle` 是100度，输入目标角度 `rad` 是150度，pid控制器需要输出正数才能让电机转向目标角度，因此pid控制器也需要输入正数，因此只有 `rad - motor_logic_angle` 才是得到正数。
`position_loop` 函数是干嘛用的？它有输入和输出，可以和速度环、力矩环串起来，因此单独隔离出一个函数方便控制环之间的串联。
d轴是不提供转向力矩的，对位置环没有用，因此目标d轴强度设置为0。
`foc_forward` 开环控制在这里又用起来了，这个函数的本质是将目标d轴q轴强度落实到电机相线pwm通道上。
后续的速度环和位置环同理。

```c
//foc.c
//......
static float position_loop(float rad)
{
    float diff = cycle_diff(rad - motor_logic_angle, position_cycle);
    return arm_pid_f32(&pid_position, diff);
}

void lib_position_control(float rad)
{
    float d = 0;
    float q = position_loop(rad);
    foc_forward(d, q, rotor_logic_angle);
}
//......
```

### 速度控制

速度是没有周期的，所以不需要使用 `cycle_diff` 函数周期化差值。

```c
//foc.c
//......
static float speed_loop(float speed_rad)
{
    float diff = speed_rad - motor_speed;
    return arm_pid_f32(&pid_speed, diff);
}
void lib_speed_control(float speed)
{
    float d = 0;
    float q = speed_loop(speed);
    foc_forward(d, q, rotor_logic_angle);
}
//......
```

### 力矩（电流）控制

d轴和q轴都有力矩环，将d轴和q轴电流与宏定义设定的最大电流的比例看作【力矩强度】，力矩环输入的是0到1之间的百分比强度数据。

```c
//foc.c
//......
static float torque_d_loop(float d)
{
    float diff = d - motor_i_d / MAX_CURRENT;
    return arm_pid_f32(&pid_torque_d, diff);
}

static float torque_q_loop(float q)
{
    float diff = q - motor_i_q / MAX_CURRENT;
    return arm_pid_f32(&pid_torque_q, diff);
}

void lib_torque_control(float torque_norm_d, float torque_norm_q)
{
    float d = torque_d_loop(torque_norm_d);
    float q = torque_q_loop(torque_norm_q);
    foc_forward(d, q, rotor_logic_angle);
}
//......
```

### 位置-速度-力矩控制

将位置环、速度环、力矩环串联起来，就是【位置-速度-力矩控制】。可前往查看 [前文位置、速度、电流控制](https://blog.csdn.net/qq570437459/article/details/138872078) 的控制框图。
位置-速度-力矩联合控制的时候，主角是还是位置环，速度、力矩是运行过程中的最大值，比如：输入的速度是30rad/s，意思是电机角度到位过程中的速度按照30rad/s进行控制，角度到位后，电机速度会按照0rad/s进行控制。
这里的代码抽出了速度-力矩控制作为一个单独的函数，这样既开放了【速度-力矩控制】的接口，也可以被【位置-速度-力矩控制】调用。

```c
//foc.c
//......
void lib_speed_torque_control(float speed_rad, float max_torque_norm)
{
    float torque_norm = speed_loop(speed_rad);
    torque_norm = min(fabs(torque_norm), max_torque_norm) * (torque_norm > 0 ? 1 : -1);
    lib_torque_control(0, torque_norm);
}

void lib_position_speed_torque_control(float position_rad, float max_speed_rad, float max_torque_norm)
{
    float speed_rad = position_loop(position_rad);
    speed_rad = min(fabs(speed_rad), max_speed_rad) * (speed_rad > 0 ? 1 : -1);
    lib_speed_torque_control(speed_rad, max_torque_norm);
}
//......
```

### PID系数调节

到目前位置，已经在ADC中断中放置了FOC代码，也在 `main.c` 中设置好了闭环控制类型（示例是位置控制），只要再设置好PID系数，电机就能进行闭环动作了。PID系数调节比较依靠经验，由于本人能力有限，我无法深入讲解，网上有大量的PID系数调节教程。

-  **位置环** 

本文选择的电机是云台电机，这里的位置环的PID系数只用到P系数和D系数，可以在主while(1)循环里打印电机实时角度辅助调节。
首先设定为位置控制模式，由于FOC代码里位置控制是按照逻辑角度进行控制的，因此这里设置的90度是逻辑角度：

```c
//main.c
//......
  /* USER CODE BEGIN WHILE */
  motor_control_context.position = deg2rad(90);
  motor_control_context.type = control_type_position;
  while (1)
  {
  	printf("%f\n", motor_logic_angle);
  	/* USER CODE END WHILE */
//......
```

调节P系数建议从2开始，0.1为步距往上调整，直到电机到位过程中出现轻微位置弹簧感：
 ![在这里插入图片描述](./assets/60_40.png)

然后设定D系数，建议从5开始，1为步距往上调，直到弹簧感消失，这样一个归位迅速而回弹轻微的位置环就调节好了：
 ![在这里插入图片描述](./assets/60_41.png)

-  **速度环** 

调节转速环的时候，转速滤波系数 `filter_alpha_speed` 非常重要，决定了计算出来的速度是否平稳，本文使用的低通滤波，如果想要滤波平稳一点，那么就会有滞后，如果想要速度更新及时一点，那么滤波结果波动就大，这个转速滤波的参数也是需要自己调节测试的，我为了验证FOC算法，设定的0.07，滞后比较厉害，但是速度滤波出来比较平稳。
在主while(1)前设定FOC为速度控制模式：

```c
//main.c
//......
  /* USER CODE BEGIN WHILE */
  motor_control_context.speed = 20 * 2 * PI;
  motor_control_context.type = control_type_speed;
  while (1)
  {
  	printf("%f\n", motor_speed);
  	/* USER CODE END WHILE */
//......
```

速度环主要是使用P系数和I系数，速度波动比较剧烈，D系数干扰大。P系数要给的非常小，建议从0.01开始，步距0.001往上调节，I系数从0.001开始往上调节。
经过我简单的调节，本文选用的电机在空载时，在速度环模式下，速度大概能到每秒122.6弧度（每秒39转，每分钟1171转）左右。
 ![在这里插入图片描述](./assets/60_42.png)

-  **力矩环** 

力矩环同样有滤波系数 `filter_alpha_i_d` 和 `filter_alpha_i_q` ，分别对应d轴电流和q轴电流滤波，我为了验证FOC算法，这两个参数设置的0.1。
在主while(1)前设定FOC为力矩控制模式：

```c
//main.c
//......
  /* USER CODE BEGIN WHILE */
  motor_control_context.torque_norm_d = 0;
  motor_control_context.torque_norm_q = 0.4;
  motor_control_context.type = control_type_torque;
  while (1)
  {
  	printf("%f\n", motor_speed);
  	/* USER CODE END WHILE */
//......
```

经过我简单的调节，本文选用的电机在空载时，在力矩环模式下，空载速度大概能到每秒145.6弧度（每秒23转，每分钟1391转）左右。
 ![在这里插入图片描述](./assets/60_43.png)

力矩环的PID参数调节方式通常单独调节d轴电流然后复制一份给q轴，或者在堵转情况下对q轴进行调节。

-  **位置-速度-力矩串级PID** 

本文的PID系数没有经过精调，三者串级控制的时候，最好不要直接使用上面单独控制时的PID系数，需要重新调节，要从最内环开始串级调节到最外环，即先调好力矩控制，再调好速度-力矩控制，再调好位置-速度-力矩控制。

---

## 注意点

- 注意调试过程中打断点或者点击Stop Debug的时候，不要暂停时间过长，因为暂停的时候电机相线的pwm占空比也固定住了，如果某一相的占空比刚好固定在非常高的状态，会导致电机迅速发热。

- stm32f103系列的算力有限，keil编译的时候请开启-O3优化，否则可能需要再降低SPI频率或者提高高级定时器重复计数器以降低FOC代码计算频率。

- 用到了 `__attribute__((weak))` 这个语法，需要使用keil5的ARM Compiler 6编译器。

---

至此已经完成了从零开始实现stm32无刷电机FOC，本文完整代码工程全部开源，可前往查看： [https://gitee.com/best_pureer/stm32_foc](https://gitee.com/best_pureer/stm32_foc) 。