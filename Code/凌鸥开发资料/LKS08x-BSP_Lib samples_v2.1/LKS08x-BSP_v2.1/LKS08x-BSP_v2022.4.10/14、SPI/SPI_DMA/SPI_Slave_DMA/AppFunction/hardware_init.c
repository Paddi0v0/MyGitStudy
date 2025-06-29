/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� hardware_init.c
 * �ļ���ʶ��
 * ����ժҪ�� Ӳ����ʼ������
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Howlet Li
 * ������ڣ� 2015��11��5��
 *
 * �޸ļ�¼1��
 * �޸����ڣ�
 * �� �� �ţ�
 * �� �� �ˣ�
 * �޸����ݣ�
 *
 *******************************************************************************/
#include "basic.h"
#include "hardware_config.h"
#include "lks32mc08x_spi.h"

void SPI_init(void);

/*******************************************************************************
 �������ƣ�    void Hardware_init(void)
 ����������    Ӳ�����ֳ�ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();                /* �ر��ж� �ж��ܿ��� */
    SYS_WR_PROTECT = 0x7a83;        /* ʹ��ϵͳ�Ĵ���д����*/
    FLASH_CFG |= 0x00080000;        /* FLASHԤȡ����ʹ��*/
    GPIO_init();                    /* GPIO��ʼ��*/
    SPI_init();                     /* SPI��ʼ��*/
    NVIC_EnableIRQ(SPI0_IRQn);      /* ʹ��SPI�ж�*/
    NVIC_SetPriority(SPI0_IRQn, 1); /* SPI�ж����ȼ�����*/
    __enable_irq();                 /* �����ж� */
}

/*******************************************************************************
 �������ƣ�    void GPIO_init(void)
 ����������    GPIOӲ����ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    /*SPI��ʼ��*/
    GPIO_StructInit(&GPIO_InitStruct);

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //����Ϊ����ģʽ
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_1;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_3, AF5_SPI);  //GPIO2.3����SPI_CS����
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_1, AF5_SPI);  //GPIO2.1����SPI_clk����
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_10, AF5_SPI); //GPIO2.10����SPI_DI����

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //����Ϊ���ģʽ
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_0, AF5_SPI); //GPIO1.0����SPI_DO����
}

/*******************************************************************************
 �������ƣ�    void SPI_Init(void)
 ����������    SPIӲ�����ֳ�ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/8/31      V1.0           HMG               ����
 *******************************************************************************/
void SPI_init(void)
{
    SPI_InitTypeDef SPI_InitStruct;

    SYS_SFT_RST |= BIT8;  //��λSPI
    SYS_SFT_RST &= ~BIT8; //�ͷ�SPI

    SPI_StructInit(&SPI_InitStruct);              // SPI�ṹ���ʼ��
    SPI_InitStruct.Duplex = SPI_Full;             // ˫��ģʽ����
    SPI_InitStruct.Mode = SPI_Slave;              // Slave�ӻ�ģʽ
    SPI_InitStruct.EN = ENABLE;                   // ʹ��SPIģ��
    SPI_InitStruct.SS = 1;                        // Slaveģʽ�£�Ƭѡ�ź�Master
    SPI_InitStruct.DMA = SPI_DMA_ENABLE;          // ѡ��SPI���Ʒ�ʽ����DMA�������ݵ�SPI
    SPI_InitStruct.Trig = 0;                      // �ڲ��Զ���������
    SPI_InitStruct.DataOrder = SPI_FIRSTSEND_MSB; // ���ֽ��ȷ��� MSB
    SPI_InitStruct.CPHA = 0;                      // ��һ����Ϊ��������ʱ��
    SPI_InitStruct.CPOL = 1;                      // CLKĬ�ϸߵ�ƽ
    SPI_InitStruct.BaudRate = 30;                 //�����ٶ�96MHZ/(2*(30+1))= 1.548MHZ
    SPI_InitStruct.ByteLength = 0;                // ��������ֽ�
    //ʹ���жϿ��أ� ʹ�� SPI��������ж�;  ʹ�ܴ����쳣�жϣ� ʹ��������ж�
    SPI_InitStruct.IRQEna = DISABLE; //�ر�SPI���ж�
    SPI_Init(SPI, &SPI_InitStruct);  //SPI��ʼ������
	  
}

