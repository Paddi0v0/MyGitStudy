#include "hardware_init.h"
#include "mygpio_init.h"

int main(void)
{
    Hardware_init(); /* Ӳ����ʼ��*/
    while (1)
    {
        Led_12off();
        Led_3off();
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR
 * **********************/
/* ------------------------------END OF FILE------------------------------------
 */
