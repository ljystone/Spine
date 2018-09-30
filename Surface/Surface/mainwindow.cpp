#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QStringList>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_thread=new MyThread(this);
    connect(m_thread,&MyThread::request,this,&MainWindow::showData);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButtonStart_clicked()
{
    //this->m_thread->startThread();
    m_serial=new QSerialPort;
    m_serial->setPortName("COM5");
    m_serial->open(QIODevice::ReadWrite);

    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    m_serial->setDataTerminalReady(true);

    connect(m_serial,&QSerialPort::readyRead,this,showData1);
}
void MainWindow::showData1()
{

        static QByteArray data;
        data+=m_serial->readAll();
        QString s(data);
        qDebug()<<s;
       QStringList list=s.split("!");
      for(int i=0;i<list.size();i++)
      {
          QStringList list2=list[i].split("#");
          if(list2.size()==4)
          {
              ui->lineEditLPush->setText(list2[0]);
              ui->lineEditrRPush->setText(list2[1]);
              ui->lineEditLMove->setText(list2[2]);
              ui->lineEditRMove->setText(list2[3]);

          }

      }

}
void MainWindow::showData(const QString &s)
{


       QStringList list=s.split("!");
      for(int i=0;i<list.size();i++)
      {
          QStringList list2=list[i].split("#");
          if(list2.size()==4)
          {
              ui->lineEditLPush->setText(list2[0]);
              ui->lineEditrRPush->setText(list2[1]);
              ui->lineEditLMove->setText(list2[2]);
              ui->lineEditRMove->setText(list2[3]);

          }

      }

}

void MainWindow::on_pushButtonStop_clicked()
{
   // m_thread->closeThread();
    m_serial->close();
}
