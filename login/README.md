Qt打包安装

# 1 编译
## 1.1 windows
```bat
cd D:\MyWork\2022\QtParts\login
rd /S /Q D:\MyWork\2022\QtParts\login\build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=E:/vcpkg/scripts/buildsystems/vcpkg.cmake -Wno-dev -DQt5_DIR=E:\Qt\5.15.1\msvc2019_64 -DCMAKE_INSTALL_PREFIX=E:/test/loading
cmake --build build --config Release
cmake --install build
rd /S /Q D:\MyWork\2022\QtParts\login\build
copy /Y "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\MSVCP140.dll" "E:/test/loading"
copy /Y "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\MSVCP140_1.dll" "E:/test/loading"
copy /Y "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\vcruntime140_1.dll" "E:/test/loading"
copy /Y "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\vcruntime140.dll" "E:/test/loading"

copy /Y "C:\Windows\SysWOW64\api-ms-win-core-console-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-datetime-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-debug-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-errorhandling-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-file-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-file-l1-2-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-file-l2-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-handle-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-heap-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-interlocked-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-libraryloader-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-localization-l1-2-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-memory-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-namedpipe-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-processenvironment-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-processthreads-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-processthreads-l1-1-1.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-profile-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-rtlsupport-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-string-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-synch-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-synch-l1-2-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-sysinfo-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-timezone-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-core-util-l1-1-0.dll" "E:/test/loading"

copy /Y "C:\Windows\SysWOW64\api-ms-win-crt-convert-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-crt-environment-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-crt-filesystem-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-crt-heap-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-crt-locale-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-crt-math-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-crt-multibyte-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-crt-runtime-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-crt-stdio-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-crt-string-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-crt-time-l1-1-0.dll" "E:/test/loading"
copy /Y "C:\Windows\SysWOW64\api-ms-win-crt-utility-l1-1-0.dll" "E:/test/loading"

copy /Y "C:\Windows\SysWOW64\concrt140.dll" "E:/test/loading"
```

## 1.2 linux
```sh
cd ~/code/login
rm -rf ~/code/login/build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DQt5_DIR=/usr/local/Qt/5.15.2/gcc_64/lib/cmake/Qt5 -DCMAKE_INSTALL_PREFIX=~/app/loading
cmake --build build --config Release
cmake --install build
rm -rf ~/code/login/build
```

# 2 依赖项配置
## 2.1 windows
```sh
dumpbin /DEPENDENTS E:/test/loading/iconv-2.dll
dumpbin /DEPENDENTS E:/test/loading/intl-8.dll
dumpbin /DEPENDENTS E:/test/loading/loading.exe
dumpbin /DEPENDENTS E:/test/loading/Qt5Core.dll
dumpbin /DEPENDENTS E:/test/loading/Qt5Gui.dll
dumpbin /DEPENDENTS E:/test/loading/Qt5Widgets.dll
```
## 2.2 linux
```sh
~/app/loading/loading
#报告错误
#./loading: error while loading shared libraries: libQt5Widgets.so.5: cannot open shared object file: No such file or directory
```
查看依赖项
```sh
ldd ~/app/loading/loading
```
查看依赖项输出
```asm
linux-vdso.so.1 (0x00007fff50bae000)
	libQt5Widgets.so.5 => not found
	libQt5Gui.so.5 => not found
	libQt5Core.so.5 => not found
	libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f7079883000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f7079868000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f7079676000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f7079525000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f7079abc000)

```
### 2.2.1 临时设置LD_LIBRARY_PATH
```
export LD_LIBRARY_PATH=/usr/local/Qt/5.15.2/gcc_64/lib
```

### 2.2.2 永久保存LD_LIBRARY_PATH
/etc/environment 设置的是整个系统的环境
```bash
sudo  vim /etc/environment
```
在PATH前添加以下内容,然后保存退出
```text
LD_LIBRARY_PATH=${$LD_LIBRARY_PATH}:/usr/local/Qt/5.15.2/gcc_64/lib
```
然后重新加载环境
```bash
source  /etc/environment
```

# 3 windeployqt打包
```bash
cd D:\MyWork\2022\QtParts\login\build\Release
windeployqt D:\MyWork\2022\QtParts\login\build\Release\loading.exe
```