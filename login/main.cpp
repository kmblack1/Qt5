#include <stdio.h>
#include <stdlib.h>
#include <libintl.h>
#include <QFile>
#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>
#include <QTextStream>
#include "stringbuffer.h"
#include "KcUtility.h"
#include "QdKcLogin.h"

int main(int argc, char *argv[]) {
    int32_t rc = KC_OK;
    StringBuffer str = NULL;

    QApplication *app = NULL;
    QSharedMemory *shared = NULL;
    QdKcLogin *dialog = NULL;
    QFile *stream = NULL;
    QTextStream *textStream = NULL;
    QFont *font=NULL;

    str = createStringBuffer();

    //1.高分屏设置，必须在创建QApplication前面设置
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); //启用高分屏缩放
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); //启用高分屏高清QIcon
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);//设置高分屏缩放舍入策略，向下舍入

    //2.创建QApplication
    app = new QApplication(argc, argv);
    KC_CHECK_MALLOC(app, str);

    //3.设置中文字体
#ifdef _WIN32
    font = new QFont("Microsoft Yahei", 12);
#else
    font = new QFont("Monospace", 12);
#endif
    KC_CHECK_MALLOC(font, str);
    font->setStyleStrategy(QFont::PreferAntialias);
    app->setFont(*font);
    //4.注册元数据类型后才可以在信号槽中使用
    qRegisterMetaType<int32_t>("int32_t");
    qRegisterMetaType<int64_t>("int64_t");
    //5.设置应用程序信息
    QCoreApplication::setOrganizationName(QString::fromLocal8Bit("kuncb.cn"));
    QCoreApplication::setApplicationName(QString::fromLocal8Bit("loading"));
    QCoreApplication::setApplicationVersion(QString::fromLocal8Bit("1.0.0"));

    //6.只允许运行一个程序
    shared = new QSharedMemory(QCoreApplication::applicationName());
    KC_CHECK_MALLOC(shared, str);
    if (!shared->create(1))
        KC_GOTOERR(str,"%s","application is already running."/*shared->errorString().toLocal8Bit().data()*/);
    //7.加载默认语言包

    //8.加载全局样式
    stream = new QFile(":/qss/black.css"); //工程控件样式表需要在qss/lightblue.qss里面
    KC_CHECK_MALLOC(stream, str);
    if (stream->exists()) {
        stream->open(QIODevice::ReadOnly | QIODevice::Text);
        textStream = new QTextStream(stream);
        KC_CHECK_MALLOC(textStream, str);
        app->setStyleSheet(textStream->readAll());
    }
    KC_SAFE_DELETE(textStream);
    KC_SAFE_CLOSE_DELETE(stream);

    //9.显示窗体
    dialog = new QdKcLogin(str);
    KC_CHECK_MALLOC(dialog, str);
    if (QDialog::Accepted == dialog->exec()) {
        KC_SAFE_DELETE(dialog);
        //在这里显示主窗体

        rc = app->exec();
    }
    KC_SAFE_DELETE(dialog);
    KC_SAFE_DELETE(font);
    KC_SAFE_DESTROYED_DELETE(shared);
    KC_SAFE_EXIT_DELETE(app);
    KC_SAFE_STRINGBUF_FREE(str);
    return rc;
KC_ERROR_CLEAR:
    KC_SAFE_DELETE(textStream);
    KC_SAFE_DELETE(stream);
    KC_SAFE_DELETE(dialog);
    KC_SAFE_DELETE(font);
    KC_SAFE_DESTROYED_DELETE(shared);
    QMessageBox::critical(Q_NULLPTR, QString::fromLocal8Bit(_TR("error")), QString::fromLocal8Bit(_TR(str->data)),
                          QMessageBox::Ok, QMessageBox::Ok);
    KC_SAFE_EXIT_DELETE(app);
    KC_SAFE_STRINGBUF_FREE(str);
    return EXIT_FAILURE;
}
