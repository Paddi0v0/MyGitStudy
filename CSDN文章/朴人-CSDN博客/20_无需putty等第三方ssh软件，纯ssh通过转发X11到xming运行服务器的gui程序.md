# 20 无需putty等第三方ssh软件，纯ssh通过转发X11到xming运行服务器的gui程序

> 朴人 于 2020-11-26 19:17:10 发布 阅读量1.9k 收藏 7 点赞数 4
> 文章链接：https://blog.csdn.net/qq570437459/article/details/110196551

如果本地是wsl或者win10，那么先安装并以默认设置运行 `xming` 软件。

### 【服务器端设置】

- 如果你的ssh服务器端有图形界面，那么 **无需设置** ，不要听网上其他乱七八糟的教程， `/etc/ssh/sshd_config` 中关于X11的任何选项都不要动！如果你改动了，请恢复默认。

- 如果你的ssh服务器端是server版本，很少人用server版本运行gui程序，所以自行百度给ubuntu server安装 `Xwindow` ，并检查 `/etc/ssh/sshd_config` 中设置了 `X11Forwarding yes` 。

---

### 【本地是linux平台】

依次运行：

1.  `export DISPLAY=localhost:0.0` 
   （如果不想每次都输入这个命令，要写在.bashrc(或.zshrc等)中，写在.profile不顶用。）

2.  `ssh -X hyz@192.168.xxx.xxx` 
   （或者在 `~/.ssh/config` 中的主机参数里加上 `ForwardX11 yes` ，只需加这个）

---

### 【本地是win10平台】

使用powershell或cmd，依次运行：

1.  `$env:DISPLAY='localhost:0.0'` 
   （如果不想每次都输入这个命令，就在环境变量里添加一条 `DISPLAY` ，值为 `localhost:0.0` ）

2.  `ssh -XY hyz@192.168.xxx.xxx` 
   （win10平台需要加上-XY选项，或者在.ssh/config中的主机参数里加上 `ForwardX11 yes` 和 `ForwardX11Trusted yes` ）
   *windows某些版本的ssh在设置了DISPLAY会有bug，导致ssh无法连接。

