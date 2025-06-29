#include <intrins.h>
#include <STC89C5xRC.H>
// 延时函数，基础单位1ms（适用于11.0592MHz晶振）
void Delay1ms(unsigned int ms) {
  unsigned int i, j;
  for (i = ms; i > 0; i--)
    for (j = 120; j > 0; j--)
      ; // 延时1ms的基本单位（11.0592MHz） 
}

void main() {
  while (1) {
    P20 = 0;       // LED亮
    Delay1ms(500); // 延时500msP20 = 1;       // LED灭
    Delay1ms(500); // 延时500ms for (i = 0; i < 10; i++) {   P20 = 0;       //
                   // LED亮 Delay1ms(500); // 延时500ms
    P20 = 1;       // LED灭
  }
}

