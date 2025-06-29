#include <STC89C5xRC.H>
void main()
{
    while (1)
    {
        // Code
        P0 = 0x00; // 给P0口全部写0，LED没亮，证明没有电流，也就是说数码管全部共阴极
        P01 = 1;
        P02 = 1;

    }
}

