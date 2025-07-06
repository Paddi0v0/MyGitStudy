echo off
cd ../..
del buildall.log
for /f "delims=" %%i in ('dir /b /s "*.uvprojx"')do (
@REM rd /s/q "%%~i"
@REM xcopy %periph_driver1% "%%~i\" /e /q
C:\Keil_v5\UV4\UV4.exe -j10 -b %%~i -l tmp.txt
echo %%~i
echo %%~i >> buildall.log
type tmp.txt >> buildall.log
del tmp.txt
)
exit
