/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_dsp.c\n
 * 文件标识： 无 \n
 * 内容摘要： DSP驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2015年11月5日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 *@par 修改日志:DSP调用函数内增加中断打断重新复位DSP功能
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月18日 <td>2.0     <td>Zhu Jie   <td>修改
 * </table>
 */

#include "lks32mc08x_dsp.h"

/**
 *@brief @b 函数名称:   void DSP_Cmd(FuncState state)
 *@brief @b 功能描述:   DSP使能和关闭
 *@see被引用内容：       SYS_ModuleClockCmd()
 *@param输入参数：       state：ENABLE：使能 ， DISABLE:失能
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
            DSP_Cmd(ENABLE);//使能DSP时钟
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie          <td>创建
 * </table>
 */
void DSP_Cmd(FuncState state)
{
    SYS_ModuleClockCmd(SYS_Module_DSP, state); /* DSP时钟使能 */
}

/**
 *@brief @b 函数名称:   void DSP_CalcDivision(stru_DiviComponents * stru_Divi)
 *@brief @b 功能描述:   DSP使能和关闭
 *@see被引用内容：       stru_DiviComponents ，SYS_SoftResetModule()
 *@param输入参数：       .nDID,被除数   .nDIS除数
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：
                        1、除法10个总线周期完成 \n
                        2、被除数Dividend为32位大小，即范围是 -(2^31 - 1) ~ (2^31 - 1) \n
                        3、除数Divisor为16位大小，即范围是 -(2^15 - 1) ~ (2^15 - 1) \n
                        4、被除数不支持赋值为-2^31，除数不支持赋值为-2^15 \n
                        5、商Quotient为32位大小 \n
                        6、余数Remainder为16位大小
 *@warning              无
 *@par 示例代码：
 *@code
            stru_DiviComponents DiviData; //定义除法函数计算结构体变量
            DiviData.Dividend = 100;//被除数赋值
            DiviData.Divisor = 10;  //除数赋值
            DSP_CalcDivision(&DiviData);
            除法的商储存位置：DiviData.Quotient
            除法的余数储存位置：DiviData.Remainder
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年5月25日 <td>1.0         <td>cfwu          <td>创建
 * </table>
 *@par 修改日志:使用结构体变量，增加防止DSP计算被打断逻辑语句
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月18日 <td>2.0     <td>Zhu Jie          <td>修改
 * </table>
 */

void DSP_CalcDivision(stru_DiviComponents *stru_Divi)
{
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_DID = stru_Divi->Dividend; /* 被除数寄存器赋值 */
    DSP_DIS = stru_Divi->Divisor;  /* 除数寄存器赋值   */

    stru_Divi->Quotient = DSP_QUO;  /* 取出商寄存器值 */
    stru_Divi->Remainder = DSP_REM; /* 取出余数寄存器值 */
    __set_PRIMASK(flg);
}

