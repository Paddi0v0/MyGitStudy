@echo off
rem 递归更新所有例程的库函数
rem 需要最新的库函数放在update_periph_driver里

set periph_driver=%~dp0
set periph_driver1="%periph_driver%update_periph_driver"
cd ../..
for /f "delims=" %%i in ('dir /s/b/ad lks32mc08x_periph_driver') do (
rd /s/q "%%~i"
xcopy %periph_driver1% "%%~i\" /e /q
)
exit
