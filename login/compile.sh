#!/bin/sh

SOURCE_PATH=$(
  cd $(dirname $0)
  pwd
)
QT_INSTALLED_PATH="/usr/local/Qt/5.15.2/gcc_64/lib/cmake/Qt5"
APP_INSTALL_PATH="~/app/loading"

cd ${SOURCE_PATH}
rm -rf ${SOURCE_PATH}/build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DQt5_DIR=${QT_INSTALLED_PATH} -DCMAKE_INSTALL_PREFIX=${APP_INSTALL_PATH}
cmake --build build --config Release
cmake --install build
rm -rf ${SOURCE_PATH}\build
