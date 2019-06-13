#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->stackedWidget->setCurrentIndex(static_cast<int>(ScreenName::PROXY) );

    setScreen(ScreenName::PROXY);
    connect(&proxy,SIGNAL(textReceived(QString)),this, SLOT(on_textReceived(QString)), Qt::QueuedConnection);



}

MainWindow::~MainWindow()
{
    delete ui;
}

//methods

void MainWindow::setScreen(ScreenName screenName){


    proxy.stop();
    webtools.stop();

    switch(screenName){

        case ScreenName::PROXY:
            qDebug() << "Proxy";

            if(proxyThread.isRunning())
                proxyThread.wait();

            proxy.doSetup(proxyThread);
            proxy.moveToThread(&proxyThread);
            proxyThread.start();
            break;

        case ScreenName::SPIDER:
            qDebug() << "Spider";

            if(webtoolsThread.isRunning())
                webtoolsThread.wait();

            webtools.doSetup(webtoolsThread, Operation::SPIDER);
            webtools.moveToThread(&webtoolsThread);
            webtoolsThread.start();
            break;

        case ScreenName::DUMP:
            qDebug() << "DUMP";

            if(webtoolsThread.isRunning())
                webtoolsThread.wait();

            webtools.doSetup(webtoolsThread, Operation::DUMP);
            webtools.moveToThread(&webtoolsThread);
            webtoolsThread.start();
            break;
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

void MainWindow::on_textReceived(QString txt){
    ui->plainTextEdit->document()->setPlainText(txt);
}

