//
// Created by kmblack on 2022/3/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QmKcMain.h" resolved
#include <libintl.h>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include "KcUtility.h"
#include "QdKcLogin.h"
#include "ui_QdKcLogin.h"


QdKcLogin::QdKcLogin(StringBuffer str, QWidget *parent) :
        QDialog(parent), mStr(str), ui(new Ui::QdKcLogin) {
    KC_CHECK_MALLOC(this->ui, str);
    ui->setupUi(this);

    KC_CHECK_RCV2(this->loadmage());

#pragma region 窗体设置
    this->setAttribute(Qt::WA_TranslucentBackground);   //背景透明
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog); //去除标题栏
    this->setModal(true); // 模态对话框,Qt::WA_ShowModal简化函数
    //this->setAttribute(Qt::WA_ShowModal, true); // 设置WA_ShowModal属性
    //this->setWindowModality(Qt::ApplicationModal); // 设置阻塞方式
    this->setFixedSize(this->mImage->width(), this->mImage->height());    //固定大小
#pragma endregion

#pragma region 信号槽
    QObject::connect(this->ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
#pragma endregion

    this->ui->txtUserId->setFocus();
    this->ui->btnOk->setEnabled(false);
    return;
KC_ERROR_CLEAR:
    QMessageBox::critical(this, QString::fromLocal8Bit(_TR("error")), QString::fromLocal8Bit(_TR(str->data)),
                          QMessageBox::Ok, QMessageBox::Ok);
    this->reject();
}

QdKcLogin::~QdKcLogin() {
    KC_SAFE_DELETE(this->mImage);
    KC_SAFE_DELETE(this->mPixmap);
    KC_SAFE_DELETE(ui);
}

int32_t QdKcLogin::loadmage() {
    StringBuffer str = this->mStr;

    this->mImage = new QImage();
    KC_CHECK_MALLOC(this->mImage, str);
    if (!this->mImage->load(QString(":/login/loading.png")))
        KC_GOTOERR(str, "%s", "load background image fail.");
    return KC_OK;
KC_ERROR_CLEAR:
    KC_SAFE_DELETE(this->mImage);
    KC_SAFE_DELETE(this->mPixmap);
    return KC_FAIL;
}


#pragma region 重写父类中的方法

void QdKcLogin::resizeEvent(QResizeEvent *event) {
    StringBuffer str = this->mStr;
    const QSize &qsize = event->size();
    QRect src, target(0, 0, qsize.width(), qsize.height());
    QPainter *painter = NULL;
    QPen pen;
    //QBrush brush;

    if (NULL == this->mImage)
        return;
    src = this->mImage->rect();

    KC_SAFE_DELETE(this->mPixmap);
    this->mPixmap = new QPixmap(qsize);
    KC_CHECK_MALLOC(this->mPixmap, str);
    this->mPixmap->fill(Qt::transparent);//用透明色填充	


    painter = new QPainter();
    KC_CHECK_MALLOC(painter, str);
    painter->begin(this->mPixmap);
    painter->setRenderHint(QPainter::Antialiasing);    //开启抗锯齿
    /*
     * 使用图片插值算法（如双线性插值算法）
     * 当窗体大小不等于源图片大小时，图片缩放时会采用插值算法对像素点进行插值。
     * 插值后的图像清晰度会大幅提升。
     */
    painter->setRenderHints(QPainter::SmoothPixmapTransform, true);
    /*
    * 请不要使用QPainter::TextAntialiasing。相反，请在字体的样式策略上设置 QFont：：NoAntialias。
    *	QFont font;
    *	font.setStyleStrategy(QFont::PreferAntialias);
    */
    //painter->setRenderHint(QPainter::TextAntialiasing);    //开启文字抗锯齿，这个方法已经过时，请使用 QFont：：PreferAntialias

    pen.setWidth(3);                                // 设置画笔宽度（线宽）
    pen.setColor(Qt::white);                    //设置画笔颜色
    pen.setStyle(Qt::SolidLine);                // 线的样式
    pen.setCapStyle(Qt::FlatCap);            // 线条的端点样式
    pen.setJoinStyle(Qt::BevelJoin);        // 连接点的样式
    painter->setPen(pen);

    //// brush属性
    //QBrush brush;
    //brush.setColor(Qt::green);        // 填充颜色
    //brush.setStyle(Qt::SolidPattern);   // 填充样式
    //painter->setBrush(brush);

    //强制将图片绘制为窗体大小
    painter->drawImage(target, *this->mImage, src);
    //绘制边框
    painter->drawRect(target);
    painter->end();
    KC_SAFE_DELETE(painter);
    return;
KC_ERROR_CLEAR:
    KC_SAFE_DELETE(painter);
    QMessageBox::critical(this, QString::fromLocal8Bit(_TR("error")), QString::fromLocal8Bit(_TR(str->data)),
                          QMessageBox::Ok, QMessageBox::Ok);
}

/**
 * 双缓冲绘图,减少窗体闪烁
 * @param event
 * 1.每次窗体大小发生变化时将在内存中重新绘制与窗体大小相同的图像
 * 2.当窗体需要重新绘制时直接绘制在内存中的图像
 */
void QdKcLogin::paintEvent(QPaintEvent *event) {
    StringBuffer str = this->mStr;
    QPainter *painter = NULL;

    if (NULL == this->mPixmap)
        return;
    painter = new QPainter();
    KC_CHECK_MALLOC(painter, str);

    painter->begin(this);
    painter->drawPixmap(0, 0, *this->mPixmap);
    painter->end();
    KC_SAFE_DELETE(painter);
    return;
KC_ERROR_CLEAR:
    KC_SAFE_DELETE(painter);
    QMessageBox::critical(this, QString::fromLocal8Bit(_TR("error")), QString::fromLocal8Bit(_TR(str->data)),
                          QMessageBox::Ok, QMessageBox::Ok);
}

//鼠标按下事件
void QdKcLogin::mousePressEvent(QMouseEvent *event) {
    mMouseLastPos = event->globalPos();  //获取按下时的坐标(全局坐标)
    this->mIsMove = true;
}

//鼠标移动事件
void QdKcLogin::mouseMoveEvent(QMouseEvent *event) {
    if (this->mIsMove) {
        int dx = event->globalX() - mMouseLastPos.x();   //
        int dy = event->globalY() - mMouseLastPos.y();

        mMouseLastPos = event->globalPos();
        move(x() + dx, y() + dy);            //移动窗体
    }
}

//鼠标释放事件可以有也可以没有
void QdKcLogin::mouseReleaseEvent(QMouseEvent *event) {
    if (this->mIsMove) {
        int dx = event->globalX() - mMouseLastPos.x();
        int dy = event->globalY() - mMouseLastPos.y();
        move(x() + dx, y() + dy);
        this->mIsMove = false;
    }
}

#pragma endregion