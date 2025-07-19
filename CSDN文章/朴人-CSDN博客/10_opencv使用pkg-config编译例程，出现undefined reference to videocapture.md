# 10 opencv使用pkg-config编译例程，出现undefined reference to videocapture

> 朴人 于 2020-07-07 19:46:48 发布 阅读量464 收藏 点赞数
> 文章链接：https://blog.csdn.net/qq570437459/article/details/107188810

主要有三个需要注意的：
1.g++ facedetect.cpp -o my.out `pkg-config --cflags --libs opencv`
这里不是单引号啊！是键盘左上角那个一撇。

2.g++ facedetect.cpp -o my.out `pkg-config --cflags --libs opencv`
如果你是opencv4.0+ 这里改做pkg-config --cflags --libs opencv4

3.g++ facedetect.cpp -o my.out `pkg-config --cflags --libs opencv`
pkg-config --cflags --libs opencv这个东西要写在最后面，比如以下就是错误示范

g++ `pkg-config --cflags --libs opencv` facedetect.cpp -o my.out