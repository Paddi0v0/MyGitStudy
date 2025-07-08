SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\Windows\System32;C:\Users\Administrator\AppData\Local\Microsoft\WindowsApps;C:\Program Files\JetBrains\CLion 2025.1.1\bin;C:\Stm32Bin\ninja-win;C:\Stm32Bin\clangd-windows-20.1.0\bin;C:\Stm32Bin\cmake-4.0.1-windows-x86_64\bin;C:\Stm32Bin\arm-gnu-toolchain-14.2.rel1-mingw-w64-x86_64-arm-none-eabi\bin;C:\Stm32Bin\mingw64\bin;C:\Stm32Bin\llvm\bin;C:\Users\Administrator\AppData\Local\GitHubDesktop\bin;C:\Stm32Bin\openocd\bin;C:\Program Files (x86)\SEGGER\JLink;C:\Windows\System32;C:\Program Files\Git\bin;
SET ARMCC5_ASMOPT=--diag_suppress=9931
SET ARMCC5_CCOPT=--diag_suppress=9931
SET ARMCC5_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=LKS32MC087M6S8
SET CPU_VENDOR=Linko
SET UV2_TARGET=LK_StdPeriph_GPIO
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hardware_init.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\interrupt.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_adc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_can.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_cmp.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_dac.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_dma.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_dsp.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_exti.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_flash.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_hall.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_i2c.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_iwdg.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_mcpwm.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_opa.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_spi.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_sys.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_tim.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_uart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lks32mc08x_tmp.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_lks32mc08x._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\LK_StdPeriph_GPIO.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\LK_StdPeriph_GPIO.axf" --i32combined --output ".\Objects\LK_StdPeriph_GPIO.hex"
