#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QJSEngine> // 修改此行
#include <QMessageBox> // 添加此行

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_OneButton_released();
    void on_TwoButton_released();
    void on_ThreeButton_released();
    void on_FourButton_released();
    void on_FiveButton_released();
    void on_SixButton_released();
    void on_Seven_Button_released();
    void on_EightButton_released();
    void on_NineButton_released();
    void on_ZeroButton_released();
    void on_AddButton_released();
    void on_SubButton_released();
    void on_WorkButton_released();
    void on_CleraButton_released();
    void on_DeleteButton_released();

private:
    Ui::Widget *ui;
    QString expression;
};
#endif // WIDGET_H
