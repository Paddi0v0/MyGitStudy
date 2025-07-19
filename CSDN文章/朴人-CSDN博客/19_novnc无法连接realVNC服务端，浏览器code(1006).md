# 19 novnc无法连接realVNC服务端，浏览器code(1006)

> 朴人 于 2020-11-09 16:42:38 发布 阅读量2.8k 收藏 3 点赞数 1
> 文章链接：https://blog.csdn.net/qq570437459/article/details/109580803

解决方法：
用超级权限进入realVNC的Options，将“Unix password”改为“VNC password”，然后重启电脑。

感谢 [https://github.com/novnc/noVNC/issues/1438](https://github.com/novnc/noVNC/issues/1438) 