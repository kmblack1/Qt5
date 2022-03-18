#include <stdio.h>
#include <stdlib.h>
#include <libintl.h>
#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>
#include "stringbuffer.h"
#include "KcUtility.h"
#include "QmKcMain.h"

int main(int argc, char *argv[]) {
    int32_t rc = KC_OK;
    StringBuffer str = NULL;

    QApplication *app = NULL;
    QSharedMemory *shared = NULL;
    QmKcMain *mainWindow = NULL;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); //启用高分屏缩放
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); //启用高分屏高清QIcon
    //设置高分屏缩放舍入策略，必须写在QApplication的前面
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);//向下舍入

    str = createStringBuffer();
    app = new QApplication(argc, argv);
    KC_CHECK_MALLOC(app, str);
    //只允许运行一个程序
//    shared = new QSharedMemory("loading");
//    KC_CHECK_MALLOC(app, str);
//    if (!shared->create(1)) {
//        KC_SAFE_QOBJECT_DELETE(shared);
//        KC_SAFE_QAPPLICATION_EXIT_DELETE(app);
//        return EXIT_FAILURE;
//    }
    //设置中文字体 
#ifdef _WIN32
    app->setFont(QFont("Microsoft Yahei", 12));
#else
    app->setFont(QFont("Noto Mono", 12));
#endif
    //注册元数据类型后才可以在信号槽中使用
    qRegisterMetaType<int32_t>("int32_t");
    qRegisterMetaType<int64_t>("int64_t");
    //设置应用程序信息
    QCoreApplication::setOrganizationName(QString::fromLocal8Bit("kuncb.cn"));
    QCoreApplication::setApplicationName(QString::fromLocal8Bit("loading"));
    QCoreApplication::setApplicationVersion(QString::fromLocal8Bit("1.0.0"));
    //加载默认语言包
//    QFile file(":/qss/black.css"); //控件样式表需要在qss/lightblue.qss里面
//    if (file.exists())
//        file.open(QFile::ReadOnly);
//    QString styleSheet = QLatin1String(file.readAll());
//    app.setStyleSheet(styleSheet);
//    file.close();
//

    mainWindow = new QmKcMain();
    KC_CHECK_MALLOC(mainWindow, str);
    mainWindow->show();
    rc = app->exec();
    KC_SAFE_QOBJECT_DELETE(mainWindow);
    KC_SAFE_QOBJECT_DELETE(shared);
    KC_SAFE_QAPPLICATION_EXIT_DELETE(app);
    KC_SAFE_STRINGBUF_FREE(str);
    return rc;
KC_ERROR_CLEAR:
    QMessageBox::critical(Q_NULLPTR, QString::fromLocal8Bit(_TR("error")), QString::fromLocal8Bit(_TR(str->data)),
                          QMessageBox::Ok, QMessageBox::Ok);

    KC_SAFE_QOBJECT_DELETE(mainWindow);
    KC_SAFE_QOBJECT_DELETE(shared);
    KC_SAFE_QAPPLICATION_EXIT_DELETE(app);
    KC_SAFE_STRINGBUF_FREE(str);
    return EXIT_FAILURE;
}
