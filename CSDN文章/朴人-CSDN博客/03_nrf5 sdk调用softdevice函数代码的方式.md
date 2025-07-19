# 03 nrf5 sdk调用softdevice函数代码的方式

> 朴人 于 2018-12-19 20:28:29 发布 阅读量802 收藏 3 点赞数
> 文章链接：https://blog.csdn.net/qq570437459/article/details/85107670

刚开始用nrf5 sdk的时候，好奇app程序是如何调用softdevice函数的。工程里没有静态库，也没有源代码，只有一个hex。

跟着ble的函数走下去，发现走到了一个SVCALL函数就走不下去了，再往下走就是softdevice真正的函数了，可惜nordic将其直接做成了hex，看不到源码，也无法追踪。

## SVCALL使用了arm的svc指令，经过以下几步，就实现了调用softdevice函数。

1. 手动发起svc中断，并将ble相关函数代号放在cpu寄存器r0里面

2. svc中断处理函数由softdevice实现，我们也是看不到的，中断发起后，由中断向量表带着cpu的pc寄存器走到了flash中的svc处理函数地址，在svc处理函数中解析函数代号，并跳转到对应函数执行，比如使用以下的逻辑：

```c
//这段程序位于softdevice的hex里，在此只是演示一下逻辑
if (number == 0x10)//这个0x10是在我们的app程序里约定好的，大家可以自己去找
	ble_enable();
```