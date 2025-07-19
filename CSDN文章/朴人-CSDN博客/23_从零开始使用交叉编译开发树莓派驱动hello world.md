# 23 从零开始使用交叉编译开发树莓派驱动hello world

> 朴人 于 2021-04-07 12:57:18 发布 阅读量378 收藏 1 点赞数
> 文章链接：https://blog.csdn.net/qq570437459/article/details/115415695

 **【以下命令没有特别说明，都在上位机端执行】** 

### 1.交叉编译环境准备

arm设备性能低，一般不在arm板上编译东西，所以使用交叉编译。此处上位机为linux pc。

- 【kernel源码】：树莓派运行 `uname -r` 查看当前树莓派的内核版本。上位机下载对应版本的内核 `git clone git://github.com/raspberrypi/linux.git` 。

- 【compiler chain】： `git clone git://github.com/raspberrypi/tools.git` 

### 2.编写驱动

网上有很多教程说需要编译kernel源码，实测不需要，只需按照以下做即可。

2.1. 驱动源码

```c
#include <linux/init.h>
#include <linux/module.h>

static int hello_init(void)
{
        printk(KERN_ALERT"hello INIT.\n");
        return 0;
}

static void hello_exit(void)
{
        printk(KERN_ALERT"hello EXIT.\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("xx");
```

2.2. 驱动Makefile，是否使用绝对路径与环境变量有关。

```shell
ifneq ($(KERNELRELEASE),)

obj-m:=hello.o
else
KDIR := /home/xx/linux-rpi-5.10.y
PWD := $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=/home/xx/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf- -j10
endif
clean:
	rm -f *.ko *.o *.symvers  *.order  *.mod  *.mod.c  *.mod.o
.PHONY: clean
```

在写好的驱动目录中，运行 `make` ，会生成驱动文件hello.ko，将这个文件传输到树莓派中，然后树莓派运行 `sudo insmod hello.ko` 即可安装驱动，树莓派运行 `dmesg` 即可看到驱动打印出来的信息。