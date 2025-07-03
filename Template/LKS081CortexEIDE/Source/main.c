#include "lks32mc08x_lib.h"
#include "mygpio_init.h"

int main(void)
{
    Hardware_init(); /* Ó²¼þ³õÊ¼»¯*/
    while (1)
    {
        Led_12on();
        Led_3on();
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR
 * **********************/
/* ------------------------------END OF FILE------------------------------------
 */
