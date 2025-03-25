#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QListView>  // 添加这行
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
   
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QSerialPort *serilaPort;

private slots:
    void on_SendButton_released();

    void on_OpenButton_released();

    void on_CloseButton_released();

    void serilaPortReadyRead_Slot();


    void on_RefreshButton_released();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
