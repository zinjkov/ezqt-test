#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QUdpSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->pushButton->setText("Потушить");
    socket = new QUdpSocket(this);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete socket;
}

void MainWindow::on_pushButton_clicked()
{
    static bool led = false;
    uint32_t adr;
    adr = (192 << 24) + (168 << 16) + (88 << 8) + (14);
    QHostAddress addr;
    bool res = addr.setAddress("192.168.88.14");
    if(led) {
        socket->writeDatagram("d", addr, 1111);
        ui->pushButton->setText("Потушить");
    } else {
        ui->pushButton->setText("Зажеч");
        socket->writeDatagram("u", addr, 1111);
    }
    if (!res) {
        ui->pushButton->setText("don't send");

    }
    led = !led;
}
