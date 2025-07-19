# 08 关于在conda环境下，pip已安装好包，但是python import错误的解决方法

> 朴人 于 2020-04-23 13:43:51 发布 阅读量6.1k 收藏 9 点赞数 2
> 文章链接：https://blog.csdn.net/qq570437459/article/details/105705870

## 1.pip uninstall [那个包]

## 2.conda install [那个包]

## 或者

## 复制系统python目录下的Lib->site-packages文件夹覆盖conda虚拟环境下的对应文件夹

---

###### 原因： pip为系统的pip，可通过 `pip -V` 查看pip的路径，如果不是当前conda环境的pip，可使用python -m pip代替pip来使用conda环境中的pip。

