//
// Created by kmblack on 2022/3/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QmKcMain.h" resolved

#include "QmKcMain.h"
#include "ui_QmKcMain.h"


QmKcMain::QmKcMain(QWidget *parent) :
        QDialog(parent), ui(new Ui::QmKcMain) {
    ui->setupUi(this);
#pragma region 信号槽
    QObject::connect(this->ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
#pragma endregion
}

QmKcMain::~QmKcMain() {
    delete ui;
}

