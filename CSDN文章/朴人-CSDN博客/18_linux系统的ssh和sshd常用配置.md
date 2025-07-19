# 18 linux系统的ssh和sshd常用配置

> 朴人 于 2020-11-05 20:26:20 发布 阅读量365 收藏 点赞数
> 文章链接：https://blog.csdn.net/qq570437459/article/details/109519537

由于本人记性极差，每次配置新系统的ssh都要去网上查，特此记录，方便以后查阅。

#### 服务器：

-  **生成一对ssh密钥命令** ： `ssh-keygen` 。

-  **添加客户端的公钥** ：

1. 手动添加。服务器打开(没有此文件则新建)，将客户端的 `~/.ssh/id_rsa.pub` (没有则在客户端运行 `ssh-keygen` 新建)里的内容添加到服务器端的 `~/.ssh/authorized_keys` 文件里(没有这个文件则新建)。注意 `authorized_keys` 里每个公钥之间都要空一行，最后一行必须是空行。

2. 自动添加。客户端运行 `ssh-copy-id -i ~/.ssh/id_rsa.pub user_name@192.168.xxx.xxx` (user_name@192.168.xxx.xxx为服务器的用户名和ip地址)。

-  **安装sshd服务** ： `sudo apt-get install openssh-server` 。

-  **重启sshd服务** ： `sudo service ssh restart` 。

-  **设置sshd密钥登录和密码登录** ：配置 `/etc/ssh/sshd_config` 里 `PubkeyAuthentication yes` 和 `PasswordAuthentication yes` 。

---

#### 客户端：

-  **生成一对ssh密钥命令** ： `ssh-keygen` 。

-  **连接服务器** ： `ssh username@192.168.xxx.xxx` (user_name@192.168.xxx.xxx为服务器的用户名和ip地址)。

-  **将公钥添加到服务器** ：见上面服务器端使用方法。

-  **服务器别名** ：~/.ssh/config的书写规则

> 

- Host tencent
>   Hostname 192.168.xxx.xxx
>   User ubuntu
>   IdentityFile ~/.ssh/tencent_priv

