# 26 windows平台，mingw64编译环境下的socket使用

> 朴人 于 2021-07-05 14:18:01 发布 阅读量3.3k 收藏 2 点赞数 1
> 文章链接：https://blog.csdn.net/qq570437459/article/details/118488957

代码并不重要，主要看最后的编译命令：

```c
//test.cpp
#include <winsock2.h>
#include <iostream>
using namespace std;

int main()
{
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrSrv.sin_port = htons(12345);

    if (connect(s, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR)) == INVALID_SOCKET)
    {
        cout << "connect() fail" << WSAGetLastError() << endl;
        return -1;
    }
}
```

编译命令： `g++ .\test.cpp -LD:\application\mingw64\x86_64-w64-mingw32\lib -lws2_32` 
注意自行修改mingw64所在路径