/****************************************************************************************************
 �������ƣ�    void Spi_master_DMA(UINT8 *spi_txdma_data ��UINT8 *spi_rxdma_data, u32 spi_txdma_len)
 ����������    SPI���ݷ�������պ���
 ���������    spi_txdma_data�����������ڴ��ַ
              spi_rxdma_data�����������ڴ��ַ
              spi_txdma_len : �����ֽ���
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��ʵ��SPI����Ϊȫ˫��������SPIһ�η���len���ݣ�ͬʱ��������Ҳ��len����
              ������Ҫȷ�������뷢�ͻ�������Сһ��
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/8/31      V1.0           HMG               ����
 ****************************************************************************************************/
void Spi_master_DMA(UINT8 *spi_txdma_data, UINT8 *spi_rxdma_data, u8 spi_len)
{
    SPI_SIZE = spi_len + 1;                                    //SPIһ�ַ���spi_txdma_len�ֽڡ�spi_len+1��
	                                                             //��SPI����spi_len�ֽں�ʹSPI���������״̬
    DMA_CTMS2 = (((spi_len) << 16) & 0x00ff0000) | 0x00000001; //����1�֣�ÿ��1���ֽ�
    DMA_CPAR2 = (u32)&SPI_TX_DATA;                             //SPI_TX_DATA
    DMA_CMAR2 = (u32)spi_txdma_data;                           //�ڴ��ַ

    DMA_CCR2 = 0x2091; //BIT0:ͨ��2ʹ��,BIT4�����䷽���������ڴ�,BIT7���ڴ�ڶ��ֵ�ַ�ڵ�һ���ϵ�����
                       //BIT8~BIT9 = 0b00:�������λ��byte��BIT10~BIT11 = 0b00:�ڴ����λ��byte
                       //BIT12~BIT14 = 0b010:ѡ��SPI_TX��ΪDMA_CH2�����ź�

    DMA_CTMS1 = (((spi_len) << 16) & 0x00ff0000) | 0x00000001; //����1�֣�ÿ��һ���ֽ�
    DMA_CPAR1 = (u32)&SPI_RX_DATA;                             //SPI_RX_DATA
    DMA_CMAR1 = (u32)spi_rxdma_data;                           //�ڴ��ַ

    DMA_CCR1 = 0x1081; //BIT0:ͨ��2ʹ��,BIT1:��������ж�ʹ��,BIT7���ڴ�ڶ��ֵ�ַ�ڵ�һ���ϵ���
                       //BIT8~BIT9 = 0b00:�������λ��byte��BIT10~BIT11 = 0b00:�ڴ����λ��byte
                       //BIT12~BIT14 = 0b001:ѡ��SPI_RX��ΪDMA_CH1�����ź�
	
    DMA_CTRL = 0x0001;             //DMAʹ��
	
	  if(!(SPI_IE & SPI_IF_TranDone))//SPI������ɱ�־λδ��λ
		{
		  SPI_TX_DATA = 0x00000000; //����SPI������ɱ�־λ��λ��ʹSPI_DMA���ƣ�
		}
	
		

}

/*******************************************************************************
 �������ƣ�    void Clock_Init(void)
 ����������    ʱ������
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;      /* ���ϵͳ�Ĵ���д���� */
    SYS_AFE_REG5 |= BIT15 | BIT0; /* BIT15:PLLPDN  BIT0:ADC_Clock*/
    SYS_CLK_CFG |= 0x000001ff;    /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff��Ӧ96Mʱ�� ; ��������ʱ��*/
}

/*******************************************************************************
 �������ƣ�    void SystemInit(void)
 ����������    Ӳ��ϵͳ��ʼ��������ʱ�ӳ�ʼ������
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2016/3/14      V1.0           Howlet Li          ����
 *******************************************************************************/
void SystemInit(void)
{
    Clock_Init(); /* ʱ�ӳ�ʼ�� */
}

/*******************************************************************************
 �������ƣ�    void Delay(void)
 ����������    ��ʱ����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/8/31      V1.0            HMG               ����
 *******************************************************************************/
void Delay(u32 cnt)
{
    u32 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}
