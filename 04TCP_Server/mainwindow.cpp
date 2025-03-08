#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,800);
    esp_server=new QTcpServer(this);

   if( !esp_server->listen(QHostAddress::AnyIPv4,8080))
   {
       qDebug()<<esp_server->errorString();
       qDebug()<<"8080监听失败";

   }
   qDebug()<<"8080监听成功";


   //时间显示
    DateTime=QDateTime::currentDateTime();
    connect(&timer, &QTimer::timeout, [this]() {
           DateTime=DateTime.addSecs(1);
           ui->time_lab->setText(DateTime.toString("yyyy-MM-dd hh:mm:ss"));


       });
    timer.start(1000); // 每秒更新一次时间


    //让连接信号和连接处理函数联系起来
   connect(esp_server,&QTcpServer::newConnection,this,&MainWindow::esp_server_New_Connect);
}





void MainWindow::esp_server_New_Connect()   //当有新的链接来的时候
{
    //获取客户端连接
    socket_esp = esp_server->nextPendingConnection();
    QObject::connect(socket_esp, &QTcpSocket::readyRead, this, &MainWindow::socket_espRead_Data);
    QObject::connect(socket_esp, &QTcpSocket::disconnected, socket_esp, &QTcpSocket::deleteLater);
    qDebug()<<"esp连接";

    if(socket_esp!=nullptr)
    {

    }
}




void MainWindow::socket_espRead_Data()
{
    QByteArray buffer;
    buffer = socket_esp->readAll();
    QString data = QString(buffer);//接收数据格式sh95.0%te25.3li3256
    //输出接收到的数据
    qDebug() << "Received data: " << data;

    QString envir;

    if(data.contains("Start"))//接收到连接信号,发送1次初始时间
    {
        DateTime = QDateTime::currentDateTime();
        qDebug() << "Current Date and Time: " << "time"+DateTime.toString("yyyy-MM-dd hh:mm:ss");
        socket_esp->write("time"+DateTime.toString("yyyy-MM-dd hh:mm:ss").toUtf8());
    }
    if(data.contains("not pass"))//接收到无人活动标志
    {
    ui->led_data_lab->setText("无人活动，建议关灯");
    }

    if(data.contains("temp"))//接收到无人活动标志
    {
      envir =data;
    }


    QString tem;
    QString light;
    tem=envir.mid(6,6);//从小标0开始的5位数据
    light=envir.mid(18,6);
    ui->temp_lab->setText(tem.toUtf8());
    ui->light_lab->setText(light.toUtf8());




}





MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_time_btn_clicked()
{

    DateTime=QDateTime::fromString(ui->dateTimeEdit->text(),"yyyy-MM-dd hh:mm:ss");


    if(socket_esp!=nullptr)
    {

        qDebug()<<ui->dateTimeEdit->text();
        QString t1="time"+ui->dateTimeEdit->text();
        socket_esp->write(t1.toUtf8());
    }

}



void MainWindow::on_temp_btn_clicked()//温度阈值设置
{
    if(socket_esp!=nullptr)
    {
        QString t="temp"+ui->temp_Edit->text();
        socket_esp->write(t.toUtf8());
    }
}

void MainWindow::on_st_btn_clicked()//时间常量设置
{
    if(socket_esp!=nullptr)
    {
        QString t="pass"+ui->ST_Edit->text();
        socket_esp->write(t.toUtf8());
    }
}

void MainWindow::on_led_ON_clicked()//led开启按钮
{
    if(socket_esp!=nullptr)
    {
        QString t="ledon";
        socket_esp->write(t.toUtf8());
    }
    ui->led_data_lab->setText("灯已开启");

}

void MainWindow::on_led_OFF_clicked()//led关闭按钮
{
    if(socket_esp!=nullptr)
    {
        QString t="ledoff";
        socket_esp->write(t.toUtf8());
    }
    ui->led_data_lab->setText("灯已关闭");
}
