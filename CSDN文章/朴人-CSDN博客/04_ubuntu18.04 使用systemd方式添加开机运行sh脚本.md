# 04 ubuntu18.04 使用systemd方式添加开机运行sh脚本

> 朴人 于 2019-02-12 16:02:12 发布 阅读量2w 收藏 49 点赞数 4
> 文章链接：https://blog.csdn.net/qq570437459/article/details/87094870

ubuntu18.04压根就没有rc.local，而且很多发行版都推荐使用systemd而不是initd了。

### 1.准备好你的sh脚本文件

内容略过，就假设路径是 `/usr/local/my/my.sh` 吧。别忘了chmod +x。

### 2.创建一个service文件

进入 `/etc/systemd/system/` ，创建一个 `my.service` 文件，内容如下：

```
[Unit]
Description=just for test                    这里填简介
After=BBB.service　XXX.service  AAA.service   这里填上你这个脚本所需要的前置service，都在/etc/systemd/system/下

[Service]
ExecStart=/usr/local/my/my.sh                  这里填sh文件路径，比如这里运行了这个my.sh，后面也可以跟参数，比如 -D -I                                                                                                                                  

[Install]
WantedBy=multi-user.target

```

### 3.完事

使用以下命令使能这个服务开机启动：

```shell
# 重新加载配置文件
$ sudo systemctl daemon-reload              service文件改动后要重新转载一下
$ sudo systemctl enable my.service          这句是为了设置开机启动
```

如果你想不重启立刻使用这个sh脚本，就运行下面这句：

```shell
# 重启相关服务
$ sudo systemctl start my.service           启动服务
```

---

关于service文件里的一些选项，在

>  [http://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-part-two.html](http://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-part-two.html) 

里有详细的说明。