/**
 *@brief @b 函数名称:   void DSP_CalcCordic(stru_CordicComponents *Cordic, Arc_or_SinCFuction choise)
 *@brief @b 功能描述:   DSP三角运算
 *@see被引用内容：       stru_CordicComponents ，Arc_or_SinCFuction ，SYS_SoftResetModule()
 *@param输入参数：       Cordic：角度或坐标X和Y，choise：计算模式选择 0 Arctan;1 sin/cos
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：
                        1、开方8个总线周期完成 \n
 *                      2、Theta(角度)为16位有符号定点数，表示范围 (-(32768) ~ 32767 ) 对应(-(π) ~ π) \n
 *                      3、SinValue值为16位有符号定点数，其中 1bit 符号位，15bit小数位；表示范围(-(1) ~ 1)  \n
 *                      4、CosValue值为16位有符号定点数，其中 1bit 符号位，15bit小数位；表示范围(-(1) ~ 1 ) \n
 *                      5、ArctanX值为16位有符号定点数，Q15 格式，其中 1bit 符号位，15bit整数位，表示范围(-(32768)~32767) \n
 *                      6、ArctanY值为16位有符号定点数，Q15 格式，其中 1bit 符号位，15bit整数位，表示范围(-(32768)~32767) \n
 *                      7、ArctanValue值为16位有符号定点数，表示范围 (-(32768) ~ 32767)对应(-(π) ~ π)
 *@warning              无
 *@par 示例代码：
 *@code
 *           stru_CordicComponents CordicData;// 定义三角函数计算结构体变量
 *       示例1：
 *           CordicData.ArctanX = 100; //坐标X赋值  取值范围(-(32768)~32767)
 *           CordicData.ArctanY = 10;  //坐标Y赋值  取值范围(-(32768)~32767)
 *			 DSP_CalcDivision(&CordicData,ARCTAN);
 *           arctan储存位置： CordicData.ArctanValue （输出范围-(32768) ~ 32767对应(-(π) ~ π)）
 *       示例2：
 *           CordicData.Theta = 0;      //角度赋值  取值范围(-(32768) ~ 32767) 对应(-(π) ~ π)
 *			 DSP_CalcDivision(&CordicData,SINCOS);
 *           sin结果储存位置： CordicData.SinValue   （输出范围-(32768) ~ 32767对应(-(1) ~ 1)）
 *           cos结果储存位置： CordicData.CosValue   （输出范围-(32768) ~ 32767对应(-(1) ~ 1)）
 *
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年5月25日 <td>1.0         <td>cfwu          <td>创建
 * </table>
 *@par 修改日志:使用结构体变量，增加防止DSP计算被打断逻辑语句
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月18日 <td>2.0     <td>Zhu Jie          <td>修改
 * </table>
 */
void DSP_CalcCordic(stru_CordicComponents *Cordic, Arc_or_SinCFuction choise)
{
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    if (choise) /* Sin Cos 值计算*/
    {
        DSP_SC = BIT2 | BIT1;                    /* 计算模式选择 Sin和Cos */
        DSP_CORDIC_THETA = Cordic->Theta;  /* 角度寄存器赋值 */
        Cordic->SinValue = DSP_CORDIC_SIN; /* 取出sin寄存器值 */
        Cordic->CosValue = DSP_CORDIC_COS; /* 取出cos寄存器值 */
    }
    else /* Arctan 值计算*/
    {
        DSP_SC = BIT1;                       /* 计算模式选择 Arctan */
        DSP_CORDIC_X = Cordic->ArctanX;          /* 坐标X寄存器赋值 */
        DSP_CORDIC_Y = Cordic->ArctanY;          /* 坐标Y寄存器赋值 */
        Cordic->ArctanValue = DSP_CORDIC_ARCTAN; /* 取出arctan寄存器值 */
    }
    __set_PRIMASK(flg);
}

/**
 *@brief @b 函数名称:   s16 DSP_CalcSprt(s16 X,s16 Y)
 *@brief @b 功能描述:   DSP两个数平方后开方运算
 *@see被引用内容：       无
 *@param输入参数：       X和Y
 *@param输出参数：       无
 *@return返 回 值：      sqrt(X^2+Y^2)结果值
 *@note其它说明：
                        1、开方8个总线周期完成
                        2、X值为16位有符号定点数，Q15 格式，其中 1bit 符号位，15bit整数位，表示范围(-(32768)~32767) \n
                        3、Y值为16位有符号定点数，Q15 格式，其中 1bit 符号位，15bit整数位，表示范围(-(32768)~32767) \n
                        4、输出结果sqrt(X^2+Y^2)：为16位有符号定点数，其中1bit符号位，15bit整数位，表示范围(-(32768) ~ 32767)
 *@warning              无
 *@par 示例代码：
 *@code
            s16 DSP_Value = 0;
            DSP_Value = DSP_CalcSprt(50,100);//sqrt(50^2+100^2) 50的平方加100的平方后开根号
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年5月25日 <td>1.0         <td>cfwu          <td>创建
 * </table>
 *@par 修改日志:使用结构体变量，增加防止DSP计算被打断逻辑语句
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月18日 <td>2.0     <td>Zhu Jie          <td>修改
 * </table>
 */
