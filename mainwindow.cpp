#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->stackedWidget->setCurrentIndex(static_cast<int>(ScreenName::PROXY) );
    setScreen(ScreenName::PROXY);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//methods

void MainWindow::setScreen(ScreenName screenName){

    if(proxyThread.isRunning()){
        proxy.stop();
        proxyThread.wait();
    }

    if(screenName == ScreenName::PROXY){
        qDebug() << "Proxy";



        proxy.doSetup(proxyThread);
        proxy.moveToThread(&proxyThread);
        proxyThread.start();

    }

    ui->stackedWidget->setCurrentIndex( static_cast<int>(screenName) );


}

//slots

void MainWindow::on_actionproxy_triggered()
{
   // ui->stackedWidget->setCurrentIndex(static_cast<int>(ScreenName::PROXY) );
   setScreen(ScreenName::PROXY);
}

void MainWindow::on_actionspider_triggered()
{
   // ui->stackedWidget->setCurrentIndex(static_cast<int>(ScreenName::SPIDER));
    setScreen(ScreenName::SPIDER);
}

void MainWindow::on_actiondump_triggered()
{
  //  ui->stackedWidget->setCurrentIndex(static_cast<int>(ScreenName::DUMP));
    setScreen(ScreenName::DUMP);
}
