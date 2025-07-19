# 22 【简洁清晰】使用ssh自带的反向代理功能，实现访问内网设备的任意端口，包括ssh、vnc等

> 朴人 于 2021-03-14 19:31:42 发布 阅读量2.7k 收藏 4 点赞数 1
> 文章链接：https://blog.csdn.net/qq570437459/article/details/114796519

机器A：内网设备
机器B：中转设备，用来转发，最好有公网ip
机器C：任意设备，客户端，用来访问机器A，就是你正在用的电脑
 ![内网穿透图示](./assets/22_1.png)

---

0.自行配置好[机器A>>机器B]、[机器C>>机器A]、[机器C>>机器B]的ssh密码或密钥。

---

##### 1.配置机器B：

将 `/etc/ssh/sshd_config` 中的 `GatewayPorts` 设置为 `yes` ，重启sshd `sudo systemctl restart sshd.service` 

---

##### 2.配置机器A：

机器A运行命令： `ssh -fNR [中转端口]:localhost:[机器A将被访问的端口] [机器B的ssh用户名]@[机器B的ip]` 
-f:后台运行
-N:只端口转发
-R:将机器B的指定端口转发到本地指定端口。

举例：

- 【转发ssh】
  机器A运行： `ssh -fNR 21212:localhost:22 ubuntu@36.152.44.96` 

- 【转发vnc】
  机器A运行： `ssh -fNR 23456:localhost:5900 ubuntu@36.152.44.96` 

---

##### 3.机器C的远程连接机器A：

举例：

- 【穿透ssh】
  机器C运行： `ssh [机器A的用户名]@[机器B的ip] -p [中转端口]` ,比如 `ssh pi@36.152.44.96 -p 21212` ，（机器B的安全组里的21212端口需要设置为放行)

- 【穿透vnc】
  这里使用VNC Viewer来连接，看下图：
   ![vnc viewer](./assets/22_2.png)

  ，然后输入机器A的用户密码即可。（机器B的端口同样需要设置放行）

---

##### *长时间保持反向代理：

机器A与机器B的反向代理ssh如果长时间不流动数据，ssh会自动断开。现在将其设置为长时间不断开。

- 【不推荐】方法一：
  在机器B `/etc/ssh/sshd_config` 中，设置 `ClientAliveInterval` 为60，设置 `ClientAliveCountMax` 为10，重启sshd `sudo systemctl restart sshd.service` 。
  代表机器B每60秒都会发空包，如果连续10次都没有收到回应，那么断开连接。

- 【推荐】方法二：
  机器A使用第三方软件autossh，举例： `autossh -M 1234 -fNR 21212:localhost:22 ubuntu@36.152.44.96` 
  -M:用一个端口来监听ssh是否断开，注意不要设置为21212或相邻的值

---

##### *开机自启动：

参考 [ubuntu18.04开机自启动脚本](https://blog.csdn.net/qq570437459/article/details/87094870) 。
要注意你的脚本需要后台运行，并且等待网络连接成功后再运行ssh反向代理命令，特别是wifi网络，开机后需要一定时间才能连接上（autossh不用管这条）。如果有多个端口需要反向代理，请用sleep 1等待一秒隔开。