static volatile u8 dsp_flg1; /**< 标志位，用于判断程序是否被打断*/
s16 DSP_CalcSprt(s16 X, s16 Y)
{
    s16 dsp_mod;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_SC = BIT1;
    DSP_CORDIC_X = X;
    DSP_CORDIC_Y = Y;
    dsp_mod = DSP_CORDIC_MOD;
    __set_PRIMASK(flg);
    return dsp_mod;
}

/**
 *@brief @b 函数名称:   uint32_t DSP_GetSqrt(uint32_t Data)
 *@brief @b 功能描述:   DSP开平方函数
 *@see被引用内容：       无
 *@param输入参数：       被开方数
 *@param输出参数：       无
 *@return返 回 值：      开方根
 *@note其它说明：
                        1、开方8个总线周期完成 \n
                        2、被开方数Data为32位无符号数，即范围是(0 ~ (2^31)) \n
                        3、开方根sqrt(Data)为16位无符号数，即范围是(0 ~ (2^15)) \n
 *@warning              无
 *@par 示例代码：
 *@code
            u16 GetSqrt_Value = 0;
            GetSqrt_Value = DSP_GetSqrt(100);//sqrt(100) 100开根号结果为10
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年5月25日 <td>1.0         <td>cfwu          <td>创建
 * </table>
 *@par 修改日志:使用结构体变量，增加防止DSP计算被打断逻辑语句
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月18日 <td>2.0     <td>Zhu Jie          <td>修改
 * </table>
 */
uint32_t DSP_GetSqrt(uint32_t Data)
{
    uint32_t tdsp_sqrt;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_RAD = Data; /*被开方寄存器赋值*/
    tdsp_sqrt = DSP_SQRT;
    __set_PRIMASK(flg);
    return tdsp_sqrt;
}

void DSP_Init(void)
{
    SYS_ModuleClockCmd(SYS_Module_DSP, ENABLE); /* DSP时钟使能*/
}
s16 DSP_arctan(s16 x, s16 y)
{
    s16 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_SC = BIT1;              /* 计算模式选择 Arctan */
    DSP_CORDIC_X = x;           /* 坐标X寄存器赋值 */
    DSP_CORDIC_Y = y;           /* 坐标Y寄存器赋值 */
    answer = DSP_CORDIC_ARCTAN; /* 取出arctan寄存器值 */
    __set_PRIMASK(flg);
    return answer;
}
s32 DSP_div(s32 a, s32 b)
{
    s32 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_DID = a;
    DSP_DIS = b;
    answer = DSP_QUO;
    __set_PRIMASK(flg);
    return answer;
}
s16 DSP_sin(u16 angle)
{
    s16 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_SC = BIT2 | BIT1;
    DSP_THETA = angle;
    answer = DSP_SIN;
    __set_PRIMASK(flg);
    return answer;
}
s16 DSP_cos(u16 angle)
{
    s16 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_SC = BIT2 | BIT1;
    DSP_THETA = angle;
    answer = DSP_COS;
    __set_PRIMASK(flg);
    return answer;
}
u16 DSP_rms(s16 a, s16 b)
{
    u16 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_DID = a;
    DSP_DIS = b;
    answer = DSP_REM;
    __set_PRIMASK(flg);
    return answer;
}
s16 DSP_mod(s32 x, s16 y)
{
    s16 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_SC = BIT1;              /* 计算模式选择 Arctan */
    DSP_X = x;
    DSP_Y = y;
    answer = DSP_MOD;
    __set_PRIMASK(flg);
    return answer;
}
u16 DSP_sqrt(u32 val)
{
    u16 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_RAD = val;
    answer = DSP_SQRT;
    __set_PRIMASK(flg);
    return answer;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
