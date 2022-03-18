//
// Created by kmblack on 2022/3/18.
//

#ifndef LOADING_QMKCMAIN_H
#define LOADING_QMKCMAIN_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class QmKcMain; }
QT_END_NAMESPACE

class QmKcMain : public QDialog {
Q_OBJECT

public:
    explicit QmKcMain(QWidget *parent = nullptr);

    ~QmKcMain() override;

private:
    Ui::QmKcMain *ui;
};


#endif //LOADING_QMKCMAIN_H
