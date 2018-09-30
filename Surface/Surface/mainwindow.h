#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QStringList>
#include "mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:


private slots:
void showData1();
    void showData(const QString &s);//显示数据槽函数
    void on_pushButtonStart_clicked();//开始按钮槽函数


    void on_pushButtonStop_clicked();//关闭按钮槽函数

private:
    Ui::MainWindow *ui;
    MyThread *m_thread;
    QSerialPort* m_serial;


};

#endif // MAINWINDOW_H
