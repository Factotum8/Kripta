/*

#ifndef CLIENTEXAMPLE_H
#define CLIENTEXAMPLE_H

#include <QObject>
#include <iostream>
#include <QCoreApplication>
#include <QString>
#include <QSslSocket>
#include <QThread>

class ClientExample : public QObject
{
    Q_OBJECT

public:
    ClientExample(QObject *parent = 0);


public slots:
    void run();
};

#endif // CLIENTEXAMPLE_H*/


#include <QWidget>
#include <QTcpSocket>
#include <QtWidgets>
#include <QTcpSocket>
#include <QTextEdit>
#include <qtcpserver.h>
#include <QObject>
#include <iostream>
#include <QCoreApplication>
#include <QString>
#include <QSslSocket>
#include <QThread>

class QTextEdit;
class QLineEdit;

class MyClient : public QWidget {
Q_OBJECT
private:
    QSslSocket* m_pTcpSocket;
    QTextEdit*  m_ptxtInfo;
    QLineEdit*  m_ptxtInput;
    quint16     m_nNextBlockSize;

public:
    MyClient(const QString& strHost, int nPort, QWidget* pwgt = 0) ;

private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );
};
