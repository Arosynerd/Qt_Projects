#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPixmap pic("://1.png");
    ui->Picture->setPixmap(pic);
    //设置标题
    this->setWindowTitle("Image Slideshow");
    this->setWindowIcon(QIcon("://favice.ico"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_StartButton_clicked()
{
    timer_id = this->startTimer(TIMEOUT);
}
void Widget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != timer_id)
        return;
    // 更新图片
    pic_cnt++;
    if (pic_cnt > 3)
        pic_cnt = 1;
    QString str = QString("://%1.png").arg(pic_cnt);
    QPixmap pic(str);
    ui->Picture->setPixmap(pic);
}

void Widget::on_StopButton_released()
{
    this->killTimer(timer_id);
}

