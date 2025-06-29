# LKS08x_FOC_SensorLessV4.25 之前库函数升级操作步骤

1、首先保证全工程能够编译通过。

2、将 LKS08x_FOC_SensorLessV4.24 文件内 LKS32MC08x_Periph_Driver 内的 Include 和 Source 替换为新的库函数。

![](images/1ac15e046b79ee7a7607858f73cf382fb73b5cf872339985a608fbb3f2e5d0f2.jpg)

3、将文件所有的 Iks32cm08x_xxx.c 库函数放入 keil 内。

![](images/8310a2f766aeac67636f933fb8d7579da70b895560dbe4732608194932cc92bf.jpg)

4、将 hardware_init.h 声明的 PGA_init、DAC_init、CMP_init 的 init 大写的 i 改为小写的 i，即 PGA_init、DAC_init、CMP_init。因为最新库函数将库函数定义的模块初始化名称 xxx_Init() (xxx 可以是 PGA，CMP 等) 的 init 首字母大写，这样统一后用户使用不会混乱，所以用户自定义的模块初始化配置函数为 xxx_init() 的 init 就为小写开头。

![](images/9baed2626d5f7e11de62a48f7f6c15abbd11c5639aa38c57e27268dae5497014.jpg)

5、hardware_init.h 声明的 PGA_Init、DAC_Init、CMP_Init 更改过后，对应的 hardware_init.c 也需要更改。

![](images/42b861f102fb4a2cc49567d6b44f925deb11620a12c0095a5374030603ccb8db.jpg)

![](images/96cd1f77e6fa95c681a60b5cca2c21560e48db810436d7e5b02872cbb32f5711.jpg)

6、CMP_init 初始化内容需要更改，对应结构体成员名称发生改变。CMP_InitStructure.CMP0_InEnable 改为 CMP_InitStructure.CMP0_IN_EN

CMP InitStruct.CMP1_InEnable 改为 CMP InitStruct.CMP1_IN_ENCMP InitStruct.CMP_FltCnt = 15; 改为 CMP InitStruct.FIL_CLK10_DIV16 = 15;CMP InitStruct.CMP_CLK_EN = ENABLE; 改为 CMP InitStruct.CLK10_EN = ENABLE;Comparator_init(&CMP InitStruct); 改为 CMP Init(&CMP InitStruct);

# 更改前：

![](images/a605ec7cade81fda813cc215b67667832ade717a8739007c1f2c5ef8d0af5ff9.jpg)

# 更改后：

![](images/abdc863bf8c4bea554e566f753356fc24cafab82a30b7a5a3890d7848b064e7b.jpg)

7、新的库函数将OPA的放大倍数放置在lks32mc08x_opa.h文件内，所以导致

hardware_config.h 内的放大倍数宏定义重复，所以将 hardware_config.h 内的 OPA 放大倍数宏定义删除。

更改前：

![](images/916c2426fd382f5fa9937a92d54f858c345c88e6fb5565739ae9236627f2821c.jpg)

更改后：

![](images/218622a4e3e6b6ff95074469aa15ebe16b1fdb4be24cb44d68596987f423d091.jpg)

8、因为新的库函数将芯片内置温度模块单独做了一个.c 和.h 文件，所以导致与 global_variable.c、hardware_init.c 和 process_control.c 内定义的相关温度传感器的函数重复，因此我们需要将

1）global_variable.c 内的【Stru_TempertureCof_Def m_TempertureCof；/*温度传感器系数 */】删除；

![](images/6b9525b8dae92fe3ce387d558470d8cc1baca4bc9014b7eaa9242f4d6e9602df.jpg)

2）hardware_init.c 内的【void TempSensor_Init(void)】函数删除。

![](images/c5d90dc715b8b5f6812e540f34e5c7b66f660c040c7772cf3b0481cbf6115155.jpg)

3）process_control.c 内的【s16GetCurrentTemperature(s16ADC_value)】函数删除。

![](images/dbbb83661ae6d91c27110242e6ae97376a0a46b7d986b47ae4d0b9fb4e07bdff.jpg)

# 》》》到此刻在编译就不会报错啦！！！

9、最后还有5个警告需要去掉，主要原因是占空比寄存器是有符号型，但负数赋值都强制转为无符号型，所以我们将强制转换语句去掉即可。更改hardware_init.c和SignalChain_Sample.c文件。

![](images/2f165e870f61575b682efb508f5284f8fc411d109d2b960b603e6f28a9c72081.jpg)

![](images/22e509e05acdda70fd6eebfa7ea847121622b93c8ff1dfde65c6278c28ada0f6.jpg)