#ifndef MYSERVER_H
#define MYSERVER_H
#include <QWidget>
#include <QWidgetSet>
#include <QVBoxLayout>
#include <QMessageBox>
//#include <QtWidgets>
#include <QTcpSocket>
#include <QTextEdit>
#include <qtcpserver.h>
#include <QTime>

//class QTcpServer;
//class QTextEdit;
//class QTcpSocket;

class MyServer : public QWidget {
Q_OBJECT
private:
  QTcpServer * m_ptcpServer;
  QTextEdit *  m_ptxt;
  quint16     m_nNextBlockSize;

private:
    void sendToClient(class QTcpSocket* pSocket, const QString& str);

public:
    MyServer(int nPort, QWidget* pwgt = 0);

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
};

#endif _MyServer_H


