# 25 windows平台，mingw64编译使用matplotlibcpp

> 朴人 于 2021-07-05 13:44:38 发布 阅读量429 收藏 点赞数
> 文章链接：https://blog.csdn.net/qq570437459/article/details/118488221

编译以下代码：

```c
//test.cpp
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
int main() {
    plt::plot({1,3,2,4});
    plt::show();
}
```

编译命令： `g++ test.cpp -DWITHOUT_NUMPY -ID:\application\miniconda3\include -LD:\application\miniconda3 -lpython38` 
注意自行更改python所在的路径和python版本，-lpython38不可写做-lpython3。