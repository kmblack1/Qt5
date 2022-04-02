set SOURCE_PATH=%~dp0
set VCPKG_INSTALLED_PATH=E:\vcpkg
set QT_INSTALLED_PATH=E:\Qt\5.15.1\msvc2019_64
set APP_INSTALL_PATH=E:\test\loading
set VC_INSTALL_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional
set WIN_SYS=C:\Windows\SysWOW64

rd /S /Q %APP_INSTALL_PATH%
rd /S /Q %SOURCE_PATH%build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=%VCPKG_INSTALLED_PATH%\scripts\buildsystems\vcpkg.cmake -Wno-dev -DQt5_DIR=%QT_INSTALLED_PATH% -DCMAKE_INSTALL_PREFIX=%APP_INSTALL_PATH%
cmake --build build --config Release
cmake --install build
rd /S /Q %SOURCE_PATH%build

rem msvc runtime 14依赖的dll开始.无需安装vcruntime
copy /Y "%VC_INSTALL_PATH%\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\MSVCP140.dll" "%APP_INSTALL_PATH%"
copy /Y "%VC_INSTALL_PATH%\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\MSVCP140_1.dll" "%APP_INSTALL_PATH%"
copy /Y "%VC_INSTALL_PATH%\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\vcruntime140_1.dll" "%APP_INSTALL_PATH%"
copy /Y "%VC_INSTALL_PATH%\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\vcruntime140.dll" "%APP_INSTALL_PATH%"

copy /Y "%WIN_SYS%\api-ms-win-core-console-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-datetime-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-debug-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-errorhandling-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-file-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-file-l1-2-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-file-l2-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-handle-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-heap-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-interlocked-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-libraryloader-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-localization-l1-2-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-memory-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-namedpipe-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-processenvironment-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-processthreads-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-processthreads-l1-1-1.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-profile-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-rtlsupport-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-string-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-synch-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-synch-l1-2-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-sysinfo-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-timezone-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-core-util-l1-1-0.dll" "E:/test/loading"

copy /Y "%WIN_SYS%\api-ms-win-crt-convert-l1-1-0.dll" "%APP_INSTALL_PATH%"
copy /Y "%WIN_SYS%\api-ms-win-crt-environment-l1-1-0.dll" "%APP_INSTALL_PATH%"
copy /Y "%WIN_SYS%\api-ms-win-crt-filesystem-l1-1-0.dll" "%APP_INSTALL_PATH%"
copy /Y "%WIN_SYS%\api-ms-win-crt-heap-l1-1-0.dll" "%APP_INSTALL_PATH%"
copy /Y "%WIN_SYS%\api-ms-win-crt-locale-l1-1-0.dll" "%APP_INSTALL_PATH%"
copy /Y "%WIN_SYS%\api-ms-win-crt-math-l1-1-0.dll" "%APP_INSTALL_PATH%"
copy /Y "%WIN_SYS%\api-ms-win-crt-multibyte-l1-1-0.dll" "%APP_INSTALL_PATH%"
copy /Y "%WIN_SYS%\api-ms-win-crt-runtime-l1-1-0.dll" "%APP_INSTALL_PATH%"
copy /Y "%WIN_SYS%\api-ms-win-crt-stdio-l1-1-0.dll" "%APP_INSTALL_PATH%"
copy /Y "%WIN_SYS%\api-ms-win-crt-string-l1-1-0.dll" "%APP_INSTALL_PATH%"
copy /Y "%WIN_SYS%\api-ms-win-crt-time-l1-1-0.dll" "%APP_INSTALL_PATH%"
copy /Y "%WIN_SYS%\api-ms-win-crt-utility-l1-1-0.dll" "%APP_INSTALL_PATH%"

copy /Y "%WIN_SYS%\concrt140.dll" "%APP_INSTALL_PATH%"
rem msvc runtime 14依赖的dll结束