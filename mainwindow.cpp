#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->stackedWidget->setCurrentIndex(static_cast<int>(ScreenName::PROXY) );

    setScreen(ScreenName::PROXY);
    //connect(&proxy,SIGNAL(textReceived(QString)),this, SLOT(on_textReceived(QString)), Qt::QueuedConnection);

    //interface mostra o request quando o proxy manda
    connect(&proxy, SIGNAL(requestReceived(QString)),this, SLOT(on_requestReceived(QString)), Qt::QueuedConnection);

    //conecta botao à acão do proxy
    connect(this, SIGNAL(sendRequestAndReply(QString,QString)), &proxy, SLOT(on_buttonPressed(QString,QString)), Qt::QueuedConnection);

    //ao enviar o request, desabilita o botao e a edicao do request
    connect(&proxy, SIGNAL(requestSent()),this, SLOT(on_requestSent()), Qt::QueuedConnection);

    //interface mostra o reply e habilita o botao
     connect(&proxy, SIGNAL(replyReceived(QString)),this, SLOT(on_replyReceived(QString)), Qt::QueuedConnection);

     //ao enviar o reply para o client, inicia novamente
     connect(&proxy, SIGNAL(replyRetrieved()),this, SLOT(on_replyRetrieved()), Qt::QueuedConnection);




}

MainWindow::~MainWindow()
{
    delete ui;
}

//methods

void MainWindow::setScreen(ScreenName screenName){


    proxy.stop();
    if(proxyThread.isRunning()){
        proxyThread.terminate();
  //      proxy.close_sockets();
    }


    webtools.stop();

    switch(screenName){

        case ScreenName::PROXY:
            qDebug() << "Proxy";

           ui->plainTextEdit->setPlainText("");
           ui->plainTextEdit_2->setPlainText("");
           // if(proxyThread.isRunning())
           //     proxyThread.wait();

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
    ui->pushButton->setDisabled(false);

}

void MainWindow::on_requestReceived(QString req){
    ui->plainTextEdit->document()->setPlainText(req);
    ui->pushButton->setText("Send request");

    ui->pushButton->setDisabled(false);
    ui->plainTextEdit_2->setDisabled(true);
    ui->plainTextEdit->setDisabled(false);

}

void MainWindow::on_requestSent(){
    ui->plainTextEdit->setDisabled(true);
    //ui->pushButton->setDisabled(true);

   //ui->pushButton->setText("retrieve reply");
}

void MainWindow::on_replyReceived(QString reply){

    ui->plainTextEdit_2->document()->setPlainText(reply);
    ui->plainTextEdit_2->setDisabled(false);
    ui->plainTextEdit->setDisabled(true);


    ui->pushButton->setText("Retrieve reply");
    ui->pushButton->setDisabled(false);
}

void MainWindow::on_replyRetrieved(){
    ui->plainTextEdit->setDisabled(true);
    ui->plainTextEdit_2->setDisabled(true);
    ui->pushButton->setDisabled(true);
}


void MainWindow::on_pushButton_clicked()
{
    //qDebug() << "clicou";
    emit sendRequestAndReply(ui->plainTextEdit->toPlainText(), ui->plainTextEdit_2->toPlainText() );
    ui->pushButton->setDisabled(true);
    //emit sendRequest("TESTE");
}
