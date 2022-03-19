//
// Created by kmblack on 2022/3/18.
//

#ifndef LOADING_QMKCMAIN_H
#define LOADING_QMKCMAIN_H

#include <stdint.h>
#include <QDialog>
#include <QImage>
#include <QPixmap>
#include "stringbuffer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QdKcLogin; }
QT_END_NAMESPACE

class QdKcLogin : public QDialog {
Q_OBJECT
private:
    Ui::QdKcLogin *ui;
    bool mIsMove = false;
    QPoint mMouseLastPos;

    StringBuffer mStr = NULL;
    QImage* mImage = NULL;
    QPixmap* mPixmap = NULL;


public:
    explicit QdKcLogin(StringBuffer str,QWidget *parent = nullptr);

    ~QdKcLogin() override;
private:
    int32_t loadmage();
protected:
    void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent* event)  Q_DECL_OVERRIDE;
    //void showEvent(QShowEvent*) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

};


#endif //LOADING_QMKCMAIN_H
