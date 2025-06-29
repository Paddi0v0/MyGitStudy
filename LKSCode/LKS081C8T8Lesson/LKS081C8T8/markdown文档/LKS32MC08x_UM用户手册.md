# LKS32MC08x User Manual

© 2019, 版权归凌鸥创芯所有机密文件，未经许可不得扩散

# 目录

目录. II

表格目录

图片目录

# 1 文档约定

1.1 寄存器读写权限 11.2 缩略词汇表 1

# 2 地址空间 2

# 3 内核 3

3.1 ARM@CORTEXTM- M0 核心 3

3.2 NVIC控制器 3

3.3 异常和中断 4

3.4 SYSTICK定时器 5

3.4.1 SYST_CSR 控制和状态寄存器 5

3.4.2 SYST_RVR 重载值寄存器 6

3.4.3 SYST_CVR 当前值寄存器 7

# 4 模拟电路 8

4.1 简述 8

4.2 POWER 电源管理系统 9

4.3 CLOCK 时钟系统 10

4.4 BGP 基准电压源 10

4.5 ADC 模数转换器 11

4.6 OPA 运算放大器 11

4.7 CMP 比较器 12

4.8 TMP 温度传感器 12

4.9 DAC 数模转换器 13

# 5 系统控制及时钟复位 15

5.1 时钟 15

5.1.1 时钟源. 15

5.1.2 功耗管理及休眠唤醒 17

5.1.2.1 休眠. 17

5.1.2.2 唤醒. 17

5.1.2.3 外设时钟门控. 17

5.1.2.4 外设时钟分频. 18

5.2 复位. .错误|未定义书签。

5.2.1 复位源. 18

5.2.1.1 硬件复位. 18

5.2.1.1.1 硬件复位架构. 18

5.2.1.1.2 硬件复位记录. 19

5.2.1.2 软件复位. 19

5.2.2 复位作用域. 19

5.3 寄存器. 20

5.3.1 地址分配. 20

5.3.2 SYS_AFE_CMP 模拟前端信息寄存器. 21

5.3.3 模拟寄存器概述. 22

5.3.4 SYS_AFE_REG0 模拟配置寄存器0. 22

5.3.5 SYS_AFE_REG1 模拟配置寄存器1. 23

5.3.6 SYS_AFE_REG2 模拟配置寄存器2. 24

5.3.7 SYS_AFE_REG3 模拟配置寄存器3. 24

5.3.8 SYS_AFE_REG4 模拟配置寄存器4. 26

5.3.9 SYS_AFE_REG5 模拟配置寄存器5. 26

5.3.10 SYS_AFE_REG6 模拟配置寄存器6. 28

5.3.11 SYS_AFE_REG7 模拟配置寄存器7. 29

5.3.12 SYS_AFE_DAC DAC 数字量寄存器. 30

5.3.13 SYS_CLK_CFG 时钟控制寄存器. 30

5.3.14 SYS_RST_CFG 复位控制寄存器. 31

5.3.15 SYS_RST_SRC 复位源记录寄存器. 32

5.3.16 SYS_CLR_RST 复位源记录清除寄存器. 32

5.3.17 SYS_CLK_DIV0 外设时钟分频寄存器0. 32  5.3.18 SYS_CLK_DIV2 外设时钟分频寄存器2. 33  5.3.19 SYS_CLK_FEN 外设时钟门控寄存器 33  5.3.20 SYS_CLK_SLP 休眠寄存器 34  5.3.21 SYS_TRIM 校正模式寄存器 34  5.3.22 SYS_SFT_RST 软复位寄存器 35  5.3.23 SYS_WR_PROTECT 写保护寄存器 35  5.3.24 SYS_AFE_DAC_AMC DAC 增益校正寄存器 36  5.3.25 SYS_AFE_DAC_DC DAC 直流偏置寄存器 36

# 6 FLASH 38

6.1 概述 38

6.2 功能特点 38

6.2.1 功能描述 39

6.2.1.1 复位操作 39

6.2.1.2 休眠操作 39

6.2.1.3 FLASH 读取操作 40

6.2.1.4 FLASH 编程操作 40

6.2.1.5 FLASH 擦除操作 42

6.2.1.6 FLASH 预取操作 43

6.2.1.7 FLASH 加密保护 43

6.2.1.8 FLASH 在线升级(IAP) 44

6.2.1.8.1 开启中断的在线升级 44

6.2.1.8.2 关闭中断的在线升级 44

6.2.1.8.3 在线升级函数的位置 45

6.3 寄存器 45

6.3.1 地址分配 45

6.3.2 FLASH_CFG 配置寄存器（推荐先读回，按或/与方式修改） 45

6.3.3 FLASH_ADDR 地址寄存器 46

6.3.4 FLASH_WDATA 与数据寄存器 47

6.3.5 FLASH_RDATA 读数据寄存器 47

6.3.6 FLASH_ERASE 擦除控制寄存器 476.3.7 FLASH_PROTECT 加密状态寄存器 486.3.8 FLASH_READY 工作状态寄存器 48

# 7 DMA 52

7.1 概述 527.2 请求 547.3 优先级 557.4 仲裁 557.5 中断 567.6 寄存器 567.6.1 地址分配 567.6.2 DMA_CTRLDMA 控制寄存器 567.6.3 DMA_IFDMA 中断标志寄存器 577.6.4 DMA 通道配置寄存器 577.6.4.1 DMA_CCRx (where  $\mathrm{x} = 0,1,2,3$  577.6.4.2 DMA_CTMSx (where  $\mathrm{x} = 0,1,2,3$  597.6.4.3 DMA_CPARx (where  $\mathrm{x} = 0,1,2,3$  607.6.4.4 DMA_CMARx (where  $\mathrm{x} = 0,1,2,3$  60

# 8 GPIO 62

8.1 概述 628.1.1 功能框图 628.1.2 产品特点 638.2 寄存器 648.2.1 地址分配 648.2.2 GPIOx PIE 648.2.3 GPIOx POE 658.2.4 GPIOx PDI 668.2.5 GPIOx PDO 668.2.6 GPIOx PUE 678.2.7 GPIOx PODE 67

8.2.8 GPIOx_LCKR. .688.2.9 GPIOx_F3210. .698.2.10 GPIOx_F7654. .708.2.11 GPIOx_FBA98. .708.2.12 GPIOx_FFEDC. .718.2.13 外部中断、唤醒、锁定保护. .718.2.13.1 EXTI_CR0. .718.2.13.2 EXTI_CR1. .738.2.13.3 EXTI_IF. .748.2.13.4 LCKR_PRT. .758.2.13.5 WAKE_POL. .768.2.13.6 WAKE_EN. .768.3 实现说明. .778.3.1 上拉实现. .778.4 应用指南. .778.4.1 配置锁定. .778.4.2 外部中断. .798.4.3 使用GPIO的模拟功能. .799 CRC. .809.1 概述. .809.2 基本原理. .809.3 基本概念. .809.3.1 对应关系. .809.3.2 生成多项式. .819.3.3 校验码位数. .819.3.4 生成步骤. .819.4 寄存器. .829.4.1 地址分配. .829.4.2 寄存器描述. .839.4.2.1 CRC_DR CRC 信息码寄存器. .83

9.4.2.2 CRC_CR CRC 控制寄存器 839.4.2.3 CRC_INIT CRC 初始码寄存器 849.4.2.4 CRC_POL CRC 生成码寄存器 85

# 10 ADC 86

10.1 概述 86

10.1.1 功能框图 86

10.1.2 ADC 触发方式 88

10.1.3 ADC 通道选择 88

10.1.4 ADC 中断 89

10.1.5 ADC 输出数制 89

10.1.6 ADC 基准电压与量程 90

10.1.6.1 2.4V 基准电压模式 90

10.1.6.2 1.2V 基准电压模式 91

10.1.7 ADC 校正 91

10.1.8 ADC 配置流程 92

10.2 寄存器 93

10.2.1 地址分配 93

10.2.2 采样数据寄存器 94

10.2.2.1 ADC0_DAT0 94

10.2.2.2 ADC0_DAT1 94

10.2.2.3 ADC0_DAT2 95

10.2.2.4 ADC0_DAT3 95

10.2.2.5 ADC0_DAT4 96

10.2.2.6 ADC0_DAT5 96

10.2.2.7 ADC0_DAT6 96

10.2.2.8 ADC0_DAT7 97

10.2.2.9 ADC0_DAT8 97

10.2.2.10 ADC0_DAT9 98

10.2.2.11 ADC0_DAT10 98

10.2.2.12 ADC0_DAT11 98

10.2.2.13 ADC0_DAT12. 99

10.2.2.14 ADC_DAT13. 99

10.2.2.15 ADC0_DAT14. 100

10.2.2.16 ADC0_DAT15. 100

10.2.2.17 ADC0_DAT16. 100

10.2.2.18 ADC0_DAT17. 101

10.2.2.19 ADC0_DAT18. 101

10.2.2.20 ADC0_DAT19. 102

# 10.2.3 信号来源寄存器 102

10.2.3.1 ADC0_CHN0. 102

10.2.3.2 ADC0_CHN1. 103

10.2.3.3 ADC0_CHN2. 103

10.2.3.4 ADC0_CHN3. 104

10.2.3.5 ADC0_CHN4. 104

10.2.3.6 ADC0_CHN5. 105

10.2.3.7 ADC0_CHN6. 105

10.2.3.8 ADC0_CHN7. 106

10.2.3.9 ADC0_CHN8. 106

10.2.3.10 ADC0_CHN9. 107

# 10.2.4 分段通道数寄存器 108

10.2.4.1 ADC0_CHNT0. 108

10.2.4.2 ADC0_CHNT1. 108

10.2.5 配置寄存器 109

10.2.5.1 ADC0_CFG. 109

10.2.5.2 ADC0_TRIG. 109

10.2.6 增益选择寄存器 111

10.2.6.1 ADC0_GAIN0. 111

10.2.6.2 ADC0_GAIN1. 111

10.2.7 中断寄存器 112

10.2.7.1 ADC0_IE. 112

# LKS32MC08x User Manual

10.2.7.2 ADC0_IF. 113

10.2.8 软件触发寄存器 113

10.2.8.1 ADC0 SWT. 113

10.2.9 直流偏置寄存器 114

10.2.9.1 ADC0_DC_A0 114

10.2.9.2 ADC0_DC_A1 114

10.2.9.3 ADC0_DC_B0 115

10.2.9.4 ADC0_DC_B1 115

10.2.10 增益校正寄存器 115

10.2.10.1 ADC0_AMC_A0 115

10.2.10.2 ADC0_AMC_A1 116

10.2.10.3 ADC0_AMC_B0 116

10.2.10.4 ADC0_AMC_B1 117

10.2.11 通道0阈值寄存器 117

10.2.11.1 ADC0_DATA0_TH 117

10.3 实现说明 118

10.3.1 DMA请求 118

10.3.2 连续采样 118

10.4 应用指南 118

10.4.1 ADC采样触发模式 118

10.4.1.1 单段触发模式 120

10.4.1.2 两段触发模式 120

10.4.1.3 四段触发模式 121

10.4.2 中断 122

10.4.2.1 单段触发采样完成中断 122

10.4.2.2 两段触发采样完成中断 122

10.4.2.3 四段触发采样完成中断 122

10.4.3 配置修改 122

10.4.4 选择对应的模拟通道 122

11 通用定时器 124

11.1 概述. 124

11.1.1 功能框图. 124

11.1.1.1 总线接口模块. 124

11.1.1.2 寄存器模块. 124

11.1.1.3 IO 滤波模块. 125

11.1.1.4 通用定时器模块. 125

11.1.1.5 编码器模块. 125

11.1.1.6 时钟分频模块. 125

11.1.2 功能特点. 125

11.2 实现说明. 126

11.2.1 时钟分频. 126

11.2.2 滤波. 126

11.2.3 模式. 126

11.2.3.1 计数器. 126

11.2.3.2 比较模式. 127

11.2.3.3 捕获模式. 128

11.2.4 编码器. 129

11.2.4.1 正交编码信号. 129

11.2.4.2 符号加脉冲信号. 130

11.2.4.3 CCW/CW 双脉冲信号. 131

11.3 寄存器. 131

11.3.1 地址分配. 131

11.3.2 系统控制寄存器. 132

11.3.2.1 UTIMER_CFG. 132

11.3.3 滤波控制寄存器. 133

11.3.3.1 UTIMER_FLT_TH01. 133

11.3.3.2 UTIMER_FLT_TH23. 134

11.3.4 定时器寄存器. 134

11.3.4.1 UTIMER_UNT0_CFG_Timer0 配置寄存器. 134

11.3.4.2 UTIMER_UNT1_CFG_Timer1 配置寄存器. 136

# 11.3.4.3 UTIMER_UNT2_CFG_Timer2 配置寄存器 137

11.3.4.4 UTIMER_UNT3_CFG_Timer3 配置寄存器 13811.3.4.5 UTIMER_UNT0_TH Timer 0 门限寄存器 13911.3.4.6 UTIMER_UNT1_TH Timer 1 门限寄存器 14011.3.4.7 UTIMER_UNT2_TH Timer 2 门限寄存器 14011.3.4.8 UTIMER_UNT3_TH Timer 3 门限寄存器 14111.3.4.9 UTIMER_UNT0_CNT Timer 0 计数寄存器 14111.3.4.10 UTIMER_UNT1_CNT Timer 1 计数寄存器 14111.3.4.11 UTIMER_UNT2_CNT Timer 2 计数寄存器 14211.3.4.12 UTIMER_UNT3_CNT Timer 3 计数寄存器 14211.3.4.13 UTIMER_UNT0_CMP0 Timer 0 通道 0 比较捕获寄存器 14311.3.4.14 UTIMER_UNT0_CMP1 Timer 0 通道 1 比较捕获寄存器 14311.3.4.15 UTIMER_UNT1_CMP0 Timer 1 通道 0 比较捕获寄存器 14411.3.4.16 UTIMER_UNT1_CMP1 Timer 1 通道 1 比较捕获寄存器 14411.3.4.17 UTIMER_UNT2_CMP0 Timer 2 通道 0 比较捕获寄存器 14511.3.4.18 UTIMER_UNT2_CMP1 Timer 2 通道 1 比较捕获寄存器 14511.3.4.19 UTIMER_UNT3_CMP0 Timer 3 通道 0 比较捕获寄存器 14611.3.4.20 UTIMER_UNT3_CMP1 Timer 3 通道 1 比较捕获寄存器 14611.3.4.21 UTIMER_UNT0_EVT Timer0 外部事件选择寄存器 14711.3.4.22 UTIMER_UNT1_EVT Timer1 外部事件选择寄存器 14711.3.4.23 UTIMER_UNT2_EVT Timer2 外部事件选择寄存器 14811.3.4.24 UTIMER_UNT3_EVT Timer3 外部事件选择寄存器 14811.3.5 编码器寄存器 14911.3.5.1 UTIMER_ECD0_CFG Encoder0 配置寄存器 14911.3.5.2 UTIMER_ECD0_TH Encoder0 计数门限寄存器 15011.3.5.3 UTIMER_ECD0_CNT Encoder0 计数值寄存器 15011.3.6 中断管理寄存器 15111.3.6.1 UTIMER_IE 中断使能寄存器 15111.3.6.2 UTIMER_IF 中断标志寄存器 15211.3.7 DMA 管理寄存器 153

11.3.7.1 UTIMER_RE DMA 请求使能寄存器 153

# 12 HALL 信号处理模块 155

12.1 综述 155

12.2 实现说明 155

12.2.1 信号来源 155

12.2.2 工作时钟 155

12.2.3 信号滤波 155

12.2.4 捕获 156

12.2.5 中断 156

12.2.6 数据流程 157

12.3 寄存器 157

12.3.1 地址分配 157

12.3.2 HALL_CFG HALL 模块配置寄存器 157

12.3.3 HALL_INFO HALL 模块信息寄存器 158

12.3.4 HALL_WIDTH HALL 宽度计数值寄存器 159

12.3.5 HALL_TH HALL 模块计数器门限值寄存器 159

12.3.6 HALL_CNT HALL 计数寄存器 160

# 13 MCPWM 161

13.1 概述 161

13.1.1 Base Counter 模块 162

13.1.2 Fail 信号处理 163

13.1.3 MCPWM 特殊输出状态 164

13.1.4 IO DRIVER 模块 164

13.1.4.1 MCPWM 波形输出- 中心对齐模式 165

13.1.4.2 MCPWM 波形控制- 中心对齐推挽模式 166

13.1.4.3 MCPWM 波形输出- 边沿对齐模式 166

13.1.4.4 MCPWM 波形控制- 边沿对齐推挽模式 167

13.1.4.5 MCPWM IO 死区控制 168

13.1.4.6 MCPWM IO 极性设置 168

13.1.4.7 MCPWM IO 自动保护 168

13.1.5 ADC Trigger Timer 模块. 169

13.1.6 MCPWM 主要事件列表. 169

13.2 寄存器. 169

13.2.1 地址分配. 169

13.2.2 MCPWM_TH00. 171

13.2.3 MCPWM_TH01. 172

13.2.4 MCPWM_TH10. 172

13.2.5 MCPWM_TH11. 173

13.2.6 MCPWM_TH20. 173

13.2.7 MCPWM_TH21. 173

13.2.8 MCPWM_TH30. 174

13.2.9 MCPWM_TH31. 174

13.2.10 MCPWM_TMR0. 175

13.2.11 MCPWM_TMR1. 175

13.2.12 MCPWM_TMR2. 176

13.2.13 MCPWM_TMR3. 176

13.2.14 MCPWM_TH. 176

13.2.15 MCPWM_UPDATE. 177

13.2.16 MCPWM_IE. 178

13.2.17 MCPWM_IF. 179

13.2.18 MCPWM_EIE. 180

13.2.19 MCPWM_EIF. 181

13.2.20 MCPWM_RE. 182

13.2.21 MCPWM_PP. 182

13.2.22 MCPWM_IO01. 183

13.2.23 MCPWM_IO23. 184

13.2.24 MCPWM_SDCPG. 185

13.2.25 MCPWM_TCLK. 185

13.2.26 MCPWM_FAIL. 186

13.2.27 MCPWM_PRT. 187

13.2.28 MCPWM_CNT. 188 13.2.29 MCPWM_DTH0. 188 13.2.30 MCPWM_DTH01. 189 13.2.31 MCPWM_DTH10. 189 13.2.32 MCPWM_DTH11. 189 13.2.33 MCPWM_DTH20. 190 13.2.34 MCPWM_DTH21. 190 13.2.35 MCPWM_DTH30. 191 13.2.36 MCPWM_DTH31. 191

# 14 UART 192

14.1 概述 192

14.2 功能说明 192

14.2.1 发送 192 14.2.2 接收 192 14.2.3 波特率配置 192 14.2.4 收发端口互换(TX/RX互换) 193 14.2.5 DMA配置 193

# 14.3 寄存器 194

14.3.1 地址分配 194 14.3.2 UARTx_CTRL UARTx 控制寄存器 194 14.3.3 UARTx_DIVH UARTx 波特率设置高字节寄存器 195 14.3.4 UARTx_DIVL UARTx 波特率设置低字节寄存器 195 14.3.5 UARTx_BUFF UARTx 收发缓冲寄存器 196 14.3.6 UARTx_ADR UARTx 地址匹配寄存器 196 14.3.7 UARTx_STT UARTx 状态寄存器 196 14.3.8 UARTx_IE UARTx 中断使能寄存器 197 14.3.9 UARTx_IF UARTx 中断标志寄存器 198 14.3.10 UARTx_INV UARTx IO 翻转寄存器 199

# 15 DSP 200

15.1 概述 200

15.1.1 功能框图. 201

15.1.2 DSP核寄存器 201

15.1.3 位宽. 202

15.1.4 指令周期. 202

15.1.5 地址空间. 202

15.2 寄存器. 203

15.2.1 地址分配. 203

15.2.2 DSP状态控制寄存器. 203

15.2.2.1 DSP_SC. 203

15.2.3 DSPsin/cos相关寄存器. 204

15.2.3.1 DSP_THETA. 204

15.2.3.2 DSP_SIN. 205

15.2.3.3 DSP_COS. 205

15.2.4 DSP arctan相关寄存器. 206

15.2.4.1 DSP_X. 206

15.2.4.2 DSP_Y. 206

15.2.4.3 DSP_MOD. 207

15.2.4.4 DSP_ARCTAN. 207

15.2.5 DSP除法相关寄存器. 208

15.2.5.1 DSP_DID. 208

15.2.5.2 DSP_DIS. 208

15.2.5.3 DSP_QUO. 209

15.2.5.4 DSP_REM. 209

15.2.6 DSP开方相关寄存器. 210

15.2.6.1 DSP_RAD. 210

15.2.6.2 DSP_SQRT. 210

15.3 DSP指令集. 211

15.3.1 Instruction Set Summary. 211

15.3.2 ADD. 212

15.3.2.1 编码. 212

15.3.2.2 汇编语法. .212 15.3.2.3 伪代码. .212

# 15.3.3 ADDI (reserved) .212

15.3.3.1 指令编码. .212 15.3.3.2 汇编语法. .212 15.3.3.3 伪代码. .212

# 15.3.4 SUB. .213

15.3.4.1 指令编码. .213 15.3.4.2 汇编语法. .213 15.3.4.3 伪代码. .213

# 15.3.5 ASR. .213

15.3.5.1 指令编码. .213 15.3.5.2 汇编语法. .213 15.3.5.3 伪代码. .213

# 15.3.6 ASRI. .214

15.3.6.1 指令编码. .214 15.3.6.2 汇编语法. .214 15.3.6.3 伪代码. .214

# 15.3.7 LSL. .214

15.3.7.1 指令编码. .214 15.3.7.2 汇编语法. .214 15.3.7.3 伪代码. .214

# 15.3.8 LSLI. .214

15.3.8.1 指令编码. .214 15.3.8.2 汇编语法. .215 15.3.8.3 伪代码. .215

# 15.3.9 MAC. .215

15.3.9.1 指令编码. .215 15.3.9.2 汇编语法. .215 15.3.9.3 伪代码. .215

# 15.3.10 MACI (reserved) 215

15.3.10.1 指令编码 216

15.3.10.2 汇编语法 216

15.3.10.3 伪代码 216

# 15.3.11 DIV 216

15.3.11.1 指令编码 216

15.3.11.2 汇编语法 216

15.3.11.3 伪代码 216

# 15.3.12 SAT 217

15.3.12.1 指令编码 217

15.3.12.2 汇编语法 217

15.3.12.3 伪代码 217

# 15.3.13 SATI (reserved) 217

15.3.13.1 指令编码 217

15.3.13.2 汇编语法 217

15.3.13.3 伪代码 217

# 15.3.14 SIN_COS 217

15.3.14.1 指令编码 217

15.3.14.2 汇编语法 218

15.3.14.3 伪代码 218

# 15.3.15 ARCTAN 218

15.3.15.1 指令编码 218

15.3.15.2 汇编语法 218

15.3.15.3 伪代码 218

# 15.3.16 SQRT 218

15.3.16.1 指令编码 218

15.3.16.2 汇编语法 218

15.3.16.3 伪代码 218

# 15.3.17 LDRWI 219

15.3.17.1 指令编码 219

15.3.17.2 汇编语法. .219  15.3.17.3 伪代码. .219

# 15.3.18 LDRDHI. .219

15.3.18 LDRDHI. .219  15.3.18.1 指令编码. .219  15.3.18.2 汇编语法. .219  15.3.18.3 伪代码. .219

# 15.3.19 STRWI. .220

15.3.19 STRWI. .220  15.3.19.1 指令编码. .220  15.3.19.2 汇编语法. .220  15.3.19.3 伪代码. .220

# 15.3.20 STRDHI (reserved) .220

15.3.20.1 指令编码. .220  15.3.20.2 汇编语法. .220  15.3.20.3 伪代码. .220

# 15.3.21 JUMP (reserved) .221

15.3.21.1 指令编码. .221  15.3.21.2 汇编语法. .221  15.3.21.3 伪代码. .221

# 15.3.22 JUMPI. .221

15.3.22.1 指令编码. .221  15.3.22.2 汇编语法. .221  15.3.22.3 伪代码. .221

# 15.3.23 JLE. .221

15.3.23.1 指令编码. .221  15.3.23.2 汇编语法. .222  15.3.23.3 伪代码. .222

# 15.3.24 JLEI. .222

15.3.24.1 指令编码. .222  15.3.24.2 汇编语法. .222  15.3.24.3 伪代码. .222

15.3.25 IRQ. 222

15.3.25.1 指令编码. 222

15.3.25.2 汇编语法. 222

15.3.25.3 伪代码. 222

15.3.26 R（仅用于模拟器） 223

15.3.26.1 指令编码. 223

15.3.26.2 汇编语法. 223

15.3.26.3 伪代码. 223

15.3.27 BREAK（仅用于模拟器） 223

15.3.27.1 指令编码. 223

15.3.27.2 汇编语法. 223

15.3.27.3 伪代码. 223

15.3.28 END（仅用于模拟器） 223

15.3.28.1 指令编码. 223

15.3.28.2 汇编语法. 223

15.3.28.3 伪代码. 224

15.4 应用指南 224

15.4.1 访存寻址. 224

15.4.2 Load after Store. 225

15.4.3 多周期指令的的延迟提交. 225

15.4.4 数据填装. 225

16 I2C. 227

16.1 概述. 227

16.2 主要特性. 227

16.3 功能描述. 227

16.3.1 功能框图. 227

16.3.2 功能说明. 228

16.3.2.1 模式选择. 228

16.3.2.2 I2C 接口从模式. 229

16.3.2.2.1 从模式单字节传输. 230

# LKS32MC08x User Manual

16.3.2.2.2 从模式单字节发送 23116.3.2.2.3 从模式单字节接收 231

16.3.2.3 从模式 DMA 传输 231

16.3.2.3.1 从模式 DMA 发送 231

16.3.2.3.2 从模式 DMA 接收 232

16.3.2.4 I2C 接口主模式 232

16.3.2.4.1 主模式单字节传输 233

16.3.2.4.2 主模式单字节发送 233

16.3.2.4.3 主模式单字节接收 234

16.3.2.4.4 主模式 DMA 传输 234

16.3.2.4.5 主模式 DMA 发送 234

16.3.2.4.6 主模式 DMA 接收 235

16.3.2.5 I2C 总线异常处理 236

16.3.2.6 DMA 传输 236

16.3.2.7 CPU 传输 237

16.3.2.8 中断处理 237

16.3.2.9 通讯速度设置 237

16.4 寄存器 238

16.4.1 地址分配 238

16.4.2 寄存器说明 238

16.4.2.1 I2C0_ADDR 地址寄存器 238

16.4.2.2 I2C0_CFG 系统控制寄存器 238

16.4.2.3 I2C0_SCR 状态控制寄存器 239

16.4.2.4 I2C0_DATA 数据寄存器 240

16.4.2.5 I2C0_MSCR 主模式寄存器 241

16.4.2.6 I2C0_BCR DMA 传输控制寄存器 242

17 SPI 243

17.1 概述 243

17.2 主要特性 243

17.3 功能描述 243

17.3.1 功能框图. 243

17.3.2 功能说明. 244

17.3.2.1 全双工模式. 244  17.3.2.2 半双工模式. 245  17.3.2.3 片选信号. 246  17.3.2.4 通讯格式. 247  17.3.2.5 数据格式. 249  17.3.2.6 DMA传输. 249  17.3.2.7 CPU传输. 249  17.3.2.8 外部事件传输. 250  17.3.2.9 中断处理. 250  17.3.2.10 波特率设置. 251

17.4 寄存器. 251

17.4.1 地址分配. 251  17.4.2 SPI_CFG SPI控制寄存器. 251  17.4.3 SPI_IE SPI中继寄存器. 252  17.4.4 SPI_DIV SPI波特率寄存器. 253  17.4.5 SPI_TX_DATA SPI数据发送寄存器. 254  17.4.6 SPI_RX_DATA SPI数据接收寄存器. 254  17.4.7 SPI_SIZE SPI数据传输长度寄存器. 254

# 18 CMP. 256

18.1 概述. 256

18.2 寄存器. 258

18.2.1 地址分配. 258

18.2.2 CMP模块寄存器描述. 258

18.2.2.1 CMP_IE. 258

18.2.2.2 CMP_IF. 258

18.2.2.3 CMP_TCLK. 259

18.2.2.4 CMP_CFG. 260

18.2.2.5 CMP_BLCWIN. 262

# 19 CAN. 264

19.1 概述. 26419.1 主要特性 26419.2 功能描述 26419.2.1 功能框图. 26419.2.2 功能说明. 26519.2.2.1 工作模式. 26519.2.2.2 DMA传输. 26519.2.2.3 CPU传输. 26519.2.2.4 中断处理. 26619.2.2.4.1 接收中断. 26619.2.2.4.2 发送中断. 26619.2.2.4.3 错误报警中断. 26619.2.2.4.4 数据溢出中断. 26719.2.2.4.5 仲裁丢失中断. 26719.2.2.4.6 总线错误中断. 26719.2.2.5 通讯采样设置. 26719.2.2.6 ID滤波. 26919.2.2.7 发送帧格式. 27119.2.2.8 接收帧格式. 27219.2.2.9 发送. 27319.2.2.10 接收. 27319.2.2.11 错误管理. 27419.2.2.12 错误计数. 27519.2.2.13 错误报警限制. 27619.2.2.14 被动错误. 27619.2.2.15 离线状态与离线恢复. 27619.2.3 寄存器. 27619.2.3.1 地址分配. 27619.2.3.2 寄存器说明. 278

19.2.3.2.1 CAN_MOD 模式寄存器 .27819.2.3.2.2 CAN CMR 命令寄存器 .27819.2.3.2.3 CAN_SR 状态寄存器 .27919.2.3.2.4 CAN_IR 中断状态寄存器 .28019.2.3.2.5 CAN_EIR 中断控制寄存器 .28119.2.3.2.6 CAN_BTR0 波特率 0 控制寄存器 .28119.2.3.2.7 CAN_BTR1 波特率 1 控制寄存器 .28219.2.3.2.8 CAN_ALC 仲裁丢失捕捉寄存器 .28219.2.3.2.9 CAN_ECC 错误码捕捉寄存器 .28319.2.3.2.10 CAN_EVLR 错误&警告门限值寄存器 .28419.2.3.2.11 CAN_RXERR 接收错误计数器寄存器 .28519.2.3.2.12 CAN_TXERR 发送错误计数器寄存器 .28519.2.3.2.13 CAN_TXRX0~CAN_TXRXC 发送接收寄存器 .28619.2.3.2.14 CAN_ACR ID 寄存器 .28619.2.3.2.15 CAN_AMR ID 掩码寄存器 .28619.2.3.2.16 CAN_RMC FIFO 有效接收数据寄存器 .28719.2.3.2.17 CAN_RBSA 有效接收数据地址寄存器 .28719.2.3.2.18 CAN_RFIFO0~CAN_RFIFO31 RX FIFO 寄存器 .28819.2.3.2.19 CAN_TFIFO0~CAN_TFIFO12 TX FIFO 寄存器 .288

# 20 SIF 290

20.1 概述 .29020.2 主要特性 .29020.3 功能描述 .29020.3.1 功能框图 .29020.3.2 功能说明 .29020.3.3 模式选择 .29120.3.4 SIF 接口传输 .29120.3.5 中断处理 .29120.3.6 通讯速度设置 .29120.4 寄存器 .291

# LKS32MC08x User Manual

20.4.1 地址分配. 291

20.4.2 寄存器说明. 292

20.4.2.1 SIF_CFG 配置寄存器. 292

20.4.2.2 SIF_FREQ 波特率寄存器. 292

20.4.2.3 SIF_IRQ 状态控制寄存器. 293

20.4.2.4 SIF_WDATA 数据寄存器. 293

21 看门狗. 294

21.1 概述. 294

21.2 寄存器. 294

21.2.1 地址分配. 294

21.2.2 寄存器说明. 294

21.2.2.1 SYS_WDT_CLR 看门狗清零寄存器. 294

22 版本历史. 296

LKS32MC08x User Manual

# 表格目录

表2- 1系统地址空间分配. 2表3- 1中断号分布. 4表3- 2中断号分布. 5表3- 3SYST_CSR控制和状态寄存器. 5表3- 4SYST_RVR重载值寄存器. 6表3- 5SYST_CVR当前值寄存器. 7表5- 1系统时钟源. 15表5- 2PLL作为MCLK时钟时的分频配置 16表5- 3硬件复位源. 18表5- 4复位作用域. 19表5- 5系统控制寄存器. 20表5- 6模拟前端信息寄存器SYS_AFE_CMP. 21表5- 7模拟配置寄存器0SYS_AFE_REG0. 22表5- 8模拟配置寄存器1SYS_AFE_REG1. 23表5- 9模拟配置寄存器2SYS_AFE_REG2. 24表5- 10模拟配置寄存器3SYS_AFE_REG3. 25表5- 11模拟配置寄存器4SYS_AFE_REG4. 26表5- 12模拟配置寄存器5SYS_AFE_REG5. 27表5- 13模拟配置寄存器6SYS_AFE_REG6. 28表5- 14模拟配置寄存器7SYS_AFE_REG7. 29表5- 20DAC数字量寄存器SYS_AFE_DAC. 30表5- 21时钟控制寄存器SYS_CLK_CFG. 30表5- 22复位控制寄存器SYS_RST_CFG. 31表5- 23复位源记录寄存器SYS_RST_SRC. 32表5- 24复位源记录清除寄存器SYS_CLK_RST. 32表5- 25外设时钟分频寄存器0SYS_CLK_DIV0. 33表5- 26外设时钟分频寄存器2SYS_CLK_DIV2. 33表5- 27外设时钟门控寄存器SYS_CLK_FEN. 33

表5- 28 休眠寄存器 SYS_CLK_SLP ..... 34表5- 29 校正模式寄存器 SYS_TRIM ..... 34表5- 30 软复位寄存器 SYS_SFT_RST ..... 35表5- 31 写保护寄存器 SYS_WR_PROTECT ..... 35表5- 32 DAC 增益校正寄存器 SYS_AFE_DAC_AMC ..... 36表5- 33 DAC 直流偏置寄存器 SYS_AFE_DAC_DC ..... 36表6- 1 FLASH 访问空间分配表 ..... 40表6- 2 FLASH Sector 地址分配表 ..... 42表6- 3 IAP VTOR 寄存器描述 ..... 44表6- 4 FLASH 控制器模块寄存器列表 ..... 45表6- 5 配置寄存器 FLASH_CFG ..... 45表6- 6 地址寄存器 FLASH_ADDR ..... 46表6- 7 写数据寄存器 FLASH_WDATA ..... 47表6- 8 读数据寄存器 FLASH_RDATA ..... 47表6- 9 擦除控制寄存器 FLASH_ERASE ..... 48表6- 10 加密状态寄存器 FLASH_PROTECT ..... 48表6- 11 工作状态寄存器 FLASH_READY ..... 48表7- 1 DMA 请求 ..... 54表7- 2 DMA 寄存器列表 ..... 56表7- 3 DMA 控制寄存器 DMA_CTRL ..... 56表7- 4 DMA 中断标志寄存器 DMA_IF ..... 57表7- 5 DMA 通道配置寄存器 DMA_CCRx ..... 57表7- 6 DMA 通道请求信号 ..... 58表7- 7 DMA 传输次数寄存器 DMA_CTMSx ..... 59表7- 8 DMA 外设地址寄存器 DMA_CPARx ..... 60表7- 9 DMA 内存地址寄存器 DMA_CMARx ..... 60表8- 1 GPIOx 寄存器列表 ..... 64表8- 2 GPIO 中断/唤醒/配置锁定模块寄存器列表 ..... 64表8- 3 GPIOx 输入使能寄存器 GPIOx PIE ..... 65表8- 4 GPIOx 输出使能寄存器 GPIOx POE ..... 65

表8- 5 GPIOx输入数据寄存器 GPIOx_PDI. 66表8- 6 GPIOx输出数据寄存器 GPIOx_PDO. 66表8- 7 GPIOx上拉使能寄存器 GPIOx_PUE. 67表8- 8 GPIOx开漏使能寄存器 GPIOx_PODE. 68表8- 9 GPIOx配置锁定寄存器 GPIOx_LCKR. 68表8- 10 GPIOx功能选择寄存器 GPIOx_F3210. 69表8- 11 GPIO功能复用. 70表8- 12 GPIOx功能选择寄存器 GPIOx_F7654. 70表8- 13 GPIOx功能选择寄存器 GPIOx_FBA98. 70表8- 14 GPIOx功能选择寄存器 GPIOx_FFEDC. 71表8- 15外部中断配置寄存器EXTI_CR0. 72表8- 16外部中断配置寄存器EXTI_CR1. 73表8- 17外部中断标志寄存器EXTI_IF. 74表8- 18锁定保护寄存器LCKR_PRT. 75表8- 19外部唤醒源极性配置寄存器WAKE_POL. 76表8- 20外部唤醒源使能寄存器WAKE_EN. 76表8- 21 GPIO上拉资源分布表. 77表9- 1 CRC寄存器列表. 82表9- 2 CRC数据寄存器 CRC_DR. 83表9- 3 CRC控制寄存器 CRC_CR. 83表9- 4 CRC初始码寄存器 CRC_INIT. 84表9- 5 CRC生成码寄存器 CRC_POL. 85表10- 1 ADC分段触发方式触发源配置. 88表10- 2 四段触发分段采样通道数示例. 88表10- 3 ADC通道选择与寄存器配置对应关系. 89表10- 4 ADC输出数字量数制转换. 90表10- 5 ADC0寄存器列表. 93表10- 6采样数据寄存器ADC0_DAT0. 94表10- 7采样数据寄存器ADC0_DAT1. 95表10- 8采样数据寄存器ADC0_DAT2. 95

表10- 9采样数据寄存器ADC0_DAT3. .95表10- 10采样数据寄存器ADC0_DAT4. .96表10- 11采样数据寄存器ADC0_DAT5. .96表10- 12采样数据寄存器ADC0_DAT6. .97表10- 13采样数据寄存器ADC0_DAT7. .97表10- 14采样数据寄存器ADC0_DAT8. .97表10- 15采样数据寄存器ADC0_DAT9. .98表10- 16采样数据寄存器ADC0_DAT10. .98表10- 17采样数据寄存器ADC0_DAT11. .99表10- 18采样数据寄存器ADC0_DAT12. .99表10- 19采样数据寄存器ADC0_DAT13. .99表10- 20采样数据寄存器ADC0_DAT14. .100表10- 21采样数据寄存器ADC0_DAT15. .100表10- 22采样数据寄存器ADC0_DAT16. .101表10- 23采样数据寄存器ADC0_DAT17. .101表10- 24采样数据寄存器ADC0_DAT18. .101表10- 25采样数据寄存器ADC0_DAT19. .102表10- 26信号来源寄存器ADC0_CHN0. .102表10- 27信号来源寄存器ADC0_CHN1. .103表10- 28信号来源寄存器ADC0_CHN2. .103表10- 29信号来源寄存器ADC0_CHN3. .104表10- 30信号来源寄存器ADC0_CHN4. .104表10- 31信号来源寄存器ADC0_CHN5. .105表10- 32信号来源寄存器ADC0_CHN6. .105表10- 33信号来源寄存器ADC0_CHN7. .106表10- 34信号来源寄存器ADC0_CHN8. .106表10- 35信号来源寄存器ADC0_CHN9. .107表10- 36ADC采样信号通道选择. .107表10- 37分段通道数寄存器ADC0_CHNT0. .108表10- 38分段通道数寄存器ADC0_CHNT1. .108

表10- 39模式配置寄存器ADC0_CFG. .109表10- 40触发控制寄存器ADC0_TRIG. .109表10- 41增益选择寄存器ADC0_GAIN0. .111表10- 42增益选择寄存器ADC0_GAIN1. .111表10- 43中断使能寄存器ADC0_IE. .112表10- 44中断标志寄存器ADC0_IF. .113表10- 45软件触发寄存器ADC0 SWT. .113表10- 46直流偏置寄存器ADC0_DC_A0. .114表10- 47直流偏置寄存器ADC0_DC_A1. .114表10- 48直流偏置寄存器ADC0_DC_B0. .115表10- 49直流偏置寄存器ADC0_DC_B1. .115表10- 50增益校正寄存器ADC0_AMC_A0. .116表10- 51增益校正寄存器ADC0_AMC_A1. .116表10- 52增益校正寄存器ADC0_AMC_B0. .116表10- 53增益校正寄存器ADC0_AMC_B1. .117表10- 54通道0阈值寄存器ADC0_DAT0_TH. .117表10- 55ADC采样触发模式. .119表11- 1编码器正交编码工作模式. .129表11- 2编码器符号加脉冲工作模式. .130表11- 3编码器CCW/CW双脉冲工作模式. .131表11- 4通用定时器配置寄存器地址分配. .131表11- 5UTIMER配置寄存器UTIMER_CFG. .133表11- 6滤波控制寄存器UTIMER_FLT_TH01. .133表11- 7滤波控制寄存器UTIMER_FLT_TH23. .134表11- 8Timer0配置寄存器UTIMER_UNTO_CFG. .135表11- 9Timer0配置寄存器UTIMER_UNTO_CFG. .136表11- 10Timer2配置寄存器UTIMER_UNT2_CFG. .137表11- 11Timer3配置寄存器UTIMER_UNT3_CFG. .138表11- 12Timer0门限寄存器UTIMER_UNTO_TH. .139表11- 13Timer1门限寄存器UTIMER_UNT1_TH. .140

表11- 14 Timer 2 门限寄存器UTIMER_UNT2_TH .140表11- 15 Timer 3 门限寄存器UTIMER_UNT3_TH .141表11- 16 Timer 0 计数寄存器UTIMER_UNTO_CNT. .141表11- 17 Timer 1 计数寄存器UTIMER_UNT1_CNT. .142表11- 18 Timer 2 计数寄存器UTIMER_UNT2_CNT. .142表11- 19 Timer 3 计数寄存器UTIMER_UNT3_CNT. .142表11- 20 Timer 0 通道0 比较捕获寄存器UTIMER_UNTO_CMP0. .143表11- 21 Timer 0 通道1 比较捕获寄存器UTIMER_UNTO_CMP1. .143表11- 22 Timer 1 通道0 比较捕获寄存器UTIMER_UNT1_CMP0. .144表11- 23 Timer 1 通道1 比较捕获寄存器UTIMER_UNT1_CMP1. .144表11- 24 Timer 2 通道0 比较捕获寄存器UTIMER_UNT2_CMP0. .145表11- 25 Timer 2 通道1 比较捕获寄存器UTIMER_UNT2_CMP1. .145表11- 26 Timer 3 通道0 比较捕获寄存器UTIMER_UNT3_CMP0. .146表11- 27 Timer 3 通道1 比较捕获寄存器UTIMER_UNT3_CMP1. .146表11- 28 Timer 0 外部事件选择寄存器UTIMER_UNTO_EVT .147表11- 29 Timer 1 外部事件选择寄存器UTIMER_UNT1_EVT .147表11- 30 Timer 2 外部事件选择寄存器UTIMER_UNT2_EVT .148表11- 31 Timer 3 外部事件选择寄存器UTIMER_UNT3_EVT .149表11- 32 Encoder0 配置寄存器UTIMER_ECD0_CFG. .149表11- 33 Encoder0 计数门限寄存器UTIMER_ECD0_TH. .150表11- 34 Encoder0 计数值寄存器UTIMER_ECD0_CNT. .150表11- 35 中断使能寄存器UTIMER_IE. .151表11- 36 中断标志寄存器UTIMER_IF. .152表11- 37 DMA 请求使能寄存器RE. .153表12- 1HALL 模块寄存器地址分配. .157表12- 2HALL 模块配置寄存器HALL_CFG. .157表12- 3HALL 模块信息寄存器HALL_INFO. .158表12- 4HALL 宽度计数值寄存器HALL_WIDTH. .159表12- 5HALL 模块计数器门限值寄存器HALL_TH. .160表12- 6HALL 计数寄存器HALL_CNT. .160

表13- 1 MCPWM计数器阈值与事件对应表 .169表13- 2 MCPWM模块寄存器列表 .169表13- 3受MCPWM_PRT保护的寄存器 .170表13- 4存在影子寄存器的寄存器 .171表13- 5 MCPWM_TH00配置寄存器 .171表13- 6 MCPWM_TH01配置寄存器 .172表13- 7 MCPWM_TH10配置寄存器 .172表13- 8 MCPWM_TH11配置寄存器 .173表13- 9 MCPWM_TH20配置寄存器 .173表13- 10 MCPWM_TH21配置寄存器 .174表13- 11 MCPWM_TH30配置寄存器 .174表13- 12 MCPWM_TH31配置寄存器 .174表13- 13 MCPWM_TMR0配置寄存器 .175表13- 14 MCPWM_TMR1配置寄存器 .175表13- 15 MCPWM_TMR2配置寄存器 .176表13- 16 MCPWM_TMR3配置寄存器 .176表13- 17 MCPWM_TH配置寄存器 .177表13- 18 MCPWM_UPDATE配置寄存器 .177表13- 19 MCPWM_IE配置寄存器 .178表13- 20 MCPWM_IF配置寄存器 .179表13- 21 MCPWM_EIE配置寄存器 .180表13- 22 MCPWM_EIF配置寄存器 .181表13- 23 MCPWM_RE配置寄存器 .182表13- 24 MCPWM_PP配置寄存器 .182表13- 25 MCPWM_IO01配置寄存器 .183表13- 26 MCPWM_IO23配置寄存器 .184表13- 27 MCPWM_SDCFG配置寄存器 .185表13- 28 MCPWM_TCLK配置寄存器 .185表13- 29 MCPWM_FAIL配置寄存器 .186表13- 30 MCPWM_PRT配置寄存器 .187

表13- 31 MCPWM_CNT配置寄存器. .188表13- 32 MCPWM_DTH00配置寄存器 .188表13- 33 MCPWM_DTH01配置寄存器 .189表13- 34 MCPWM_DTH10配置寄存器 .189表13- 35 MCPWM_DTH11配置寄存器 .190表13- 36 MCPWM_DTH20配置寄存器 .190表13- 37 MCPWM_DTH21配置寄存器 .190表13- 38 MCPWM_DTH30配置寄存器 .191表13- 39 MCPWM_DTH31配置寄存器 .191表14- 1 UART波特率配置示例 .192表14- 2 UARTx地址分配列表 .194表14- 3 UARTx控制寄存器UARTx_CTRL .194表14- 4 UARTx波特率设置高字节寄存器UARTx_DIVH .195表14- 5 UARTx波特率设置低字节寄存器UARTx_DIVL .195表14- 6 UARTx收发缓冲寄存器UARTx_BUFF .196表14- 7 UARTx地址匹配寄存器UARTx_ADR .196表14- 8 UARTx状态寄存器UARTx_STT .197表14- 9 UARTx中断使能寄存器UARTx_IE .197表14- 10 UARTx中断使能寄存器UARTx_IF .198表14- 11 UARTx中断使能寄存器UARTx_INV .199表15- 1 DSP核心寄存器 .201表15- 2 DSP地址空间 .202表15- 3 DSP寄存器列表 .203表15- 4 DSP状态控制寄存器DSP_SC .204表15- 5 DSP sin/cos角度输入寄存器 .205表15- 6 DSP sin/cos正弦结果寄存器 .205表15- 7 DSP sin/cos余弦结果寄存器 .205表15- 8 DSP arctan/module坐标X输入寄存器 .206表15- 9 DSP arctan/module计算坐标Y输入寄存器 .206表15- 10 DSP arctan向量模结果sqrt  $(X^{2} + Y^{2})$  寄存器 .207

表15- 11 DSP arctan角度结果 arctan(Y/X) 角度寄存器. .207表15- 12DSP除法被除数寄存器 .208表15- 13DSP除法除数寄存器 .208表15- 14DSP除法商寄存器 .209表15- 15DSP除法余数寄存器 .209表15- 16DSP被开方数寄存器 .210表15- 17DSP平方根寄存器 .210表16- 1I2C寄存器地址分配表 .238表16- 2地址寄存器I2C0_ADDR .238表16- 3系统控制寄存器I2C0_CFG .239表16- 4状态控制寄存器I2C0_SCR .239表16- 5数据寄存器I2C0_DATA .240表16- 6主模式寄存器I2C0_MSCR .241表16- 7DMA传输控制寄存器I2C0_BCR .242表17- 1SPI模块控制寄存器列表 .251表17- 2系统控制寄存器SPI_CFG .251表17- 3SPI_IE中断寄存器 .252表17- 4SPI_DIV控制寄存器 .253表17- 5SPI_TX_DATA数据发送寄存器 .254表17- 6SPI_RX_DATA数据接收寄存器 .254表17- 7SPI_SIZE数据传输长度寄存器 .254表18- 1比较器模块寄存器列表 .258表18- 2比较器中断使能寄存器CMP_IE .258表18- 3比较器中断标志寄存器CMP_IF .258表18- 4比较器分频时钟控制寄存器CMP_TCLK .259表18- 5比较器控制寄存器CMP_CFG .260表18- 6比较器开窗控制寄存器CMP_BLCWIN .262表19- 1发送帧结构 .271表19- 2发送SFF头信息 .271表19- 3发送EFF头信息 .272

表19- 4接收帧结构 .272表19- 5接收SFF头信息 .273表19- 6接收EFF头信息 .273表19- 7CAN寄存器地址分配 .276表19- 8模式寄存器CAN_MOD .278表19- 9命令寄存器CAN_CMR .278表19- 10状态寄存器CAN_SR .279表19- 11中断状态寄存器CAN_IR .280表19- 12中断控制寄存器CAN_EIR .281表19- 13波特率0控制寄存器CAN_BTR0 .281表19- 14波特率1控制寄存器CAN_BTR1 .282表19- 15仲裁丢失捕捉寄存器CAN_ALC .282表19- 16错误码捕捉寄存器CAN_ECC .283表19- 17错误&警告门限值寄存器CAN_EWLR .284表19- 18接收错误计数器寄存器CAN_RXERR .285表19- 19发送错误计数器寄存器CAN_TXERR .285表19- 20发送接收寄存器CAN_TXRX .286表19- 21ID寄存器CAN_ACR .286表19- 22ID掩码寄存器CAN_AMR .287表19- 23FIFO有效接收数据寄存器CAN_RMC .287表19- 24有效接收数据地址寄存器CAN_RBSA .287表19- 25RXFIFO寄存器CAN_RFIFO0~CAN_RFIFO31 .288表19- 26TXFIFO寄存器CAN_TFIFO0~CAN_TFIFO12 .288表20- 1SIF模块控制寄存器列表 .291表20- 2地址寄存器SIF_CFG .292表20- 3系统控制寄存器SIF_FREQ .292表20- 4状态控制寄存器SIF_IRQ .293表20- 5数据寄存器SIF_WDATA .293表21- 1看门狗模块寄存器 .294表21- 2看门狗清零寄存器SYS_WDT_CLR .294

表 22- 1 文档版本历史 296

# 图片目录

图 4- 1 模拟电路功能框图 ..... 9图 4- 3 温度传感器曲线 ..... 12图 5- 1 时钟架构 ..... 16图 5- 2 硬件复位架构 ..... 19图 5- 3 SYS_CLK_CFG 不同配置时的系统主时钟分频波形 ..... 31图 6- 1 FLASH 存储体空间划分框图 ..... 38图 6- 2 FLASH 控制状态转换图 ..... 39图 6- 3 FLASH 间接读取操作流程图 ..... 40图 6- 4 FLASH 模块编程操作流程图 ..... 41图 6- 5 FLASH 模块编程操作流程图 ..... 42图 6- 6 FLASH 模块擦除操作流程图 ..... 43图 7- 1 multi- layer AHB lite 总线架构 ..... 52图 7- 2 DMA 地址递增控制 ..... 53图 7- 3 DMA 通道优先级 ..... 55图 8- 1 GPIO 功能框图 ..... 62图 10- 1 ADC 采集模块功能框图 ..... 87图 10- 2 ADC 中断产生 ..... 89图 10- 3 一倍增益设置下 ADC 模数转换数制量程 ..... 90图 10- 4 ADC 单段采样状态转移图 ..... 120图 10- 5 ADC 两段采样状态转移图 ..... 121图 10- 6 ADC 四段采样状态转移图 ..... 121图 11- 1 模块顶层功能框图 ..... 124图 11- 2 滤波示意图 ..... 126图 11- 3 通用计数器 ..... 127图 11- 4 比较模式 ..... 128图 11- 5 捕获模式 ..... 128图 11- 6 编码器只在 T1 时刻计数的正交编码信号计数情况 ..... 129图 11- 7 编码器在 T1 或 T2 时刻计数的正交编码信号计数情况 ..... 130

图11- 8编码器在T1上升下降沿都计数的符号加脉冲信号计数情况 .130图11- 9编码器在仅T1上升沿计数的符号加脉冲信号计数情况 .130图11- 10编码器仅在T1/T2上升沿计数的CCW/CW双脉冲信号计数情况 .131图11- 11编码器在T1/T2上升下降沿计数的CCW/CW双脉冲信号计数情况 .131图12- 17/5滤波模块框图 .156图12- 2数据流程框图 .157图13- 1MCPWM模块框图 .161图13- 2BaseCounter t0/t1时序 .162图13- 3MCPWM更新机制 .163图13- 4MCPWMFAIL逻辑示意图 .163图13- 5MCPWMFail信号滤波时钟生成逻辑 .164图13- 6IODriver模块数据流程图 .165图13- 7MCPWM时序  $\mathrm{TH}< \mathrm{n} > 0$  和  $\mathrm{TH}< \mathrm{n} > 1$  - 互补模式 .166图13- 8MCPWM时序  $\mathrm{TH}< \mathrm{n} > 0$  和  $\mathrm{TH}< \mathrm{n} > 1$  - 互补模式 .166图13- 9MCPWM时序边沿对齐模式 .167图13- 10MCPWM时序  $\mathrm{TH}< \mathrm{n} > 0$  和  $\mathrm{TH}< \mathrm{n} > 1$  边沿对齐推挽模式 .167图13- 11MCPWMIO控制示意图 .168图15- 1DSP模块功能框图 .201图15- 2CPU访问DSPMEM一致性问题 .226图15- 3增加Dummy写操作解决DSPMEM一致性问题 .226图15- 4CPU因命中cache无法读取DSPDATAMEM真实数据 .226图16- 1I2C模块顶层功能框图 .228图16- 2基本I2C传输时序图 .229图16- 3从模式下单字节传输示意图 .231图16- 4从模式下多字节发送示意图 .232图16- 5从模式下多字节接收示意图 .232图16- 6主模式下单字节传输示意图 .233图16- 7主模式下多字节发送示意图 .235图16- 8主模式下多字节接收示意图 .235

图17- 1SPI模块结构框图 .244图17- 2SPI接口全双工模式互连框图 .245图17- 3SPI接口半双工模式互连框图 .246图17- 4SPI模块Slave模式片选信号选择 .247图17- 5SPI模块Master模式片选信号选择 .247图17- 6SPI通讯信号极性相位(Polarity  $\coloneqq 0$  ,Phase  $\coloneqq 0$  .248图17- 7SPI通讯信号极性相位(Polarity  $\coloneqq 0$  ,Phase  $\coloneqq 1$  .248图17- 8SPI通讯信号极性相位(Polarity  $\coloneqq 1$  ,Phase  $\coloneqq 0$  .248图17- 9SPI通讯信号极性相位(Polarity  $\coloneqq 1$  ,Phase  $\coloneqq 1$  .249图17- 10SPI模块中断选信号产生图 .250图4- 2BEMFx_MID信号 .257图18- 1比较器滤波时钟产生 .260图18- 2比较器控制及中断产生逻辑 .261图18- 3CMP与MCPWM的联动 .261图18- 4比较器开窗功能图示 .262图19- 1CAN模块顶层功能框图 .264图19- 2CAN模块Bit周期介绍图 .268图19- 3CAN模块ID滤波逻辑关系 .271图19- 4CAN模块错误管理 .274图20- 1SIF模块顶层功能框图 .290图20- 2SIF基本传输时序图 .291

# 1 文档约定

# 1.1 寄存器读写权限

RW 读/写，软件可以读写这些位。  RO 只读，软件只能读取这些位。  WO 只写，软件只能写入该位。读取该位时将返回默认值。  RW1C(Read and Write 1 to Clear) 可读，写 1 清零。

# 1.2 缩略词汇表

字：32位数据/指令。

半字：16位数据/指令。

字节：8位数据。

双字：64位数据。

ADC：Analog- Digital Converter，模数转换器

DAC：Digital- Analog Converter，数模转换器

BGP：Bandgap，带隙基准

WDT：Watch dog，看门狗

LSI：Low Speed Internal Clock，即 32kHz RC 时钟

HSI：High Speed Internal Clock，即 4MHz RC 时钟

HSE：High Speed External Clock，即 4~8MHz 外部晶振时钟

PLL：Phase Lock Loop Clock，即 96MHz 锁相环时钟，通常用作系统高速时钟

POR：Power- On Reset，即上电复位，芯片系统上电时产生的复位信号

NVR：Non- Volatile Register，flash 中区别于 main 区域之外的一块存储区域

IAP（在应用中编程）：IAP是指可以在用户程序运行期间对微控制器的Flash进行重新编程。ICP（在线编程）：ICP是指可以在器件安装于用户应用电路板上时使用JTAG协议、SWD协议或自举程序对微控制器的Flash进行编程。

CW：Clockwise，顺时针

CCW：Counter clockwise，逆时针

Option bytes：选项字节，保存在 Flash 中的 CPU 配置字节

# 2 地址空间

数据字节以小端格式存放在存储器中。一个字里的最低地址字节被认为是该字的最低有效字节，而最高地址字节是最高有效字节。其他所有没有分配给片上存储器和外设的存储器空间都是保留的地址空间。

表2-1系统地址空间分配  

<table><tr><td>外设</td><td>时钟/软复位</td><td>开始地址</td><td>结束地址</td><td>大小</td><td>说明</td></tr><tr><td>FLASH</td><td>PLL/无</td><td>0x0000_0000</td><td>0x0000_FFFF</td><td>64kB</td><td>FLASH 存储空间</td></tr><tr><td>RAM</td><td>PLL/无</td><td>0x2000_0000</td><td>0x2000_1FFF</td><td>8kB</td><td>RAM</td></tr><tr><td>SYS</td><td>PLL/无</td><td>0x4000_0000</td><td>0x4000_03FF</td><td>1kB</td><td>SYSTEM control, Clock / Reset Management</td></tr><tr><td>FLSCR</td><td>PLL/无</td><td>0x4000_0400</td><td>0x4000_07FF</td><td>1kB</td><td>FLASH control registers</td></tr><tr><td>SPI</td><td>FCLK[8]/sft rst[0]</td><td>0x4001_0000</td><td>0x4001_03FF</td><td>1kB</td><td>SPI interface</td></tr><tr><td>I2C</td><td>FCLK[0]/sft rst[0]</td><td>0x4001_0400</td><td>0x4001_07FF</td><td>1kB</td><td>I2C interface</td></tr><tr><td>CMP</td><td>PLL/无</td><td>0x4001_0C00</td><td>0x4001_0FFF</td><td>1kB</td><td>Comparator</td></tr><tr><td>HALL</td><td>FCLK[1]/sft rst[1]</td><td>0x4001_1000</td><td>0x4001_13FF</td><td>1kB</td><td>HALL interface</td></tr><tr><td>ADC</td><td>ACLK</td><td>0x4001_1400</td><td>0x4001_17FF</td><td>1kB</td><td>ADC interface</td></tr><tr><td>TIMER</td><td>FCLK[2]/sft rst[2]</td><td>0x4001_1800</td><td>0x4001_1BFF</td><td>1kB</td><td>General Purpose Timer</td></tr><tr><td>MCPWM</td><td>FCLK[3]/sft rst[3]</td><td>0x4001_1C00</td><td>0x4001_1FFF</td><td>1kB</td><td>Motor Control Pulse Width Modulation</td></tr><tr><td>GPIO</td><td>PLL/无</td><td>0x4001_2000</td><td>0x4001_23FF</td><td>1kB</td><td>General Purpose Input / Output</td></tr><tr><td>CRC</td><td>PLL/无</td><td>0x4001_2400</td><td>0x4001_27FF</td><td>1kB</td><td>Cyclic Redundancy Check</td></tr><tr><td>UART0</td><td>FCLK[4]/sft rst[4]</td><td>0x4001_2800</td><td>0x4001_2BFF</td><td>1kB</td><td></td></tr><tr><td>UART1</td><td>FCLK[5]/sft rst[5]</td><td>0x4001_2C00</td><td>0x4001_2FFF</td><td>1kB</td><td></td></tr><tr><td>DMA</td><td>PLL/无</td><td>0x4001_3000</td><td>0x4001_33FF</td><td>1kB</td><td></td></tr><tr><td>CAN</td><td>FCLK[7]/无</td><td>0x4001_3400</td><td>0x4001_37FF</td><td>1kB</td><td></td></tr><tr><td>SIF</td><td>PLL/无</td><td>0x4001_3800</td><td>0x4001_3BFF</td><td>1kB</td><td></td></tr><tr><td>DSP</td><td>FCLK[6]/无</td><td>0x4001_4000</td><td>0x4001_5FFF</td><td>8kB</td><td></td></tr></table>

# 3 内核

# 3.1 ARM@CortexTM-M0核心

Cortex- M0是Cortex- M家族中的M0系列。最大特点是低功耗的设计。Cortex- M0为32位、3级流水线RISC处理器，其核心仍为冯.诺依曼结构，是指令和数据共享同一总线的架构。作为新一代的处理器，Cortex- M0的设计进行了许多的改革与创新，如系统存储器地址映像(System AddressMap)、改善效率并增强确定性的嵌套向量中断系统(NVIC)与不可屏蔽中断(NMI)、全新的调试单元等等，都带给了使用者全新的体验和更便利、更有效率的操作。

Cortex- M0其核心架构为ARMv6M，其运算能力可以达到0.9DMIPS/MHz，而与其他的16位与8位处理器相比，由于CortexM0的运算性能大幅提高，所以在同样任务的执行上Cortex- M0只需较低的运行速度，而大幅降低了整体的动态功耗。

有关内核的更多信息请参考ARM官方技术手册"Cortex- M0 Technical Reference Manual”（汉译版本为"Cortex- M0技术参考手册")。

本小节重点描述NVIC控制器、SysTick定时器、LKS32MC08x中断向量表定义及中断向量表重定义三个功能。

# 3.2 NVIC控制器

为了管理中断请求的优先级并处理其他异常，Cortex- M0处理器内置了嵌套中断控制器(NVIC)。NVIC的一些可编程控制器控制着中断管理功能，这些寄存器被映射到系统地址空间里，它们所处的区域被称为系统控制空间（SCS)。SCS的地址空间为：0xE000_E000- 0xE000_EFFF。

NVIC有以下特性：

灵活的中断管理；

Cortex- M0处理器中，每一个外部中断都可以被使能或者禁止，并且可以被设置为挂起状态或者清除状态。处理器的中断可以是电平信号的（在中断服务程序清除中断请求以前，外设的请求会一直保持)，也可以是脉冲信号的（最小一个始终周期)，这样中断控制器就可以处理任何中断源。

支持嵌套中断；

Cortex- M0处理器的任何中断都有一个固定或者可编程的中断优先级。当外部中断之类的异常发生时，NVIC将该异常的优先级与当前的优先级进行比较，如果新的优先级更高，当前的任务会被暂停，处理器进行核心寄存器入栈保持，然后开始处理新的异常程序，这个过程也被称为“抢占”。高优先级的中断完成后，异常返回就会执行，处理器自动进行出栈操作恢复刚才寄存器的值，并继续运行刚才的任务。这种机制并没有带来软件开销。

向量化的异常入口；

异常发生时，处理器需要定位异常对用的程序入口。传统的处理方式需要软件去完成。而M0处理器会从存储器的向量表中，自动定位异常的程序入口。从异常到异常的处理事件会被缩减。

中断屏蔽；

NVIC通过一组特殊寄存器提供了一种中断屏蔽机制，NVIC除了硬件错误（HardFault）和NMI之外，可以屏蔽所有的异常。有些操作，比如对时间敏感的控制任务或实时多媒体解码任务，不应该被打断，此时中断屏蔽的作用就表现了出来。具体参见ARM手册。

LKS32MC08x支持ARM公司推出的CMSIS(CortexMicrocontrollerSoftwareInterfaceStandard，即Cortex微控制器软件接口标准）函数。用户在工程中包含cm0_core.h和cm0_core.c代码，即可实现对NVIC模块的操作。

# 3.3 异常和中断

异常，会引起程序控制的变化。在异常发生时，处理器停止当前的任务，转而执行异常处理程序，异常处理完成后，会继续执行刚才的任务。异常分为很多种，中断是其中之一。Cortex- M0处理器最多支持32个外部中断（IRQ）和一个不可屏蔽中断（NMI)，中断事件的处理叫做中断服务程序(ISR)，中断一般由芯片上的硬件资源产生。

每一个异常都对应一个异常编号，异常编号还指明了异常向量的地址。异常编号和中断编号是相互独立的。系统异常使用负数定义，中断使用0- 31正数定义。复位是一种特殊的异常，数值为- 15。除了NMI，HardFault和复位，其他所有异常的优先级都是可编程的，NMI和HardFault的优先级是固定的，并且比其他异常的优先级高。

LKS32MC08x系列芯片共使用了其中的21个外部中断，后11个保留未使用。NMI未实现。最多支持4个中断优先级可供编程选择。

表3-1中断号分布  

<table><tr><td>异常/中断号</td><td>说明</td><td>异常/中断号</td><td>说明</td></tr><tr><td>-14</td><td>NMI</td><td rowspan="14" colspan="2"></td></tr><tr><td>-13</td><td>HardFault</td></tr><tr><td>-12</td><td rowspan="7">保留</td></tr><tr><td>-11</td></tr><tr><td>-10</td></tr><tr><td>-9</td></tr><tr><td>-8</td></tr><tr><td>-7</td></tr><tr><td>-6</td></tr><tr><td>-5</td><td>SVCall</td></tr><tr><td>-4</td><td rowspan="2">保留</td></tr><tr><td>-3</td></tr><tr><td>-2</td><td>PendSV</td></tr><tr><td>-1</td><td>SysTick</td></tr><tr><td>0</td><td>TIMERO</td><td>16</td><td>WAKEUP，系统唤醒中断</td></tr><tr><td>1</td><td>TIMER1</td><td>17</td><td>电源电压过低</td></tr><tr><td>2</td><td>TIMER2</td><td>18</td><td>DMA</td></tr><tr><td>3</td><td>TIMER3</td><td>19</td><td>CAN</td></tr></table>

<table><tr><td>4</td><td>ENCODERO</td><td>20</td><td>SIF</td></tr><tr><td>5</td><td>ENCODER1</td><td>21</td><td>Reserved</td></tr><tr><td>6</td><td>I2C</td><td>22</td><td>Reserved</td></tr><tr><td>7</td><td>GPIO</td><td>23</td><td>Reserved</td></tr><tr><td>8</td><td>UART0</td><td>24</td><td>Reserved</td></tr><tr><td>9</td><td>HALL</td><td>25</td><td>Reserved</td></tr><tr><td>10</td><td>SPI</td><td>26</td><td>Reserved</td></tr><tr><td>11</td><td>ADC</td><td>27</td><td>Reserved</td></tr><tr><td>12</td><td>DSP</td><td>28</td><td>Reserved</td></tr><tr><td>13</td><td>MCPWM</td><td>29</td><td>Reserved</td></tr><tr><td>14</td><td>UART1</td><td>30</td><td>Reserved</td></tr><tr><td>15</td><td>CMP</td><td>31</td><td>Reserved</td></tr></table>

异常发生时，处理器需要定位异常对应的程序入口。标准的 Cortex- M0处理器不支持中断向量表的重定义，即每个异常的入口地址是固定的。在线升级应用，将擦除FLASH部分内容，用户可能擦除/破坏中断向量表。因此，此种应用，一般推荐关闭中断。LKS32MC08x芯片增加了该功能，实现了中断向量表的重定义功能。即在升级过程中，可开启中断，编程更灵活。具体使用，参见本文档FLASH章节- - FLASH在线升级(IAP)部分的描述。

# 3.4 SysTick定时器

SysTick定时器是Cortex- M0处理器自带的系统滴答定时器。其存在的主要目的是为嵌入式操作系统提供  $100\mathrm{Hz}$  (即  $10\mathrm{ms}$  )的定时节拍。当然，也可以做普通定时等其他用途。

可编程设置频率的RTOS定时器(例如  $100\mathrm{Hz}$  )，调用一个SysTick服务程序。简单计数器。软件可使用它测量时间（如：完成任务所需时间、已使用时间)。

SysTick定时器使用起来非常简单。它一共有三个寄存器：SYST_CSR、SYST_RVR、SYST_CVR。寄存器的基地址为0xE000_E000。LKS32MC08x芯片，针对实际应用，三个寄存器的配置如下。

表3-2中断号分布  

<table><tr><td>名称</td><td>偏移</td><td>描述</td></tr><tr><td>SYST_CSR</td><td>0x10</td><td>SysTick 定时器控制和状态寄存器</td></tr><tr><td>SYST_RVR</td><td>0x14</td><td>SysTick 定时器重载值寄存器</td></tr><tr><td>SYST_CVR</td><td>0x18</td><td>SysTick 定时器当前值寄存器</td></tr></table>

# 3.4.1 SYST_CSR控制和状态寄存器

地址：0xE000_E010

复位值：0x00000000

<table><tr><td colspan="14">表 3-3 SYST_CSR 控制和状态寄存器</td><td></td><td></td></tr><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr></table>

<table><tr><td rowspan="2" colspan="35"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="33"></td><td>TICKINT</td><td>ENABLE</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>RW</td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[16]</td><td>FLAG</td><td>SYSTick 定时器计数器回零标志位，读清除。
0：没有回零
1：发生回零</td></tr><tr><td>[15:3]</td><td>--</td><td>保持为 0</td></tr><tr><td>[2]</td><td>CLKSRC</td><td>SYSTick 定时器时钟选择信号。默认为 0。
0：CPU 时钟/8
1：CPU 时钟</td></tr><tr><td>[1]</td><td>TICKINT</td><td>SYSTick 定时器中断使能信号。默认为 0。
0：关闭
1：使能</td></tr><tr><td>[0]</td><td>ENABLE</td><td>SYSTick 定时器使能信号。默认为 0。
0：关闭
1：使能</td></tr></table>

# 3.4.2 SYST_RVR重载值寄存器

地址：0xE000_E014

复位值：0x00000000

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="8"></td><td colspan="99">RELOAD</td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="34">RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr></table>

<table><tr><td>[31:24]</td><td>--</td><td>保持为 0</td></tr><tr><td>[23:0]</td><td>RELOAD</td><td>SysTick 定时器周期寄存器，定时器在 0—RELOAD 之间计数。默认为 0。</td></tr></table>

# 3.4.3 SYST_CVR当前值寄存器

地址：0xE000_E018

复位值：0x00000000

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td rowspan="3" colspan="8"></td><td colspan="8">CURRENT</td></tr><tr><td colspan="8">RW</td></tr><tr><td colspan="8">0</td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="8"></td><td colspan="8">RELOAD</td></tr><tr><td colspan="8"></td><td colspan="8">RW</td></tr><tr><td colspan="8"></td><td colspan="8">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:24]</td><td>--</td><td>保持为 0</td></tr><tr><td>[23:0]</td><td>CURRENT</td><td>读取该寄存器，返回 SysTick 定时器内部计数值，默认为 0。对该寄存器写入任何值，将复位内部计数值，同时清除 SYST_CSR.FLAG。</td></tr></table>

# 4 模拟电路

# 4.1 简述

模拟电路包含以下模块：

> 集成1路同步双采样的12bit SAR ADC，采样及转换速率3Msps。最多20通道  > 集成4路运算放大器，可设置为PGA模式  > 集成两路比较器，可设置迟滞模式  > 集成12bit数模转换器  > 内置 $\pm 2^{\circ}\mathrm{C}$ 温度传感器  > 内置1.2V0.8%精度电压基准源

各个模块之间的相互关系、以及各模块的控制寄存器（寄存器的说明见下文“模拟寄存器表”）如下图所示。

![](images/2946d7d2c2e33684c14b5d26067908ec5c3788eb8b09d1c2c10216addba096c9.jpg)  
图4-1模拟电路功能框图

# 4.2 POWER 电源管理系统

电源管理系统由电源检测模块（PVD）、上电/掉电复位模块（POR）组成。

POR 模块监测 AVDD 的电压，在 AVDD 电压低于 3.0V 时（例如上电之初，或者掉电时），为数字电路提供复位信号以避免数字电路工作产生异常。

PVD 模块对 5V 输入电源进行检测，如低于某一设定阈值，则产生报警（中断）信号以提醒 CPU，欠压只产生欠压标志，不会产生复位。中断提醒阈值可通过寄存器 PVDSEL[1:0] 设置为不同的电压。

PVD 模块可通过设置 PD_PDT=1 关闭。

当发生电压过低事件时，会触发产生电源电压过低中断，对应中断号 17，详见第 3 章。

PVDSEL[1:0]/ PD_PDT 的说明见模拟寄存器 SYS_AFE_REG6

电源电压过低标志见模拟前端信息寄存器 SYS_AFE_CMP

# 4.3 CLOCK 时钟系统

时钟系统包括内部 32kHzRC 时钟、内部 4MHzRC 时钟、外部 4~8MHz 晶体起振电路、PLL 电路组成。

32kHzRC 时钟 LSI 主要用于系统内的看门狗模块以及复位信号滤波等。4MHzRC 时钟可作为 CPU 主时钟使用，CPU 也可以使用 PLL 时钟，PLL 最高可提供 96MHz 的时钟。外部 4~8MHz 晶体起振电路作为备用时钟使用。

32kHz 和 4MHzRC 时钟均带有出厂校正，32kHzRC 时钟在- 40~105°C 范围内的精度为  $\pm 50\%$ ，4MHzRC 时钟在该温度范围的精度为  $\pm 2.0\%$ 。

4MHzRC 时钟通过设置 RCHPD='0' 打开（默认打开，写 1 关闭），RC 时钟需要 BGP 电压基准源模块提供基准电压和电流，因此开启 RC 时钟需要先开启 BGP 模块（BGPPD='0'）。芯片上电的默认状态下，4MHzRC 时钟和 BGP 模块都是开启的。32kHzRC 时钟始终开启，不能关闭。

PLL 对 4MHzRC 时钟进行倍频，给 CPU、ADC 等模块提供更高速的工作时钟。CPU 和 PWM 模块的最高时钟为 96MHz，ADC 模块最高时钟 48MHz，通过寄存器 ADCLKSEL[1:0] 可设置不同的 ADC 工作频率。

PLL 通过设置 PLLPDN='1' 打开（默认关闭，设 1 打开），开启 PLL 模块之前，同样也需要开启 BGP 模块。开启 PLL 之后，PLL 需要 6us 的稳定时间来输出稳定时钟。芯片上电的默认状态下，RCH 时钟和 BGP 模块都是开启的，但 PLL 默认是关闭的，需要软件来开启。

晶体起振电路内置了放大器，需在 OSC_IN/OSC_OUT 管脚之间接入一个晶体，且在 OSC_IN/OSC_OUT 引脚各接一个 15pF 电容到地，设置 XTALPDN=1 即可起振。

ADCLKSEL<1:0>的说明见模拟寄存器 SYS_AFE_REG7

BGPPD/RCHPD/XTALPDN/PLLPDN 的说明见模拟寄存器 SYS_AFE_REG5

# 4.4 BGP 基准电压源

基准源电路(BGP REF Bandgap reference)为 ADC、DAC、RC 时钟、PLL、温度传感器、运算放大器、比较器和 FLASH 提供基准电压和电流，使用上述任何一个模块之前，都需要开启 BGP 基准电压源。

芯片上电的默认状态下，BGP 模块是开启的。通过设置 BGPPD='0' 将基准源打开，从关闭到开启，BGP 需要约 2us 达到稳定。BGP 输出电压约 1.2V，精度为  $\pm 0.8\%$

BGPPD 的说明见模拟寄存器 SYS_AFE_REG5

# 4.5 ADC 模数转换器

请参加第 10 章 ADC

# 4.6 OPA 运算放大器

芯片集成 4 路输入输出轨到轨（rail- to- rail）运算放大器，内置反馈电阻，外部引脚上需串联一个电阻  $\mathbb{R}_0$  到信号源。反馈电阻  $\mathbb{R}_2:\mathbb{R}_1$  的阻值可通过寄存器 RES_OPAx[1:0]设置，以实现不同的放大倍数。

RES_OPAx<1:0>的说明见模拟寄存器 SYS_AFE_REG0

放大器的结构示意图如下所示：

![](images/d7e8b024a13bf0757606482f70d57c5f5f2d20653fd2d5c69e420d44a4030d7c.jpg)  
图 4-2 放大器框图

图中两个  $\mathbb{R}_0$  是片外需放置的电阻，阻值必须相等，最终的放大倍数为  $\mathrm{R}_2 / (\mathrm{R}_1 + \mathrm{R}_0)$ 。

对于 MOS 管电阻直接采样的应用，由于 MOS 下管关断、上管导通时信号会升高到数十 V 的电源电压，为减小此时往芯片引脚里流入的电流，建议接  $>20\mathrm{k}\Omega$  的外部电阻。

对于分流电阻采样的应用，建议接  $100\sim 2\mathrm{k}\Omega$  的外部电阻。  $\mathrm{C}_0$  为信号滤波电容，和  $\mathrm{R}_0$  形成一阶 RC 滤波电路。  $\mathrm{R}_0$  的具体阻值可根据  $\mathrm{R}_0^*\mathrm{C}_0$  的滤波常数而定。如果信号上噪声较小不需要滤波、或者信号需要很大的带宽（较快的响应速度），则  $\mathrm{C}_0$  可以不加。

放大器可通过设置 OPAOUT_EN<2:0>选择将 4 路放大器中的某一路输出信号通过 BUFFER 送至 P2.7 管脚口进行测量和应用（对应关系见 datasheet 芯片管脚说明）。因为有 BUFFER 存在，在运放正常工作模式下也可以选择送一路运放输出信号出来。

OPAOUT_EN<2:0>的说明见模拟寄存器 SYS_AFE_REG2

芯片上电的默认状态下，放大器模块是关闭的。放大器可通过设置 OPAxPDN=1 (x=0,1,2,3) 打开。开启放大器之前，需要先开启 BGP 模块。

OPAxPDN 的说明见模拟寄存器 SYS_AFE_REG5

运放输入正负端内置钳位二极管，电机相线通过一个匹配电阻后直接接入输入端，从而简化了 MOSFET 电流采样的外置电路。

# 4.7 CMP 比较器

内置 2 路输入轨到轨（rail- to- rail）比较器，比较器比较速度可编程、迟滞电压可编程、信号源可编程。比较器的比较延时可设置为  $0.15\mathrm{uS} / 0.6\mathrm{uS}$  。迟滞电压可设置为  $20\mathrm{mV} / 0\mathrm{mV}$  。支持多种比较器输入信号来源。

# 4.8 TMP 温度传感器

芯片内置温度传感器，在  $- 40\sim 85^{\circ}C$  范围内典型精度为  $2^{\circ}C$  。  $85\sim 105^{\circ}C$  范围内典型精度为  $3^{\circ}C$  。

测量时需选择内部基准，且需要设置 SYS_AFE_REG1. GAIN_REF=0，选择外部基准会引起结果的较大偏差。

芯片出厂前会经温度校正，校正值保存在 flash_info 区(详见 6.3.9)。出厂较正时所用增益为 ADC_GAIN=0，建议应用时也选择此增益，可以使较正值更准确。

芯片上电的默认状态下，温度传感器模块是关闭的。开启传感器之前，需要先开启 BGP 模块。

温度传感器通过设置 TMPPDN=1 打开，开启到稳定需要约 2us，因此需在 ADC 测量传感器之前 2us 打开。

温度传感器信号连至 ADC 的通道 18。

ADC 部分的设置参考模数转换器(ADC)章节

TMPPDN 的说明见模拟寄存器 SYS_AFE_REG5

温度传感器的典型曲线如下图所示：

![](images/7bb3f22f1dfdee93e5a02de3bed21e3442018080d4913bd25b6a0d522caec5c8.jpg)  
图 4-2 温度传感器曲线

图中X轴为温度传感器的温度信号所对应的ADC值，Y轴为传感器所处的温度。测温时，按照如上要求配置传感器相关寄存器，并得到ADC值后，将ADC值作为X代入公式：

$$
y = -0.6032x + 364.96
$$

求得的Y值即为此时的温度。

公式中有两个系数，  $\mathsf{a} = - 0.6032,\mathsf{b} = 364.96$  。对于不同的芯片，b系数的值是不一样的。芯片出厂前会经过温度标定，将每颗芯片所对应的系数b写入flash的info区，地址为  $0\mathrm{x}0000039\mathrm{C}$  。存储时，会将b系数小数点右移一位（乘10）存入info区，小数点后第二位不进行保存。

同时为方便客户操作，系数a也会存入flashinfo区，地址为  $0\mathrm{x}00000398$  。存储时，将a系数小数点右移四位（乘10000）存入info区。

实际使用中，应从flashinfo区对应地址读出a/b系数，同时将读取到的ADC测到的当下温度传感器值代入公式，即可计算得到当下温度值，单位为摄氏度。计算时，需注意系数a/b在保存时小数点的位移数，即a系数应除以10000，b系数除以10。

注意，上述计算公式，基于ADC右对齐实现。若换成左对齐，ADC采样值需右移4位后，才能代入上述公式。

# 4.9 DAC数模转换器

芯片内置一路12bitDAC，输出信号的最大量程可通过寄存器DAC_GAIN<1:0>设置为1.2V/3V/4.85V

12bitDAC可通过配置寄存器DACOUT_EN  $= 1$  ，将DAC输出送至P0.0管脚，可驱动  $>5\mathrm{k}\Omega$  的负载电阻和50pF的负载电容。

DAC最大输出码率为1MHz。

芯片上电的默认状态下，DAC模块是关闭的。DAC可通过设置DAC12BPDN  $= 1$  打开，开启DAC模块之前，需要先开启BGF模块。

DAC的输入数字信号寄存器为SYS_AFE_DAC，低12BIT有效。信号范围是  $0\mathrm{x}000\sim 0\mathrm{x}\mathrm{FFF}$  。  $0\mathrm{x}000$  对应零模拟量输出0V，0xFFF对应满量程模拟量输出为  $DAC_{fs}$  ，如上文所述，  $DAC_{fs}$  的值可由DAC_GAIN<1:0>寄存器进行设置。每一档信号(LSB)所对应的模拟信号幅度为  $\frac{DAC_{fs}}{4096}$  。若SYS_AFE_DAC的数字值为Din，则该数字信号所对应的DAC输出模拟信号为  $\frac{DAC_{fs}}{4096} *Din$  。

不同芯片，DAC存在制造偏差，为抵消偏差，DAC自带校准硬件模块。DAC输出遵循公式  $y = ax - b$  。x为SYS_AFE_DAC填入值（理想值对应数字量）。a来自SYS_AFE_DAC_AMC寄存器，b来自SYS_AFE_DAC_DC。硬件根据SYS_AFE_DAC、SYS_AFE_DAC_AMC和SYS_AFE_DAC_DC进行乘加从而求得校正后的数字量，送至DAC输入端，使得DAC最终输出的模拟值就是填入的理想数字量对应的值。系统上电后，默认加载3V的校准值，若换成其它量程，软件需读取flashinfo区域，重新加载到相应寄存器。

地址  $0\mathrm{x}00000330$  ，为3V量程的a参数，地址  $0\mathrm{x}00000340$  ，为3V量程的b参数。

地址 0x00000334，为 1.2V 量程的 a 参数，地址 0x00000344，为 1.2V 量程的 b 参数。

地址 0x00000338，为 4.85V 量程的 a 参数，地址 0x00000348，为 4.85V 量程的 b 参数。

DAC 输出的模拟信号，除了可以送至 IO 口供外部模块使用外，还可通过配置寄存器连至芯片内部的 2 路比较器负端，作为比较器的基准信号使用。详见比较器章节。

DACOUT_EN 的说明见模拟寄存器 SYS_AFE_REG3  DAC_GAIN<1:0>的说明见模拟寄存器 SYS_AFE_REG1  DAC12BPDN 的说明见模拟寄存器 SYS_AFE_REG5  SYS_AFE_DAC 的说明见寄存器 SYS_AFE_DAC

# 5 系统控制及时钟复位

# 5.1 时钟

# 5.1.1 时钟源

如下表所示，系统包括5个时钟源。其中内部低速RC振荡时钟LSI（Low Speed Internal Clock）/内部高速RC振荡时钟HSI（High Speed Internal Clock）不会停振。外部晶振时钟HSE（High Speed External Clock）在极端工况下可能失效，仅部分应用会使用HSE。

表5-1系统时钟源  

<table><tr><td>时钟源</td><td>频率</td><td>来源</td><td>误差</td><td>说明</td></tr><tr><td>LSI</td><td>32kHz</td><td>内部 RC 振荡器</td><td>常温 23~42kHz
全温度 16~48kHz</td><td>内部系统管理时钟，用于看门狗模块，以及复位信号的滤波和展宽</td></tr><tr><td>HSI</td><td>4MHz</td><td>内部 RC 振荡器</td><td>-40~125° 误差&amp;lt;±2.0%</td><td>可作为PLL源时钟</td></tr><tr><td>PLL</td><td>96MHz</td><td>PLL 可钟</td><td>0</td><td>PLL 输出时钟，以HSI/HSE 作为参考时钟，输出是HSI/HSE 时钟的24倍频，作为系统主时钟。</td></tr><tr><td>HSE</td><td>4~8MHz</td><td>外部晶体振荡器</td><td>0</td><td>外部晶体，在对时钟精度有严格要求(例如ppm级别的精度要求)的应用下，可使用4MHz HSE 作为PLL 参考时钟来产生96MHz 的系统主时钟，不支持使用其他频率HSE 作为PLL 参考时钟</td></tr><tr><td>SWD</td><td>1MHz*</td><td>调试器</td><td>-</td><td>SWD 的JTAG 时钟</td></tr></table>

\*SWD时钟速率典型值，实际大小与硬件环境有关。

另外，晶振起振电路可以支持  $4\sim 8\mathrm{MHz}$  的外部晶振频率，但如果需要使用HSE作为PLL参考时钟，则仍需使用4MHz晶体，以提供与HSI相同频率的PLL参考时钟。如果直接使用HSE作为系统主时钟，则无此限制。

如

图5- 1所示，系统可以使用外部晶振时钟HSE或内部高速RC时钟HSI作为PLL的参考时钟，使用SYS_AFE_REG6. PLLSR_SEL进行选择。同时，芯片内部可以检测HSE时钟是否停振，如果HSE失效会自动切换至HSI作为PLL参考时钟。PLL将4MHz的参考时钟CLK_HS倍频24倍至96MHz。

PLL经过  $\mathrm{n} / 8$  分频后，可以得到  $96\mathrm{MHz}\times \mathrm{n} / 8$  的高速时钟，SYS_CLK_CFG.CLK_SEL在此分频后的高速时钟与4MHz的CLK_HS之间进行二选一，作为系统主时钟MCLK。系统复位时，PLL默认关闭，HSI默认开启，系统选择HSI时钟，即4MHz作为系统主时钟进行工作，从而保证系统上电之

初功耗处于较低水平。

MCLK是系统主时钟。可以通过SYS_CLK_CFG寄存器CLK_DIV位域控制进行n/8分频，可以产生12,24,36,48,60,72,84,96MHz等频率值。SYS_CLK_CFG_CLK_SEL表示选择PLL或CLK_HS作为系统主时钟。当SYS_CLK_CFG_CLK_SEL为1时，SYS_CLK_CFG_CLK_DIV作为PLL的分频系数。当SYS_CLK_CFG_CLK_SEL为0时，SYS_CLK_CFG_CLK_DIV不起任何作用。

表5-2PLL作为MCLK时钟时的分频配置  

<table><tr><td>SYS_CLK_CFG</td><td>分频系数</td><td>频率/MHz</td><td>是否均匀</td></tr><tr><td>0x0101</td><td>1/8</td><td>12</td><td>是</td></tr><tr><td>0x0111</td><td>2/8</td><td>24</td><td>是</td></tr><tr><td>0x0115</td><td>3/8</td><td>36</td><td>否</td></tr><tr><td>0x0155</td><td>4/8</td><td>48</td><td>是</td></tr><tr><td>0x0157</td><td>5/8</td><td>60</td><td>否</td></tr><tr><td>0x0177</td><td>6/8</td><td>72</td><td>否</td></tr><tr><td>0x01FF</td><td>7/8</td><td>84</td><td>否</td></tr><tr><td>0x01FF</td><td>8/8</td><td>96</td><td>是</td></tr></table>

MCLK时钟经过SYS_CLK_FEN寄存器控制的开关之后供给外设。I2C时钟由SYS_CLK_DIV0寄存器控制可以进一步分频，UART时钟由SYS_CLK_DIV2寄存器控制可以进一步分频。

PLL输出的时钟经过SYS_AFE_REG7. ADCLKSEL控制的2/4/8分频后送至ADC（典型工作频率48MHz)，即ACLK。

内部32kHzRC产生一路LSI时钟LCLK，主要用于WDT工作时钟，以及部分系统控制，复位的滤波展宽等。

![](images/8e6e25681358c9efbdc0758d1cdfde5e25898e9a48d1be5c391186d8f6fa5f3d.jpg)  
图5-1时钟架构

为了保证系统可靠工作，时钟系统有防止时钟被误操作关闭的机制。如当PLL被用作系统工作主时钟时，PLL本身无法被关闭，作为PLL参考时钟的HSI或HSE无法被软件关闭；当CLK_HS作为系统工作主时钟时，作为CLK_HS的HSI或HSE无法被关闭；当HSE被使用时，如果系统检测到HSE停振会自动切换到使用HSI时钟来代替HSE时钟。32kHz LSI时钟上电即工作，且无法关闭。SWCLK由调试器提供，频率可在调试界面进行选择。

为便于调试和出厂校正，高速RC时钟HSI和低速时钟LSI可以通过配置GPIO的第二功能通过芯片管脚输出。

# 5.1.2 功耗管理及休眠唤醒

# 5.1.2.1 休眠

MCLK可以通过配置进行门控，从而令包括CPU和所有外设在内的大部分数字电路处于休眠状态。门控时，PMU状态机依次关闭PLL，HSI/HSE,BGP等模拟模块，以降低功耗。

需要注意的是，系统的休眠模式仅仅关闭PLL，HSI，HSE等高速时钟，LSI时钟仍然存在。工作于LSI时钟的看门狗如果被使能，看门狗复位作为全局复位可以令系统回到初始状态重新开始工作。

向SYS_CLK_SLP寄存器写入0xDEAD可以令芯片准备进入休眠状态，之后立刻执行_WFI0宏指令使得CPU停止取指。

在应用程序编写中请事先配置好唤醒条件。

\*建议参考官方休眠例程配置，休眠前需要先关闭所有数字模块的时钟，并关闭模拟ADC/OPA/CMP/DAC等模块。

# 5.1.2.2 唤醒

休眠后，外部IO事件、内部唤醒Timer均可以作为唤醒源

内部唤醒Timer为独立于UTimer模块的独立Timer，使用LSI时钟，不同于系统中的通用Timer工作于系统主时钟。唤醒Timer可以使用SYS_RST_CFG.WK_INTV配置0.25s,0.5s,1s,2s,4s,8s,16s,32s共8档唤醒时间间隔，具体请参考5.2.14章节。

仅有P0[1:0]、P1[1:0]四个IO可以作为外部唤醒IO使用，可以配置独立的使能和极性。具体寄存器配置请参考8.2.13.5 WAKE_POL和8.2.13.6 WAKE_EN章节。需要注意的是，由于外部IO唤醒属于电平触发，如果外部IO在芯片休眠之前处于唤醒电平，会导致芯片休眠后立刻唤醒。

在应用程序编写中请尽量避免上电即进入休眠状态，如果使用内部唤醒Timer作为唤醒源，且唤醒后立即再次睡眠，会导致普通下载器无法进行连接调试，此时需要使用芯片供应商提供的离线下载器进行应用程序擦除改写。

# 5.1.2.3 外设时钟门控

外设时钟由系统高速时钟MCLK分频而来；当外设不需要使用时可以通过配置SYS_CLK_FEN寄存器门控关闭相应的外设时钟。对于每一个外设的工作时钟，均有一个时钟门控，共有8路可关闭的外设时钟分别供给不同的外设模块，详见

图5- 1时钟架构。门控时钟上电后默认是关闭的，使用相应外设模块之前需要由软件来开启。

I2C 使用 FCLK[0]Hall 模块使用 FCLK [1]Timer 模块使用 FCLK [2]MCPWM 模块使用 FCLK [3]UART0/UART1 分别使用 FCLK [4]/ FCLK [5]DSP 使用 FCLK [6]CAN 使用 FCLK [7]SPI 使用 FCLK [8]

# 5.1.2.4 外设时钟分频

部分外设有独立的时钟分频模块使得该模块可以工作在合适的时钟频率上。

其中 I2C 使用 SYS_CLK_DIV[0] 作为分频系数，UART0/1 共享 SYS_CLK_DIV[2] 作为分频系数。UART 的波特率在 UART 模块内部还有一个额外的分频器，详见

图 5- 1 时钟架构。

# 5.1.3 复位源

芯片的复位来源包括硬件复位与软件复位。

# 5.1.3.1 硬件复位

如表 5- 3 硬件复位源所示，系统包括 4 个硬件复位源，产生的复位均为芯片全局复位，复位产生后芯片程序计数器回到 0 地址，所有寄存器恢复到默认值。4 个硬件复位均为低电平有效。

表5-3硬件复位源  

<table><tr><td>名称</td><td>来源</td><td>说明</td></tr><tr><td>LPORn</td><td>内部 1.5V 电源管理</td><td>监控 1.5V 数字电源，低于 1.25V 时产生复位</td></tr><tr><td>HPORn</td><td>内部 3.3V 电源管理</td><td>监控 3.3V 电源，低于 3.0V 时产生复位</td></tr><tr><td>RSTn</td><td>外部按键</td><td>外部 RC 组成按键复位电路</td></tr><tr><td>WDTn</td><td>硬件看门狗</td><td>如果不进行软件喂狗则定时产生复位，复位间隔可配置</td></tr></table>

# 5.1.3.1.1 硬件复位架构

如下图所示，LPORn/HPORn 来自内部模拟电路，RSTn 来自外部按键经过滤波展宽预处理的复位信号进行与运算得到一个复位信号。P0.2 引脚持续时间小于 32us 的复位脉冲会被滤除，要求可靠复位宽度大于 200us。4 个复位信号复位等级和作用域一致，均为全局复位。

![](images/13ca42a734d32d5eb7d355c1acb9f07a94d6f1e5b6ea8bffb293e6787305a8f4.jpg)  
图5-2硬件复位架构

# 5.1.3.1.2硬件复位记录

SYS_RST_SRC寄存器用于保存硬件复位事件，当某个硬件复位发生后，SYS_RST_SRC对应位置位。SYS_RST_SRC寄存器本身无法被复位信号复位，只能通过向SYS_CLR_RST寄存器写入0xC4A0清空记录，复位记录可以方便地了解是否发生以及发生过何种复位。

# 5.1.3.2 软件复位

CPU的软复位操作可以使程序计数器(PC:ProgramCounter)回到0地址，但对所有外设中的寄存器没有影响。

在集成开发环境(IDE:IntegratedDevelopmentEnvironment)中的调试模式下，点击Reset与CPU软复位操作作用相同，仅仅使得PC回到0地址，对外设中的寄存器没有影响。但如果在bootloader中进行了外设模块的软复位，则会使得外设寄存器被复位为默认值。具体bootloader实现请咨询芯片供应商。

部分外设模块有模块级软复位，可以使用SYS_SFT_RST寄存器进行复位，写入对应的位，可以将模块状态机恢复到初始状态，同时将模块的寄存器恢复到默认值，详见5.2.22。

# 5.1.4 复位作用域

表5-4复位作用域  

<table><tr><td>复位源</td><td>作用域</td></tr><tr><td>LPORn</td><td>内部 1.5V 电源管理，全局复位</td></tr><tr><td>HPOR</td><td>内部 3.3V 电源管理，全局复位，除极少数寄存器</td></tr><tr><td>RSTn</td><td>外部按键，全局复位，除极少数寄存器</td></tr><tr><td>WDTn</td><td>硬件看门狗，全局复位，除极少数寄存器</td></tr></table>

<table><tr><td>SYS_SFT_RST.SPI_SFT_RST</td><td>SPI 模块</td></tr><tr><td>SYS_SFT_RST.CAN_SFT_RST</td><td>CAN 模块</td></tr><tr><td>SYS_SFT_RST.DSP_SFT_RST</td><td>DSP 模块</td></tr><tr><td>SYS_SFT_RST.UART1_SFT_RST</td><td>UART1 模块</td></tr><tr><td>SYS_SFT_RST.UART0_SFT_RST</td><td>UART0 模块</td></tr><tr><td>SYS_SFT_RST.MCPWM_SFT_RST</td><td>MCPWM 模块</td></tr><tr><td>SYS_SFT_RST.UTIMER_SFT_RST</td><td>UTIMER 模块</td></tr><tr><td>SYS_SFT_RST.HALL_SFT_RST</td><td>HALL 模块</td></tr><tr><td>SYS_SFT_RST.I2C_SFT_RST</td><td>I2C 模块</td></tr><tr><td>NVIC_SystemReset();</td><td>CPU 软复位，仅复位 CPU 内核，将 PC 重置为 0，所有外设寄存器值仍然维持。</td></tr></table>

其中用于控制P0[2]作为GPIO使用还是作为外部复位脚使用的SYS_RST_CFG.RST_IO，用于控制看门狗使能的SYS_RST_CFG.WDT_EN，以及复位记录寄存器SYS_RST_SRC只受LPOR复位。

全局复位会复位全芯片寄存器，包括CPU内核寄存器以及所有外设寄存器，除上述极少数寄存器。

由于CPU软复位仅仅复位CPU内核，而不复位外设寄存器，因此建议重新烧录程序后使用掉电重新上电或外部复位的方式重置外设寄存器。

Flash存储内容，SRAM存储内容不受复位影响。

# 5.2 寄存器

# 5.2.1 地址分配

系统模块寄存器基地址为0x4000_0000，寄存器列表如下：

表5-5系统控制寄存器  

<table><tr><td>名称</td><td>偏移</td><td>说明</td></tr><tr><td></td><td>0x00~0x08</td><td>保留</td></tr><tr><td></td><td>0x10~0x14</td><td>保留</td></tr><tr><td>SYS_AFE_CMP</td><td>0x18</td><td>模拟前端信息寄存器</td></tr><tr><td></td><td>0x1C</td><td>保留</td></tr><tr><td>SYS_AFE_REG0</td><td>0x20</td><td>模拟配置寄存器 0</td></tr><tr><td>SYS_AFE_REG1</td><td>0x24</td><td>模拟配置寄存器 1</td></tr><tr><td>SYS_AFE_REG2</td><td>0x28</td><td>模拟配置寄存器 2</td></tr><tr><td>SYS_AFE_REG3</td><td>0x2C</td><td>模拟配置寄存器 3</td></tr><tr><td>SYS_AFE_REG4</td><td>0x30</td><td>模拟配置寄存器 4</td></tr><tr><td>SYS_AFE_REG5</td><td>0x34</td><td>模拟配置寄存器 5</td></tr><tr><td>SYS_AFE_REG6</td><td>0x38</td><td>模拟配置寄存器 6</td></tr><tr><td>SYS_AFE_REG7</td><td>0x3C</td><td>模拟配置寄存器 7</td></tr><tr><td></td><td>0x54~0x78</td><td>保留</td></tr><tr><td>SYS_AFE_DAC</td><td>0x7C</td><td>DAC 数字量寄存器</td></tr></table>

<table><tr><td>SYS_CLK_CFG</td><td>0x80</td><td>时钟控制寄存器</td></tr><tr><td>SYS_RST_CFG</td><td>0x84</td><td>复位控制寄存器</td></tr><tr><td>SYS_RST_SRC</td><td>0x88</td><td>复位源记录寄存器</td></tr><tr><td>SYS_CLR_RST</td><td>0x8C</td><td>复位源记录清除寄存器</td></tr><tr><td>SYS_CLK_DIV0</td><td>0x90</td><td>外设时钟分频寄存器 0</td></tr><tr><td></td><td>0x94</td><td>保留</td></tr><tr><td>SYS_CLK_DIV2</td><td>0x98</td><td>外设时钟分频寄存器 2</td></tr><tr><td>SYS_CLK_FEN</td><td>0x9C</td><td>外设时钟门控寄存器</td></tr><tr><td>SYS_CLK_SLP</td><td>0xA0</td><td>休眠寄存器</td></tr><tr><td></td><td>0xA4</td><td>保留</td></tr><tr><td>SYS_TRIM</td><td>0xA8</td><td>校正模式寄存器</td></tr><tr><td>SYS_SFT_RST</td><td>0xAC</td><td>软复位寄存器</td></tr><tr><td>SYS_WR_PROTECT</td><td>0xB0</td><td>写保护寄存器</td></tr><tr><td>SYS_DAC_AMC</td><td>0xB4</td><td>DAC 增益校正寄存器</td></tr><tr><td>SYS_DAC_DC</td><td>0xB8</td><td>DAC 直流偏置寄存器</td></tr></table>

# 5.2.2 SYS_AFE_CMP模拟前端信息寄存器

地址：0x4000_0018

复位值：0x0

表5-6模拟前端信息寄存器SYS_AFE_CMP  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>CMP1</td><td>CMP0</td><td>PWR_WEAK</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RO</td><td>RO</td><td>RO</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>名称</td><td>复位值</td><td>偏移</td><td>位置</td><td>权限</td><td>位名称</td><td>说明</td></tr><tr><td rowspan="5">SYS_AFE_CMP</td><td rowspan="5">0x0</td><td rowspan="5">0x18</td><td>[31:16]</td><td>NA</td><td colspan="2">未使用</td></tr><tr><td>[15]</td><td>R</td><td>CMP1_RESULT</td><td>CMP1 输出结果寄存器</td></tr><tr><td>[14]</td><td>R</td><td>CMP0_RESULT</td><td>CMP0 输出结果寄存器</td></tr><tr><td>[13]</td><td>R</td><td>PWR_WEAK</td><td>供电低于掉电监测阈值</td></tr><tr><td>[12:0]</td><td>NA</td><td colspan="2">未使用</td></tr></table>

SYS_AFE_CMP中的CMP0/CMP1为比较器的原始输出，没有经过滤波处理。CMP0/CMP1也可以通过配置GPIO的第二功能（AF1）输出，具体输出引脚请查看器件DATASHEET。

PWR_WEAK标志在当供电电压低于掉电监测电路设定的阈值时置位，同时将产生CPU掉电中断（中断号17）。在供电恢复，高于阈值后清零。此标志为只读位，无法软件清除。

掉电监测的使用请参考4.2POWER电源管理系统。

# 5.2.3 模拟寄存器概述

模拟寄存器  $0\mathrm{x}40000020\sim 0\mathrm{x}4000003\mathrm{C}$  是开放给用户的寄存器，其中保留寄存器(Res)必须全部配置为0（芯片上电后会被复位为0)。其他寄存器根据应用场合需要进行配置。下面是各个模拟寄存器的详细说明。

下面是各个模拟寄存器的详细说明。

# 5.2.4 SYS_AFE_REG0模拟配置寄存器0

地址：0x4000_0020

复位值：0x0

表5-7模拟配置寄存器0SYS_AFE_REG0  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>Resv.</td><td>Resv.</td><td>Resv.</td><td>Resv.</td><td>REF_OPA3</td><td>REF_OPA2</td><td>REF_OPA1</td><td>REF_OPA0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:14]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[13:12]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[11:10]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[9:8]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[7:6]</td><td>REF(OPA3)</td><td>运放3反馈电阻
00:200k:10.4k
01:190k:20.4k
10:180k:30.4k
11:170k:40.4k</td></tr><tr><td>[5:4]</td><td>RES(OPA2)</td><td>运放2反馈电阻
00:200k:10.4k
01:190k:20.4k
10:180k:30.4k
11:170k:40.4k</td></tr><tr><td>[3:2]</td><td>RES(OPA1)</td><td>运放1反馈电阻
00:200k:10.4k
01:190k:20.4k
10:180k:30.4k
11:170k:40.4k</td></tr><tr><td>[1:0]</td><td>RES(OPA0)</td><td>运放0反馈电阻
00:200k:10.4k</td></tr></table>

<table><tr><td></td><td></td><td>01:190k:20.4k
10:180k:30.4k
11:170k:40.4k</td></tr></table>

运放反馈电阻的比例精度为  $0.5\%$  ，具体精度数据可参考应用笔记  $\because \mathrm{AN8012}$  运放反馈电阻值精度》

# 5.2.5 SYS_AFE_REG1模拟配置寄存器1

地址：0x4000_0024

复位值：0x0

表5-8模拟配置寄存器1SYS_AFE_REG1  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr></table>

<table><tr><td>Reserved</td><td>DAC_GAIN</td><td>REFVDD5</td><td>REF2VDD</td><td>GAIN_REF</td><td>IT_CMP</td><td>CMP_FT</td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td colspan="2">未使用</td></tr><tr><td>[15]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[14]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[13]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[12]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[11:8]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[7:6]</td><td>DAC_GAIN</td><td>DAC 输出档位配置
00: DAC 输出档位，满量程为 3V
01: DAC 输出档位，满量程为 1.2V
10: DAC 输出档位，满量程为 4.85V（注意，此时供电电源需为 5V，否则 DAC 输出异常）
11: 错误配置</td></tr><tr><td>[5]</td><td>REFVDD5</td><td>电源作为 ADC REF 且电源为 5V 时，增加运放输出的信号范围
0: 运放最大输出范围为 3.3V
1: 增加运放最大输出范围到 4.8V，需在 REF2VDD 配置为&#x27;1&#x27;时才可设置为&#x27;1&#x27;</td></tr><tr><td>[4]</td><td>REF2VDD</td><td>使用外部输入电源作为 ADC REF
1: 使用外部输入电源作为 ADC REF，此时 GAIN_REF 配置无效；
0: 使用默认内部 REF 作为 ADC 基准</td></tr><tr><td>[3]</td><td>GAIN_REF</td><td>ADC 基准电压调节，采用默认配置
0: ×2
1: ×1</td></tr><tr><td>[2:1]</td><td>IT_CMP</td><td>IT_CMP&amp;lt;1&amp;gt;：比较器 1 的比较速度选择
0: 150ns
1: 600ns</td></tr></table>

<table><tr><td></td><td></td><td>IT_CMP&amp;lt;0&amp;gt;:比较器0的比较速度选择
0:150ns
1:600ns</td></tr><tr><td>[0]</td><td>CMP_FT</td><td>使能比较器快速比较
1:在IT_CMP&amp;lt;1:0&amp;gt;都为默认&#x27;00&#x27;的时候，比较器比较速度小于30ns
0:不使能，比较速度维持IT_CMP设置里的参数</td></tr></table>

# 5.2.6 SYS_AFE_REG2模拟配置寄存器2

地址：0x4000_0028

复位值：0x0

表5-9模拟配置寄存器2SYS_AFE_REG2  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>Reserved</td><td></td><td>Reserved</td><td></td><td>Reserved</td><td></td><td></td><td>Reserved</td><td></td><td></td><td>OPAOUT_EN</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td></td><td>RW</td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td></td><td>0</td><td></td><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:14]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[13]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[12]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[11:10]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[9:8]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[7]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[6]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[5:4]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[3]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[2:0]</td><td>OPAOUT_EN</td><td>使能OPAx输出信号送至IO口p2_7
000:不输出;
001:输出OPA0信号到IO口;
010:输出OPA1信号到IO口;
011:输出OPA2信号到IO口;
100:输出OPA3信号到IO口;
101~111:禁止</td></tr></table>

# 5.2.7 SYS_AFE_REG3模拟配置寄存器3

地址：0x4000_002C

复位值：0x0

表5-10模拟配置寄存器3SYS_AFE_REG3  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>Res.</td><td>CMP1_SELP</td><td>DACOUT_EN</td><td>CMP0_SELP</td><td>CMP_HYS</td><td>Res.</td><td>CMP1_SELN</td><td>CMP0_SELN</td><td>Res.</td><td>LDOOUT_EN</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[51:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[14:12]</td><td>CMP1_SELF</td><td>比较器1信号正端选择
000:连CMP1_IPO
001:连OPA3_IP
010:连OPA2_OUT
011:连OPA3_OUT
100:连CMP1_IP1
101:连CMP1_IP2
110:连CMP1_IP3
111:连AVSS
说明:上述除AVSS/OPA2_OUT/OPA3_OUT 外都为管脚名称,请参看 datasheet 里管脚定义章节</td></tr><tr><td>[11]</td><td>DACOUT_EN</td><td>DAC 输出到IO 使能
0:不使能
1:使能输出到IO P0[0]</td></tr><tr><td>[10:8]</td><td>CMP0_SELF</td><td>比较器0信号正端选择
000:连CMP0_IPO
001:连OPA0_IP
010:连OPA0_OUT
011:连OPA1_OUT
100:连CMP0_IP1
101:连CMP0_IP2
110:连CMP0_IP3
111:连CMP0_IP4
说明:上述除OPA0_OUT/OPA1_OUT 外都为管脚名称,请参看 datasheet 里管脚定义章节</td></tr><tr><td>[7]</td><td>CMP_HYS</td><td>比较器回差选择,采用默认配置
0:20mv
1:0mv</td></tr><tr><td>[6]</td><td>Reserved</td><td>保留位,需全部为&#x27;0&#x27;</td></tr><tr><td>[5:4]</td><td>CMP1_SELN</td><td>比较器1信号负端选择
00:连CMP1_IN
01:连REF
10:连DAC 输出
11:连BEMF1_MID</td></tr></table>

<table><tr><td></td><td></td><td>说明:上述CMP1_IN为管脚名称,请参看datasheet里管脚定义章节;REF为芯片内部1.2V BANDGAP基准源;DAC输出即为芯片内部DAC模块输出模拟信号;BEMF1_MID为CMP1_IP1, CMP1_IP2, CMP1_IP3信号经电阻星形连接后得到的平均值</td></tr><tr><td>[3:2]</td><td>CMP0_SELN</td><td>比较器0信号负端选择
00:连CMP0_IN
01:连REF
10:连DAC输出
11:连BEMF0_MID
说明:
上述CMP0_IN为管脚名称,请参看datasheet里管脚定义章节;REF为芯片内部1.2V BANDGAP基准源;DAC输出即为芯片内部DAC模块输出模拟信号;BEMF0_MID为CMP0_IP1, CMP0_IP2, CMP0_IP3信号经电阻星形连接后得到的平均值</td></tr><tr><td>[1]</td><td>Reserved</td><td>保留位,需全部为&#x27;0&#x27;</td></tr><tr><td>[0]</td><td>LDOOUT_EN</td><td>LDO输出到IO使能
0:不输出
1:使能输出到IO P2.7</td></tr></table>

# 5.2.8 SYS_AFE_REG4模拟配置寄存器4

地址：0x4000_0030

复位值：0x0

表5-11模拟配置寄存器4SYS_AFE_REG4  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>Res.</td><td></td><td>Res.</td><td></td><td></td><td></td><td></td><td></td><td></td><td>Res.</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td></td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[14]</td><td></td><td>未使用</td></tr><tr><td>[13]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[12:6]</td><td></td><td>未使用</td></tr><tr><td>[5]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[4:0]</td><td></td><td>未使用</td></tr></table>

# 5.2.9 SYS_AFE_REG5模拟配置寄存器5

地址：0x4000_0034

复位值：0x0

表5-12模拟配置寄存器5SYS_AFE_REG5  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>PLL PD</td><td>XTAL PD</td><td>TMPPDN</td><td>DAC12BPDN</td><td>Res.</td><td>RCHPD</td><td>Res.</td><td>BGPPD</td><td>CMP1PDN</td><td>CMP0PDN</td><td>OPA3PDN</td><td>OPA2PDN</td><td>OPA1PDN</td><td>OPA0PDN</td><td>Res.</td><td>ADCPDN</td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>PLLPDN</td><td>PLL关闭控制
0:关闭PLL（默认）
1:开启PLL</td></tr><tr><td>[14]</td><td>XTALPDN</td><td>晶体起振电路开启使能
0:关闭（默认）
1:开启</td></tr><tr><td>[13]</td><td>TMPPDN</td><td>温度传感器开启使能
0:关闭
1:开启</td></tr><tr><td>[12]</td><td>DAC12BPDN</td><td>12BIT DAC 开启使能
0:关闭
1:开启</td></tr><tr><td>[11]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[10]</td><td>RCHPD</td><td>RCH 时钟关闭使能
0:开启
1:关闭</td></tr><tr><td>[9]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[8]</td><td>BGPPD</td><td>BGP 开启使能
0:开启
1:关闭</td></tr><tr><td>[7]</td><td>CMP1PDN</td><td>CMP1 开启使能
0:关闭
1:开启</td></tr><tr><td>[6]</td><td>CMP0PDN</td><td>CMP0 开启使能
0:关闭
1:开启</td></tr><tr><td>[5]</td><td>OPA3PDN</td><td>OPA3 开启使能
0:关闭
1:开启</td></tr><tr><td>[4]</td><td>OPA2PDN</td><td>OPA2 开启使能</td></tr></table>

<table><tr><td></td><td></td><td>0:关闭
1:开启</td></tr><tr><td>[3]</td><td>OPA1PDN</td><td>OPA1 开启使能
0:关闭
1:开启</td></tr><tr><td>[2]</td><td>OPA0PDN</td><td>OPA0 开启使能
0:关闭
1:开启</td></tr><tr><td>[1]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[0]</td><td>ADCPDN</td><td>ADC 开启使能
0:关闭
1:开启</td></tr></table>

如果SYS_CLK_CFG选择PLL时钟，则PLLPDN是被硬件控制的，软件配置PLLPDN关闭PLL无效。关闭PLL需要PLLPDN  $= 0$  ，且SYS_CLK_CFG不选择PLL作为芯片主时钟，这两个条件都须满足。

同理，如果SYS_CLK_CFG选择了HRC时钟，则RCHPD是被硬件控制的，软件配置RCHPD关闭RCH无效。关闭PLL需要  $\mathrm{RCHPD} = 1$  ，且芯片进入休眠。

如果芯片主时钟为PLL时钟，且HRC为PLL参考时钟，则RCH也是被硬件控制的。

由于RCH和PLL依赖BGP（bandgap），所以BGPPD也是硬件控制的，在芯片使用了RCH或PLL时，软件配置BGPPD关闭BGP无效。关闭BGP需要先顺序关闭PLL和RCH，且芯片进入休眠。

# 5.2.10 SYS_AFE_REG6模拟配置寄存器6

地址：0x4000_0038

复位值：0x0

表5-13模拟配置寄存器6SYS_AFE_REG6  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>PLLSR_SEL</td><td colspan="3">Reserved</td><td colspan="2">PVDSEL</td><td colspan="3">Reserved</td><td colspan="2">Reserved</td><td colspan="2">VSR PDT</td><td colspan="2">PD PDT</td><td></td></tr><tr><td>RW</td><td colspan="3">RW</td><td colspan="2">RW</td><td colspan="3">RW</td><td colspan="2">RW</td><td colspan="2">RW</td><td colspan="2">RW</td><td></td></tr><tr><td>0</td><td colspan="3">0</td><td colspan="2">0</td><td colspan="3">0</td><td colspan="2">0</td><td colspan="2">0</td><td colspan="2">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>PLLSR_SEL</td><td>PLL 时钟源选择
0: 使用 RCH 作为输入时钟源;
1: 使用 XTAL OSC 作为输入时钟源</td></tr><tr><td>[14]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[13]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr></table>

<table><tr><td>[12]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[11]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[10]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[9:8]</td><td>PVDSEL</td><td>电源掉电监测阈值选择
当 VSR_PDT=0 时，
00: 4.5V
01: 4.2V
10: 3.9V
11: 3.6V
当 VSR_PDT=1 时，
4 个档位与 DAC 设定值有关，分别为
00: 4.5/1.35*DAC V
01: 4.2/1.35*DAC V
10: 3.9/1.35*DAC V
11: 3.6/1.35*DAC V</td></tr><tr><td>[7]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[6:5]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[4:3]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[2]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[1]</td><td>VSR_PDT</td><td>掉电检测基准源选择，其中低功耗基准源为 1.35V 左右，DAC 输出则可以通过软件配置；低电压检测的阈值有 4 档可选，通过 PVDSEL 选择
0: 选择低功耗基准源；
1: 选择 DAC 输出作为掉电检测基准源</td></tr><tr><td>[0]</td><td>PD_PDT</td><td>关闭掉电检测电路
0: 开启
1: 关闭</td></tr></table>

# 5.2.11 SYS_AFE_REG7模拟配置寄存器7

地址：0x4000_003C

复位值：0x0

表5-14模拟配置寄存器7SYS_AFE_REG7  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="9">Reserved</td><td colspan="3">ADCLKSEL</td><td colspan="3">Reserved</td><td></td></tr><tr><td colspan="9">RW</td><td colspan="3">RW</td><td colspan="3">RW</td><td></td></tr><tr><td colspan="9">0</td><td colspan="3">0</td><td colspan="3">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[14]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[13:8]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr></table>

<table><tr><td>[7:6]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr><tr><td>[5:4]</td><td>ADCLKSEL</td><td>ADC 时钟频率选择
00: 48MHz
01: 禁止
10: 12MHz
11: 24MHz</td></tr><tr><td>[3:0]</td><td>Reserved</td><td>保留位，需全部为&#x27;0&#x27;</td></tr></table>

# 5.2.12 SYS_AFE_DAC DAC 数字量寄存器

地址：0x4000_007C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:12]</td><td></td><td>未使用</td></tr><tr><td>[11:0]</td><td>DAC_IN</td><td>DAC 待转换的数字量输入</td></tr></table>

# 5.2.13 SYS_CLK_CFG 时钟控制寄存器

地址：0x4000_0080

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3">CLK_SEL</td><td></td><td>CLK_DIV</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td></td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:9]</td><td></td><td>未使用</td></tr><tr><td>[8]</td><td>CLK_SEL</td><td>CLK_HS/PLL 选择，0: CLK_HS, 1:PLL。默认选择 CLK_HS，CLK_HS 根据是否使用外部晶体时钟，可以是 HSI 或 HSE。
PLL 在上电后默认关闭，需要软件来开启</td></tr><tr><td>[7:0]</td><td>CLK_DIV</td><td>PLL 输出分频控制，选择 8 个时钟周期中，哪些周期输出时钟，例如</td></tr></table>

<table><tr><td></td><td></td><td>8&#x27;b00000001，表示1/8分频，8&#x27;b00010001表示1/4分频，8&#x27;b00100101表示1/3分频，但不均匀。</td></tr></table>

![](images/946f8d44c604c8c648e206a7c34141ad96420cd2ac2cbd2030e887fb8a278de5.jpg)  
图5-3 SYS_CLK_CFG不同配置时的系统主时钟分频波形

当使用4MHzHSI时钟作为系统主时钟时，SYS_CLK_CFG[7:0]的分频系数无效，最终输出的系统时钟频率即为4MHz。

# 5.2.14 SYS_RST_CFG复位控制寄存器

地址：0x4000_0084

复位值：0x0

表5-17复位控制寄存器SYS_RST_CFG  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:6]</td><td></td><td>未使用</td></tr><tr><td>[5]</td><td>RST_IO</td><td>RSTn/P0[2]复用选择，0: RSTn, 1:P0[2]
当用作外部复位引脚时，片内上拉默认开启，且不可控。
当用作 GPIO P0[2]时，片内上拉默认关闭，且不可控。</td></tr><tr><td>[4:2]</td><td>WK_INTV</td><td>休眠唤醒间隔设置
000: 0.25S      100: 4S
001: 0.5S      101: 8S
010: 1S      110: 16S
011: 2S      111: 32S</td></tr><tr><td>[1]</td><td></td><td>未使用</td></tr></table>

<table><tr><td>[0]</td><td>WDT_EN</td><td>看门狗使能，高有效。</td></tr></table>

# 5.2.15 SYS_RST_SRC 复位源记录寄存器

地址：0x4000_0088

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15"></td><td></td></tr><tr><td rowspan="4" colspan="15"></td><td></td></tr><tr><td></td></tr><tr><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:4]</td><td></td><td>未使用</td></tr><tr><td>[3]</td><td>WDT_RST_RCD</td><td>看门狗复位发生标志，高有效</td></tr><tr><td>[2]</td><td>KEY_RST_RCD</td><td>按键复位发生标志，高有效</td></tr><tr><td>[1]</td><td>HPOR_RST_RCD</td><td>HPOR 复位发生标志，高有效</td></tr><tr><td>[0]</td><td>LPOR_RST_RCD</td><td>LPOR 复位发生标志，高有效</td></tr></table>

# 5.2.16 SYS_CLR_RST 复位源记录清除寄存器

地址：0x4000_008C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">PSW</td><td></td></tr><tr><td colspan="15">WO</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>PSW</td><td>写入 0xC4A0，清除复位标志记录
请注意由于复位记录工作于低速时钟域，清除执行完成需要一定时间，不应清除后立即读记录状态</td></tr></table>

# 5.2.17 SYS_CLK_DIV0 外设时钟分频寄存器 0

地址：0x4000_0090

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16">DIV0</td></tr><tr><td colspan="16">RW</td></tr><tr><td colspan="16">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[51:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DIV0</td><td>I2C 工作时钟=MCLK/(CLK_DIV0+1)。其中 MCLK 由 SYS_CLK_CFG 分频系数决定</td></tr></table>

# 5.2.18 SYS_CLK_DIV2外设时钟分频寄存器2

地址：0x4000_0098

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DIV2</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DIV2</td><td>UART 工作时钟=MCLK/(CLK_DIV2+1)
UART0/UART1 共享此分频配置，波特率根据 UART 波特率寄存器进一步分频，其中 MCLK 由 SYS_CLK_CFG 分频系数决定</td></tr></table>

# 5.2.19 SYS_CLK_FEN外设时钟门控寄存器

地址：0x4000_009C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="16"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td>SPCLK_EN</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td>CAN_CLK_EN</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td>DSP_CLK_EN</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td>UART1_CLK_EN</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td>UART2_CLK_EN</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td>MCPWM_CLK_EN</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td>UTIMER_CLK_EN</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td>HALL_CLK_EN</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td>I2C_CLK_EN</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td></td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:9]</td><td></td><td>未使用</td></tr><tr><td>[8]</td><td>SPI_CKL_EN</td><td>SPI 时钟门控，1:使能时钟；0:禁用时钟</td></tr><tr><td>[7]</td><td>CAN_CLK_EN</td><td>CAN 时钟门控，1:使能时钟；0:禁用时钟</td></tr><tr><td>[6]</td><td>DSP_CLK_EN</td><td>DSP 时钟门控，1:使能时钟；0:禁用时钟</td></tr><tr><td>[5]</td><td>UART1_CLK_EN</td><td>UART1 时钟门控，1:使能时钟；0:禁用时钟</td></tr><tr><td>[4]</td><td>UART0_CLK_EN</td><td>UART0 时钟门控，1:使能时钟；0:禁用时钟</td></tr><tr><td>[3]</td><td>MCPWM_CLK_EN</td><td>MCPWM 时钟门控，1:使能时钟；0:禁用时钟</td></tr><tr><td>[2]</td><td>UTIMER_CLK_EN</td><td>UTIMER 时钟门控，1:使能时钟；0:禁用时钟</td></tr><tr><td>[1]</td><td>HALL_CLK_EN</td><td>HALL 时钟门控，1:使能时钟；0:禁用时钟</td></tr><tr><td>[0]</td><td>I2C_CLK_EN</td><td>I2C 时钟门控，1:使能时钟；0:禁用时钟</td></tr></table>

# 5.2.20 SYS_CLK_SLP 休眠寄存器

地址：0x4000_00A0

复位值：0x0

表5-23休眠寄存器SYS_CLK_SLP  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">PSW</td><td></td></tr><tr><td colspan="15">WO</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>PSW</td><td>写入密码 0xDEAD，系统关闭高速时钟，进入休眠状态</td></tr></table>

# 5.2.21 SYS_TRIM 校正模式寄存器

地址：0x4000_00A8

复位值：0x0

表5-24校正模式寄存器SYS_TRIM  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15"></td><td></td></tr><tr><td colspan="15"></td><td></td></tr><tr><td rowspan="3" colspan="15"></td><td></td></tr><tr><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:1]</td><td></td><td>未使用</td></tr><tr><td>[0]</td><td>TRIM</td><td>芯片复位后，进入TRIM模式
TRIM结束后，通过软复位退出TRIM模式</td></tr></table>

# 5.2.22 SYS_SFT_RST 软复位寄存器

地址：0x4000_00AC

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>I2C_SFT_RST</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:9]</td><td></td><td>未使用</td></tr><tr><td>[8]</td><td>SPI_SFT_RST</td><td>SPI 软复位，写 1 复位，再写 0 释放</td></tr><tr><td>[7]</td><td>CAN_SFT_RST</td><td>CAN 软复位，写 1 复位，再写 0 释放</td></tr><tr><td>[6]</td><td>DSP_SFT_RST</td><td>DSP 软复位，写 1 复位，再写 0 释放</td></tr><tr><td>[5]</td><td>UART1_SFT_RST</td><td>UART1 软复位，写 1 复位，再写 0 释放</td></tr><tr><td>[4]</td><td>UART0_SFT_RST</td><td>UART0 软复位，写 1 复位，再写 0 释放</td></tr><tr><td>[3]</td><td>MCPWM_SFT_RST</td><td>MCPWM 软复位，写 1 复位，再写 0 释放</td></tr><tr><td>[2]</td><td>UTIMER_SFT_RST</td><td>UTIMER 软复位，写 1 复位，再写 0 释放</td></tr><tr><td>[1]</td><td>HALL_SFT_RST</td><td>HALL 软复位，写 1 复位，再写 0 释放</td></tr><tr><td>[0]</td><td>I2C_SFT_RST</td><td>I2C 软复位，写 1 复位，再写 0 释放</td></tr></table>

注意，模块软复位在 SYS_SFT_RST 对应位写入 1 后会保持在复位状态，需要再次写入 0 才能解除复位状态。

# 5.2.23 SYS_WR_PROTECT 写保护寄存器

地址：0x4000_00B0

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr></table>

<table><tr><td>PSW</td></tr><tr><td>WO</td></tr><tr><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>PSW</td><td>除 SYS_AFE_REG3、SYS_AFE_DAC、SYS_AFE_DAC_AMC、SYS_AFE_DAC_DC 外，其他系统寄存器受写保护；写入前需先写入密码解除写保护写入 0x7A83，使能系统寄存器写操作写入 0xCAFE，使能看门狗 WDT_CLR 寄存器写操作写入其它值，禁止寄存器写操作</td></tr></table>

# 5.2.24 SYS_AFE_DAC_AMC DAC 增益校正寄存器

地址：0x4000_00B4

复位值：0x0

表5-27DAC增益校正寄存器SYS_AFE_DAC_AMC  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td></td></tr><tr><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:10]</td><td></td><td>未使用</td></tr><tr><td>[9:0]</td><td>DAC_AMC</td><td>DAC 增益校正值，10bit 无符号定点数，B[9]为整数部分，B[8:0]为小数部分</td></tr></table>

# 5.2.25 SYS_AFE_DAC_DC DAC 直流偏置寄存器

地址：0x4000_00B8

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3" colspan="8">DAC_DC</td><td></td><td></td></tr><tr><td colspan="8">RW</td><td></td></tr><tr><td colspan="8">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr></table>

<table><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>DAC_DC</td><td>DAC 直流偏置，8bit 有符号数，B[7]为符号位</td></tr></table>

DAC 增益校正，记模拟输出的 12bitDAC 数值为 DAC_raw，经过校正后的 12bit DAC 数值为 DAC_cali

DAC_cali = DAC_raw * DAC_AMC - DAC_DC;

其中 DAC_AMC 为 DAC 增益校正系数，为 10bit 定点无符号数，B[9]为整数，B[8:0]为小数，大小为 1 左右，例如 DAC_AMC = 10'b10_0001_0000 = 1+1/32，或

DAC_AMC = 10'b01_1110_1100 = 1- 5/128

DAC_DC 位 DAC 直流偏置，为 8bit 有符号整数。

增益校正计算结果进行截断保留，最终 DAC_cali 仍为 12bit 整数。

且增益校正加直流偏置校正后的数值会进行饱和处理，最大为 0xff，最小为 0x000。

需要注意的是，DAC 有三个输出档位，系统上电后，加载默认档位的 DAC 校准值，若切换到其它档位，请使用原厂提供的库函数。

# 6 FLASH

# 6.1 概述

FLASH 存储体包含两个部分：NVR 和 MAIN。NVR 大小为 1KB，MAIN 为 32KB 或 64KB（不同型号）。

主闪存存储区（MAIN），包括应用程序和用户数据区

信息存储区（info区/NVR），预留给用户使用，大小为1KB，供客户存储私有信息

![](images/40f22a094de2a45671c851e7355ca11c9e3f3e18c1f924a84e0bb675d6320156.jpg)  
图6-1 FLASH存储体空间划分框图

- 可反复擦除写入不低于2万次- 室温数据保持长达100年- 单字节编程时间最长7.5us，Sector擦除时间最长5ms。- Sector大小512字节，可按Sector擦除写入，支持运行时编程，擦写一个Sector的同时读取访问另一个Sector- Flash数据防窃取（最后一个word须写入非0xFFFFFFFF的任意值）

# 6.2 功能特点

FLASH控制器模块，主要实现对FLASH存储体的相关操作。包括：

- FLASH读取数据的操作，包括对NVR部分的读取和对MAIN部分的读取。

- FLASH写入数据的操作，包括对NVR部分的写入和对MAIN部分的写入。

- FLASH擦除操作，包括CHIP擦除和SECTOR擦除。NVR部分仅支持SECTOR擦除，MAIN部分支持CHIP擦除和SECTOR擦除。

- FLASH深度休眠的操作，以降低芯片的休眠功耗。

- FLASH 存储体内容的加密操作。- FLASH 的读取加速操作，以提升芯片整体运行效率。- FLASH 控制寄存器的访问。

# 6.2.1 功能描述

控制模块，实现了对 FLASH 存储体的复位/读出/写入/擦除/休眠等操作。如下为控制状态转换图：

![](images/5523f1a518a17f569ad78dc0960d843d7ef6032a9c627fa34f4001e7e5bb901e.jpg)  
图 6-2 FLASH 控制状态转换图

# 6.2.1.1 复位操作

系统完成复位后，FLASH 需要一段时间恢复。其目的是保证 FLASH 存储体内部的电路稳定。待内部稳定后，才可对 FLASH 执行操作。此恢复操作由硬件自动实现，无需软件干预。

# 6.2.1.2 休眠操作

FLASH 的休眠操作分成两个部分：Standby 和 Deep Sleep。当系统不执行对 FLASH 的操作时，FLASH 可自动进入 StandBy 状态（若开启预取，此功能失效）。当系统执行 Deep Sleep 操作时，将触发 FLASH 也进入 Deep Sleep，实现降低功耗的目的。FLASH 进入 Deep Sleep 的操作，硬件自动完成，无需软件介入。

当外界唤醒系统，同时将唤醒 FLASH。经过一段时间恢复后，FLASH 可执行正常操作。此唤醒恢复操作，硬件自动完成，无需软件介入。

# 6.2.1.3 FLASH读取操作

读操作为FLASH的基本操作。系统可通过两条路径访问FLASH内部的数据。

CPU通过AHB总线，直接对FLASH执行取指取数操作。取指宽度为32bit，且只能访问MAIN空间的数据。为了加快CPU的取指取数据的速度，硬件提供了加速的功能。

CPU通过AHB总线，访问控制器的寄存器，间接实现读取FLASH内部数据的操作。可以访问MAIN和NVR空间的数据；若执行连续读取操作，硬件可自动完成地址累加，无需每次都更新地址寄存器的值。

FLASH_CFGREGION位指示当前访问的是哪个空间。具体表格如下：

表6-1FLASH访问空间分配表  

<table><tr><td>NVR (FLASH_CFGREGION)</td><td>访问区域</td></tr><tr><td>0</td><td>MAIN 区域</td></tr><tr><td>1</td><td>NVR 区域</td></tr></table>

访问控制器的寄存器，实现间接读取FLASH内部数据的操作的执行流程如下：

![](images/fe9534db0dbe50b4b25bba59e1026828ed94a3bcc85b80a605a84392d046de1d.jpg)  
图6-3FLASH间接读取操作流程图

# 6.2.1.4 FLASH编程操作

执行对FLASH存储体的编程操作。一般而言，我们先执行擦除操作，然后才能执行数据编程操作。同时，只能通过访问FLASH控制器的寄存器，实现编程操作。具体流程为：

$\bullet$  控制寄存器CFG，开启编程使能 $\bullet$  地址寄存器ADDR，写入编程地址 $\bullet$  写数据寄存器WDATA，写入编程数据访问本控制器的寄存器，实现FLASH编程操作的执行流程如下：

![](images/f2f36f3aa607aba69881da642cc772c7175e7066b5a187653c86a9aece35b038.jpg)  
图6-4 FLASH模块编程操作流程图

系统工作频率的判断，需要参考SYS_CLK_CFG的配置。FLASH写入/擦除操作的绝对时间是固定的，FLASH控制器需要保存这些绝对时间对应的计数值。FLASH_CFG.TBS默认值是96MHz时钟频率下的计数值；当芯片工作在其他频率下时，需要配置FLASH_CFG.TBS的值，以实现48MHz/24MHz和12MHz的计数值（其它频率暂不支持）。最终保证计数值的的值×时钟频率等于恒定的时间。不同频率下对应的的FLASH_CFG.TBS值请参考6.3.2。切记，FLASH_CFG.TBS仅能配置寄存器说明中提供的几组值，不能被写入其它值，否则可能导致FLASH编程/擦除失败。建议对FLASH_CFG的操作，执行先读回，然后按照或/与的方法操作。另外，在执行FLASH的编程/擦除操作时，CPU将暂停工作直至FLASH的编程/擦除操作完毕。

图6- 4仅展示了一次编程的流程。若执行连续编程时，可以在写入FLASH_ADDR寄存器前，配置FLASH_CFG.ADR_INC，开启地址自动递增模式，后续只需要反复写FLASHWDATA寄存器即可，FLASH_ADDR每次写入一次数据会自动增加  $0\times 4$  。连续读操作类似。连续编程的流程如下：

![](images/ff50e9836ad08d7b4f3fe072902450a9157d398f7438638b0a6da3d666004f33.jpg)  
图6-5 FLASH 模块编程操作流程图

# 6.2.1.5 FLASH 擦除操作

擦除操作为 FLASH 的基本操作。系统只能通过访问 FLASH 控制器的寄存器实现。具体流程为：

- FLASH 擦除操作使能- 地址寄存器 ADDR，写入擦除地址- 写擦除寄存器 ERASE，触发擦除操作

执行对 FLASH 存储体的擦除操作。擦除分成 Sector 和 FullChip。分别对应，512Byte 的擦除和 32KB/64kB 的擦除。通过配置 FLASH 控制寄存器决定执行哪一种类型的擦除操作。

下表为 Block 和 Secotor 地址分配空间。

表6-2FLASHSector地址分配表  

<table><tr><td>Name</td><td>Addresses</td><td>Size(Bytes)</td></tr><tr><td>Sector 0</td><td>0x0000 0000 - 0x0000 01FF</td><td>512</td></tr><tr><td>Sector1</td><td>0x0000 0200 - 0x0000 03FF</td><td>512</td></tr><tr><td>Sector2</td><td>0x0000 0400 - 0x0000 05FF</td><td>512</td></tr><tr><td>...</td><td>...</td><td>...</td></tr><tr><td>Sector127</td><td>0x0000 FE00 - 0x0000 FFFF</td><td>512</td></tr></table>

NVR 区域只能实现 Sector 擦除；MAIN 区域可以实现 Sector 擦除和 FULL 擦除。具体表格如下：

<table><tr><td>NVR (FLASH_CFGREGION)</td><td>Sector Erase</td><td>FULL Erase</td></tr><tr><td>0</td><td>Main 区域</td><td>Main 区域</td></tr></table>

<table><tr><td>1</td><td>NVR 区域</td><td>Main 区域</td></tr></table>

FLASH 擦除操作流程如下所示。

![](images/9aaa80efd9e272df8fdb08a7012603ec25fa328c496259cf34ffc10efe18076b.jpg)  
图6-6 FLASH 模块擦除操作流程图

若选择 Secotor 擦除，需要通过 FLASH_ADDR 确定哪个 Secotor 被擦除，若是 Full Chip 模式的话，FLASH_ADDR 的值将失效。FLASH_ERASE 写入 0x7654DCBA 触发擦除操作。

# 6.2.1.6 FLASH 预取操作

因 FLASH 存储体的速度限制，无法达到 96MHz 的速度。当对 FLASH 进行读取操作时，需要大于 1 个时钟周期才能完成数据的读出。为了加快数据的读出，FLASH 控制器增加了预取功能。当 FLASH 控制器执行完当前读取操作后，在不影响正常程序执行的前提下，顺序预取下一个 WORD 的数据。预取操作的开启和关闭，只需要设置 FLASH_CFG.PREF 即可。

# 6.2.1.7 FLASH 加密保护

若 FLASH 存储体内的数据处于加密状态，用户可执行解密操作，可对 FLASH 存储体内的数据进行解密。相反，若 FLASH 存储体内的数据处于解密状态，用户可执行加密操作，对 FLASH 存储体内的数据进行加密。默认情况下，FLASH 存储体内的数据处于加密状态。芯片上电复位后，硬件自动执行一次加密状态更新操作，是加密状态的话仍然加密状态，是解密的话状态变成解密状态。

FLASH 存储体共有 32kB/64kB 两个规格。无论哪种规格，相应规格中的最后一个 WORD 设计为加密字。当这个 WORD 内容为全 1 时，表明此时 FLASH 处于解密状态；当这个 WORD 的内容被写为非全 1 时，表明此时 FLASH 处于加密状态。若需要加密，执行最后一个 WORD 的编程，写入非全 1 的值，读取 FLASH_PROTECT 寄存器，即触发一次加密状态更新，完成加密（读取 FLASH_PROTECT 返回值无意义）。

对应的解密流程，分成两种情况。若最后一个 WORD 没有执行过编程写入非全 1 的操作，读取 FLASH_PROTECT 寄存器，即完成解密更新（无需考虑此时返回值）。若已经执行过编程写入非全 1

的操作，那么只能执行擦除操作才能解除。先对 FLASH 执行擦除操作，将最后一个 WORD 恢复为全 1 值，然后读取 FLASH_PROTECT 寄存器，即触发一次加密状态更新，完成解密（读取 FLASH_PROTECT 返回值无意义）。

# 6.2.1.8 FLASH 在线升级(IAP)

IAP 模式，实现中断向量表的重映射。在 LKS32MC08x 系列芯片中，包含了系统寄存器 VTOR，其地址为 0xE000_ED08。用于重新映射中断向量表入口地址。

表6-3IAPVTOR寄存器描述  

<table><tr><td>名称</td><td>复位值</td><td>偏移</td><td>位置</td><td>权限</td><td>说明</td></tr><tr><td rowspan="2">VTOR</td><td rowspan="2">0x0</td><td rowspan="2"></td><td>[31:7]</td><td>RW</td><td>执行写入操作，写入中断向量表入口地址</td></tr><tr><td>[6:0]</td><td>--</td><td>默认写 0</td></tr></table>

默认值为  $0\mathrm{x}0$  ，此时中断向量表入口地址为  $0\mathrm{x}0$  。当写入非0值时，中断向量表入口地址将映射到写入值对应的地址上，立即生效。

在 LKS32MC08x 系列芯片中，因为有 VTOR 寄存器。用户可根据自己需求，更新整个 FLASH 的内容。在线升级过程中可以使用中断，也可以关闭中断。

# 6.2.1.8.1 开启中断的在线升级

推荐软件配置流程：

关闭 CPU 的中断控制器，暂时不接收新的中断响应；在新的中断入口地址处，放置中断处理函数代码；将新的中断入口地址写入 VTOR 寄存器；开启 CPU 的中断控制器，使能中断；用户跳转至在线升级函数，开始在线升级功能；完成升级，关闭 CPU 的中断控制器，配置 VTOR 为默认值 0；执行 CPU 软复位，系统 PC 重新从 0 地址开始执行升级后的程序；

# 6.2.1.8.2 关闭中断的在线升级

关闭 CPU 的中断控制器，暂时不接收新的中断响应；

用户跳转至在线升级函数，开始在线升级功能；如果在线升级使用了类似 UART 的外设通讯，需要 CPU 轮询处理 UART 的中断标志位。

执行 CPU 软复位，系统 PC 重新从 0 地址开始执行升级后的程序；

# 6.2.1.8.3在线升级函数的位置

如果需要将flash全部擦除，则需要将在线升级函数放置在RAM中，如果需要使用中断则新的中断向量入口地址也需要位于RAM地址空间。

如果只需要擦除应用程序占用的部分flash区域，则可以将在线升级函数放置在flash高段地址的空闲区域，使用块擦除flash旧的应用程序，写入新的应用程序。

# 6.3 寄存器

# 6.3.1 地址分配

FLASH控制器模块寄存器的基地址是0x4000_0400，寄存器列表如下：

表6-4FLASH控制器模块寄存器列表  

<table><tr><td>名称</td><td>偏移</td><td>说明</td></tr><tr><td>FLASH_CFG</td><td>0x00</td><td>FLASH 配置寄存器</td></tr><tr><td>FLASH_ADDR</td><td>0x04</td><td>地址寄存器</td></tr><tr><td>FLASHWDATA</td><td>0x08</td><td>写数据寄存器</td></tr><tr><td>FLASH_RDATA</td><td>0x0C</td><td>读数据寄存器</td></tr><tr><td>FLASH_ERASE</td><td>0x10</td><td>擦除使能寄存器</td></tr><tr><td>FLASH_PROTECT</td><td>0x14</td><td>FLASH 保护状态寄存器</td></tr><tr><td>FLASH_READY</td><td>0x18</td><td>FLASH 闲忙状态寄存器</td></tr></table>

# 6.3.2 FLASH_CFG配置寄存器（推荐先读回，按或/与方式修改）

地址：0x4000_0400

复位值：0x00000060

表6-5配置寄存器FLASH_CFG  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td>ERS_EN</td><td></td><td></td><td>RMS_EN</td><td></td><td></td><td>ADR_INC</td><td></td><td></td><td>RREF</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td></td><td></td><td>RW</td><td></td><td></td><td>RW</td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td></td><td></td><td>0</td><td></td><td></td><td>0</td><td></td><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>13</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>ERS_TYPE</td><td></td><td></td><td>REGION</td><td></td><td></td><td></td><td></td><td></td><td colspan="6">TBS</td><td></td></tr><tr><td>RW</td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td colspan="6">RW</td><td></td></tr><tr><td>0</td><td></td><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td><td colspan="6">60</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31]</td><td>ERS_EN</td><td>FLASH 擦除使能。默认为 0。
0：关闭擦除</td></tr></table>

<table><tr><td></td><td></td><td>1：开启擦除</td></tr><tr><td>[27]</td><td>PRG_EN</td><td>FLASH编程使能。默认为0。
0：关闭编程
1：开启编程</td></tr><tr><td>[23]</td><td>ADR_INC</td><td>FLASH地址递增使能。默认为0。
0：关闭递增使能
1：开启递增使能
当执行FLASH连续读写访问时，可以开启此功能减少对地址的操作。</td></tr><tr><td>[19]</td><td>PREF</td><td>FLASH预取加速使能。默认为0。
0：关闭加速
1：开启加速</td></tr><tr><td>[15]</td><td>ERS_TYPE</td><td>FLASH擦除类型选择。默认为0。
0：Sector
1：FULL</td></tr><tr><td>[11]</td><td>REGION</td><td>访问FLASH区域选择。默认为0。
0：MAIN
1：NVR</td></tr><tr><td>[6:0]</td><td>TBS</td><td>编程/擦除时间基数寄存器，默认值为0x60。只能配成如下几个值
0x60：96Mhz系统频率下，FLASH编程/擦除时间基数配置值。
0x2F：48Mhz系统频率下，FLASH编程/擦除时间基数配置值。
0x17：24Mhz系统频率下，FLASH编程/擦除时间基数配置值。
0x0B：12Mhz系统频率下，FLASH编程/擦除时间基数配置值。</td></tr></table>

# 6.3.3 FLASH_ADDR地址寄存器

地址：0x4000_0404

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">ADDR</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>ADDR</td><td>地址寄存器。读/写/擦除操作对应的地址寄存器。因按照 WORD 操作，最低两位会被 FLASH 控制器忽略。
执行擦除操作时，需要根据擦除类型，地址需要对齐。一个 Sector 是 512-Byte。若执行 Sector 擦除，地址需要是 512 的整数倍（若带偏移，偏移量会被忽略）。全芯片擦除，不会参考这个寄存器的值</td></tr></table>

# 6.3.4 FLASHWDATA写数据寄存器

地址：0x4000_0408

复位值：0x0

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td colspan="15">WDATA</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">WDATA</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>WDATA</td><td>执行写入操作，写入 FLASH 的值</td></tr></table>

# 6.3.5 FLASH_RDATA读数据寄存器

地址：0x4000_040C

复位值：0x0

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td colspan="15">RDATA</td><td></td></tr><tr><td colspan="15">RO</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr><tr><td>15</td><td>-14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">RDATA</td><td></td></tr><tr><td colspan="15">RO</td><td></td></tr><tr><td colspan="15"></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>RDATA</td><td>执行读取操作，读出 FLASH 的值</td></tr></table>

# 6.3.6 FLASH_ERASE擦除控制寄存器

地址：0x4000_0410

复位值：0x0

表6-9擦除控制寄存器FLASH_ERASE  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td colspan="16">ERASE</td></tr><tr><td colspan="16">WO</td></tr><tr><td colspan="16">0</td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16">ERASE</td></tr><tr><td colspan="15">WO</td><td></td></tr><tr><td colspan="16">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>ERASE</td><td>写入 0x7654DCBA，触发擦除操作</td></tr></table>

# 6.3.7 FLASH_PROTECT 加密状态寄存器

地址：0x4000_0414

复位值：0x0

表6-10加密状态寄存器FLASH_PROTECT  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td colspan="16">PROTECT</td></tr><tr><td colspan="16">RO</td></tr><tr><td colspan="16">0</td></tr><tr><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;nl&gt;</td></tr><tr><td colspan="16">&lt;lcel&gt;</td></tr><tr><td colspan="15">&lt;lcel&gt;</td><td></td></tr><tr><td colspan="16">&lt;lcel&gt;</td></tr></table>

<table><tr><td rowspan="3" colspan="3"></td><td>READY</td></tr><tr><td>RO</td></tr><tr><td>0</td></tr><tr><td>位置</td><td>位名称</td><td colspan="2">说明</td></tr><tr><td>[31:1]</td><td></td><td colspan="2">未使用</td></tr><tr><td>[0]</td><td>READY</td><td colspan="2">1:FLASH 处于闲状态；0:FLASH 处于忙状态</td></tr></table>

# 6.3.9 NVR校正值地址信息

LKS32MC08x产品存储芯片校准参数：

校准参数，每颗产品均独立校准，每颗产品不支持校准参数混用；校准参数，在出厂前进行写入，出厂后不支持编程和擦除，仅支持读取；校准参数，通过LKS公司提供的库函数进行读取访问；校准参数，推荐关闭系统中断后，执行访问操作；

lks32mc08x_nvr.o文件包含了校准参数的读取函数：

读取函数：uint32_tRead_Trim(uint32_t adr);

表6-12校准参数列表  

<table><tr><td>地址</td><td>内容</td></tr><tr><td>0x0310</td><td>ADC0_DCO 校准值</td></tr><tr><td>0x0314</td><td>ADC0_DC1 校准值</td></tr><tr><td>0x0318</td><td>ADC0_AMC0 校准值</td></tr><tr><td>0x031C</td><td>ADC0_AMC1 校准值</td></tr><tr><td>0x0320</td><td>ADC1_DC0 校准值</td></tr><tr><td>0x0324</td><td>ADC1_DC1 校准值</td></tr><tr><td>0x0328</td><td>ADC1_AMC0 校准值</td></tr><tr><td>0x032C</td><td>ADC1_AMC1 校准值</td></tr><tr><td>0x0330</td><td>DAC 选择 3.00V 档位，SYS_AFE_DAC_AMC 校准值（扩大 512 倍结果）</td></tr><tr><td>0x0334</td><td>DAC 选择 1.20V 档位，SYS_AFE_DAC_AMC 校准值（扩大 512 倍结果）</td></tr><tr><td>0x0338</td><td>DAC 选择 4.85V 档位，SYS_AFE_DAC_AMC 校准值（扩大 512 倍结果）</td></tr><tr><td>0x0340</td><td>DAC 选择 3.00V 档位，SYS_AFE_DAC_DC 校准值</td></tr><tr><td>0x0344</td><td>DAC 选择 1.20V 档位，SYS_AFE_DAC_DC 校准值</td></tr><tr><td>0x0348</td><td>DAC 选择 4.85V 档位，SYS_AFE_DAC_DC 校准值</td></tr><tr><td>0x0350</td><td>OPA0，200K 欧姆 VS 10.4K 欧姆，GAIN 校准值（扩大 1000 倍结果），R0 为 0 欧姆</td></tr><tr><td>0x0354</td><td>OPA0，190K 欧姆 VS 20.4K 欧姆，GAIN 校准值（扩大 1000 倍结果），R0 为 0 欧姆</td></tr><tr><td>0x0358</td><td>OPA0，180K 欧姆 VS 30.4K 欧姆，GAIN 校准值（扩大 1000 倍结果），R0 为 0 欧姆</td></tr></table>

<table><tr><td>0x035C</td><td>OPA0, 170K 欧姆 VS 40.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x0360</td><td>OPA1, 200K 欧姆 VS 10.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x0364</td><td>OPA1, 190K 欧姆 VS 20.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x0368</td><td>OPA1, 180K 欧姆 VS 30.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x036C</td><td>OPA1, 170K 欧姆 VS 40.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x0370</td><td>OPA2, 200K 欧姆 VS 10.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x0374</td><td>OPA2, 190K 欧姆 VS 20.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x0378</td><td>OPA2, 180K 欧姆 VS 30.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x037C</td><td>OPA2, 170K 欧姆 VS 40.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x0380</td><td>OPA3, 200K 欧姆 VS 10.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x0384</td><td>OPA3, 190K 欧姆 VS 20.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x0388</td><td>OPA3, 180K 欧姆 VS 30.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x038C</td><td>OPA3, 170K 欧姆 VS 40.4K 欧姆, GAIN 校准值 (扩大 1000 倍结果), R0 为 0 欧姆</td></tr><tr><td>0x0398</td><td>温度传感器, 斜率校准值</td></tr><tr><td>0x039C</td><td>温度传感器, 斜率校准值</td></tr><tr><td>0x03B0</td><td>高 16-bit 存放 OPA1 共模电压, 低 16-bit 存放 OPA0 共模电压 (注意, 均是放大 10000 倍存入)</td></tr><tr><td>0x03B4</td><td>高 16-bit 存放 OPA3 共模电压, 低 16-bit 存放 OPA2 共模电压 (注意, 均是放大 10000 倍存入)</td></tr><tr><td>0x02C0</td><td>OPA0, 200K 欧姆:10.4K 欧姆。高 16 位为 R2 实际电阻值, 低 16 位为 R1 实际电阻值 (扩大 100 倍结果)</td></tr><tr><td>0x02C4</td><td>OPA0, 190K 欧姆:20.4K 欧姆。高 16 位为 R2 实际电阻值, 低 16 位为 R1 实际电阻值 (扩大 100 倍结果)</td></tr><tr><td>0x02C8</td><td>OPA0, 180K 欧姆:30.4K 欧姆。高 16 位为 R2 实际电阻值, 低 16 位为 R1 实际电阻值 (扩大 100 倍结果)</td></tr><tr><td>0x02CC</td><td>OPA0, 170K 欧姆:40.4K 欧姆。高 16 位为 R2 实际电阻值, 低 16 位为 R1 实际电阻值 (扩大 100 倍结果)</td></tr><tr><td>0x02D0</td><td>OPA1, 200K 欧姆:10.4K 欧姆。高 16 位为 R2 实际电阻值, 低 16 位为 R1 实际电阻值 (扩大 100 倍结果)</td></tr><tr><td>0x02D4</td><td>OPA1, 190K 欧姆:20.4K 欧姆。高 16 位为 R2 实际电阻值, 低 16 位为 R1 实际电阻值 (扩大 100 倍结果)</td></tr><tr><td>0x02D8</td><td>OPA1, 180K 欧姆:30.4K 欧姆。高 16 位为 R2 实际电阻值, 低 16 位为 R1 实际电阻值 (扩大 100 倍结果)</td></tr><tr><td>0x02DC</td><td>OPA1, 170K 欧姆:40.4K 欧姆。高 16 位为 R2 实际电阻值, 低 16 位为 R1 实际电阻值 (扩大 100 倍结果)</td></tr><tr><td>0x02E0</td><td>OPA2, 200K 欧姆:10.4K 欧姆。高 16 位为 R2 实际电阻值, 低 16 位为 R1 实际电阻值 (扩大 100 倍结果)</td></tr><tr><td>0x02E4</td><td>OPA2, 190K 欧姆:20.4K 欧姆。高 16 位为 R2 实际电阻值, 低 16 位为 R1 实际电阻值 (扩大 100 倍结果)</td></tr><tr><td>0x02E8</td><td>OPA2, 180K 欧姆:30.4K 欧姆。高 16 位为 R2 实际电阻值, 低 16 位为 R1 实际电阻值 (扩大 100 倍结果)</td></tr><tr><td>0x02EC</td><td>OPA2, 170K 欧姆:40.4K 欧姆。高 16 位为 R2 实际电阻值, 低 16 位为 R1 实际电阻值 (扩大 100 倍结果)</td></tr></table>

<table><tr><td>0x02F0</td><td>OPA3, 200K 欧姆:10.4K 欧姆。高 16 位为 R2 实际电阻值，低 16 位为 R1 实际电阻值（扩大 100 倍结果）</td></tr><tr><td>0x02F4</td><td>OPA3, 190K 欧姆:20.4K 欧姆。高 16 位为 R2 实际电阻值，低 16 位为 R1 实际电阻值（扩大 100 倍结果）</td></tr><tr><td>0x02F8</td><td>OPA3, 180K 欧姆:30.4K 欧姆。高 16 位为 R2 实际电阻值，低 16 位为 R1 实际电阻值（扩大 100 倍结果）</td></tr><tr><td>0x02FC</td><td>OPA3, 170K 欧姆:40.4K 欧姆。高 16 位为 R2 实际电阻值，低 16 位为 R1 实际电阻值（扩大 100 倍结果）</td></tr></table>

# 7 DMA

# 7.1 概述

增加DMA后，总线上主设备由CPU增加为CPU和DMA，总线架构需要由AHBlite 演进为multi- layerAHBlite架构。如图7- 1所示。其中部分设备不需要被DMA访问，仅仅挂载于与CPU相连的AHBBridge0上。包括ADC/DAC/SPI/I2CMCPWM/UART/SRAM在内的设备被CPU和DMA共享访问，挂载于AHBBridge1上。而Timer/DSP/GPIO/Hall/Flash等设备，DMA无法访问。

从设备端的仲裁模块本质上相当于一个二选一的多路选择器。只有端口上有仲裁器的从设备才能被DMA访问到，否则无法被DMA访问，而所有外设设备均可被CPU访问。

![](images/b1f2a4b035e5943e0eb2c051dc98ba2fb46034afb566b5ab7fa241d994c7219c.jpg)  
图7-1 multi-layerAHBlite总线架构

出于功耗控制考虑，DMA模块可以通过设置DMA_CTRL.EN位为0来被禁用（要求关闭DMA使能前先关闭4个通道对应的使能DMA_CCRx.EN），此时DMA时钟被门控关闭。DMA包含配置寄存器（相当于一个从设备，被CPU配置）和数据搬运模块（对于总线为主设备，向总线发起各种设备访问请求）。

DMA支持8，16或32bit(byte，half- word，orword）三种位宽的传输操作，通过配置DMA_CCRx.PBTW和DMA_CCRx.MBTW来选择外设和内存访问的位宽，外设访问的位宽与内存访问的位宽可以不同。

DMA每完成一次传输，地址根据DMA_CCRx.PINC和DMA_CCRx.MINC决定是否自动递增。所有的外设寄存器地址都是word对齐的，所以外设的地址递增永远是0/4（根据DMA_CCRx.PINC=0/1设置)。例如对于UART/SPI/I2C，因为每次都是访问UART_DATA或SPI/I2CFIFO接口的固定地址，DMA_CCRx.PINC=0；如要访问ADC数据寄存器，则地址通常需要自动加4，需要设置

DMA_CCRx.PINC=1。而对于内存，如果设置了DMA_CCRx.MINC=1，每次地址递增的值，根据内存数据位宽(DMA_CCRx.MBTW)设定，对于内存访问位宽为byte的情况，地址自动加1，对于half- word，地址自动加2，对于word，地址自动加4。

需要注意的是，我们将DMA的传输分为多个轮次，每轮传输内可以有多次传输。DMA_CCRx.PINC用于控制外设地址每次传输是否递增。外设地址每轮传输一定重复上一轮的地址，即轮内可以递增，轮间不递增；DMA_CCRx.MINC用于控制内存地址轮间是否递增，每次传输一定递增。

![](images/72921548cea8c87af156cc3b066b59f9961cb9360552b47031f321b24522d42e.jpg)  
图7-2 DMA地址递增控制

DMA有循环模式和单次模式两种模式，由DMA_CCRx.CIRC控制。循环模式下DMA完成一定大小的数据块搬运后重新开始下一轮搬运，如果是搬运数据到内存，则覆盖之前搬运至内存的数据；如果是搬运至外设，则重复一轮数据发射。以将ADC数据搬运至内存为例，设定数据块大小为16bit×12channel×8次，则在循环模式下DMA完成一轮96个half word搬运后重新开始下一轮搬运，并覆盖之前使用的内存地址，不设置DMA完成中断标志位。单次模式下，DMA完成一定大小的数据块搬运后即完成本次DMA操作，设置完成DMA完成中断标志位，同时硬件自动关闭对应的DMA通道，即硬件电路自动在该通道传输完成后将DMA_CCRx.EN设为0。DMA需要搬运的轮次由DMA_CTMS寄存器进行控制。

# 7.2 请求

DMA的请求分为软件请求和硬件请求两类，软件请求通过设置对应DMA通道的DMA_CCRx.SW_TRIG  $\equiv 1$  来产生，写1即产生，软件触发位设置后需要软件清零。硬件请求通常为外设的中断事件，当特定的外设中断事件作为DMA传输请求时，通常要禁用对应事件的中断响应。而且硬件DMA请求信号经过DMA通道受理握手后会被DMA硬件清零，无法软件清除事件标志。

表7-1DMA请求  

<table><tr><td>触发来源</td><td>描述</td></tr><tr><td>软件</td><td>软件触发时进行的搬运操作由配置寄存器DMA_CCRx指定，当设置了DMA_CCRx.SW_TRIG，一旦通道被使能即开始进行DMA 操作。此版本DMA 暂不支持内存至内存搬运！！！</td></tr><tr><td>ADC</td><td>ADC在单段触发模式下，一次完成若干个通道后采样后产生中断请求，由DMA把ADC转换后的值搬运到SRAM。ADC单段采样完成中断事件作为DMA请求信号，请求信号在得到DMA响应后由DMA将其清零，不要软件清零；注意此时需要软件同时禁用ADC采用完成中断，使中断不再被CPU响应。</td></tr><tr><td>UART</td><td>串口模块使用 UART_IF触发DMA请求，如果DMA配置的传输方向是内存到串口，则使用UART发送完成事件产生DMA请求信号；如果传输方向是串口到内存，则应使用UART接收完成事件产生DMA请求信号。事件标志由DMA自动清零。UART在由DMA操作时应同样禁用相应中断防止被CPU响应。有两种方案可选：
方案1：若 UARTx_IE.TX_BUF_EMPTY_RE配置有效，UARTx模块将预取第一个字节，准备发送；一旦数据进入发射队列，UARTx_IE.UARTx_BUF 不能为空，硬件自动会请求DMA搬移下一个字节直至数据搬移完毕。DMA搬移完毕后，将产生DMA完成中断，但是UARTx很可能没有发送完毕最后一个字节，若立即操作UARTx，将可能会产生异常。建议在DMA中断处理程序中，开启UARTx_IE.TX_DONE_IE中断，UARTx将最后一个字节发送完毕，产生发送完成中断，在UARTx中断处理函数里面，再关闭UARTx_IE.TXT_DONE_IE。
方案2：若 UARTx_IE.TX_DONE_RE配置有效。建议UART初始化阶段不要清除TX_DONE标志。当前传输的数据长度为Len，DMA配置传输的字节数为Len，开启DMA中断，DMA传输完毕后，UART也发送完毕，软复位UARTx模块并重新初始化UARTx，可开启下一次UARTx的发送。</td></tr><tr><td>SPI</td><td>SPI模块使用接收缓冲区满事件作为DMA请求信号，由于SPI是同时收发，所以接收缓冲区满既是接收完毕也是发送完毕的事件标志。读取SPI FIFO自动清除事件标志。</td></tr><tr><td>I2C</td><td>I2C模块使用I2C0_SCR.BYTE_CMPLT即字节发送完成作为触发DMA请求，DMA自动清除I2C的请求标志。其他I2C中断事件仍由CPU响应</td></tr><tr><td>Timer</td><td>Timer使用过零/比较/捕获事件作为DMA请求，具体DMA操作根据配置寄存器设定，通常作为定时事件（如每隔10ms触发一次DMA操作）</td></tr><tr><td>MCPWM</td><td>MCPWM模块使用过零/计数周期结束/4个ADC触发信号作为DMA请求，具体DMA操作根据配置寄存器设定</td></tr><tr><td>CAN</td><td></td></tr></table>

# 7.3 优先级

DMA的优先级采用固定优先级，优先级如图7- 3所示。为避免出现来不及响应某些外设请求的情况，在设计应用软件时应考虑任务实时性，每个通道不配置搬运过于大量的数据导致其他通道得不到及时响应。

如图7- 3所示，优先级由上至下降低。4个DMA通道中，优先级关系为：通道  $0>$  通道  $1>$  通道 $2>$  通道3(>号表示优先级高于)。在DMA各通道内部，通常有3个硬件请求事件和一个软件请求事件，硬件请求优先级高于软件请求。3个硬件请求事件优先级相同，通常应用上面一个DMA通道配置一个硬件请求事件使能，多个硬件请求不应在一个通道内同时发生。

![](images/12524905e61bfa95330bcd5148d65b3be2abe74bb6f739c329cb62856f2638c0.jpg)  
图7-3DMA通道优先级

# 7.4 仲裁

当DMA处于空闲状态，或刚刚完成某一通道的DMA传输后，若此时恰好有一个或多个DMA请求发生，应根据优先级设定进行仲裁，优先级高的外设请求率先得到DMA服务。比如ADC连续模式下，每完成一轮ADC数据搬运，ADC的采样完成事件标志被DMA清零，DMA回到空闲状态或转而服务其他外设请求；对于UART，每搬运一个byte重新仲裁；对于SPI/I2C每搬运完一个FIFO的数据，重新仲裁。

CPU访问RAM的优先级始终高于DMA。

为了避免CPU或DMA长期占用外设/SRAM，在外设/SRAM的端口仲裁模块中加入了时间片机制，即一个主设备占用一段时间后释放访问权，仲裁模块观测另一个主设备是否在请求访问，如果

是则转而允许另一个主设备访问，否则继续当前主设备未完成的访问。

# 7.5 中断

DMA的一个通道完成DMA操作后或出错则产生DMA中断。当DMA某一个通道完成操作后，会自动关闭该通道的使能为DMACCRx.EN。

# 7.6 寄存器

# 7.6.1 地址分配

DMA控制器模块寄存器的基地址是0x4001_3000，寄存器列表如下：

表7-2DMA寄存器列表  

<table><tr><td>名称</td><td>偏移地址</td><td>说明</td></tr><tr><td>DMACCR0</td><td>0x00</td><td>DMA通道0通道配置寄存器</td></tr><tr><td>DMACTMS0</td><td>0x04</td><td>DMA通道0传输次数寄存器</td></tr><tr><td>DMACPAR0</td><td>0x08</td><td>DMA通道0外设地址寄存器</td></tr><tr><td>DMACMAR0</td><td>0x0C</td><td>DMA通道0内存地址寄存器</td></tr><tr><td>DMACCR1</td><td>0x10</td><td>DMA通道1通道配置寄存器</td></tr><tr><td>DMACTMS1</td><td>0x14</td><td>DMA通道1传输次数寄存器</td></tr><tr><td>DMACPAR1</td><td>0x18</td><td>DMA通道1外设地址寄存器</td></tr><tr><td>DMACMAR1</td><td>0x1C</td><td>DMA通道1内存地址寄存器</td></tr><tr><td>DMACCR2</td><td>0x20</td><td>DMA通道2通道配置寄存器</td></tr><tr><td>DMACTMS2</td><td>0x24</td><td>DMA通道2传输次数寄存器</td></tr><tr><td>DMACPAR2</td><td>0x2B</td><td>DMA通道2外设地址寄存器</td></tr><tr><td>DMACMAR2</td><td>0x2C</td><td>DMA通道2内存地址寄存器</td></tr><tr><td>DMACCR3</td><td>0x30</td><td>DMA通道3通道配置寄存器</td></tr><tr><td>DMACTMS3</td><td>0x34</td><td>DMA通道3传输次数寄存器</td></tr><tr><td>DMACPAR3</td><td>0x38</td><td>DMA通道3外设地址寄存器</td></tr><tr><td>DMACMAR3</td><td>0x3C</td><td>DMA通道3内存地址寄存器</td></tr><tr><td>DMACTRL</td><td>0x40</td><td>DMA控制寄存器</td></tr><tr><td>DMAIF</td><td>0x44</td><td>DMA中断标志寄存器</td></tr></table>

# 7.6.2 DMA_CTRLDMA控制寄存器

地址：0x4001_3040

复位值：0x0

<table><tr><td colspan="13">表 7-3 DMA 控制寄存器 DMA_CTRL</td><td></td><td></td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>PRIORITY</td><td>EN</td><td></td></tr></table>

<table><tr><td rowspan="2"></td><td>RW</td><td>RW</td></tr><tr><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:2]</td><td></td><td>未使用</td></tr><tr><td>[1]</td><td>PRIORITY</td><td>0:CPU 优先级高；1:DMA 优先级高，此版本必须设置 CPU 优先级高</td></tr><tr><td>[0]</td><td>EN</td><td>DMA 使能</td></tr></table>

# 7.6.3 DMA_IF DMA 中断标志寄存器

地址：0x4001_3044

复位值：0x0

15 14 13 12 11 10 0 8 7 6 5 4 3 2 1 0

表7-4DMA中断标志寄存器DMA_IF  

<table><tr><td rowspan="3"></td><td>CH3_EIF</td><td>CH2_EIF</td><td>CH1_EIF</td><td>CH0_EIF</td><td>CH2_FIF</td><td>CH2_FIF</td><td>CH1_FIF</td><td>CH0_FIF</td></tr><tr><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7]</td><td>CH3_EIF</td><td>通道3错误中断标志</td></tr><tr><td>[6]</td><td>CH2_EIF</td><td>通道2错误中断标志</td></tr><tr><td>[5]</td><td>CH1_EIF</td><td>通道1错误中断标志</td></tr><tr><td>[4]</td><td>CH0_EIF</td><td>通道0错误中断标志</td></tr><tr><td>[3]</td><td>CH3_FIF</td><td>通道3完成中断标志</td></tr><tr><td>[2]</td><td>CH2_FIF</td><td>通道2完成中断标志</td></tr><tr><td>[1]</td><td>CH1_FIF</td><td>通道1完成中断标志</td></tr><tr><td>[0]</td><td>CH0_FIF</td><td>通道0完成中断标志</td></tr></table>

# 7.6.4 DMA 通道配置寄存器

# 7.6.4.1 DMA_CCRx(where  $\mathbf{x} = 0,1,2,3$

地址分别是：0x4001_3000，0x4001_3010，0x4001_3020，0x4001_3030

复位值：0x0

表7-5DMA通道配置寄存器DMA_CCRx  

<table><tr><td>SW_TRIG</td><td>REQ_EN</td><td>MBTW</td><td>PBTW</td><td>MINC</td><td>PINC</td><td>CIRC</td><td>DIR</td><td>TEIE</td><td>TCIE</td><td>EN</td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td></tr></table>

<table><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>SW_TRIG</td><td>软件触发，高有效*2</td></tr><tr><td>[14:12]</td><td>REQ_EN</td><td>通道X三个硬件DMA请求使能*1，高有效</td></tr><tr><td>[11:10]</td><td>MBTW</td><td>内存访问位宽，0:byte, 1:half-word, 2:word, 3:保留</td></tr><tr><td>[9:8]</td><td>PBTW</td><td>外设访问位宽，0:byte, 1:half-word, 2:word, 3:保留</td></tr><tr><td>[7]</td><td>MINC</td><td>内存地址第二轮是否在第一轮地址的基础上递增（轮内一定递增），高有效</td></tr><tr><td>[6]</td><td>PINC</td><td>指示外设地址每轮内是否递增（外设地址第二轮一定重复第一轮地址），高有效</td></tr><tr><td>[5]</td><td>CIRC</td><td>循环模式，高有效</td></tr><tr><td>[4]</td><td>DIR</td><td>传输方向，0:外设至内存，1:内存至外设</td></tr><tr><td>[3]</td><td></td><td>保留</td></tr><tr><td>[2]</td><td>TEIE</td><td>错误中断使能，高有效</td></tr><tr><td>[1]</td><td>TCIE</td><td>传输完成中断使能，高有效</td></tr><tr><td>[0]</td><td>EN</td><td>通道&amp;amp;使能，高有效，在通道操作全部完成后由DMA清除此位</td></tr></table>

$^{*1}$  以通道0为例，DMA_CCR0. REQ_EN[2:0]分别为Timer1、Timer0、ADC0的DMA请求使能。且DMA的通道中配置的内存、外设地址应与使能的外设中断请求相对应，这一点需要由应用软件保证。其中软件请求始终处于使能状态，即软件写入DMA_CCRx.SW_TRIG位即开始一次DMA传输。来自外设的硬件请求进入DMA后通过或逻辑形成一个请求信号，每一个DMA通道同时只应使能一个硬件DMA请求。  $^* 2$  软件触发标志DMA_CCRx.SW_TRIG写入1后需要软件清0。

表7-6DMA通道请求信号  

<table><tr><td>DMA 通道</td><td>设备请求信号编号</td><td>外设</td></tr><tr><td rowspan="3">Channel 0</td><td>0</td><td>ADC0</td></tr><tr><td>1</td><td>Timer0</td></tr><tr><td>2</td><td>Timer1</td></tr><tr><td rowspan="3">Channel 1</td><td>0</td><td>SPI_RX</td></tr><tr><td>1</td><td>MCPWM</td></tr><tr><td>2</td><td>Timer2</td></tr><tr><td rowspan="3">Channel 2</td><td>0</td><td>UART0</td></tr><tr><td>1</td><td>SPI_TX</td></tr><tr><td>2</td><td>Timer3</td></tr><tr><td rowspan="3">Channel 3</td><td>0</td><td>UART1</td></tr><tr><td>1</td><td>CAN</td></tr><tr><td>2</td><td>I2C</td></tr></table>

# 7.6.4.2 DMA_CTMSx (where  $\mathrm{x} = 0,1,2,3$

地址分别是：0x4001_3004，0x4001_3014，0x4001_3024，0x4001_3034

复位值：0x0

![](images/7eaf16c03499d1722905100d439d3c89031b8b60602d1652625969811d2ea28d.jpg)

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:24]</td><td></td><td>未使用</td></tr><tr><td>[23:16]</td><td>ROUND</td><td>DMA 通道 x 采样轮数</td></tr><tr><td>[15:9]</td><td></td><td>未使用</td></tr><tr><td>[8:0]</td><td>TIMES</td><td>DMA 通道 x 每轮数据搬运次数，0～512。此寄存器在该通道使能后变为只读。</td></tr></table>

DMA_CTMSx寄存器只有在通道禁用，即DMA_CCRx.EN=0之后才可以写入数据。

以外设数据宽度为16，内存数据宽度为32，即CTMS.TIMES  $= 16$  ，CTMS.ROUND  $= 2$  为例，DMA每轮需要读取外设数据16bit  $\times 16 = 32$  byte，写入内存数据32bit  $\times 16 = 64$  byte。一共需要搬运两轮，即读取外设64byte，输入内存128byte；

即使仅仅搬运一轮，也需要设置CTMS.ROUND  $= 1$  ，而不能让其为0。

当设置DMA_CCRx.CIRC=1（即循环模式）时，CTMS.ROUND不再起作用，相当于无限轮；其他情况需要相应设置CTMS.ROUND，如CTMS.ROUND  $= 1$  ，用于搬运一轮数据。

当DMA_CTRL=1且DMA_CCRx.EN=0时，重新填写CTMSx值，可以将DMA内部已搬运的轮数次数计数器清零。

通常在开启DMA之前需要将触发DMA启动的外设接收中断标志位清零，防止之前留下的中断标志位成为DMA触发源造成一次错误触发。以UART为例，通常DMA被配置为多轮搬运，每轮搬运一次，每次搬运一个字节。如果UART接收FIFO不空，且UART_IF[1]未清零，则使能DMA通道后立即发生一次DMA搬运，但此时的DMA搬运的数据是UART之前遗留的数据，并非实际需要搬运的数据，且此时DMA内部的轮次增1，可能会导致接收的UART数据帧发生错位。出现这种情况，可以通过重写DMA_CTMS来讲DMA内部的轮次计数重置。

而在使用DMA通过UART发送数据时，通常使用的是UART TX_FIFO空标志作为DMA请求，外设上电后发送FIFO空即有效，无须软件清除这一标志。否则无法向DMA产生第一次的发送请求。

# 7.6.4.3 DMA_CPARx (where  $\mathrm{x} = 0,1,2,3$

地址分别是：0x4001_3008，0x4001_3018，0x4001_3028，0x4001_3038

复位值：0x0

![](images/8c1bda905d96d80590fb3c0db6d6eb5b125fa2e84565dd726de57247140be907.jpg)

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:17]</td><td></td><td>未使用</td></tr><tr><td>[16:0]</td><td>PERI_ADDR</td><td>DMA 通道 x 外设地址</td></tr></table>

当DMA_CCRx.PBTW=7'b01时，即配置为以16bit为单位搬运外设数据。CPARx.PERI_ADDR[0]值无效，外设地址会以2为单位递增。

当DMA_CCRx.PBTW=7'b10时，即配置为以32bit为单位搬运外设数据。CPARx.PERI_ADDR[1:0]值无效，外设地址会以4为单位递增。

注意：DMA_CPARx寄存器只有在通道禁用，即DMA_CCRx.EN=0之后才可以写入数据！！！

由于只进行内存与外设间的数据搬运，因此DMA_CPAR只存储外设地址的低17位，高15位恒为  $0\mathrm{x}2000$  ，高20位可能为  $0\mathrm{x}40000$  (对应SYS寄存器)或  $0\mathrm{x}4001^{*}$  (对应外设寄存器)。

# 7.6.4.4 DMA_CMARx (where  $\mathrm{x} = 0,1,2,3$

地址分别是：0x4001_300C，0x4001_301C，0x4001_302C，0x4001_303C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td></td></tr><tr><td></td></tr><tr><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr></table>

当 DMA_CCRx.MBTW=2'b01 时, 即配置为以 16bit 为单位搬运内存数据。CMARx.MEM_ADDR[0] 值无效, 内存地址会以 2 为单位递增。

当 DMA_CCRx.MBTW=2'b10 时, 即配置为以 32bit 为单位搬运内存数据。CMARx.MEM_ADDR[1:0] 值无效, 内存地址会以 4 为单位递增。

注意：DMA_CMARx 寄存器只有在通道禁用, 即 DMA_CCRx.EN=0 之后才可以写入数据!!!

由于只进行内存与外设间的数据搬运, 因此 DMA_CMAR 只存储地址的低 13 位, 对应 SRAM8kB 地址空间。高 19 位恒为 0x10000。

# 8 GPIO

# 8.1 概述

LSK32MC08X系列芯片共集成了4组16bit位宽GPIO。P0.0/P0.1/P1.0/P1.14个GPIO可以作为系统的唤醒源。  $\mathrm{P0.15\sim P0.0}$  共16个GPIO可以用作外部中断源输入。

其中P0.2既可以当做外部复位脚，也可以当做GPIO使用。可以通过软件设置SYS_RST_CFG.RST_IO进行切换。上电后，P0.2默认用做外部复位脚，因此应用上应该注意上电后P0.2的外部信号不能一直为低，否则芯片会一直处于复位状态。复位释放后，软件可以将SYS_RST_CFG.RST_IO置1，将P0.2切换为GPIO功能，SYS_RST_CFG受SYS_WR_PROTECT保护。

在某些低引脚数封装中，例如SSOP24，P2.15与SWDIO复用为同一个引脚。此种复用是通过封装直接bonding在一起实现的。芯片上电后，P2.15默认状态下输入输出全部禁用，此时不影响SWDIO参与SWD通讯。如果应用上需要将此引脚复用为GPIO，即使用P2.15，需要注意保留某种手段再次关闭P2.15的输出使能，以将引脚切换成SWDIO，否则可能导致芯片SWD无法使用。

# 8.1.1 功能框图

![](images/4a918ef62aa879ef9454b101be5dd5e8c2ffc07e16880ab113b208e48f9f85bf.jpg)  
图8-1 GPIO功能框图

![](images/dff2d112070bb39921ae1450615e9d40c86f4178186942b00053f14ccccf90ed.jpg)

图8- 1所示， $\mathrm{Pm[n]}$  为芯片PAD，m可以是  $0\sim 3$  ，表示4组GPIO中的任意一组，n可以是  $0\sim 15$  ，表示一组16bit GPIO中的一个IO。模拟信号通过一个电阻串联直接连接到PAD，电阻阻值为 $100\sim 200\Omega$  。数字信号经过一个三态门输出，当输出使能GPIom_POE[n]  $= 0$  时，buffer输出高阻态，否则buffer输出与GPIom_PDO[n]电平相同。数字信号输入通过一个与门进入芯片内部，当GPIom_PIE[n]  $= 0$  时，GPIom_PDI[n]恒为0，当GPIom_PIE[n]  $= 1$  ，即输入使能打开时，GPIom_PDI[n]的电平与  $\mathrm{Pm[n]}$  电平相同。芯片PAD可以配置上拉，P0[2]引脚因为复用为外部复位脚RSTN上拉电阻为  $100k\Omega$  ，其余上拉电阻为  $10k\Omega$  ，注意，并非所有PAD都配备上拉电阻，具体哪些PAD具有上拉电阻资源，请参考8.3.1上拉实现章节。没有上拉电阻的PAD也可以配置GPIom_PUE[n]寄存器，但无实际作用。

# 8.1.2 产品特点

- 4组16bit GPIO- 支持开漏- 部分IO支持上拉- 支持配置锁定保护- 支持外部中断- 支持GPIO唤醒

# 8.2 寄存器

# 8.2.1 地址分配

GPIO0模块在芯片中的基地址是0x40012000。GPIO1模块在芯片中的基地址是0x40012040。GPIO2模块在芯片中的基地址是0x40012080。GPIO3模块在芯片中的基地址是0x400120C0。

GPIO0/1/2/3的寄存器定义完全相同，仅基地址不同，寄存器列表如下：

表8-1GPIOx寄存器列表  

<table><tr><td>名称</td><td>偏移地址</td><td>说明</td></tr><tr><td>GPIOx_PIE</td><td>0x00</td><td>GPIO x 输入使能</td></tr><tr><td>GPIOx_POE</td><td>0x04</td><td>GPIO x 输出使能</td></tr><tr><td>GPIOx_PDI</td><td>0x08</td><td>GPIO x 输入数据</td></tr><tr><td>GPIOx_PDO</td><td>0x0C</td><td>GPIO x 输出数据</td></tr><tr><td>GPIOx_PUE</td><td>0x10</td><td>GPIO x 上拉使能</td></tr><tr><td>GPIOx_PODE</td><td>0x18</td><td>GPIO x 开漏使能</td></tr><tr><td>GPIOx_LCKR</td><td>0x1C</td><td>GPIO x 配置锁定</td></tr><tr><td>GPIOx_F3210</td><td>0x20</td><td>GPIO x [3:0] 功能选择</td></tr><tr><td>GPIOx_F7654</td><td>0x24</td><td>GPIO x [7:4] 功能选择</td></tr><tr><td>GPIOx_FBA98</td><td>0x28</td><td>GPIO x [11:8] 功能选择</td></tr><tr><td>GPIOx_FFEDC</td><td>0x2C</td><td>GPIO x [15:12] 功能选择</td></tr></table>

GPIO中断/唤醒/配置锁定模块的基地址是0x40012100，寄存器列表如下：

表8-2GPIO中断/唤醒/配置锁定模块寄存器列表  

<table><tr><td>名称</td><td>偏移地址</td><td>说明</td></tr><tr><td>EXTI_CR0</td><td>0x00</td><td>GPIO 0[7:0] 中断触发类型</td></tr><tr><td>EXTI_CR1</td><td>0x04</td><td>GPIO 0[15:8] 中断触发类型</td></tr><tr><td>EXTI_IF</td><td>0x08</td><td>GPIO 中断标志</td></tr><tr><td>LCKR_PRT</td><td>0x0C</td><td>GPIO 保护锁定配置</td></tr><tr><td>WAKE_POL</td><td>0x10</td><td>GPIO 唤醒信号极性</td></tr><tr><td>WAKE_EN</td><td>0x14</td><td>GPIO 唤醒使能</td></tr></table>

# 8.2.2 GPIOxPIE

地址分别是：0x4001_2000，0x4001_2040，0x4001_2080，0x4001_20C0

复位值：0x0

表8-3GPIOx输入使能寄存器GPIOxPIE  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>PIE15</td><td>PIE14</td><td>PIE13</td><td>PIE12</td><td>PIE11</td><td>PIE10</td><td>PIE9</td><td>PIE8</td><td>PIE7</td><td>PIE6</td><td>PIE5</td><td>PIE4</td><td>PIE3</td><td>PIE2</td><td>PIE1</td><td>PIE0</td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[S1:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>PIE15</td><td>GPIO x[15] / Px[15] 输入使能</td></tr><tr><td>[14]</td><td>PIE14</td><td>GPIO x[14] / Px[14] 输入使能</td></tr><tr><td>[13]</td><td>PIE13</td><td>GPIO x[13] / Px[13] 输入使能</td></tr><tr><td>[12]</td><td>PIE12</td><td>GPIO x[12] / Px[12] 输入使能</td></tr><tr><td>[11]</td><td>PIE11</td><td>GPIO x[11] / Px[11] 输入使能</td></tr><tr><td>[10]</td><td>PIE10</td><td>GPIO x[10] / Px[10] 输入使能</td></tr><tr><td>[9]</td><td>PIE9</td><td>GPIO x[9] / Px[9] 输入使能</td></tr><tr><td>[8]</td><td>PIE8</td><td>GPIO x[8] / Px[8] 输入使能</td></tr><tr><td>[7]</td><td>PIE7</td><td>GPIO x[7] / Px[7] 输入使能</td></tr><tr><td>[6]</td><td>PIE6</td><td>GPIO x[6] / Px[6] 输入使能</td></tr><tr><td>[5]</td><td>PIE5</td><td>GPIO x[5] / Px[5] 输入使能</td></tr><tr><td>[4]</td><td>PIE4</td><td>GPIO x[4] / Px[4] 输入使能</td></tr><tr><td>[3]</td><td>PIE3</td><td>GPIO x[3] / Px[3] 输入使能</td></tr><tr><td>[2]</td><td>PIE2</td><td>GPIO x[2] / Px[2] 输入使能</td></tr><tr><td>[1]</td><td>PIE1</td><td>GPIO x[1] / Px[1] 输入使能</td></tr><tr><td>[0]</td><td>PIE0</td><td>GPIO x[0] / Px[0] 输入使能</td></tr></table>

# 8.2.3 GPIOxPOE

地址分别是：0x4001_2004，0x4001_2044，0x4001_2084，0x4001_20C4

复位值：0x0

表8-4GPIOx输出使能寄存器GPIOxPOE  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>POE1</td><td>POE1</td><td>POE1</td><td>POE1</td><td>POE1</td><td>POE1</td><td>POE</td><td>POE</td><td>POE</td><td>POE</td><td>POE</td><td>POE</td><td>POE</td><td>POE</td><td>POE</td><td>POE</td></tr><tr><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>POE15</td><td>GPIO x[15] / Px[15] 输出使能</td></tr><tr><td>[14]</td><td>POE14</td><td>GPIO x[14] / Px[14] 输出使能</td></tr></table>

<table><tr><td>[13]</td><td>POE13</td><td>GPIOx[13] / Px[13] 输出使能</td></tr><tr><td>[12]</td><td>POE12</td><td>GPIOx[12] / Px[12] 输出使能</td></tr><tr><td>[11]</td><td>POE11</td><td>GPIOx[11] / Px[11] 输出使能</td></tr><tr><td>[10]</td><td>POE10</td><td>GPIOx[10] / Px[10] 输出使能</td></tr><tr><td>[9]</td><td>POE9</td><td>GPIOx[9] / Px[9] 输出使能</td></tr><tr><td>[8]</td><td>POE8</td><td>GPIOx[8] / Px[8] 输出使能</td></tr><tr><td>[7]</td><td>POE7</td><td>GPIOx[7] / Px[7] 输出使能</td></tr><tr><td>[6]</td><td>POE6</td><td>GPIOx[6] / Px[6] 输出使能</td></tr><tr><td>[5]</td><td>POE5</td><td>GPIOx[5] / Px[5] 输出使能</td></tr><tr><td>[4]</td><td>POE4</td><td>GPIOx[4] / Px[4] 输出使能</td></tr><tr><td>[3]</td><td>POE3</td><td>GPIOx[3] / Px[3] 输出使能</td></tr><tr><td>[2]</td><td>POE2</td><td>GPIOx[2] / Px[2] 输出使能</td></tr><tr><td>[1]</td><td>POE1</td><td>GPIOx[1] / Px[1] 输出使能</td></tr><tr><td>[0]</td><td>POE0</td><td>GPIOx[0] / Px[0] 输出使能</td></tr></table>

# 8.2.4 GPIOx_PDI

地址分别是：0x4001_2008，0x4001_2048，0x4001_2088，0x4001_20C8

复位值：0x0

表8-5GPIOx输入数据寄存器GPIOx_PDI  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">PDI</td><td></td></tr><tr><td colspan="15">RO</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>PDI</td><td>GPIOx输入数据</td></tr></table>

当GPIOxPIE  $= 0$  时，GPIOx_PDI读回为0。

# 8.2.5 GPIOx_PDO

地址分别是：0x4001_200C，0x4001_204C，0x4001_208C，0x4001_20CC

复位值：0x0

表8-6GPIOx输出数据寄存器GPIOx_PDO  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">PDO</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>PDO</td><td>GPIOx 输出数据</td></tr></table>

# 8.2.6 GPIOx_PUE

地址分别是：0x4001_2010，0x4001_2050，0x4001- 2090，0x4001_20D0

复位值：0x0

表8-7GPIOx上拉使能寄存器GPIOx_PUE  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>PUE15</td><td>PUE14</td><td>PUE13</td><td>PUE12</td><td>PUE11</td><td>PUE10</td><td>PUE9</td><td>PUE8</td><td>PUE7</td><td>PUE6</td><td>PUE5</td><td>PUE4</td><td>PUE3</td><td>PUE2</td><td>PUE1</td><td>PUE0</td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>PUE15</td><td>GPIOx[15] / Px[15] 上拉使能</td></tr><tr><td>[14]</td><td>PUE14</td><td>GPIOx[14] / Px[14] 上拉使能</td></tr><tr><td>[13]</td><td>PUE13</td><td>GPIOx[13] / Px[13] 上拉使能</td></tr><tr><td>[12]</td><td>PUE12</td><td>GPIOx[12] / Px[12] 上拉使能</td></tr><tr><td>[11]</td><td>PUE11</td><td>GPIOx[11] / Px[11] 上拉使能</td></tr><tr><td>[10]</td><td>PUE10</td><td>GPIOx[10] / Px[10] 上拉使能</td></tr><tr><td>[9]</td><td>PUE9</td><td>GPIOx[9] / Px[9] 上拉使能</td></tr><tr><td>[8]</td><td>PUE8</td><td>GPIOx[8] / Px[8] 上拉使能</td></tr><tr><td>[7]</td><td>PUE7</td><td>GPIOx[7] / Px[7] 上拉使能</td></tr><tr><td>[6]</td><td>PUE6</td><td>GPIOx[6] / Px[6] 上拉使能</td></tr><tr><td>[5]</td><td>PUE5</td><td>GPIOx[5] / Px[5] 上拉使能</td></tr><tr><td>[4]</td><td>PUE4</td><td>GPIOx[4] / Px[4] 上拉使能</td></tr><tr><td>[3]</td><td>PUE3</td><td>GPIOx[3] / Px[3] 上拉使能</td></tr><tr><td>[2]</td><td>PUE2</td><td>GPIOx[2] / Px[2] 上拉使能</td></tr><tr><td>[1]</td><td>PUE1</td><td>GPIOx[1] / Px[1] 上拉使能</td></tr><tr><td>[0]</td><td>PUE0</td><td>GPIOx[0] / Px[0] 上拉使能</td></tr></table>

# 8.2.7 GPIOx_PODE

地址分别是：0x4001_2018，0x4001_2058，0x4001_2098，0x4001_20D8

复位值：0x0

表8-8GPIOx开漏使能寄存器GPIOxPODE  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>PODE15</td><td>PODE14</td><td>PODE13</td><td>PODE12</td><td>PODE11</td><td>PODE10</td><td>PODE9</td><td>PODE8</td><td>PODE7</td><td>PODE6</td><td>PODE5</td><td>PODE4</td><td>PODE3</td><td>PODE2</td><td>PODE1</td><td>PODE0</td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>PODE15</td><td>GPIO x[15] / Px[15] 开漏使能</td></tr><tr><td>[14]</td><td>PODE14</td><td>GPIO x[14] / Px[14] 开漏使能</td></tr><tr><td>[13]</td><td>PODE13</td><td>GPIO x[13] / Px[13] 开漏使能</td></tr><tr><td>[12]</td><td>PODE12</td><td>GPIO x[12] / Px[12] 开漏使能</td></tr><tr><td>[11]</td><td>PODE11</td><td>GPIO x[11] / Px[11] 开漏使能</td></tr><tr><td>[10]</td><td>PODE10</td><td>GPIO x[10] / Px[10] 开漏使能</td></tr><tr><td>[9]</td><td>PODE9</td><td>GPIO x[9] / Px[9] 开漏使能</td></tr><tr><td>[8]</td><td>PODE8</td><td>GPIO x[8] / Px[8] 开漏使能</td></tr><tr><td>[7]</td><td>PODE7</td><td>GPIO x[7] / Px[7] 开漏使能</td></tr><tr><td>[6]</td><td>PODE6</td><td>GPIO x[6] / Px[6] 开漏使能</td></tr><tr><td>[5]</td><td>PODE5</td><td>GPIO x[5] / Px[5] 开漏使能</td></tr><tr><td>[4]</td><td>PODE4</td><td>GPIO x[4] / Px[4] 开漏使能</td></tr><tr><td>[3]</td><td>PODE3</td><td>GPIO x[3] / Px[3] 开漏使能</td></tr><tr><td>[2]</td><td>PODE2</td><td>GPIO x[2] / Px[2] 开漏使能</td></tr><tr><td>[1]</td><td>PODE1</td><td>GPIO x[1] / Px[1] 开漏使能</td></tr><tr><td>[0]</td><td>PODE0</td><td>GPIO x[0] / Px[0] 开漏使能</td></tr></table>

# 8.2.8 GPIOx_LCKR

地址分别是：0x4001_201C，0x4001_205C，0x4001_209C，0x4001_20DC

复位值：0x0

表8-9GPIOx配置锁定寄存器GPIOx_LCKR  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>PLCKR15</td><td>PLCKR14</td><td>PLCKR13</td><td>PLCKR12</td><td>PLCKR11</td><td>PLCKR10</td><td>PLCKR9</td><td>PLCKR8</td><td>PLCKR7</td><td>PLCKR6</td><td>PLCKR5</td><td>PLCKR4</td><td>PLCKR3</td><td>PLCKR2</td><td>PLCKR1</td><td>PLCKR0</td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>PLCKR15</td><td>GPIO x[15] / Px[15] 配置锁定</td></tr><tr><td>[14]</td><td>PLCKR14</td><td>GPIO x[14] / Px[14] 配置锁定</td></tr><tr><td>[13]</td><td>PLCKR13</td><td>GPIO x[13] / Px[13] 配置锁定</td></tr><tr><td>[12]</td><td>PLCKR12</td><td>GPIO x[12] / Px[12] 配置锁定</td></tr><tr><td>[11]</td><td>PLCKR11</td><td>GPIO x[11] / Px[11] 配置锁定</td></tr><tr><td>[10]</td><td>PLCKR10</td><td>GPIO x[10] / Px[10] 配置锁定</td></tr><tr><td>[9]</td><td>PLCKR9</td><td>GPIO x[9] / Px[9] 配置锁定</td></tr><tr><td>[8]</td><td>PLCKR8</td><td>GPIO x[8] / Px[8] 配置锁定</td></tr><tr><td>[7]</td><td>PLCKR7</td><td>GPIO x[7] / Px[7] 配置锁定</td></tr><tr><td>[6]</td><td>PLCKR6</td><td>GPIO x[6] / Px[6] 配置锁定</td></tr><tr><td>[5]</td><td>PLCKR5</td><td>GPIO x[5] / Px[5] 配置锁定</td></tr><tr><td>[4]</td><td>PLCKR4</td><td>GPIO x[4] / Px[4] 配置锁定</td></tr><tr><td>[3]</td><td>PLCKR3</td><td>GPIO x[3] / Px[3] 配置锁定</td></tr><tr><td>[2]</td><td>PLCKR2</td><td>GPIO x[2] / Px[2] 配置锁定</td></tr><tr><td>[1]</td><td>PLCKR1</td><td>GPIO x[1] / Px[1] 配置锁定</td></tr><tr><td>[0]</td><td>PLCKR0</td><td>GPIO x[0] / Px[0] 配置锁定</td></tr></table>

配置保护，高有效；有效时 GPIO 输入/输出/上下拉/开漏/功能选择不能被修改；需要注意，只有在 LCKR_PRT 写保护打开时才能改写 LCKR。

# 8.2.9 GPIOx_F3210

地址分别是：0x4001_2020，0x4001_2060，0x4001_20A0，0x4001_20E0

复位值：0x0

表8-10GPIOx功能选择寄存器GPIOxF3210  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>F3</td><td></td><td></td><td>F2</td><td></td><td></td><td></td><td>F1</td><td></td><td></td><td>F0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td>RW</td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td></td><td></td><td>0</td><td></td><td></td><td></td><td>0</td><td></td><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:12]</td><td>F3</td><td>GPIO x[3] / Px[3] 功能选择</td></tr><tr><td>[11:8]</td><td>F2</td><td>GPIO x[2] / Px[2] 功能选择</td></tr><tr><td>[7:4]</td><td>F1</td><td>GPIO x[1] / Px[1] 功能选择</td></tr><tr><td>[3:0]</td><td>F0</td><td>GPIO x[0] / Px[0] 功能选择</td></tr></table>

GPIO 引脚功能复用如表 8- 11 所示。

表8-11GPIO功能复用  

<table><tr><td>GPIOx_Fxxxx 配置值</td><td>第二功能代号</td><td>功能</td></tr><tr><td>0x0</td><td>AF0</td><td>模拟功能</td></tr><tr><td>0x1</td><td>AF1</td><td>SYS_AF，比较器及时钟等数字信号输出功能</td></tr><tr><td>0x2</td><td>AF2</td><td>HALL</td></tr><tr><td>0x3</td><td>AF3</td><td>MCPWM</td></tr><tr><td>0x4</td><td>AF4</td><td>UART</td></tr><tr><td>0x5</td><td>AF5</td><td>SPI</td></tr><tr><td>0x6</td><td>AF6</td><td>HC</td></tr><tr><td>0x7</td><td>AF7</td><td>Timer0/Time1</td></tr><tr><td>0x8</td><td>AF8</td><td>Timer2/ TimeC3/QEP0/QEP1</td></tr><tr><td>0x9</td><td>AF9</td><td>ADC trigger debug</td></tr><tr><td>0xA</td><td>AF10</td><td>CAN</td></tr><tr><td>0xB</td><td>AF11</td><td>SIF</td></tr></table>

# 8.2.10 GPIOx_F7654

地址分别是：0x4001_2024，0x4001_2064，0x4001_20A4，0x4001_20E4

复位值：0x0

表8-12GPIOx功能选择寄存器GPIOxF7654  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>F7</td><td></td><td></td><td></td><td>F6</td><td></td><td></td><td>F5</td><td></td><td></td><td>F4</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td></td><td></td><td></td><td>RW</td><td></td><td></td><td>RW</td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td></td><td></td><td></td><td>0</td><td></td><td></td><td>0</td><td></td><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:12]</td><td>F7</td><td>GPIO x[7] / Px[7] 功能选择</td></tr><tr><td>[11:8]</td><td>F6</td><td>GPIO x[6] / Px[6] 功能选择</td></tr><tr><td>[7:4]</td><td>F5</td><td>GPIO x[5] / Px[5] 功能选择</td></tr><tr><td>[3:0]</td><td>F4</td><td>GPIO x[4] / Px[4] 功能选择</td></tr></table>

# 8.2.11 GPIOx_FBA98

地址分别是：0x4001_2028，0x4001_2068，0x4001_20A8，0x4001_20E8

复位值：0x0

表8-13GPIOx功能选择寄存器GPIOxFBA98  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>F11</td><td></td><td></td><td></td><td>F10</td><td></td><td></td><td>F9</td><td></td><td></td><td>F8</td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:12]</td><td>F11</td><td>GPIO x[11] / Px[11] 功能选择</td></tr><tr><td>[11:8]</td><td>F10</td><td>GPIO x[10] / Px[10] 功能选择</td></tr><tr><td>[7:4]</td><td>F9</td><td>GPIO x[9] / Px[9] 功能选择</td></tr><tr><td>[3:0]</td><td>F8</td><td>GPIO x[8] / Px[8] 功能选择</td></tr></table>

# 8.2.12 GPIOxFFEDC

地址分别是：0x4001_202C，0x4001_206C，0x4001_20AC，0x4001_20EC

复位值：0x0

表8-14GPIOx功能选择寄存器GPIOxFFEDC  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>F15</td><td></td><td></td><td>F14</td><td></td><td></td><td></td><td>F13</td><td></td><td></td><td></td><td></td><td>F12</td><td></td><td></td><td></td></tr><tr><td>RW</td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td></td><td>RW</td><td></td><td></td><td></td></tr><tr><td>0</td><td></td><td></td><td>0</td><td></td><td></td><td></td><td>0</td><td></td><td></td><td></td><td></td><td>0</td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:12]</td><td>F15</td><td>GPIO x[15] / Px[15] 功能选择</td></tr><tr><td>[11:8]</td><td>F14</td><td>GPIO x[14] / Px[14] 功能选择</td></tr><tr><td>[7:4]</td><td>F13</td><td>GPIO x[13] / Px[13] 功能选择</td></tr><tr><td>[3:0]</td><td>F12</td><td>GPIO x[12] / Px[12] 功能选择</td></tr></table>

GPIO的功能复用详细列表请见对应产品DATASHEET管脚分布章节。

# 8.2.13 外部中断、唤醒、锁定保护

P0.0/P0.1/P1.0/P1.1.4个GPIO可以作为系统的唤醒源。P0.15～P0.0共16个GPIO可以用作外部中断源输入。唤醒功能和外部中断功能使用的是IO的GPIO功能。GPIO第二功能可以配置为0。

# 8.2.13.1 EXTLCR0

地址：0x4001_2100

复位值：0x0

表8-15外部中断配置寄存器EXTI_CR0  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>T7</td><td>T6</td><td></td><td>T5</td><td></td><td>T4</td><td></td><td>T3</td><td></td><td>T2</td><td></td><td>T1</td><td></td><td>T0</td><td></td><td></td></tr><tr><td>RW</td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td></td></tr><tr><td>0</td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:14]</td><td>T7</td><td>GPIO 0[7]/P0[7]外部中断触发类型选择
00:不触发
01:下降沿触发
10:上升沿触发
11:上升沿、下降沿均触发</td></tr><tr><td>[13:12]</td><td>T6</td><td>GPIO 0[6]/P0[6]外部中断触发类型选择
00:不触发
01:下降沿触发
10:上升沿触发
11:上升沿、下降沿均触发</td></tr><tr><td>[11:10]</td><td>T5</td><td>GPIO 0[5]/P0[5]外部中断触发类型选择
00:不触发
01:下降沿触发
10:上升沿触发
11:上升沿、下降沿均触发</td></tr><tr><td>[9:8]</td><td>T4</td><td>GPIO 0[4]/P0[4]外部中断触发类型选择
00:不触发
01:下降沿触发
10:上升沿触发
11:上升沿、下降沿均触发</td></tr><tr><td>[7:6]</td><td>T3</td><td>GPIO 0[3]/P0[3]外部中断触发类型选择
00:不触发
01:下降沿触发
10:上升沿触发
11:上升沿、下降沿均触发</td></tr><tr><td>[5:4]</td><td>T2</td><td>GPIO 0[2]/P0[2]外部中断触发类型选择
00:不触发
01:下降沿触发
10:上升沿触发
11:上升沿、下降沿均触发</td></tr><tr><td>[3:2]</td><td>T1</td><td>GPIO 0[1]/P0[1]外部中断触发类型选择
00:不触发
01:下降沿触发
10:上升沿触发
11:上升沿、下降沿均触发</td></tr></table>

<table><tr><td>[1:0]</td><td>T0</td><td>GPIO 0[0]/P0[0]外部中断触发类型选择
00:不触发
01:下降沿触发
10:上升沿触发
11:上升沿、下降沿均触发</td></tr></table>

# 8.2.13.2 EXTI_CR1

地址：0x4001_2104

复位值：0x0

表8-16外部中断配置寄存器EXTI_CR1  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>T15</td><td>T14</td><td>T13</td><td>T12</td><td>T11</td><td>T10</td><td>T9</td><td>T8</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:14]</td><td>T15</td><td>GPIO 0[15]/P0[15]外部中断触发类型选择
00:不触发
01:下降沿触发
10:上升沿触发
11:上升沿、下降沿均触发</td></tr><tr><td>[13:12]</td><td>T14</td><td>GPIO 0[14]/P0[14]外部中断触发类型选择
00:不触发
01:下降沿触发
10:上升沿触发
11:上升沿、下降沿均触发</td></tr><tr><td>[11:10]</td><td>T13</td><td>GPIO 0[13]/P0[13]外部中断触发类型选择
00:不触发
01:下降沿触发
10:上升沿触发
11:上升沿、下降沿均触发</td></tr><tr><td>[9:8]</td><td>T12</td><td>GPIO 0[12]/P0[12]外部中断触发类型选择
00:不触发
01:下降沿触发
10:上升沿触发
11:上升沿、下降沿均触发</td></tr><tr><td>[7:6]</td><td>T11</td><td>GPIO 0[11]/P0[11]外部中断触发类型选择
00:不触发
01:下降沿触发</td></tr></table>

<table><tr><td></td><td></td><td>10：上升沿触发
11：上升沿、下降沿均触发</td></tr><tr><td>[5:4]</td><td>T10</td><td>GPIO 0[10]/P0[10]外部中断触发类型选择
00：不触发
01：下降沿触发
10：上升沿触发
11：上升沿、下降沿均触发</td></tr><tr><td>[3:2]</td><td>T9</td><td>GPIO 0[9]/P0[9]外部中断触发类型选择
00：不触发
01：下降沿触发
10：上升沿触发
11：上升沿、下降沿均触发</td></tr><tr><td>[1:0]</td><td>T8</td><td>GPIO 0[8]/P0[8]外部中断触发类型选择
00：不触发
01：下降沿触发
10：上升沿触发
11：上升沿、下降沿均触发</td></tr></table>

# 8.2.13.3 EXTI_IF

地址：0x4001_2108

复位值：0x0

表8-17外部中断标志寄存器EXTI_IF  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>IF15</td><td>IF14</td><td>IF13</td><td>IF12</td><td>IF11</td><td>IF10</td><td>IF9</td><td>IF8</td><td>IF7</td><td>IF6</td><td>IF5</td><td>IF4</td><td>IF3</td><td>IF2</td><td>IF1</td><td>IF0</td></tr><tr><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>IF15</td><td>GPIO 0[15] / P0[15] 外部中断标志
中断标志高有效，写 1 清零</td></tr><tr><td>[14]</td><td>IF14</td><td>GPIO 0[14] / P0[14] 外部中断标志
中断标志高有效，写 1 清零</td></tr><tr><td>[13]</td><td>IF13</td><td>GPIO 0[13] / P0[13] 外部中断标志
中断标志高有效，写 1 清零</td></tr><tr><td>[12]</td><td>IF12</td><td>GPIO 0[12] / P0[12] 外部中断标志
中断标志高有效，写 1 清零</td></tr><tr><td>[11]</td><td>IF11</td><td>GPIO 0[11] / P0[11] 外部中断标志</td></tr></table>

<table><tr><td></td><td></td><td>中断标志高有效，写1清零</td></tr><tr><td>[10]</td><td>IF10</td><td>GPIO 0[10] / P0[10] 外部中断标志
中断标志高有效，写1清零</td></tr><tr><td>[9]</td><td>IF9</td><td>GPIO 0[9] / P0[9] 外部中断标志
中断标志高有效，写1清零</td></tr><tr><td>[8]</td><td>IF8</td><td>GPIO 0[8] / P0[8] 外部中断标志
中断标志高有效，写1清零</td></tr><tr><td>[7]</td><td>IF7</td><td>GPIO 0[7] / P0[7] 外部中断标志
中断标志高有效，写1清零</td></tr><tr><td>[6]</td><td>IF6</td><td>GPIO 0[6] / P0[6] 外部中断标志
中断标志高有效，写1清零</td></tr><tr><td>[5]</td><td>IF5</td><td>GPIO 0[5] / P0[5] 外部中断标志
中断标志高有效，写1清零</td></tr><tr><td>[4]</td><td>IF4</td><td>GPIO 0[4] / P0[4] 外部中断标志
中断标志高有效，写1清零</td></tr><tr><td>[3]</td><td>IF3</td><td>GPIO 0[3] / P0[3] 外部中断标志
中断标志高有效，写1清零</td></tr><tr><td>[2]</td><td>IF2</td><td>GPIO 0[2] / P0[2] 外部中断标志
中断标志高有效，写1清零</td></tr><tr><td>[1]</td><td>IF1</td><td>GPIO 0[1] / P0[1] 外部中断标志
中断标志高有效，写1清零</td></tr><tr><td>[0]</td><td>IF0</td><td>GPIO 0[0] / P0[0] 外部中断标志
中断标志高有效，写1清零</td></tr></table>

# 8.2.13.4 LCKR_PRT

地址：0x4001_210C

复位值：0x0

表8-18锁定保护寄存器LCKR_PRT  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">PRT</td><td></td></tr><tr><td colspan="15">WO</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>PRT</td><td>配置锁定写保护；写入 0x5AC4 关闭写保护，然后才能修改 GPIO_LCKR；写入任意其他数据开启写保护；B[0]状态指示当前写保护与否，高电平表示处于写保护，低电平表示处于非写保护。</td></tr></table>

# 8.2.13.5 WAKE_POL

地址：0x4001_2110

复位值：0x0

表8-19外部唤醒源极性配置寄存器WAKE_POL  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:4]</td><td></td><td>未使用</td></tr><tr><td>[3]</td><td>GPIO1_1_POL</td><td>GPIO 1[1] / P1[1]外部唤醒触发电平选择
1：高电平；0：低电平</td></tr><tr><td>[2]</td><td>GPIO1_0_POL</td><td>GPIO 1[0] / P1[0]外部唤醒触发电平选择
1：高电平；0：低电平</td></tr><tr><td>[1]</td><td>GPIO0_1_POL</td><td>GPIO 0[1] / P0[1]外部唤醒触发电平选择
1：高电平；0：低电平</td></tr><tr><td>[0]</td><td>GPIO0_0_POL</td><td>GPIO 0[0] / P0[0]外部唤醒触发电平选择
1：高电平；0：低电平</td></tr></table>

# 8.2.13.6 WAKE_EN

地址：0x4001_2114

复位值：0x0

表8-20外部唤醒源使能寄存器WAKE_EN  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td>GPIO1_1_WKEN</td><td>GPIO1_0_WKEN</td><td>GPIO0_1_WKEN</td><td>GPIO0_0_WKEN</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:4]</td><td></td><td>未使用</td></tr><tr><td>[3]</td><td>GPIO1_1_WKEN</td><td>GPIO 1[1] / P1[1] 外部唤醒使能
1：使能；0：禁用。</td></tr><tr><td>[2]</td><td>GPIO1_0_WKEN</td><td>GPIO 1[0] / P1[0] 外部唤醒使能
1：使能；0：禁用。</td></tr><tr><td>[1]</td><td>GPIO0_1_WKEN</td><td>GPIO 0[1] / P0[1] 外部唤醒使能
1：使能；0：禁用。</td></tr></table>

<table><tr><td>[0]</td><td>GPIO0_0_WKEN</td><td>GPIO 0[0] / P0[0] 外部唤醒使能
1：使能；0：禁用。</td></tr></table>

# 8.3 实现说明

# 8.3.1 上拉实现

LKS32MC08x系列芯片，通过内部模拟电路进行上拉功能实现。所有GPIO都有上拉控制寄存器PUE，但不是所有GPIO都有上拉电路。配备上拉功能的GPIO如下：

表8-21GPIO上拉资源分布表  

<table><tr><td></td><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>P0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>√</td><td>√</td><td></td><td></td><td></td><td></td><td></td><td>√</td><td></td></tr><tr><td>P1</td><td></td><td></td><td></td><td></td><td>√</td><td>√</td><td></td><td></td><td></td><td></td><td></td><td>√</td><td></td><td></td><td>√</td><td></td></tr><tr><td>P2</td><td></td><td></td><td></td><td></td><td></td><td>√</td><td></td><td>√</td><td>√</td><td>√</td><td>√</td><td></td><td></td><td>√</td><td></td><td></td></tr><tr><td>P3</td><td></td><td></td><td></td><td></td><td></td><td></td><td>√</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

# 8.4 应用指南

# 8.4.1 配置锁定

芯片提供对GPIO配置的保护功能。当LCKR_PRT写保护使能时，3组GPIO的GPIO_LCKR不能修改，GPIO_PIE/GPIO_PIOE/GPIO_PUE/GPIO_PDE/GPIO_ODE/GPIO_F3210/GPIO_F7654/GPIO_FBA98/GPIO_FFEDC不能修改；

若需要修改GPIO配置，应先解除LCKR_PRT写保护，然后将对应GPIO的GPIO_LCKR写0，解除配置锁定，然后修改GPIO配置。

示例如下：

GPIO0_PIE  $= 0\mathrm{x}1234$  GPIO1_PIE  $= 0\mathrm{x}7777$  GPIO2_PIE  $= 0\mathrm{x}\mathrm{F}000$  // // lock specific gpio GPIO0_LCKR  $= 0\mathrm{x}0100$  //lock gpio0 here GPIO1_LCKR  $= 0\mathrm{x}\mathrm{F}\mathrm{F}\mathrm{F}\mathrm{F}$  //lock gpio1 here GPIO2_LCKR  $= 0\mathrm{x}8000$  //lock gpio2 here

// modify to test if gpio config is lockedGPI00_PIE = 0x3333;GPI01_PIE = 0x0000;GPI02_PIE = 0x0000;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// read gpio config to flag PASS or FAIL

if(GPIO0_PIE != 0x3233)FAIL;if(GPIO1_PIE != 0x7777)FAIL;if(GPIO2_PIE != 0x8000)FAIL;

LCKR_PRT = 0x0000; // write any value other than 0x5AC4 to enable lock protectGPI00_LCKR = 0x0000;GPI01_LCKR = 0x0000;GPI02_LCKR = 0x0000;

if(GPIO0_LCKR != 0x0100)FAIL;if(GPIO1_LCKR != 0xFFFF)FAIL;if(GPIO2_LCKR != 0x8000)FAIL;

LCKR_PRT = 0x5AC4; // disable protectGPI00_LCKR = 0x0000;GPI01_LCKR = 0x0000;GPI02_LCKR = 0x0000;

if(GPIO0_LCKR != 0x0000)FAIL;if(GPIO1_LCKR != 0x0000)FAIL;if(GPIO2_LCKR != 0x0000)FAIL;

$i = 1000$

while(i- - ); PASS;

# 8.4.2 外部中断

示例如下：

GPI00 PIE  $=$  0x0080; //使能P0[7]输入NVIC_EnableIRQ(GPIO_IRQn);//使能GPIO中断_enable_irqO; //使能中断 $\mathrm{i} = 1000$  while(i- - );//P0[7]IO上外接方波信号EXTI  $\mathsf{CR0} = 0\mathbf{x}8000$  ；//使能p0[7]上升沿触发，产生外部中断while(irq_flag  $! = 2$  ；//外部信号翻转两次，产生两次中断，irq_flag在GPIO中断处理程序中递增两次EXTI  $\mathsf{CR0} = 0\mathbf{x}4000$  ；//使能p0[7]下降沿触发，产生外部中断while(irq_flag  $! = 4$  ；EXTI  $\mathsf{CR0} = 0\mathbf{x}C000$  ；//同时使能P0[7]上升沿、下降沿触发，产生外部中断while(irq_flag  $! = 8$  ；EXTI  $\mathsf{CR0} = 0\mathbf{x}0000$  ；//同时禁用P[7]上下沿触发，将无法产生外部中断 $\mathrm{i} = 1000$  while(i- - );if(irq_flag  $! = 8$  )FAIL; $\mathrm{i} = 1000$  while(i- - );PASS;

# 8.4.3 使用GPIO的模拟功能

将GPIO的IE和OE关闭，即可使用模拟功能。此时，PAD通过内部电阻直接与模拟模块相连。

# 9 CRC

# 9.1 概述

CRC即循环冗余校验码（CyclicRedundancyCheck）：是数据通信领域中最常用的一种查错校验码，其特征是信息字段和校验字段的长度可以任意选定。循环冗余检查（CRC）是一种数据传输检错功能，对数据进行多项式计算，并将得到的结果附在帧的后面，接收设备也执行类似的算法，以保证数据传输的正确性和完整性。

利用CRC进行检错的过程可简单描述为：在发送端根据要传送的K位二进制码序列，以一定的规则产生一个校验用的R位监督码(CRC码)，附在原始信息后边，构成一个新的二进制码序列数共 $\mathrm{K} + \mathrm{R}$  位，然后发送出去。在接收端，根据信息码和CRC码之间所遵循的规则进行检验，以确定传送中是否出错。这个规则，在差错控制理论中称为"生成多项式”。

# 9.2 基本原理

循环冗余校验码（CRC）的基本原理是：在K位信息码后再拼接R位的校验码，整个编码长度为N位，因此，这种编码也叫（N，K）码。对于一个给定的（N，K）码，可以证明存在一个最高次幂为  $\mathrm{N - K = R}$  的多项式  $\mathbf{G}(\mathbf{x})$  。根据  $\mathbf{G}(\mathbf{x})$  可以生成K位信息的校验码，而  $\mathbf{G}(\mathbf{x})$  叫做这个CRC码的生成多项式。校验码的具体生成过程为：假设要发送的信息用多项式  $\mathbf{C}(\mathbf{X})$  表示，将  $\mathbf{C}(\mathbf{x})$  左移R位（可表示成  $\mathbf{C}(\mathbf{x})^{*}2^{\mathbb{R}}$  ，这样  $\mathbf{C}(\mathbf{x})$  的右边就会空出R位，这就是校验码的位置。用  $\mathbf{C}(\mathbf{x})^{*}2^{\mathbb{R}}$  除以生成多项式  $\mathbf{G}(\mathbf{x})$  得到的余数就是校验码。

任意一个由二进制位串组成的代码都可以和一个系数仅为  $^{\prime}0^{\prime}$  和'1'取值的多项式一一对应。例如：代码1010111对应的多项式为  $\mathbf{x}^6 +\mathbf{x}^4 +\mathbf{x}^2 +\mathbf{x} + 1$  ，而多项式为  $\mathbf{x}^5 +\mathbf{x}^3 +\mathbf{x}^2 +\mathbf{x} + 1$  对应的代码101111。

# 9.3 基本概念

# 9.3.1 对应关系

多项式和二进制数有直接对应关系：X的最高幂次对应二进制数的最高位，以下各位对应多项式的各幂次，有此幂次项对应1，无此幂次项对应0。可以看出：X的最高幂次为R，转换成对应的二进制数有  $\mathbb{R} + 1$  位。

多项式包括生成多项式G(X)和信息多项式C(X)。

如生成多项式为  $\scriptstyle \mathrm{G(X) = X^4 + X^3 + X + 1}$  ，可转换为二进制数码11011。

而发送信息为101111，可转换为数据多项式为  $\scriptstyle \mathrm{C(X) = X^5 + X^3 + X^2 + X + 1}$  0

# 9.3.2 生成多项式

生成多项式是接受方和发送方的一个约定，也就是一个二进制数，在整个传输过程中，这个数始终保持不变。

在发送方，利用生成多项式对信息多项式做模2除生成校验码。在接收方利用生成多项式对收到的编码多项式做模2除检测和确定错误位置。

应满足以下条件：

A、生成多项式的最高位和最低位必须为1。B、当被传送信息（CRC码）任何一位发生错误时，被生成多项式做除后应该使余数不为0。C、不同位发生错误时，应该使余数不同。D、对余数继续做除，应使余数循环。

# 9.3.3 校验码位数

CRC校验码位数  $=$  生成多项式位数- 1。注意有些生成多项式的简记式中将生成多项式的最高位1省略了。

# 9.3.4 生成步骤

1、将X的最高次幂为R的生成多项式G(X)转换成对应的  $\mathbb{R} + 1$  位二进制数。

2、将信息码左移R位，相当于对应的信息多项式  $\mathbb{C}(\mathbf{X})^{*}2\mathbb{R}$

3、用生成多项式（二进制数）对信息码做除，得到R位的余数(注意：这里的二进制做除法得到的余数其实是模2除法得到的余数，并不等于其对应十进制数做除法得到的余数。)。

4、将余数拼到信息码左移后空出的位置，得到完整的CRC码。

【例】假设使用的生成多项式是  $\scriptstyle \mathrm{G(X) = X3 + X + 1}$  。4位的原始报文为1010，求编码后的报文。解：

1、将生成多项式  $\scriptstyle \mathrm{G(X) = X3 + X + 1}$  转换成对应的二进制除数1011。

2、此题生成多项式有4位（  $\mathbb{R} + 1$  ）(注意：4位的生成多项式计算所得的校验码为3位，R为校验码位数)，要把原始报文C(X)左移3（R）位变成1010000

3、用生成多项式对应的二进制数对左移3位后的原始报文进行模2除（高位对齐)，相当于按位异或：

1010000

1011

0001000

0001011

0000011

得到的余位011，所以最终编码为：1010011

POL=0x13，data=0x77

011101110000000

10010011

01111101000000

10010011

0110100100000

10010011

010000010000

10010011

00010001000

10010011

00011011

# 9.4 寄存器

# 9.4.1 地址分配

CRC的基地址是0x4001_2400，寄存器列表如下：

表9-1CRC寄存器列表  

<table><tr><td>名称</td><td>偏移地址</td><td>说明</td></tr><tr><td>CRC_DR</td><td>0x00</td><td>CRC 数据（输入信息码/输出编码）寄存器</td></tr><tr><td>CRC_CR</td><td>0x04</td><td>CRC 控制寄存器</td></tr><tr><td>CRC_INIT</td><td>0x08</td><td>CRC 初始码寄存器</td></tr><tr><td>CRC_POL</td><td>0x0C</td><td>CRC 生成多项式对应的二进制码寄存器</td></tr></table>

# 9.4.2 寄存器描述

9.4.2.1 CRC_DR CRC 信息码寄存器

地址：0x4001_2400复位值：0x0

<table><tr><td colspan="68">表9-2 CRC 数据寄存器 CRC_DR</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="34">DR</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="34">RW</td><td colspan="66"></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>DR</td><td>存放待编码的信息码和经 CRC 校验后的编码</td></tr></table>

CRC_DR 寄存器既用于放入待校验数据，也用于返回校验结果。写入 CRC_DR 寄存器即触发一次 CRC 计算。待编码数据应在 CR 等寄存器配置完成后最后写入，以触发 CRC 计算开始。

# 9.4.2.2 CRC_CR CRC 控制寄存器

地址：0x4001_2404

复位值：0x0

表9-3CRC控制寄存器CRC_CR  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td>REV_OUT_TYPE</td><td rowspan="3"></td><td rowspan="3"></td><td>REV_IN_TYPE</td><td rowspan="3"></td><td rowspan="3"></td><td>POLY_SIZE</td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td>RESET</td><td></td><td></td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>WO</td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12]</td><td>REV_OUT_TYPE</td><td>是否将 CRC 校验后的编码反转后输出，即 b[31]=b[0], b[30]=b[1],...[b0]=b[31]</td></tr><tr><td>[11:10]</td><td></td><td>未使用</td></tr><tr><td>[9:8]</td><td>REV_IN_TYPE</td><td>待编码数据反转类型
00:不反转</td></tr></table>

<table><tr><td></td><td></td><td>01:按字节反转，即 b[31]=b[24], b[30]=b[25], ..., b[24]=b[31], ..., b[7]=b[0], b[6]=b[1], ..., b[0]=b[7]
10:按半字（16bit）反转，即 b[31]=b[16], b[30]=b[17], ..., b[16]=b[31], ..., b[15]=b[0], b[14]=b[1], ..., b[0]=b[15]
11:按字反转，即 b[31]=b[0], b[30]=b[1], ..., b[0]=b[31]</td></tr><tr><td>[7:6]</td><td></td><td>未使用</td></tr><tr><td>[5:4]</td><td>POLY_SIZE</td><td>输出编码（多项式）位宽
00:32bits
01:16bits
10:8bits
11:7bits</td></tr><tr><td>[3:1]</td><td></td><td>未使用</td></tr><tr><td>[0]</td><td>RESET</td><td>与输入信息码进行 CRC 计算的数据来源
0:来自于上一次的计算结果
1:来自于 CRC_INIT
写入 1 实现 CRC 数据重置并自动清零，读回恒为 0.</td></tr></table>

同时需要注意的是，向CRC_CR_RESET写入1会将CRC_INIT寄存器复位为0xFFFFFFFF。

如果需要清除CRC的计算结果，应向CRC_CR_RESET写入1，否则后续CRC计算会以之前的计算结果为初值进行。

# 9.4.2.3 CRC_INIT CRC初始码寄存器

地址：0x4001_2408

复位值：0x0

<table><tr><td colspan="68">表9-4 CRC 初始码寄存器 CRC_INIT</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="34">RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="34">0xFFFFFFFF</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="34">INIT</td><td colspan="66">RIW</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>INIT</td><td>存放初始码</td></tr></table>

CRC_DR与CRC_INIT相异或后开始进行CRC校验计算。

# 9.4.2.4 CRC_POL CRC生成码寄存器

地址：0x4001_240C

复位值：0x0

![](images/fc60031b75448706ddd26e35a6931a1aa441851958229a2c7bb04cd5a907dcf3.jpg)

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>POL</td><td>存放生成多项式对应的生成码</td></tr></table>

# 10 ADC

# 10.1概述

LKS32MC08x系列芯片集成了1个12bitSARADC，采用双路同步采样设计，可以同一个时刻采样两个通道的信号，每个采样电路对应10路输入通道，共20路。主要有以下特性：

3Msps采样及转换速率，48MHz工作频率。- 最多支持20通道选择。- 支持软件、硬件触发功能。- 可以与MCPWM、UTimer单元联动，触发指示信号ADC_TRIGGER可通过GPIO送出用于调试- 支持单段、双段、四段自定义采样序列采样，序列次数和通道号可灵活配置。- 支持连续采样模式。- 支持DMA搬移数据。- 支持ADC硬件数值比较功能，可以设置上或下阈值，达到阈值触发ADC比较中断。- 支持左对齐、右对齐模式。

ADC采样的量词含义约定：

1次采样：完成对应的一个通道的模拟信号量到数据信号量的采样转换并存储数字量至ADC_DATx寄存器；

1段采样：可能包含1次或若干次采样，若干次采样可以是相同的模拟量通道，也可以是不同的模拟量通道。采样开始通常由MCPWM、UTimer或软件进行触发，一个触发信号完成一段采样，采样完成后产生相应的段采样完成中断；以MCPWM触发的四段采样为例，每段采样3次（即完成3个模拟量的采样)，TADC[0]触发ADC开始第一段采样，第一段采样完成后ADC进入等待状态，等待TADC[1]触发事件发生；TADC[1]发生后，触发ADC开始第二段采样；同理，TADC[2]/TADC[3]分别触发第三段和第四段采样。

1轮采样：可能包含1段、2段或4段采样，每段分别由特定触发信号触发；ADC完成一轮采样后回归空闲状态等待下次触发。

# 10.1.1 功能框图

ADC接口包括20个数据寄存器（ADC20次采样各个通道模拟量对应的数字量)，以及若干控制寄存器。

ADC配备双采样电路，同一时刻进行两个通道的采样，然后依次先后完成到数字量的转换。

数据寄存器ADC_DATx用于存储ADC第x个采样得到的数据量。被转换的模拟信号来源由寄存器ADC_CHNx中的某5bit进行选择（详见9.2.3信号来源寄存器章节)。以ADC_CHN0为例，位[4:0]选择第0个采样的模拟通道号，通道号CH0\~CH19任选，若ADC_CHN0[4:0]=0,ADC_CHN0[12:8]=3，

则第0个采样的模拟量对应通道CH0，第1个采样的模拟量对应通道CH3，以此类推。注意，由于双采样电路同步工作，因此第0个采样和第1个采样实际是同时完成的，即采样电路一次就消费ADC_CHNx选择的两个模拟通道。

分段采样次数寄存器ADC_CHNTO/1控制每轮采样的个数，1表示1个采样，2表示2个采样，，12表示12个采样，，20表示20个采样。双采样电路一次完成两个采样，如果配置的采样个数是奇数，则最后一次仅完成一个采样的模拟信号的转换。

控制逻辑根据触发配置寄存器ADC_TRIG选择来自MCPWM或通用定时器UTimer的触发信号启动一轮采样或者软件触发启动。MCPWM/UTimer会送出定时触发信号TADC[0]/TADC[1]/TADC[2]/TADC[3]，可选择TADC[0]/TADC[1]/TADC[2]/TADC[3]作为触发信号。

一段转换（一段内的所有通道采样转换完毕)完成，触发ADC转换完成中断。多段触发模式下，每一段转换完成可触发产生一个转换完成中断。

![](images/1d46f714d8c0834e52d69201ba4b78d6bd98029ecfa1f9f8b500da2a97b2a481.jpg)  
图10-1ADC采集模块功能框图

用户可以灵活配置采样顺序、以及采样信号来源，甚至实现对单个信号多次采样。同时每个通道的ADC增益也可以通过寄存器配置（两档增益可选)。控制寄存器使得用户可以配置采样个数，提高采样频率或降低采样功耗。

芯片上电的默认状态下，ADC模块是关闭的。通过将SYS_AFE_REG5. ADCPDN设置为1来开启ADC,ADC开启前，需要先开启BGP、4MRC时钟和PLL模块，并通过配置SYS_AFE_REG7. ADCCLKSEL选择ADC工作频率。

ADCPDN的说明见模拟寄存器5.2.9SYSAFE REG5

# ADCCLKSEL  $< 1:0>$  的说明见模拟寄存器5.2.11SYSAFE_REG7

ADC完成一次转换需要16个ADC时钟周期，其中13个为转换周期，3个为采样周期。在ADC时钟设为48MHz时，转换速率是3Msps。

# 10.1.2 ADC触发方式

支持单段触发、两段触发、四段触发完成采样单段触发可以设置触发事件发生次数，当触发事件发生一定次数后才开始采样两段触发的触发源只能为MCPWM/UTimer的定时信号  $\mathrm{T0 + T1}$  ，或两次软件触发四段触发的触发源只能为MCPWM/UTimer的定时信号  $\mathrm{T0 + T1 + T2 + T3}$  ，或四次软件触发每段触发完成均可配置产生中断触发指示信号可以通过GPIO送出用于调试

表10-1ADC分段触发方式触发源配置  

<table><tr><td>分段触发方式</td><td>当前段</td><td colspan="3">可能的触发源</td></tr><tr><td></td><td></td><td>MCPWM</td><td>UTIMER</td><td>软件触发</td></tr><tr><td>单段触发</td><td>-</td><td>N次T0
或N次T1
或N次T2
或N次T3</td><td>N次T0
或N次T1
或N次T2
或N次T3</td><td>一次软件触发</td></tr><tr><td rowspan="2">两段触发</td><td>第一段</td><td>T0</td><td>T0</td><td>软件触发</td></tr><tr><td>第二段</td><td>T1</td><td>T1</td><td>软件触发</td></tr><tr><td rowspan="4">四段触发</td><td>第一段</td><td>T0</td><td>T0</td><td>软件触发</td></tr><tr><td>第二段</td><td>T1</td><td>T1</td><td>软件触发</td></tr><tr><td>第三段</td><td>T2</td><td>T2</td><td>软件触发</td></tr><tr><td>第四段</td><td>T3</td><td>T3</td><td>软件触发</td></tr></table>

其中N=ADC_TRIG.SINGLE_TNCT。可以同时开启MCPWM和UTIMER的触发使能，但由于时序控制的原因，通常不进行这样的配置。

各段采样的个数由ADC_CHNTO/1进行控制。（1表示1个采样，2表示2个采样，，12表示12个采样)。

表10-2四段触发分段采样通道数示例  

<table><tr><td>第n段</td><td>ADC_CHNTO/1</td><td>寄存器值</td><td>当前段采样个数</td></tr><tr><td>1</td><td>ADC_CHNTO[4:0]</td><td>4</td><td>4</td></tr><tr><td>2</td><td>ADC_CHNTO[12:8]</td><td>1</td><td>1</td></tr><tr><td>3</td><td>ADC_CHNT1[4:0]</td><td>6</td><td>6</td></tr><tr><td>4</td><td>ADC_CHNT1[12:8]</td><td>1</td><td>1</td></tr></table>

# 10.1.3 ADC通道选择

每个ADC模块有10个通道信号来源寄存器，控制采样序列  $0\sim 19$  的信号选择。ADC_CHN0控

制采样  $0\sim 1$  ，ADC_CHN1控制采样  $2\sim 3$  ，...，ADC_CHN9控制序列  $18\sim 19$  。每个序列选择范围都是  $0\sim 19$  ，对应通道  $0\sim 19$  ，也就是可以对某一个通道进行多次采样。每一个采样对应一个结果寄存器，转换结束后，可以直接到对应结果寄存器中获取到ADC采样结果。

表10-3ADC通道选择与寄存器配置对应关系  

<table><tr><td>ADC 采样序列</td><td>对应的采样数据寄存器</td><td>对应信号来源寄存器</td></tr><tr><td>第 0 个采样</td><td>ADC_DAT0</td><td>ADC_CHN0[4:0]</td></tr><tr><td>第 1 个采样</td><td>ADC_DAT1</td><td>ADC_CHN0[12:8]</td></tr><tr><td>第 2 个采样</td><td>ADC_DAT2</td><td>ADC_CHN1[4:0]</td></tr><tr><td>第 3 个采样</td><td>ADC_DAT3</td><td>ADC_CHN1[12:8]</td></tr><tr><td colspan="3">......</td></tr><tr><td>第 18 个采样</td><td>ADC_DAT18</td><td>ADC_CHN9[4:0]</td></tr><tr><td>第 19 个采样</td><td>ADC_DAT19</td><td>ADC_CHN9[12:8]</td></tr></table>

# 10.1.4 ADC中断

ADC中断信号在每段采样完成后置高。

软件或硬件触发事件如果在ADC工作时发生，则产生异常触发中断

ADC_DAT0具备阈值中断，阈值可以设置为上阈值/下阈值，通过ADC_CFG[1]设置，当ADC_DAT0超过ADC_DAT0_TH时发生中断。

![](images/1cccd2ae76f4fd2d2ab96d9ce7cb3db8c198c63bff3e9fad0dfc888e37f883b9.jpg)  
图10-2ADC中断产生

# 10.1.5 ADC输出数制

ADC输出数据为12bit补码，输入信号0对应12h'0000_0000_0000，以1倍增益配置为例，输入信号- 2.4V对应12h'1000_0000_0000，输入信号  $+2.4\mathrm{V}$  对应12h'0111_1111_1111。ADC转换后的12bit补码需扩展为16BIT存入16bit位宽的采样数据寄存器，左对齐/右对齐可根据配置寄存器进行设置。以12'h1000_0000_1101为例，如果配置为左对齐，右侧补4个0，存入ADCx_DAT的值为16'h1000_0000_1101_0000；如果配置为右对齐，左侧进行符号扩展，存入ADCx_DAT的值为16'h1111_1000_0000_1101。推荐统一使用左对齐方式。但由于ADC存在增益校正系数，在增益校正值不为1(0x200)时，左对齐后4位可能不为全0。

需要注意的是，由于存在增益校正和直流偏置校正，ADC最终数据可能会超过12bit有符号数的表示范围，比如在右对齐的模式下，ADC某次转换的数字量可能为0xF745，此时直接进行低12bit

的截取取出  $0 \times 745$ ，会使得负数被作为正数处理，即发生溢出错误。亦或者ADC某次转换的数字量可能为  $0 \times 0810$ ，此时直接进行低12bit的截取取出  $0 \times 810$ ，会使得正数被错误地当做负数处理。因此需要将ADC数据作为16bit有符号数进行处理。

表10-4ADC输出数字量数制转换  

<table><tr><td>ADC一倍增益输入模拟量数值/V</td><td>ADC 2/3 倍增益输入模拟量数值/V</td><td>转为有符号数后的数值</td></tr><tr><td>2.4</td><td>3.6</td><td>12&#x27;h0111_1111_1111</td></tr><tr><td>0</td><td>0</td><td>12&#x27;h0000_0000_0000</td></tr><tr><td>-2.4</td><td>-3.6</td><td>12&#x27;h1000_0000_0000</td></tr></table>

![](images/dc5680444e83226534806203d00cac57b452f9ceb5d90f3eaa07f73260c0f807.jpg)  
图10-3一倍增益设置下ADC模数转换数制量程

# 10.1.6 ADC基准电压与量程

ADC有2.4V/1.2V两种基准电压配置，通过设置SYS_AFE_REG1. GAIN_REF位实现选择，详见5.2.5。

# 10.1.6.12.4V基准电压模式

芯片工作在5V系统时，推荐使用2.4V的默认基准电压配置，此时ADC正常工作的最低供电电压为3.2V。

ADC有两种增益模式：高增益（1倍）和低增益（2/3倍），针对这两种增益，ADC的量程也相应有所区别。1倍增益模式下，对应最大  $\pm 2.4V$  的输入信号幅度，2/3倍增益模式下，对应最大  $\pm 3.6V$  的输入信号幅度。

在ADC采样通道配置为运放的输出信号时（即OPA0~OPA3），应选择合适的运放增益，使得具体应用上的最大信号可被放大到接近  $+ / - 3.3V$  的水平，同时将ADC配置为2/3倍增益。举例来说，相线电流最大100A（正弦波有效值），MOS内阻（假设为MOS内阻采样）为  $5\mathrm{mR}$ ，则运放的最大

输入信号幅值为  $+ / - 707\mathrm{mV}$  。此时应该选择运放的放大倍数为4.5倍（放大倍数选择方式详见4.60PA运算放大器），则放大后的信号约为  $+ / - 3.18\mathrm{V}$  。

如果因为客观原因，运放的输出信号经放大后，最大信号仍然小于  $+ / - 2.4\mathrm{V}$ ，则应将ADC的增益配置为1倍。

在ADC采样通道配置为GPIO复用口输入的信号时，同样根据信号的最大幅度来选择ADC增益。由于IO口的限制，GPIO复用口输入的信号范围只能在  $- 0.3\mathrm{V} \sim \mathrm{AVDD} + 0.3\mathrm{V}$  之间。

高低增益选择由ADC_GAIN0/1增益寄存器进行控制。

# 10.1.6.2 1.2V基准电压模式

芯片工作在3.3V系统时，必须使用1.2V的默认基准电压配置，此时ADC正常工作的最低供电电压为  $2.8\mathrm{V}$  。通过设置SYS_AFE_REG1. GAIN_REF  $\mathbf{\omega} = \mathbf{\omega}^{\prime}\mathbf{1}^{\prime}$  将ADC配置为1.2V基准电压模式。这一模式下相比2.4V模式，ADC的有效精度(ENOB)基本不变。

这一模式和2.4V模式的区别在于：

1）对于最常用的ADC2/3倍增益设置（对应  $+ / - 3.6\mathrm{V}$  量程），没有任何影响。芯片会自动调整增益为1/3，因此同一个信号的ADC采样值不变，量程也不变。

2）对于ADC1倍增益设置，SYS_AFE_REG1. GAIN_REF  $\mathbf{\omega} = \mathbf{\omega}^{\prime}\mathbf{1}^{\prime}$  后，使用该性增益设置的ADC通道，其量程变为  $+ / - 1.2\mathrm{V}$ ，同一个信号对应的ADC值也会变大一倍

3）对于内部的温度传感器，ADC的增益设置不起作用。ADC采样温度传感器的转换后的数值需要除以2，再使用a/b系数计算温度。温度传感器a/b系数的描述详见4.8TMP温度传感器。由于温度系数a/b是在ADC2.4V基准电压下校正得到的，因此这种工作模式下温度精度会比2.4V基准略低，推荐使用2.4V基准。

# 10.1.7 ADC校正

ADC硬件接口模块可以进行直流偏置校正与增益校正

ADC_AMC存储的是增益校正系数  $\mathrm{AMP_{correction}}$ ，为10bit无符号定点数，ADC_AMC[9]为整数部分，ADC_AMC[8:0]为小数部分。可以表示数值在1附近的定点数。

芯片出厂时已经过工厂标定，标定数据存放在NVR中，芯片上电会自动加载。ADC模块在初始化的时候，需要根据数据左右对齐模式配置DC offset，可以参看芯片供应商提供的库函数。

需要注意的是，ADC有高增益和低增益两挡配置，两种配置对应两套校正参数，每套校正数据分别包含一个DC offset(以下记为DC offset)和一个增益校正值  $\mathrm{AMP_{correction}}$  。同时每套校正参数包含两组DC/AMC分别对应采样电路a/b。高增益对应的校正系数为ADC_DC_A1/ADC_AMC_A1和ADC_DC_B1/ADC_AMC_B1，低增益对应的校正系数为ADC_DC_A0/ADC_AMC_A0和ADC_DC_B0/ADC_AMC_B0。

记ADC输出的数字量为  $\mathrm{D_{ADC}}$ ， $\mathrm{D_{ADC}}$  对应的真实值为D， $\mathrm{D_0}$  为编码数制的0，则

$$
\mathrm{D} = (\mathrm{D_{ADC}} - \mathrm{D_0} - \mathrm{DC_{offset}})^{*}\mathrm{AMP_{correction}}
$$

最终硬件会将进行校正后的D存入相应的采样数据寄存器。ADC接口硬件电路会根据每个通道

的增益配置(ADC_GAIN0/1)来自动选择 AMPcorrection 与 DCoffset。

# 10.1.8 ADC 配置流程

推荐配置流程：

1. 打开 ADC 模拟开关，选择 ADC 工作频率通过配置寄存器 SYS_AFE_REG5_ADCPDN 可以开启 ADC，ADC 开启前，需要先开启 BGP、4M RC 时钟和 PLL 模块。通过配置寄存器 SYS_AFE_REG7_ADCCLKSEL[5:4] 设置 ADC 工作频率，00 为 48MHz，10 为 12MHz，11 为 24MHz。

2. 配置 ADC 数据输出格式

ADC 的输出格式可配置为左对齐或者右对齐，配置的是 ADC0_CFG_DATA_ALIGN 寄存器，0 为左对齐，1 为右对齐。

3. 配置 ADC 采样模式

ADC 的采样模式可配置为单段、双段、四段采样模式，配置的是 ADC0_TRIG_TRG_MODE[13:12] 寄存器，00 为单段采样模式，01 为两段采样模式，11 为四段采样模式。

4. 配置 ADC 触发事件

ADC 采样的触发事件选择，一共有 8 种采样事件可选择，配置的是 ADC0_TRIG 寄存器。单段采样模式下可以设置触发一次采样所需的事件数，配置的是 ADC0_TRIG_SINGLETCNT[11:8] 寄存器，设置范围是 0~15，0 表示一次事件即触发，15 表示 16 次事件才触发。

5. 配置 ADC 量程

ADC 的基准电压可以通过配置寄存器 SYS_AFE_REG1_GAIN_REF 进行选择，0 为 2.4V，1 为 1.2V。ADC 的两种增益模式可以通过配置 ADC_GAIN0/1 增益寄存器进行逐个通道选择，0 为低增益（2/3 倍），1 为高增益（1 倍）。

6. 配置 ADC 通道数，选择采样信号源

配置各段采样模式下，采样的通道个数，配置的是 ADC0_CHNT0、ADC0_CHNT1 寄存器，设置范围是 1~20，1 代表一个通道。ADC 的采样信号源配置，通过配置 ADC0_CHN0、ADC0_CHN1 等寄存器选择，设置范围是 0~15。

7. 配置 ADC 中断

ADC 一共有七种中断：第一段~第四段采样完成中断、软件触发发生在非空闲状态下的中断、硬件触发发生在非空闲状态下的中断、ADC0_DTA0 超阈值中断。通过配置 ADC0_IE 寄存器可以使能以上中断。即使未开启中断，中断事件仍能置位 ADC0_IE，但不会提出中断请求。

# 10.2 寄存器

# 10.2.1 地址分配

ADC在芯片中的基地址是0x4001_1400，寄存器列表如下：

表10-5ADC0寄存器列表  

<table><tr><td>名称</td><td>偏移地址</td><td>说明</td></tr><tr><td>ADC0_DAT0</td><td>0x00</td><td>ADC 第 0 个采样数据</td></tr><tr><td>ADC0_DAT1</td><td>0x04</td><td>ADC 第 1 个采样数据</td></tr><tr><td>ADC0_DAT2</td><td>0x08</td><td>ADC 第 2 个采样数据</td></tr><tr><td>ADC0_DAT3</td><td>0x0C</td><td>ADC 第 3 个采样数据</td></tr><tr><td>ADC0_DAT4</td><td>0x10</td><td>ADC 第 4 个采样数据</td></tr><tr><td>ADC0_DAT5</td><td>0x14</td><td>ADC 第 5 个采样数据</td></tr><tr><td>ADC0_DAT6</td><td>0x18</td><td>ADC 第 6 个采样数据</td></tr><tr><td>ADC0_DAT7</td><td>0x1C</td><td>ADC 第 7 个采样数据</td></tr><tr><td>ADC0_DAT8</td><td>0x20</td><td>ADC 第 8 个采样数据</td></tr><tr><td>ADC0_DAT9</td><td>0x24</td><td>ADC 第 9 个采样数据</td></tr><tr><td>ADC0_DAT10</td><td>0x29</td><td>ADC 第 10 个采样数据</td></tr><tr><td>ADC0_DAT11</td><td>0x2C</td><td>ADC 第 11 个采样数据</td></tr><tr><td>ADC0_DAT12</td><td>0x30</td><td>ADC 第 12 个采样数据</td></tr><tr><td>ADC0_DAT13</td><td>0x34</td><td>ADC 第 13 个采样数据</td></tr><tr><td>ADC0_DAT14</td><td>0x38</td><td>ADC 第 14 个采样数据</td></tr><tr><td>ADC0_DAT15</td><td>0x3C</td><td>ADC 第 15 个采样数据</td></tr><tr><td>ADC0_DAT16</td><td>0x40</td><td>ADC 第 16 个采样数据</td></tr><tr><td>ADC0_DAT17</td><td>0x44</td><td>ADC 第 7 个采样数据</td></tr><tr><td>ADC0_DAT18</td><td>0x48</td><td>ADC 第 18 个采样数据</td></tr><tr><td>ADC0_DAT19</td><td>0x4C</td><td>ADC 第 19 个采样数据</td></tr><tr><td>ADC0_CHN0</td><td>0x50</td><td>ADC 第 0~1 采样信号选择</td></tr><tr><td>ADC0_CHN1</td><td>0x54</td><td>ADC 第 2~3 采样信号选择</td></tr><tr><td>ADC0_CHN2</td><td>0x58</td><td>ADC 第 4~5 采样信号选择</td></tr><tr><td>ADC0_CHN3</td><td>0x5C</td><td>ADC 第 6~7 采样信号选择</td></tr><tr><td>ADC0_CHN4</td><td>0x60</td><td>ADC 第 8~9 采样信号选择</td></tr><tr><td>ADC0_CHN5</td><td>0x64</td><td>ADC 第 10~11 采样信号选择</td></tr><tr><td>ADC0_CHN6</td><td>0x68</td><td>ADC 第 12~13 采样信号选择</td></tr><tr><td>ADC0_CHN7</td><td>0x6C</td><td>ADC 第 14~15 采样信号选择</td></tr><tr><td>ADC0_CHN8</td><td>0x70</td><td>ADC 第 16~17 采样信号选择</td></tr><tr><td>ADC0_CHN9</td><td>0x74</td><td>ADC 第 18~19 采样信号选择</td></tr><tr><td>ADC0_CHNT0</td><td>0x78</td><td>ADC 各种触发模式下前两段采样通道数</td></tr><tr><td>ADC0_CHNT1</td><td>0x7C</td><td>ADC 各种触发模式下后两段采样通道数</td></tr><tr><td></td><td>0x80</td><td>保留</td></tr><tr><td></td><td>0x84</td><td>保留</td></tr><tr><td>ADC0_GAIN0</td><td>0x88</td><td>ADC 第 0~9 采样保持电路增益控制</td></tr></table>

<table><tr><td>ADC0_GAIN1</td><td>0x8C</td><td>ADC 第 10~19 采样保持电路增益控制</td></tr><tr><td>ADC0_DC_A0</td><td>0x90</td><td>ADC 采样保持电路 A 非 1 倍增益 DC offset</td></tr><tr><td>ADC0_DC_A1</td><td>0x94</td><td>ADC 采样保持电路 A 1 倍增益 DC offset</td></tr><tr><td>ADC0_AMC_A0</td><td>0x98</td><td>ADC 采样保持电路 A 非 1 倍增益增益校正</td></tr><tr><td>ADC0_AMC_A1</td><td>0x9C</td><td>ADC 采样保持电路 A 1 倍增益增益校正</td></tr><tr><td>ADC0_DC_B0</td><td>0xA0</td><td>ADC 采样保持电路 B 非 1 倍增益 DC offset</td></tr><tr><td>ADC0_DC_B1</td><td>0xA4</td><td>ADC 采样保持电路 B 1 倍增益 DC offset</td></tr><tr><td>ADC0_AMC_B0</td><td>0xA8</td><td>ADC 采样保持电路 B 非 1 倍增益增益校正</td></tr><tr><td>ADC0_AMC_B1</td><td>0xA C</td><td>ADC 采样保持电路 B 1 倍增益增益校正</td></tr><tr><td>ADC0_IE</td><td>0xB0</td><td>ADC 中断使能</td></tr><tr><td>ADC0_IF</td><td>0xB4</td><td>ADC 中断标志</td></tr><tr><td>ADC0_CFG</td><td>0xB8</td><td>ADC 对齐模式配置</td></tr><tr><td>ADC0_TRIG</td><td>0xBC</td><td>ADC 采样模式配置</td></tr><tr><td>ADC0 SWT</td><td>0xC0</td><td>ADC 软件触发</td></tr><tr><td>ADC0_DAT0_TH</td><td>0xC4</td><td>ADC 通道 0 阈值寄存器</td></tr></table>

# 10.2.2 采样数据寄存器

10.2.2.1 ADC0_DAT0

地址：0x4001_1400

复位值：0x0

表10-6采样数据寄存器ADC0_DAT0  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16">DATA0</td></tr><tr><td colspan="16">RW</td></tr><tr><td colspan="16">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DATA0</td><td>ADC 第 0 个采样数据</td></tr></table>

# 10.2.2.2 ADC0_DAT1

地址：0x4001_1404

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT1</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT1</td><td>ADC 第 1 个采样数据</td></tr></table>

# 10.2.2.3 ADC0_DAT2

地址：0x4001_1408

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT2</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT2</td><td>ADC 第 2 个采样数据</td></tr></table>

# 10.2.2.4 ADC0_DAT3

地址：0x4001_140C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT3</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr></table>

<table><tr><td>[15:0]</td><td>DAT3</td><td>ADC 第 3 个采样数据</td></tr></table>

# 10.2.2.5 ADC0_DAT4

地址：0x4001_1410

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT4</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DATA4</td><td>ADC 第 4 个采样数据</td></tr></table>

# 10.2.2.6 ADC0_DAT5

地址：0x4001_1414

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT5</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DATA5</td><td>ADC 第 5 个采样数据</td></tr></table>

# 10.2.2.7 ADC0_DAT6

地址：0x4001_1418

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT6</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT6</td><td>ADC 第 6 个采样数据</td></tr></table>

# 10.2.2.8 ADC0_DAT7

地址：0x4001_141C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT7</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT7</td><td>ADC 第 7 个采样数据</td></tr></table>

# 10.2.2.9 ADC0_DAT8

地址：0x4001_1420

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT8</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr></table>

<table><tr><td>[15:0]</td><td>DAT8</td><td>ADC 第 8 个采样数据</td></tr></table>

# 10.2.2.10 ADC0_DAT9

地址：0x4001_1424

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT9</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT9</td><td>ADC 第 9 个采样数据</td></tr></table>

# 10.2.2.11 ADC0_DAT10

地址：0x4001_1428

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT10</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT10</td><td>ADC 第 10 个采样数据</td></tr></table>

# 10.2.2.12 ADC0_DAT11

地址：0x4001_142C复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT11</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT11</td><td>ADC 第 11 个采样数据</td></tr></table>

# 10.2.2.13 ADC0_DAT12

地址：0x4001_1430

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT12</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT12</td><td>ADC 第 12 个采样数据</td></tr></table>

# 10.2.2.14 ADC_DAT13

地址：0x4001_1434

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT13</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr></table>

<table><tr><td>[15:0]</td><td>DAT13</td><td>ADC 第 13 个采样数据</td></tr></table>

# 10.2.2.15 ADC0_DAT14

地址：0x4001_1438

复位值：0x0

表10-20采样数据寄存器ADC0_DAT14  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT14</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT14</td><td>ADC 第 14 个采样数据</td></tr></table>

# 10.2.2.16 ADC0_DAT15

地址：0x4001_143C

复位值：0x0

表10-21采样数据寄存器ADC0_DAT15  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT15</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT15</td><td>ADC 第 15 个采样数据</td></tr></table>

# 10.2.2.17 ADC0_DAT16

地址：0x4001_1440复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT16</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT16</td><td>ADC 第 16 个采样数据</td></tr></table>

# 10.2.2.18 ADC0_DAT17

地址：0x4001_1444

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT17</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT17</td><td>ADC 第 17 个采样数据</td></tr></table>

# 10.2.2.19 ADC0_DAT18

地址：0x4001_1448

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT18</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr></table>

<table><tr><td>[15:0]</td><td>DAT18</td><td>ADC 第 18 个采样数据</td></tr></table>

# 10.2.2.20 ADC0_DAT19

地址：0x4001_144C

复位值：0x0

表10-25采样数据寄存器ADC0_DAT19  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DAT19</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT19</td><td>ADC 第 19 个采样数据</td></tr></table>

# 10.2.3 信号来源寄存器

# 10.2.3.1 ADC0_CHNO

地址：0x4001_1450

复位值：0x0

表10-26信号来源寄存器ADC0_CHNO  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td>DS1</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>DS0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12:8]</td><td>DS1</td><td>ADC 第 1 个采样信号选择</td></tr><tr><td>[7:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>DS0</td><td>ADC 第 0 个采样信号选择</td></tr></table>

ADC第0/1次采样是同步采样。

# 10.2.3.2 ADC0_CHN1

地址：0x4001_1454

复位值：0x0

表10-27信号来源寄存器ADC0_CHN1  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="6"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td colspan="4">DS2</td><td></td><td></td></tr><tr><td></td><td colspan="9">RW</td><td colspan="4">RW</td><td></td></tr><tr><td></td><td colspan="9">0</td><td colspan="4">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名
称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12:8]</td><td>DS3</td><td>ADC 第 3 个采样信号选择</td></tr><tr><td>[7:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>DS2</td><td>ADC 第 2 个采样信号选择</td></tr></table>

ADC第2/3次采样是同步采样。

# 10.2.3.3 ADC0_CHN2

地址：0x4001_1458

复位值：0x0

表10-28信号来源寄存器ADC0_CHN2  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td rowspan="2"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名
称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12:8]</td><td>DS5</td><td>ADC 第 5 个采样信号选择</td></tr><tr><td>[7:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>DS4</td><td>ADC 第 4 个采样信号选择</td></tr></table>

ADC第4/5次采样是同步采样。

# 10.2.3.4 ADC0_CHN3

地址：0x4001_145C复位值：0x0

表10-29信号来源寄存器ADC0_CHN3  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="6"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名
称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12:8]</td><td>DS7</td><td>ADC 第 7 个采样信号选择</td></tr><tr><td>[7:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>DS6</td><td>ADC 第 6 个采样信号选择</td></tr></table>

ADC第6/7次采样是同步采样。

# 10.2.3.5 ADC0_CHN4

地址：0x4001_1460

复位值：0x0

表10-30信号来源寄存器ADC0_CHN4  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td rowspan="2"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td rowspan="2"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td rowspan="2"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td rowspan="2"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名
称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12:8]</td><td>DS9</td><td>ADC 第 9 个采样信号选择</td></tr><tr><td>[7:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>DS8</td><td>ADC 第 8 个采样信号选择</td></tr></table>

ADC第8/9次采样是同步采样。

# 10.2.3.6 ADC0_CHN5

地址：0x4001_1464

复位值：0x0

表10-31信号来源寄存器ADC0_CHN5  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="6"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td colspan="4">DS10</td><td></td><td></td></tr><tr><td></td><td colspan="9">RW</td><td colspan="4">RW</td><td></td></tr><tr><td></td><td colspan="9">0</td><td colspan="4">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名
称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12:8]</td><td>DS11</td><td>ADC 第 11 个采样信号选择</td></tr><tr><td>[7:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>DS10</td><td>ADC 第 10 个采样信号选择</td></tr></table>

ADC第10/11次采样是同步采样。

# 10.2.3.7 ADC0_CHN6

地址：0x4001_1468

复位值：0x0

表10-32信号来源寄存器ADC0_CHN6  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td rowspan="2"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名
称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12:8]</td><td>DS13</td><td>ADC 第 13 个采样信号选择</td></tr><tr><td>[7:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>DS12</td><td>ADC 第 12 个采样信号选择</td></tr></table>

ADC第12/13次采样是同步采样。

# 10.2.3.8 ADC0_CHN7

地址：0x4001_146C复位值：0x0

表10-33信号来源寄存器ADC0_CHN7  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="6"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td colspan="4">DS14</td><td></td><td></td></tr><tr><td></td><td colspan="9">RW</td><td colspan="4">RW</td><td></td></tr><tr><td></td><td colspan="9">0</td><td colspan="4">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名
称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12:8]</td><td>DS15</td><td>ADC 第 15 个采样信号选择</td></tr><tr><td>[7:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>DS14</td><td>ADC 第 14 个采样信号选择</td></tr></table>

ADC第14/15次采样是同步采样。

# 10.2.3.9 ADC0_CHN8

地址：0x4001_1470

复位值：0x0

表10-34信号来源寄存器ADC0_CHN8  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td rowspan="2"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名
称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12:8]</td><td>DS17</td><td>ADC 第 17 个采样信号选择</td></tr><tr><td>[7:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>DS16</td><td>ADC 第 16 个采样信号选择</td></tr></table>

ADC第16/17次采样是同步采样。

# 10.2.3.10 ADC0_CHN9

地址：0x4001_1474

复位值：0x0

表10-35信号来源寄存器ADC0_CHN9  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="6"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td colspan="4">DS18</td><td></td><td></td></tr><tr><td></td><td colspan="9">RW</td><td colspan="4">RW</td><td></td></tr><tr><td></td><td colspan="9">0</td><td colspan="4">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名
称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12:8]</td><td>DS19</td><td>ADC 第 19 个采样信号选择</td></tr><tr><td>[7:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>DS18</td><td>ADC 第 18 个采样信号选择</td></tr></table>

ADC第18/19次采样是同步采样。

表10-36ADC采样信号通道选择  

<table><tr><td rowspan="20">ADC采样电路输入信号正端选择</td><td>5&#x27;h00</td><td>OPA0_OUT</td></tr><tr><td>5&#x27;h01</td><td>OPA1_OUT</td></tr><tr><td>5&#x27;h02</td><td>OPA2_OUT</td></tr><tr><td>5&#x27;h03</td><td>OPA3_OUT</td></tr><tr><td>5&#x27;h04</td><td>ADC_CH4</td></tr><tr><td>5&#x27;h05</td><td>ADC_CH5</td></tr><tr><td>5&#x27;h06</td><td>ADC_CH6</td></tr><tr><td>5&#x27;h07</td><td>ADC_CH7</td></tr><tr><td>5&#x27;h08</td><td>ADC_CH8</td></tr><tr><td>5&#x27;h09</td><td>ADC_CH9</td></tr><tr><td>5&#x27;h0A</td><td>ADC_CH10</td></tr><tr><td>5&#x27;h0B</td><td>ADC_CH11</td></tr><tr><td>5&#x27;h0C</td><td>ADC_CH12</td></tr><tr><td>5&#x27;h0D</td><td>ADC_CH13</td></tr><tr><td>5&#x27;h0E</td><td>ADC_CH14</td></tr><tr><td>5&#x27;h0F</td><td>ADC_CH15</td></tr><tr><td>5&#x27;h10</td><td>ADC_CH16</td></tr><tr><td>5&#x27;h11</td><td>ADC_CH17</td></tr><tr><td>5&#x27;h12</td><td>Temp</td></tr><tr><td>5&#x27;h13</td><td>VSS</td></tr></table>

ADC采样电路输入信号的负端统一接地。

以单段触发采样8个采样为例，ADC0_CHNx寄存器里设置的第0/1个采样是同步采样的，2/3是同步采样的，4/5是同步采样的，6/7是同步采样的。若设置的采样个数是奇数，则最后一次只仍同步采样两个通道，但只转换一个通道的采样值。

# 10.2.4 分段通道数寄存器

# 10.2.4.1 ADC0_CHNT0

地址：0x4001_1478

复位值：0x0

表10-37分段通道数寄存器ADC0_CHNT0  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td></td></tr><tr><td></td></tr><tr><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12:8]</td><td>S2</td><td>两段或四段采样模式下第二段采样个数</td></tr><tr><td>[7:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>S1</td><td>单段、两段或四段采样模式下第一段采样个数</td></tr></table>

注意，ADC0_CHNT0. S1在单段、两段、四段模式均不允许设置为0；ADC0_CHN0. S2在两段、四段模式下不允许设置为0，在单段模式下由于没有用到这一字段可以为0。

# 10.2.4.2 ADC0_CHNT1

地址：0x40011400_0x7C

复位值：0x0

表10-38分段通道数寄存器ADC0_CHNT1  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12:8]</td><td>S4</td><td>四段采样模式下第四段采样个数</td></tr></table>

<table><tr><td>[7:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>S3</td><td>四段采样模式下第三段采样个数</td></tr></table>

注意，ADC0_CHNT1. S3 在四段模式不允许设置为 0；ADC0_CHN1. S4 在四段模式下不允许设置为 0，在单段、两段模式下由于没有用到这两个字段可以为 0。

1 表示 1 个采样，2 表示 2 个采样，……，12 表示 12 个采样，……，20 表示 20 个采样。多次采样可以采样同一个模拟通道，也可以采样不同的模拟通道。

# 10.2.5 配置寄存器

# 10.2.5.1 ADC0_CFG

地址：0x4001_14B8

复位值：0x0

表10-39模式配置寄存器ADC0_CFG  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>FSM_RESET</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>TH_TYPE</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>DATA_ALIGN</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>RW</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:3]</td><td></td><td>未使用</td></tr><tr><td>[2]</td><td>FSM_RESET</td><td>状态机复位，软件写入后状态机回到 idle 状态，完成后自动清零</td></tr><tr><td>[1]</td><td>TH_TYPE</td><td>ADC0_DAT0_TH 作为上阈值或下阈值
1: 上阈值
0: 下阈值</td></tr><tr><td>[0]</td><td>DATA_ALIGN</td><td>ADC0_DAT 对齐方式
0: 左对齐，右端补 4&#x27;h0，
1: 右对齐，左端补 4bit 符号位</td></tr></table>

# 10.2.5.2 ADC0_TRIG

地址：0x4001_14BC

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr></table>

<table><tr><td rowspan="3"></td><td>CON_TRIG</td><td>TRG_MODE</td><td>SINGLE_TCNT</td><td>UTIMER3 CMP1_E</td><td>UTIMER3 CMP0_E</td><td>UTIMER2 CMP1_E</td><td>UTIMER2 CMP0_E</td><td>MCPWM_TRG3_E</td><td>MCPWM_TRG2_E</td><td>MCPWM_TRG1_E</td><td>MCPWM_TRG0_E</td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:15]</td><td></td><td>未使用</td></tr><tr><td>[14]</td><td>CON_TRIG</td><td>连续触发使能，高有效
写1，ADC进入连续触发模式进行连续采样
写0，ADC停止采样</td></tr><tr><td>[13:12]</td><td>TRG_MODE</td><td>触发模式
0:单段触发；
1:两段触发；
2:保留；
3:四段触发</td></tr><tr><td>[11:8]</td><td>SINGLE_TCNT</td><td>单段触发模式下触发一次采样所需的事件数
(0表示1次事件即触发，15表示16次事件才触发)</td></tr><tr><td>[7]</td><td>UTIMER3_CMP_E</td><td>4&#x27;b1xxx:UTimer3 CMP1 被使能</td></tr><tr><td>[6]</td><td>UTIMER3_CMP0_E</td><td>4&#x27;bx1xx:UTimer3 CMP0 被使能</td></tr><tr><td>[5]</td><td>UTIMER2_CMP1_E</td><td>4&#x27;bxx1x:UTimer2 CMP1 被使能</td></tr><tr><td>[4]</td><td>UTIMER2_CMP0_E</td><td>4&#x27;bxxx1:UTimer2 CMP0 被使能</td></tr><tr><td>[3]</td><td>MCPWM_TRG3_E</td><td>4&#x27;b1xxx: MCPWM T3 被使能</td></tr><tr><td>[2]</td><td>MCPWM_TRG2_E</td><td>4&#x27;bx1xx: MCPWM T2 被使能</td></tr><tr><td>[1]</td><td>MCPWM_TRG1_E</td><td>4&#x27;bxx1x: MCPWM T1 被使能</td></tr><tr><td>[0]</td><td>MCPWM_TRG0_E</td><td>4&#x27;bxxx1: MCPWM T0 被使能</td></tr></table>

TADC[3] = MCPWM_T3 | UTimer3_CMP1  TADC[2] = MCPWM_T2 | UTimer3_CMP0  TADC[1] = MCPWM_T1 | UTimer2_CMP1  TADC[0] = MCPWM_T0 | UTimer2_CMP0

来自两个不同设备的四个触发源相或之后送至ADC采样模块作为触发事件TADC[3:0]

在进入连续采样模式之前，须保证ADC采样模块处于空闲状态，推荐关闭ADC所有硬件触发使能，同时通过写ADC0_CFG.FSM_RESET=1；使得ADC采样状态机回到空闲状态。

MCPWM对ADC的触发信号可以通过配置GPIO为第9功能，即ADC_TRIGGER功能送出用于捕捉调试。ADC触发信号在芯片内部为一个ADC时钟周期的窄脉冲。每发生一次ADC触发，ADC_TRIGGER信号翻转一次，以便于输出捕捉。

UTimer 对 ADC 的触发信号可以通过配置 GPIO 为第 8 功能，即 Timer2/3 功能送出用于捕捉调试。

# 10.2.6 增益选择寄存器

# 10.2.6.1 ADC0_GAIN0

地址：0x4001_1488

复位值：0x0

表10-41增益选择寄存器ADC0_GAIN0  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名
称</td><td>说明</td></tr><tr><td>[31:10]</td><td></td><td>未使用</td></tr><tr><td>[9]</td><td>DG9</td><td>ADC0_DAT9 采样保持电路增益选择</td></tr><tr><td>[8]</td><td>DG8</td><td>ADC0_DAT8 采样保持电路增益选择</td></tr><tr><td>[7]</td><td>DG7</td><td>ADC0_DAT7 采样保持电路增益选择</td></tr><tr><td>[6]</td><td>DG6</td><td>ADC0_DAT6 采样保持电路增益选择</td></tr><tr><td>[5]</td><td>DG5</td><td>ADC0_DAT5 采样保持电路增益选择</td></tr><tr><td>[4]</td><td>DG4</td><td>ADC0_DAT4 采样保持电路增益选择</td></tr><tr><td>[3]</td><td>DG3</td><td>ADC0_DAT3 采样保持电路增益选择</td></tr><tr><td>[2]</td><td>DG2</td><td>ADC0_DAT2 采样保持电路增益选择</td></tr><tr><td>[1]</td><td>DG1</td><td>ADC0_DAT1 采样保持电路增益选择</td></tr><tr><td>[0]</td><td>DG0</td><td>ADC0_DAT0 采样保持电路增益选择</td></tr></table>

0:2/3 增益，1:1 倍增益。

# 10.2.6.2 ADC0_GAIN1

地址：0x4001_148C

复位值：0x0

表10-42增益选择寄存器ADC0_GAIN1  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td>DG19</td><td>DG18</td><td>DG17</td><td>DG16</td><td>DG15</td><td>DG14</td><td>DG13</td><td>DG12</td><td>DG11</td><td>DG10</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td></td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名
称</td><td>说明</td></tr><tr><td>[31:10]</td><td></td><td>本使用</td></tr><tr><td>[9]</td><td>DG19</td><td>ADC0_DAT19 采样保持电路增益选择</td></tr><tr><td>[8]</td><td>DG18</td><td>ADC0_DAT18 采样保持电路增益选择</td></tr><tr><td>[7]</td><td>DG17</td><td>ADC0_DAT17 采样保持电路增益选择</td></tr><tr><td>[6]</td><td>DG16</td><td>ADC0_DAT16 采样保持电路增益选择</td></tr><tr><td>[5]</td><td>DG15</td><td>ADC0_DAT15 采样保持电路增益选择</td></tr><tr><td>[4]</td><td>DG14</td><td>ADC0_DAT14 采样保持电路增益选择</td></tr><tr><td>[3]</td><td>DG13</td><td>ADC0_DAT13 采样保持电路增益选择</td></tr><tr><td>[2]</td><td>DG12</td><td>ADC0_DAT12 采样保持电路增益选择</td></tr><tr><td>[1]</td><td>DG11</td><td>ADC0_DAT11 采样保持电路增益选择</td></tr><tr><td>[0]</td><td>DG10</td><td>ADC0_DAT10 采样保持电路增益选择</td></tr></table>

0:2/3 增益，1:1 倍增益。

# 10.2.7 中断寄存器

10.2.7.1 ADC0_IE

地址：0x4001_14B0

复位值：0x0

表10-43中断使能寄存器ADC0_IE  

<table><tr><td colspan="9">15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0</td></tr><tr><td rowspan="3"></td><td>TH_IE</td><td>HERR_IE</td><td>SERR_IE</td><td>S4FINISH_IE</td><td>S3FINISH_IE</td><td>S2FINISH_IE</td><td>S1FINISH_IE</td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:7]</td><td></td><td>未使用</td></tr><tr><td>[6]</td><td>TH_IE</td><td>ADC0_DAT0 超阈值中断使能</td></tr><tr><td>[5]</td><td>HERR_IE</td><td>硬件触发发生在非空闲状态中断使能</td></tr><tr><td>[4]</td><td>SERR_IE</td><td>软件触发发生在非空闲状态中断使能</td></tr><tr><td>[3]</td><td>S4FINISH_IE</td><td>第四段采样完成中断使能</td></tr><tr><td>[2]</td><td>S3FINISH_IE</td><td>第三段采样完成中断使能</td></tr><tr><td>[1]</td><td>S2FINISH_IE</td><td>第二段采样完成中断使能</td></tr><tr><td>[0]</td><td>S1FINISH_IE</td><td>第一段采样完成中断使能</td></tr></table>

# 10.2.7.2 ADC0_IF

地址：0x4001_14B4

复位值：0x0

表10-44中断标志寄存器ADC0_IF  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>TH_IF</td><td>HERR_IF</td><td>SERR_IF</td><td>S4FINISH_IF</td><td>S3FINISH_IF</td><td>S2FINISH_IF</td><td>S1FINISH_IF</td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:7]</td><td></td><td>未使用</td></tr><tr><td>[6]</td><td>TH_IF</td><td>ADC0_DAT0 超阈值中断标志</td></tr><tr><td>[5]</td><td>HERR_IF</td><td>硬件触发发生在非空闲状态中断标志</td></tr><tr><td>[4]</td><td>SERR_IF</td><td>软件触发发生在非空闲状态中断标志</td></tr><tr><td>[3]</td><td>S4FINISH_IF</td><td>第四段采样完成中断标志</td></tr><tr><td>[2]</td><td>S3FINISH_IF</td><td>第三段采样完成中断标志</td></tr><tr><td>[1]</td><td>S2FINISH_IF</td><td>第二段采样完成中断标志</td></tr><tr><td>[0]</td><td>S1FINISH_IF</td><td>第一段采样完成中断标志</td></tr></table>

以上ADC0_IF标志位，0：表示未发生中断，1：表示发生过中断，写1清零

# 10.2.8 软件触发寄存器

# 10.2.8.1 ADC0 SWT

地址：0x4001_14C0

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">SWT</td><td></td></tr><tr><td colspan="15">WO</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr></table>

<table><tr><td>[15:0]</td><td>SWT</td><td>写入数据为 0x5AA5 时，产生一次软件触发</td></tr></table>

注意，软件触发采集寄存器为只写寄存器，且只有写入数据为0x5AA5时产生软件触发事件，一次总线的写入产生一次软件触发，数据写入产生一个软件触发后寄存器自动清零，等待后续的软件触发到来。

# 10.2.9 直流偏置寄存器

芯片出厂时已经过工厂标定，标定数据存放在Flash info中，芯片上电会自动加载。ADC模块在初始化的时候，需要根据数据左右对齐模式配置DC offset，可以参看芯片供应商提供的库函数。

# 10.2.9.1 ADC0_DC_A0

地址：0x4001_1490

复位值：0x0

表10-46直流偏置寄存器ADC0_DC_A0  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DC_OFFSET</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DC_OFFSET</td><td>采样电路 A 非一倍增益 ADC DC offset</td></tr></table>

# 10.2.9.2 ADC0_DC_A1

地址：0x4001_1494

复位值：0x0

表10-47直流偏置寄存器ADC0_DC_A1  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DC OFFSET</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DC_OFFSET</td><td>采样电路 A 一倍增益 ADC DC offset</td></tr></table>

# 10.2.9.3 ADC0_DC_B0

地址：0x4001_14A0  复位值：0x0

表10-48直流偏置寄存器ADC0_DC_B0  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DC_OFFSET</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DC_OFFSET</td><td>采样电路 B 非一倍增益 ADC DC offset</td></tr></table>

# 10.2.9.4 ADC0_DC_B1

地址：0x4001_14A4

复位值：0x0

表10-49直流偏置寄存器ADC0_DC_B1  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="14">DC_OFFSET</td><td></td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="14">0</td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DC_OFFSET</td><td>采样电路 B 一倍增益 ADC DC offset</td></tr></table>

# 10.2.10增益校正寄存器

# 10.2.10.1ADC0_AMC_A0

地址：0x4001_1498

复位值：0x0

表10-50增益校正寄存器ADC0_AMC_A0  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="6"></td><td colspan="9">AM_CALL</td><td></td></tr><tr><td colspan="9">RW</td><td></td></tr><tr><td colspan="9">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:10]</td><td></td><td>未使用</td></tr><tr><td>[9:0]</td><td>AM_CALL</td><td>采样电路 A 非一倍增益 ADC 增益校正寄存器</td></tr></table>

# 10.2.10.2 ADC0_AMC_A1

地址：0x4001_149C

复位值：0x0

表10-51增益校正寄存器ADC0_AMC_A1  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="6"></td><td colspan="9">A M CALL</td><td></td></tr><tr><td colspan="9">RW</td><td></td></tr><tr><td colspan="8">0&lt;lcol&gt;</td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:10]</td><td></td><td>未使用</td></tr><tr><td>[9:0]</td><td>AM_CALL</td><td>采样电路 A 一倍增益 ADC 增益校正寄存器</td></tr></table>

# 10.2.10.3 ADC0_AMC_B0

地址：0x4001_14A8

复位值：0x0

表10-52增益校正寄存器ADC0_AMC_B0  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="6"></td><td colspan="9">(AM_CALL)</td><td></td></tr><tr><td colspan="9">RW</td><td></td></tr><tr><td colspan="8">0&lt;lcel&quot;&gt;</td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:10]</td><td></td><td>未使用</td></tr></table>

<table><tr><td>[9:0]</td><td>AM_CALL</td><td>采样电路 B 非一倍增益 ADC 增益校正寄存器</td></tr></table>

# 10.2.10.4 ADC0_AMC_B1

地址：0x4001_14AC

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:10]</td><td></td><td>未使用</td></tr><tr><td>[9:0]</td><td>AM_CALL</td><td>采样电路 B 一倍增益 ADC 增益校正寄存器</td></tr></table>

ADC0_AMC存储的为增益校正系数  $\mathrm{AMP}_{\mathrm{correction}}$  ，为10bit无符号定点数，ADCAMC[9]为整数部分，ADCAMC[8:0]为小数部分。所存值为1左右。

ADC有1倍增益和非1倍增益两种配置，两种配置对应两套校正参数，每套校正数据分别包含一个DC offset(以下记为DCoffset)和一个增益校正值  $\mathrm{AMP}_{\mathrm{correction}}$  。

记ADC输出的数字量为  $\mathrm{D_{ADC}}$  ，  $\mathrm{D_{ADC}}$  对应的真实值为D。  $\mathbf{D}_0$  为编码数制的0，则

$$
\mathrm{D} = (\mathrm{D}_{\mathrm{ADC}}\cdot \mathrm{D}_0)^*\mathrm{AMP}_{\mathrm{correction}}\cdot \mathrm{DC}_{\mathrm{offset}}
$$

因为有A/B两路采样电路，因此有两组DC和AMC校正值，硬件会在不同通道进行数据校正时自动选择对应的A/B路的DC/AMC。

# 10.2.11通道0阈值寄存器

10.2.11.1 ADC0_DAT0_TH

地址：0x4001_14C4

复位值：0x0

表10-54通道0阈值寄存器ADC0_DAT0_TH  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DATA0_TH</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DAT0_TH</td><td>通道 0 阈值寄存器</td></tr></table>

用来配置ADC数值比较中断，当ADC0_DAT0大于或小于ADC0_DAT0_TH设置的值时，可以触发ADC数值比较中断。根据ADC0_CFG[1]配置，ADC0_DAT0_TH可作为ADC0_DAT0的上调值或下阈值；在一些应用上可以替代硬件比较器。具体来说，当ADC0_CFG.TH_TYPE=1时，即ADC0_DAT0_TH为上调值，如果ADC0_DAT0>ADC0_DAT0_TH，则产生阈值中断；当ADC0_CFG.TH_TYPE=0时，即ADC0_DAT0_TH为下阈值，如果ADC0_DAT0<ADC0_DAT0_TH，则产生阈值中断。

# 10.3 实现说明

# 10.3.1 DMA请求

只有ADC_IFS1FINISHLIF，即第一段采样完成事件可以作为DMA请求事件。因此只有单段触发采样完成，或多段触发采样第一段采样完成时会发起DMA请求，且这个请求与ADC_IE设置无关。DMA响应请求后会通过内部的写清零直接将ADC_IFS1FINISHLIF清零。

# 10.3.2 连续采样

当配置了连续采样模式时，即ADC_TRIG.CON_TRIG=1，ADC会反复采样单段模式下的各个通道，结束后立即开始下一轮单段采样，如果开启了单段采样中断，则会频繁发生中断，大部分情况下CPU来不及响应如此频繁的中断。软件写入ADC_TRIG.CON_TRIG=0，可以关闭连续采样。

连续采样模式可以配合ADC_DAT0阈值中断进行使用，只有检测到信号超过阈值时才产生阈值中断通知CPU。

连续采样可以配置采样多个通道，具体采样通道的配置与单段采样模式相同。

# 10.4 应用指南

# 10.4.1 ADC采样触发模式

ADC支持一段、两段、四段采样模式，每段采样需要特定的外部事件来触发开始，每段采样支持不同采样次数和采样信号通道配置。ADC内部的状态转移描述如下，共有8个状态分别为采样状态0~3，空闲状态0~3。

第一次触发

来自MCPWM/UTimer的定时事件TADC[0]/TADC[1]/TADC[2]/TADC[3]可以触发ADC采样。可以选择四个触发源的任何一个或者几个触发采样。也可以通过向ADC SWT写入命令字的方式16'h5AA5软件触发ADC采样。

第一段采样

判断是否为一段采样。

是：采样次数达到预设值ADC_CHNT0. S1即第一段采样次数后，ADC回到空闲状态0；若采样次数尚未达到预设值，继续采样。

否：采样次数达到预设值ADC_CHNT.S1，ADC进入空闲状态1（两段或四段采样第一段完成，等待触发第二段)；采样次数未达到预设值，继续第一段采样。

第二段触发

进入第二段采样

第二段采样

第二段采样次数到达预设值ADC_CHNT0. S2即第二段采样次数，判断是否为两段采样。

是：结束本次采样，回到空闲状态0。

否：进入空闲状态2，等待第三次触发及第四次触发完成采样。

第三段触发

进入第三段采样，如果到了次状态，则配置一定是四段采样。

第三段采样

第三段采样次数到达预设值ADC_CHNT1. S3即第三段采样次数，进入空闲状态3。

第四段触发

第四段采样

第四段采样通道数到达预设值ADC_CHNT1. S4即第四段采样次数，回到空闲状态0。

各种硬件触发模式的触发条件汇总如表10- 55所示。其中单段采样模式较为特殊，可以通过ADC0_CFG寄存器设置，一次MCPWM/UTimer定时事件即触发采样，还是多次MCPWM/UTimer定时事件发生到一定次数才触发采样；而两段、四段采样模式仅支持一次MCPWM/UTimer事件即触发采样。

此外ADC模块也支持通过软件向ADC0 SWT写入0x5AA5的方式触发采样，软件触发也仅支持写入一次即触发。

表10-55ADC采样触发模式  

<table><tr><td></td><td>单段触发</td><td>两段触发</td><td>四段触发</td></tr><tr><td rowspan="6">Timer触发</td><td>None
(Timer trigger 使能未打开)</td><td rowspan="6">第一段 TADC[0]
第二段 TADC[1]</td><td rowspan="6">第一段 TADC[0]
第二段 TADC[1]
第三段 TADC[2]
第四段 TADC[3]</td></tr><tr><td>C 次 TADC[0]</td></tr><tr><td>C 次 TADC[1]</td></tr><tr><td>C 次 TADC[2]</td></tr><tr><td>C 次 TADC[3]</td></tr><tr><td>C 次*</td></tr></table>

<table><tr><td></td><td>TADC[0]/TADC[1]/
TADC[2]/TADC[3]</td><td></td><td></td></tr><tr><td>软件触发</td><td>向 ADC_SWT 写入 16&#x27;h5aa5</td><td>第一段向 ADC0_SWT 写入 0x5AA5
第二段向 ADC0_SWT 写入 0x5AA5</td><td>第一段向 ADC0_SWT 写入 0x5AA5
第二段向 ADC0_SWT 写入 0x5AA5
第三段向 ADC0_SWT 写入 0x5AA5
第四段向 ADC0_SWT 写入 0x5AA5</td></tr></table>

$^{*}\mathrm{C}$  次通过ADC0_TRIG.SINGLE_TCNT设置。ADC0_TRIG.SINGLE_TCNT只在单段触发下使用，如果同时使能了TADC[3:0]，则4个触发源都会被计数，到SINGLE_TCNT次触发一次ADC采样转换。

# 10.4.1.1 单段触发模式

单段触发收到一次触发完成一段采样动作，一段采样可能包含多次对模拟信号的采样，次数由分段采样次数寄存器配ADC_CHNT0[4:0]进行配置，寄存器数值为  $1\sim 20$  时，对应的采样次数为  $1\sim 20$

假设单段采样配置通道数目为4，则采样转换后的数据会依次填充到ADC0DAT0、ADC0DAT1、ADC0DAT2、ADC0DAT3。

触发事件可以是来自外部的MCPWM/UTimer定时信号TADC[0]、TADC[1]、TADC[2]、TADC[3]、发生到预设次数、或者为软件触发。

每个采样的信号源通过信号来源寄存器ADCCHN0/1/2. ../19进行配置选定，信号源的选定需在触发前完成，且在一次采样过程完成前不应该改变。

完成一段采样动作后，进入空闲状态，并产生采样完成中断。

以MCPWM触发单段采样为例，设置TADC[2]发生4次才进行触发，状态转移如图10- 4所示。

![](images/59353b98c234ed509ba525991e3cea2300d11f72a981681f15877a2d25df86b5.jpg)  
图10-4ADC单段采样状态转移图

# 10.4.1.2 两段触发模式

两段触发需要两次触发才能完成完整的一轮采样。第一个触发到达时进行第一段采样，第二个触发到达时进行第二段采样。

触发事件可以是来自外部的MCPWM/UTimer定时信号TADC[0]和TADC[1]或两次软件触发。

TADC[0]或软件触发发生后，先进行ADC_CHNT0[4:0]次采样，完成后进入空闲状态并等待下一个触发信号的到来；TADC[1]或软件触发作为第二个触发信号发生后，再进行ADC_CHNT0[12:8]次

采样。采样次数均通过分段采样次数寄存器ADC_CHNT0进行配置。

假设两段采样配置通道数目分别为2和3，则第一段采样转换后的数据会依次填充到ADC0_DAT0、ADC0_DAT1，第二段采样转换后的数据会依次填充到ADC0_DAT2、ADC0_DAT3、ADC0_DAT4。

每个采样的信号源通过寄存器配置选定，信号源的选定需在触发前完成，且在一次采样过程完成前不应该改变。

软件触发较硬件触发的优先级低，在硬件触发采样的过程中发生软件触发，状态机不予处理，而产生一个错误中断。即只有状态机处于空闲状态时才会处理软件触发的采样请求。如果需要使用软件触发采样，需要确保硬件触发已经关闭。然后通过向ADC SWT寄存器写入0x5AA5以产生一次软件触发。

以两次软件触发两段采样为例，状态转移如图10- 5所示

![](images/915133e1cc53ae56218a0dc50bf5f6655ec27f8bebde24245dc39694f055e626.jpg)  
图10-5ADC两段采样状态转移图

# 10.4.1.3 四段触发模式

与两段触发类似。四段的触发源分别为TADC[0]、TADC[1]、TADC[2]、TADC[3]，且必须为MCPWM/UTimer TADC[0]/TADC[1]TADC[2]TADC[3]顺序触发ADC的四段采样；或者也可以是4次软件触发采样。四段采样的第一、二、三、四段采样次数分别为ADC_CHNT0[4:0]、ADC_CHNT0[12:8]、ADC_CHNT1[4:0]、ADC_CHNT1[12:8]。

假设四段采样配置通道数目分别为2、3、1、5，则第一段采样转换后的数据会依次填充到ADC0_DAT0、ADC0_DAT1，第二段采样转换后的数据会依次填充到ADC0_DAT2、ADC0_DAT3、ADC0_DAT4，第三段采样转换后的数据会填充到ADC0_DAT5，第四段采样转换后的数据会依次填充到ADC0_DAT6、ADC0_DAT7、ADC0_DAT8、ADC0_DAT9、ADC0_DAT10

以MCPWMTADC[0]/TADC[1]/TADC[2]/TADC[3]触发四段采样为例的状态转移如图10- 6所示。

![](images/5bf0bd2e21d03d8342e0568225eb8bd1166000c9bedb409711f65dded50af1d8.jpg)  
图10-6ADC四段采样状态转移图

为使用MCPWM定时器产生ADC采样触发信号，需要配置MCPWM_TMR0/ MCPWM_TMR1/ MCPWM_TMR2/ MCPWM_TMR3等寄存器，对应TADC0/1/2/3发生时的MCPWM计数器值，此外需要配置MCPWM_TH设置计数器计数范围以及MCPWM_TCLK设置计数时钟频率并使能时钟。

同理，如果使用UTimer对ADC进行定时触发，也需要配置UTIMER_UNT2_CMP0/UTIMER_UNT2_CMP1/UTIMER_UNT3_CMP0/UTIMER_UNT3_CMP1。

# 10.4.2 中断

# 10.4.2.1 单段触发采样完成中断

采样完成产生一个中断。

# 10.4.2.2 两段触发采样完成中断

第一段采样完成产生一个中断，第二段采样完成产生一个中断。

# 10.4.2.3 四段触发采样完成中断

第一段采样完成产生一个中断，第二段采样完成产生一个中断，第三段采样完成产生一个中断，第四段采样完成产生一个中断。

# 10.4.3 配置修改

建议在ADC中断中进行ADC0_CHNTx的配置和修改，因为进入ADC中断后说明ADC此时已完成一段采样且处于空闲状态。而在主程序中，无法确认ADC运行状态，因此在主程序中如需修改ADC0_CHNx和ADC0_CHNT等寄存器，需要先关闭ADC触发，并向ADC0_CFG.FSM_RESET写入1，以复位ADC接口电路状态机，确保ADC不在工作状态。如果ADC在运行中配置发生变化会发生不可预判的行为。

示例程序如下

ADC0_TRIG_temp = ADC0_TRIG; //保存ADC采样触发配置ADC0_TRIG = 0x0000; //关闭ADC采样触发ADC0_CFG |= 0x0004; //复位ADC接口电路状态机//此处进行的ADC采样通道和通道数的修改仅为示例ADC0_CHNT0 = 0x0005 //修改ADC单段采样通道数为5ADC0_CHN0 = 0x0305; //修改ADC第0/1次采样通道为模拟通道5和3ADC0_CHN1 = 0x0604; //修改ADC第2/3次采样通道为模拟通道4和6

ADC0_TRIG = ADC0_TRIG_temp; //恢复ADC采样触发配置

# 10.4.4 选择对应的模拟通道

ADC所采样信号对应的通道，请查阅表10- 36ADC采样信号通道选择以及DATASHEET中

表 2.2 引脚功能选择。关闭对应 IO 的 IE 和 OE，即可使用其模拟功能。

# 11 通用定时器

# 11.1 概述

# 11.1.1 功能框图

如图 11- 1 所示，通用定时器 UTIMER 主要包括 4 个独立的 Timer，分别可以独立配置运行计数时钟和滤波常数。每个 Timer 可以用于输出特定周期占空比的波形，也可以捕获外部波形进行周期占空比的检测。

![](images/60f84f8dc95549b16938b5f3148557c530e1544f72acca2a0b42e6860f4f2d3c.jpg)  
图 11-1 模块顶层功能框图

# 11.1.1.1 总线接口模块

总线接口模块包括：

将来自 AHB 总线的访问信号翻译为寄存器读写信号，控制寄存器模块的时钟，并对寄存器模块发起读写。

CG 时钟门控模块，在 AHB 总线无访问时，将寄存器模块时钟关闭以降低功耗。

# 11.1.1.2 寄存器模块

utimer_reg 寄存器模块，实现

对各个子模块控制寄存器的读写。

对各个子模块状态、结果寄存器的访问。

对各个子模块中断信号的处理和中断产生。

# 11.1.1.3 IO 滤波模块

10 滤波模块对来自芯片外部的输入信号进行滤波，降低毛刺对定时器功能的影响。

# 11.1.1.4 通用定时器模块

utimer_unt 模块实现了通用的定时器功能，包括比较和捕获工作模式，可以处理两个外部输入信号或者产生两个脉冲信号送到芯片外部。定时器模块中一共包括 4 个独立工作的通用定时器，Timer0/Unit0、Timer1/Unit1 为 16bit 位宽，Timer2/Unit2、Timer3/Unit3 为 32bit 位宽。每个定时器包含两个通道。

utimer_unt 模块，支持外部事件触发开始计数。外部事件源头可配。当外部事件触发后，utimer_unt 定时器开始自增。

# 11.1.1.5 编码器模块

编码器模块用于对芯片外部送入的编码器编码信号进行计数。定时器模块中集成了 2 个编码器模块。其中编码器的输入分别来自 Timer2 的通道 0/1 和 Timer3 的通道 0/1。使用编码器不影响 Timer 功能。

# 11.1.1.6 时钟分频模块

时钟分频模块用于产生时钟分频的各种信号。

# 11.1.2 功能特点

定时器模块有以下特点：

- 独立工作，可工作在不同频率下

- Timer0 和 Timer1 为 16bit 通用定时器

- Timer2 和 Timer3 为 32bit 通用定时器

- 每个通用定时器处理 2 个外部输入信号（捕获模式），或者产生 2 个输出信号（比较模式）

- 2 个独立工作计数器

- 对每个输入信号可以进行最大 120 个系统主时钟的滤波，即，当芯片工作在 96MHz 时钟频率下时，可以滤除 1.25us 宽度以下毛刺

- 支持 DMA 传输

# 11.2 实现说明

# 11.2.1 时钟分频

为了实现各个timer独立分频，且可以方便对中断/计数值进行写操作，采取了各个timer均工作在系统主频，但使用分频计数器来降低计数器计数频率。

# 11.2.2 滤波

定时器模块共有8个/4对通道输入，定时器可以对每个输入进行不同程度的滤波。

通过配置滤波寄存器可以调整滤波宽度，  $0\sim 120$  个系统时钟宽度。

输入信号滤波始终使用系统高速时钟，通常为96MHzPLL时钟，UTIMER_UNTx_CFG.CLK_DIV对Timer计数时钟的分频对滤波时钟没有影响。

如图11- 2所示，原始输入信号在t1\~t6几个时刻发生了翻转，滤波器宽度配置成T。可以看到只有t3和t6时刻发生的翻转维持了大于T的时间，因此从滤波器的输出看，信号仅发生了两次翻转。

![](images/06a44384deac16c45247c11c4f2a3faa5a8157120fe422134d8bbcc6c0fe7583.jpg)  
图11-2滤波示意图

# 11.2.3 模式

# 11.2.3.1计数器

Timer中的计数器采用递增方向计数。

计数器从0计数到TH值，再回到0重新开始计数，计数器回到0时，产生回零中断。实际计数周期为clk_freq\*(TH+1)。

![](images/af68a298b7a438db10c5af89321e139f4277d647b254d4de36cafd3e20a503a1.jpg)  
图11-3通用计数器

# 11.2.3.2 比较模式

比较模式下，计数器计数到UTIMER_UNTx_CMP值时，产生比较中断。比较模式可以驱动一个比较脉冲发生，在回零时，向IO口输出一个电平（极性可配置），在比较事件发生时，电平翻转，向IO口输出另一个电平。计数器回零时，仍然会产生回零中断。回零事件优先于比较事件，因此，两者同时发生时候（CMP==0），输出回零的值，而不会输出比较事件的值。

# 如果要实现某个Timer通道0输出全0：

1）可以设置UTIMER_UNTx_CFG.CH0_POL=0

2）并设置UTIMER_UNTx_CMP0=UTIMER_UNTx_TH+1，。即Timer计数值回0时，通道输出0，且Timer计数值全程不命中CMP0。

或设置UTIMER_UNTx_CMP0=0，即Timer命中CMP0和回零事件为相同事件。

# 如果要实现某个Timer通道0输出全1：

1）可以设置UTIMER_UNTx_CFG.CH0_POL=1

2）并设置UTIMER_UNTx_CMP0=UTIMER_UNTx_TH+1，。即Timer计数值回0时，通道输出1，且Timer计数值全程不命中CMP0。

或设置UTIMER_UNTx_CMP0=0，即Timer命中CMP0和回零事件为相同事件。

![](images/86e48f85252b05e854b0ba640fd476c5c1b074c61af20a32cbc1ad4bedc20751.jpg)

![](images/fdd95b2c5797e0b23256b00cb306fc2c979994cf59c15949ab7feef6d7af230c.jpg)  
图11-4 比较模式

# 11.2.3.3 捕获模式

捕获模式下，可以使用Timer来检测输入信号的上升/下降或者双沿，发生捕获事件（即输入信号电平变化）时，定时器计数值存入UTIMER_UNTx_CMP寄存器，并产生捕获中断。计数器回零时，仍然会产生回零中断。

![](images/01c9275c88281a6b81afbd0401b15f6e60a37375b952a97895de8d6ad4e187b0.jpg)  
图11-5 捕获模式

如图10- 5所示，定时器设置为上升沿捕获。在CAP0/CAP1/CAP2三个时刻点，捕获到输入信号发生上升沿变化，对应时刻点的定时器计数值将存入UTIMER_UNTx_CMP寄存器中。

# 11.2.4 编码器

编码器接口支持正交编码信号、符号加脉冲信号、CW/CCW双脉冲信号三种模式。

其中Encoder0的两个输入信号T1/T2分别来自Timer2Channel0/1对应的GPIO输入；Encoder1的T1/T2信号分别来自Timer3Channel0/1对应的GPIO输入。开启编码器功能时并不影响Timer功能的正常使用。

# 11.2.4.1 正交编码信号

正交编码信号多用于计数编码器圈数，输入为T1/T2两个信号，支持下表中两个模式。

概括来讲，T1/T2的跳变沿会导致计数器递增或递减。而计数器计数方向（递增或递减）由跳变信号之外的另一个稳态信号的电平高低决定。

如果T1发生了上升沿跳变，则看T2是高电平还是低电平，如果是高电平则计数器递减，如果是低电平计数器递增，T1下降沿计数器变化相反。

如果T2发生了上升沿跳变，则看T1是高电平还是低电平，如果是高电平则计数器递增，如果是低电平计数器递减，T2下降沿计数器变化相反。

以下式子表示

CounterUp  $= (\mathrm{T1}! = \mathrm{T2})@(\mathrm{T1}$  triggering edges) |  $(\mathrm{T1} = =\mathrm{T2})$ $a$  (T2 triggering edges) Counter Down  $= (\mathrm{T1} = =\mathrm{T2})$ $a$  (T1 triggering edges) |  $(\mathrm{T1}! = \mathrm{T2})$ $a$  (T2 triggering edges)

表11-1编码器正交编码工作模式  

<table><tr><td rowspan="2">计数模式</td><td rowspan="2">T1/T2 电平状态(稳态信号)</td><td colspan="2">T1 变化边沿状态</td><td colspan="2">T2 变化边沿状态</td></tr><tr><td>上升沿</td><td>下降沿</td><td>上升沿</td><td>下降沿</td></tr><tr><td rowspan="2">仅 T1 计数</td><td>T2 高</td><td>递减</td><td>递增</td><td>不计数</td><td>不计数</td></tr><tr><td>T2 低</td><td>递增</td><td>递减</td><td>不计数</td><td>不计数</td></tr><tr><td rowspan="4">T1/T2 都计数</td><td>T2 高</td><td>递减</td><td>递增</td><td>不计数</td><td>不计数</td></tr><tr><td>T2 低</td><td>递增</td><td>递减</td><td>不计数</td><td>不计数</td></tr><tr><td>T1 高</td><td>不计数</td><td>不计数</td><td>递增</td><td>递减</td></tr><tr><td>T1 低</td><td>不计数</td><td>不计数</td><td>递减</td><td>递增</td></tr></table>

![](images/05af8e85aaed32968c7ca9cc1972004b5250c33d5cd8d48968016a5c10be1348.jpg)  
图11-6编码器只在T1时刻计数的正交编码信号计数情况

![](images/f8300be6452063a90b05a4f301604376e24482c14f9379667debcb1597c380bb.jpg)  
图11-7编码器在T1或T2时刻计数的正文编码信号计数情况

# 11.2.4.2符号加脉冲信号

这种工作模式下，T1为脉冲信号，T2为符号信号。T1的边沿触发计数，T2电平控制计数方向，高则递增，低则递减。可以配置仅T1上升沿计数还是T1上升下降沿都计数。

CounterUp  $= (\mathrm{T2} = =1)$  @ (T1 triggering edges) Counter Down  $= (\mathrm{T2} = =0)$  @ (T1 triggering edges)

表11-2编码器符号加脉冲工作模式  

<table><tr><td rowspan="2">计数模式</td><td rowspan="2">T2 电平状态 (稳态信号)</td><td colspan="2">T1 变化边沿状态</td></tr><tr><td>上升沿</td><td>下降沿</td></tr><tr><td rowspan="2">仅 T1 上升沿</td><td>高</td><td>递增</td><td>不计数</td></tr><tr><td>低</td><td>递减</td><td>不计数</td></tr><tr><td rowspan="2">T1 上升下降沿</td><td>高</td><td>递增</td><td>递减</td></tr><tr><td>低</td><td>递减</td><td>递增</td></tr></table>

![](images/5e4b8be1380ba126cfca82359cafad02abe3c338a06932d72f35105750c16632.jpg)  
图11-8编码器在T1上升下降沿都计数的符号加脉冲信号计数情况

![](images/30b6f1f01c9b56d1484832c2e035b5ef79300f978b39e2b1df541bee0104e05a.jpg)  
图11-9编码器在仅T1上升沿计数的符号加脉冲信号计数情况

# 11.2.4.3 CCW/CW双脉冲信号

在T1跳变时计数器递增，在T2跳变时计数器递减。可以配置计数器仅在上升沿变化或者在上升下降沿都变化。以下式表示

CounterUp  $= 1\circledast$  (T1 triggering edges) Counter Down  $= 1\circledast$  (T2 triggering edges)

表11-3编码器CCW/CW双脉冲工作模式  

<table><tr><td rowspan="2">计数模式</td><td colspan="4">变化边沿状态</td></tr><tr><td>T1上升沿</td><td>T1下降沿</td><td>T2上升沿</td><td>T2下降沿</td></tr><tr><td>T1/T2上升沿</td><td>递增</td><td>不计数</td><td>递减</td><td>不计数</td></tr><tr><td>T1/T2上升下降沿</td><td>递增</td><td>递增</td><td>递减</td><td>递减</td></tr></table>

![](images/c70817589a479f601401905e0ba77498c1a988e852393898e3a700a5304251ae.jpg)  
图11-10编码器仅在T1/T2上升沿计数的CCW/CW双脉冲信号计数情况

![](images/fc21ca1ca1210a4b0f346e10976f7803bde4957e82f4965654dca56ccaf21b6a.jpg)  
图11-11编码器在T1/T2上升下降沿计数的CCW/CW双脉冲信号计数情况

# 11.3 寄存器

# 11.3.1 地址分配

通用定时器模块在芯片中的基地址是0x4001_1800，寄存器列表如下：

表11-4通用定时器配置寄存器地址分配  

<table><tr><td>名称</td><td>偏移</td><td>描述</td></tr></table>

<table><tr><td>UTIMER_UNTO_CFG</td><td>0x00</td><td>Timer0 配置寄存器</td></tr><tr><td>UTIMER_UNTO_TH</td><td>0x04</td><td>Timer0 计数门限寄存器</td></tr><tr><td>UTIMER_UNTO_CNT</td><td>0x08</td><td>Timer0 计数值寄存器</td></tr><tr><td>UTIMER_UNTO_CMP0</td><td>0x0C</td><td>Timer0 比较/捕获寄存器 0</td></tr><tr><td>UTIMER_UNTO_CMP1</td><td>0x10</td><td>Timer0 比较/捕获寄存器 1</td></tr><tr><td>UTIMER_UNTO_EVT</td><td>0x14</td><td>Timer0 外部事件选择寄存器</td></tr><tr><td>UTIMER_UNT1_CFG</td><td>0x20</td><td>Timer1 配置寄存器</td></tr><tr><td>UTIMER_UNT1_TH</td><td>0x24</td><td>Timer1 计数门限寄存器</td></tr><tr><td>UTIMER_UNT1_CNT</td><td>0x28</td><td>Timer1 计数值寄存器</td></tr><tr><td>UTIMER_UNT1_CMP0</td><td>0x2C</td><td>Timer1 比较/捕获寄存器 0</td></tr><tr><td>UTIMER_UNT1_CMP1</td><td>0x30</td><td>Timer1 比较/捕获寄存器 1</td></tr><tr><td>UTIMER_UNT1_EVT</td><td>0x34</td><td>Timer1 外部事件选择寄存器</td></tr><tr><td>UTIMER_UNT2_CFG</td><td>0x40</td><td>Timer2 配置寄存器</td></tr><tr><td>UTIMER_UNT2_TH</td><td>0x44</td><td>Timer2 计数门限寄存器</td></tr><tr><td>UTIMER_UNT2_CNT</td><td>0x48</td><td>Timer2 计数值寄存器</td></tr><tr><td>UTIMER_UNT2_CMP0</td><td>0x4C</td><td>Timer2 比较/捕获寄存器 0</td></tr><tr><td>UTIMER_UNT2_CMP1</td><td>0x50</td><td>Timer2 比较/捕获寄存器 1</td></tr><tr><td>UTIMER_UNT2_EVT</td><td>0x54</td><td>Timer2 外部事件选择寄存器</td></tr><tr><td>UTIMER_UNT3_CFG</td><td>0x60</td><td>Timer3 配置寄存器</td></tr><tr><td>UTIMER_UNT3_TH</td><td>0x64</td><td>Timer3 计数门限寄存器</td></tr><tr><td>UTIMER_UNT3_CNT</td><td>0x68</td><td>Timer3 计数值寄存器</td></tr><tr><td>UTIMER_UNT3_CMP0</td><td>0x6C</td><td>Timer3 比较/捕获寄存器 0</td></tr><tr><td>UTIMER_UNT3_CMP1</td><td>0x70</td><td>Timer3 比较/捕获寄存器 1</td></tr><tr><td>UTIMER_UNT3_EVT</td><td>0x74</td><td>Timer3 外部事件选择寄存器</td></tr><tr><td>UTIMER_ECD0_CFG</td><td>0x80</td><td>Encoder0 配置寄存器</td></tr><tr><td>UTIMER_ECD0_TH</td><td>0x84</td><td>Encoder0 计数门限寄存器</td></tr><tr><td>UTIMER_ECD0_CNT</td><td>0x88</td><td>Encoder0 计数值寄存器</td></tr><tr><td>UTIMER_ECD1_CFG</td><td>0x90</td><td>Encoder1 配置寄存器</td></tr><tr><td>UTIMER_ECD1_TH</td><td>0x94</td><td>Encoder1 计数门限寄存器</td></tr><tr><td>UTIMER_ECD1_CNT</td><td>0x98</td><td>Encoder1 计数值寄存器</td></tr><tr><td>UTIMER_FLT_TH01</td><td>0xA0</td><td>滤波门限寄存器 01</td></tr><tr><td>UTIMER_FLT_TH23</td><td>0xA4</td><td>滤波门限寄存器 23</td></tr><tr><td>UTIMER_CFG</td><td>0xF0</td><td>通用定时器配置寄存器</td></tr><tr><td>UTIMER_IE</td><td>0xF4</td><td>中断使能寄存器</td></tr><tr><td>UTIMER_IF</td><td>0xF8</td><td>中断标志寄存器</td></tr><tr><td>UTIMER_RE</td><td>0xFC</td><td>DMA 管理寄存器</td></tr></table>

# 11.3.2 系统控制寄存器

# 11.3.2.1 UTIMER_CFG

地址：0x4001_18F0

复位值：0x0

表11-5UTIMER配置寄存器UTIMER_CFG  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td></td></tr><tr><td></td></tr><tr><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:10]</td><td></td><td>未使用</td></tr><tr><td>[9]</td><td>ENC1_EN</td><td>1: 启动编码器 1, 0: 停止编码器 1</td></tr><tr><td>[8]</td><td>ENC0_EN</td><td>1: 启动编码器 0, 0: 停止编码器 0</td></tr><tr><td>[7]</td><td>TIMER3_EN</td><td>Timer3 使能，当 TIMER3_EN 为 0 时，Timer3 停止计数</td></tr><tr><td>[6]</td><td>TIMER2_EN</td><td>Timer2 使能，当 TIMER2_EN 为 0 时，Timer2 停止计数</td></tr><tr><td>[5]</td><td>TIMER1_EN</td><td>Timer1 使能，当 TIMER1_EN 为 0 时，Timer1 停止计数</td></tr><tr><td>[4]</td><td>TIMER0_EN</td><td>Timer0 使能，当 TIMER0_EN 为 0 时，Timer0 停止计数</td></tr><tr><td>[3:0]</td><td></td><td>系统保留，推荐写入 0</td></tr></table>

当Timer停止计数时，Timer的寄存器配置不受影响，仍然保持；且在停止计数时仍可以通过软件修改Timer的寄存器配置。

# 11.3.3 滤波控制寄存器

# 11.3.3.1UTIMER_FLT_TH01

地址：0x4001_18A0

复位值：0x0

表11-6滤波控制寄存器UTIMER_FLT_TH01  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>T1_CH1_FLT</td><td></td><td></td><td>T1_CH0_FLT</td><td></td><td></td><td></td><td>T0_CH1_FLT</td><td></td><td></td><td></td><td>T0_CH0_FLT</td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td></td><td></td><td>0</td><td></td><td></td><td></td><td>0</td><td></td><td></td><td></td><td>0</td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:12]</td><td>T1_CH1_FLT</td><td>TIM1_CH1 信号滤波宽度选择，取值范围 0～15。
[15:12]为 0 时，对 TIM1_CH1 不进行滤波。
[15:12]不为 0 时，对 TIM1_CH1 信号进行滤波：滤波宽度为 T1_CH1_FLT×8。当 TIM1_CH1 电平稳定超过 T1_CH1_FLT×8 个系统时钟周期宽度时，滤波器输出更新到 TIM1_CH1 信号值；否则，滤波器保</td></tr></table>

<table><tr><td></td><td></td><td>持当前的输出不变。</td></tr><tr><td>[11:8]</td><td>T1_CH0_FLT</td><td>TIM1_CH0 信号滤波宽度选择。含义同 T1_CH1_FLT。</td></tr><tr><td>[7:4]</td><td>T0_CH1_FLT</td><td>TIM0_CH1 信号滤波宽度选择。含义同 T1_CH1_FLT。</td></tr><tr><td>[3:0]</td><td>T0_CH0_FLT</td><td>TIM0_CH0 信号滤波宽度选择。含义同 T1_CH1_FLT。</td></tr></table>

# 11.3.3.2UTIMER_FLT_TH23

地址：0x4001_18A4

复位值：0x0

表11-7滤波控制寄存器UTIMER_FLT_TH23  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="4">T3_CH1_FLT</td><td colspan="3">T3_CH0_FLT</td><td colspan="3">T2_CH1_FLT</td><td colspan="5">T2_CH0_FLT</td><td></td></tr><tr><td colspan="4">RW</td><td colspan="3">RW</td><td colspan="3">RW</td><td colspan="5">RW</td><td></td></tr><tr><td colspan="4">0</td><td colspan="3">0</td><td colspan="3">0</td><td colspan="5">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:12]</td><td>T3_CH1_FLT</td><td>TIM3_CH1 信号滤波宽度选择，取值范围 0~15。
[15:12]为 0 时，对 TIM3_CH1 不进行滤波。
[15:12]不为 0 时，对 TIM3_CH1 信号进行滤波：滤波宽度为 T3_CH1_FLT×8。当 TIM3_CH1 电平稳定超过 T3_CH1_FLT×8 个系统时钟周期宽度时，滤波器输出更新到 TIM3_CH1 信号值；否则，滤波器保持当前的输出不变。</td></tr><tr><td>[11:8]</td><td>T3_CH0_FLT</td><td>TIM3_CH0 信号滤波宽度选择。含义同 T3_CH1_FLT。</td></tr><tr><td>[7:4]</td><td>T2_CH1_FLT</td><td>TIM2_CH1 信号滤波宽度选择。含义同 T3_CH1_FLT。</td></tr><tr><td>[3:0]</td><td>T2_CH0_FLT</td><td>TIM2_CH0 信号滤波宽度选择。含义同 T3_CH1_FLT。</td></tr></table>

# 11.3.4 定时器寄存器

Timer0/1完全相同，此处仅说明Timer0寄存器

Timer2/3完全相同，与Timer0/1不同之处在于Timer2/3计数器相关寄存器为32位宽，而Timer0/1计数器相关寄存器为16位宽。

Encoder0复用了Timer2的输入端口，Encoder1复用了Timer3的输入端口；开启Encoder功能时，并不影响对应Timer的正常使用。

# 11.3.4.1UTIMER_UNTO_CFGTimer0配置寄存器

地址：0x4001_1800

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td>ETON</td><td rowspan="3"></td><td>CLK_DIV</td><td></td><td>CH1_POL</td><td></td><td>CH1_MODE</td><td></td><td>CH1_RE_CAP_EN</td><td></td><td>CH1_POL</td><td></td><td>CH0_MODE</td><td></td><td>CH0_RE_CAP_EN</td><td></td></tr><tr><td>RW</td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td></tr><tr><td>0</td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:12]</td><td></td><td>未使用</td></tr><tr><td>[11]</td><td>ETON</td><td>Timer0 计数器计数使能来源。
0，自动运行，持续计数；
1，等待外部事件触发计数一个 Timer 周期后停止。
外部事件通过 UTM ER_UNTO_EVT 寄存器进行配置。</td></tr><tr><td>[10]</td><td></td><td>系统保留，恒 0。</td></tr><tr><td>[9:8]</td><td>CLK_DIV</td><td>Timer0 计数器频率配置，计数器计数频率是系统主时钟频率的 1/2/4/8 分频：
00：1 分频，01：2 分频，10：4 分频，11：8 分频</td></tr><tr><td>[7]</td><td>CH1_POL</td><td>通道 1 在比较模式下的输出极性控制：当计数器计数值回零时的输出值。</td></tr><tr><td>[6]</td><td>CH1_MODE</td><td>通道 1 的工作模式：
0，比较模式，输出方波，在通道 1 计数器计数值等于 0 或等于比较捕获寄存器值时发生翻转。
1，捕获模式，当通道 1 输入信号发生捕获事件时，将计数器计数值存入通道 1 比较捕获寄存器。</td></tr><tr><td>[5]</td><td>CH1_FE_CAP_EN</td><td>通道 1 下降沿捕获事件使能。1：使能；0：关闭。
通道 1 输入信号发生 1→0 跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。</td></tr><tr><td>[4]</td><td>CH1_RE_CAP_EN</td><td>通道 1 上升沿捕获事件使能。1：使能；0：关闭。
通道 1 输入信号发生 0→1 跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。</td></tr><tr><td>[3]</td><td>CH0_POL</td><td>通道 0 在比较模式下的输出极性控制：当计数器计数值回零时的输出值。</td></tr><tr><td>[2]</td><td>CH0_MODE</td><td>通道 0 的工作模式：
0，比较模式，输出方波，在通道 0 计数器计数值等于 0 或等于比较捕获寄存器值时发生翻转。
1，捕获模式，当通道 0 输入信号发生捕获事件时，将计数器计数值存入通道 0 比较捕获寄存器。</td></tr><tr><td>[1]</td><td>CH0_FE_CAP_EN</td><td>通道 0 下降沿捕获事件使能。1：使能；0：关闭。
通道 0 输入信号发生 1→0 跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。</td></tr><tr><td>[0]</td><td>CH0_RE_CAP_EN</td><td>通道 0 上升沿捕获事件使能。1：使能；0：关闭。</td></tr></table>

<table><tr><td></td><td></td><td>通道0输入信号发生0→1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。</td></tr></table>

# 11.3.4.2UTIMER_UNT1_CFGTimer1配置寄存器

地址：0x4001_1820

复位值：0x0

表11-9Timer0配置寄存器UTIMER_UNT0_CFG  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td>ETON</td><td rowspan="3"></td><td>CLK_DIV</td><td></td><td>CH1_POL</td><td></td><td>CH1_MODE</td><td></td><td>CH1_FE_CAP_EN</td><td></td><td>CH1_RE_CAP_EN</td><td></td><td>CH0_POL</td><td></td><td>CH0_MODE</td><td></td><td>CH0_FE_CAP_EN</td><td></td><td>CH0_RE_CAP_EN</td><td></td></tr><tr><td>RW</td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:12]</td><td></td><td>未使用</td></tr><tr><td>[11]</td><td>ETON</td><td>Timer1计数器计数使能来源。
0，自动运行，持续计数；
1，等待外部事件触发计数一个Timer周期后停止。
外部事件通过UTIMER_UNT1_EVT寄存器进行配置。</td></tr><tr><td>[10]</td><td></td><td>系统保留，恒0。</td></tr><tr><td>[9:8]</td><td>CLK_DIV</td><td>Timer1计数器频率配置，计数器计数频率是系统主频率的1/2/4/8分频：
00：1分频，01：2分频，10：4分频，11：8分频</td></tr><tr><td>[7]</td><td>CH1_POL</td><td>通道1在比较模式下的输出极性控制：当计数器计数值回零时的输出值。</td></tr><tr><td>[6]</td><td>CH1_MODE</td><td>通道1的工作模式：
0，比较模式，输出方波，在通道1计数器计数值等于0或等于比较捕获寄存器值时发生翻转。
1，捕获模式，当通道1输入信号发生捕获事件时，将计数器计数值存入通道1比较捕获寄存器。</td></tr><tr><td>[5]</td><td>CH1_FE_CAP_EN</td><td>通道1下降沿捕获事件使能。1：使能；0：关闭。
通道1输入信号发生1→0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。</td></tr><tr><td>[4]</td><td>CH1_RE_CAP_EN</td><td>通道1上升沿捕获事件使能。1：使能；0：关闭。
通道1输入信号发生0→1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。</td></tr><tr><td>[3]</td><td>CH0_POL</td><td>通道0在比较模式下的输出极性控制：当计数器计数值回零时的输出值。</td></tr></table>

<table><tr><td>[2]</td><td>CH0_MODE</td><td>通道0的工作模式，
0，比较模式，输出方波，在通道0计数器计数值等于0或等于比较捕获寄存器值时发生翻转。
1，捕获模式，当通道0输入信号发生捕获事件时，将计数器计数值存入通道0比较捕获寄存器。</td></tr><tr><td>[1]</td><td>CH0_FE_CAP_EN</td><td>通道0下降沿捕获事件使能。1：使能；0：关闭。
通道0输入信号发生1→0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。</td></tr><tr><td>[0]</td><td>CH0_RE_CAP_EN</td><td>通道0上升沿捕获事件使能。1：使能；0：关闭。
通道0输入信号发生0→1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。</td></tr></table>

# 11.3.4.3UTIMER_UNT2_CFGTimer2配置寄存器

地址：0x4001_1840

复位值：0x0

表11-10Timer2配置寄存器UTIMER_UNT2_CFG  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>ETON</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td>RW</td><td></td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td></tr><tr><td></td><td></td><td></td><td></td><td>0</td><td></td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:12]</td><td></td><td>未使用</td></tr><tr><td>[11]</td><td>ETON</td><td>0，自动运行，持续计数；
1，等待外部事件触发计数一个 Timer 周期后停止。
外部事件通过 UTM ER_UNT2_EVT 寄存器进行配置。</td></tr><tr><td>[10]</td><td></td><td>系统保留，恒 0。</td></tr><tr><td>[9:8]</td><td>CLK_DIV</td><td>Timer2 计数器频率配置，计数器计数频率是系统主频率的 1/2/4/8 分频：
00：1 分频，01：2 分频，10：4 分频，11：8 分频</td></tr><tr><td>[7]</td><td>CH1_POL</td><td>通道 1 在比较模式下的输出极性控制：当计数器计数值回零时的输出值。</td></tr><tr><td>[6]</td><td>CH1_MODE</td><td>通道 1 的工作模式：
0，比较模式，输出方波，在通道 1 计数器计数值等于 0 或等于比较捕获寄存器值时发生翻转。
1，捕获模式，当通道 1 输入信号发生捕获事件时，将计数器计数值存入通道 1 比较捕获寄存器。</td></tr></table>

<table><tr><td>[5]</td><td>CH1_FE_CAP_EN</td><td>通道1下降沿捕获事件使能。1：使能；0：关闭。
通道1输入信号发生1→0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。</td></tr><tr><td>[4]</td><td>CH1_RE_CAP_EN</td><td>通道1上升沿捕获事件使能。1：使能；0：关闭。
通道1输入信号发生0→1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。</td></tr><tr><td>[3]</td><td>CH0_POL</td><td>通道0在比较模式下的输出极性控制：当计数器计数值回零时的输出值。</td></tr><tr><td>[2]</td><td>CH0_MODE</td><td>通道0的工作模式，
0，比较模式，输出方波，在通道0计数器计数值等于0或等于比较捕获寄存器值时发生翻转。
1，捕获模式，当通道0输入信号发生捕获事件时，将计数器计数值存入通道0比较捕获寄存器。</td></tr><tr><td>[1]</td><td>CH0_FE_CAP_EN</td><td>通道0下降沿捕获事件使能。1：使能；0：关闭。
通道0输入信号发生1→0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。</td></tr><tr><td>[0]</td><td>CH0_RE_CAP_EN</td><td>通道0上升沿捕获事件使能。1：使能；0：关闭。
通道0输入信号发生0→1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。</td></tr></table>

# 11.3.4.4UTIMER_UNT3_CFGTimer3配置寄存器

地址：0x4001_1860

复位值：0x0

表11-11Timer3配置寄存器UTIMER_UNT3_CFG  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td>ETON</td><td rowspan="3"></td><td>CLK_DIV</td><td></td><td>CH1_POL</td><td></td><td>CH1_MODE</td><td></td><td>CH1_FE_CAP_EN</td><td></td><td>CH1_RE_CAP_EN</td><td></td><td>CH0_POL</td><td></td><td>CH0_MODE</td><td></td><td>CH0_FE_CAP_EN</td><td></td><td>CH0_RE_CAP_EN</td><td></td></tr><tr><td>RW</td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td>RW</td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td>0</td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:12]</td><td></td><td>未使用</td></tr><tr><td>[11]</td><td>ETON</td><td>0，自动运行，持续计数；
1，等待外部事件触发计数一个 Timer 周期后停止。
外部事件通过 UTIMER_UNT3_EVT 寄存器进行配置。</td></tr><tr><td>[10]</td><td></td><td>系统保留，恒 0。</td></tr><tr><td>[9:8]</td><td>CLK_DIV</td><td>Timer3 计数器频率配置，计数器计数频率是系统主频率的 1/2/4/8 分频：</td></tr></table>

<table><tr><td></td><td></td><td>00:1分频, 01:2分频, 10:4分频, 11:8分频</td></tr><tr><td>[7]</td><td>CH1_POL</td><td>通道1在比较模式下的输出极性控制:当计数器计数值回零时的输出值。</td></tr><tr><td>[6]</td><td>CH1_MODE</td><td>通道1的工作模式:
0,比较模式,输出方波,在通道1计数器计数值等于0或等于比较捕获寄存器值时发生翻转。
1,捕获模式,当通道1输入信号发生捕获事件时,将计数器计数值存入通道1比较捕获寄存器。</td></tr><tr><td>[5]</td><td>CH1_FE_CAP_EN</td><td>通道1下降沿捕获事件使能。1:使能;0:关闭。
通道1输入信号发生1→0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。</td></tr><tr><td>[4]</td><td>CH1_RE_CAP_EN</td><td>通道1上升沿捕获事件使能。1:使能;0:关闭。
通道1输入信号发生0→1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。</td></tr><tr><td>[3]</td><td>CH0_POL</td><td>通道0在比较模式下的输出极性控制:当计数器计数值回零时的输出值。</td></tr><tr><td>[2]</td><td>CH0_MODE</td><td>通道0的工作模式,
0,比较模式,输出方波,在通道0计数器计数值等于0或等于比较捕获寄存器值时发生翻转。
1,捕获模式,当通道0输入信号发生捕获事件时,将计数器计数值存入通道0比较捕获寄存器。</td></tr><tr><td>[1]</td><td>CH0_FE_CAP_EN</td><td>通道0下降沿捕获事件使能。1:使能;0:关闭。
通道0输入信号发生1→0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。</td></tr><tr><td>[0]</td><td>CH0_RE_CAP_EN</td><td>通道0上升沿捕获事件使能。1:使能;0:关闭。
通道0输入信号发生0→1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。</td></tr></table>

在LKS32MC08x系列中，Timer0/1为16bit位宽；Timer2/3为32bit位宽，因此Timer2/3下列相关寄存器为32bit位宽。

# 11.3.4.5UTIMER_UNTO_THTimer0门限寄存器

地址：0x4001_1804

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16">UNTO_TH</td></tr><tr><td colspan="16">RW</td></tr><tr><td colspan="16">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr></table>

<table><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>UNTO_TH</td><td>Timer 0 计数器计数门限。计数器从 0 计数到 UTIMER_UNTO_TH 值后再次回 0 开始计数。</td></tr></table>

# 11.3.4.6UTIMER_UNT1_THTimer1门限寄存器

地址：0x4001_1824

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">UNT1_TH</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>UNT1_TH</td><td>Timer 1 计数器计数门限。计数器从 0 计数到 UTIMER_UNT1_TH 值后再次回 0 开始计数。</td></tr></table>

11.3.4.7UTIMER_UNT2_THTimer2门限寄存器

地址：0x4001_1844

复位值：0x0

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>10</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td colspan="15">UNT2_TH</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td colspan="14"></td></tr></table>

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">UNT2_TH</td><td></td></tr><tr><td colspan="16">RW</td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>UNT2_TH</td><td>Timer 2 计数器计数门限。计数器从 0 计数到 UTIMER_UNT2_TH 值后再次回 0 开始计数。</td></tr></table>

# 11.3.4.8UTIMER_UNT3_THTimer3门限寄存器

地址：0x4001_1864

复位值：0x0

表11.15Timer3门限寄存器UTIMER_UNT3_TH  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td colspan="15">UNT3_TH</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">UNT3_TH</td><td></td></tr><tr><td colspan="16">RW</td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>UNT3_TH</td><td>Timer 3 计数器计数门限。计数器从 0 计数到 UTIMER_UNT3_TH 值后再次回 0 开始计数。</td></tr></table>

# 11.3.4.9UTIMER_UNTO_CNTTimer0计数寄存器

地址：0x4001_1808

复位值：0x0

表11-16Timer0计数寄存器UTIMER_UNTO_CNT  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">UNTO_CNT</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>UNTO_CNT</td><td>Timer 0 计数器当前计数值。写操作可以写入新的计数值。</td></tr></table>

# 11.3.4.10UTIMER_UNT1_CNTTimer1计数寄存器

地址：0x4001_1828

复位值：0x0

表11-17Timer1计数寄存器UTIMER_UNT1_CNT  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">UNT1_CNT</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[S1:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>UNT1_CNT</td><td>Timer 1 计数器当前计数值。写操作可以写入新的计数值。</td></tr></table>

# 11.3.4.11UTIMER_UNT2_CNTTimer2计数寄存器

地址：0x4001_1848

复位值：0x0

表11-18Timer2计数寄存器UTIMER_UNT2_CNT  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>10</td><td>19</td><td>18</td><td>17</td><td>16</td><td></td><td></td></tr><tr><td colspan="15">UNT2_CNT</td><td></td><td></td><td></td></tr><tr><td colspan="15">RW</td><td></td><td></td><td></td></tr><tr><td colspan="2">0</td><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">UNT2_CNT</td><td></td><td></td><td></td></tr><tr><td colspan="2">RW</td><td colspan="14">0</td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>UNT2_CNT</td><td>Timer 2 计数器当前计数值。写操作可以写入新的计数值。</td></tr></table>

# 11.3.4.12UTIMER_UNT3_CNTTimer3计数寄存器

地址：0x4001_1868

复位值：0x0

表11-19Timer3计数寄存器UTIMER_UNT3_CNT  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>10</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td colspan="15">UNT3_CNT</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="14">0</td><td></td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">UNT3_CNT</td><td></td></tr></table>

<table><tr><td>RW</td></tr><tr><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>UNT3_CNT</td><td>Timer3 计数器当前计数值。写操作可以写入新的计数值。</td></tr></table>

11.3.4.13UTIMER_UNTO_CMP0Timer0通道0比较捕获寄存器

地址：0x4001_180C

复位值：0x0

表11- 20Timer0通道0比较捕获寄存器UTIMER_UNTO_CMP0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">UNTO_CMP0</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>UNTO_CMP0</td><td>Timer 0 通道 0 工作在比较模式时，当计数器计数值等于UTIMER_UNTO_CMP0时，发生比较事件。
Timer 0 通道 0 工作在捕获模式时，发生捕获事件时的计数器计数值存入UTIMER_UNTO_CMP0寄存器。</td></tr></table>

11.3.4.14UTIMER_UNTO_CMP1Timer0通道1比较捕获寄存器

地址：0x4001_1810

复位值：0x0

表11- 21Timer0通道1比较捕获寄存器UTIMER_UNTO_CMP1

<table><tr><td colspan="2">UNTO_CMP1</td></tr><tr><td colspan="2">RW</td></tr><tr><td colspan="2">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>UNTO_CMP1</td><td>Timer 0 通道 1 工作在比较模式时，当计数器计数值等于UTIMER_UNTO_CMP1时，发生比较事件。</td></tr></table>

<table><tr><td></td><td></td><td>Timer 0 通道 1 工作在捕获模式时，发生捕获事件时的计数器计数值存入 UTIMER_UNTO_CMP1 寄存器。</td></tr></table>

11.3.4.15UTIMER_UNT1_CMP0Timer1通道0比较捕获寄存器

地址：0x4001_182C

复位值：0x0

<table><tr><td colspan="13">表11-22 Timer 1 通道 0 比较捕获寄存器 UTIMER_UNT1_CMP0</td><td></td><td></td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="13">UNT1_CMP0</td><td></td><td></td><td></td></tr><tr><td colspan="13">RW</td><td></td><td></td><td></td></tr><tr><td colspan="13">0</td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>UNT1_CMP0</td><td>Timer 1 通道 0 工作在比较模式时，当计数器计数值等于 UTIMER_UNT1_CMP0 时，发生比较事件。
Timer 1 通道 0 工作在捕获模式时，发生捕获事件时的计数器计数值存入 UTIMER_UNT1_CMP0 寄存器。</td></tr></table>

11.3.4.16UTIMER_UNT1_CMP1Timer1通道1比较捕获寄存器

地址：0x4001_1830

复位值：0x0

表11- 23Timer1通道1比较捕获寄存器UTIMER_UNT1_CMP1

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">UNT1_CMP1</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>UNT1_CMP1</td><td>Timer 1 通道 1 工作在比较模式时，当计数器计数值等于 UTIMER_UNT1_CMP1 时，发生比较事件。
Timer 1 通道 1 工作在捕获模式时，发生捕获事件时的计数器计数值存入 UTIMER_UNT1_CMP1 寄存器。</td></tr></table>

# 11.3.4.17UTIMER_UNT2CMPOTimer2通道0比较捕获寄存器

地址：0x4001_184C

复位值：0x0

表11-24Timer2通道0比较捕获寄存器UTIMER_UNT2CMP0  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td colspan="16">UNT2_CMP0</td></tr><tr><td colspan="16">RW</td></tr><tr><td colspan="16">0</td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16">UNT2_CMP0</td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="16">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>UNT2_CMP0</td><td>Timer 2 通道 0 工作在比较模式时，当计数器计数值等于 UTM ER_UNT2_CMP0 时，发生比较事件。
Timer 2 通道 0 工作在捕获模式时，发生捕获事件时的计数器计数值存入 UTM ER_UNT2_CMP0 寄存器。</td></tr></table>

11.3.4.18UTIMER_UNT2CMP1Timer2通道1比较捕获寄存器

地址：0x4001_1850

复位值：0x0

表11-25Timer2通道1比较捕获寄存器UTIMER_UNT2CMP1  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>0</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td colspan="16">UNT2_CMP1</td></tr><tr><td colspan="16">RW</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="16">&lt;lcel&gt;</td></tr><tr><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td>&lt;nl&gt;</td></tr><tr><td colspan="16">&lt;lcel&gt;</td></tr><tr><td colspan="15">&lt;lcel&gt;</td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="15">&lt;lcel&gt;</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>UNT2_CMP1</td><td>Timer 2 通道 1 工作在比较模式时，当计数器计数值等于 UTM ER_UNT2_CMP1 时，发生比较事件。
Timer 2 通道 1 工作在捕获模式时，发生捕获事件时的计数器计数值存入 UTM ER_UNT2_CMP1 寄存器。</td></tr></table>

# 11.3.4.19UTIMER_UNT3CMPOTimer3通道0比较捕获寄存器

地址：0x4001_186C

复位值：0x0

表11-26Timer3通道0比较捕获寄存器UTIMER_UNT3CMP0  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td colspan="16">UNT3_CMP0</td></tr><tr><td colspan="16">RW</td></tr><tr><td colspan="16">0</td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16">UNT3_CMP0</td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="16">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>UNT3_CMP0</td><td>Timer 3 通道 0 工作在比较模式时，当计数器计数值等于 UTIMER_UNT3_CMP0 时，发生比较事件。
Timer 3 通道 0 工作在捕获模式时，发生捕获事件时的计数器计数值存入 UTIMER_UNT3_CMP0 寄存器。</td></tr></table>

11.3.4.20UTIMER_UNT3CMP1Timer3通道1比较捕获寄存器

地址：0x4001_1870

复位值：0x0

表11-27Timer3通道1比较捕获寄存器UTIMER_UNT3CMP1  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td colspan="16">UNT3_CMP1</td></tr><tr><td colspan="16">RW</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="16">&lt;lcel&gt;</td></tr><tr><td>&lt;fcel&gt;</td><td>&lt;fcel&gt;</td><td colspan="14">&lt;lcel&gt;</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>UNT3_CMP1</td><td>Timer 3 通道 1 工作在比较模式时，当计数器计数值等于 UTIMER_UNT3_CMP1 时，发生比较事件。</td></tr></table>

<table><tr><td></td><td></td><td>Timer 3 通道 1 工作在捕获模式时，发生捕获事件时的计数器计数值存入 UTIMER_UNT3_CMP1 寄存器。</td></tr></table>

11.3.4.21UTIMER_UNTO_EVTTimer0外部事件选择寄存器

地址：0x4001_1814

复位值：0x0

表11-28Timer0外部事件选择寄存器UTIMER_UNT0_EVT  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="12"></td><td colspan="3">EVT_SRC</td><td></td></tr><tr><td colspan="3">RW</td><td></td></tr><tr><td colspan="3">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:3]</td><td></td><td>未使用</td></tr><tr><td>[2:0]</td><td>EVT_SRC</td><td>Timer0 外部事件选择寄存器，本寄存器需要配合UTIMER_UNTO_CFG[11]使用。U0CFG[11]为高时，根据本寄存器选择触发Timer0计数的事件。
0: MCPWM TADC[2]比较事件
1: MCPWM TADC[3]比较事件
2: TIMER1 通道0比较事件
3: TIMER1 通道1比较事件
4: TIMER2 通道0比较事件
5: TIMER2 通道1比较事件
6: TIMER3 通道0比较事件
7: TIMER3 通道1比较事件</td></tr></table>

11.3.4.22UTIMER_UNT1_EVTTimer1外部事件选择寄存器

地址：0x4001_1834

复位值：0x0

表11-29Timer1外部事件选择寄存器UTIMER_UNT1_EVT  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3" colspan="7"></td><td rowspan="3" colspan="11"></td><td colspan="3">EVT_SRC</td></tr><tr><td colspan="3">RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="3">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:3]</td><td></td><td>未使用</td></tr></table>

<table><tr><td>[2:0]</td><td>EVT_SRC</td><td>Timer1 外部事件选择寄存器，本寄存器需要配合UTIMER_UNT1_CFG[11]使用。UTIMER_UNT1_CFG[11]为高时，根据本寄存器选择触发 Timer1 计数的事件。
0：TIMER0 通道 0 比较事件
1：TIMER0 通道 1 比较事件
2：MCPWM TADC[2]比较事件
3：MCPWM TADC[3]比较事件
4：TIMER2 通道 0 比较事件
5：TIMER2 通道 1 比较事件
6：TIMER3 通道 0 比较事件
7：TIMER3 通道 1 比较事件</td></tr></table>

# 11.3.4.23UTIMER_UNT2_EVTTimer2外部事件选择寄存器

地址：0x4001_1854

复位值：0x0

表11-30Timer2外部事件选择寄存器UTIMER_UNT2_EVT  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:3]</td><td></td><td>未使用</td></tr><tr><td>[2:0]</td><td>EVT_SRC</td><td>Timer2 外部事件选择寄存器，本寄存器需要配合UTIMER_UNT2_CFG[11]使用。UTIMER_UNT2_CFG[11]为高时，根据本寄存器选择触发 Timer2 计数的事件。
0：TIMER0 通道 0 比较事件
1：TIMER0 通道 1 比较事件
2：TIMER1 通道 0 比较事件
3：TIMER1 通道 1 比较事件
4：MCPWM TADC[2]比较事件
5：MCPWM TADC[3]比较事件
6：TIMER3 通道 0 比较事件
7：TIMER3 通道 1 比较事件</td></tr></table>

# 11.3.4.24UTIMER_UNT3_EVTTimer3外部事件选择寄存器

地址：0x4001_1874

复位值：0x0

表11-31Timer3外部事件选择寄存器UTIMER_UNT3_EVT  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[S1:3]</td><td></td><td>未使用</td></tr><tr><td>[2:0]</td><td>EVT_SRC</td><td>Timer3 外部事件选择寄存器，本寄存器需要配合UTIMER_UNT3_CFG[11]使用。UTIMER_UNT3_CFG[11]为高时，根据本寄存器选择触发 Timer3 计数的事件。
0：TIMER0 通道 0 比较事件
1：TIMER0 通道 1 比较事件
2：TIMER1 通道 0 比较事件
3：TIMER1 通道 1 比较事件
4：TIMER2 通道 0 比较事件
5：TIMER2 通道 1 比较事件
6：MCPWM TADC[2]比较事件
7：MCPWM TADC[3]比较事件</td></tr></table>

# 11.3.5 编码器寄存器

Encoder0/1功能完全相同仅寄存器地址分配不同。

11.3.5.1UTIMER_ECDx_CFGEncoderX配置寄存器

UTIMER_ECD0_CFG地址：0x4001_1880

UTIMER_ECD1_CFG地址：0x4001_1890

复位值：0x0

表11-32EncoderX配置寄存器UTIMER_ECDx_CFG  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td>FE_CNT_EN</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td>0</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:11]</td><td></td><td>未使用</td></tr><tr><td>[10]</td><td>FE_CNT_EN</td><td>CCW+SIGN/CCW+CW 两种模式下，是否在下降沿进行计数（上升沿总是计数）</td></tr></table>

<table><tr><td>[9:8]</td><td>MODE</td><td>EncoderX编码器模式选择
00: counting on T1,
01: counting on T1 &amp;amp; T2
以上两种模式都为正交编码信号计数模式
10: CCW+SIGN,符号加脉冲信号计数模式
11: CCW+CW,CCW+CW双脉冲信号计数模式</td></tr><tr><td>[7:0]</td><td></td><td>未使用</td></tr></table>

11.3.5.2UTIMER_ECDx_THEncoderX计数门限寄存器

UTIMER_ECD0_TH地址：0x4001_1884

UTIMER_ECD1_TH地址：0x4001_1894

复位值：0x0

表11-33EncoderX计数门限寄存器UTIMER_ECDx_TH  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">ECD0_TH</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>ECDx_TH</td><td>EncoderX 计数门限 TH。编码器向上计数（增）到 TH 值后，再次向上计数会导致计数器回到 0。编码器向下计数（减）到 0 值后，再次向下计数会导致计数器回到 TH。</td></tr></table>

11.3.5.3UTIMER_ECDxCNTEncoderX计数值寄存器

UTIMER_ECD0_CNT地址：0x4001_1888

UTIMER_ECD1_CNT地址：0x4001_1898

复位值：0x0

表11-34Encoder0计数值寄存器UTIMER_ECD0_CNT  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">ECD0_CNT</td><td></td></tr><tr><td colspan="15">RO</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr></table>

<table><tr><td>[15:0]</td><td>ECDx_CNT</td><td>EncoderX 计数值。</td></tr></table>

# 11.3.6 中断管理寄存器

中断管理寄存器包括中断标志寄存器UTIMER_IF和中断使能寄存器UTIMER_IE。两个寄存器各个比特对应相同的中断。

# 11.3.6.1UTIMER_IE中断使能寄存器

地址：0x4001_18F4

复位值：0x0

表11-35中断使能寄存器UTIMER_IE  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>ENC1_OF_IE</td><td></td><td>ENC1_OF_IE</td><td></td><td>ENC0_OF_IE</td><td></td><td>T3_CH1_IE</td><td></td><td>T3_CH0_IE</td><td></td><td>T2_ZC_IE</td><td></td><td>T1_CH1_IE</td><td></td><td>T1_ZC_IE</td><td></td><td>T0_CH1_IE</td><td></td><td>T0_CH0_IE</td><td></td><td>T0_ZC_IE</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>R</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>ENC1_OF_IE</td><td>Encoder1上溢出中断使能，高电平有效。当Encoder1计数器计数达到计数门限时，上计数事件触发上溢出中断。</td></tr><tr><td>[14]</td><td>ENC1_UF_IE</td><td>Encoder1下溢出中断使能，高电平有效。当Encoder1计数器计数达到0时，下计数事件触发下溢出中断。</td></tr><tr><td>[13]</td><td>ENC0_OF_IE</td><td>Encoder0上溢出中断使能，高电平有效。</td></tr><tr><td>[12]</td><td>ENC0_UF_IE</td><td>Encoder0下溢出中断使能，高电平有效。</td></tr><tr><td>[11]</td><td>T3_CH1_IE</td><td>Timer3通道1比较/捕获中断使能，高电平有效。</td></tr><tr><td>[10]</td><td>T3_CH0_IE</td><td>Timer3通道0比较/捕获中断使能，高电平有效。</td></tr><tr><td>[9]</td><td>T3_ZC_IE</td><td>Timer3计数器过0中断使能，高电平有效。</td></tr><tr><td>[8]</td><td>T2_CH1_IE</td><td>Timer2通道1比较/捕获中断使能，高电平有效。</td></tr><tr><td>[7]</td><td>T2_CH0_IE</td><td>Timer2通道0比较/捕获中断使能，高电平有效。</td></tr><tr><td>[6]</td><td>T2_ZC_IE</td><td>Timer2计数器过0中断使能，高电平有效。</td></tr><tr><td>[5]</td><td>T1_CH1_IE</td><td>Timer1通道1比较/捕获中断使能，高电平有效。</td></tr><tr><td>[4]</td><td>T1_CH0_IE</td><td>Timer1通道0比较/捕获中断使能，高电平有效。</td></tr><tr><td>[3]</td><td>T1_ZC_IE</td><td>Timer1计数器过0中断使能，高电平有效。</td></tr><tr><td>[2]</td><td>T0_CH1_IE</td><td>Timer0通道1比较/捕获中断使能，高电平有效。</td></tr><tr><td>[1]</td><td>T0_CH0_IE</td><td>Timer0通道0比较/捕获中断使能，高电平有效。</td></tr><tr><td>[0]</td><td>T0_ZC_IE</td><td>Timer0计数器过0中断使能，高电平有效。</td></tr></table>

# 11.3.6.2UTIMER_IF中断标志寄存器

地址：0x4001_18F8

复位值：0x0

表11-36中断标志寄存器UTIMER_IF  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>ENC1_OF_IF</td><td>ENC1_OF_IF</td><td>ENC1_OF_IF</td><td>ENC0_OF_IF</td><td>ENC0_OF_IF</td><td>T3_OF_IF</td><td>T3_OF_0_IF</td><td>T3_OF_C_F</td><td>T2_OF_IF</td><td>T2_OF_0_IF</td><td>T2_OF_C_F</td><td>T1_OF_IF</td><td>T1_OF_0_IF</td><td>T1_OF_C_F</td><td>T0_OF_IF</td><td>T0_OF_0_IF</td></tr><tr><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>ENC1_OF_IF</td><td>Encoder1 上溢出中断标志，高电平有效，对此 bit 写 1 可清 0 此 bit。当 Encoder1 计数器计数达到计数门限时，上计数事件触发上溢出中断。</td></tr><tr><td>[14]</td><td>ENC1_OF_IF</td><td>Encoder1 下溢出中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。当 Encoder1 计数器计数达到 0 时，下计数事件触发下溢出中断。</td></tr><tr><td>[13]</td><td>ENC0_OF_IF</td><td>Encoder0 上溢出中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。当 Encoder0 计数器计数达到计数门限时，上计数事件触发上溢出中断。</td></tr><tr><td>[12]</td><td>ENC0_UF_IF</td><td>Encoder0 下溢出中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。当 Encoder0 计数器计数达到 0 时，下计数事件触发下溢出中断。</td></tr><tr><td>[11]</td><td>T3_CH1_IF</td><td>Timer3 通道 1 比较/捕获中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。</td></tr><tr><td>[10]</td><td>T3_CH0_IF</td><td>Timer3 通道 0 比较/捕获中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。</td></tr><tr><td>[9]</td><td>T3_ZC_IF</td><td>Timer3 计数器过 0 中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。</td></tr><tr><td>[8]</td><td>T2_CH1_IF</td><td>Timer2 通道 1 比较/捕获中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。</td></tr><tr><td>[7]</td><td>T2_CH0_IF</td><td>Timer2 通道 0 比较/捕获中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。</td></tr><tr><td>[6]</td><td>T2_ZC_IF</td><td>Timer2 计数器过 0 中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。</td></tr><tr><td>[5]</td><td>T1_CH1_IF</td><td>Timer1 通道 1 比较/捕获中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。</td></tr><tr><td>[4]</td><td>T1_CH0_IF</td><td>Timer1 通道 0 比较/捕获中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。</td></tr><tr><td>[3]</td><td>T1_ZC_IF</td><td>Timer1 计数器过 0 中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。</td></tr><tr><td>[2]</td><td>T0_CH1_IF</td><td>Timer0 通道 1 比较/捕获中断标志。高电平有效，对此 bit 写 1 可清 0</td></tr></table>

<table><tr><td></td><td></td><td>此 bit。</td></tr><tr><td>[1]</td><td>T0_CH0_IF</td><td>Timer0 通道 0 比较/捕获中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。</td></tr><tr><td>[0]</td><td>T0_ZC_IF</td><td>Timer0 计数器过 0 中断标志。高电平有效，对此 bit 写 1 可清 0 此 bit。</td></tr></table>

其中Timer2通道0/1、Timer3通道0/1的比较事件可作为ADC采样触发事件UTimer_T0/UTimer_T1/UTimer_T2/UTimer_T3;

此4个事件与MCPWM产生的MCPWM_T0/MCPWM_T1/MCPWM_T2/MCPWM_T3在ADC内部经过使能控制后分别相或得到4个ADC采样触发事件TADC[0]/TADC[1]/TADC[2]/TADC[3]。

中断标志写1清零，一般不建议用如下  $\mid =$  方式清零，因为  $\mid =$  是先读取中断标志，将对应位改为1再写入清零，如果同时有其他中断标志置位，会被一起清零，而这通常不是软件所期望的。例如，如下写法本意是清零T0_ZC_IF，但如果同时T0_CH0_IF在写入执行前置1了，则软件先读取回UTIMER_IF值为  $0\times 2$  ，然后执行或操作  $0\times 2|0\times 1 = 0\times 3$  ，然后写入，同时对T0_CH0_IF和T0_ZC_IF进行了清零，可能导致Timer少进入一次因捕获而产生的中断。

如果希望清零T0_ZC_IF标志位，应以如下方式，直接对BIT0写1.

# 11.3.7 DMA管理寄存器

中断管理寄存器包括中断标志寄存器IF和中断使能寄存器IE。两个寄存器各个比特对应相同的中断。

# 11.3.7.1UTIMER_REDMA请求使能寄存器

地址：0x4001_18FC

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="4"></td><td rowspan="4"></td><td>T3_CH0_DMA_RE</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>T3_CH0_DMA_RE</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:12]</td><td></td><td>未使用</td></tr></table>

# LKS32MC08x User Manual

<table><tr><td>[11]</td><td>T3_CH1_DMA_RE</td><td>Timer3 通道 1 比较/捕获 DMA 请求使能，高电平有效。</td></tr><tr><td>[10]</td><td>T3_CH0_DMA_RE</td><td>Timer3 通道 0 比较/捕获 DMA 请求使能，高电平有效。</td></tr><tr><td>[9]</td><td>T3_DMA_RE</td><td>Timer3 计数器过 0 DMA 请求使能，高电平有效。</td></tr><tr><td>[8]</td><td>T2_CH1_DMA_RE</td><td>Timer2 通道 1 比较/捕获 DMA 请求使能，高电平有效。</td></tr><tr><td>[7]</td><td>T2_CH0_DMA_RE</td><td>Timer2 通道 0 比较/捕获 DMA 请求使能，高电平有效。</td></tr><tr><td>[6]</td><td>T2_DMA_RE</td><td>Timer2 计数器过 0 DMA 请求使能，高电平有效。</td></tr><tr><td>[5]</td><td>T1_CH1_DMA_RE</td><td>Timer1 通道 1 比较/捕获 DMA 请求使能，高电平有效。</td></tr><tr><td>[4]</td><td>T1_CH0_DMA_RE</td><td>Timer1 通道 0 比较/捕获 DMA 请求使能，高电平有效。</td></tr><tr><td>[3]</td><td>T1_DMA_RE</td><td>Timer1 计数器过 0 DMA 请求使能，高电平有效。</td></tr><tr><td>[2]</td><td>T0_CH1_DMA_RE</td><td>Timer0 通道 1 比较/捕获 DMA 请求使能，高电平有效。</td></tr><tr><td>[1]</td><td>T0_CH0_DMA_RE</td><td>Timer0 通道 0 比较/捕获 DMA 请求使能，高电平有效。</td></tr><tr><td>[0]</td><td>T0_DMA_RE</td><td>Timer0 计数器过 0 DMA 请求使能，高电平有效。</td></tr></table>

# 12HALL信号处理模块

# 12.1综述

芯片共支持3路HALL信号输入。

对于输入的HALL传感器信号，所进行的处理包括：

滤波，消除HALL信号毛刺的影响

捕获，当HALL输入有变化时，记录当前的定时器值，并输出中断

溢出，当HALL信号长时间不发生变化导致计数器溢出时，输出中断

# 12.2 实现说明

# 12.2.1 信号来源

HALL信号来源于GPIO，对于每一路HALL信号，芯片有两个IO可以作为该信号的来源。通过配置GPIO寄存器，用户可以选择将其中一个GPIO的输入信号做为HALL信号使用。

详细管脚位置说明见芯片器件datasheet。

# 12.2.2 工作时钟

12.2.2 工作时钟HALL模块工作频率可调。通过配置HALL_CFG.CLK_DIV寄存器，可以选择系统主时钟的1/2/4/8分频作为HALL模块工作频率，滤波和计数均采用该频率工作。

# 12.2.3 信号滤波

滤波模块主要用于去除HALL信号上的毛刺。

滤波包括两级滤波器：

第一级采用7判5进行滤波，即连续7个采样点中，如果达到超过5个1则输出1，如果达到或超过5个0则输出0，否则输出保持上一次的滤波结果。具体如下图所示：

![](images/b8c1a001117bdb9e13b81788f38158c3c1509c82f8b03088d0e6809add119d8a.jpg)  
图12-17/5滤波模块框图

第二级采用连续滤波，在连续N个采样点中，如全为0则输出0，如全为1则输出1，否则输出保持上一次的滤波结果。

通过配置HALL_CFG.FIL_75可以选择是否使能第一级滤波器。

通过配置HALL_CFG.FIL_LEN可以配置第二级滤波器滤波深度，即连续采样个数。连续采样个数最大为  $2^{15}$ ，滤波时间常数计算公式如下：

$$
\mathrm{T_{fit} = T_{clk} * (HALL\_CFG.FIL\_LEN[14:0] + 1)}
$$

举例，在96MHz工作频率下，周期Tclk是10.4ns，寄存器配置最大为32767，最长滤波宽度为约  $10.4\mathrm{ns}\times 32768\approx 340\mathrm{us}$ 。

通过访问HALL_INFO.FIL_DATA[2:0]可以捕捉滤波后的HALL信号；HALL_INFO.RAW_DATA[2:0]则是滤波前原始HALL输入信号，详见12.3.3。

# 12.2.4 捕获

捕获模块用于测量两次HALL信号变化之间的时间，其核心为一个24位计数器，在96MHz工作频率下，如果Hall时钟进行8分频，最大可以记录约  $2^{\wedge}24^{*}8 / 96\mathrm{e}6 = 1.40\mathrm{s}$  的时间宽度，达到10.42ns的时间分辨率。

HALL_CNT从0开始计数，当发生HALL信号变化时，将此时刻的HALL_CNT值保存到HALL_WIDTH寄存器，将此时刻的HALL信号保存到HALL_INFO.FIL_DATA，输出HALL信号变化中断，HALL_CNT重新从0开始计数。

当计数器计数值达到HALL_TH时，输出HALL计数器溢出中断，计数器重新从0开始计数。

# 12.2.5 中断

捕获、溢出事件触发中断，中断使能控制位位于HALL_CFG.CHG_IE和HALL_CFG.OV_IE，中断标志位位于HALL_INFO.CHG_IF和HALL_INFO.OV_IF。终端标志可以通过对HALL_INFO.CHG_IF和HALL_INFO.OV_IF写1清空。

# 12.2.6 数据流程

12.2.6 数据流程HALL 模块的数据流程如下图所示，FCLK[1]为受 SYS_CLK_FEN 门控控制的系统主时钟，通常为 96MHz 的 PLL 时钟。

![](images/93c94129200f9c65c2e5d8cc37ece94cb57af2ee6dfa0fe5442b861c4257d80f.jpg)  
图12-2数据流程框图

# 12.3 寄存器

# 12.3.1 地址分配

HALL模块寄存器的基地址是0x4001_1000，寄存器列表如下：

表12-1HALL模块寄存器地址分配  

<table><tr><td>名称</td><td>偏移</td><td>描述</td></tr><tr><td>HALL_CFG</td><td>0x00</td><td>HALL 模块配置寄存器</td></tr><tr><td>HALL_INFO</td><td>0x04</td><td>HALL 模块信息寄存器</td></tr><tr><td>HALL_WIDTH</td><td>0x08</td><td>HALL 宽度计数值寄存器</td></tr><tr><td>HALL_TH</td><td>0x0C</td><td>HALL 模块计数器门限值寄存器</td></tr><tr><td>HALL_CNT</td><td>0x10</td><td>HALL 计数寄存器</td></tr></table>

# 12.3.2 HALL_CFGHALL模块配置寄存器

地址：0x4001_1000

复位值：0x0

表12-2HALL模块配置寄存器HALL_CFG  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td rowspan="3"></td><td>SW_IE</td><td>OV_IE</td><td>CHG_IE</td><td rowspan="3"></td><td rowspan="3"></td><td>HALL_EN</td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td>FL_75</td><td rowspan="3"></td><td rowspan="3"></td><td>CLK_DIV</td><td rowspan="3"></td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr></table>

<table><tr><td rowspan="3"></td><td>FIL_LEN_</td></tr><tr><td>RW</td></tr><tr><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31]</td><td></td><td>未使用</td></tr><tr><td>[30]</td><td>SW_IE</td><td>软件触发HALL信号变化中断使能,高电平有效。有效此位后,INFO[18]写1,将手动产生HALL信号变化中断。</td></tr><tr><td>[29]</td><td>OV_IE</td><td>HALL计数器溢出中断使能开关。默认关闭。
1,使能
0,关闭</td></tr><tr><td>[28]</td><td>CHG_IE</td><td>HALL信号变化中断使能开关。默认关闭。
1,使能
0,关闭</td></tr><tr><td>[27:25]</td><td></td><td>未使用</td></tr><tr><td>[24]</td><td>HALL_EN</td><td>HALL模块使能开关。默认关闭。
1,使能
0,关闭</td></tr><tr><td>[23:21]</td><td></td><td>未使用</td></tr><tr><td>[20]</td><td>FIL_75</td><td>7/5滤波开关（连续采样7次，5次值一致）。默认关闭。
1,使能
0,关闭</td></tr><tr><td>[19:18]</td><td></td><td>未使用</td></tr><tr><td>[17:16]</td><td>CLK_DIV</td><td>HALL时钟分频系数
00:不分频
01:2分频
10:4分频
11:8分频</td></tr><tr><td>[15]</td><td></td><td>未使用</td></tr><tr><td>[14:0]</td><td>FIL_LEN</td><td>滤波宽度，低于对应脉冲宽度的信号将被硬件自动过滤掉。滤波宽度的计算公式为[14:0]+1。</td></tr></table>

# 12.3.3 HALL_INFO HALL 模块信息寄存器

地址：0x4001_1004

复位值：0x0

表12-3HALL模块信息寄存器HALL_INFO  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td>SW_IF</td><td>OV_IF</td><td>CHG_IF</td><td></td></tr><tr><td>WO</td><td>RW</td><td>RW</td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td></td></tr></table>

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td></td></tr><tr><td></td></tr><tr><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:19]</td><td></td><td>未使用</td></tr><tr><td>[18]</td><td>SW_IF</td><td>软件触发 HALL 信号变化中断。写 1 触发，自动清零。当 HALL_CFG.SW_IE=1 时，向 SW_IF 写 1 可以触发 CHG_IF 置位。需要使 能 HALL_CFG.CHG_IE，才能产生 HALL 中断。</td></tr><tr><td>[17]</td><td>OV_IF</td><td>HALL 计数器溢出事件标志，写 1 清空</td></tr><tr><td>[16]</td><td>CHG_IF</td><td>HALL 信号变化事件标志，写 1 清空</td></tr><tr><td>[15:11]</td><td></td><td>系统保留，必须写入 0，读出 0</td></tr><tr><td>[10:8]</td><td>RAW_DATA</td><td>HALL 值，未滤波结果</td></tr><tr><td>[7:3]</td><td></td><td>系统保留，必须写入 0，读出 0</td></tr><tr><td>[2:0]</td><td>FLT_DATA</td><td>HALL 值，滤波结果</td></tr></table>

# 12.3.4 HALL_WIDTH HALL 宽度计数值寄存器

地址：0x4001_1008

复位值：0x0

表12-4HALL宽度计数值寄存器HALL_WIDTH  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>0</td><td>19</td><td>18</td><td>17</td><td>16</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3" colspan="8"></td><td colspan="7">CAP_CNT</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="7">RO</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="7">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="2" colspan="8"></td><td colspan="7">CAP_CNT</td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="7">RO</td><td colspan="7">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:24]</td><td></td><td>未使用</td></tr><tr><td>[23:0]</td><td>CAP_CNT</td><td>HALL 宽度计数器值</td></tr></table>

# 12.3.5 HALL_TH HALL 模块计数器门限值寄存器

地址：0x4001_100C

复位值：0x0

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td rowspan="3" colspan="8"></td><td colspan="8">TH</td></tr><tr><td colspan="8">RW</td></tr><tr><td colspan="8">0</td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="8"></td><td colspan="8">TH</td></tr><tr><td colspan="7">RW</td><td></td></tr><tr><td colspan="8">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:24]</td><td></td><td>未使用</td></tr><tr><td>[23:0]</td><td>TH</td><td>HALL 计数器门限值</td></tr></table>

# 12.3.6 HALL_CNT HALL 计数寄存器

地址：0x4001_1010

复位值：0x0

表12-6HALL计数寄存器HALL_CNT  

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>0</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td rowspan="3" colspan="8"></td><td colspan="8">CNT</td></tr><tr><td colspan="8">RW</td></tr><tr><td colspan="8">0</td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:24]</td><td></td><td>未使用</td></tr><tr><td>[23:0]</td><td>CNT</td><td>HALL 计数值，写入任意值可清零</td></tr></table>

# 13 MCPWM

# 13.1 概述

MCPWM 模块，是一个精确控制电机驱动波形输出的模块。

包含一个16位递增计数器，用于提供一个基础周期。计数器的时钟分频有1/2/4/8四种选项，产生的的分频时钟频率分别为96MHz、48MHz、24MHz和12MHz。

包含四组PWM生成模块。

- 可以产生4对（互补信号）不交叠的或8路边沿对齐的（边沿模式）PWM信号；- 支持边沿对齐PWM- 中心对齐PWM- 移相PWM

同时可以产生4路与MCPWM同时基的定时信息，用于触发ADC模块同步采样，进行与MCPWM的联动。

包含一组急停保护模块，用于不依赖CPU软件的处理快速关断MCPWM模块输出。MCPWM模块可输入4路急停信号，其中两路来自芯片IO，两路来自片内比较器的输出。当急停事件发生时（支持有效电平极性选择），把所有MCPWM输出信号复位到规定状态，以避免短路发生。

对急停信号有独立滤波模块。

MCPWM的每个输出IO支持两种控制模式：PWM硬件控制或者软件直接控制（用于EABS软刹车，或BLDC方波换相控制）。

![](images/97e6484644ca91ac1db12243f35ce79770039749b3b83c0f7c105302ce54a8ea.jpg)  
图13-1MCPWM模块框图

为了保证定时精度，通常采用96MHz的时钟作为MCPWM模块工作频率。

# 13.1.1 BaseCounter模块

该模块主要是由一个递增计数器组成，其计数门限值为MCPWM_TH，计数器从t0时刻开始从- TH递增计数，在t1时刻过0点，在t2时刻计数到TH完成一次计数循环，回到- TH，重新开始计数。计数周期为  $(\mathrm{TH}\times 2 + 1)\times$  计数时钟周期。

在t0/t1(本次t0即上一次t2)可产生定时事件中断，MCPWM_IFT0_IF和MCPWM_IFT1_IF将被置位。

可通过寄存器配置MCPWM_TCLK.BASE_CNT_EN控制BaseCounter的启动和停止。

![](images/e0e9159b92100f8b741514b02735f5c8a47d22593642841af65a7ad0de4dfe0f.jpg)  
图13-2BaseCountert0/t1时序

在运行MCPWM模块前，用户一般需将对应的比较门限值MCPWM_TH00~MCWM_TH31，死区寄存器MCPWM_DTH00~MCWM_DTH31以及PWM周期MCPWM_TH配置好。在实际运行过程中，也可动态改变比较门限值和PWM周期寄存器，可通过写MCPWM_UPDATE寄存器实现手动更新，也可以通过配置MCPWM_SDCFG.T1_UPDATE_EN及MCPWM_SDCFG.TO_UPDATE_EN进行硬件自动更新。硬件更新，仅在t0及t1时刻（可配置t0或t1更新和t0t1时刻都更新）才能产生更新事件，硬件把加载寄存器的值载入到实际运行的寄存器中。而更新事件的发生频率可以配置，即每间隔N个t0及t1时刻才发生更新。无论是否发生更新，t0/t1时刻均可产生相应的中断。若硬件把加载寄存器的值到载入实际运行的寄存器后，产生装载中断。

通过配置MCPWM_SDCFG寄存器选择更新发生在t0或者t1或者二者皆可，配置更新间隔数，间隔数为1~16。最频繁的更新配置为更新发生在t0和t1，连续发生。最低速的更新配置为更新发生在t1，每16个t1更新一次。

![](images/c1ec639a67d10ff9358ec77683c3087fc99fd5080108a30183fe49d04fa0f23a.jpg)  
图13-3 MCPWM更新机制

# 13.1.2 Fail信号处理

Fail信号即急停信号，主要用于在出现异常时迅速关断功率管，以免造成不可逆的硬件损毁。该信号处理模块主要是根据实际情况设置急停事件，实现快速关断PWM的输出。有两路fail信号输入MCPWM，即FAIL0和FAIL1，分别可以来自芯片IO MCPWM_BKIN[1:0]或芯片内部比较器的输出CMP[1:0]。

![](images/9c99c13a6e6ae4af93f1f194e5a5c58bf1d8003d7de2ee3d55616f2a8106b774.jpg)  
图13-4 MCPWM FAIL逻辑示意图

Filter滤波模块的时钟，来自系统主时钟MCLK的门控时钟FCLK[3]，并经过两级分频，第一级分频由MCPWM_TCLK.CLK_DIV控制，进行1/2/4/8倍分频。第二级分频可实现1~16倍的分频，如果Fail信号来自MCPWM_BKIN[1:0]则使用MCPWM_TCLK.IO_FLT_CLKDIV[3:0]作为第二级的分频系数；如果Fail信号来自芯片内部比较器输出，则使用MCPWM_TCLK.CMP_FLT_CLKDIV[3:0]作为第二级的分频系数，如图13- 5所示。

MCPWM 模块使用分频后的时钟进行 Fail 信号滤波，滤波宽度固定为 16 个周期，即输入信号必须保持至少 16 个时钟（两级分频后的时钟）周期稳定后，硬件才判定其为有效输入信号。滤波时间常数的公式为，其中  $\mathbf{T}_{\mathrm{MCLK}}$  为 MCLK/FCLK[3] 的时钟周期，96MHz 对应 10.4ns。MCPWM_TCLKFLT_CLKDIV 根据配置情况可能是 MCPWM_TCLK.IOFLT_CLKDIV 或 MCPWM_TCLK.CMPFLT_CLKDIV。

![](images/1dd397f90e8afe6a15686bb22be9d6021f29d59615c11c16a2f85fdb5a744806.jpg)  
图 13-5 MCPWM Fail 信号滤波时钟生成逻辑

一旦发生 Fail 事件，即

图 13- 4 最终输出 Fail 信号，硬件将 IO 输出强制变为 MCPWM_FAIL.CHxN_DEFAULT 和 MCPWM_FAIL.CHxP_DEFAULT 寄存器所指定的故障缺省值，此时 MCPWM_FAIL.CHxN_DEFAULT 和 MCPWM_FAIL.CHxP_DEFAULT 的值直接输出到 IO 口，不再受到 MCPWM_FAIL.FAIL.POL 等极性控制的影响。

来自比较器的 FAIL 信号为模拟比较器输出的原始信号，未经过比较器数字接口模块的滤波处理，但是可以被 MCPWM 的通道信号进行开窗控制，开窗控制设置见比较器数字接口模块。FAIL 信号进入 MCPWM 模块后，可以通过设置 MCPWM_TCLK 进行滤波。

# 13.1.3 MCPWM 特殊输出状态

电机控制中经常会用到全零和全 1 输出状态，以下互补模式设置可以得到期望的输出。

1. 如果  $\mathrm{THn0}\geq \mathrm{THn1}$  ，芯片处于恒0状态（  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  关闭，  $\mathrm{CH}< \mathrm{n} > \mathrm{N}$  开启)，无死区2.如果  $\mathrm{THn0 = -TH}$  ，  $\mathrm{THn1 = TH}$  ，芯片处于恒1状态（  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  开启，  $\mathrm{CH}< \mathrm{n} > \mathrm{N}$  关闭)，无死区

# 13.1.4 IO DRIVER 模块

该模块根据实际 MCPWM 的寄存器配置情况，将 IO 设置到相应电平。IO Driver 模块的整体数据流程图如下：

![](images/ce88cc7c6e8ac740c3043c62e5027ba26ba21a4a43cd3f1c7b9b2dcd7569914d.jpg)  
图13-6 IO Driver 模块数据流程图

# 13.1.4.1 MCPWM波形输出-中心对齐模式

4个MCPWM IO Driver采用独立的控制门限，独立死区宽度（每一对互补IO的死区需要独立配置，即4个死区配置寄存器)，共享数据更新事件。

采用  $\mathrm{TH}< \mathrm{n} > 0$  和  $\mathrm{TH}< \mathrm{n} > 1$  控制第  $< n>$  个MCPWMIO的启动、关闭动作，n为  $1 / 2 / 3 / 4$  0

当计数器CNT值向上计数达到  $\mathrm{TH}< \mathrm{n} > 0$  时，在t3时刻关闭  $\mathrm{CH}< \mathrm{n} > \mathrm{N}$  ，经过死区延时DTH0，打开  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  0

当计数器CNT值向上计数达到  $\mathrm{TH}< \mathrm{n} > 1$  时，在t4时刻关闭  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  ，经过死区延时DTH1，打开  $\mathrm{CH}< \mathrm{n} > \mathrm{N}$  0

采用独立的启动和关闭时间控制，可以提供相位控制的能力。

死区延时保证  $\mathrm{CH}< \mathrm{n} > \mathrm{P} / \mathrm{CH}< \mathrm{n} > \mathrm{N}$  不会同时为高，避免短路发生。

t3/t4时刻均会产生相应中断。

![](images/16824c81201220c5994cc45a335ac85d61a603b38bac7c2b39191437146cc6a2.jpg)  
图13-7 MCPWM时序  $\mathrm{TH}< \mathrm{n} > 0$  和  $\mathrm{TH}< \mathrm{n} > 1$  -互补模式

13.1.4.2 MCPWM波形控制-中心对齐推挽模式

互补推挽模式。第一个周期内，在t3时刻  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  置1，在t4时刻，  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  变低。第二个周期内，在t3时刻  $\mathrm{CH}< \mathrm{n} > \mathrm{N}$  置1，在t4时刻，  $\mathrm{CH}< \mathrm{n} > \mathrm{N}$  变低。

t3/t4均会产生相应中断。

![](images/c0fc9ad2c55e7c32b6b85362a9a71695419c8862143533484713508d2581e848.jpg)  
图13-8 MCPWM时序  $\mathrm{TH}< \mathrm{n} > 0$  和  $\mathrm{TH}< \mathrm{n} > 1$  -互补模式

13.1.4.3 MCPWM波形输出-边沿对齐模式

边沿对齐模式中，在t0时刻  $\mathrm{CH}< \mathrm{n} > \mathrm{P} / \mathrm{CH}< \mathrm{n} > \mathrm{N}$  同时置0，在t3时刻，  $\mathrm{CH}< \mathrm{n} > \mathrm{N}$  变高，在t4时刻，  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  变高。

t3/t4均会产生相应中断。

边沿对齐模式下，  $\mathrm{CH}< \mathrm{n} > \mathrm{P} / \mathrm{CH}< \mathrm{n} > \mathrm{N}$  无需死区保护。

![](images/f78ca616ba3ba1e160ba75f7710f4e654c33e74f080443a4870f660c0d243e97.jpg)  
图13-9 MCPWM时序边沿对齐模式

13.1.4.4 MCPWM波形控制- 边沿对齐推挽模式

边沿对齐推挽模式。第一个周期内，在t0时刻  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  置1，在t3时刻，  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  变低。第二个周期内，在t0时刻  $\mathrm{CH}< \mathrm{n} > \mathrm{N}$  置1，在t3时刻，  $\mathrm{CH}< \mathrm{n} > \mathrm{N}$  变低。

t0/t3均会产生相应中断。

![](images/fa53d2f6571b3e713eee3c7ff96ceed3eba264c0c64cced7c0ea8fa3c5c2260a.jpg)  
图13-10 MCPWM时序  $\mathrm{TH}< \mathrm{n} > 0$  和  $\mathrm{TH}< \mathrm{n} > 1$  边沿对齐推挽模式

# 13.1.4.5 MCPWMIO死区控制

13.1.4.5 MCPWMIO死区控制MCPWMIO是一对互斥控制信号  $\mathrm{CH}< \mathrm{n} > \mathrm{P} / \mathrm{CH}< \mathrm{n} > \mathrm{N}$ ，控制如下图所示的电路，当  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  为高  $/\mathrm{CH}< \mathrm{n} > \mathrm{N}$  为低时，Vout输出高（VDD）；当  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  为低  $/\mathrm{CH}< \mathrm{n} > \mathrm{N}$  为高时，Vout输出低（VSS）；当  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  为高  $/\mathrm{CH}< \mathrm{n} > \mathrm{N}$  为高时，Vout输出不确定，但是会产生VDD到VSS的短路；当  $\mathrm{CH}< \mathrm{n} > \mathrm{P}$  为低  $/\mathrm{CH}< \mathrm{n}>$  为低时，Vout输出不确定。必须避免  $\mathrm{CH}< \mathrm{n} > \mathrm{P} / \mathrm{CH}< \mathrm{n} > \mathrm{N}$  同时为高的情况，死区的引入，可以有效避免VDD到VSS的短路。四组MCPWMIO的死区宽度可独立调整。对于互补模式MCPWMIO自动插入死区。对于边沿对齐模式，MCPWMIO无死区。

在IODriver模块中增加  $\mathrm{CH}< \mathrm{n} > \mathrm{P} / \mathrm{CH}< \mathrm{n} > \mathrm{N}$  冲突检测，发生冲突时，自动将IO拉低，同时给出错误中断（中断保持，直到CPU写0)。

MCPWMIO也可通过软件配置的方式输出，此时，死区控制通过软件实现，如果PWM模式为互补，仍然由硬件保证不同时为高或者为低。

$\mathrm{CH}< \mathrm{n} > \mathrm{P} / \mathrm{CH}< \mathrm{n} > \mathrm{N}$  ，在IO上可以互换。

![](images/7fbc6c1e3bfcb4eacef4dd45de617641d2895b0e4edbe00ca994a6420c79225e.jpg)  
图13-11MCPWMIO控制示意图

# 13.1.4.6MCPWMIO极性设置

13.1.4.6 MCPWMIO极性设置CH<n>P/CH<n>N的有效电平可以配置为高有效/低有效，每个IO的有效电平单独可配。CH<n>P/CH<n>N输出到IO的位置通过软件配置可以互换。

# 13.1.4.7MCPWMIO自动保护

当发生急停事件（Fail事件），应立刻将  $\mathrm{CH}< \mathrm{n} > \mathrm{P} / \mathrm{CH}< \mathrm{n} > \mathrm{N}$  自动切换到关闭状态。需要注意关闭电平配置（MCPWM_FAIL.CHxN_DEFAULT和MCPWM_FAIL.CHxP_DEFAULT控制默认电平)。

芯片正常工作后，IO默认输出的电平是寄存器MCPWM_FAIL.CHxN_DEFAULT和MCPWM_FAIL.CHxP_DEFAULT指定值，当用户配置完毕，MCPWM正常工作后，配置MCPWM_FAIL.MCPWM_OE（即MOE）为1，IO输出电平受到MCPWMIO模块控制。

当发生Fail短路状况时，硬件立即切换到IO默认输出电平。当芯片调试中，CPU Halt时，PWM停止输出，输出FAIL[15:8]的值。

# 13.1.5 ADCTriggerTimer模块

13.1.5 ADC Trigger Timer 模块MCPWM 可以提供 ADC 采样控制。当计数器计数到 MCPWM_TMR0/ MCPWM_TMR1/ MCPWM_TMR2/ MCPWM_TMR3 时，可产生定时事件，触发 ADC 采样。该触发信号可同时输出到 GPIO，便于调试之用。输出的具体 GPIO，参见对应器件的 datasheet。

# 13.1.6 MCPWM主要事件列表

MCPWM模块，计数器阀值同对应事件如下表所述

表13-1MCPWM计数器阀值与事件对应表  

<table><tr><td>T0</td><td>-MCPWM_TH</td></tr><tr><td>T1</td><td>0</td></tr><tr><td>TI00[0]</td><td>MCPWM_TH00</td></tr><tr><td>TI00[1]</td><td>MCPWM_TH01</td></tr><tr><td>TI01[0]</td><td>MCPWM_TH10</td></tr><tr><td>TI01[1]</td><td>MCPWM_TH11</td></tr><tr><td>TI02[0]</td><td>MCPWM_TH20</td></tr><tr><td>TI02[1]</td><td>MCPWM_TH21</td></tr><tr><td>TI03[0]</td><td>MCPWM_TH30</td></tr><tr><td>TI03[1]</td><td>MCPWM_TH31</td></tr><tr><td>TADC[0]</td><td>MCPWM_TMR0</td></tr><tr><td>TADC[1]</td><td>MCPWM_TMR1</td></tr><tr><td>TADC[2]</td><td>MCPWM_TMR2</td></tr><tr><td>TADC[3]</td><td>MCPWM_TMR3</td></tr></table>

# 13.2 寄存器

# 13.2.1 地址分配

MCPWM模块寄存器的基地址是0x4001_1C00，寄存器列表如下：

表13-2MCPWM模块寄存器列表  

<table><tr><td>名称</td><td>偏移地址</td><td>说明</td></tr><tr><td>MCPWM_TH00</td><td>0x00</td><td>MCPWM CH0_P 比较门限值寄存器</td></tr><tr><td>MCPWM_TH01</td><td>0x04</td><td>MCPWM CH0_N 比较门限值寄存器</td></tr><tr><td>MCPWM_TH10</td><td>0x08</td><td>MCPWM CH1_P 比较门限值寄存器</td></tr><tr><td>MCPWM_TH11</td><td>0x0C</td><td>MCPWM CH1_N 比较门限值寄存器</td></tr><tr><td>MCPWM_TH20</td><td>0x10</td><td>MCPWM CH2_P 比较门限值寄存器</td></tr></table>

<table><tr><td>MCPWM_TH21</td><td>0x14</td><td>MCPWM CH2_N 比较门限值寄存器</td></tr><tr><td>MCPWM_TH30</td><td>0x18</td><td>MCPWM CH3_P 比较门限值寄存器</td></tr><tr><td>MCPWM_TH31</td><td>0x1C</td><td>MCPWM CH3_N 比较门限值寄存器</td></tr><tr><td>MCPWM_TMR0</td><td>0x20</td><td>ADC 采样定时器比较门限 0 寄存器</td></tr><tr><td>MCPWM_TMR1</td><td>0x24</td><td>ADC 采样定时器比较门限 1 寄存器</td></tr><tr><td>MCPWM_TMR2</td><td>0x28</td><td>ADC 采样定时器比较门限 2 寄存器</td></tr><tr><td>MCPWM_TMR3</td><td>0x2C</td><td>ADC 采样定时器比较门限 3 寄存器</td></tr><tr><td>MCPWM_TH</td><td>0x30</td><td>MCPWM 门限值寄存器</td></tr><tr><td>MCPWM_UPDATE</td><td>0x34</td><td>MCPWM 加载控制寄存器</td></tr><tr><td>MCPWM_IE</td><td>0x38</td><td>MCPWM 中断控制寄存器</td></tr><tr><td>MCPWM_IF</td><td>0x3C</td><td>MCPWM 中断标志位寄存器</td></tr><tr><td>MCPWM_EIE</td><td>0x40</td><td>MCPWM 异常中断控制寄存器</td></tr><tr><td>MCPWM_EIF</td><td>0x44</td><td>MCPWM 异常中断标志位寄存器</td></tr><tr><td>MCPWM_RE</td><td>0x48</td><td>MCPWM DMA 请求使能寄存器</td></tr><tr><td>MCPWM_PP</td><td>0x4C</td><td>MCPWM 推挽模式使能寄存器</td></tr><tr><td>MCPWM_IO01</td><td>0x50</td><td>MCPWM IO01 控制寄存器</td></tr><tr><td>MCPWM_IO23</td><td>0x54</td><td>MCPWM IO23 控制寄存器</td></tr><tr><td>MCPWM_SDCFG</td><td>0x58</td><td>MCPWM 加载配置寄存器</td></tr><tr><td>MCPWM_TCLK</td><td>0x60</td><td>MCPWM 时钟分频控制寄存器</td></tr><tr><td>MCPWM_FAIL</td><td>0x64</td><td>MCPWM 短路控制寄存器</td></tr><tr><td>MCPWM_PRT</td><td>0x74</td><td>MCPWM 保护寄存器</td></tr><tr><td>MCPWM_CNT</td><td>0x78</td><td>MCPWM 计数器寄存器</td></tr><tr><td>MCPWM_DTH00</td><td>0x80</td><td>MCPWM CH0 N 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH01</td><td>0x84</td><td>MCPWM CH0 P 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH10</td><td>0x88</td><td>MCPWM CH1 N 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH11</td><td>0x8C</td><td>MCPWM CH1 P 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH20</td><td>0x90</td><td>MCPWM CH2 N 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH21</td><td>0x94</td><td>MCPWM CH2 P 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH30</td><td>0x98</td><td>MCPWM CH3 N 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH31</td><td>0x9C</td><td>MCPWM CH3 P 通道死区宽度控制寄存器</td></tr></table>

13-3受MCPWM_PRT保护的寄存器  

<table><tr><td>名称</td><td>偏移地址</td><td>说明</td></tr><tr><td>MCPWM_TH</td><td>0x30</td><td>MCPWM 门限值寄存器</td></tr><tr><td>MCPWM_IE</td><td>0x38</td><td>MCPWM 中断控制寄存器</td></tr><tr><td>MCPWM_EIE</td><td>0x40</td><td>MCPWM 异常中断控制寄存器</td></tr><tr><td>MCPWM_RE</td><td>0x48</td><td>MCPWM DMA 请求使能寄存器</td></tr><tr><td>MCPWM_PP</td><td>0x4C</td><td>MCPWM 推挽模式使能寄存器</td></tr><tr><td>MCPWM_IO01</td><td>0x50</td><td>MCPWM IO01 控制寄存器</td></tr><tr><td>MCPwm_ID023</td><td>0x54</td><td>MCPWM IO023 控制寄存器</td></tr><tr><td>MCPWM_SDCFG</td><td>0x58</td><td>MCPWM 加载配置寄存器</td></tr><tr><td>MCPWM_TCLK</td><td>0x60</td><td>MCPWM 时钟分频控制寄存器</td></tr></table>

<table><tr><td>MCPWM_FAIL</td><td>0x64</td><td>MCPWM 短路控制寄存器</td></tr><tr><td>MCPWM_DTH00</td><td>0x80</td><td>MCPWM CH0 N 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH01</td><td>0x84</td><td>MCPWM CH0 P 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH10</td><td>0x88</td><td>MCPWM CH1 N 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH11</td><td>0x8C</td><td>MCPWM CH1 P 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH20</td><td>0x90</td><td>MCPWM CH2 N 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH21</td><td>0x94</td><td>MCPWM CH2 P 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH30</td><td>0x98</td><td>MCPWM CH3 N 通道死区宽度控制寄存器</td></tr><tr><td>MCPWM_DTH31</td><td>0x9C</td><td>MCPWM CH3 P 通道死区宽度控制寄存器</td></tr></table>

表13-4存在影子寄存器的寄存器  

<table><tr><td>名称</td><td>偏移地址</td><td>说明</td></tr><tr><td>MCPWM_TH00</td><td>0x00</td><td>MCPWM CH0_P 比较门限值寄存器</td></tr><tr><td>MCPWM_TH01</td><td>0x04</td><td>MCPWM CH0_N 比较门限值寄存器</td></tr><tr><td>MCPWM_TH10</td><td>0x08</td><td>MCPWM CH1_P 比较门限值寄存器</td></tr><tr><td>MCPWM_TH11</td><td>0x0C</td><td>MCPWM CH1_N 比较门限值寄存器</td></tr><tr><td>MCPWM_TH20</td><td>0x10</td><td>MCPWM CH2_P 比较门限值寄存器</td></tr><tr><td>MCPWM_TH21</td><td>0x14</td><td>MCPWM CH2_N 比较门限值寄存器</td></tr><tr><td>MCPWM_TH30</td><td>0x18</td><td>MCPWM CH3_P 比较门限值寄存器</td></tr><tr><td>MCPWM_TH31</td><td>0x1C</td><td>MCPWM CH3_N 比较门限值寄存器</td></tr><tr><td>MCPWM_TMR0</td><td>0x20</td><td>ADC 采样定时器比较门限 0 寄存器</td></tr><tr><td>MCPWM_TMR1</td><td>0x24</td><td>ADC 采样定时器比较门限 1 寄存器</td></tr><tr><td>MCPWM_TMR2</td><td>0x28</td><td>ADC 采样定时器比较门限 2 寄存器</td></tr><tr><td>MCPWM_TMR3</td><td>0x2C</td><td>ADC 采样定时器比较门限 3 寄存器</td></tr><tr><td>MCPWM_TH</td><td>0x30</td><td>MCPWM 门限值寄存器</td></tr></table>

# 13.2.2 MCPWM_TH00

无写保护的寄存器

地址：0x4001_1C00

复位值：0x0

表13-5MCPWM_TH00配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16">TH00</td></tr><tr><td colspan="16">RW</td></tr><tr><td colspan="16">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr></table>

<table><tr><td>[15:0]</td><td>TH00</td><td>MCPWM CH0_P 比较门限值，16 位有符号数；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.3 MCPWM_TH01

无写保护的寄存器

地址：0x4001_1C04

复位值：0x0

表13-6MCPWM_TH01配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">TH01</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>TH01</td><td>MCPWM CH0_N 比较门限值，16 位有符号数；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.4 MCPWM_TH10

无写保护的寄存器

地址：0x4001_1C08

复位值：0x0

表13-7MCPWM_TH10配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">TH10</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>TH10</td><td>MCPWM CH1_P 比较门限值，16 位有符号数；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.5 MCPWM_TH11

无写保护的寄存器

地址：0x4001_1C0C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">TH11</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>TH11</td><td>MCPWM CH1_N 比较门限值，16 位有符号数；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.6 MCPWM_TH20

无写保护的寄存器

地址：0x4001_1C10

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">TH20</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>TH20</td><td>MCPWM CH2_P 比较门限值，16 位有符号数；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.7 MCPWM_TH21

无写保护的寄存器

地址：0x4001_1C14

复位值：0x0

<table><tr><td colspan="13">表13-10 MCPWM_TH21配置寄存器</td><td></td><td></td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="13">TH21</td><td></td><td></td><td></td></tr><tr><td colspan="13">RW</td><td></td><td></td><td></td></tr><tr><td colspan="13">0</td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>TH21</td><td>MCPWM CH2_N 比较门限值，16 位有符号数；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.8 MCPWM_TH30

无写保护的寄存器

地址：0x4001_1C18

复位值：0x0

表13-11MCPWM_TH30配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="14">TH30</td><td></td><td></td></tr><tr><td colspan="14">RW</td><td></td><td></td></tr><tr><td colspan="14">0</td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>TH30</td><td>MCPWM CH3_P 比较门限值，16 位有符号数；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.9 MCPWM_TH31

无写保护的寄存器

地址：0x4001_1C1C

复位值：0x0

表13-12MCPWM_TH31配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="14">TH31</td><td></td><td></td></tr><tr><td colspan="14">RW</td><td></td><td></td></tr><tr><td colspan="4">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>TH31</td><td>MCPWM CH3_N 比较门限值，16 位有符号数；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.10 MCPWM_TMR0

无写保护的寄存器

地址：0x4001_1C20

复位值：0x0

表13-13MCPWM_TMR0配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">TMRO</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>TMR0</td><td>ADC 采样定时器比较门限 0 寄存器，16 位有符号数；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.11 MCPWM_TMR1

无写保护的寄存器

地址：0x4001_1C24

复位值：0x0

表13-14MCPWM_TMR1配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">TMR1</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>TMR1</td><td>ADC 采样定时器比较门限 1 寄存器，16 位有符号数；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.12 MCPWM_TMR2

无写保护的寄存器

地址：0x4001_1C28

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">TMR2</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>TMR2</td><td>ADC 采样定时器比较门限 2 寄存器，16 位有符号数；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.13 MCPWM_TMR3

无写保护的寄存器

地址：0x4001_1C2C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">TMR3</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>TMR3</td><td>ADC 采样定时器比较门限 3 寄存器，16 位有符号数；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.14 MCPWM_TH

写保护的寄存器

地址：0x4001_1C30

复位值：0x0

表13-17MCPWM_TH配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:15]</td><td></td><td>未使用</td></tr><tr><td>[14:0]</td><td>TH</td><td>MCPWM 计数器门限值，15 位无符号数，MCPWM 实际运行系统中的计数器从-TH 计数到 TH；发生更新事件后，本寄存器加载到 MCPWM 实际运行系统中。</td></tr></table>

# 13.2.15 MCPWM_UPDATE

无写保护的寄存器

地址：0x4001_1C34

复位值：0x0

表13-18MCPWM_UPDATE配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3"></td><td>TH_UPDATE</td><td>TMR3_UPDATE</td><td>TMR2_UPDATE</td><td>TMR1_UPDATE</td><td>TMR0_UPDATE</td><td>TH31_UPDATE</td><td>TH30_UPDATE</td><td>TH21_UPDATE</td><td>TH20_UPDATE</td><td>TH11_UPDATE</td><td>TH10_UPDATE</td><td>TH01_UPDATE</td><td>TH00_UPDATE</td><td></td><td></td></tr><tr><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:13]</td><td></td><td>未使用</td></tr><tr><td>[12]</td><td>TH_UPDATE</td><td>手动将加载 MCPWM_TH 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr><tr><td>[11]</td><td>TMR3_UPDATE</td><td>手动将加载 MCPWM_TMR3 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr><tr><td>[10]</td><td>TMR2_UPDATE</td><td>手动将加载 MCPWM_TMR2 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr><tr><td>[9]</td><td>TMR1_UPDATE</td><td>手动将加载 MCPWM_TMR1 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr><tr><td>[8]</td><td>TMR0_UPDATE</td><td>手动将加载 MCPWM_TMR0 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr></table>

<table><tr><td>[7]</td><td>TH31_UPDATE</td><td>手动将加载 MCPWM_TH31 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr><tr><td>[6]</td><td>TH30_UPDATE</td><td>手动将加载 MCPWM_TH30 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr><tr><td>[5]</td><td>TH21_UPDATE</td><td>手动将加载 MCPWM_TH21 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr><tr><td>[4]</td><td>TH20_UPDATE</td><td>手动将加载 MCPWM_TH20 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr><tr><td>[3]</td><td>TH11_UPDATE</td><td>手动将加载 MCPWM_TH11 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr><tr><td>[2]</td><td>TH10_UPDATE</td><td>手动将加载 MCPWM_TH10 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr><tr><td>[1]</td><td>TH01_UPDATE</td><td>手动将加载 MCPWM_TH01 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr><tr><td>[0]</td><td>TH00_UPDATE</td><td>手动将加载 MCPWM_TH00 寄存器的内容到 MCPWM 运行系统中。
1：加载；0：不加载。</td></tr></table>

向MCPWM_UPDATE对应位写1可以触发寄存器值从预装载寄存器写入影子寄存器，MCPWM_UPDATE写入后自动清零。每写1一次，进行一次软件/手动触发。

# 13.2.16 MCPWM_IE

写保护的寄存器

地址：0x4001_1C38

复位值：0x0

表13-19MCPWM_IE配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3"></td><td>SHADE_IE</td><td>TMR3_IE</td><td></td><td>TMR2_IE</td><td>TMR1_IE</td><td></td><td>TMR0_IE</td><td></td><td>TMR1_IE</td><td></td><td>TMR0_IE</td><td></td><td>TMR1_IE</td><td></td><td>TMR0_IE</td><td></td><td>TLIE</td><td></td><td>TOIE</td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:15]</td><td></td><td>未使用</td></tr><tr><td>[14]</td><td>SHADE_IE</td><td>MCPWM_TH/MCPWM_TH00~MCPWM_TH31/MCPWM_TMR0~MCPWM_TMR3 等寄存器更新到 MCPWM 实际运行系统的中断源使能。
1，使能；0，关闭。</td></tr><tr><td>[13]</td><td>TMR3_IE</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TMR3 中断源使能。
1，使能；0，关闭。</td></tr><tr><td>[12]</td><td>TMR2_IE</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TMR2 中断源使能。
1，使能；0，关闭。</td></tr><tr><td>[11]</td><td>TMR1_IE</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TMR1 中断源使能。</td></tr></table>

<table><tr><td></td><td></td><td>1，使能；0，关闭。</td></tr><tr><td>[10]</td><td>TMR0_IE</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TMR0 中断源使能。1，使能；0，关闭。</td></tr><tr><td>[9]</td><td>TH31_IE</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH31 中断源使能。1，使能；0，关闭。</td></tr><tr><td>[8]</td><td>TH30_IE</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH30 中断源使能。1，使能；0，关闭。</td></tr><tr><td>[7]</td><td>TH21_IE</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH21 中断源使能。1，使能；0，关闭。</td></tr><tr><td>[6]</td><td>TH20_IE</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH20 中断源使能。1，使能；0，关闭。</td></tr><tr><td>[5]</td><td>TH11_IE</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH11 中断源使能。1，使能；0，关闭。</td></tr><tr><td>[4]</td><td>TH10_IE</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH10 中断源使能。1，使能；0，关闭。</td></tr><tr><td>[3]</td><td>TH01_IE</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH01 中断源使能。1，使能；0，关闭。</td></tr><tr><td>[2]</td><td>TH00_IE</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH00 中断源使能。1，使能；0，关闭。</td></tr><tr><td>[1]</td><td>T1_IE</td><td>t1 事件，计数器的计数值到达 0 中断源使能。1，使能；0，关闭。</td></tr><tr><td>[0]</td><td>T0_IE</td><td>t0 事件，计数器的计数值回到 MCPWM_TH 中断源使能。1，使能；0，关闭。</td></tr></table>

# 13.2.17 MCPWM_IF

无写保护的寄存器

地址：0x4001_1C3C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3"></td><td>HADE_IF</td><td>TMR3_IF</td><td>TMR2_IF</td><td>TMR1_IF</td><td>TMRO_IF</td><td>TH31_IF</td><td>TH30_IF</td><td>TH21_IF</td><td>TH20_IF</td><td>TH11_IF</td><td>TH02_IF</td><td>TH01_IF</td><td>TH00_IF</td><td>TL1F</td><td>TO1F</td></tr><tr><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:15]</td><td></td><td>未使用</td></tr><tr><td>[14]</td><td>SHADE_IF</td><td>MCPWM_TH/MCPWM_TH00~MCPWM_TH31/MCPWM_TMR0~MCPWM_TMR3 等寄存器更新到 MCPWM 实际运行系统的中断源事件。</td></tr></table>

<table><tr><td></td><td></td><td>1，发生；0，没发生。写1清零。</td></tr><tr><td>[13]</td><td>TMR3_IF</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TMR3 中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[12]</td><td>TMR2_IF</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TMR2 中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[11]</td><td>TMR1_IF</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TMR1 中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[10]</td><td>TMR0_IF</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TMR0 中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[9]</td><td>TH31_IF</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH31 中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[8]</td><td>TH30_IF</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH30 中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[7]</td><td>TH21_IF</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH21 中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[6]</td><td>TH20_IF</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH20 中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[5]</td><td>TH11_IF</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH11 中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[4]</td><td>TH10_IF</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH10 中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[3]</td><td>TH01_IF</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH01 中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[2]</td><td>TH00_IF</td><td>MCPWM 实际运行系统中计数器的计数值等于 MCPWM_TH00 中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[1]</td><td>T1_IF</td><td>t1 事件，计数器的计数值到达0中断源事件。1，发生；0，没发生。写1清零。</td></tr><tr><td>[0]</td><td>T0_IF</td><td>t0 事件，计数器的计数值回到 MCPWM_TH 中断源事件。1，发生；0，没发生。写1清零。</td></tr></table>

# 13.2.18 MCPWM_EIE

写保护的寄存器

地址：0x4001_1C40

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>CH3_SHORT_IE</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>CH2_SHORT_IE</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>CH1_SHORT_IE</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>CH0_SHORT_IE</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>RW</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>RW</td></tr></table>

<table><tr><td></td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:6]</td><td></td><td>未使用</td></tr><tr><td>[5]</td><td>FAIL1_IE</td><td>FAIL1 中断源使能。1，使能；0，关闭。</td></tr><tr><td>[4]</td><td>FAIL0_IE</td><td>FAIL0 中断源使能。1，使能；0，关闭。</td></tr><tr><td>[3]</td><td>CH3_SHORT_IE</td><td>MCPWM CH3_P 和 CH3_N 同时有效，中断源使能。1，使能；0，关闭。</td></tr><tr><td>[2]</td><td>CH2_SHORT_IE</td><td>MCPWM CH2_P 和 CH2_N 同时有效，中断源使能。1，使能；0，关闭。</td></tr><tr><td>[1]</td><td>CH1_SHORT_IE</td><td>MCPWM CH1_P 和 CH1_N 同时有效，中断源使能。1，使能；0，关闭。</td></tr><tr><td>[0]</td><td>CH0_SHORT_IE</td><td>MCPWM CH0_P 和 CH0_N 同时有效，中断源使能。1，使能；0，关闭。</td></tr></table>

# 13.2.19 MCPWM_EIF

无写保护的寄存器

地址：0x4001_1C44复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td>FAIL1_IF</td><td>FAIL0_IF</td><td>CH3_SHORT_IF</td><td>CH2_SHORT_IF</td><td>CH1_SHORT_IF</td><td>CH0_SHORT_IF</td><td></td><td></td><td></td><td></td></tr><tr><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td>RW1C</td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:6]</td><td></td><td>未使用</td></tr><tr><td>[5]</td><td>FAIL1_IF</td><td>FAIL1 中断源事件。1，发生；0，没发生。写 1 清零。</td></tr><tr><td>[4]</td><td>FAIL0_IF</td><td>FAIL0 中断源事件。1，发生；0，没发生。写 1 清零。</td></tr><tr><td>[3]</td><td>CH3_SHORT_IF</td><td>MCPWM CH3_P 和 CH3_N 同时有效，中断源事件。
1，发生；0，没发生。写 1 清零。</td></tr><tr><td>[2]</td><td>CH2_SHORT_IF</td><td>MCPWM CH2_P 和 CH2_N 同时有效，中断源事件。
1，发生；0，没发生。写 1 清零。</td></tr><tr><td>[1]</td><td>CH1_SHORT_IF</td><td>MCPWM CH1_P 和 CH1_N 同时有效，中断源事件。
1，发生；0，没发生。写 1 清零。</td></tr><tr><td>[0]</td><td>CH0_SHORT_IF</td><td>MCPWM CH0_P 和 CH0_N 同时有效，中断源事件。
1，发生；0，没发生。写 1 清零。</td></tr></table>

# 13.2.20 MCPWM_RE

写保护的寄存器

地址：0x4001_1C48

复位值：0x0

表13-23MCPWM_RE配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>ZC_RE</td><td>STOV_RE</td><td>TMR3_RE</td><td>TMR2_RE</td><td>TMR1_RE</td><td>TMR0_RE</td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:6]</td><td></td><td>未使用</td></tr><tr><td>[5]</td><td>ZC_RE</td><td>DMA 请求使能信号。过零事件请求。写 1，使能；写 0，关闭。</td></tr><tr><td>[4]</td><td>STOV_RE</td><td>DMA 请求使能信号。起点事件请求。写 1，使能；写 0，关闭。</td></tr><tr><td>[3]</td><td>TMR3_RE</td><td>DMA 请求使能信号。ADC 通道 3 请求。写 1，使能；写 0，关闭。</td></tr><tr><td>[2]</td><td>TMR2_RE</td><td>DMA 请求使能信号。ADC 通道 2 请求。写 1，使能；写 0，关闭。</td></tr><tr><td>[1]</td><td>TMR1_RE</td><td>DMA 请求使能信号。ADC 通道 1 请求。写 1，使能；写 0，关闭。</td></tr><tr><td>[0]</td><td>TMR0_RE</td><td>DMA 请求使能信号。ADC 通道 0 请求。写 1，使能；写 0，关闭。</td></tr></table>

# 13.2.21 MCPWM_PP

写保护的寄存器

地址：0x4001_1C4C

复位值：0x0

表13-24MCPWM_PP配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td>IO3_PPE</td><td>IO2_PPE</td><td>IO1_PPE</td><td>IO0_PPE</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW&lt;fnl&gt;</td><td></td><td></td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:4]</td><td></td><td>未使用</td></tr><tr><td>[3]</td><td>IO3_PPE</td><td>IO3 推挽模式使能信号。写 1，使能；写 0，关闭。</td></tr><tr><td>[2]</td><td>IO2_PPE</td><td>IO2 推挽模式使能信号。写 1，使能；写 0，关闭。</td></tr><tr><td>[1]</td><td>IO1_PPE</td><td>IO1 推挽模式使能信号。写 1，使能；写 0，关闭。</td></tr><tr><td>[0]</td><td>IO0_PPE</td><td>IO0 推挽模式使能信号。写 1，使能；写 0，关闭。</td></tr></table>

推挽模式使能信号。根据工作模式不同而不同。边沿模式，开启边沿模式的推挽模式；中心对齐，开启中心对齐的推挽模式。

# 13.2.22 MCPWM_I001

写保护的寄存器

地址：0x4001_1C50

复位值：0x0

表13-25MCPWM_I001配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>CH1_WM</td><td>CH1_PN_SW</td><td>CH1_SCTRLP</td><td>CH1_SCTRLN</td><td>CH1_PS</td><td>CH1_NS</td><td>CH1_PP</td><td>CH1_NP</td><td>CH0_WM</td><td>CH0_PN_SW</td><td>CH0_SCTRLP</td><td>CH0_PS</td><td>CH0_NS</td><td>CH0_PP</td><td>CH0_NP</td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15]</td><td>CH1_WM</td><td>CH1 工作模式选择。1：Edge 模式；0：互补模式。</td></tr><tr><td>[14]</td><td>CH1_PN_SW</td><td>CH1 的 P 和 N 通道输出互换选择。即 P 通道信号最后从 N 通道输出，N 通道的信号最后从 P 通道输出。1：互换；0：不互换。</td></tr><tr><td>[13]</td><td>CH1_SCTRLP</td><td>当 CH1_PS=1 时，输出到 CH1 P 通道的值。</td></tr><tr><td>[12]</td><td>CH1_SCTRLN</td><td>当 CH1_NS=1 时，输出到 CH1 N 通道的值。</td></tr><tr><td>[11]</td><td>CH1_PS</td><td>CH1 P 来源。1：来自 CH1_SCTRLP；0：MCPWM 内部计数器产生。</td></tr><tr><td>[10]</td><td>CH1_NS</td><td>CH1 N 来源。1：来自 CH1_SCTRLN；0：MCPWM 内部计数器产生。</td></tr><tr><td>[9]</td><td>CH1_PP</td><td>CH1 P 极性选择。1：CH1 P 信号取反输出；0：CH1 P 信号正常输出。</td></tr><tr><td>[8]</td><td>CH1_NP</td><td>CH1 N 极性选择。1：CH1 N 信号取反输出；0：CH1 N 信号正常输出。</td></tr><tr><td>[7]</td><td>CH0_WM</td><td>CH0 工作模式选择。1：Edge 模式；0：互补模式。</td></tr><tr><td>[6]</td><td>CH0_PN_SW</td><td>CH0 的 P 和 N 通道输出互换选择。即 P 通道信号最后从 N 通道输出，N 通道的信号最后从 P 通道输出。1：互换；0：不互换。</td></tr><tr><td>[5]</td><td>CH0_SCTRLP</td><td>当 CH0_PS=1 时，输出到 CH0 P 通道的值。</td></tr><tr><td>[4]</td><td>CH0_SCTRLN</td><td>当 CH0_NS=1 时，输出到 CH0 N 通道的值。</td></tr><tr><td>[3]</td><td>CH0_PS</td><td>CH0 P 来源。1：来自 CH0_SCTRLP；0：MCPWM 实际运行系统中计数器产生。</td></tr><tr><td>[2]</td><td>CH0_NS</td><td>CH0 N 来源。1：来自 CH0_SCTRLN；0：MCPWM 实际运行系统中计数器产生。</td></tr><tr><td>[1]</td><td>CH0_PP</td><td>CH0 P 极性选择。1：CH0 P 信号取反输出；0：CH0 P 信号正常输出。</td></tr><tr><td>[0]</td><td>CH0_NP</td><td>CH0 N 极性选择。1：CH0 N 信号取反输出；0：CH0 N 信号正常输出。极性选择跟随通道交换，例如 CH0 N 选择取反输出，同时选择了通道交换，则交换后的 CH0 N 仍是取反输出。</td></tr></table>

# 13.2.23 MCPWM_IO23

写保护的寄存器

地址：0x4001_1C54

复位值：0x0

<table><tr><td></td><td></td><td>换，则交换后的 CH0 N 仍是取反输出。</td></tr></table>

# 13.2.24 MCPWM_SDCFG

写保护的寄存器

地址：0x4001_1C58

复位值：0x0

表13-27MCPWM_SDCFG配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td>AUTO_ERR_CLR</td><td>T1_UPDATE_EN</td><td>T0_UPDATE_EN</td><td>UPDATE_INTV</td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:7]</td><td></td><td>未使用</td></tr><tr><td>[6]</td><td>AUTO_ERR_CLR</td><td>AUTO_ERR_CLR 更新事件是否自动清除 MCPWM_EIF[5:4]并置位MOE，恢复 MCPWM 信号输出。
1：使能自动故障清除功能；0：关闭自动故障清除功能。</td></tr><tr><td>[5]</td><td>T1_UPDATE_EN</td><td>t1（过零）事件更新使能。1：使能；0，关闭。</td></tr><tr><td>[4]</td><td>T0_UPDATE_EN</td><td>t0（起点）事件更新使能。1：使能；0，关闭。</td></tr><tr><td>[3:0]</td><td>UPDATE_INTV</td><td>更新间隔。t0/t1 发生次数同 UPDATE_INTV+1 相等时，，MCPWM 系统自动触发 MCPWM_TH（包括 THxx）和 MCPWM_TMR 寄存器加载到 MCPWM 运行系统的操作。若 B[5]和 B[4]均关闭，将不会触发此类型加载，只能手动触发加载。</td></tr></table>

# 13.2.25 MCPWM_TCLK

写保护的寄存器

地址：0x4001_1C60

复位值：0x0

表13-28MCPWM_TCLK配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="3">CMP_FLT_CLKDIV</td><td colspan="3">IO_FLT_CLKDIV</td><td rowspan="3" colspan="3"></td><td colspan="2">BASE_CNT_EN</td><td colspan="2">CLK_EN</td><td colspan="2">CLK_DIV</td><td></td></tr><tr><td colspan="3">RW</td><td colspan="3">RW</td><td colspan="2">RW</td><td colspan="2">RW</td><td colspan="2">RW</td><td></td></tr><tr><td colspan="3">0</td><td colspan="3">0</td><td colspan="2">0</td><td colspan="2">0</td><td colspan="2">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr></table>

<table><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:12]</td><td>CMP_FLT_CLKDIV</td><td>比较器输出的滤波时钟分频寄存器，基于系统时钟分频，影响 MCPWM_FAIL[1:0]。计算公式如下：
系统时钟/(B[15:12]+1)。分频范围是1-16。</td></tr><tr><td>[11:8]</td><td>IO_FLT_CLKDIV</td><td>GPIO输入的滤波时钟分频寄存器，基于系统时钟分频，影响 MCPWM_FAIL[1:0]。计算公式如下：
系统时钟/(B[11:8]+1)。分频范围是1-16。</td></tr><tr><td>[7:4]</td><td></td><td>未使用</td></tr><tr><td>[3]</td><td>BASE_CNT_EN</td><td>MCPWM 实际运行计数器使能开关。1：使能；0：关闭。</td></tr><tr><td>[2]</td><td>CLK_EN</td><td>MCPWM 工作时钟使能。1：使能；0：关闭。</td></tr><tr><td>[1:0]</td><td>CLK_DIV</td><td>MCPWM 工作时钟分频寄存器。
0：系统时钟
1：系统时钟/2
2：系统时钟/4
3：系统时钟/8</td></tr></table>

# 13.2.26 MCPWM_FAIL

写保护的寄存器

地址：0x4001_1C64

复位值：0x0

表13-29MCPWM_FAIL配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>CH3N_DEFAULT</td><td></td><td>CH3P_DEFAULT</td><td></td><td>CH2N_DEFAULT</td><td></td><td>CH2P_DEFAULT</td><td></td><td>CH1P_DEFAULT</td><td></td><td>CHON_DEFAULT</td><td></td><td>CHOP_DEFAULT</td><td></td><td>HALT_PRT</td><td></td><td>MCPWM_OE</td><td></td><td>FAIL_EN</td><td></td><td>FAIL_OEN</td><td></td><td>FAIL_LPOL</td><td></td><td>FAIL_OPOL</td><td></td><td>FAIL_I_SEL</td><td></td><td>FAIL_O_SEL</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>Rw</td><td>Rw</td><td>Rw</td><td>RW</td><td>RW</td><td>R</td></tr></table>

<table><tr><td></td><td></td><td>出默认电平。默认电平输出不受 MCPWM_IO01 和 MCPWM_IO23 的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14 通道交换和极性控制的影响，直接控制通道输出。</td></tr><tr><td>[7]</td><td>HALT_PRT</td><td>CPU 进入 HALT 状态，MCPWM 输出值选择。
1：正常输出；0：强制 MCPWM 输出保护值。</td></tr><tr><td>[6]</td><td>MCPWM_OE</td><td>MOE 控制 MCPWM CHP 和 N 输出值。
1：输出 MCPWM 产生的正常信号
0：输出 CHxN_DEFAULT 和 CHxP_DEFAULT 默认值，此默认值不受极性/通道选择等控制。
MCPWM_EIF_FAIL1_IF 和 MCPWM_EIF_FAIL0_IF 任意一位变 1 将触发 MCPWM_OE 变成 0，输出默认值。</td></tr><tr><td>[5]</td><td>FAIL1_EN</td><td>FAIL1 输入使能。1：使能；0：关闭。</td></tr><tr><td>[4]</td><td>FAIL0_EN</td><td>FAIL0 输入使能。1：使能；0：关闭。</td></tr><tr><td>[3]</td><td>FAIL1_POL</td><td>FAIL1 极性选择。1：信号极性取反输入，信号输入低为有效电平；
0：信号极性正常输入，信号输入高为有效电平。</td></tr><tr><td>[2]</td><td>FAIL0_POL</td><td>FAIL0 极性选择。1：信号极性取反输入，信号输入低为有效电平；
0：信号极性正常输入，信号输入高为有效电平。</td></tr><tr><td>[1]</td><td>FAIL1_SEL</td><td>FAIL1 来源选择。1：比较器 1 的结果；0：来自 GPIO 第 1 路。</td></tr><tr><td>[0]</td><td>FAIL0_SEL</td><td>FAIL0 来源选择。1：比较器 0 的结果；0：来自 GPIO 第 0 路。</td></tr></table>

MCPWM_FAIL 可以用来设置紧急停车事件，封锁 MCPWM 的信号输出。急停事件主要有两个 FAIL0 和 FAIL1。共有 4 个信号来源，比较器 0 输出和比较器 1 输出以及 MCPWM_BKIN0 和 MCPWM_BKIN0。FAIL0 可以来自比较器 0 输出或芯片 IO MCPWM_BKIN0，FAIL1 可以来自比较器 1 输出或芯片 IO MCPWM_BKIN1。

FAIL 的输入信号可以使用数字滤波，滤波时钟的第一级分频由 MCPWM_TCLKCLK_DIV 寄存器设置。信号来源比较器 0 输出和比较器 1 输出的滤波时钟分频由 MCPWM_TCLKCMP_FLT_CLKDIV 设置；信号来源 MCPWM_BKIN0 和 MCPWM_BKIN0 的滤波时钟分频由 MCPWM_TCLK.IO_FLT_CLKDIV 设置。

最后 FAIL0, FAIL1 会对信号进行 16 个滤波时钟的滤波，即只有信号稳定时间超过 16 个滤波周期才能通过滤波器。即滤波宽度 = 滤波时钟周期 * 16。

更多信息可以参考 13.1.2 Fail 信号处理。

# 13.2.27 MCPWM_PRT

无写保护的寄存器

地址：0x4001_1C74

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16">PRT</td></tr><tr><td colspan="16">RW</td></tr></table>

<table><tr><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>PRT</td><td>写入 0xDEAD，解除 MCPWM 寄存器写保护；写入其它值，MCPWM 寄存器进入写保护。</td></tr></table>

# 13.2.28 MCPWM_CNT

无写保护的寄存器

地址：0x4001_1C78

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">CNT</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>CNT</td><td>MCPWM 实际运行系统中计数器的值。实际读出的计数范围为 0x8000-TH ~ 0x8000+TH，即读出值与 MCPWM 内部 CNT 计数值存在 0x8000 的偏移</td></tr></table>

# 13.2.29 MCPWM_DTH00

写保护的寄存器

地址：0x4001_1C80

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DTH00</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr></table>

<table><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DTH00</td><td>MCPWM CH0 P 通道死区宽度控制寄存器，10bit 无符号数</td></tr></table>

# 13.2.30 MCPWM_DTH01

写保护的寄存器

地址：0x4001_1C84

复位值：0x0

表13-33MCPWM_DTH01配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="15">DTH01</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DTH01</td><td>MCPWM CH0 N 通道死区宽度控制寄存器，10bit 无符号数</td></tr></table>

# 13.2.31 MCPWM_DTH10

写保护的寄存器

地址：0x4001_1C88

复位值：0x0

表13-34MCPWM_DTH10配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>位置</td><td>位名称</td><td>说明</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>[31:16]</td><td></td><td>未使用</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>[15:0]</td><td>DTH10</td><td>MCPWM CH1 P 通道死区宽度控制寄存器，10bit 无符号数</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

# 13.2.32 MCPWM_DTH11

写保护的寄存器

地址：0x4001_1C8C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16">DTH11</td></tr><tr><td colspan="16">RW</td></tr><tr><td colspan="16">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DTH11</td><td>MCPWM CH1 N 通道死区宽度控制寄存器，10bit 无符号数</td></tr></table>

# 13.2.33 MCPWM_DTH20

写保护的寄存器

地址：0x4001_1C90

复位值：0x0

<table><tr><td>DTH20</td></tr><tr><td>RW</td></tr><tr><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DTH20</td><td>MCPWM CH2 P 通道死区宽度控制寄存器，10bit 无符号数</td></tr></table>

# 13.2.34 MCPWM_DTH21

写保护的寄存器

地址：0x4001_1C94

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DTH21</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DTH21</td><td>MCPWM CH2 N 通道死区宽度控制寄存器，10bit 无符号数</td></tr></table>

# 13.2.35 MCPWM_DTH30

写保护的寄存器

地址：0x4001_1C98

复位值：0x0

表13-38MCPWM_DTH30配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DTH30</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DTH30</td><td>MCPWM CH3 P 通道死区宽度控制寄存器，10bit 无符号数</td></tr></table>

# 13.2.36 MCPWM_DTH31

写保护的寄存器

地址：0x4001_1C9C

复位值：0x0

表13-39MCPWM_DTH31配置寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">DTH31</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="2">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>DTH31</td><td>MCPWM CH3 N 通道死区宽度控制寄存器，10bit 无符号数</td></tr></table>

# 14 UART

# 14.1概述

UART特征如下：

全双工工作支持7/8位数据位支持1/2停止位支持奇/偶/无校验模式带1字节发送缓存带1字节接收缓存支持Multi- dropSlave/Master模式

# 14.2功能说明

# 14.2.1 发送

UART包括一个字节发送缓冲区，当发送缓冲区有数据时，UART将发送缓冲区的数据加载，并通过TX发送出去。

完成加载后，产生发送缓冲区空中断，此时，用户可以往发送缓冲区填入下一个需要发送的字节，这样，发送完成后，UART将加载这个字节进行发送。

完成发送后，会产生发送完成中断。

# 14.2.2 接收

UART包括一个字节的接收缓冲区，当完成一个字节的接收后，会产生接收中断，并将接收到字节存储到接收缓冲区，用户应当在UART接收完成下一个字节前完成此字节的读取，否则缓冲区会被写入新接收的字节。

# 14.2.3 波特率配置

UART输入时钟为系统主时钟，波特率通过两级分频实现。波特率  $\equiv$  UART模块时钟/（  $256^{*}$  UARTx_DIVH  $^+$  UARTx_DIVL+1)可以通过SYS_CLK_DIV2对UART模块时钟进行分频，UART模块时钟  $\equiv$  系统主时钟/(1+SYS_CLK_DIV2)

表14-1UART波特率配置示例  

<table><tr><td>UART 波特率</td><td>SYS_CLK_DIV2</td><td>UART_DIVH</td><td>UART_DIVL</td></tr></table>

<table><tr><td>300</td><td>0x0007</td><td>0x9C</td><td>0x3F</td></tr><tr><td>600</td><td>0x0003</td><td>0x9C</td><td>0x3F</td></tr><tr><td>1200</td><td>0x0001</td><td>0x9C</td><td>0x3F</td></tr><tr><td>2400</td><td>0x0000</td><td>0x9C</td><td>0x3F</td></tr><tr><td>4800</td><td>0x0000</td><td>0x4E</td><td>0x1F</td></tr><tr><td>9600</td><td>0x0000</td><td>0x27</td><td>0x0F</td></tr><tr><td>19200</td><td>0x0000</td><td>0x13</td><td>0x87</td></tr><tr><td>38400</td><td>0x0000</td><td>0x09</td><td>0xC3</td></tr><tr><td>43000</td><td>0x0000</td><td>0x08</td><td>0xB8</td></tr><tr><td>56000</td><td>0x0000</td><td>0x06</td><td>0xB1</td></tr><tr><td>57600</td><td>0x0000</td><td>0x06</td><td>0x82</td></tr><tr><td>115200</td><td>0x0000</td><td>0x03</td><td>0x40</td></tr></table>

注意，波特率配置系数仅为示例，可能不唯一。

# 14.2.4 收发端口互换(TX/RX互换)

UART模块支持Tx与Rx端口互换。通过将Tx对应的GPIO配置为输入使能，Rx对应的GPIO配置为输出使能，即可实现Tx与Rx端口的互换。此时，GPIO第二功能仍选择为UART，UART本身配置无需修改。

此外，如果要使用一个GPIO同时作为Tx和Rx，需要将IO分时复用为输入或输出，对应Rx或Tx，即可实现单口半双工逻辑。

# 14.2.5 DMA配置

UART模块，支持DMA操作。实现DMA搬移数据，能极大减轻CPU的负担。UART采用DMA操作，有以下注意事项。

接收和发送，不能同时使用DMA。只能接收，或者只能发送使用DMA。

发送模式，有两种配置DMA的方案。

方案1：若UARTx_IE.TX_BUF_EMPTY_RE配置有效。UARTx模块将预取第一个字节，准备发送；一旦数据进入发射队列，UARTx_IE.UARTx_BUF即为空，硬件自动会请求DMA搬移下一个字节直至数据搬移完毕。DMA搬移完毕后，将产生DMA完成中断，但是UARTx很可能没有发送完毕最后一个字节，若立即操作UARTx，将可能会产生异常。建议在DMA中断处理程序中，开启UARTx_IE.TX_DONE_IE中断，UARTx将最后一个字节发送完毕，产生发送完成中断，在UARTx中断处理函数里面，再关闭UARTx_IE.TX_DONE_IE。

方案2：若UARTx_IE.TX_DONE_RE配置有效。建议UART初始化阶段不要清除TX_DONE标志。当前传输的数据长度为Len，DMA配置传输的字节数为Len，开启DMA中断，DMA传输完毕后，UART也发送完毕，软复位UARTx模块并重新初始化UARTx，可开启下一次UARTx的发送。

# 14.3 寄存器

# 14.3.1 地址分配

UART0与UART1实现完全相同。UART0基地址0x4001_2800。UART1基地址0x4001_2C00。

表14-2UARTx地址分配列表  

<table><tr><td>名称</td><td>偏移地址</td><td>说明</td></tr><tr><td>UARTx_CTRL</td><td>0x00</td><td>UART 控制寄存器</td></tr><tr><td>UARTx_DIVH</td><td>0x04</td><td>UART 波特率设置高字节寄存器</td></tr><tr><td>UARTx_DIVL</td><td>0x08</td><td>UART 波特率设置低字节寄存器</td></tr><tr><td>UARTx_BUFF</td><td>0x0C</td><td>UART 收发缓冲寄存器</td></tr><tr><td>UARTx_ADR</td><td>0x10</td><td>485 通信地址匹配寄存器</td></tr><tr><td>UARTx_STT</td><td>0x14</td><td>UART 状态寄存器</td></tr><tr><td>UARTx_IE</td><td>0x18</td><td>UART 中断使能寄存器</td></tr><tr><td>UARTx_IF</td><td>0x1C</td><td>UART 中断标志寄存器</td></tr><tr><td>UARTx_INV</td><td>0x20</td><td>UART IO 翻转使能</td></tr></table>

# 14.3.2 UARTx_CTRLUARTx控制寄存器

UART0_CTRL地址：0x4001_2800

UART1_CTRL地址：0x4001_2C00

复位值：0x0

表14-3UARTx控制寄存器UARTx_CTRL  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[6]</td><td>MDMASTER_BIT9</td><td>Multi-drop Master 模式时，第 9 个数据位值</td></tr><tr><td>[5]</td><td>MD_EN</td><td>使能 Multi-drop，0:禁用，1:使能</td></tr><tr><td>[4]</td><td>CK_EN</td><td>使能校验，0:禁用，1:使能</td></tr></table>

<table><tr><td>[3]</td><td>CK_TYPE</td><td>奇偶校验，0:EVEN 1:ODD</td></tr><tr><td>[2]</td><td>BIT_ORDER</td><td>先发送的比特，0:LSB,1:MSB</td></tr><tr><td>[1]</td><td>STOP_LEN</td><td>停止位长度，0:1bit,1:2bit</td></tr><tr><td>[0]</td><td>DAT_LEN</td><td>数据长度，0:8bit,1:7bit</td></tr></table>

# 14.3.3 UARTx_DIVH UARTx 波特率设置高字节寄存器

UART0_DIVH 地址：0x4001_2804  UART1_DIVH 地址：0x4001_2C04

复位值：0x0

表14-4UARTx波特率设置高字节寄存器UARTx_DIVH  

<table><tr><td colspan="3">15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0</td></tr><tr><td rowspan="3" colspan="2"></td><td>DIVH</td></tr><tr><td>RW</td></tr><tr><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>DIVH</td><td>波特率设置高字节
BAUDRATE =主时钟/(1+DIVL+256*DIVH)</td></tr></table>

# 14.3.4 UARTx_DIVL UARTx 波特率设置低字节寄存器

UART0_DIVL 地址：0x4001_2808

UART1_DIVL 地址：0x4001_2C08

复位值：0x0

表14-5UARTx波特率设置低字节寄存器UARTx_DIVL  

<table><tr><td colspan="3">15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0</td></tr><tr><td rowspan="3" colspan="2"></td><td>DIVL</td></tr><tr><td>RW</td></tr><tr><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>DIVL</td><td>波特率设置低字节
BAUDRATE =主时钟/(1+256* UARTx_DIVH+UARTx_DIVL)</td></tr></table>

# 14.3.5 UARTxBUFFUARTx收发缓冲寄存器

UARTOBUFF地址：0x4001_280C UART1BUFF地址：0x4001_2C0C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="9"></td><td colspan="6">BUFF</td><td></td></tr><tr><td colspan="6">RW</td><td></td></tr><tr><td colspan="6">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>BUFF</td><td>写:发送数据缓存读:接收数据寄存器</td></tr></table>

UART的Tx_buffer和Rx_buffer共享地址  $0\times 0C$  地址。其中，Tx_buffer是只写的，Rx_buffer是只读的。因此读访问UARTxBUFF是访问UARTx_RXBUFF，写访问UARTxBUFF是访问UARTx_TX_BUFF

# 14.3.6 UARTxADRUARTx地址匹配寄存器

UARTOADER地址：0x4001_2810 UART1ADER地址：0x4001_2C10

复位值：0x0

表14-7UARTx地址匹配寄存器UARTxADR  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3" colspan="7"></td><td colspan="7"></td><td colspan="7">ADR</td></tr><tr><td colspan="7">RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="7"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>ADR</td><td>用作 485 通信时的匹配地址</td></tr></table>

# 14.3.7 UARTxSTTUARTx状态寄存器

UARTO_STT地址：0x4001_2814 UART1_STT地址：0x4001_2C14

复位值：0x0

表14-8UARTx状态寄存器UARTx_STT  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>1</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>TX_BUF_EMPTY</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>TX_BUF_EMPTY</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:3]</td><td></td><td>未使用</td></tr><tr><td>[2]</td><td>ADR_MATCH</td><td>Multi-drop 模式下，地址匹配标志位。
1：匹配；0：未匹配。</td></tr><tr><td>[1]</td><td>TX_DONE</td><td>发送完成（此时发送缓存如不为空，则可以继续发送缓存中的数据）
1：完成；0：未完成。</td></tr><tr><td>[0]</td><td>TX_BUF_EMPTY</td><td>发送缓存状态位。
1：空；0：非空。</td></tr></table>

# 14-3.8 UARTx_IE UARTx 中断使能寄存器

UART0_IE地址：0x4001_2818

UART1_IE地址：0x4001_2C18

复位值：0x0

表14-9UARTx中断使能寄存器UARTx_IE  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7]</td><td>TX_BUF_EMPTY_RE</td><td>发送缓冲区空 DMA 请求使能， 默认值为 0。
0：关闭；1：开启。</td></tr><tr><td>[6]</td><td>RX_DONE_RE</td><td>接收完成 DMA 请求使能， 默认值为 0。</td></tr></table>

<table><tr><td></td><td></td><td>0：关闭；1：开启。</td></tr><tr><td>[5]</td><td>TX_DONE_IE</td><td>发送完成 DMA 请求使能，默认值为 0。
0：关闭；1：开启。</td></tr><tr><td>[4]</td><td>CK_ERR_IE</td><td>校验错误中断开关，默认值为 0。
0：关闭；1：开启。</td></tr><tr><td>[3]</td><td>STOP_ERR_IE</td><td>停止位错误中断开关，默认值为 0。
0：关闭；1：开启。</td></tr><tr><td>[2]</td><td>TX_BUF_EMPTY_IE</td><td>发送缓冲区空中断开关，默认值为 0。
0：关闭；1：开启。</td></tr><tr><td>[1]</td><td>RX_DONE_IE</td><td>接收完成中断开关，默认值为 0。
0：关闭；1：开启。</td></tr><tr><td>[0]</td><td>TX_DONE_IE</td><td>发送完成中断开关，默认值为 0。
0：关闭；1：开启。</td></tr></table>

# 14.3.9 UARTx_IF UARTx 中断标志寄存器

UART0_IF 地址：0x4001_281C

UART1_IF 地址：0x4001_2C1C

复位值：0x0

表14-10UARTx中断使能寄存器UARTx_IF  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>1</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="4" colspan="11"></td><td rowspan="9">TXDONEIF</td><td rowspan="9">STOP_ERRIF</td><td rowspan="8">TXBUF_EMPTYIF</td><td rowspan="6">RXDONEIF</td><td>TXDONEIF</td></tr><tr><td></td></tr><tr><td></td></tr><tr><td></td></tr><tr><td rowspan="5" colspan="11"></td><td></td></tr><tr><td></td></tr><tr><td rowspan="2"></td><td></td></tr><tr><td></td></tr><tr><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:5]</td><td></td><td>未使用</td></tr><tr><td>[4]</td><td>CK_ERR_IF</td><td>校验错误中断标志，高有效，写1清零。</td></tr><tr><td>[3]</td><td>STOP_ERR_IF</td><td>停止位错误中断标志，高有效，写1清零。</td></tr><tr><td>[2]</td><td>TX_BUF_EMPTY_IF</td><td>发送缓冲区空中断标志，高有效，写1清零。</td></tr><tr><td>[1]</td><td>RX_DONE_IF</td><td>接收完成中断标志，高有效，写1清零。</td></tr><tr><td>[0]</td><td>TX_DONE_IF</td><td>发送完成中断标志，高有效，写1清零。</td></tr></table>

上电后发送缓冲区空标志TX_BUF_EMPTY_IF和发送完成中断标志TX_DONE_IF默认为1。

中断标志写1清零，一般不建议用如下  $\mid =$  方式清零，因为  $\mid =$  是先读取中断标志，将对应位改为1再写入清零，如果同时有其他中断标志置位，会被一起清零，而这通常不是软件所期望的。例如，如下写法本意是清零TX_DONE_IF，但如果同时RX_DONE_IF在写入执行前置1了，则软件先读取

回 UARTx_IF 值为  $0 \times 2$ ，然后执行或操作  $0 \times 2 \mid 0 \times 1 = 0 \times 3$ ，然后写入，同时对 RX_DONE_IF 和 TX_DONE_IF 进行了清零，可能导致 UART 少进入一次因接收数据产生的中断，从而少接收到一字节数据。

如果希望清零 TX_DONE_IF 标志位，应以如下方式，直接对 BIT0 写 1.

# 14.3.10 UARTx_INV UARTx IO 翻转寄存器

UART0_INV 地址：0x4001_2820

UART1_INV 地址：0x4001_2C20

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>RXD_INV</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>RXD_INV</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>RW</td><td>RW</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:2]</td><td></td><td>未使用</td></tr><tr><td>[1]</td><td>TXD_INV</td><td>TXD 输出极性使能开关， 默认值为 0。
0：正常输出；1：取反输出。
正常输出极性，是指软件发送 1，硬件发送的即是 1；取反输出极性，是指软件发送 1，硬件发送的是 0。</td></tr><tr><td>[0]</td><td>RXD_INV</td><td>RXD 输入极性使能开关， 默认值为 0。
0：正常输入；1：取反输入。
正常输入极性，是指硬件接收 1，软件接收的即是 1；取反输入极性，是指硬件接收 1，软件接收到的是 0。</td></tr></table>

# 15 DSP

# 15.1概述

DSP模块使用自主设计的DSP指令集，可以进行加法、乘累加、移位、饱和等单周期算术指令，以及除法、开方、三角函数等多周期算术运算指令；具备load/store等访存指令，无条件跳转以及条件跳转等分支指令，还有中断提起等杂项指令。有断点指令和寄存器赋值等伪指令可以在模拟器上用于调试。DSP有两种运行模式，自主运行、被动调用。

DSP有两种运行模式，自主运行、被动调用。

所谓自主运行即DSP读取CODEMEM中的指令和DATAMEM中的数据进行DSP程序执行，独立于ARM CortexM0，此时DSP_SC.PAUSED  $= 0$  ，即DSP处于运行状态；CODEMEM和DATAMEM允许DSP访问但不允许CPU访问改写。

被动调用是指DSP作为一个外设模块被ARM CortexM0所调用，CPU直接访问DSP内部的算术运算资源如除法、开方、三角函数等。此时DSP_SC.PAUSED  $= 1$  ，即DSP不运行DSP程序，处于暂停状态，CODEMEM和DATAMEM允许CPU进行访问改写，对于不进行DSP程序开发的用户，推荐使用此种模式，通过CPU运行的软件直接调用DSP的算术单元。

DSP配备独立的程序存储器(CODEMEM)和数据存储器(DATAMEM)。在DSP暂停即DSP_SC.PAUSED  $= 1$  时可以通过CPU访问这两个独立的存储区域，在DSP初始化的过程中需要由CPU将DSP运行的程序和初始数据分别写入DSP的CODEMEM和DATAMEM。DSP具备提起中断的指令，中断置位后，DSP同时进入暂停状态，此时允许CPU通过总线接口访问DATAMEM与DSP进行数据交互，包括读取DSP运算结果，以及写入DSP后续运行所需的数据等。

此外，为充分灵活利用DSP，在DSP暂停时允许CPU通过DSP寄存器接口直接访问DSP除法器、开方器、三角函数等运算模块，即允许CPU将DSP当做简单的运算协处理模块使用。

# 15.1.1 功能框图

![](images/89e70b1b2357a3584b8c0ad9de21edd9fedcd22c572a80525e012033f5a28387.jpg)  
图15-1DSP模块功能框图

# 15.1.2 DSP核寄存器

表15-1DSP核心寄存器  

<table><tr><td>Register</td><td>Bit Width</td><td>Usage</td></tr><tr><td>R0</td><td>32</td><td>Always read as 0</td></tr><tr><td>R1</td><td>32</td><td></td></tr><tr><td>R2</td><td>32</td><td></td></tr><tr><td>R3</td><td>32</td><td></td></tr><tr><td>R4</td><td>32</td><td></td></tr><tr><td>R5</td><td>32</td><td></td></tr><tr><td>R6</td><td>32</td><td>ARCTAN module destination</td></tr><tr><td>R7</td><td>32</td><td>MAC result / DIV dividend</td></tr><tr><td>PC</td><td>16</td><td>Program Counter</td></tr></table>

其中R0寄存器为常0寄存器，不能写入数据，读回恒为0。R0寄存器可作为特殊操作数构造一些伪指令。如

ADDRORORO相当于NOP

MACR1R2RO相当于MULR1R2，即乘累加中累加的数为0，变为乘法操作

R6寄存器在ARCTAN指令中固定用于存放向量模值

R7 寄存器在 MAC 指令中固定用于存放计算结果，在 DIV 指令中固定用于存放被除数操作数。以上约定是由于受定长指令编码限制，在 4 操作数指令中需要固定一个操作数使用约定寄存器。

# 15.1.3 位宽

除法的被除数和商位宽均为 32 位有符号数，除数和余数为 16 位有符号数。被开方数为 32 位无符号数，平方根为 16 位无符号数。乘累加的两个乘数均为 16 位有符号数，加数和结果为 32 位有符号数。三角函数 CORDIC 模块位宽为 16 位，Q15 定点数格式。

注意：在使用 DSP 算术运算资源时，无论是 CPU 调用还是通过 DSP 算术指令调用，请务必保证操作数不要超过表示范围，否则会出现计算异常。例如乘法的两个操作数为 16 位有符号数，除法的除数为 16 位有符号数。16 位有符号数的表示范围为 - 32768~32767，如果输入的 32 位数据超过这一范围，比如以 50000 或 - 40000 作为乘法的操作数，则会因源操作数被截取了低 16 位而出现计算错误。

除法（DIV 指令）的操作数，被除数范围是  $- (2^{\wedge}31 - 1)\sim (2^{\wedge}31 - 1)$ ，除数的范围是  $- (2^{\wedge}15 - 1)\sim (2^{\wedge}15 - 1)$ ；被除数不支持赋值为  $- 2^{\wedge}31$ ，除数不支持赋值为  $- 2^{\wedge}15$ 。

减法（SUB 指令）的操作数，减数范围为  $- (2^{\wedge}31 - 1)\sim (2^{\wedge}31 - 1)$ ，减数不支持赋值为  $- 2^{\wedge}31$ 。

此外，由于 CORDIC 运算基于多次旋转逐次逼近，计算结果存在不超过  $0.1\%$  的计算误差。

# 15.1.4 指令周期

除法指令需要 10 个总线周期（96MHz）完成。

开方指令需要 8 个总线周期（96MHz）完成。

三角函数指令需要 8 个总线周期（96MHz）完成。

其余指令均为单周期指令

# 15.1.5 地址空间

表15-2DSP地址空间  

<table><tr><td>模块</td><td>空间大小</td><td>空间区域</td><td>实际存储体大小</td></tr><tr><td>code_mem</td><td>2kB</td><td>0x4001_4000～0x4001_47FF</td><td>512 x 16bit</td></tr><tr><td>data_mem</td><td>2kB</td><td>0x4001_4800～0x4001_4FFF</td><td>64 x 32bit</td></tr><tr><td>reg</td><td>2kB</td><td>0x4001_5000～0x4001_57FF</td><td></td></tr><tr><td>Reserved</td><td>2kB</td><td>0x4001_5800～0x4001_5FFF</td><td></td></tr></table>

DSP 的地址空间分为 4 段，分别为程序段、数据段、寄存器段、保留段，各段空间占用 2kB 的地址空间，但实际的 CODE MEM 和 DATA MEM 存储空间不足 2kB。程序段（CODE MEM）用于存放 DSP 运行所需程序代码，为单口 SRAM，单周期完成读写操作；数据段（DATA MEM）用于存放 DSP 运行所需数据，为单口 SRAM，单周期完成读写操作；寄存器段为允许 CPU 通过总线访问的 DSP 寄存器；保留段暂未使用。

CODEMEM位宽为16，但仍按word寻址，亦即地址每次增4。

DSP地址空间需要在适当的时机才能访问。其中DSP的状态控制寄存器可以在任何时间访问；DSP的CODEMEM、DATAMEM、以及寄存器段中CODIC三角函数模块、DIV除法器、SQRT开方器只有在DSP暂停即DSP_SC.PAUSED  $\mathbf{\tau} = \mathbf{1}$  时才能进行寄存器访问。因为在DSP运行期间，所有的运算单元可能在被DSP使用，CPU同时通过寄存器接口进行访问会造成访问冲突。因此在DSP运行期间，即DSP_SC.PAUSED  $\mathbf{\tau} = \mathbf{0}$  时，禁止通过寄存器接口访问DSP的运算单元。

DSP遇到中断指令会提起中断等待CPU处理，同时DSP进入暂停状态，DSP_SC.PAUSED会置位为1。此外软件也可以在任意时刻通过写DSP_SC.PAUSED  $\mathbf{\tau} = \mathbf{1}$  来使DSP进入暂停状态。这一机制主要是为了防止DSP写入的程序中没有IRQ指令，导致DSP在不掉电的情况下会永久运行。

# 15.2 寄存器

# 15.2.1 地址分配

DSP模块在芯片中的基地址是0x4001_4000。DSP寄存器在芯片中的基地址是0x4001_5000。

表15-3DSP寄存器列表  

<table><tr><td>名称</td><td>偏移</td><td>说明</td></tr><tr><td>DSP_SC</td><td>0x00</td><td>DSP 状态控制寄存器</td></tr><tr><td>DSP_THETA</td><td>0x04</td><td>DSP sin/cos 输入角度寄存器</td></tr><tr><td>DSP_X</td><td>0x08</td><td>DSP arctan/module 计算输入坐标 X 寄存器</td></tr><tr><td>DSP_Y</td><td>0x0C</td><td>DSP arctan/module 计算输入坐标 Y 寄存器</td></tr><tr><td>DSP_SIN</td><td>0x10</td><td>DSP sin/cos 计算结果 sin 寄存器</td></tr><tr><td>DSP_COS</td><td>0x14</td><td>DSP sin/cos 计算结果 cos 寄存器</td></tr><tr><td>DSP_MOD</td><td>0x18</td><td>DSP arctan 计算结果 sqrt(X²+Y²) 寄存器</td></tr><tr><td>DSP_ARCTAN</td><td>0x1C</td><td>DSP arctan 计算结果 arctan(Y/X) 角度寄存器</td></tr><tr><td>DSP_DID</td><td>0x20</td><td>DSP 除法操作被除数</td></tr><tr><td>DSP_DIS</td><td>0x24</td><td>DSP 除法操作除数</td></tr><tr><td>DSP_QUO</td><td>0x28</td><td>DSP 除法操作商</td></tr><tr><td>DSP_REM</td><td>0x2C</td><td>DSP 除法操作余数</td></tr><tr><td>DSP_RAD</td><td>0x30</td><td>DSP 开方操作被开方数</td></tr><tr><td>DSP_SQRT</td><td>0x34</td><td>DSP 开方操作平方根</td></tr></table>

# 15.2.2 DSP状态控制寄存器

# 15.2.2.1 DSP_SC

地址：0x4001_5000

复位值：0x2

<table><tr><td colspan="11">表15-4DSP状态控制寄存器DSP_SC</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td>RESET_PC</td><td>CORDIC_MODE</td><td>PAUSED</td><td>IRQ</td><td></td></tr><tr><td>W0</td><td>RW</td><td>RW</td><td>RWIC</td><td></td></tr><tr><td>0</td><td>0</td><td>1</td><td>0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:4]</td><td></td><td>保留</td></tr><tr><td>[3]</td><td>RESET_PC</td><td>当DSP暂停时，写1重置DSP PC到0地址</td></tr><tr><td>[2]</td><td>CORDIC_MODE</td><td>CORDIC mode, 0: arctan, 1: sin/cos</td></tr><tr><td>[1]</td><td>PAUSED</td><td>指示DSP是否处于暂停状态，当DSP执行到IRQ指令时此bit置1，软件写可以将此bit置1。软件将此bit清零可以启动DSP运行
0：DSP正读取CODE MEM和DATA MEM自主运行DSP程序
1：DSP暂停取指令，允许ARM软件通过寄存器访问DSP内部算术单元，向寄存器写入操作数触发运算，读取寄存器取得运算结果
对于不编写DSP CODE MEM程序的用户，PAUSED需保持为1</td></tr><tr><td>[0]</td><td>IRQ</td><td>DSP中断标志，写1清零</td></tr></table>

注意，复位后DSP处于暂停状态，即DSP_SC.PAUSED  $= 1$  时；DSP_SC.CORDIC_MODE用于CPU通过寄存器接口访问CORDIC模块时，sin/cos mode和arctan mode的选择，CORDIC模块计算sin/cos或arctan使用的是相同的硬件电路。因此在进行某一种计算前，应通过配置DSP_SC计算器进行适当模式选择。

只有当DSP处于暂停状态时，CPU才可以通过寄存器接口调用DSP。当DSP自主运行时，CPU无法通过寄存器接口访问DSP内部资源。

DSP_SC.CORDIC_MODE位仅在CPU通过寄存器接口调用DSPCORDIC单元时需要设置，DSP程序可以根据SIN_COS或ARCTAN指令直接进行模式切换，DSP_SC.CORDIC_MODE不再起作用。

软件调用CORDIC模块计算sin/cos时以角度DSP_THETA为输入，计算并输出sin/cos结果到DSP_SIN/DSP_COS寄存器；计算arctan时以坐标DSP_X/DSP_Y为输入，计算并输出角度theta=arctan  $(y / x)$  和module  $=$  sqrt  $(x^{2} + y^{2})$  到DSP_ARCTAN和DSP_MOD寄存器。

# 15.2.3DSPsin/cos相关寄存器

CORDIC模块计算sin/cos和arctan使用的是相同的数据通路，因此通过CPU使用CORDIC模块进行sin/cos计算，需要先将DSP_SC.CORDIC_MODE写为1，使CORDIC进入sin/cos模式。

# 15.2.3.1DSP_THETA

地址：0x4001_5004

复位值：0x0

表15-5DSPsin/cos角度输入寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">THETA</td><td></td></tr><tr><td colspan="15">RW</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>保留，读出时为符号扩展，即{16{DSP_THETA[15]}}</td></tr><tr><td>[15:0]</td><td>THETA</td><td>DSP sin/cos 输入角度寄存器</td></tr></table>

DSP_THETA为16位有符号定点数，表示范围（  $- 32768\sim 32767$  ）对应（  $- \pi \sim \pi$  ）。

15.2.3.2DSP_SIN

地址：0x4001_5010

复位值：0x0

表15-6DSPsin/cos正弦结果寄存器  

<table><tr><td>SIN</td></tr><tr><td>RO</td></tr><tr><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>保留，读出时为符号扩展，即{16{DSP_SIN[15]}}</td></tr><tr><td>[15:0]</td><td>SIN</td><td>DSP sin/cos 计算结果 sin 寄存器</td></tr></table>

DSP_SIN为16位有符号定点数，其中1bit符号位，15bit小数位；表示范围（  $- 1\sim 1$  ）。

15.2.3.3DSP_COS

地址：0x4001_5014

复位值：0x0

表15-7DSPsin/cos余弦结果寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">COS</td><td></td></tr><tr><td colspan="15">RO</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>保留，读出时为符号扩展，即{16{DSP_COS[15]}}</td></tr><tr><td>[15:0]</td><td>COS</td><td>DSP sin/cos 计算结果 cos 寄存器</td></tr></table>

DSP_COS为16位有符号定点数，其中1bit符号位，15bit小数位；表示范围（- 1～1）。

# 15.2.4 DSP arctan 相关寄存器

15.2.4.1 DSP_X

地址：0x4001_5008

复位值：0x0

表15-8DSParctan/module坐标X输入寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>保留，读出时为符号扩展，即{16{DSP_X[15]}}</td></tr><tr><td>[15:0]</td><td>X</td><td>DSP arctan/module 计算输入坐标 X 寄存器</td></tr></table>

DSP_X为16位有符号定点数，Q15格式，其中1bit符号位，15bit整数位，表示范围（- 32768～32767）。

15.2.4.2 DSP_Y

地址：0x4001_500C

复位值：0x0

表15-9DSParctan/module计算坐标Y输入寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>保留，读出时为符号扩展，即{16{DSP_Y[15]}}</td></tr></table>

<table><tr><td>[15:0]</td><td>Y</td><td>DSP arctan/module 计算输入坐标 Y 寄存器</td></tr></table>

DSP_Y为16位有符号定点数，其中1bit符号位，15bit整数位，表示范围（- 32768～32767）。

15.2.4.3 DSP_MOD

地址：0x4001_5018

复位值：0x0

表15-10DSParctan向量模结果sqrt  $(X^{2} + Y^{2})$  寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16">MOD</td></tr><tr><td colspan="16">RO</td></tr><tr><td colspan="16">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>保留，读出为 0</td></tr><tr><td>[15:0]</td><td>MOD</td><td>DSP arctan 计算结果 sqrt(X²+Y²) 寄存器</td></tr></table>

DSP_MOD为16位有符号定点数，其中1bit符号位，15bit整数位，表示范围（- 32768～32767）。

需要注意的是，当计算arctan(Y/X)时，需要保证sqrt  $(X^{2} + Y^{2})$  也不超过32767，因此一般建议abs(DSP_X)和abs(DSP_Y)不超过  $2^{14}$  为宜。

15.2.4.4 DSP_ARCTAN

地址：0x4001_501C

复位值：0x0

表15-11DSParctan角度结果arctan(Y/X）角度寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">ARCTAN</td><td></td></tr><tr><td colspan="15">RO</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>保留，读出时为符号扩展，即{16{DSP_ARCTAN[15]}}</td></tr><tr><td>[15:0]</td><td>ARCTAN</td><td>DSP arctan 计算结果 arctan(Y/X) 角度寄存器</td></tr></table>

DSP_ARCTAN为16位有符号定点数，表示范围（- 32768～32767）对应（- π～π）。

需要注意的是，当计算arctan(Y/X)时，需要保证sqrt  $(X^{2} + Y^{2})$  也不超过32767，因此一般建议abs(DSP_X)和abs(DSP_Y)不超过  $2^{14}$  为宜。

# 15.2.5 DSP除法相关寄存器

# 15.2.5.1 DSP_DID

地址：0x4001_5020

复位值：0x0

<table><tr><td>31</td><td>30</td><td>29</td><td>28</td><td>27</td><td>26</td><td>25</td><td>24</td><td>23</td><td>22</td><td>21</td><td>20</td><td>19</td><td>18</td><td>17</td><td>16</td></tr><tr><td colspan="16">DID</td></tr><tr><td colspan="16">RW</td></tr><tr><td colspan="16">0</td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16">DID</td></tr><tr><td colspan="14">RW</td><td></td><td></td></tr><tr><td colspan="16">0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>DID</td><td>DSP 除法被除数寄存器</td></tr></table>

# 15.2.5.2 DSP_DIS

地址：0x4001_5024

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16">DIS</td></tr><tr><td colspan="16">RW</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="16">&lt;lcel&gt;</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>保留，读出时为符号扩展，即{16{DSP_DIS[15]}}</td></tr><tr><td>[15:0]</td><td>DIS</td><td>DSP 除法除数寄存器</td></tr></table>

# 15.2.5.3 DSP_QUO

地址：0x4001_5028

复位值：0x0

![](images/eb8920a4315a586970730f061edd64e2141845ebf0a617e82c045839951ac86e.jpg)

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>QUO</td><td>DSP 商寄存器</td></tr></table>

# 15.2.5.4 DSP_REM

地址：0x4001_502C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">REM</td><td></td></tr><tr><td colspan="15">RO</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>权限</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>保留，读出时为符号扩展，即{16{DSP_REM[15]}}</td></tr><tr><td>[15:0]</td><td>REM</td><td>DSP 除法余数寄存器</td></tr></table>

当CPU需要使用DSP除法器时，应首先保证DSP处于暂停状态。先向DSP写入被除数，后写入除数；写入除数可以触发一次除法操作，32/16位除法需要8周期完成，期间读取除法结果DSP_QUO或DSP_REM会使CPU进入等待状态，等待除法计算完成并通过总线返回计算结果。

# 15.2.6 DSP 开方相关寄存器

# 15.2.6.1 DSP_RAD

地址：0x4001_5030

复位值：0x0

![](images/6a64b0546f606c405ac8d8a7878e1b70c3cf39793842dadd7f6d8583d21820ef.jpg)  
表15-16DSP被开方数寄存器

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:0]</td><td>RAD</td><td>DSP 被开方数寄存器</td></tr></table>

# 15.2.6.2 DSP_SQRT

地址：0x4001_5034

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">SQRT</td><td></td></tr><tr><td colspan="15">RO</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>保留，读出时恒为 0</td></tr><tr><td>[15:0]</td><td>SQRT</td><td>DSP 平方根寄存器</td></tr></table>

当CPU需要使用DSP开方器时，应首先保证DSP处于暂停状态。向DSP写入被开方数；写入被开方数可以触发一次开方操作，32位开方需要8周期完成，期间读取开方结果DSP_SQRT会使CPU进入等待状态，等待开方计算完成并通过总线返回计算结果。

# 15.3 DSP指令集

# 15.3.1 Instruction Set Summary

<table><tr><td>Operation</td><td>Description</td><td colspan="4">Assembler</td><td>Cycles</td></tr><tr><td rowspan="2">Add</td><td></td><td>ADD</td><td>Rd1</td><td>Rs1</td><td>Rs2</td><td>1</td></tr><tr><td>5bit Immediate</td><td>ADDI</td><td>Rd1</td><td>Rs1</td><td>#&lt;l&gt;1</td><td></td></tr><tr><td>Subtract</td><td></td><td>SUB</td><td>Rd1</td><td>Rs1</td><td>Rs2</td><td>1</td></tr><tr><td rowspan="4">Shift</td><td>Arithmetic right shift</td><td>ASR</td><td>Rd1</td><td>Rs1</td><td>Rs2</td><td>1</td></tr><tr><td>5bit Immediate</td><td>ASRI</td><td>Rd1</td><td>Rs1</td><td>#&lt;l&gt;1</td><td></td></tr><tr><td>Logical left shift</td><td>LSL</td><td>Rd1</td><td>Rs1</td><td>Rs2</td><td>1</td></tr><tr><td>5bit Immediate</td><td>LSLI</td><td>Rd1</td><td>Rs1</td><td>#&lt;l&gt;1</td><td></td></tr><tr><td rowspan="2">Multiply and accumulation</td><td></td><td>MAC</td><td>Rs1</td><td>Rs2</td><td>Rs3</td><td>1</td></tr><tr><td>5bit Immediate</td><td>MACI</td><td>Rs1</td><td>Rs2</td><td>#&lt;l&gt;1</td><td></td></tr><tr><td>Divide</td><td></td><td>DIV</td><td>Rd1</td><td>Rs1</td><td>Rs2</td><td>10</td></tr><tr><td rowspan="2">Saturation</td><td></td><td>SAT</td><td>Rd1</td><td>Rs1</td><td>Rs2</td><td>1</td></tr><tr><td>4bit Immediate</td><td>SATI</td><td>Rd1</td><td>#&lt;l&gt;1&lt;l&gt;1</td><td></td><td></td></tr><tr><td rowspan="2">Cordic</td><td>SIN/COS</td><td>SIN_COS</td><td>Rd1</td><td>Rd2</td><td>Rs1</td><td>8</td></tr><tr><td>Arctan/Module</td><td>ARCTAN</td><td>Rd1</td><td>Rs1</td><td>Rs2</td><td>8</td></tr><tr><td>Square root</td><td>Square root</td><td>SQRT</td><td>Rd1</td><td>Rs1</td><td>#&lt;l&gt;8</td><td></td></tr><tr><td rowspan="4">Memory access</td><td>Load word</td><td>LDRWI</td><td>Rd1</td><td>#&lt;l&gt;1</td><td></td><td></td></tr><tr><td>Load double half words</td><td>LDRDHI</td><td>Rd1</td><td>Rd2</td><td>#&lt;l&gt;1</td><td></td></tr><tr><td>Store word</td><td>STRWI</td><td>Rs1</td><td>#&lt;l&gt;1</td><td></td><td></td></tr><tr><td>Store double half words</td><td>STRDHI</td><td>Rs1</td><td>Rs2</td><td>#&lt;l&gt;1</td><td></td></tr><tr><td rowspan="4">Branch</td><td>Unconditional Jump</td><td>JUMP</td><td>Rs1</td><td>#&lt;l&gt;2</td><td></td><td></td></tr><tr><td>Immediate</td><td>JUMPI</td><td colspan="3">#&lt;l&gt;2</td><td></td></tr><tr><td>Jump if less than or equal to</td><td>JLE</td><td>Rs1</td><td>Rs2</td><td>Rs3</td><td>2</td></tr><tr><td>Immediate</td><td>JLEI</td><td>Rs1</td><td>Rs2</td><td>#&lt;l&gt;2</td><td></td></tr><tr><td>Miscellaneous</td><td>Generate IRQ and Pause DSP</td><td>IRQ</td><td colspan="3">#&lt;l&gt;1</td><td></td></tr></table>


</l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l></l>

DSP使用16bit定长编码指令，因为通用寄存器共8个，所以寄存器编码需要3bit。其中大部分指令为3操作数指令，包括两个源操作数寄存器和一个目的操作数寄存器；部分指令包含立即数；部分指令会涉及4个操作数，以乘加（MAC）操作为例， $\mathrm{Rd} = \mathrm{Rs}1*\mathrm{Rs}2 + \mathrm{Rs}3$ ，由于指令长度不够表示4个寄存器，将Rd固定为R7，在指令编码中不显示。其余4操作数指令还有ARCTAN/DIV。具体操作数分配见下文指令的详细解释。

# 15.3.2 ADD

15.3.2.1编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>Rs2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td></tr></table>

15.3.2.2汇编语法

ADD Rd1 Rs1 Rs2

15.3.2.3伪代码

$\mathrm{Rd1} = \mathrm{Rs1} + \mathrm{Rs2}$  结果防溢出保护，上溢出后  $\mathrm{Rd1} = 0\mathrm{x}7\mathrm{FFF}\_ \mathrm{FFF}$  下溢出后  $\mathrm{Rd1} = 0\mathrm{x}8000\_ 0000$

# 15.3.3 ADDI(reserved)

带立即数的加法指令在此版本DSP中保留，未实现。

15.3.3.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td colspan="4">Imm</td><td colspan="3">Rd1</td><td colspan="4">Rs1</td></tr></table>

立即数为5bit有符号数，表示数值范围是  $- 16\sim 15$

15.3.3.2汇编语法

ADDI Rd1 Rs1 Imm

15.3.3.3伪代码

$\mathrm{Rd1} = \mathrm{Rs1} + \mathrm{Imm}$  结果防溢出保护，上溢出后  $\mathrm{Rd1} = 0\mathrm{x}7\mathrm{FFF}\_ \mathrm{FFF}$

下溢出后  $\mathrm{Rd1} = 0\mathrm{x}8000\_ 0000$

# 15.3.4 SUB

15.3.4.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>Rs2</td><td></td><td>Rd1</td><td></td><td>Rs1</td><td></td><td></td><td></td><td></td></tr></table>

15.3.4.2汇编语法

SUB Rd1 Rs1 Rs2

15.3.4.3伪代码

$\mathrm{Rd1} = \mathrm{Rs1} - \mathrm{Rs2}$  结果防溢出保护，上溢出后  $\mathrm{Rd1} = 0\mathrm{x}7\mathrm{FFF}\_ \mathrm{FFF}$  下溢出后  $\mathrm{Rd1} = 0\mathrm{x}8000\_ 0000$

# 15.3.5 ASR

15.3.5.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>Rs2</td><td></td><td>Rd1</td><td></td><td>Rs1</td><td></td><td></td><td></td><td></td></tr></table>

15.3.5.2汇编语法

ASR Rd1 Rs1 Rs2

15.3.5.3伪代码

$$
\mathrm{Rd1} = \mathrm{Rs1} > > \mathrm{Rs2}
$$

算术右移指令只支持  $0\sim 31$  bit的右移。

# 15.3.6 ASRI

15.3.6.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>0</td><td>0</td><td>1</td><td>0</td><td>1</td><td colspan="4">Imm</td><td colspan="3">Rd1</td><td colspan="4">Rs1</td></tr></table>

立即数为5bit无符号数，表示数值范围是  $0\sim 31$

15.3.6.2汇编语法

ASRI Rd1 Rs1 Imm

15.3.6.3伪代码

$\mathrm{Rd1} = \mathrm{Rs1} > > \mathrm{Imm}$  带立即数的算术右移指令只支持0\~31bit的右移。

# 15.3.7 LSL

15.3.7.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>0</td><td>0</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td colspan="2">Rs2</td><td colspan="3">Rd1</td><td colspan="4">Rs1</td></tr></table>

15.3.7.2汇编语法

LSL Rd1 Rs1 Rs2

15.3.7.3伪代码

$$
\mathrm{Rd1} = \mathrm{Rs1} < < \mathrm{Rs2}
$$

逻辑左移只支持  $0\sim 31$  bit左移。

# 15.3.8 LSLI

15.3.8.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr></table>

<table><tr><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>Imm</td><td>Rd1</td><td>Rs1</td></tr></table>

立即数为5bit无符号数，表示数值范围是  $0\sim 31$

15.3.8.2汇编语法

LSLI Rd1 Rs1 Imm

15.3.8.3伪代码

$$
\mathrm{Rd1} = \mathrm{Rs1} < < \mathrm{Imm}
$$

带立即数的逻辑左移只支持  $0\sim 31$  bit左移。

15.3.9 MAC

15.3.9.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>Rs3</td><td>Rs2</td><td>Rs1</td><td></td><td></td><td></td><td></td><td></td></tr></table>

15.3.9.2汇编语法

MAC Rs1 Rs2 Rs3

15.3.9.3伪代码

$$
\mathrm{Rd7} = \mathrm{Rs1} \times \mathrm{Rs2} + \mathrm{Rs3}
$$

结果防溢出保护，

上溢出后  $\mathrm{Rd7} = 0\mathrm{x7}\mathrm{FFF}\_ \mathrm{FFF}$

下溢出后  $\mathrm{Rd7} = 0\mathrm{x8000\_0000}$

其中Rs1、Rs2为16位有符号数，Rs3为32位有符号数。注意，作为操作数的Rs1和Rs2不要超出16位有符号数的表达范围。当Rs3为R0时，MAC可以当做乘法指令MUL使用。

# 15.3.10 MACI (reserved)

带立即数的乘加指令在此版本DSP中保留，未实现。

15.3.10.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>0</td><td>1</td><td>0</td><td>0</td><td>1</td><td colspan="4">Imm</td><td colspan="3">Rs2</td><td colspan="4">Rs1</td></tr></table>

立即数为5bit有符号数，表示数值范围是- 16~15.

15.3.10.2汇编语法

MACI Rs1 Rs2 Imm

15.3.10.3伪代码

$\mathrm{Rd7} = \mathrm{Rs1}\times \mathrm{Rs2} + \mathrm{Imm}$  结果防溢出保护，上溢出后  $\mathrm{Rd7} = 0\mathrm{x7FFF\_FFF}$  下溢出后  $\mathrm{Rd7} = 0\mathrm{x8000\_0000}$

15.3.11 DIV

15.3.11.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td>1</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>Rd2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd2</td><td>Rd2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd0</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd0</td><td>Rd2</td><td>Rd2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd2</td><td>Rd2</td><td>Rd2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd0</td><td>Rd2</td><td>Rd0</td><td>Rd2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Ri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rli</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rir</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rrit</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rrib</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rii</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>R ri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rni</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rrri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>&lt;nl&gt;</td></tr></table>

15.3.11.2汇编语法

DIV Rd2 Rd1 Rs1

15.3.11.3伪代码

$\mathrm{Rd1} = \mathrm{Rd7} / \mathrm{Rs1},\mathrm{Rd2} = \mathrm{Rd7}\% \mathrm{Rs1}$

除法指令需要10个周期才会结束提交，在除法进行计算的过程中，DSP不应该再发射其他的多周期指令，即同一时刻只能由一个多周期指令在long- pipeline中。其他多周期指令包括三角函数指令以及开方指令。多周期指令可以后台运行，即多周期指令运算的同时，DSP可以继续执行其他的单周期指令。但同一时间只能有一条多周期指令在后台运行。在多周期指令计算期间，DSP仍可以使用多周期指令的目的操作数，但需要注意是当多周期计算完成提交结果的时候，目的操作数寄存器会被改写。

其中Rd7为32为有符号数，Rs1,为16为有符号数，Rd1为32位有符号数，Rd2为16位有符

号数。

# 15.3.12 SAT

15.3.12.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>Rs2</td><td></td><td>Rd1</td><td></td><td>Rs1</td><td></td><td></td><td></td></tr></table>

15.3.12.2汇编语法

SAT Rd1 Rs1 Rs2

15.3.12.3伪代码

If  $(\mathrm{Rd}1< \mathrm{Rs}1)$  Rd1  $\equiv$  Rs1;else if  $(\mathrm{Rd}1 > \mathrm{Rs}2)$  Rd1  $\equiv$  Rs2

# 15.3.13 SATI (reserved)

带立即数的饱和指令在此版本DSP中保留，未实现。

15.3.13.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td colspan="3">Imm2</td><td colspan="3">Imm1</td><td colspan="4">Rs1</td><td></td></tr></table>

15.3.13.2汇编语法

SATI Rd1 Imm1 Imm2

15.3.13.3伪代码

If  $(\mathrm{Rd}1< \mathrm{Imm}1)$  Rd1  $\equiv$  mm1;else if  $(\mathrm{Rd}1 > \mathrm{Imm}2)$  Rd1  $\equiv$  mm2

# 15.3.14 SIN_COS

15.3.14.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>Rd2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd2</td><td>Rd2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd0</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd0</td><td>Rd2</td><td>Rd2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd2</td><td>Rd2</td><td>Rd2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd0</td><td>Rd2</td><td>Rd0</td><td>Rd2</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rd1</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rdi</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Ri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rli</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rrit</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rir</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rrib</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rii</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>R ri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rrri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>Rri</td><td>&lt;nl&gt;</td></tr></table>

# 15.3.14.2汇编语法

SIN_COS Rd1 Rd2 Rs1

15.3.14.3伪代码

Sin/cos指令8周期结束并提交，在其执行期间，DSP不应该发射其他的多周期指令。

Rd1  $=$  cos(Rs1);Rd2  $=$  sin(Rs1)

# 15.3.15 ARCTAN

15.3.15.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>0</td><td>1</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>Rs2</td><td></td><td>Rd1</td><td></td><td>Rs1</td><td></td><td></td><td></td><td></td></tr></table>

15.3.15.2汇编语法

ARCTAN Rd1 Rs1 Rs2

15.3.15.3伪代码

ARCTAN指令8周期结束并提交，在其执行期间，DSP不应该发射其他的多周期指令。Rd1  $=$  arctan(Rs2/Rs1);  $\mathrm{R6} =$  sqrt(Rs1^2+Rs2^2)

# 15.3.16 SQRT

15.3.16.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>1</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>Rd1</td><td>Rs1</td><td></td><td></td><td></td></tr></table>

15.3.16.2汇编语法

SQRT Rd1 Rs1

15.3.16.3伪代码

开方指令8周期结束并提交，在其执行期间，DSP不应该发射其他的多周期指令。

Rd1  $=$  sqrt(Rs1)

# 15.3.17 LDRWI

15.3.17.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>1</td><td>0</td><td>1</td><td>0</td><td colspan="4">Imm</td><td>Rd1</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td></tr></table>

15.3.17.2汇编语法

LDRWI Rd1 Imm

15.3.17.3伪代码

Rd1  $=$  word(SRAM[imm])

由于Load指令都是立即数指令，访问的数据地址可以在译码阶段产生，因此load操作可以在一个周期内完成。而类似的load指令，CPU需要访问寄存器来计算地址，因此需要2个周期。

立即数imm的表达范围是  $0\sim 63$  。因为DSP datamem是64个32bitword构成。

# 15.3.18 LDRDHI

15.3.18.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>1</td><td>1</td><td>1</td><td>1</td><td colspan="4">Imm</td><td colspan="3">Rd1</td><td colspan="4">Rd2</td><td></td></tr></table>

15.3.18.2汇编语法

LDRDHI Rd1 Rd2 Imm

15.3.18.3伪代码

LDRDHI Rd1 Rd2

$\{\mathrm{Rd1,Rd2}\} =$  word(SRAM[Imm]),

从datamem取回的32bit数据高16位会进行符号扩展为32位，然后赋值给Rd1，低16位会进行符号扩展为32位，然后赋值给Rd2。

立即数imm的表达范围是  $0\sim 63$  。因为DSP datamem是64个32bitword构成。

# 15.3.19 STRWI

15.3.19.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>1</td><td>0</td><td>1</td><td>1</td><td colspan="5">Imm</td><td>0</td><td>0</td><td>0</td><td colspan="4">Rs1</td></tr></table>

15.3.19.2汇编语法

STRWI Rs1 Imm

15.3.19.3伪代码

word{SRAM[imm]}=Rs1

Store指令的数据来自寄存器，因此即使待写入地址在译码阶段产生也无法立即完成Store操作。需要将地址锁存一个周期，然后与写入的数据一起送至datamemory接口。因此Store指令后续如果立刻连接load指令会出现访问冲突。在设计汇编程序时应避免出现此种指令序列。如果STR指令后必须是LDR指令，可以在两者之间插入ADDR0R0R0指令作为指令bubble。

立即数imm的表达范围是  $0\sim 63$  。因为DSPdatamem是64个32bitword构成。

# 15.3.20 STRDHI (reserved)

带立即数的存储双半字指令在此版本DSP中保留，未实现。

15.3.20.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>1</td><td>0</td><td>0</td><td>0</td><td colspan="5">Imm</td><td colspan="3">Rs1</td><td colspan="4">Rs2</td></tr></table>

15.3.20.2汇编语法

STRDHI Rs1 Rs2 Imm

15.3.20.3伪代码

word{SRAM[imm]}={Rs1, Rs2}

立即数imm的表达范围是  $0\sim 63$  。因为DSPdatamem是64个32bitword构成。

# 15.3.21JUMP(reserved)

基于寄存器的跳转指令在此版本DSP中保留，未实现。

15.3.21.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>Rs1</td><td></td></tr></table>

15.3.21.2汇编语法

JUMP Rs1

15.3.21.3伪代码

$$
\mathrm{PC} = \mathrm{PC} + 1 + \mathrm{Rs}1
$$

15.3.22JUMPI

15.3.22.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>1</td><td>1</td><td>0</td><td>0</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

15.3.22.2汇编语法

JUMPI Imm

15.3.22.3伪代码

$$
\mathrm{PC} = \mathrm{PC} + 1 + \mathrm{IMM}
$$

15.3.23JLE

15.3.23.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>1</td><td>1</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>Rs3</td><td>Rs2</td><td>Rs1</td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

15.3.23.2汇编语法

JLE Rs1 Rs2 Rs3

15.3.23.3伪代码

$$
\mathrm{PC} = \mathrm{PC} + 1 + \mathrm{Rs}3,\mathrm{if}\left(\mathrm{Rs}1< = \mathrm{Rs}2\right)
$$

15.3.24 JLEI

15.3.24.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>1</td><td>1</td><td>0</td><td>1</td><td>1</td><td colspan="3">Imm</td><td colspan="2">Rs2</td><td colspan="6">Rs1</td></tr></table>

15.3.24.2汇编语法

JLEI Rs1 Rs2 Imm

15.3.24.3伪代码

$\mathrm{PC} = \mathrm{PC} + 1 + \mathrm{IMM},\mathrm{if}\left(\mathrm{Rs}1< = \mathrm{Rs}2\right)$

15.3.25 IRQ

15.3.25.1指令编码

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

15.3.25.2汇编语法

IRQ

15.3.25.3伪代码

IRQ指令会产生中断，等待CPU处理，并将DSP暂停运行。

# 15.3.26 R（仅用于模拟器）

15.3.26.1指令编码

无

15.3.26.2汇编语法

R50x5555 #Assign0x5555toR5 R120 #Assign20toR1

15.3.26.3伪代码

调试指令，仅在DSPEmulator中使用。可用于在DSP程序的任意位置将R1~R7置为任意指定数值。

# 15.3.27BREAK（仅用于模拟器）

15.3.27.1指令编码

无

15.3.27.2汇编语法

BREAK

15.3.27.3伪代码

调试指令，仅在DSPEmulator中使用。可用于在DSP程序的任意位置插入断点并打印R1~R7寄存器值。断点命中后按回车继续程序运行。

# 15.3.28END（仅用于模拟器）

15.3.28.1指令编码

无

15.3.28.2汇编语法

END

# 15.3.28.3伪代码

类似于断点指令，仅在DSP Emulator中使用。在指令模拟中遇到该指令即中断模拟器的运行，直接打印核心寄存器值。

# 15.4应用指南

# 15.4.1 访存寻址

DSP使用立即数寻址，由于DATAMEM地址空间有限，STR和LDR指令中的6bit立即数可以直接表示DATAMEM全部地址偏移。

以如下DATAMEM内容为例，第一行数据0x01000100对应0x0地址，第二行数据0x30005000对应0x1地址，第三行数据0x0003FFF8对应0x2地址。

使用LDRDHIR1R20x1可对R1,R2进行赋值  $\mathrm{R1 = 0x3000}$  ，  $\mathrm{R2 = 0x5000}$

使用STRWIR30x3可以将R3的32bit数据写入0x3地址并覆盖掉数据0xFFFE000。

需要注意的是，虽然DSP访存寻址每增加1是增加4Byte，对于CPU来说，每增加4地址才是增加4Byte。因此CPU访存DSPDATAMEM时，应该按照DSP_DATA_MEM_BASE+offset\*4的方式进行计算。以如下DATAMEM内容为例，第二行数据0x30005000对应的CPU寻址地址为0x4001_4804，第三行数据0x0003FFF8对应的CPU寻址地址为0x4001_4808。

DATAMEM:

0x00100010 0x30005000 0x0003FFF8 0xFFFFE000 0x30004000 0x7FFFFFFF 0x7FFFFFF 0xF0000003 0x00007FFF #8 0x00008000 0x80000000 0x00000000

# 15.4.2 Load after Store

DSP STR 指令之后不能立即使用 LDR，可在其间插入 “ADD R0 R0 R0” 作为 “NOP” 指令使用。

# 15.4.3 多周期指令的的延迟提交

DSP的多周期算术指令包括除法、开方、三角函数。除法指令需要10个总线周期（96MHz）完成。开方指令需要8个总线周期（96MHz）完成。三角函数指令需要8个总线周期（96MHz）完成。

为了充分利用DSP性能，允许多周期指令后台执行，即多周期指令计算期间DSP仍可其他指令，而不会阻塞流水线。这需要在编程时对指令序列有所考虑，在多周期指令的发射和结果使用之间插入其他不相关指令。如下指令序列，其中ADD R0 R0 R0作用类似NOP，在实际应用中可以替换为其他指令。

SIN_COS R1 R2 R3 ADD R0 R0 R0 ADD R0 R0 R0 ADD R0 R0 R0 ADD R0 R0 R0 ADD R0 R0 R0 ADD R0 R0 R0 ADD R0 R0 R0 LDRWI R4 0x10 MAC R1 R4 R0

# 15.4.4 数据填装

15.4.4 数据填装DATA MEM 支持按字、半字、字节写入。为了解决 AHB 总线协议写后立即读问题，SRAM 端口处有一个 word 深度的 cache。DSP CODE MEM 和 DATA MEM 由于允许 CPU 和 DSP 两个主设备访问，就存在一致性问题。举例来说，如图 15- 2 所示。CPU 先向 DSP DATAMEM 顺序写入 4 个 word，然后读取最后一个 word。由于 cache 的存在，最后一个 word 实际上留存在 cache 中，而没有真正写入 DSP DATAMEM，但 CPU 读取这一 word 数据时，命中 cache，所以直接从 cache 返回数据，读回的数据是正确的。但 DSP 读取 DATAMEM 时，则只能读取到前 3 个 word，留存在 cache 中的最后一个 word 是访问不到的。

![](images/9ed731cf418b83a7f274adad00bf3378b68c445d5b76ce3c6e5e3b06fde7f7ae.jpg)  
图15-2 CPU访问DSPMEM一致性问题

因此要求最后一次写入后需要再写任意一个其他地址，从而将停留在cache中的数据真实地写入DSPMEM。对于单一主设备的系统来说，所有的读写操作都通过接口上的cache，所以不会出现一致性问题，但由于DSP中的MEM被CPU写入后是由DSP经由另外的通道进行访问，所以需要通过一次冗余的写入操作实现cache数据推送，如图15- 3所示。

![](images/9f58465a32a691aed4d906399f7447143a968ca0eded2cc76ade05c5432a15c8.jpg)  
图15-3增加Dummy写操作解决DSPMEM一致性问题

同理，由于CPU最后一次读写的地址信号会留存在Cache中，如果之后DSP在运行中修改了DATA MEM数据。而后CPU读取DSP DATA MEM数据，如果命中CPU最后一次读写的地址，CPU会去cache中取数据，而不会从DSP DATA MEM取数，即CPU认为cache数据仍然有效，如。因此应用上应该CPU最后一次写入一个dummy数据方式来规避此种情况出现。

![](images/6812b6f5442a5816a8630fa6c17dd6ca56b6eeba4e7e4a28b8c9a105aa67d75c.jpg)  
图15-4 CPU因命中cache无法读取DSP DATA MEM真实数据

# 16 I2C

# 16.1概述

16.1 概述I2C 总线接口连接微控制器和串行 I2C 总线。它提供多主机功能，控制所有 I2C 总线特定的时序、协议、仲裁和定时。支持标准和快速两种模式。根据特定设备的需要，可以使用 DMA 以减轻 CPU 的负担。

# 16.2主要特性

多主机功能：该模块既可做主设备也可做从设备。

I2C主设备功能：产生时钟、START和STOP事件。

I2C从设备功能：可编程的I2C硬件地址比较（仅支持7位硬件地址）、停止位检测。

根据系统分频，实现不同的通讯速度。

状态标志：发送器/接收器模式标志、字节发送结束标志、I2C总线忙标志。

$\bullet$  错误标志：主模式时的仲裁丢失、地址/数据传输后的应答(ACK)错误、检测到错位的起始或停止条件。

$\bullet$  一个中断向量，包含五个中断源：总线错误中断源、完成中断源、NACK中断源、硬件地址匹配中断源和传输完成中断源。

$\bullet$  具单字节缓冲器的DMA。

# 16.3功能描述

# 16.3.1 功能框图

本接口采用同步串行设计，实现CPU同外部设备之间的I2C传输。支持轮询和中断方式获得传输状态信息。本接口的主要功能模块如下图所示。

![](images/93dd0b6825d1ffac4452aa674e8d976468807b37f777d081a8232f17d54d16da.jpg)  
图16-1 I2C模块顶层功能框图

I2C接口同外界通讯只有SCL和SDA两根信号线。SDA为双向复用信号线，受到sda_oe控制。模块级，I2C接口信号包括，scl_i，sda_i，scl_o，sda_o和sda_oe。

scl_i：时钟信号。当I2C接口配置为从模式时，此为I2C总线的时钟输入信号。

sda_i：数据信号。当I2C接口接收数据时（无论主模式还是从模式），此为I2C总线的数据输入信号。

scl_o：时钟信号。当I2C接口配置为主模式时，此为I2C总线的时钟输出信号。

sda_o：数据信号。当I2C接口发送数据时（无论主模式还是从模式），此为I2C总线的数据输出信号。

sda_oe：数据使能信号。当sda_o输出时，sda_oe有效；当sda_i输入时，sda_oe无效。

# 16.3.2 功能说明

12C模块接收和发送数据，并将数据从串行转换成并行，或并行转换成串行。可以开启或禁止中断。接口通过数据引脚(SDA)和时钟引脚(SCL)连接到I2C总线。

# 16.3.2.1 模式选择

接口可以下述4种模式中的一种运行：

从发送模式从接收模式主发送模式主接收模式

I2C接口默认主从均不使能。接口根据配置情况，进入主模式或者从模式。当仲裁丢失或产生停止信号时，主模式自动释放总线并产生相应异常中断。允许多主机功能。

主模式时，I2C接口启动数据传输并产生时钟信号。串行数据传输总是以起始条件开始并以停止条件结束。起始条件和停止条件都是在主模式下由软件控制产生。

从模式时，I2C接口能识别它自己的地址(7位)。软件能够控制开启或禁止硬件地址比较功能，

硬件地址比较功能可降低CPU的负担。只有地址匹配才通知CPU进行相关处理。

数据和地址按8位/字节进行传输，高位在前。跟在起始条件后的1个字节是地址。地址只在主模式发送。

在一个字节传输的8个时钟后的第9个时钟期间，接收器必须回送一个应答位(ACK)给发送器。

软件可以开启或禁止应答(ACK)，并可以设置I2C接口的地址。

![](images/5b0bfb2ed9014fbb18610a42ac854f7291e6b1e734eb29f3fbf35d204cc419bc.jpg)  
图16-2基本I2C传输时序图

I2C接口没有FIFO，若一次性发送大量数据，为了降低CPU的负担，需DMA配合。I2C接口支持DMA传输（多字节传输）和非DMA传输（单字节传输)。上述四种传输模式进一步扩展为：

从模式单字节发送，从模式DMA发送从模式单字节接收，从模式DMA接收主模式单字节发送，主模式DMA发送主模式单字节接收，主模式DMA接收

一般情况下，非DMA方式时，一次传输一个字节（可反复单次传输，需软件介入提供数据)。DMA方式，一次连续传输可以多字节(最大不超过16字节，极端情况一次传输一个字节，因无FIFO，每次DMA请求，仅传输一个字节，多轮完成本次数据传输)。

上述所有模式，遵循如下基本原则：

单字节发送，中断将在8- bit数据发送完毕且收到响应后（ACK/NACK均可）产生。- 单字节接收，中断将在8- bit数据接收完毕后产生。- DMA发送，正常情况下，中断将在数据发送完毕且收到响应后（ACK/NACK均可）产生。- DMA接收，正常情况下，中断将在数据接收完毕后产生。- 当I2C接口配置为主模式时，检测到错误后，I2C接口会主动释放总线，恢复到起始状态并产生中断信号。

# 16.3.2.2I2C接口从模式

默认情况下，I2C接口主模式和从模式均关闭。若工作在从模式，需使能从模式。为了产生正确的时序，必须通过系统寄存器SYS_CLK_DIV0设定I2C接口的工作时钟频率，I2C接口时钟基于系统高速主时钟进行分频，SYS_CLK_DIV0是I2C接口工作时钟的分频系数。

从模式下，I2C接口时刻在监控总线上的信号。一旦检测到起始条件，其将保存地址位数据和读写位数据。

- 从模式下，若硬件地址匹配功能开启，只有地址匹配的情况下，才会产生中断，通知 CPU 进行后续处理。若没有开启，每次收到地址及读写位数据，都将产生中断。- 从模式下，单字节接收模式。每次收到一个字节的数据后，产生中断，此时 I2C 接口可拉低 SCL，直至中断完成，继续后续操作。- 从模式下，单字节发送模式。每次发送一个字节完毕后且收到响应（ACK/NACK），产生中断，此时 I2C 接口可拉低 SCL，直至中断完成，继续后续操作。- 从模式下，DMA 接收模式。每次收到 SIZE 约定后的数据，产生中断，此时 I2C 接口可拉低 SCL，直至中断完成。- 从模式下，DMA 发送模式。每次发送 SIZE 约定后的数据并收到响应（ACK/NACK），产生中断，此时 I2C 接口可拉低 SCL，直至中断完成。

# 16.3.2.2.1 从模式单字节传输

单字节传输，并不意味着仅仅传输一个字节数据，其含义为每次传输完一个字节的数据后，将产生中断判断是否还要继续传输。单字节传输的极端情况是仅传输一个字节的数据。下图为单字节传输的总线示意图。从图可知，一般单字节传输的流程如下：

- 地址匹配，产生地址匹配中断，准备开始传输。- 若是接收模式，一个字节接收完毕后，产生中断，软件判断是否继续接收，返回 ACK/NACK 响应。- 若是发送模式，一个字节发送完毕后，等待响应（ACK/NACK），产生中断，根据响应判断后续操作。- 获得总线 STOP 事件，本次传输完成。

![](images/83bd22607c572f89861d2c50ebdd0dcb683c29524afa87c22dd6e29bfebb5ffd.jpg)

# 16.3.2.2.2 从模式单字节发送

地址匹配后，从发送器将字节从I2C_DATA寄存器经由内部移位寄存器发送到SDA线上。在I2C_DATA数据没有准备好之前，从设备可拉底SCL，直到待发送数据已写入I2C_DATA寄存器。I2C接口在发送完毕每个字节后都执行下列操作：

$\bullet$  如果接收到ACK位，装载下一个字节数据，继续传输。装载过程中，可拉底SCL。 $\bullet$  如果接收到NACK位，停止下一个字节的装载。 $\bullet$  等待STOP事件，停止本次传输。

# 16.3.2.2.3 从模式单字节接收

地址匹配后，从接收器将通过内部移位寄存器从SDA线接收到的数据存入I2C_DATA寄存器。I2C接口在接收到每个字节后都执行下列操作：

$\bullet$  如果设置了ACK位，在一个字节接收完毕后，产生一个ACK应答脉冲。 $\bullet$  如果清除了ACK位，在一个字节接收完毕后，产生一个NACK应答脉冲。 $\bullet$  等待STOP事件，结束本次传输。

# 16.3.2.3从模式DMA传输

从模式下，一般仅配置I2C时钟、从地址以及硬件地址匹配使能，等待总线有访问请求后，根据芯片实际情况决定是否响应本次传输请求。DMA传输，其含义为每次传输多个字节的数据后，将产生中断判断是否还要继续传输。DMA传输的极端情况是仅传输一个字节的数据。DMA传输，一般建议开启硬件地址比较功能，NACK中断，传输完成中断。一般DMA传输的流程如下：

$\bullet$  配置I2C从地址，使能I2C中断（可使能硬件地址比较中断)。地址匹配，产生I2C地址匹配中断，在中断处理函数中，配置DMA，准备好发送数据或者准备好接收地址。然后写I2CSCR，准备开始传输或者停止本次传输。 $\bullet$  若是接收模式，I2C_BOR_BURST_SIZE约定的字节接收完毕后，产生中断，软件判断是否继续接收，返回ACK/NACK响应。 $\bullet$  若是发送模式，I2C_BOR_BURST_SIZE约定的字节发送完毕后，等待响应（ACK/NACK），产生中断，根据响应判断后续操作。 $\bullet$  获得总线完成标志，本次传输完成。

# 16.3.2.3.1 从模式DMA发送

地址匹配后，配置完毕DMA。通过发送DMA请求，将字节从RAM搬移到I2C_DATA寄存器，然后经由内部移位寄存器发送到SDA线上。在I2C_DATA数据没有准备好之前，从设备可拉底SCL，

直到待发送数据已写入 I2C_DATA 寄存器。从模式下发送数据，需要软件协助触发第一次 DMA 搬移，配置 I2C_BCR.BYTE_CMPLT 为 1 即可。I2C 接口在发送完毕 I2C_BCR.BURST_SIZE 约定的字节数据后都执行下列操作：

$\bullet$  如果接收到ACK位，配置DMA，准备下一批数据，继续传输。准备过程中，可拉低SCL。 $\bullet$  如果接收到NACK位，停止准备下一批数据，停止本次传输。

![](images/b0b4fe5ea6ac8b91bf842fb2e5f560a13eb0ad4068dfb8f5d6cace3169f9e5df.jpg)  
图16-4从模式下多字节发送示意图

# 16.3.2.3.2 从模式DMA接收

地址匹配后，配置好DMA，从SDA线接收到的数据先存入I2C_DATA寄存器，然后通过DMA搬移到RAM。I2C接口在接收到一个字节后都将执行DMA请求。完成I2C_BCR.BURST_SIZE约定的数据传输后，执行下列操作：

$\bullet$  如果设置了ACK位，在I2C_BCR.BURST_SIZE约定数据接收完毕后，产生一个ACK应答脉冲。 $\bullet$  如果清除了ACK位，在I2C_BCR.BURST_SIZE约定数据接收完毕后，产生一个NACK应答脉冲。

![](images/517370bdcf84dad7e52bdb059be5fe8f5c77493f8b9bd7d655f9590ed109d76e.jpg)  
图16-5从模式下多字节接收示意图

# 16.3.2.4I2C接口主模式

默认情况下，I2C接口主模式和从模式均关闭。若工作在主模式，需使能主模式。为了产生正确的时序，必须在系统寄存器CLK_DIV0中设定I2C接口的工作时钟。

I2C接口执行主模式传输之前，需要判断总线是否空闲。可读取I2C_MSCR寄存器的BIT3，查

询当前总线状态。若总线处于忙的状态，可以开启 I2C 中断，通过收到 STOP 中断事件判断总线是否空闲下来。只有空闲状态下，才能正常发送 START 状态，以及后续的数据。

# 16.3.2.4.1 主模式单字节传输

单字节传输，并不意味着仅仅传输一个字节数据，其含义为每次传输完一个字节的数据后，将产生中断判断是否还要继续传输。单字节传输的极端情况是仅传输一个字节的数据。图 6 为单字节传输的总线示意图。从图可知，一般单字节传输的流程如下：

- 判断总线是否空闲，若空闲，准备开始传输。- 若是接收模式，一个字节接收完毕后，产生中断，软件判断是否继续接收，返回 ACK/NACK 响应。- 若是发送模式，一个字节发送完毕后，等待响应（ACK/NACK），产生中断，根据响应判断后续操作。- 发送总线 STOP 事件，本次传输完成。

![](images/841b9ad6f75de6b6075666c3beec5393755535726b7191b35c3b7bfd5b6534f0.jpg)  
图 16-6 主模式下单字节传输示意图

# 16.3.2.4.2 主模式单字节发送

开始传输后，I2C 接口将字节从 I2C_DATA 寄存器经由内部移位寄存器发送到 SDA 线上。在 I2C_DATA 数据没有准备好之前，主设备可不产生 SCL 时钟信号，直到待发送数据已写入 I2C_DATA 寄存器。I2C 接口在发送完毕每个字节后都执行下列操作：

- 如果接收到 ACK 位，装载下一个字节数据，继续传输。装载过程中，可拉底 SCL。

- 如果接收到 NACK 位，停止下一个字节的装载。

- 产生 STOP 事件，结束本次传输。

# 16.3.2.4.3 主模式单字节接收

开始传输后，I2C接口将通过内部移位寄存器从SDA线接收到的数据存入I2C_DATA寄存器。I2C接口在接收到每个字节后都执行下列操作：

$\bullet$  如果设置了ACK位，在一个字节接收完毕后，产生一个ACK应答脉冲。 $\bullet$  如果清除了ACK位，在一个字节接收完毕后，产生一个NACK应答脉冲。 $\bullet$  产生STOP事件，结束本次传输。

# 16.3.2.4.4 主模式DMA传输

DMA传输，其含义为每次传输多个字节的数据后，将产生中断判断是否还要继续传输。DMA传输的极端情况是仅传输一个字节的数据。DMA传输，一般建议开启NACK中断，传输完成中断。一般DMA传输的流程如下：

总线空闲，准备开始传输。- 若是接收模式，I2C_BCR.BURST_SIZE约定的字节接收完毕后，产生中断，软件判断是否继续接收，返回ACK/NACK响应。- 若是发送模式，I2C_BCR.BURST_SIZE约定的字节发送完毕后，等待响应（ACK/NACK），产生中断，根据响应判断后续操作。- 发送STOP事件，本次传输完成。

# 16.3.2.4.5 主模式DMA发送

总线空闲，配置完毕DMA。通过发送DMA请求，将字节从RAM搬移到I2C_DATA寄存器，然后经由内部移位寄存器发送到SDA线上。在I2C_DATA数据没有准备好之前，主设备可不产生SCL时钟，直到待发送数据已写入I2C_DATA寄存器。I2C接口在发送完毕SIZE约定的字节数据后都执行下列操作：

如果接收到ACK位，配置DMA，准备下一批数据，继续传输。准备过程中，可拉低SCL。

如果接收到NACK位，停止加载下一批数据。

如果本次数据发送完毕，停止后续发送。

产生STOP事件，停止本次传输。

异常情况是：

若从设备地址不匹配或者从设备没有准备好，此时从设备将返回NACK

主设备产生STOP事件，停止本次传输。

等待一段时间后，重新配置I2C寄存器，关闭DMA对应的通道使能信号，重新配置DMA寄存器，再次发送传输请求。关闭DMA对应通道是因为I2C有预取，DMA已经不是初始状态。

![](images/8b77e196562c4874c0d34c7b62fa5bb004ed508726668f03ac453c5d331ff3ee.jpg)  
图16-7主模式下多字节发送示意图

# 16.3.2.4.6 主模式DMA接收

总线空闲，配置好DMA从SDA线接收到的数据先存入I2C_DATA寄存器，然后通过DMA搬移到RAM。I2C接口在接收到一个字节后都将执行DMA请求。完成I2C_BCR.BURST_SIZE约定的数据传输后，执行下列操作：

- 如果设置了ACK位，在I2C_BCR.BURST_SIZE约定数据接收完毕后，产生一个ACK应答脉冲。- 如果清除了ACK位，在I2C_BCR.BURST_SIZE约定数据接收完毕后，产生一个NACK应答脉冲。- 产生STOP事件，停止本次传输。异常情况是：- 若从设备地址不匹配或者从设备没有准备好，此时从设备将返回NACK。- 主设备产生STOP事件，停止本次传输。- 等待一段时间后，重新配置I2C寄存器，再次发送传输请求。因为上一次没有收到有效数据，DMA并没有任何动作，所以不用重置DMA。

![](images/a4fa600b963586c24bed2ec85187f882bcc5f24decd57d1298d6256499e09c2c.jpg)  
图16-8主模式下多字节接收示意图

# 16.3.2.5I2C总线异常处理

在一个地址或数据字节传输期间，当I2C接口检测到一个外部的停止或起始条件则产生总线错误。一般而言，产生总线错误是由于总线上有干扰、某些I2C设备没有同步于本I2C网络自行发送了START事件/STOP事件。根据I2C协议规定，发生总线错误的时候，在收到START事件/STOP事件后要重置本I2C设备的接口逻辑。对于从设备而言，这个操作是没有问题的；对于主设备而言，总线错误强行要求其释放总线并重置其I2C接口逻辑。因为主设备是不响应外部START和STOP事件的，发生总线错误后，需要中断处理函数处理本次异常，并指导主设备继续监视总线情况，以便后续执行I2C总线传输。

本I2C接口。主模式下，总线错误可被检测到同时总线错误中断也会产生；从模式下，总线错误将触发地址数据被接收，同时让I2C接口恢复空闲状态并产生中断。

# 16.3.2.6DMA传输

在大容量数据传输应用下，I2C接口支持DMA传输，减轻CPU的负担。一次传输，最大传输量为16字节，最小传输量为1字节。因I2C无FIFO，I2C发送一次DMA请求，DMA只能搬移一个字节数据。若要实现多字节搬移，DMA需配置为多轮搬移，每一轮搬移一个字节的方式。

在接收到新的数据后，硬件自动产生DMA请求，通过DMA模块将数据搬移到RAM中。在发送新数据前，硬件自动产生DMA请求，通过DMA模块将数据从RAM中搬移到I2C接口。

DMA传输需要配置DMA模块相应寄存器

因I2C接口支持DMA传输，也支持CPU传输。两者区别在于DMA传输，发送的数据来自DMA的搬移；CPU传输，发送的数据来自CPU的搬移。

DMA传输，推荐软件配置流程如下：

初始化DMA模块，将本次发送的数据来源，接收的数据去向配置好，传输长度配置完毕。

初始化GPIO模块，将I2C复用的GPIO配置完毕。

初始化I2C接口，I2C_CFG/I2C_BCR等寄存器配置完毕。

主模式下，触发I2C接口，进入发送状态；从模式下，等待主发送传输请求。

若I2C接口为从发送模式，需要考虑预取，I2C_BCRB[4]为预取开关。一般从模式传输的时候，可以开启硬件地址比较(I2C_A00R B[7])，可选择是否开启硬件地址比较中断使能(I2C_BCR B[6])。

开启硬件地址比较中断，从设备收到的地址同自身匹配成功后，会产生中断。通知软件此时主设备请求获得从设备数据，软件判断是否接收，若接收就回ACK，软件需要I2C_BCR B[4]置1，协助硬件预取第一次传输的数据；否则就回NACK。

关闭硬件地址比较中断，一旦总线上出现START事件，从设备硬件预取第一次传输数据，无论从设备是否地址匹配成功。匹配成功，也不会产生地址匹配中断，直接开始数据传输。匹配不成功，从设备不会传输数据。此时，若匹配不成功，因为I2C有预取的操作，为后续匹配成功后传输正常，需要对DMA进行清除操作。

# 16.3.2.7CPU传输

CPU传输，一次只能发送/接收1个字节，每次完成后需要通过中断或者轮询的方式判断传输是否完成。

CPU传输，推荐软件配置流程如下：

初始化GPIO模块，将I2C复用的GPIO配置完毕。- 初始化I2C接口，IE/CFG等寄存器配置完毕。- CPU触发I2C接口进入发送流程，发送的数据来自CPU对I2C_DATA写入值。

# 16.3.2.8中断处理

I2C接口包含三种类型的中断事件，分别是：数据传输完成事件，总线错误事件、STOP事件、NACK事件和硬件地址匹配事件。

数据完成事件。当前数据传输完成，高电平有效，对I2CSCR的BIT0写0清除。- 总线错误事件。传输过程中，总线产生错误的START事件/STOP事件，高电平有效，对I2CSCR的BIT7写0清除。- STOP事件。当前数据传输完成，主设备发送STOP事件，从设备收到STOP事件并产生相应中断。高电平有效，对I2CSCR的BIT5写0清除。- NACK事件。发送端接收到NACK响应，表明接收端无法继续后续传输。高电平有效，对I2CSCR的BIT1写0清除。- 硬件地址匹配事件。从模式下接收到的地址同本设备地址匹配，产生相应中断。高电平有效，对I2CSCR的BIT3写0清除。- 使用DMA协助数据传输。若本模块为接收模式，I2C收到数据后还需要通过DMA搬移到RAM，此时数据最终完成是要看DMA是否搬移完成，若使用I2C的完成中断作为判断依据的话，推荐在中断处理函数中查询下DMA的状态。若本模块为发送模式，无此问题。直接使用I2C的完成中断作为判断依据即可。

# 16.3.2.9通讯速度设置

I2C模块的波特率时钟来自系统时钟的分频，分频寄存器为SYS模块的CLK_DIV0。

I2C接口采用同步设计，需要对外部设备的信号进行同步采样，同步时钟为I2C接口工作时钟。数据和时钟信号的时钟频率为接口工作时钟/17。

I2C模块工作时钟频率  $\equiv$  系统频率/  $(\mathrm{CLK\_DIV0} + 1)$

I2C波特率：I2C波特率  $=$  （系统频率/  $(\mathrm{CLK\_DIV0} + 1)$  ）/17

# 16.4 寄存器

# 16.4.1 地址分配

I2C 模块寄存器的基地址是 0x4001_0400，寄存器列表如下：

表16-1I2C寄存器地址分配表  

<table><tr><td>名称</td><td>偏移</td><td>说明</td></tr><tr><td>I2C0_ADDR</td><td>0x00</td><td>I2C 地址寄存器</td></tr><tr><td>I2C0_CFG</td><td>0x04</td><td>I2C 配置寄存器</td></tr><tr><td>I2C0_SCR</td><td>0x08</td><td>I2C 状态寄存器</td></tr><tr><td>I2C0_DATA</td><td>0x0C</td><td>I2C 数据寄存器</td></tr><tr><td>I2C0_MSCR</td><td>0x10</td><td>I2C 主模式寄存器</td></tr><tr><td>I2C0_BCR</td><td>0x14</td><td>I2C DMA 传输控制寄存器</td></tr></table>

# 16.4.2 寄存器说明

16.4.2.1 I2C0_ADDR 地址寄存器

地址：0x4001_0400

复位值：0x0

表16-2地址寄存器I2C0_ADDR  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="6"></td><td>ADDR_CMP</td><td colspan="8">ADDR</td><td></td></tr><tr><td>RW</td><td colspan="8">RW</td><td></td></tr><tr><td>0</td><td colspan="8">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7]</td><td>ADDR_CMP</td><td>I2C 硬件地址比较使能开关，只有在 DMA 模式下开启才有效。默认值为 0。
1：使能
0：关闭</td></tr><tr><td>[6:0]</td><td>ADDR</td><td>从模式下，I2C 设备硬件地址。主模式下，仅在 DMA 模式下，才需填入从设备地址；否则，从设备地址写入 I2C_DATA 寄存器。</td></tr></table>

# 16.4.2.2 I2C0_CFG 系统控制寄存器

地址：0x4001_0404

复位值：0x0

表16-3系统控制寄存器I2C0_CFG  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7]</td><td>IE</td><td>I2C 中断使能信号。默认值为 0。
1：使能 I2C 中断
0：关闭 I2C 中断</td></tr><tr><td>[6]</td><td>TC_IE</td><td>I2C 数据传输完成中断使能信号。默认值为 0。
1：使能此中断源
0：屏蔽此中断源</td></tr><tr><td>[5]</td><td>BUS_ERR_IE</td><td>I2C 总线错误事件中断使能信号。默认值为 0。
1：使能此中断源
0：屏蔽此中断源</td></tr><tr><td>[4]</td><td>STOP_IE</td><td>I2CSTOP 事件中断使能信号。默认值为 0。
1：使能此中断源
0：屏蔽此中断源</td></tr><tr><td>[3:2]</td><td></td><td>NA</td></tr><tr><td>[1]</td><td>MST_MODE</td><td>I2C 主模式使能信号。默认值为 0。
1：使能主模式
0：关闭主模式</td></tr><tr><td>[0]</td><td>SLV_MODE</td><td>I2C 从模式使能信号。默认值为 0。
1：使能从模式
0：关闭从模式</td></tr></table>

# 16.4.2.3 I2C0_SCR 状态控制寄存器

地址：0x4001_0408

复位值：0x0

表16-4状态控制寄存器I2C0SCR  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td>STT_ERR</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RX</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td colspan="2">未使用</td></tr><tr><td>[7]</td><td>STT_ERR</td><td>总线错误状态标志位，仅用于主模式下，写 0 清除。
0：无 START/STOP 总线错误
1：有 START/STOP 总线错误</td></tr><tr><td>[6]</td><td>LOST_ARB</td><td>总线仲裁丢失状态标志位，仅用于主模式下，发生总线仲裁丢失事件将此位置 1，无中断事件产生，在字节完成中断中需查此位。
总线上任何 START 事件将导致硬件清除此位。
0：无总线仲裁丢失错误发生
1：有总线仲裁丢失错误发生</td></tr><tr><td>[5]</td><td>STOP_EVT</td><td>STOP 事件状态标志位，主从模式均可使用，写 0 清除。
0：无 STOP 事件
1：有 STOP 事件</td></tr><tr><td>[4]</td><td>BYTE_CMPLT</td><td>ACK 发生控制位，主从模式均可使用。发送前配置好改位。单字节模式下，发送字节完毕后硬件自动清除；多字节模式下，全部发送完毕后硬件自动清除。
0：字节发送完成，返回 NACK 回应
1：字节发送完成，返回 ACK 回应</td></tr><tr><td>[3]</td><td>ADDR_DATA</td><td>Address 数据标志位，主从模式均可使用，写 0 清除。
0：发送或接收到的数据非 Address 数据
1：发送或接收到的数据是 Address 数据</td></tr><tr><td>[2]</td><td>DATA_DIR</td><td>发送或接收控制位，主从模式均可使用，通过此位决定数据传输方向。总线上 START 事件可清除此位，同时也可写 0 清除此位。
0：接收
1：触发发送</td></tr><tr><td>[1]</td><td>RX_ACK</td><td>接收响应标志位，主从模式均可使用，总线上 START 事件可清除此位，同时也可写 0 清除此位。
0：本 I2C 接口发送数据，接收到 ACK 响应
1：本 I2C 接口发送数据，接收到 NACK 响应</td></tr><tr><td>[0]</td><td>Done</td><td>传输完成状态标志位，主从模式均可使用，总线上 START 事件可清除此位，同时也可写 0 清除此位。
0：传输未完成
1：传输已完成</td></tr></table>

一般，进入中断后，需读取 I2C_SCR 寄存器，获得当前 I2C 总线状态及当前传输处于什么阶段；然后，对 I2C_SCR 进行写操作，写入不同的值，软件通知硬件下一步如何处理。

# 16.4.2.4 I2C0_DATA 数据寄存器

地址：0x4001_040C

复位值：0x0

# 表16-5数据寄存器I2C0_DATA

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr></table>

<table><tr><td rowspan="3"></td><td>DATA</td></tr><tr><td>RW</td></tr><tr><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>DATA</td><td>数据寄存器，主从模式均可使用。对寄存器写入，数据进入 I2C 内部发送部分，无法直接读取到刚写入数据。读出操作，获得 I2C 接收到的数据。主/从接收模式：存放接收的数据。单字节传输，需等待完成中断；多字节传输，数据会被 DMA 搬移到 RAM，仅保留最后一个字节。从发送模式：存放发送的数据。一般先填好数据，然后触发 I2C_SCR 的 BIT[2]。多字节传输，数据会被 DMA 从 RAM 搬移到 I2C_DATA，然后由 I2C 接口发送。主发送模式：单字节传输，I2C_DATA 填入地址；多字节传输，I2C_ADDR 填入地址，I2C_DATA 数据由 DMA 传输。</td></tr></table>

# 16.4.2.5 I2C0_MSCR 主模式寄存器

地址：0x4001_0410

复位值：0x0

表16-6主模式寄存器I2C0_MSCR  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="9"></td><td>BUSY</td><td>MST_CHECK</td><td>RESTART</td><td>START</td><td></td><td></td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:4]</td><td></td><td>未使用</td></tr><tr><td>[3]</td><td>BUSY</td><td>I2C 总线，闲忙状态。1，检测到 START 事件，忙碌；0，检测到 STOP 事件，空闲。</td></tr><tr><td>[2]</td><td>MST_CHECK</td><td>主模式争抢总线标志位。争抢到总线，置 1；STOP 事件或者发生总线冲突本模块释放总线，置 0。</td></tr><tr><td>[1]</td><td>RESTART</td><td>再次触发 START 事件，写 1 有效。发送 START 完毕，硬件清 0。I2C_CFG[1] 置 1，才能实现写 1 操作。</td></tr><tr><td>[0]</td><td>START</td><td>触发 START 事件并发送地址数据至总线，写 1 有效。I2C_CFG[1] 置 1，才能实现写 1 操作。</td></tr></table>

# 16.4.2.6I2C0_BCRDMA传输控制寄存器

地址：0x4001_0414

复位值：0x0

表16-7DMA传输控制寄存器I2C0BCR  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td></td></tr><tr><td></td></tr><tr><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7]</td><td>BURST_NACK</td><td>I2C 传输，NACK 事件中断使能信号。
1：使能此中断源
0：屏蔽此中断源</td></tr><tr><td>[6]</td><td>BURST_ADDR_CMP</td><td>I2C 传输，硬件地址匹配中断使能信号。
1：使能此中断源
0：屏蔽此中断源</td></tr><tr><td>[5]</td><td>BUSRT_EN</td><td>I2C 多数据传输使能，需要采用 DMA 方式。
1：使能
0：关闭</td></tr><tr><td>[4]</td><td>SLV_DMA_PREF</td><td>I2C 多数据传输。从模式执行 DMA 方式发送，触发硬件预取第一个字节。硬件自动清零。
1：使能
0：关闭</td></tr><tr><td>[3:0]</td><td>BURST_SIZE</td><td>I2C 数据传输长度寄存器，用于多字节传输。
实际传输字节数 = B[3:0] + 1</td></tr></table>

# 17 SPI

# 17.1概述

17.1 概述SPI 接口主要使用在，外部设计采用 SPI 协议的应用场景下。SPI 的工作模式软件可选，默认为 SPI Motorola 模式。SPI 接口支持全双工传输和半双工传输。当接口配置为 Master 模式时，可发送时钟信号供外部 Slave 设备使用。

# 17.2主要特性

17.2 主要特性- 支持 Master 和 Slave 操作- 全双工传输，可根据应用情况，使用 3 根或者 4 根信号线- 支持半双工传输，可根据应用情况，使用 2 根信号线- 可编程的时钟极性和相位- 可编程的数据顺序：MSB 或 LSB- 最快传输速度为系统最高时钟频率的 1/8- 片选信号均可选。Master 模式下，片选信号可以软件控制也可以硬件产生；Slave 模式下，片选信号可以恒定有效，也可以来自外界设备- 无本地 FIFO，支持 DMA 操作。包含溢出检测和片选信号异常检测

# 17.3功能描述

# 17.3.1 功能框图

本接口采用同步串行设计，实现CPU同外部设备之间的SPI传输。支持轮询和中断方式获得传输状态信息。本接口的主要功能模块如下图所示。

![](images/bb2e54ef4ad176782d68952359794f8f3693e882fd3b0151a0aaba389ce32c3a.jpg)

接口信号包括，spi_din，spi dout，sclk_in，sclk_out，ss_in和ss_out。

spi_din：接口接收的数据信号。同SPI协议比较，当接口配置为Master模式时，其等效为MISO；当接口配置为Slave模式时，其等效为MOSI。

spi dout：接口发送的数据信号。同SPI协议比较，当接口配置为Master模式时，其等效为MOSI；当接口配置为Slave模式时，其等效为MISO。

sclk_in：接口接收的时钟信号。此时，接口的工作模式为Slave。非Slave模式下，此信号输入无效。

sclk_out：接口发送的时钟信号。此时，接口的工作模式为Master，非Master模式下，此信号输出恒定为0。

ss_in：接口接收的片选信号。此时，接口的工作模式为Slave。非Slave模式下，此信号输入无效。

ss_out：接口发送的片选信号。此时，接口的工作模式为Master。非Master模式下，此信号输出恒定为1。

# 17.3.2 功能说明

# 17.3.2.1 全双工模式

默认情况下，SPI接口配置为全双工模式。此时，数据传输需要两根数据线。数据信号的变化，发生在时钟信号的边沿，即同步于时钟信号。

接口为Master模式时：

spi_dout为数据输出，接外部Slave设备的MOSIspi_ss_out为片选信号，根据应用情况选择是使用该信号还是软件控制其它GPIO实现

接口为Slave模式时：

spi_dout为数据输出，接外部Slave设备的MISOspi_ss_in为片选信号，根据应用情况是使用该信号还是片选恒有效

![](images/22bf66d4ec29d36bd23485fdd2850232ff0a60910c9053c1a950a85d1f7cd449.jpg)  
图17-2 SPI接口全双工模式互连框图

从上图可知，GPIO若配置为输出，则SPI接口可发送数据；GPIO若配置为输入，则SPI接口可接收数据。亦即SPI_DI关闭GPIO输入使能且开启GPIO输出使能时，即可作为SPI_DO使用，SPI_DO关闭GPIO输出使能且开启GPIO输入使能时，即可作为SPI_DI使用。

# 17.3.2.2 半双工模式

SPI接口可配置为半双工模式。此时，数据传输只需要一根数据线。数据信号的变化，发生在时钟信号的边沿，即同步于时钟信号。一次传输只能是一个方向的，要不就是发送，要不就是接收。

![](images/24155b6c427e7ef37528df767d4bc7dae809f1b3675ecae01adbd5cf1ab9be2a.jpg)  
图17-3 SPI接口半双工模式互连框图

注意，上图中若本接口做Master，则clk为本接口的输出信号；若本接口做Slave，则clk为本接口的输入信号。

仅发送

CFG[7:6]配置为2，半双工发送模式有效。此时，本接口只能发送数据。GPIO_0的oe使能，发送spi_dout数据到外界；GPIO_0的ie关闭，spi_din恒定输入为0。此模式下，支持DMA传输、支持Master/Slave模式下的发送。

仅接收

CFG[7:6]配置为3，半双工接收模式有效。此时，本接口只能接收数据。GPIO_0的oe关闭，spi_dout无法发送数据到外界；GPIO_0的ie开启，spi_din接收来自外部的数据。此模式下，支持DMA传输、支持Master/Slave模式下的接收。

注意，全双工下是两个GPIO用于数据传输，半双工下可从中任意选一个GPIO用于数据传输。

# 17.3.2.3 片选信号

本接口做Slave模式时，片选信号可选，CFG[5]决定片选来源。ss为Master设备发出的选通使能信号，低电平有效。

![](images/9a8f51e796e1ded1dfd796f8f484a011cd4ce56f95f80ec97642c4501792cc4b.jpg)  
图17-4 SPI 模块 Slave 模式片选信号选择

本接口做 Master 模式时，片选信号亦可选。模块硬件产生了标准的片选信号，实际应用可屏蔽此信号通过软件操作额外的 GPIO 实现。

![](images/d18ca2bdd4703479c49c033de3a8ef63975defb6f5184733fb3b2c23675813b2.jpg)  
图17-5 SPI 模块 Master 模式片选信号选择

注意，图14- 5 虚线仅表示不确定。若使用 spi_ss_out 为 ss 的源头，那么将 GPIO_0 同外界设备互连；若使用软件操作 GPIO 的方式，那么可将 GPIO_1 同外界设备互连。

# 17.3.2.4 通讯格式

在 SPI 通讯过程中，发送或者接收操作均是基于 SPI 时钟的。通讯格式受到 CFG[3:2] 控制。CFG[3] 为 Phase 控制位，CFG[2] 为 Polarity 控制位。

Polarity 控制了 SPI 时钟信号在默认情况下的电平状态。Polarity 为 0 时，默认时钟电平为低电平；Polarity 为 1 时，默认电平为高电平。

Phase 控制了 SPI 数据的发送/接收时刻。Phase 为 0 时，时钟从默认电平到第一个跳变边沿为采样数据时刻，Phase 为 1 时，时钟从默认电平到第一个跳变边沿为发送数据时刻。

![](images/cce00b0f266a10ece64f418d0150d50bae0687fed40f329e279aee9ab3ad0011.jpg)

![](images/c523499a936e3c026c05e827298da6f8860678d85ec33f5e4ac87da3bfc458d2.jpg)  
图17-7SPI通讯信号极性相位(Polarity  $= 0$  ,Phase  $= 1$

![](images/f3ddbc472ed4194bb88149b332bc85b16bc1886dce8b41a1946f8b2199ff5848.jpg)  
图17-8SPI通讯信号极性相位(Polarity  $= 1$  ,Phase  $= 0$

![](images/78c3a728baa6c6544630d95cdd51d228b46043f276faefd3ce4cca2aa818e2c0.jpg)

![](images/a1adbc2b69cd9d6ecd77d3bdebaf234c9c15be4361f30da149aaff5985cda6a4.jpg)  
图17-9 SPI通讯信号极性相位(Polarity  $= 1$ , Phase  $= 1$ )

# 17.3.2.5 数据格式

SPI数据传输格式分成两种：MSB和LSB。数据传输格式受到CFG[1]控制。注意，在数据传输过程中硬件自动实现传输格式的转换，无需软件转换。

# 17.3.2.6 DMA传输

在大容量数据传输应用下，SPI接口支持DMA传输，减轻CPU的负担。一次传输，最大传输量为255字节，最小传输量为1字节。在全双工模式下，接收和发送均可实现DMA传输；在半双工模式下，仅接收或发送实现DMA传输。

在接收到新的数据后，硬件自动产生DMA请求，通过DMA模块将数据搬移到RAM中。在发送新数据前，硬件自动产生DMA请求，通过DMA模块将数据从RAM中搬移到SPI接口。因SPI无FIFO，SPI发送一次DMA请求，DMA只能搬移一个字节数据。若要实现多字节搬移，DMA需配置为多轮搬移，每一轮搬移一个字节的方式。

DMA传输需要配置DMA模块相应寄存器

因SPI接口支持DMA传输，也支持CPU传输。两者区别在于- - DMA传输，发送的数据来自DMA的搬移；CPU传输，发送的数据来自CPU的搬移。

DMA传输，推荐软件配置流程如下：

- 初始化DMA模块，将本次发送的数据来源，接收的数据去向配置好，传输长度配置完毕。- 初始化GPIO模块，将SPI复用的GPIO配置完毕。- 初始化SPI接口，IE/CFG/BAUD/SIZE等寄存器配置完毕。- 触发SPI接口，进入发送/接收状态。触发条件是CPU对TX_DATA寄存器执行写操作，因最终发送的数据来自DMA，本次CPU写入的数据不会混入SPI发送流程。

# 17.3.2.7 CPU传输

CPU传输，一次只能发送/接收1个字节，每次完成后需要通过中断或者轮询的方式判断传输

是否完成。

SPI接口支持DMA传输，也支持CPU传输。CPU传输，SPI接口无需触发发送状态，只要CPU将数据搬移到SPI接口，就可开始发送数据到外界。

CPU传输，推荐软件配置流程如下：

初始化GPIO模块，将SPI复用的GPIO配置完毕。

初始化SPI接口，IE/CFG/BAUD/SIZE等寄存器配置完毕。注意SIZE只能配置为1。

CPU对TX_DATA寄存器执行写操作，触发SPI接口进入发送流程，发送的数据来自CPU对TX_DATA写入值。

# 注意：若需要连续发送，则需要重新配置SIZE和TX_DATA寄存器。1

# 17.3.2.8外部事件传输

17.3.2.8 外部事件传输在大容量数据传输应用下，SPI接口支持DMA传输。传输过程中，可被打断也可不被打断。所谓打断是指，当前字节传输完成，需等待外部事件才开始下一个字节的传输；不打断是指，当前字节传输完成，直接下一个字节的传输。打断模式需要同其它模块配合使用。例如定时器模块，定时器可触发下一字节的传输。打断模式仅在Master模式有效。IE[3]控制了是否使用打断模式。

# 17.3.2.9中断处理

SPI接口包含三种类型的中断事件，分别是：数据传输完成事件，异常事件和溢出事件。

数据完成事件，当前数据传输完成。高电平有效，对IE[0]写1清除。

异常事件，SPI接口为Slave模式，若在传输过程中片选信号受到干扰，被拉高，将产生片选异常事件。高电平有效，对IE[1]写1清除。

溢出事件，数据没有及时通过DMA返回RAM，或者从RAM获得数据，将产生溢出事件。高电平有效，对IE[2]写1清除。

上述事件，默认是不触发SPI中断，可以通过配置IE[6:4]使能事件产生中断。

![](images/b94e099b84a5993f7ebfffd6efaa9a154f27d98e8853db6332cfa445eb5b820a.jpg)  
图17-10SPI模块中断选信号产生图

数据传输完毕后，可通过DMA中断或者SPI自身中断判断结束。

发送模式下，DMA先完成搬移操作，SPI后发送完毕。SPI发送完毕，可作为本次传输完成标

识。

$\bullet$  接收模式下，SPI接收完毕，触发DMA搬移。DMA搬移完成，可作为本次传输完成标识。

溢出事件。在全双工模式下，发送和接收的DMA均有效，一般情况下不会发送溢出事件；在半双工模式下，只有发送（或接收），此时硬件屏蔽了接收（或发送）的溢出判断。

# 17.3.2.10波特率设置

SPI接口时钟通过对系统时钟分频获得，分频系数来自BAUD[5:0]。分频范围是  $1\sim 128$  ，对应的BAUD[5:0]的值为  $0\sim 63$  。

SPI协议为半拍协议，上升沿发送数据，下降沿采集数据；或者下降沿发送数据，上升沿采用数据。

SPI接口采用同步设计，需要对外部设备的信号进行同步采样，同步时钟为系统时钟。数据和时钟信号（此时为Slave模式）的同步，需要两拍系统时钟。考虑到时钟相位的偏移，此时需要一拍系统时钟的冗余，由此推导出最快的BAUD率为系统时钟的1/8，高电平周期为四拍系统时钟，低电平周期为四拍系统时钟。

# 17.4寄存器

# 17.4.1 地址分配

SPI模块寄存器的基地址是0x4001_0000，寄存器列表如下：

表17-1SPI模块控制寄存器列表  

<table><tr><td>名称</td><td>偏移</td><td>说明</td></tr><tr><td>SPI_CFG</td><td>0x00</td><td>SPI 配置寄存器</td></tr><tr><td>SPI_IE</td><td>0x04</td><td>SPI 中断寄存器</td></tr><tr><td>SPI_DIV</td><td>0x08</td><td>SPI 波特率寄存器</td></tr><tr><td>SPI_TX_DATA</td><td>0x0C</td><td>SPI 发送数据寄存器</td></tr><tr><td>SPI_RX_DATA</td><td>0x10</td><td>SPI 接收数据寄存器</td></tr><tr><td>SPI_SIZE</td><td>0x14</td><td>SPI 传输数据长度寄存器</td></tr></table>

# 17.4.2 SPI_CFGSPI控制寄存器

地址：0x4001_0000

复位值：0x0

表17-2系统控制寄存器SPI_CFG  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td></td></tr><tr><td></td></tr><tr><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:6]</td><td>DUPLEX</td><td>半双工模式设置
0X: 关闭半双工模式
10: 开启半双工模式，仅发送
11: 开启半双工模式，仅接收</td></tr><tr><td>[5]</td><td>CS</td><td>SPI 从设备下，片选信号来源。默认值为 1。
1: Slave 模式下，片选信号来自 Master 设备
0: Slave 模式下，片选信号恒为有效值--0</td></tr><tr><td>[4]</td><td>MS</td><td>SPI 主从模式选择。默认值为 0。
1: Master 模式
0: Slave 模式</td></tr><tr><td>[3]</td><td>SAMPLE</td><td>SPI 相位选择。默认值为 0。
1: Phase 为 1
0: Phase 为 0</td></tr><tr><td>[2]</td><td>CLK_POL</td><td>SPI 极性选择。默认值为 0。
1: Polarity 为 1
0: Polarity 为 0</td></tr><tr><td>[1]</td><td>ENDIAN</td><td>SPI 模块传输顺序。默认值为 0。
1: LSB，低位先传输
0: MSB，高位先传输</td></tr><tr><td>[0]</td><td>EN</td><td>SPI 模块使能信号。默认值为 0。
1: 开启 SPI 模块
0: 关闭 SPI 模块</td></tr></table>

SPI_CFG[3:2]对应的通讯波形极性和相位可参考17.3.2.4。

# 17.4.3 SPI_IE SPI中断寄存器

地址：0x4001_0004

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td>IE</td><td>CMPI_EIE</td><td>AR_EIE</td><td>OV_EIE</td><td>TANX_TANX</td><td>CMPI_EIE</td><td>AR_EIE</td><td>OV_EIE</td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7]</td><td>IE</td><td>SPI 中断使能开关。默认值为 0。
1：使能 SPI 中断</td></tr></table>

<table><tr><td></td><td></td><td>0：关闭 SPI 中断</td></tr><tr><td>[6]</td><td>CMPLT_IE</td><td>SPI 传输，完成事件中断使能信号。
1：使能此中断源
0：屏蔽此中断源</td></tr><tr><td>[5]</td><td>AB_IE</td><td>SPI 传输，异常事件中断使能信号。
1：使能此中断源
0：屏蔽此中断源</td></tr><tr><td>[4]</td><td>OV_IE</td><td>SPI 传输，溢出事件中断使能信号。默认值为 0。
1：使能此中断源
0：屏蔽此中断源</td></tr><tr><td>[3]</td><td>TRANS_TRIG</td><td>传输触发选择。
1：外部触发
0：内部自动执行。仅主模式有效</td></tr><tr><td>[2]</td><td>CMPLT_IF</td><td>SPI 传输，完成事件。高电平有效，写 1 清除。</td></tr><tr><td>[1]</td><td>AB_IF</td><td>SPI 传输，异常事件。Slave 模式下，传输未完成，发生片选信号无效事件。高电平有效，写 1 清除。</td></tr><tr><td>[0]</td><td>OV_IF</td><td>SPI 传输，溢出事件。包含两种情况：
1. 前次接收的旧数据没有被取得走，本次接收的新数据已经到达。
2. 本次发送的数据已发送完毕，新数据没有准备好。高电平有效，写 1 清除。</td></tr></table>

# 17.4.4 SPI_DIV SPI 设特率寄存器

地址：0x4001_0008

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="8"></td><td colspan="2">TRANS_MODE</td><td colspan="5">BAUD</td><td></td></tr><tr><td colspan="2">RW</td><td colspan="5">RW</td><td></td></tr><tr><td colspan="2">0</td><td colspan="5">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7]</td><td>TRANS_MODE</td><td>SPI数据搬移方式。默认为0，DMA方式。
0：SPI接口支持DMA搬移数据到SPI接口，完成发送和接收。
1：SPI接口支持CPU搬移数据到SPI接口，完成发送和接收。</td></tr><tr><td>[6]</td><td></td><td>未使用</td></tr><tr><td>[5:0]</td><td>BAUD</td><td>SPI传输波特率配置，SPI实际传输速度计算公式为：
SPI传输速度=系统时钟/(2*(BAUD+1)) 
切记，BAUD的配置值不能小于3。</td></tr></table>

# 17.4.5 SPI_TX_DATA SPI数据发送寄存器

地址：0x4001_000C

复位值：0x0

表17-5SPI_TX_DATA数据发送寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td></tr><tr><td rowspan="6" colspan="16"></td><td></td></tr><tr><td></td></tr><tr><td></td></tr><tr><td></td><td></td></tr><tr><td></td><td></td></tr><tr><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>TX_DATA</td><td>SPI数据发送寄存器。CPU方式，寄存器写入要发送的数据；DMA方式，对寄存器执行写入操作，仅仅是触发DMA搬移，要发送的数据来自DMA，非本寄存器。</td></tr></table>

# 17.4.6 SPI_RX_DATA SPI数据接收寄存器

地址：0x4001_0010

复位值：0x0

表17-6SPI_RX_DATA数据接收寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3" colspan="7"></td><td colspan="7"></td><td colspan="8">RX_DATA</td></tr><tr><td colspan="8">RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="8">0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>RX_DATA</td><td>SPI 数据接收寄存器</td></tr></table>

# 17.4.7 SPI_SIZE SPI数据传输长度寄存器

地址：0x4001_0014

复位值：0x0

表17-7SPI_SIZE数据传输长度寄存器  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="2" colspan="15"></td><td></td></tr><tr><td colspan="8">RW</td><td></td></tr></table>

<table><tr><td></td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>SIZE</td><td>SPI 数据传输长度寄存器。CPU 方式，只能写入 1，一次传输一个字节的数据，传输完成后 SIZE 变成 0；DMA 方式，表示本次传输的数据总量，硬件每传输完成一个字节，SIZE 自减 1，传输完成后 SIZE 变成 0。</td></tr></table>

# 18 CMP

# 18.1概述

比较器信号处理模块（以下简称CMP模块，为便于区分，后续图示中模拟比较器使用Comparator表示，数字CMP模块使用CMP表示），用于处理两个模拟轨到轨比较器产生的输出信号，由一系列使能、极性控制、滤波等数字电路组成。

比较器可用于以下功能：

1. 反电势过零点检测2. 硬件过流检测3. 作为MCPWM的fail信号来源

比较器的主要特性如下：

1. 每个比较器都具备多种的信号来源可供选择：

多路GPIO口输入信号 $\bullet$  运放输出信号 $\bullet$  运放正端输出信号1.2VBANDGAP基准源DAC输出信号

2. 比较速度可编程，迟滞电压可编程

3. 输出信号可滤波，滤波深度可选

4. 可产生CMP中断

需说明的是，CMP负输入端的BEMFx_MID信号，是对正输入端信号CMPx_IP1/ CMPx_IP2/ CMPx_IP3信号的平均，具体连接方式见图18- 1，图中电阻  $\mathrm{R} = 8.2\mathrm{k}$  欧，图中的开关只有在比较器负输入端信号选择为BEMFx_MID之后才会导通，否则开关都处于断开状态。

BEMFx_MID主要用于BLDC方波模式控制时，虚拟电机相线中心点电压，用于反电势过零点检测。三个相线分压后，分别接CMPx_IP1、CMPx_IP2、CMPx_IP3，比较器负端选择BEMFx_MID，比较器正端的多路选择器以分时复用的方式分别选择CMPx_IP1、CMPx_IP2、CMPx_IP3，就可以比较出反电势过零点。

![](images/446cefc8a68625d0899fc212fe2008d4539bc6eccefbb8db51fd7dce17673f94.jpg)  
图18-1BEMFx_MID信号

此模块的信号处理时钟由系统主时钟分频得到。模拟比较器未经滤波的原始输出值，可以通过读取寄存器SYSAFECMP值获得，同时也可以通过配置GPIO的第二功能通过P0.14和P2.3送出，具体GPIO第二功能配置及引进位置，请参考器件datasheet。

推荐配置流程：

1. 配置CMP的模拟开关芯片上电的默认状态下，比较器模块是关闭的，通过配置寄存器SYSAFE_REG5.CMPxPDN可以打开比较器  $(x = 0 / 1$  ，代表CMP0/CMP1两个比较器)。开启比较器之前，需要先开启BGP模块。

2. 配置CMP的数字时钟开关、时钟滤波和信号输入开关

通过配置寄存器CMPTCLKCLKEN可以打开CMP的数字时钟开关，1表示打开，0表示关闭；通过配置寄存器CMPTCLK_FILCLKDIV16[7:4]可以配置滤波时钟，数值设置范围是  $0\sim 15$  ，0表示1分频滤波，15表示16分频滤波；通过配置寄存器CMPCFG.CMPxINEN可以打开信号输入开关，1表示打开，0表示关闭。

3. 配置CMP的比较速度和迟滞电压

比较器的比较延时可通过配置寄存器SYSAFE_REG1. ITCM[1:0]设置为 $0.15\mathrm{uS} / 0.6\mathrm{uS}$  。迟滞电压可通过配置寄存器SYSAFE_REG3.CMP_HYS设置为 $20\mathrm{mV} / 0\mathrm{mV}$  。

4. 选择CMP的正负端信号来源

CMP的正端信号有8种信号来源可选择，可以通过配置寄存器SYSAFE_REG3. CMPxSELP[2:0]进行设置，负端有4种信号来源可选择，可以通过配置寄存器SYSAFE_REG3. CMPxSELN[1:0]进行设置。

5. 配置CMP的中断

通过配置寄存器CMPIE.CMPxIE可以打开CMP中断，1表示打开，0表示关闭。

# 18.2 寄存器

# 18.2.1 地址分配

CMP模块所涉及的寄存器包括两部分，一是18.1中提到的模拟配置寄存器，二是CMP_IE等CMP模块寄存器。

CMP模块寄存器的基地址是0x4001_0C00，寄存器列表如下：

表18-1比较器模块寄存器列表  

<table><tr><td>名称</td><td>偏移地址</td><td>说明</td></tr><tr><td>CMP_IE</td><td>0x00</td><td>比较器中断使能寄存器</td></tr><tr><td>CMP_IF</td><td>0x04</td><td>比较器中断标志寄存器</td></tr><tr><td>CMP_TCLK</td><td>0x08</td><td>比较器分频时钟控制寄存器</td></tr><tr><td>CMP_CFG</td><td>0x0C</td><td>比较器控制寄存器</td></tr><tr><td>CMP_BLCWIN</td><td>0x10</td><td>比较器开窗控制寄存器</td></tr></table>

# 18.2.2 CMP模块寄存器描述

18.2.2.1 CMP_IE

地址：0x4001_0C00

复位值：0x0

表18-2比较器中断使能寄存器CMP_IE  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="13"></td><td>CMP1_IE</td><td>CMP0_IE</td><td></td></tr><tr><td>RW</td><td>RW</td><td></td></tr><tr><td>0</td><td>0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:2]</td><td></td><td>未使用</td></tr><tr><td>[1]</td><td>CMP1_IE</td><td>比较器1中断使能，高有效</td></tr><tr><td>[0]</td><td>CMP0_IE</td><td>比较器0中断使能，高有效</td></tr></table>

# 18.2.2.2 CMP_IF

地址：0x4001_0C04

复位值：0x0

表18-3比较器中断标志寄存器CMP_IF  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr></table>

<table><tr><td rowspan="3"></td><td>CMP1_IF</td><td>CMP0_IF</td></tr><tr><td>RW1C</td><td>RW1C</td></tr><tr><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:2]</td><td></td><td>未使用</td></tr><tr><td>[1]</td><td>CMP1_IF</td><td>比较器 1 中断标志，高有效，写 1 清零</td></tr><tr><td>[0]</td><td>CMP0_IF</td><td>比较器 0 中断标志，高有效，写 1 清零</td></tr></table>

# 18.2.2.3 CMP_TCLK

地址：0x4001_0C08

复位值：0x0

表18-4比较器分频时钟控制寄存器CMP_TCLK  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td></td></tr><tr><td></td></tr><tr><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:4]</td><td>FIL_CLK_DIV16</td><td>比较器滤波时钟分频，基于MCLK进行1~16分频，影响进入比较器中断的时间</td></tr><tr><td>[3]</td><td>CLK_EN</td><td>时钟使能，高有效</td></tr><tr><td>[2]</td><td></td><td>未使用</td></tr><tr><td>[1:0]</td><td>FIL_CLK_DIV1248</td><td>比较器滤波时钟分频，2&#x27;b00:1分频，2&#x27;b01:2分频，2&#x27;b10:4分频，2&#x27;b11:8分频</td></tr></table>

CMP滤波时钟频率

Freq(CMP_Filter) = Freq(MCLK)/2<sup>CMP_TCLK_FIL_CLK_DIV1248</sup> / (CMP_TCLK_FIL_CLK_DIV16+1)，其中MCLK为系统的主时钟，通常为96MHz全速时钟。需要注意的是，产生CMP滤波时钟需要使能CMP_TCLK_CLK_EN位。

![](images/6833126987d14d2c2ab98af94f6af2184facbf824e71f361a1de99e787f24a19.jpg)  
图18-2比较器滤波时钟产生

CMP模块使用此滤波时钟对模拟比较器的输出信号进行16时钟周期长的滤波，即只有信号稳定时间超过16个滤波时钟周期才能通过滤波器，CMP模块输出的滤波后的信号才会发生变化，如果输入信号稳定时间不足16个滤波时钟周期即发生变化，则CMP模块输出的滤波后的信号维持原值不变。即滤波宽度  $\equiv$  滤波时钟周期  $\ast 16$

# 18.2.2.4CMP_CFG

地址：0x4001_0C0C

复位值：0x0

表18-5比较器控制寄存器CMP_CFG  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td>CMPLW_PWM_POL</td><td></td><td>CMPL_IRQ_TRIG</td><td></td><td>CMPL_IN_EN</td><td></td><td>CMPL_POL</td><td></td><td>CMPL_IRQ_TRIG</td><td></td><td>CMPL_IN_EN</td><td></td><td>CMPL_POL</td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7]</td><td>CMP1_W_PWM_POL</td><td>比较器1开窗PWM信号极性选择，在CMP_BLCWIN使能情况下使用</td></tr><tr><td>[6]</td><td>CMP1_IRQ_TRIG</td><td>比较器1中断触发类型，0:电平触发，1:边沿触发</td></tr><tr><td>[5]</td><td>CMP1_IN_EN</td><td>比较器1信号输入使能</td></tr><tr><td>[4]</td><td>CMP1_POL</td><td>比较器1极性选择，0:高电平有效；1:低电平有效</td></tr><tr><td>[3]</td><td>CMP0_W_PWM_POL</td><td>比较器0开窗PWM信号极性选择，在CMP_BLCWIN使能情况下使用</td></tr><tr><td>[2]</td><td>CMP0_IRQ_TRIG</td><td>比较器0中断触发类型，0:电平触发，1:边沿触发</td></tr><tr><td>[1]</td><td>CMP0_IN_EN</td><td>比较器0信号输入使能</td></tr><tr><td>[0]</td><td>CMP0_POL</td><td>比较器0极性选择，0:高电平有效；1:低电平有效</td></tr></table>

比较器的极性及使能控制如图 18- 3 所示。

![](images/90023a52e9840abe1ece4f517586a7162bf304dcc836d90fa262b53a0006b404.jpg)  
图18-3比较器控制及中断产生逻辑

比较器模块与MCPWM模块可以联合动作，其中MCPWM模块的P管控制信号可以作为比较器开窗的控制信号。但比较器自身的中断信号产生于开窗控制无关，仅仅受CMP_CFG寄存器影响。

MCPWM的fail信号可以来自GPIO，也可以来自比较器模块，使用MCPWM_FAIL寄存器进行控制。如果MCPWM的fail信号来自比较器，则是经过比较器模块内部的开窗控制的。fail信号进入MCPWM后也会进行极性使能以及滤波等处理，与比较器模块类似但完全独立，由MCPWM内部的寄存器进行控制。MCPWM内部与fail相关的错误中断信号产生收到MCPWM内部有关极性使能滤波控制寄存器的影响。具体请参考MCPWM章节。

![](images/e31d24b82656968d15fc06ad2063488ac14251a06a65ac2cfbf46e8b95cb97da.jpg)  
图18-4CMP与MCPWM的联动

图18- 4 CMP与MCPWM的联动对于比较器的开窗功能，若CMP_CFG.CMP0_PWM_POL=1，则在对应MCPWM CHNx_P信号为1时，比较器0可以产生比较信号输出，其他时刻比较信号为0；反之，若CMP_CFG.CMP0_PWM_POL=0，则在对应MCPWM CHNx_P信号为0时，比较器0可以产生比较信号输出，其他时刻比较信号为0。

比较器1的开窗控制信号极性由CMP_CFG.CMP1_PWM_POL位进行控制，逻辑相同。

注意：CMP_CFG.CMP0_W_PWM_POL和CMP_CFG.CMP1_W_PWM_POL同时会影响送入MCPWM模块作为FAIL信号的比较器信号，如图18- 5所示。来自比较器的MCPWMFAIL信号为模拟比较器输出的原始信号，未经过比较器数字接口模块的滤波处理，但是可以被MCPWM的通道信号进行开窗控制，开窗控制设置见比较器数字接口模块。FAIL信号进入MCPWM模块后，可以通过设置MCPWM_TCLK进行滤波。

![](images/f73c019da93494230845e2b612cd14cfd3883ee27ce4af1e7dddccd8305235ed.jpg)  
图18-5比较器开窗功能图示

# 18.2.2.5CMP_BLCWIN

地址：0x4001_0C10

复位值：0x0

表18-6比较器开窗控制寄存器CMP_BLCWIN  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>保留</td></tr><tr><td>[7]</td><td>CMP1_CHN3P_WIN_EN</td><td>使用 MCPWM 模块 CHN3_P 通道输出的 P 管开关控制信号作为比较器 1 开窗使能</td></tr><tr><td>[6]</td><td>CMP1_CHN2P_WIN_EN</td><td>使用 MCPWM 模块 CHN2_P 通道输出的 P 管开关控制信号作</td></tr></table>

<table><tr><td></td><td></td><td>为比较器 1 开窗使能</td></tr><tr><td>[5]</td><td>CMP1_CHN1P_WIN_EN</td><td>使用 MCPWM 模块 CHN1_P 通道输出的 P 管开关控制信号作为比较器 1 开窗使能</td></tr><tr><td>[4]</td><td>CMP1_CHN0P_WIN_EN</td><td>使用 MCPWM 模块 CHN0_P 通道输出的 P 管开关控制信号作为比较器 1 开窗使能</td></tr><tr><td>[3]</td><td>CMP0_CHN3P_WIN_EN</td><td>使用 MCPWM 模块 CHN3_P 通道输出的 P 管开关控制信号作为比较器 0 开窗使能</td></tr><tr><td>[2]</td><td>CMP0_CHN2P_WIN_EN</td><td>使用 MCPWM 模块 CHN2_P 通道输出的 P 管开关控制信号作为比较器 0 开窗使能</td></tr><tr><td>[1]</td><td>CMP0_CHN1P_WIN_EN</td><td>使用 MCPWM 模块 CHN1_P 通道输出的 P 管开关控制信号作为比较器 0 开窗使能</td></tr><tr><td>[0]</td><td>CMP0_CHN0P_WIN_EN</td><td>使用 MCPWM 模块 CHN0_P 通道输出的 P 管开关控制信号作为比较器 0 开窗使能</td></tr></table>

通常 CMP_BLCWIN[3:0]或 CMP_BLCWIN[7:4]中有 1bit 为 1，表明使用对应的 CHNx_P 对比较器 0/1 的信号产生进行控制。如果 CMP_BLCWIN[3:0]或 CMP_BLCWIN[7:4]为 4'b0000，则表示比较器 0/1 比较信号的产生与 PWM 信号无关。

# 19 CAN

# 19.1概述

19.1 概述CAN 总线接口连接微控制器和串行 CAN 总线。本 CAN 模块根据特定设备的需要，可以使用 DMA 以减轻 CPU 的负担。使用 CAN 通信时需要用外部晶振作为参考时钟。

# 19.1主要特性

支持BOSCH2.0A和2.0B协议。2.0A等效CAN1.2，包含了11位ID格式；2.0B包含了11位ID和29位ID。

支持SJA1000大部分功能（部分不支持点在文档后续有说明）。- 有两种模式：工作模式和复位模式。- 支持监听和自测试。监听模式下，仅接收外界信号但不会返回任何信号。- 支持DMA功能。

# 19.2功能描述

# 19.2.1 功能框图

本接口采用同步串行设计，实现CPU同外部设备之间的CAN传输。支持轮询和中断方式获得传输状态信息。本接口的主要功能模块如下图所示。

![](images/61b2fffe5a40bf55eba0388d0becd36e2850b6062cc0b6d15bd6858be8d413f1.jpg)  
图19-1CAN模块顶层功能框图

CAN接口同外界通讯只有tx和rx两根信号线。tx发送有效数据时候，tx_oe有效。tx不发送有效数据的时候，tx_oe无效。

rx：数据信号。接收来自外界的CAN数据

tx：数据信号。发送CAN数据到CAN总线。

tx_oe：数据使能信号。当tx输出时，tx_oe有效；当tx无数据输出时，tx_oe无效。

# 19.2.2 功能说明

CAN模块接收和发送数据，并将数据从串行转换成并行，或并行转换成串行。可以开启或禁止中断。接口通过数据输出引脚(TX)和数据输入引脚(RX)连接到CAN总线的PHY芯片上。

# 19.2.2.1工作模式

CAN模块主要包含两个工作模式：正常工作模式和复位模式。

复位模式，时序参数、ID配置、错误统计值等均在此模式下设定好。CAN_MOD.0为1，是复位模式。硬件复位结束后，CAN模块处于复位模式下。

正常工作模式，CAN_MOD.0为0。此时，可以正常响应CAN总线请求。

在上述两个模式下，扩展了监听模式（ListenOnly）和自测试模式（SelfTest)。前者，类似一个搜集器，只接收CAN总线上的数据，不发送任何数据。后者，是内部自测试，发送的数据同时被自己接收，检测内部功能是否正确。

# 19.2.2.2DMA传输

在大容量数据传输应用下，CAN接口支持DMA传输，减轻CPU的负担。一次传输，SFF为11个字节，EFF为13个字节。

在接收到新的数据后，即CAN_IR.RFIFO_N_EMPTY_IF硬件自动产生DMA请求，通过DMA模块将数据搬移到RAM中。在发送新数据前，硬件自动产生DMA请求，通过DMA模块将数据从RAM中搬移到CAN接口。

DMA传输需要配置DMA模块相应寄存器

因CAN接口支持DMA传输，也支持CPU传输。两者区别在于- - DMA传输，发送的数据来自DMA的搬移；CPU传输，发送的数据来自CPU的搬移。

DMA传输，推荐软件配置流程如下：

初始化DMA模块，将本次发送的数据来源，接收的数据去向配置好，传输长度配置完毕。

初始化GPIO模块，将CAN复用的GPIO配置完毕。

初始化CAN接口，控制寄存器配置完毕。

触发CAN接口，进入发送状态。

本CAN模块设计的DMA不同于其它模块的DMA搬移操作，需要CPU介入部分搬移操作。假定当前配置CAN模块发送IN帧数据，那么第一帧数据需要CPU搬移到CAN模块寄存器中，后续帧（N- 1）的数据可由DMA实现搬移。

# 19.2.2.3CPU传输

CPU传输，根据SFF还是EFF，搬移11个字节或者13个字节；完成后需要通过中断或者轮询的方式判断传输是否完成。

CPU传输，推荐软件配置流程如下：

- 初始化 GPIO 模块，将 CAN 复用的 GPIO 配置完毕。- 初始化 CAN 接口，控制寄存器配置完毕。- CPU 触发 CAN 接口进入发送流程，发送的数据来自 CPU 对 CAN_TXDATA 写入值。

19.2.2.4 中断处理

CAN 接口包含中断事件比较多，在 CAN_IR 和 CAN_EIR 寄存器描述中有相应说明。根据实际使用情况，开启对应的中断事件使能开关。

CAN控制器提供了以下七种中断：

·接收中断·发送中断·错误报警中断·数据溢出中断·被动错误中断·仲裁丢失中断·总线错误中断

只要在 CAN_IR 一个或多个中断位为 1，CAN 控制器中的中断信号即为有效，当 CAN_IR 中的所有位都被清除时，CAN 控制器中的中断信号则失效。寄存器 CAN_IR 被读取后，其中的大多数中断位将自动清除。但是，接收中断不包括在内，直到通过 CAN_CMR 的 bit2 写 1，读取所有接收报文后，接收中断位才能被清除。

# 19.2.2.4.1 接收中断

当 CAN 接收 FIFO 中有待读取帧时（CAN_RMC > 0），都会触发接收中断。CAN_RMC 中记录的帧数量包括接收 FIFO 中的有效帧和溢出帧。直到通过给 CAN_CMR 的 bit2 写 1，清除所有挂起接收帧后，接收中断才会失效。

# 19.2.2.4.2 发送中断

每当发送缓冲器空闲，将其他帧加载到发送缓冲器中等待发送时，都会触发发送中断。以下情况下，发送缓冲器将变为空闲，同时发送中断将失效：

- 帧发送已成功完成（如，应答未发现错误）。任何发送失败将自动重发。- 单次发送已完成（CAN_SR bit3 指示发送成功与否）。- CAN_CMR 的 bit1 位，写 1，终止帧发送。

# 19.2.2.4.3 错误报警中断

每当寄存器 CAN_IR 中 ON_BUS 或 ERR_OV 的位值改变时（如，从 0 变为 1 或反之），都会触发

此中断。根据触发时 ON_BUS 或 ERR_OV 的值分成以下几种情况：

- 如果 ERR_OV = 0 且 ON_BUS = 0:- 如果 CAN 控制器处于主动错误状态，则表示接收错误计数和发送错误计数的值都返回到了 CAN_EWLR 所设的阈值之下。- 如果 CAN 控制器此前正处于总线恢复状态，则表示此时总线恢复已成功完成。- 如果 ERR_OV = 1 且 ON_BUS = 0: 则表示接收错误计数或发送错误计数的值超过了 CAN_EWLR 所设的阈值。- 如果 ERR_OV = 1 且 ON_BUS = 1: 表示 CAN 控制器已进入 BUS_OFF 状态（因发送错误计数 >= 256）。- 如果 ERR_OV = 0 且 ON_BUS = 1: 表示 BUS_OFF 恢复期间，CAN 控制器的发送错误计数的数值已低于 CAN_EWLR 所设的阈值。

# 19.2.2.4.4 数据溢出中断

接收 FIFO 满，若还收到有效帧，将触发数据溢出中断。

# 19.2.2.4.5 仲裁丢失中断

每当 CAN 控制器尝试发送帧且丢失仲裁时，都会触发此中断。CAN 控制器丢失仲裁的 bit 位置将自动记录在仲裁丢失捕捉寄存器 CAN_ALC 中。仲裁丢失捕捉寄存器被清除（通过 CPU 读取该寄存器）之前，将不会再记录新发生的仲裁失败时的 bit 位置。

# 19.2.2.4.6 总线错误中断

每当 CAN 控制器在 CAN 总线上检测到错误时，都会触发此中断。发生总线错误时，总线错误的类型和发生错误时的 bit 位置都将自动记录在错误捕捉寄存器 CAN_ECC 中。错误捕捉寄存器被清除（通过 CPU 的读取）之前，将不会再记录新的总线错误信息。

# 19.2.2.5 通讯采样设置

CAN 的波特率设定，主要依靠 CAN_BTR0 和 CAN_BTR1 两个寄存器配合完成。CAN_BTR0 主要是配置 TQ 参数（TQ 的计算见 BTR0 寄存器说明），CAN_BTR1 主要处理 1- bit 数据的采样点、采样次数以及宽度信息。

CAN_BTR0 设置传输基本时间单元参数 TQ: TQ = 2 * Tcl * (CAN_BTR0. BAUDRATE + 1)  LKS00x 时钟最快为 96M，对应的 Tcl 为 10.4ns，TQ 最大值为 1.3312us。

CAN_BTR1 设置波特率：同时，可调节 BIT 信息中各个部分的宽度（TSEG1、TSEG2 和 Sync.Seg），找到理想采样点。

![](images/772302d2a4c35196c47d9a81ee81b9abd76c85d4d65d403a3f6567568e3d7f44.jpg)  
图19-2 CAN模块Bit周期介绍图

SEG1段时间计算公式：  $\mathrm{Tseg1} = \mathrm{TQ}^{*}(\mathrm{CAN\_BTR1. SEG1} + 1)$

SEG2段时间计算公式：  $\mathrm{Tseg2} = \mathrm{TQ}^{*}(\mathrm{CAN\_BTR1. SEG2} + 1)$

波特率计算公式为：CanBaudrate  $= 1 / (1 * \mathrm{TQ} + \mathrm{Tseg1} + \mathrm{Tseg2})$

CAN_BTR0. SJW是SJW位，其为容差范围的配置寄存器。在一定波特率下通讯的各个设备，允许多大的通讯时间误差存在。

总线下界容差  $<$  总线波特率  $<$  总线上限容差

容差计算公式为：  $\mathrm{TQ}^{*}(\mathrm{SJW} + 1)$

CAN_BTR1. SAM是SAM位，其位采样次数配置寄存器。0：一次；1：三次。根据实际使用情况配置即可，此位不参与波特率计算。

基于LKS08x芯片，常规波特率索引值如下：

<table><tr><td>Can 波特率</td><td>BTR0</td><td>BTR1</td></tr><tr><td>1Mbps</td><td>0x05</td><td>0x14</td></tr><tr><td>800Kbps</td><td>0x05</td><td>0x16</td></tr><tr><td>666Kbps</td><td>0x85</td><td>0xB6</td></tr><tr><td>500Kbps</td><td>0x05</td><td>0x1C</td></tr><tr><td>400Kbps</td><td>0x05</td><td>0xFA</td></tr><tr><td>250Kbps</td><td>0x0B</td><td>0x1C</td></tr><tr><td>200Kbps</td><td>0x0B</td><td>0xFA</td></tr><tr><td>125Kbps</td><td>0x17</td><td>0x1C</td></tr><tr><td>100Kbps</td><td>0x1D</td><td>0x1C</td></tr><tr><td>83.33Kbps</td><td>0x17</td><td>0x6F</td></tr><tr><td>80Kbps</td><td>0x97</td><td>0xFF</td></tr><tr><td>66.66Kbps</td><td>0x1D</td><td>0x6F</td></tr><tr><td>50Kbps</td><td>0x3B</td><td>0x1C</td></tr><tr><td>40Kbps</td><td>0xAF</td><td>0xFF</td></tr></table>

理论上，可以通过配置寄存器实现1- bit数据的时间宽度在3TQ到25TQ之间。实际应用中，

如果遵循BOSCH标准，1- bit数据的时间宽度在8TQ到25TQ之间。若不遵循BOSCH标准，实际可达的范围在4TQ到25TQ之间。

# 19.2.2.6 ID滤波

CAN总线，可以挂载很多设备。通过ID号，不同设备可以知道当前总线上发送的帧是否需要被自己接收，或者发送出去的帧，是否有响应。

接收滤波器允许CAN控制器根据帧ID过滤接收帧（有时可以过滤帧的第一个数据字节和帧类型)。只有通过过滤的帧才能存储到接收FIFO中。接收滤波器的使用可以一定程度地减轻CAN控制器的运行负荷（如，可减少使用接收FIFO和发生接收中断的次数)，因为CAN控制器将只需要操作一小部分过滤后的帧。只有当CAN控制器处于复位模式时，才可以访问接收滤波器的配置寄存器。

CAN帧的ID号码，有两种长度- - 11位和29位。前者对应的SFF（standard frame format），后者对应EFF（extended frame format）。通过CAN_ACR和CAN_AMR判断当前CAN模块可接收的ID范围。CAN_ACR列出了一个特定的ID，CAN_AMR为MASK寄存器，标识CAN_ACR中对应位数据同接收到的ID对应位数据需完全匹配，哪些位可以不用。极端情况就是CAN_ACR上每一位都要匹配，或者每一位都不要匹配。CAN_AMR对应位是0，表示接收到的ID对应位需要同CAN_ACR对应位匹配；CAN_AMR对应位是1，表示接收到的ID对应位不需要同CAN_ACR对应位匹配。

CAN_MOD.3决定了CAN_ACR包含两个滤波ID还是一个滤波ID。为1的话，CAN_ACR包含一个长的滤波ID；为0的话，CAN_ACR包含了两个短的滤波ID。两个滤波ID情况下，只要接收帧的ID同其中一个匹配，就会被CAN接收。

SFF，单滤波ID数据格式

滤波ID设置  

<table><tr><td>CAN_TXRX1</td><td>CAN_TXRX2</td><td>CAN_TXRX3</td><td>CAN_TXRX4</td></tr><tr><td>ID.28..ID21</td><td>ID.20..ID.18 RTR XXXX</td><td>Data Byte 1</td><td>Data Byte 2</td></tr></table>

<table><tr><td>ACRO[7:0]</td><td>ACR1[7:4] (ACR1[3:0] unused)</td><td>ACR2[7:0]</td><td>ACR3[7:0]</td></tr><tr><td>AMRO[7:0]</td><td>AMR1[7:4] (AMR1[3:0] unused)</td><td>AMR2[7:0]</td><td>AMR3[7:0]</td></tr></table>

此时，ACR2和ACR3若没有用到，对应的AMR2和AMR3需配置为全1。RTR是否需要匹配，结合实际情况配置AMR。

SFF，双滤波ID数据格式  

<table><tr><td>CAN_TXRX1</td><td>CAN_TXRX2</td><td>CAN_TXRX3</td><td>CAN_TXRX4</td></tr><tr><td>ID.28..ID21</td><td>ID.20..ID.18 RTR XXXX</td><td>Data Byte 1</td><td>Data Byte 2</td></tr></table>

滤波ID1

<table><tr><td>ACR0[7:0]</td><td>ACR1[7:0]</td><td>ACR3[3:0]</td></tr><tr><td>AMR0[7:0]</td><td>AMR1[7:0]</td><td>AMR3[3:0]</td></tr></table>

滤波ID2  

<table><tr><td>ACR2[7:0]</td><td>ACR3[7:4]</td></tr><tr><td>AMR2[7:0]</td><td>AMR3[7:4]</td></tr></table>

此时，ACR若没有用到，对应的AMR需配置为全1。例如滤波ID1的ACR1[3:0]和ACR[3:0]。RTR是否需要匹配，结合实际情况配置AMR。

EFF，单滤波ID数据格式  

<table><tr><td>CAN_TXRX1</td><td>CAN_TXRX2</td><td>CAN_TXRX3</td><td>CAN_TXRX4</td></tr><tr><td>ID.28..ID21</td><td>ID.20..ID.13</td><td>ID.12..ID.5</td><td>ID.4..ID.0 RTR X X</td></tr></table>

滤波ID  

<table><tr><td>ACR0[7:0]</td><td>ACR1[7:0]</td><td>ACR2[7:0]</td><td>ACR3[7:2]</td></tr><tr><td>AMR0[7:0]</td><td>AMR1[7:0]</td><td>AMR2[7:0]</td><td>AMR3[7:2]</td></tr></table>

此时，ACR3[1:0]没有用到，对应的AMR需配置为全1。

EFF，双滤波ID数据格式  

<table><tr><td>CAN_TXRX1</td><td>CAN_TXRX2</td><td>CAN_TXRX3</td><td>CAN_TXRX4</td></tr><tr><td>ID.28..ID21</td><td>ID.20..ID.13</td><td>ID.12..ID.5(not matched)</td><td>ID.4..ID.0 RTR X X(not matched)</td></tr></table>

滤波ID1  

<table><tr><td>ACR0[7:0]</td><td>ACR1[7:0]</td></tr><tr><td>AMR0[7:0]</td><td>AMR1[7:0]</td></tr></table>

滤波ID2  

<table><tr><td>ACR2[7:0]</td><td>ACR3[7:0]</td></tr><tr><td>AMR2[7:0]</td><td>AMR3[7:0]</td></tr></table>

此时，实际接收的ID12—ID5，不同ACR比较。

ACR和AMR的关系如下：

![](images/840618cbb914978079a34e134e39133f1d1c6324d89ba28dfd2af0da808d4809.jpg)  
图19-3 CAN模块ID滤波逻辑关系

# 19.2.2.7 发送帧格式

发送帧分成ID部分和数据部分。第一个字节包含了帧分类等信息，确定是SFF（标准）帧还是EFF（扩展）帧；确定是远程帧，还是数据帧；以及，确定数据长度。SFF的ID长度为2个字节，EFF的ID长度为4个字节。数据长度为最大8个字节。

表19-1发送帧结构  

<table><tr><td colspan="2">SFF</td><td colspan="2">EFF</td></tr><tr><td>地址</td><td>域</td><td>地址</td><td>域</td></tr><tr><td>0x40</td><td>TX 帧信息</td><td>0x40</td><td>TX 帧信息</td></tr><tr><td>0x44</td><td>TX ID0</td><td>0x44</td><td>TX ID0</td></tr><tr><td>0x48</td><td>TX ID1</td><td>0x48</td><td>TX ID1</td></tr><tr><td>0x4C</td><td>TX DATA0</td><td>0x4C</td><td>TX ID2</td></tr><tr><td>0x50</td><td>TX DATA1</td><td>0x50</td><td>TX ID3</td></tr><tr><td>0x54</td><td>TX DATA2</td><td>0x54</td><td>TX DATA0</td></tr><tr><td>0x58</td><td>TX DATA3</td><td>0x58</td><td>TX DATA1</td></tr><tr><td>0x5C</td><td>TX DATA4</td><td>0x5C</td><td>TX DATA2</td></tr><tr><td>0x60</td><td>TX DATA5</td><td>0x60</td><td>TX DATA3</td></tr><tr><td>0x64</td><td>TX DATA6</td><td>0x64</td><td>TX DATA4</td></tr><tr><td>0x68</td><td>TX DATA7</td><td>0x68</td><td>TX DATA5</td></tr><tr><td>0x6C</td><td>unused</td><td>0x6C</td><td>TX DATA6</td></tr><tr><td>0x70</td><td>unused</td><td>0x70</td><td>TX DATA7</td></tr></table>

# SFF帧非数据信息

表19-2发送SFF头信息  

<table><tr><td>CAN Address</td><td>BIT 7</td><td>BIT 6</td><td>BIT 5</td><td>BIT 4</td><td>BIT 3</td><td>BIT 2</td><td>BIT 1</td><td>BIT 0</td></tr><tr><td>0x40</td><td>FF</td><td>RTR</td><td>X1</td><td>X1</td><td>DLC.3</td><td>DLC.2</td><td>DLC.1</td><td>DLC.0</td></tr><tr><td>0x44</td><td>ID.28</td><td>ID.27</td><td>ID.26</td><td>ID.25</td><td>ID.24</td><td>ID.23</td><td>ID.22</td><td>ID.21</td></tr></table>

<table><tr><td>0x48</td><td>ID.20</td><td>ID.19</td><td>ID.18</td><td>X2</td><td>X1</td><td>X1</td><td>X1</td><td>X1</td></tr></table>

EFF帧非数据信息

表19-3发送EFF头信息  

<table><tr><td>CAN Address</td><td>BIT 7</td><td>BIT 6</td><td>BIT 5</td><td>BIT 4</td><td>BIT 3</td><td>BIT 2</td><td>BIT 1</td><td>BIT 0</td></tr><tr><td>0x40</td><td>FF</td><td>RTR</td><td>X1</td><td>X1</td><td>DLC.3</td><td>DLC.2</td><td>DLC.1</td><td>DLC.0</td></tr><tr><td>0x44</td><td>ID.28</td><td>ID.27</td><td>ID.26</td><td>ID.25</td><td>ID.24</td><td>ID.23</td><td>ID.22</td><td>ID.21</td></tr><tr><td>0x48</td><td>ID.20</td><td>ID.19</td><td>ID.18</td><td>ID.17</td><td>ID.16</td><td>ID.15</td><td>ID.14</td><td>ID.13</td></tr><tr><td>0x4C</td><td>ID.12</td><td>ID.11</td><td>ID.10</td><td>ID.9</td><td>ID.8</td><td>ID.7</td><td>ID.6</td><td>ID.5</td></tr><tr><td>0x50</td><td>ID.4</td><td>ID.3</td><td>ID.2</td><td>ID.1</td><td>ID.0</td><td>X2</td><td>X1</td><td>X1</td></tr></table>

FF：1表示是EFF（扩展）帧，0表示是SFF（标准）帧。

RTR：1标识是remote（远程）帧，0表示是data（数据）帧。

DLC：表示此帧要发送数据的长度。最大为8个字节，最小为0个字节。

ID：帧标识号。SFF帧的ID长度为11位（ID.28到ID.18）。EFF帧的ID长度为29位（ID.28到ID.0）。高位优先发送。

DATA：数据。字节间顺序，从大到小，即TXDATA7先发送。字节内顺序，从高位到低位。

X2：最好同RTR值一致

X1：1或0均可

19.2.2.8接收帧格式

接收帧分成ID部分和数据部分。第一个字节包含了帧分类等信息，确定是SFF（标准）帧还是EFF（扩展）帧；确定是远程帧，还是数据帧；以及，确定数据长度。SFF的ID长度为2个字节，EFF的ID长度为4个字节。数据长度为最大8个字节。

表19-4接收帧结构  

<table><tr><td colspan="2">SFF</td><td colspan="2">EFF</td></tr><tr><td>地址</td><td>域</td><td>地址</td><td>域</td></tr><tr><td>0x40</td><td>RX 帧信息</td><td>0x40</td><td>RX 帧信息</td></tr><tr><td>0x44</td><td>RX ID0</td><td>0x44</td><td>RX ID0</td></tr><tr><td>0x48</td><td>RX ID1</td><td>0x48</td><td>RX ID1</td></tr><tr><td>0x4C</td><td>RX DATA0</td><td>0x4C</td><td>RX ID2</td></tr><tr><td>0x50</td><td>RX DATA1</td><td>0x50</td><td>RX ID3</td></tr><tr><td>0x54</td><td>RX DATA2</td><td>0x54</td><td>RX DATA0</td></tr><tr><td>0x58</td><td>RX DATA3</td><td>0x58</td><td>RX DATA1</td></tr><tr><td>0x5C</td><td>RX DATA4</td><td>0x5C</td><td>RX DATA2</td></tr><tr><td>0x60</td><td>RX DATA5</td><td>0x60</td><td>RX DATA3</td></tr><tr><td>0x64</td><td>RX DATA6</td><td>0x64</td><td>RX DATA4</td></tr></table>

<table><tr><td>0x68</td><td>RX DATA7</td><td>0x68</td><td>RX DATA5</td></tr><tr><td>0x6C</td><td>unused</td><td>0x6C</td><td>RX DATA6</td></tr><tr><td>0x70</td><td>unused</td><td>0x70</td><td>RX DATA7</td></tr></table>

SFF帧非数据信息

表19-5接收SFF头信息  

<table><tr><td>CAN Address</td><td>BIT 7</td><td>BIT 6</td><td>BIT 5</td><td>BIT 4</td><td>BIT 3</td><td>BIT 2</td><td>BIT 1</td><td>BIT 0</td></tr><tr><td>0x40</td><td>FF</td><td>RTR</td><td>0</td><td>0</td><td>DLC.3</td><td>DLC.2</td><td>DLC.1</td><td>DLC.0</td></tr><tr><td>0x44</td><td>ID.28</td><td>ID.27</td><td>ID.26</td><td>ID.25</td><td>ID.24</td><td>ID.23</td><td>ID.22</td><td>ID.21</td></tr><tr><td>0x48</td><td>ID.20</td><td>ID.19</td><td>ID.18</td><td>RTR</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

EFF帧非数据信息

表19-6接收EFF头信息  

<table><tr><td>CAN Address</td><td>BIT 7</td><td>BIT 6</td><td>BIT 5</td><td>BIT 4</td><td>BIT 3</td><td>BIT 2</td><td>BIT 1</td><td>BIT 0</td></tr><tr><td>0x40</td><td>FF</td><td>RTR</td><td>0</td><td>0</td><td>DLC.3</td><td>DLC.2</td><td>D LC.1</td><td>DLC.0</td></tr><tr><td>0x44</td><td>ID.28</td><td>ID.27</td><td>ID.26</td><td>ID.25</td><td>ID.24</td><td>ID.23</td><td>ID.22</td><td>ID.21</td></tr><tr><td>0x48</td><td>ID.20</td><td>ID.19</td><td>ID.18</td><td>ID.17</td><td>ID.16</td><td>ID.15</td><td>ID.14</td><td>ID.13</td></tr><tr><td>0x4C</td><td>ID.12</td><td>ID.11</td><td>ID.10</td><td>ID.9</td><td>ID.8</td><td>ID.7</td><td>ID.6</td><td>ID.5</td></tr><tr><td>0x50</td><td>ID.4</td><td>ID.3</td><td>ID.2</td><td>ID.1</td><td>ID.0</td><td>RTR</td><td>0</td><td>0</td></tr></table>

# 19.2.2.9发送

CAN模块要发送数据，必须在正常工作模式下。

执行发送操作，一般推荐开启发送中断源和错误警告数量中断源，而仲裁丢失和总线错误中断源头不强迫开启，CAN模块有自动重发机制。

发送的数据，存放在TXFIFO中，TXFIFO为32- Byte，及一次可以存几帧数据，且TXFIFO中的数据一旦被成功发送出去，就被CAN模块释放掉供新的数据写入。一帧数据长度为13个字节，其考虑到最大数据量为8个字节。在发送之前，需确保此时模块处于空闲状态。

发送帧的格式，分成标准帧（SFF）和扩展帧（EFF）。CAN_CMR的BIT0置1，触发CAN模块发送数据。一旦CAN总线空闲，数据就会发出。传输完毕与否，一方面可以检查CAN_SR的BIT2是否变成1（1表示空闲），也可以通过中断方式检查是否发送完毕。

在数据发送到总线前，设置CAN_CMR的BIT1，可以停止发送，产生相应中断；通过CAN_SR的BIT3，可知当前数据是否发送完毕。

# 19.2.2.10接收

CAN模块要接收数据，必须在正常工作模式下。

接收 FIFO 中存储的帧大小可以不同（3～13 byte 范围之间）。当接 FIFO 为满时（或剩余的空间不足以完全存储一帧），将触发溢出中断，后续的接收帧将丢失，直到接收 FIFO 中清除出足够的存储空间。接收 FIFO 中的第一条帧将被映射到 13- byte 的接收缓冲器中，直到该帧被清除（通过释放接收缓冲器指令）。清除后，接收缓冲器将继续映射接收 FIFO 中的下一条帧，接收 FIFO 中上一条已清除帧的空间将被释放。

接收，开始于侦测到 Start 帧。接收到的数据，执行 ID 匹配操作：

匹配成功，存入 RX FIFO，RMC 递增。RX FIFO 为 32- Byte，即一次可以存几帧数据，且 RX FIFO 中的数据一旦被 DMA 成功取走，就被 CAN 模块释放掉供新的数据写入（非 DMA 模式，需要对 CAN_CMR BIT2 写 1 释放 RX FIFO）。一帧数据长度为 13 个字节，其考虑到最大数据量为 8 个字节。RX FIFO 中有几个有效帧，通过 CAN_AMC 寄存器可知。通过读取 CAN_TXRX 寄存器可以获得最先被接收到的数据帧。若 RX FIFO 满了，抛弃此帧，RX FIFO 不接收，同时产生溢出中断（使能前提下）。

匹配失败，存入 RX FIFO，RMC 不会递增。因此，数据也会被后续帧覆盖。若 RX FIFO 满了，抛弃此帧，RX FIFO 不接收，不产生溢出中断（使能前提下）。

# 19.2.2.11 错误管理

CAN 协议要求每个节点中都包含发送错误计数和接收错误计数。这两个错误计数的数值决定了控制器当前的错误状态（如主动错误、被动错误、离线）。控制器将数值分别存储在 CAN_RXERR 和 CAN_TXERR 中，CPU 可随时进行读取。除了错误状态之外，控制器还提供错误报警限制的功能，这个功能可在 CAN 控制器进入被动错误状态之前，提醒用户，当前发生的严重总线错误。

![](images/7ed3ec7f0a0c899d1927d053646a0cfdefaf9c0a1d5c6e3c1b64c45819a1b158.jpg)  
图 19-4 CAN 模块错误管理

若发生总线错误，总线错误中断标志位（CAN_IR.BUS_ERR_IF）置位，对应中断使能的话，将产生对应中断。当总线错误积累到一定数值，总线错误报警中断位（CAN_IR.W_ERR_IF）置位，对应中断使能的话，将产生对应中断；CAN_SR.ERROR_OV 置位，表明错误超过警戒线。若继续增加，超过 127，进入被动错误状态，被动错误中断位（CAN_IR.M_ERR_IF）置位，对应中断使能的话，将产生对应中断。若总线错误继续增加（每次增加总线错误中断标志位都会置位），发送错误超过 255，CAN_SR.ON_BUS 置位进入总线关闭状态。此时，开始离线恢复，从 127 开始递减，减到 0 完成恢复，CAN_SR.ON_BUS 和 CAN_SR.ERROR_OV 自动清除。

只要发生总线错误，总线错误中断标志位（CAN_IR.BUS_ERR_IF）均置位。

# 19.2.2.12错误计数

发送错误计数和接收错误计数根据以下规则递增/递减。请注意，一帧传输中可应用多个规则。

1. 当接收器检测到错误时，接收错误计数数值将增加1。当检测到的错误为发送主动错误标志或过载标志期间的位错误除外。

2. 发送错误标志后，当接收器第一个检测到的位是显性位时，接收错误计数数值将增加8。

3. 当发送器发送错误标志时，发送错误计数数值增加8。但是，以下情况不适用于该规则：

·发送器为被动错误状态，因为在应答槽未检测到显性位而产生应答错误，且在发送被动错误标志时检测到显性位时，则发送错误计数数值不应增加。

·发送器在仲裁期间因填充错误而发送错误标志，且填充位本该是隐性位但是检测到显性位，则发送错误计数数值不应增加。

4. 若发送器在发送主动错误标志和过载标志时检测到位错误，则发送错误计数数值增加8。

5. 若接收器在发送主动错误标志和过载标志时检测到位错误，则接收错误计数数值增加8。

6. 任意节点在发送主动/被动错误标志或过载标志后，节点仅能承载最多7个连续显性位。在（发送主动错误标志或过载标志时）检测到第14个连续显性位，或在被动错误标志后检测到第8个连续显性位后，发送器将使其发送错误计数数值增加8，而接收器将使其接收错误计数数值增加8。每增加8个连续显性位的同时，（发送器的）发送错误计数和（接收器的）接收错误计数数值也将增加8。

7. 每当发送器成功发送帧后（接收到ACK，且直到EOF完成未发生错误），则发送错误计数数值将减小1，除非发送错误计数的数值已经为0。

8. 当接收器成功接收帧后（确认槽前未检测到错误，且成功发送ACK），则接收错误计数数值将相应减小。

·若接收错误计数数值位于  $1\sim 127$  之间，则其值减小1。

·若接收错误计数数值大于127，则其值减小到127。

·若接收错误计数数值为0，则仍保持为0。

9. 当一个节点的发送错误计数和/或接收错误计数数值大于等于128时，该节点变为被动错误节点。导致节点发生上述状态切换的错误，该节点仍发送主动错误标志。请注意，一旦接收错误计数数值到达128，后续任何增加该值的动作都是无效的，直到接收错误计数数值返回到128以下。

10. 当某节点的发送错误计数数值大于等于256时，该节点将变为离线节点。

11. 当某被动错误节点的发送错误计数和接收错误计数数值都小于等于127，则该节点将变为主动错误节点。

12. 当离线节点在总线上检测到128次11个连续隐性位后，该节点可变为主动错误节点（发送错误计数和接收错误计数数值都重设为0）。

# 19.2.2.13错误报警限制

错误报警限制（CAN_EWLR）为发送和接收的可配置闻值，若错误计数数值超过该闻值，将触发CAN总线错误中断，作为一个报警功能提示当前发生的严重CAN总线错误，且在CAN控制器进入被动错误状态之前被触发。CAN_EWLR寄存器存储相应闻值，此寄存器的配置必须处于复位模式下。CAN_EWLR寄存器默认数值为96。

当发送和/或接收错误的数值大于等于CAN_EWLR寄存器对应的数值时，CAN_IR.W_ERR_IF位将立即被置1。同理，当发送和/或接收错误的数值都小于CAN_EWLR寄存器对应的数值时，CAN_IR.W_ERR_IF位将立即复位为0。只要CAN_IR.W_ERR_IF（CAN_EIR.W_ERR_IF使能）位值变成1，便会触发错误报警中断。

# 19.2.2.14被动错误

19.2.2.14被动错误当发送或接收错误的数值大于127时，CAN控制器处于被动错误状态，CAN_IR.M_ERR_IF位将立即被置1。同理，当发送或接收错误的数值都小于等于127时，CAN控制器进入主动错误状态。每当CAN控制器从主动错误状态变为被动错误状态，或反之时，CAN_IR.M_ERR_IF位都将立即被置1。

# 19.2.2.15离线状态与离线恢复

当发送错误的数值大于255时，CAN控制器将进入离线状态。进入离线状态后，CAN控制器将自动进行以下动作：

·接收错误计数器的数值置为0·发送错误计数器的数值置为127·CAN_IR.BUS_ERR_IF位置1·进入CAN的复位模式

每当CAN_IR.BUS_ERR_IF/CAN_IR.W_ERR_IF的数值发生变化时，都将触发错误报警中断。

为了返回主动错误状态，CAN控制器必须进行离线恢复。要启动离线恢复，首先需要退出复位模式，进入操作模式。然后要求CAN控制器在总线上检测到128次11个连续隐性位。每一次CAN控制器检测到11个连续隐性位时，发送错误计数器的数值都将减小，以追踪离线恢复进程。当离线恢复完成后（发送错误的数值从127减小到0），CAN_IR.BUS_ERR_IF位将自动复位为0，从而触发错误报警中断。

# 19.2.3 寄存器

# 19.2.3.1地址分配

CAN模块寄存器的基地址是0x4001_3400，寄存器列表如下。

表19-7CAN寄存器地址分配  

<table><tr><td>名称</td><td>偏移</td><td>说明</td></tr><tr><td>CAN_MOD</td><td>0x000</td><td>CAN 模式寄存器</td></tr><tr><td>CAN_CMR</td><td>0x004</td><td>CAN 命令寄存器</td></tr></table>

<table><tr><td>CAN_SR</td><td>0x008</td><td>CAN 状态寄存器</td></tr><tr><td>CAN_IR</td><td>0x00C</td><td>CAN 中断状态寄存器</td></tr><tr><td>CAN_IER</td><td>0x010</td><td>CAN 中断控制寄存器</td></tr><tr><td>CAN_BTR0</td><td>0x018</td><td>CAN 总线时序控制寄存器 0</td></tr><tr><td>CAN_BTR1</td><td>0x01C</td><td>CAN 总线时序控制寄存器 1</td></tr><tr><td>CAN_ALC</td><td>0x02C</td><td>CAN 仲裁丢失捕捉寄存器</td></tr><tr><td>CAN_ECC</td><td>0x030</td><td>CAN 错误码捕捉寄存器</td></tr><tr><td>CAN_EWLR</td><td>0x034</td><td>CAN 错误&amp;amp;警告门限值设置寄存器</td></tr><tr><td>CAN_RXERRR</td><td>0x038</td><td>CAN 接收错误计数器</td></tr><tr><td>CAN_TXERR</td><td>0x03C</td><td>CAN 发送错误计数器</td></tr><tr><td>CAN_TXRX0</td><td>0x040</td><td>正常工作模式下，CAN 发送帧格式寄存器/CAN 接收帧格式寄存器</td></tr><tr><td>CAN_TXRX1</td><td>0x044</td><td>正常工作模式下，CAN 发送数据寄存器 0/CAN 接收数据寄存器 0</td></tr><tr><td>CAN_TXRX2</td><td>0x048</td><td>正常工作模式下，CAN 发送数据寄存器 1/CAN 接收数据寄存器 1</td></tr><tr><td>CAN_TXRX3</td><td>0x04C</td><td>正常工作模式下，CAN 发送数据寄存器 2/CAN 接收数据寄存器 2</td></tr><tr><td>CAN_TXRX4</td><td>0x050</td><td>正常工作模式下，CAN 发送数据寄存器 3/CAN 接收数据寄存器 3</td></tr><tr><td>CAN_TXRX5</td><td>0x054</td><td>正常工作模式下，CAN 发送数据寄存器 4/CAN 接收数据寄存器 4</td></tr><tr><td>CAN_TXRX6</td><td>0x058</td><td>正常工作模式下，CAN 发送数据寄存器 5/CAN 接收数据寄存器 5</td></tr><tr><td>CAN_TXRX7</td><td>0x05C</td><td>正常工作模式下，CAN 发送数据寄存器 6/CAN 接收数据寄存器 6</td></tr><tr><td>CAN_TXRX8</td><td>0x060</td><td>正常工作模式下，CAN 发送数据寄存器 7/CAN 接收数据寄存器 7</td></tr><tr><td>CAN_TXRX9</td><td>0x064</td><td>正常工作模式下，CAN 发送数据寄存器 8/CAN 接收数据寄存器 8</td></tr><tr><td>CAN_TXRXA</td><td>0x068</td><td>正常工作模式下，CAN 发送数据寄存器 9/CAN 接收数据寄存器 9</td></tr><tr><td>CAN_TXRXB</td><td>0x06C</td><td>正常工作模式下，CAN 发送数据寄存器 10/CAN 接收数据寄存器 10</td></tr><tr><td>CAN_TXRXC</td><td>0x070</td><td>正常工作模式下，CAN 发送数据寄存器 11/CAN 接收数据寄存器 11</td></tr><tr><td>CAN_ACR0</td><td>0x040</td><td>复位模式下，CAN ID 码寄存器 0</td></tr><tr><td>CAN_ACR1</td><td>0x044</td><td>复位模式下，CAN ID 码寄存器 1</td></tr><tr><td>CAN_ACR2</td><td>0x048</td><td>复位模式下，CAN ID 码寄存器 2</td></tr><tr><td>CAN_ACR3</td><td>0x04C</td><td>复位模式下，CAN ID 码寄存器 3</td></tr><tr><td>CAN_AMR0</td><td>0x050</td><td>复位模式下，CAN ID 掩码寄存器 0</td></tr><tr><td>CAN_AMR1</td><td>0x054</td><td>复位模式下，CAN ID 掩码寄存器 1</td></tr><tr><td>CAN_AMR2</td><td>0x058</td><td>复位模式下，CAN ID 掩码寄存器 2</td></tr><tr><td>CAN_AMR3</td><td>0x05C</td><td>复位模式下，CAN ID 掩码寄存器 3</td></tr><tr><td>CAN_RMC</td><td>0x074</td><td>CAN FIFO 有效接收信息计数器</td></tr><tr><td>CAN_RBSA</td><td>0x078</td><td>CAN 第一条有效接收信息在 FIFO 中的地址寄存器</td></tr><tr><td>CAN_RFIFO0～CAN_RFIFO31</td><td>0x080～0x144</td><td>CAN RX FIFO 地址寄存器</td></tr><tr><td>CAN_TFIFO0～CAN_TFIFO31</td><td>0x180～0x1B0</td><td>CAN TX FIFO 地址寄存器</td></tr></table>

# 19.2.3.2 寄存器说明

# 19.2.3.2.1 CAN_MOD 模式寄存器

地址：0x4001_3400

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="4" colspan="15"></td><td></td></tr><tr><td></td></tr><tr><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:5]</td><td></td><td>未使用</td></tr><tr><td>[4]</td><td>SLEEP</td><td>正常工作模式下写1，触发休眠操作，进入休眠模式。</td></tr><tr><td>[3]</td><td>FLT_ID</td><td>CAN滤波ID选择。默认值为0。
1：单滤波ID。一个32位长的滤波ID
0：双滤波ID。两个短滤波ID</td></tr><tr><td>[2]</td><td>TEST_MODE</td><td>CAN工作模式选择。默认值为0。
1：自测试模式
0：正常工作模式</td></tr><tr><td>[1]</td><td>FUNC_MODE</td><td>CAN工作模式选择。默认值为0。
1：监听模式
0：正常工作模式</td></tr><tr><td>[0]</td><td>MODE</td><td>CAN工作模式选择。默认值为1。
1：复位模式
0：正常工作模式</td></tr></table>

# 19.2.3.2.2 CAN_CMR 命令寄存器

地址：0x4001_3404

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr></table>

<table><tr><td rowspan="3" colspan="2"></td><td>DMA_EN</td><td>RX_DUR_TX</td><td>CLR_OV</td><td>RELEASE_FIFO</td><td>INTR_TRAN</td><td>TRANS_REQ</td></tr><tr><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td>WO</td><td>WO</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr></table>

<table><tr><td>[31:6]</td><td></td><td>未使用</td></tr><tr><td>[5]</td><td>DMA_EN</td><td>写 1，使能 DMA 功能</td></tr><tr><td>[4]</td><td>RX_DUR_TX</td><td>写 1，发送数据的同时也将数据接收回来</td></tr><tr><td>[3]</td><td>CLR_OV</td><td>写 1，清除数据溢出标志位</td></tr><tr><td>[2]</td><td>RELEASE_FIFO</td><td>写 1，释放 RIFIFO</td></tr><tr><td>[1]</td><td>INTR_TRANS</td><td>写 1，将中断取消未执行的发送传输</td></tr><tr><td>[0]</td><td>TRANS_REQ</td><td>写 1，产生 CAN 发送传输请求</td></tr></table>

# 19.2.3.2.3 CAN_SR状态寄存器

地址：0x4001_3408

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td rowspan="3"></td><td>ON_BUS</td><td>ERR_OV</td><td>TXING</td><td>RXING</td><td>TRANS_DONE</td><td>TFIFO_EMPTY</td><td>RFIFO_EMPTY</td><td>DATA&gt;AVAL</td><td>DATA</td><td></td></tr><tr><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7]</td><td>ON_BUS</td><td>1：CAN 模块，处于 BUS OFF 状态，无数据发送接收动作
0：CAN 模块，可以发送数据到 CAN 总线，或接收 CAN 总线数据</td></tr><tr><td>[6]</td><td>ERR_OV</td><td>1：CAN 传输产生的错误总数达到或超过 CAN_EWL 规定值
0：CAN 传输产生的错误总数低于 CAN_EWL 规定值
错误值低于 CAN_EWLR，标志自动拉低</td></tr><tr><td>[5]</td><td>TXING</td><td>1：CAN 模块正在发送一帧数据
0：CAN 模块没有发送数据的动作</td></tr><tr><td>[4]</td><td>RXING</td><td>1：CAN 模块正在接收一帧数据
0：CAN 模块没有接收数据的动作</td></tr><tr><td>[3]</td><td>TRANS_DONE</td><td>1：最近一次传输已完成
0：最近一次传输未完成</td></tr><tr><td>[2]</td><td>TFIFO_EMPTY</td><td>1：TFIFO 空，可以写入发送数据
0：TFIFO 非空，内部数据没有发送完毕</td></tr><tr><td>[1]</td><td>RFIFO_EMPTY</td><td>1：RFIFO 存入的帧太多，已满，导致数据丢失
0：RFIFO 未满
对 CAN_CMR BIT[2]写 1，可清除此位（表示用户已经取走一帧数据，暂时 RFIFO 非满了）</td></tr></table>

<table><tr><td>[0]</td><td>DATA&gt;AVALI</td><td>1: RFIFO存有一帧或多帧数据，可以通过RFIFO寄存器读取
0: RFIFO没有有效帧数据</td></tr></table>

# 19.2.3.2.4 CAN_IR中断状态寄存器

地址：0x4001_340C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>BUS_ERR_IF</td><td></td><td>LOST_ERR_IF</td><td></td><td>M_ERR_IF</td><td></td><td>WK_IF</td><td></td><td>RFIFO_OV_IF</td><td></td><td>W_ERR_IF</td><td></td><td>TX_DONE_IF</td><td></td><td>RFIFO_N_EMPTY_IF</td><td></td></tr><tr><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td>RO</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7]</td><td>BUS_ERR_IF</td><td>1：总线错误中断（CAN_EIR.7为有效前提下）</td></tr><tr><td>[6]</td><td>LOST_ARB_IF</td><td>1：丢失仲裁，改成接收模式（CAN_EIR.6为有效前提下）</td></tr><tr><td>[5]</td><td>M_ERR_IF</td><td>被动错误中断。若值为1，表明节点由于错误计数数值的变化，在主动错误状态与被动错误状态间发生了切换。</td></tr><tr><td>[4]</td><td>WK_IF</td><td>1：CAN模块从休眠中唤醒（CAN_EIR.4为有效前提下）</td></tr><tr><td>[3]</td><td>RFIFO_OV_IF</td><td>1：RFIFO数据发生溢出（CAN_EIR.3为有效前提下）</td></tr><tr><td>[2]</td><td>W_ERR_IF</td><td>错误报警中断。若值为1，表明SR寄存器中CAN_SR.7和CAN_SR.6发生变化（0变为1或1变为0）。
1：CAN_SR.7或者CAN_SR.6有变化（CAN_EIR.2为有效前提下）</td></tr><tr><td>[1]</td><td>TX_DONE_IF</td><td>4：发送完毕当前帧（CAN_EIR.1为有效前提下），可以执行新的数据发送任务</td></tr><tr><td>[0]</td><td>RFIFO_N_EMP
TY_IF</td><td>1：RFIFO有数据（CAN_EIR.0为有效前提下）</td></tr></table>

CAN_IR寄存器，为读清除寄存器。只有BIT0- - RFIFO_N_EMPTY_IF无法读清除，此位只能通过对CAN_CMRBIT2写1清除，若RXFIFO有多帧接收的数据，CAN_CMRBIT2写1也无法清除，除非RXFIFO全部读完，即读一帧数据写CAN_CMRBIT2，反复迭代。

# 19.2.3.2.5 CAN_EIR中断控制寄存器

地址：0x4001_3410

复位值：0x0

表19-12中断控制寄存器CAN_EIR  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td rowspan="4"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>BUS_ERR_IE</td><td></td><td>LOST_ERR_IE</td><td></td><td>M_ERR_IE</td><td></td><td>WK_IE</td><td></td><td>RFIFO_OV_IE</td><td></td><td>CAN_SRG7_IE</td><td></td><td>TX_DONE_IE</td><td></td><td>RFIFO_N_EMPTY_IE</td><td></td></tr><tr><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7]</td><td>BUS_ERR_IE</td><td>1：总线错误中断，中断源使能
0：该中断源关闭</td></tr><tr><td>[6]</td><td>LOST_ERR_IE</td><td>1：丢失仲裁，改成接收模式，中断源使能
0：该中断源关闭</td></tr><tr><td>[5]</td><td>M_ERR_IE</td><td>1：被动错误中断源使能
0：该中断源关闭</td></tr><tr><td>[4]</td><td>WK_IE</td><td>1：CAN 模块从休眠中唤醒，中断源使能
0：该中断源头关闭</td></tr><tr><td>[3]</td><td>RFIFO_OV_IE</td><td>1：RFIFO 数据发生溢出，中断源使能
0：该中断源头关闭</td></tr><tr><td>[2]</td><td>W_ERR_IE</td><td>1：错误报警中断，CAN_SR.7 或者 CAN_SR.6 有变化，中断源使能
0：该中断源头关闭</td></tr><tr><td>[1]</td><td>TX_DONE_IE</td><td>1：发送完毕当前帧，中断源使能
0：该中断源头关闭</td></tr><tr><td>[0]</td><td>RFIFO_N_EMP
TY_IE</td><td>1：RFIFO 有新的数据被接收到，中断源使能
0：该中断源头关闭</td></tr></table>

# 19.2.3.2.6 CAN_BTR0波特率0控制寄存器

地址：0x4001_3418

复位值：0x0

表19-13波特率0控制寄存器CAN_BTR0  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr></table>

<table><tr><td rowspan="3"></td><td>SJW</td><td>BAUDRATE</td></tr><tr><td>RW</td><td>RW</td></tr><tr><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:6]</td><td>SJW</td><td rowspan="2">同步跳转宽度配置。公式如下：
Tsjw = TQ*(SJW + 1)
波特率配置，计算 CAN 传输基本时间单元参数 TQ,Tclk 为 CAN 模块的系统时钟频率
TQ = 2*Tclk*(BAUDRATE+1)</td></tr><tr><td>[5:0]</td><td>BAUDRATE</td></tr></table>

# 19.2.3.2.7 CAN_BTR1波特率1控制寄存器

地址：0x4001_341C

复位值：0x0

表19-14波特率1控制寄存器CAN_BTR1  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="7"></td><td>OSR</td><td colspan="3">SEG2</td><td colspan="4">SEG1</td><td></td></tr><tr><td>RW</td><td colspan="3">RW</td><td colspan="4">RW</td><td></td></tr><tr><td>0</td><td colspan="3">0</td><td colspan="4">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7]</td><td>OSR</td><td>1: 1-bit 数据被采样 3 次
0: 1-bit 数据被采样 1 次</td></tr><tr><td>[6:4]</td><td>SEG2</td><td>SEG2 段时间
Tseg2 = TQ*(SEG2+1)</td></tr><tr><td>[3:0]</td><td>SEG1</td><td>SEG1 段时间
Tseg1 = TQ*(SEG1+1)</td></tr></table>

# 19.2.3.2.8 CAN_ALC仲裁丢失捕捉寄存器

地址：0x4001_342C

复位值：0x0

<table><tr><td colspan="15">表19-15仲裁丢失捕捉寄存器CAN_ALC</td><td></td></tr><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr></table>

<table><tr><td rowspan="3"></td><td>LOST_ARB</td></tr><tr><td>RW</td></tr><tr><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>LOST_ARB</td><td>记录总线仲裁丢失的具体位置。
0：ID 的第一位
1：ID 的第二位
2：ID 的第三位
3：ID 的第四位
4：ID 的第五位
5：ID 的第六位
6：ID 的第七位
7：ID 的第八位
8：ID 的第九位
9：ID 的第十位
A：ID 的第十一位
B：SRTR 位
C：IDE 位</td></tr></table>

# 19.2.3.2.9 CAN_ECC 错误码捕捉寄存器

地址：0x4001_3430

复位值：0x0

表19-16错误码捕捉寄存器CAN_ECC  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15"></td><td></td></tr><tr><td rowspan="3" colspan="6"></td><td>BUS_ERR_TYPE</td><td>ERR_TIMING</td><td colspan="7">ERR_POSITION</td><td></td></tr><tr><td>RO</td><td>RO</td><td colspan="7">RO</td><td></td></tr><tr><td>0</td><td>0</td><td colspan="7">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:6]</td><td>BUS_ERR_TYPE</td><td>总线错误类型
00: bit 错误
01: 格式错误
10: 填充错误
11: 其它类型错误</td></tr><tr><td>[5]</td><td>ERR_TIMING</td><td>1: 总线错误发生在接收过程中</td></tr></table>

<table><tr><td></td><td></td><td>0：总线错误发生在发送过程中</td></tr><tr><td>[4:0]</td><td>ERR_POSITION</td><td>错误发生的位置
02：ID.28 到 ID.21
03：起始帧
04：SRTR 位
05：IDE 位
06：ID.20 到 ID.18
07：ID.17 到 ID.13
08：CRC 数据段
09：保留位，固定为 0
0A：Data Field
0B：Data Length Code
0C：RTR 位
0D：保留位，固定为 1
0E：ID.4 到 ID.0
0F：ID.12 到 ID.5
11：active error flag
12：Intermission
13：Tolerate dominant 位
16：passive error flag
17：Error delimiter
18：CRC delimiter
19：确认位
1A：帧结束
1B：确认 delimiter
1C：Overload flag</td></tr></table>

# 19.2.3.2.10 CAN_EWLR 错误&警告门限值寄存器

地址：0x4001_3434

复位值：0x0

表19-17错误&警告门限值寄存器CAN_EWLR  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="6"></td><td colspan="9">EWLR</td><td></td></tr><tr><td colspan="9">RW</td><td></td></tr><tr><td colspan="9">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>EWLR</td><td>正常工作模式下只读，复位模式下可读写。写入新值后，在正常工作模式下生效。</td></tr></table>

# 19.2.3.2.11 CAN_RXERRR接收错误计数器寄存器

地址：0x4001_3438

复位值：0x0

<table><tr><td rowspan="3" colspan="2"></td><td>RXERR</td></tr><tr><td>RW</td></tr><tr><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>RXERRR</td><td>正常工作模式下只读，复位模式下可读写。
错误数超过 CAN_EWLR，CAN_SR_ERR_OV 被拉高；数值超过 127，CAN 模块进入被动错误状态。复位或者 BUS OFF 事件，硬件清零本寄存器。本寄存器自动增减，具体增减规则见本章 19.2.2.12。</td></tr></table>

# 19.2.3.2.12 CAN_TXERRR发送错误计数器寄存器

地址：0x4001_343C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="8"></td><td colspan="7">TXERR</td><td></td></tr><tr><td colspan="7">RW</td><td></td></tr><tr><td colspan="7">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>TXERR</td><td>正常工作模式下只读，复位模式下可读写。
错误数超过 CAN_EWLR，CAN_SR_ERR_OV 被拉高；数值超过 127，CAN 模块进入被动错误状态。数值超过 255，进入 BUS OFF 状态，CAN_MOD.MODE 被硬件拉高，处于复位模式。CAN_SR.ON_BUS 被硬件自动拉高，本寄存器被硬件赋值为 127；复位，硬件清零本寄存器。具体增减规则见本章 19.2.2.12。</td></tr></table>

# 19.2.3.2.13 CAN_TXRX0~CAN_TXRXC 发送接收寄存器

地址：0x4001_3440~0x4001_3470

复位值：0x0

表19-20发送接收寄存器CAN_TXRX  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>TXRX</td><td>发送或者接收数据寄存器。
正常工作模式下，该寄存器映射的是RFIFO中第一个有效帧数据；
正常工作模式下，对该寄存器写入数据，直接存入TFIFO中。</td></tr></table>

# 19.2.3.2.14 CAN_ACR ID 寄存器

地址：0x4001_3440~0x4001_344C

复位值：0x0

表19-21ID寄存器CANACR  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>ACR</td><td>仅复位模式下可用；复位模式下，可读写；
可接收的ID寄存器，当输入帧的ID同此匹配，则被CAN模块接受。配合AMR寄存器，可同一类ID匹配。</td></tr></table>

# 19.2.3.2.15 CAN_AMR ID 椭码寄存器

地址：0x4001_3450~0x4001_345C

复位值：0x0

表19-22ID掩码寄存器CAN_AMR  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="4" colspan="15"></td><td></td></tr><tr><td></td></tr><tr><td></td></tr><tr><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td rowspan="2">AMR</td><td>未使用</td></tr><tr><td>[7:0]</td><td>仅复位模式下可用；复位模式下，可读写；
配合ACR寄存器，同输入ID进行匹配。AMR寄存器某一位为0，标识ID对应位需要同ACR匹配；为1，标识ID对应位不需要同ACR匹配。</td></tr></table>

# 19.2.3.2.16 CAN_RMC FIFO 有效接收数据寄存器

地址：0x4001_3474

复位值：0x0

表19-23FIFO有效接收数据寄存器CAN_RMC  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="9"></td><td rowspan="3" colspan="5">FRAME_CNT</td><td></td><td></td></tr><tr><td colspan="5">RO</td><td></td></tr><tr><td colspan="5">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>FRAME_CNT</td><td>正常工作模式和复位模式，此寄存器均只可读。
CAN收到一帧数据，计数器自动累加1；DMA方式读取完毕一帧数据后，计数器自动减1；CPU方式读取完毕一帧数据后，软件需将CAN-CMR[2]写1，手动实现计数器减1。</td></tr></table>

# 19.2.3.2.17 CAN_RBSA 有效接收数据地址寄存器

地址：0x4001_3478

复位值：0x0

表19-24有效接收数据地址寄存器CAN_RBSA  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="7"></td><td colspan="9"></td><td colspan="5">RBSA</td></tr><tr><td colspan="9"></td><td colspan="5">RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td></td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:5]</td><td></td><td>未使用</td></tr><tr><td>[4:0]</td><td>RBSA</td><td>正常工作模式，只可读。复位模式，可读写
RFIFO的大小为32字节，本寄存器指明第一帧有效接收数据在RFIFO的位置。</td></tr></table>

# 19.2.3.2.18 CAN_RFIFO0~CAN_RFIFO31 RX FIFO 寄存器

地址：0x4001_3480~0x4001_34FC

复位值：0x0

表19-25RXFIFO寄存器CAN_RFIFO0\~CAN_RFIFO31  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>RX_DATA</td><td>RX FIFO 地址
正常工作模式下，只可读；复位模式下，可读写。</td></tr></table>

# 19.2.3.2.19 CAN_TFIFO0~CAN_TFIFO12 TX FIFO 寄存器

地址：0x4001_3580~0x4001_35B0

复位值：0x0

表19-26TXFIFO寄存器CAN_TFIFO0\~CAN_TFIFO12  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>TX_DATA</td><td>TX FIFO 地址
正常工作模式下和复位模式下，均只可读。</td></tr></table>

LKS32MC08x User Manual

# 20SIF

# 20.1概述

20.1 概述SIF 总线接口，支持 SIF 协议，液晶显示器与电动车控制器之间的数据传输，实现其对运行状态和故障的检测。

# 20.2主要特性

20.2 主要特性- 采用国际标准 SIF 通信协议，接口通用方便。- 主从方式采用单线单向传输，即只需要一根传输线路，电动车控制器为发送，仪表为接收方。- 传输线与电动车控制故障运行灯共用 I/O 口，不占用额外资源。- 传输波特率自适应范围宽，主机可以利用空闲时间发送数据。- 时间基准单位范围广，32us <Tosc < 320us。- 数据的电平遵守 TTL 规范。- 一个中断向量。

# 20.3功能描述

# 20.3.1 功能框图

本接口采用同步串行设计，实现CPU同外部设备之间的SIF传输。支持轮询和中断方式获得传输状态信息。本接口的主要功能模块如下图所示。

![](images/acb35ec6d54ea341038385c34573e3d571b7d2f4c45c052abf65e2f51902cec8.jpg)  
图20-1SIF模块顶层功能框图

SIF接口同外界通讯只有sif_out一根信号线

# 20.3.2 功能说明

20.3.2 功能说明SIF 接口仅支持主发送，模块发送数据，将数据从并行转换成串行。可以开启或禁止中断。接口通过数据引脚 sif_out 连接到 SIF 总线。

# 20.3.3 模式选择

SIF接口仅有一种运行模式：主发送模式。因为SIF接口的传输速度很慢，不支持DMA传输。每次传输一个字节完毕后，产生中断信号。

![](images/f3012f3793e32a69b94d82ac7256bee1f82188727201ab4df9ce7d0bc8850512.jpg)  
图20-2SIF基本传输时序图

注：图17- 2占空比为2:1，可选配为3:1。SIF_FREQ[0]控制占空比的选择。

# 20.3.4 SIF接口传输

默认情况下，SIF接口关闭。若需要发送数据，需要使能SIF接口。为了产生正确的时序，必须在SIF_CFG中设定SIF接口的工作时钟。

# 20.3.5 中断处理

SIF接口仅含一种类型的中断事件- - 数据传输完成事件。

# 20.3.6 通讯速度设置

SIF接口的基本时间单位是32us- - Tosc。Tosc的产生来自系统时钟。在不同系统频率下，通过配置SIF_FREQ寄存器，获得我们需要的基准时间。

# 20.4寄存器

# 20.4.1 地址分配

SIF模块寄存器的基地址是0x4001_3800，寄存器列表如下：

表20-1SIF模块控制寄存器列表  

<table><tr><td>名称</td><td>偏移</td><td>说明</td></tr><tr><td>SIF_CFG</td><td>0x00</td><td>SIF 配置寄存器</td></tr><tr><td>SIF_FREQ</td><td>0x04</td><td>SIF 波特率配置寄存器</td></tr><tr><td>SIF_IRQ</td><td>0x08</td><td>SIF 中断寄存器</td></tr><tr><td>SIF_WDATA</td><td>0x0C</td><td>SIF 发送数据寄存器</td></tr></table>

# 20.4.2 寄存器说明

20.4.2.1SIF_CFG配置寄存器

地址：0x4001_3800

复位值：0x0

表20-2地址寄存器SIF_CFG  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td rowspan="3" colspan="11"></td><td colspan="2">LAST_BYTE</td><td></td><td>ENDIAN</td><td>EN</td></tr><tr><td colspan="2">RW</td><td></td><td>RW</td><td>RW</td></tr><tr><td colspan="2">0</td><td></td><td>0</td><td>0</td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:5]</td><td></td><td>未使用</td></tr><tr><td>[4]</td><td>LAST_BYTE</td><td>当前字节传输完毕后，结束本次传输。SIF接口传输当前字节，字节传输完成后，产生中断。在中断处理程序中对该位写1，让SIF接口恢复默认状态。若不操作此位，表明还有数据要发送。该位读回永远是0。</td></tr><tr><td>[3:2]</td><td></td><td>未使用</td></tr><tr><td>[1]</td><td>ENDIAN</td><td>SIF大小端设置。1，MSB；0，LSB。默认为0。</td></tr><tr><td>[0]</td><td>EN</td><td>SIF模块使能。默认值为0。
1，使能
0，关闭</td></tr></table>

# 20.4.2.2SIF_FREQ波特率寄存器

地址：0x4001_3804

复位值：0x0

表20-3系统控制寄存器SIF_FREQ  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3" colspan="7"></td><td colspan="6"></td><td colspan="5">TOSC</td><td colspan="2"></td><td>DUTY</td></tr><tr><td colspan="5">RW</td><td></td><td></td><td>RW</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="5">0</td><td></td><td></td><td>0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:4]</td><td>TOSC</td><td>96Mhz系统时钟下，基准时间单位Tosc设置。
01:32us; 02:64us; 03:96us; 04:128us
05:160us; 06:192us; 07:220us; 08:256us
09:288us; 10:320us; 其它均为32us。</td></tr></table>

<table><tr><td>[3:1]</td><td></td><td>未使用</td></tr><tr><td>[0]</td><td>DUTY</td><td>SIF 传输 Data 占空比
1: 占空比为 3:1
0: 占空比为 2:1</td></tr></table>

# 20.4.2.3SIF_IRQ状态控制寄存器

地址：0x4001_3808

复位值：0x0

表20-4状态控制寄存器SIF_IRQ  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="16"></td></tr><tr><td rowspan="3" colspan="9"></td><td>IF</td><td></td><td></td><td></td><td>IE</td><td></td><td></td></tr><tr><td>RW</td><td></td><td></td><td></td><td>RW</td><td></td><td></td></tr><tr><td>0</td><td></td><td></td><td></td><td>0</td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:5]</td><td></td><td>未使用</td></tr><tr><td>[4]</td><td>IF</td><td>SIF 中断事件，高电平有效。写 1 清除。</td></tr><tr><td>[3:1]</td><td></td><td>未使用</td></tr><tr><td>[0]</td><td>IE</td><td>SIF 中断使能信号，高电平有效。默认值为 0。</td></tr></table>

# 20.4.2.4SIF_WDATA数据寄存器

地址：0x4001_380C

复位值：0x0

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td rowspan="3" colspan="7"></td><td colspan="6"></td><td colspan="8">WDATA</td></tr><tr><td colspan="9">RW</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td colspan="9">0</td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:8]</td><td></td><td>未使用</td></tr><tr><td>[7:0]</td><td>WDATA</td><td>数据寄存器，SIF接口使能后，对该寄存器写入发送数据将触发SIF的数据传输。</td></tr></table>

# 21看门狗

# 21.1概述

看门狗工作于低速RC时钟域LSI，即使用32kHz进行计数。支持2s、4s、8s、64s四档复位时间可选。

复位控制寄存器SYS_RST_CFC_WDT_EN可用于使能或禁用看门狗，SYS_RST_CFC_WDT_EN  $= 1$  则使能看门狗模块。复位源记录寄存器SYS_RST_SRC.WDT_RST_RCD记录了看门狗复位事件，SYS_RST_SRC.WDT_RST_RCD为高表示发生过看门狗复位。

看门狗复位是硬件全局复位，其作用域等同于外部引脚复位以及内部的上电复位。

# 21.2寄存器

# 21.2.1 地址分配

看门狗模块寄存器基地址为0x4000_0000。

表21-1看门狗模块寄存器  

<table><tr><td>名称</td><td>偏移</td><td>说明</td></tr><tr><td>SYS_WDT_CLR</td><td>0x38</td><td>看门狗清零寄存器</td></tr></table>

# 21.2.2 寄存器说明

21.2.2.1SYS_WDT_CLR看门狗清零寄存器

表21-2看门狗清零寄存器SYS_WDT_CLR  

<table><tr><td>15</td><td>14</td><td>13</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr><tr><td colspan="15">WDT_CLR</td><td></td></tr><tr><td colspan="15">WO</td><td></td></tr><tr><td colspan="15">0</td><td></td></tr></table>

<table><tr><td>位置</td><td>位名称</td><td>说明</td></tr><tr><td>[31:16]</td><td></td><td>未使用</td></tr><tr><td>[15:0]</td><td>WDT_CLR</td><td>写入字节 16&#x27;b0111_1001_1000_1B2B1B0。高 13 位为密码，密码正确时，B[2:0]才能写入其中，B[2:1]为 MODE
2&#x27;b00: 64 秒复位
2&#x27;b01: 8 秒复位</td></tr></table>

<table><tr><td></td><td></td><td>2&#x27;b10: 4秒复位
2&#x27;b11: 2秒复位
B[0]为CLR，写入1，则复位WDT计数器</td></tr></table>

看门狗清零前，需要向 SYS_WR_PROTECT 写入 0xCAFE，开启 WatchDog SYS_WDT_CLR 寄存器写入。

# 22 版本历史

表22-1文档版本历史  

<table><tr><td>时间</td><td>版本号</td><td>说明</td></tr><tr><td>2025.06.10</td><td>1.41</td><td>修改 CAN 波特率计算公式</td></tr><tr><td>2025.05.20</td><td>1.40</td><td>修订关于内部 4M RC 时钟精度，在 40～125℃范围内精度在±2.0%之内</td></tr><tr><td>2025.05.15</td><td>1.39</td><td>温度传感器章节增加说明</td></tr><tr><td>2025.05.13</td><td>1.38</td><td>增加关于 PVD 描述</td></tr><tr><td>2024.06.14</td><td>1.37</td><td>增加 NVR 校正值地址信息</td></tr><tr><td>2024.01.15</td><td>1.36</td><td>增加关于休眠模式的说明
增加关于 I2C 模块通讯速度的说明</td></tr><tr><td>2023.12.06</td><td>1.35</td><td>CAN 常规波特率索引值修正，计算公式修正</td></tr><tr><td>2023.09.07</td><td>1.34</td><td>修订关于 ADC TIMER 触发的说明
增加 ADC 在 3.3V 供电时必须使用 1.2V 基准的说明</td></tr><tr><td>2023.08.15</td><td>1.33</td><td>GPIO 功能框图增加 ESD 二极管</td></tr><tr><td>2023.03.18</td><td>1.32</td><td>修改时钟精度的描述</td></tr><tr><td>2023.02.28</td><td>1.31</td><td>修改 PVDSEL 的描述</td></tr><tr><td>2023.02.18</td><td>1.3</td><td>修改 MCPWM_SDCFG 的描述</td></tr><tr><td>2023.02.11</td><td>1.29</td><td>增加关于关闭 PLL 等操作的说明
增加 CAN 通讯需要使用外部晶振的描述
修改 SYS_AFE_REG5_RGPPD 的描述</td></tr><tr><td>2023.01.03</td><td>1.28</td><td>修改编码器寄存器描述</td></tr><tr><td>2022.11.07</td><td>1.27</td><td>增加 IO 与内部模拟电路间连接电阻描述</td></tr><tr><td>2022.10.29</td><td>1.26</td><td>修改 MCPWM_DTHx0/MCPWM_DTHx1 寄存器描述</td></tr><tr><td>2022.10.17</td><td>1.25</td><td>修订 DAC 校准输出公式</td></tr><tr><td>2022.09.23</td><td>1.24</td><td>修改 ADC 1.2V 基准时温度传感器使用说明</td></tr><tr><td>2022.08.18</td><td>1.23</td><td>增加 ADC/CMP 配置流程，简化 SYS_AFE_REG 部分描述</td></tr><tr><td>2022.04.08</td><td>1.22</td><td>增加 MCU 内核描述</td></tr><tr><td>2021.10.18</td><td>1.21</td><td>修订 FLASH 擦写次数的描述</td></tr><tr><td>2021.08.03</td><td>1.20</td><td>修订 CAN 模块部分描述</td></tr><tr><td>2021.06.07</td><td>1.19</td><td>修订 CAN 模块部分描述，修订 FLASH NVR 空间描述</td></tr><tr><td>2021.05.20</td><td>1.18</td><td>修订比较器 BEMFx_MID 的描述</td></tr><tr><td>2020.06.12</td><td>1.17</td><td>增加了复位源的说明，修订 UTimer ETON 的说明，SYS_AFE_CMP 修改为 SYS_AFE_INFO，增加了 PWR_WEAK 标志位的说明</td></tr><tr><td>2020.02.18</td><td>1.16</td><td>修订部分说明</td></tr><tr><td>2019.12.03</td><td>1.15</td><td>修订部分图示</td></tr><tr><td>2019.09.12</td><td>1.14</td><td>修订部分说明</td></tr><tr><td>2019.06.01</td><td>1.10</td><td>时钟部分章节修订</td></tr><tr><td>2019.03.18</td><td>1.0</td><td>针对发布的修订</td></tr><tr><td>2018.11.29</td><td>0.1</td><td>初始版本</td></tr></table>

# 免责声明

LKS和LKO为凌鸥创芯注册商标。

南京凌鸥创芯电子有限公司（以下简称：“Linko"）尽力确保本文档内容的准确和可靠，但是保留随时更改、更正、增强、修改产品和/或文档的权利，恕不另行通知。用户可在下单前获取最新相关信息。

客户应针对应用需求选择合适的Linko产品，详细设计、验证和测试您的应用，以确保满足相应标准以及任何安全、安保或其它要求。客户应对此独自承担全部责任。

Linko在此确认未以明示或暗示方式授予Linko或第三方的任何知识产权许可。

Linko产品的转售，若其条款与此处规定不同，Linko对此类产品的任何保修承诺无效。

如有更早期版本文档，一切信息以此文档为准。