#include "tcptest.h"
#include "./ui_tcptest.h"

TcpTest::TcpTest(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TcpTest)
{
    ui->setupUi(this);
}

TcpTest::~TcpTest()
{
    delete ui;
}

