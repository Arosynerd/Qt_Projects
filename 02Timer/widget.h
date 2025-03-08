#ifndef WIDGET_H
#define WIDGET_H

#define TIMEOUT 1000
#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void timerEvent(QTimerEvent *event);
    ~Widget();

private slots:
    void on_StartButton_clicked();

    void on_StopButton_released();

private:
    Ui::Widget *ui;
    int timer_id;
    int pic_cnt = 1;
};
#endif // WIDGET_H
