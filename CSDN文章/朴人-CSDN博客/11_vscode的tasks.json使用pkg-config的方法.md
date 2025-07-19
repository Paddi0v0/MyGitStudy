# 11 vscode的tasks.json使用pkg-config的方法

> 朴人 于 2020-07-12 19:17:18 发布 阅读量2.1k 收藏 3 点赞数 4
> 文章链接：https://blog.csdn.net/qq570437459/article/details/107303792

以下是在命令行中使用pkg-config的方法

```shell
g++ test.cpp  `pkg-config --cflags --libs opencv`
```

但是如果在tasks.json的编译选项中直接加入"`pkg-config --cflags --libs opencv`"会导致编译报错。

---

解决办法：
tasks.json里的编译参数要使用下面的写法

```json
"`pkg-config","--libs","--cflags","opencv`",
```