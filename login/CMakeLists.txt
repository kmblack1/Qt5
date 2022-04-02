cmake_minimum_required(VERSION 3.11)

#cmake 集成vcpkg(需要在project前增加)
IF (NOT CMAKE_TOOLCHAIN_FILE)
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
IF (NOT Qt5_DIR)
    IF (MSVC)
        set(Qt5_DIR E:/Qt/5.15.1/msvc2019_64)
    ELSE ()
        set(Qt5_DIR /usr/local/Qt/5.15.2/gcc_64/lib/cmake/Qt5)
    ENDIF ()
ENDIF ()


#设置自定义库默认路径，如果cmake没有指定“-DKMCB_DIR=E:/tools/lib”时使用
#IF (NOT DEFINED ENV{KMCB_DIR})
#    IF (MSVC)
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
IF (MSVC)
    ADD_COMPILE_OPTIONS("/utf-8")
ENDIF ()

#查找软件包
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Intl REQUIRED)
#查找自定义的类库
IF (MSVC)

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
        KcVld.c
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
IF (MSVC)
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
IF (MSVC)
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

# 移除控制台,只需要GUI
if (WIN32)
    if (MSVC)
        set_target_properties(${PROJECT_NAME} PROPERTIES
                WIN32_EXECUTABLE YES
                LINK_FLAGS "${CMAKE_LINK_FLAGS} /SUBSYSTEM:Windows /ENTRY:mainCRTStartup"
                )
    elseif (CMAKE_COMPILER_IS_GNUCXX)
        # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
    else ()
        message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
    endif (MSVC)
elseif (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE YES
            )
elseif (UNIX)
    # Nothing special required
else ()
    message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif (WIN32)

# Installation
SET(install_targets ${install_targets} ${PROJECT_NAME})
#获取QT根目录
string(REGEX REPLACE "/lib/cmake/Qt5" "" Qt5_ROOT_DIR ${Qt5_DIR})
#安装可执行文件
INSTALL(TARGETS ${install_targets}
        #可执行二进制文件
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
        )
#获取依赖的dll
IF (MSVC)
    SET(DUMP_DLL_RELEASE
            ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin/iconv-2.dll
            ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin/intl-8.dll
            )
ELSEIF ()
    #linux直接通过apt安装
    #sudo apt-cache search intl
    #sudo apt-get -y install
ENDIF (MSVC)
INSTALL(FILES ${DUMP_DLL_RELEASE} DESTINATION ${CMAKE_INSTALL_PREFIX})

#安装QT DLL(最小安装)
IF (MSVC)
    SET(QT_DEPENDENTS_DLL
            ${Qt5_ROOT_DIR}/bin/Qt5Core.dll
            ${Qt5_ROOT_DIR}/bin/Qt5Gui.dll
            ${Qt5_ROOT_DIR}/bin/Qt5Widgets.dll
            )
    INSTALL(FILES ${QT_DEPENDENTS_DLL} DESTINATION ${CMAKE_INSTALL_PREFIX})
ENDIF (MSVC)

#安装Qt插件配置文件
IF (MSVC)
    SET(QT_DEPENDENTS_CONFIG
            qt.conf
            )
    INSTALL(FILES ${QT_DEPENDENTS_CONFIG} DESTINATION ${CMAKE_INSTALL_PREFIX})
ENDIF (MSVC)

#安装QT插件(最小安装)
IF (MSVC)
    SET(QT_DEPENDENTS_PLUGINS
            ${Qt5_ROOT_DIR}/plugins/platforms/qdirect2d.dll
            ${Qt5_ROOT_DIR}/plugins/platforms/qminimal.dll
            ${Qt5_ROOT_DIR}/plugins/platforms/qoffscreen.dll
            ${Qt5_ROOT_DIR}/plugins/platforms/qwebgl.dll
            ${Qt5_ROOT_DIR}/plugins/platforms/qwindows.dll
            )
    INSTALL(FILES ${QT_DEPENDENTS_PLUGINS} DESTINATION ${CMAKE_INSTALL_PREFIX}/plugins/platforms)
ENDIF (MSVC)
#打印信息
MESSAGE(STATUS "")
MESSAGE(STATUS "")
MESSAGE(STATUS "${PROJECT_NAME} configuration summary:")
MESSAGE(STATUS "")

MESSAGE(STATUS "  Qt5 root ...................... : ${Qt5_ROOT_DIR}")
MESSAGE(STATUS "  Build type ...................... : ${CMAKE_BUILD_TYPE}")
MESSAGE(STATUS "  Install prefix .................. : ${CMAKE_INSTALL_PREFIX}")
MESSAGE(STATUS "  C compiler ...................... : ${CMAKE_C_COMPILER}")
MESSAGE(STATUS "  CXX compiler ...................... : ${CMAKE_CXX_COMPILER}")