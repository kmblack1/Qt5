cmake_minimum_required(VERSION 3.11)

#cmake 集成vcpkg(需要在project前增加)

IF (NOT DEFINED ENV{Qt5_DIR})
    IF (WIN64)
        SET(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake -Wno-dev")
    ENDIF ()
ENDIF ()
#如果是在clion中编译，需要打开file->settings->Build,Execution,Deployment->Cmake
#在Toolchain中选择Visual Studio
#在Cmake options中输入“-G "Visual Studio 16 2019" -A x64”
#因为vcpkg默认是使用Visual Studio编译而非mingw

#设置项目名
project(loading VERSION 1.0.0 LANGUAGES C CXX)

#设置编译器标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#启用QT
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


#设置QT5默认路径
IF (NOT DEFINED ENV{Qt5_DIR})
    IF (WIN32)
        set(Qt5_DIR E:/Qt/5.15.1/msvc2019_64)
    ELSE ()
        set(Qt5_DIR /usr/local/Qt/5.15.2/gcc_64/lib/cmake/Qt5)
    ENDIF ()
ENDIF ()

#设置自定义库默认路径，如果cmake没有指定“-DKMCB_DIR=E:/tools/lib”时使用
#IF (NOT DEFINED ENV{KMCB_DIR})
#    IF (WIN32)
#        set(KMCB_DIR E:/tools/lib)
#    ELSE ()
#        set(KMCB_DIR /usr/local/kmcb)
#    ENDIF ()
#ENDIF ()

#宏定义
#add_definitions(-DSQLITE_HAS_CODEC)
#IF (UNIX)
#   set(define_lfs_macros TRUE)    
#    IF (define_lfs_macros)
#        add_definitions(-D__USE_FILE_OFFSET64)
#        add_definitions(-D__USE_LARGEFILE64)
#        add_definitions(-D_LARGEFILE64_SOURCE)
#        add_definitions(-D_FILE_OFFSET_BITS=64)
#    ENDIF ()
#ELSE ()
#    add_definitions(-DWIN32_LEAN_AND_MEAN)
#ENDIF ()

#设置编译器选项
IF (WIN32)
    ADD_COMPILE_OPTIONS("/utf-8")
ENDIF ()

#查找软件包
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Intl REQUIRED)
#查找自定义的类库
IF (WIN32)

    #    find_path(KMCB_INCLUDE NAMES KcCore.h PATHS ${KMCB_DIR}/include NO_DEFAULT_PATH)
    #    find_library(KMCB_LIB kmcb.lib "${KMCB_DIR}/lib/Release")
ELSE ()
    #    find_path(KMCB_INCLUDE NAMES KcCore.h PATHS "${KMCB_DIR}/include" NO_DEFAULT_PATH)
    #    find_library(KMCB_LIB libkmcb.so "${KMCB_DIR}/lib")
ENDIF ()

#当编译为（.a、.so、dll、.lib）时需要导出的头文件。.exe不需要此项设置
#SET(KC_SRC_HEADERS
#)

#添加所有源文件
SET(KC_SRC
        main.cpp
        stringbuffer.c
        QdKcLogin.cpp)

#添加所有QT头文件
SET(KC_QT_SRC_HEADERS
        QdKcLogin.h
        )

#添加所有.ui文件
SET(KC_QT_SRC_UI
        QdKcLogin.ui
        )

#添加所有资源文件
SET(KC_QT_SRC_RESOURCES
        login.qrc
        )

#调用预编译器moc，需要使用 QT5_WRAP_CPP宏
QT5_WRAP_CPP(KC_QT_HEADERS ${KC_QT_SRC_HEADERS})
#使用uic处理.ui文件
QT5_WRAP_UI(KC_QT_UI ${KC_QT_SRC_UI})
#使用rcc处理.qrc文件
QT5_ADD_RESOURCES(KC_QT_RESOURCES ${KC_QT_SRC_RESOURCES})

#导入包含目录
IF (WIN32)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}
            ${Intl_INCLUDE_DIRS}
            #${KMCB_INCLUDE}
            )
ELSE ()
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}
            ${Intl_INCLUDE_DIRS}
            #${KMCB_INCLUDE}
            )
ENDIF ()
#生成可执行文件
ADD_EXECUTABLE(${PROJECT_NAME}
        ${KC_SRC}
        ${KC_QT_HEADERS}
        ${KC_QT_UI}
        ${KC_QT_RESOURCES}
        )


#为target添加需要链接的共享库
IF (WIN32)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME}
            #QT
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            #其它
            ${Intl_LIBRARIES}
            #${KMCB_LIB}
            )
ELSE ()
    TARGET_LINK_LIBRARIES(${PROJECT_NAME}
            #QT
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            #其它
            ${Intl_LIBRARIES}
            #${KMCB_LIB}
            )
ENDIF ()
