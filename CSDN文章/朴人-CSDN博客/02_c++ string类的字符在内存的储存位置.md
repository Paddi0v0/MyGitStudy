# 02 c++ string类的字符在内存的储存位置

> 朴人 于 2018-11-29 11:19:21 发布 阅读量3.5k 收藏 9 点赞数 4
> 文章链接：https://blog.csdn.net/qq570437459/article/details/84620899

以下数据均在ubuntu 64位系统，g++ c++11情况下测试

## 1. 数据<=16字节，在当前栈区

```c
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int main()
{
	string temp = "123456789012345";	//注意长度
	int *a = (int *)malloc(sizeof(int));
	int b = 0;
	for(auto &c:temp)
	{
		printf("c%p\n", &c);
	}
	printf("a%p\n", a);
	printf("b%p\n", &b);
}
/*
c0x7ffdb1c5b060		//地址与&b相近，位于栈区
c0x7ffdb1c5b061
c0x7ffdb1c5b062
c0x7ffdb1c5b063
c0x7ffdb1c5b064
c0x7ffdb1c5b065
c0x7ffdb1c5b066
c0x7ffdb1c5b067
c0x7ffdb1c5b068
c0x7ffdb1c5b069
c0x7ffdb1c5b06a
c0x7ffdb1c5b06b
c0x7ffdb1c5b06c
c0x7ffdb1c5b06d
c0x7ffdb1c5b06e
a0x12c3c20
b0x7ffdb1c5b01c
*/
```

## 2. 数据>16字节，在堆区

```c
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int main()
{
	string temp = "1234567890123456";    //注意长度
	int *a = (int *)malloc(sizeof(int));
	int b = 0;
	for(auto &c:temp)
	{
		printf("c%p\n", &c);
	}
	printf("a%p\n", a);
	printf("b%p\n", &b);
}
/*
c0xe86c20		//地址与a相近，位于堆区
c0xe86c21
c0xe86c22
c0xe86c23
c0xe86c24
c0xe86c25
c0xe86c26
c0xe86c27
c0xe86c28
c0xe86c29
c0xe86c2a
c0xe86c2b
c0xe86c2c
c0xe86c2d
c0xe86c2e
c0xe86c2f
a0xe86c40
b0x7ffe59e72fcc
*/
```