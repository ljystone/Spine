#include "mythread.h"
#include <QSerialPort>
#include <QMessageBox>
#include <QDebug>

MyThread::MyThread(QObject *parent) : QThread(parent),quit(false)
{

}
void MyThread::startThread()
{
    if(!isRunning())
    {
        start();
    }
}
void MyThread::closeThread()
{
    if(isRunning())
    {
       quit=true;
    }
}
void MyThread::run()
{
    m_serial=new QSerialPort;
    while (!quit) {
        m_serial->setPortName("COM5");
        if(m_serial->open(QIODevice::ReadWrite))
        {
            m_serial->setBaudRate(QSerialPort::Baud9600);
            m_serial->setParity(QSerialPort::NoParity);
            m_serial->setDataBits(QSerialPort::Data8);
            m_serial->setStopBits(QSerialPort::OneStop);
            m_serial->setFlowControl(QSerialPort::NoFlowControl);
            m_serial->setDataTerminalReady(true);

            //m_serial->clearError();
            if(m_serial->waitForReadyRead(1000)){
                static QByteArray requestData=m_serial->readAll();
                while(m_serial->waitForReadyRead(10))
                 {
                       requestData+=m_serial->readAll();
                          QString str(requestData);
                          emit this->request(str);
                          qDebug()<<str;

                 }
            }

            // m_serial->clear();
        }
        else {
            //QMessageBox::critical(this,"err","串口打开失败",QMessageBox::Yes|QMessageBox::No);
        }
    }
}
