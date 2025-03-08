#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("文本编辑器");
    connect(ui->action_N,&QAction::triggered,this,&MainWindow::on_action_New_triggered);
    connect(ui->action_O,&QAction::triggered,[this]() {
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->textEdit->setText(in.readAll());
            file.close();
            this->setWindowTitle(fileName);
        } else {
            QMessageBox::warning(this, "警告", "无法打开文件");
        }
    }
    else{
        QMessageBox::warning(this, "警告", "未选择文件");
    }
    });
    connect(ui->action_S,&QAction::triggered,this,&MainWindow::on_action_Save_triggered);
    connect(ui->action_S_2,&QAction::triggered,this,&MainWindow::on_action_SaveImmediately_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_action_New_triggered(){
    ui->textEdit->clear();
    this->setWindowTitle("新建文本文档");
}
void MainWindow::on_action_Save_triggered(){
    QString fileName = QFileDialog::getSaveFileName(this, "保存文件", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            file.close();
            this->setWindowTitle(fileName);
        } else {
            QMessageBox::warning(this, "警告", "无法保存文件");
        }
    }
    else{
        QMessageBox::warning(this, "警告", "未选择文件");
    }
}
void MainWindow::on_action_SaveImmediately_triggered(){
    QString fileName = this->windowTitle();
    if(fileName=="文本编辑器"){
        on_action_Save_triggered();
    }
    else{
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            file.close();
            //输出保存成功
            QMessageBox::information(this, "提示", "保存成功");
        } else {
            QMessageBox::warning(this, "警告", "无法保存文件");
        }
    } 
}
//键盘事件
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_S&&event->modifiers()==Qt::ControlModifier){
        on_action_SaveImmediately_triggered();
    } 
}

