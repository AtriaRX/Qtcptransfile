#ifndef SERVEROPERATE_H
#define SERVEROPERATE_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>
#include <QTimer>
#include <QRunnable>

//服务端socket处理--服务端作为发送
class ServerOperate : public QTcpServer {
    Q_OBJECT
  public:
    explicit ServerOperate(QObject *parent = nullptr);
    ~ServerOperate();

    //get/set 文件路径、监听状态等变量，使用了互斥锁
    QString getFilePath() const;

    void setFilePath(const QString &path);

    bool wisListening() const;

  signals:
    //操作记录发送到ui显示
    void logMessage(const QString &msg);
    //服务端监听状态
    void listenStateChanged(bool isListen);
    //接收进度0-100
    void progressChanged(int value);
    // 发送文件 url 给主线程，以显示到 EditLine 上面
    void showLineUrl(const QString &url);

  public slots:
    //server监听
    void doListen(const QString &address, quint16 port);
    //server取消监听
    void dislisten();
    //取消文件传输
    void cancelFileTransfer(qintptr socketDescriptor);

  private:
    //初始化
    void initOperate();
    //把槽对应的实际操作分离出来是为了复用，这样便于组合
    void doDislisten();
    void doCloseFile(qintptr socketDescriptor);
    void doCancel(qintptr socketDescriptor);
    bool isUrl(const QString &fileurl, qintptr socketDescriptor);
    bool readySendFile(qint64 size, qintptr socketDescriptor);
    void sendFile(const char *data, int size, qintptr socketDescriptor);
    void sendData(char type, const QByteArray &data, qintptr socketDescriptor);
    void operateReceiveData(const QByteArray &data, qintptr socketDescriptor);

    void TimeControl(qintptr socketDescriptor);
    bool inMap(qintptr socketDescriptor);
    QTcpSocket* getSocket(qintptr socketDescriptor);

  protected:
    void incomingConnection(qintptr socketDescriptor) override;

  private:
    //用来锁文件路径、监听状态等变量
    mutable QMutex dataMutex;
    //文件存储路径
    QString fileUrl;
    //地址和端口
    QString address;
    quint16 port;

    //文件操作
    QFile* m_file = nullptr;
    // 使用队列存储套接字对象
    QList<QTcpSocket*> clientSockets;
    //发送数据的定时器
    QList<QTimer*> timers;
    // *socketDescriptor - *timer
    QMap<qintptr, QTimer*> socket_timer;
    // *socketDescriptor - *file
    QMap<qintptr, QFile*> socket_file;
    //发送的字节数，因为Qt接口是int64，本来想用无符号类型
    QMap<qintptr, qint64> socket_sendsize;
    //文件长度
    QMap<qintptr, qint64> socket_filesize;

    //接收缓存，实际操作时还是用char*好点
    QByteArray dataTemp;

    //读取文件到缓冲区
    char fileBuffer[4096] = {0};
    //帧头+长度+类型
    char frameHead[7] = { 0x0F, (char)0xF0, 0x00, (char)0xFF, 0x00, 0x00, 0x00 };
    //帧尾
    char frameTail[2] = { 0x0D, 0x0A };
};

#endif // SERVEROPERATE_H
