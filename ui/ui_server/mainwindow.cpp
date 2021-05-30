#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("IRC - Server");
    printLog();
    updateChannelList();
    updateClientList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateClientList()
{
    short count = 3;
//    ui->textClientList->append("NICKNAME");
//    for (std::map<std::string, Client*>::iterator it = _m_pclients.begin() ; it != _m_pclients.end() ; it++){
//        ui->textClientList->append(QString::fromStdString(it->second->nickname));
//        count++;
//    }
    ui->NumberClient->display(count);
//
    ui->textClientList->append("bob");
    ui->textClientList->append("albert");
    ui->textClientList->append("jose");
//
}

void MainWindow::updateChannelList()
{
    short count = 2;
//    ui->textChannelList->append("NAME");
//    for (std::map<std::string, std::string>::iterator it = _m_topics.begin() ; it != _m_topics.end() ; it++){
//        ui->textChannelList->append(QString::fromStdString(it->first));
//        count++;
//    }
    ui->NumberChannel->display(count);
//
    ui->textChannelList->append("#bla");
    ui->textChannelList->append("#plop");
//
}

void MainWindow::printLog()
{
    ui->logText->append("LOG SERV !!");
}
