#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("串口助手");
    this->setWindowIcon(QIcon("://favice.ico"));
    serilaPort = new QSerialPort(this);
    QStringList serialNamePort;
    foreach (const QSerialPortInfo &info ,QSerialPortInfo::availablePorts()) {
        serialNamePort<<info.portName();
    }
    ui->comboBox->addItems(serialNamePort);


    connect(serilaPort,SIGNAL(readyRead()),this,SLOT(serilaPortReadyRead_Slot()));//串口接收信号
    connect(ui->lineEdit,&QLineEdit::returnPressed,this,&Widget::on_SendButton_released);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_SendButton_released()
{
    //获取lineedit输入的内容
    QString str = ui->lineEdit->text();
    //检测输入内容是否为空
    if(str.isEmpty())
    {
        QMessageBox::warning(this, "警告", "发送内容不能为空");
        return;
        }
        else {
        ui->textBrowser->setTextColor(Qt::red);
        ui->textBrowser->append("发送内容：" + str + "\r\n");
        }
}

void Widget::on_OpenButton_released()
{
    //获取串口号
    QString str = ui->comboBox->currentText();

    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity checkBits;
    //使用默认配置进行串口初始化
    baudRate = QSerialPort::Baud115200;
    dataBits = QSerialPort::Data8;
    stopBits = QSerialPort::OneStop;
    checkBits = QSerialPort::NoParity;
    //整合串口配置
    serilaPort->setPortName(ui->comboBox->currentText());
    serilaPort->setBaudRate(baudRate);
    serilaPort->setDataBits(dataBits);
    serilaPort->setStopBits(stopBits);
    serilaPort->setParity(checkBits);

    //以读写打开串口
    if(serilaPort->open(QIODevice::ReadWrite) == true){
        ui->textBrowser->setTextColor(Qt::green);
        ui->textBrowser->append("成功打开串口：" + str + "= = = = = = = = = = = = = = = = =\r\n");
    }else{
        ui->textBrowser->setTextColor(Qt::red);
        ui->textBrowser->append("失败打开串口：" + str + "= = = = = = = = = = = = = = = = =\r\n");
    }
    
}

void Widget::on_CloseButton_released()
{
    QString str = ui->comboBox->currentText();
    serilaPort->close();
    ui->textBrowser->setTextColor(Qt::red);
    ui->textBrowser->append("串口" + str + "已关闭= = = = = = = = = = = = = = = = =\r\n");
}
void Widget::serilaPortReadyRead_Slot(){
    QString buf;
    buf = QString(serilaPort->readAll());
    ui->textBrowser->setTextColor(Qt::black);
    ui->textBrowser->append("接收内容：" + buf);
}



void Widget::on_RefreshButton_released()
{
    QStringList serialNamePort;
    foreach (const QSerialPortInfo &info ,QSerialPortInfo::availablePorts()) {
        serialNamePort<<info.portName();
    }
    ui->comboBox->clear();
    ui->comboBox->addItems(serialNamePort);
}
