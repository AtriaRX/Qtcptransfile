#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>

class SocketThread : public QThread {
  public:
    explicit SocketThread(int socketDescriptor, QObject *parent = nullptr);
  protected:
    void run() override;


  private:
    int socketDescriptor;
};

#endif // SOCKETTHREAD_H
