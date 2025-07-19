# 24 linux平台的三种动态库路径设置方法

> 朴人 于 2021-05-18 15:11:06 发布 阅读量4.9k 收藏 24 点赞数 3
> 文章链接：https://blog.csdn.net/qq570437459/article/details/116989315

### 方法一： **LD_LIBRARY_PATH** 

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/your/path
```

---

建议在 `~/.profile` 最后增加一行，写入上述命令。

### 方法二： **/etc/ld.so.conf** 

用sudo权限在 `/etc/ld.so.conf` 文件最后新增一行动态库路径，比如写入 `/usr/local/lib` 。然后命令行运行 `sudo ldconfig` 。

---

### 方法三：gcc添加编译选项

```
-Wl,-rpath=/your/path:/your/path2
```

比如

```
gcc main.c -L/your/path:/your/path2 -lmylib -Wl,-rpath=/your/path:/your/path2
```

`-Wl` (warn linker)表示后面的参数会传给链接器。 `-rpath` (run path)表示运行时动态库所在目录（注意区别，-L是编译时动态库所在目录）。