# 21 Windows使用mingw64编译安装opencv

> 朴人 于 2020-12-06 16:28:50 发布 阅读量979 收藏 1 点赞数 2
> 文章链接：https://blog.csdn.net/qq570437459/article/details/110739803



1.  **准备（自行准备）** 
   1.1. opencv源码
   1.2. mingw64
   1.3. cmake

2.  **编译** 
   2.1. 生成makefile
   在opencv源码目录新建build文件夹，进入build文件夹，powershell运行
    `cmake -G "MinGW Makefiles" -D CMAKE_INSTALL_PREFIX=D:/选择你想要安装到的路径 -D OPENCV_ALLOCATOR_STATS_COUNTER_TYPE=int64_t ..` 
   命令解释：生成mingw格式的makfile，指定opencv安装目录，其中 `-D OPENCV_ALLOCATOR_STATS_COUNTER_TYPE=int64_t` 为一个坑，目前使用mingw64+opencv编译需要加上此选项。
   2.2. 编译
   运行 `mingw32-make.exe -j7` 。其中mingw32-make是mingw64的一部分，其中的32并不是32位编译，是win32的意思。

3.  **安装** 
   运行 `mingw32-make.exe install` 

---

以下是我在windows上用mingw64编译opencv4.5.0完成的编译结果。自行设置环境变量后可直接使用，无需自己编译。
[静态库合集opencv_world.dll.a](https://download.csdn.net/download/qq570437459/13457927) 

[动态库合集opencv_world.dll](https://download.csdn.net/download/qq570437459/13457914) 

[按照本文步骤生成的编译文件大合集，包含动态库合集、静态库合集、零散组件动态库、零散组件静态库等等。](https://download.csdn.net/download/qq570437459/13457932) 