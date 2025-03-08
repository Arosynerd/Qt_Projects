#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //键盘事件
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

private slots:
    void on_action_New_triggered();
    void on_action_Save_triggered();
    void on_action_SaveImmediately_triggered();
};
#endif // MAINWINDOW_H
