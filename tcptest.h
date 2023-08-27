#ifndef TCPTEST_H
#define TCPTEST_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TcpTest; }
QT_END_NAMESPACE

class TcpTest : public QMainWindow
{
    Q_OBJECT

public:
    TcpTest(QWidget *parent = nullptr);
    ~TcpTest();

private:
    Ui::TcpTest *ui;
};
#endif // TCPTEST_H
