#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setMaximumSize(340,370);
    this->setMinimumSize(340,370);
    this->setWindowTitle("calculator");
    this->setWindowIcon(QIcon("://favice.ico"));
    // 设置WorkButton的背景颜色
    ui->WorkButton->setStyleSheet("background-color: yellow;");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_OneButton_released()
{
    expression += "1";
    ui->lineEdit->setText(expression);
}

void Widget::on_TwoButton_released()
{
    expression += "2";
    ui->lineEdit->setText(expression);
}

void Widget::on_ThreeButton_released()
{
    expression += "3";
    ui->lineEdit->setText(expression);
}

void Widget::on_FourButton_released()
{
    expression += "4";
    ui->lineEdit->setText(expression);
}

void Widget::on_FiveButton_released()
{
    expression += "5";
    ui->lineEdit->setText(expression);
}

void Widget::on_SixButton_released()
{
    expression += "6";
    ui->lineEdit->setText(expression);
}

void Widget::on_Seven_Button_released()
{
    expression += "7";
    ui->lineEdit->setText(expression);
}

void Widget::on_EightButton_released()
{
    expression += "8";
    ui->lineEdit->setText(expression);
}

void Widget::on_NineButton_released()
{
    expression += "9";
    ui->lineEdit->setText(expression);
}

void Widget::on_ZeroButton_released()
{
    expression += "0";
    ui->lineEdit->setText(expression);
}

void Widget::on_AddButton_released()
{
    expression += "+";
    ui->lineEdit->setText(expression);
}

void Widget::on_SubButton_released()
{
    expression += "-";
    ui->lineEdit->setText(expression);
}

void Widget::on_WorkButton_released()
{
    // 计算表达式的结果
    QJSEngine engine;
    QJSValue result = engine.evaluate(expression);

    if (result.isError()) {
        // 如果表达式有错误，弹出警告对话框并清空lineEdit内容
        QMessageBox::warning(this, "错误", "输入的表达式不合理，请重新输入！");
        expression = "";
        ui->lineEdit->setText("");
    } else {
        QString resultString = result.toString();
        // 将结果显示在lineEdit中
        ui->lineEdit->setText(resultString);
    }
}

void Widget::on_CleraButton_released()
{
    expression = "";
    ui->lineEdit->setText("");
}

void Widget::on_DeleteButton_released()
{
    if (!expression.isEmpty()) {
        expression.chop(1); // 删除最后一个字符
        ui->lineEdit->setText(expression);
    }
}

