/*#ifndef SERVEREXAMPLE_H
#define SERVEREXAMPLE_H

#include <QObject>

class ServerExample : public QObject
{
    Q_OBJECT

public:
    ServerExample(QObject *parent = 0);


public slots:
    void run();
};

#endif // SERVEREXAMPLE_H*/


#ifndef MYSERVER_H
#define MYSERVER_H
//#include <QtWidgets>
#include <QWidget>
#include <QSslSocket>
#include <QTextEdit>
#include <qtcpserver.h>
#include <QSslSocket>
#include "SslServer.h"

//class QTcpServer;
//class QTextEdit;
//class QTcpSocket;

class MyServer : public QWidget {
Q_OBJECT
private:
  SslServer * m_ptcpServer;
  //QTcpServer * m_ptcpServer;
  QTextEdit *  m_ptxt;
  quint16     m_nNextBlockSize;

private:
    void sendToClient(class QSslSocket* pSocket, const QString& str);

public:
    MyServer(int nPort, QWidget* pwgt = 0);

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
};

#endif _MyServer_H
