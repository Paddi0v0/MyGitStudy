pymake.ini 中选择需要编译的工程名
并保证同名的 .code 和 .data 文件存在在同一目录下
然后运行LKS08x_DSP_Emulator.exe

程序运行结束后会在output文件夹下输出一些运行日志
gpr_trace是DSP程序运行过程各个周期的GPR值
inst_trace是DSP程序运行过程中各个周期执行的指令

invalid_test 和 test 是两个示例工程
具体DSP使用，请参考《LKS32MC08x_User_Manual.pdf》