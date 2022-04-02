set SOURCE_PATH=%~dp0
set VCPKG_INSTALLED_PATH="E:/vcpkg"
set QT_INSTALLED_PATH="E:/Qt/5.15.1/msvc2019_64"
set APP_INSTALL_PATH="E:/test/loading"
set VC_INSTALL_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional"
set WIN_SYS="C:\Windows\SysWOW64"

rd /S /Q %APP_INSTALL_PATH%
rd /S /Q %SOURCE_PATH%\build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=%VCPKG_INSTALLED_PATH%/scripts/buildsystems/vcpkg.cmake -Wno-dev -DQt5_DIR=%QT_INSTALLED_PATH% -DCMAKE_INSTALL_PREFIX=%APP_INSTALL_PATH%
cmake --build build --config Release
cmake --install build
rd /S /Q %SOURCE_PATH%\build

copy /Y "%VC_INSTALL_PATH%\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\MSVCP140.dll" %APP_INSTALL_PATH%
copy /Y "%VC_INSTALL_PATH%\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\MSVCP140_1.dll" %APP_INSTALL_PATH%
copy /Y "%VC_INSTALL_PATH%\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\vcruntime140_1.dll" %APP_INSTALL_PATH%
copy /Y "%VC_INSTALL_PATH%\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\vcruntime140.dll" %APP_INSTALL_PATH%

copy /Y "%WIN_SYS%\api-ms-win-crt-convert-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-crt-environment-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-crt-filesystem-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-crt-heap-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-crt-locale-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-crt-math-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-crt-multibyte-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-crt-runtime-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-crt-stdio-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-crt-string-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-crt-time-l1-1-0.dll" "E:/test/loading"
copy /Y "%WIN_SYS%\api-ms-win-crt-utility-l1-1-0.dll" "E:/test/loading"