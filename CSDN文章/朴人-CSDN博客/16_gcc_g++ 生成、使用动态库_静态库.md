# 16 gcc/g++ 生成、使用动态库/静态库

> 朴人 已于 2023-10-28 09:16:45 修改 阅读量1k 收藏 4 点赞数 2
> 文章链接：https://blog.csdn.net/qq570437459/article/details/109002571

## 生成动态库：

> ###### gcc -shared my.c -o libmy.so

有时候会报错提示加上 `-fPIC` (-flag position-independent code，为了生成位置无关代码，用全局偏移的方式，一份动态库即可给多份主程序使用，细节自己网上查吧)，加上就行了。
`libmy.so` 文件注意lib前缀和.so后缀。动态库命名格式是规定好的，细节自己网上查。

---

## 使用动态库：

> ###### gcc main.c -L.  -lmy

【 `-L` 】编译时动态库所在的目录。 `.` 代表当前目录

【 `-l` 】读音是[矮欧lib]，不是[矮include]。意思是指定动态库名字。这里动态库名字是 `libmy.so` ，所以使用 `-lmy` 。

使用动态库还需要设置动态库路径： [动态库路径的设置方法](https://blog.csdn.net/qq570437459/article/details/116989315) 。

---

## 生成静态库：

> ###### gcc -c static.c -o static.o

###### ar r libstatic.a static.o

【 `-c` 】表示只编译出.o二进制文件，不进行链接

`libstatic.a` 同样要注意命名格式。

【 `ar` 】(archive)将.o文件都打包存到.a静态库中。参数 `r` (replacement)表示将.o文件覆盖添加到静态库中。

---

## 使用静态库：

> ###### gcc main.c -L. -lstatic

用法同动态库。