#ifndef CLIENTFILETRANS_H
#define CLIENTFILETRANS_H

#include <QObject>
#include <QThread>
#include "ClientOperate.h"

class ClientFileTrans : public QObject {
    Q_OBJECT
  public:
    explicit ClientFileTrans(QString ip, quint16 port, QObject *parent = nullptr);
    ~ClientFileTrans();

    // 开始文件传输
    void startTrans(const QString &fileHash, const QString &savePath);

    // 取消文件传输
    void cancelTrans();

    int getProgressValue() const;

  signals:
    //使用信号槽操作线程中的ClientOperate
    void connectTcp(const QString &address, quint16 port);
    void disconnectTcp();

  private:
    //线程
    QThread *thread;
    //server处理放到线程中
    ClientOperate *operate;
    // 接收方 ip 地址
    QString m_ip;
    // port
    quint16 m_port;
    // progress
    int progressValue;
    Q_PROPERTY(int progressValue READ getProgressValue CONSTANT FINAL)
};

#endif // CLIENTFILETRANS_H
