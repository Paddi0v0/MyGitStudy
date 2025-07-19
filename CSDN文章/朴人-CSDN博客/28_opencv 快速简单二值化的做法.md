# 28 opencv 快速简单二值化的做法

> 朴人 于 2022-03-06 16:34:40 发布 阅读量3.1k 收藏 点赞数 1
> 文章链接：https://blog.csdn.net/qq570437459/article/details/123312502

大家在网上搜索opencv二进制，很多人会告诉你用threshold等函数。这类函数虽然支持自适应等功能，但是参数比较多，有点复杂。
我们只要简单二值化的时候可以用以下做法：

```cpp
Mat img = imread("a.png", IMREAD_GRAYSCALE)<100;
```

 ![在这里插入图片描述](./assets/28_1.png)

 ![在这里插入图片描述](./assets/28_2.png)

