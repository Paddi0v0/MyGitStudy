# 12 termux 修改自定义字体

> 朴人 已于 2022-03-09 16:34:33 修改 阅读量9.7k 收藏 4 点赞数 1
> 文章链接：https://blog.csdn.net/qq570437459/article/details/108697452

需要先安装termux styling。
termux 运行 `chfont` 可修改预设的二十几种字体，接下来的操作可以添加自己的字体。
将字体文件复制到 `~/.termux/fonts/` 里，再运行 `chfont` 就能看到自己的字体了。
实际上， `chfont` 命令运行的是 `.termux/fonts.sh` ，这个命令修改了 `.termux/font.ttf` 文件。