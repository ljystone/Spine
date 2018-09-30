#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QMutex>
#include <QSerialPort>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

    void startThread();
    void closeThread();
    void run();

signals:
    void request(const QString &s);

public slots:
private:
    //QByteArray requestData;

    QSerialPort *m_serial;
    bool quit;


};

#endif // MYTHREAD_H
