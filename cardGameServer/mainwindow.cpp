#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _server = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnStartServer_clicked()
{
    if (_server == nullptr) {
        auto port =ui->spnServerPort->value();
        _server = new gameServer(port);
        connect(_server, &gameServer::newClientConnected, this, &MainWindow::newClientConnected);
        connect(_server, &gameServer::dataReceived, this, &MainWindow::clientDataReceived);
        connect(_server, &gameServer::clientDisconnect, this, &MainWindow::clientDisconnected);

    }
    auto state = (_server->isStarted())? "1" : "0";
    ui->lblConnectionStatus->setProperty("state", state);
    style()->polish(ui->lblConnectionStatus);


}

void MainWindow::newClientConnected()
{
    ui->lstConsole->addItem("New Client connected");
}




void MainWindow::on_btnSendToAll_clicked()
{
    /*
    auto message = ui->lnMessage->text().trimmed();
    _server->sendToAll(message);
    */
}

void MainWindow::clientDisconnected()
{
    ui->lstConsole->addItem("Client Disconnected");
}

void MainWindow::clientDataReceived(QString message)
{
    ui->lstConsole->addItem(message);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    _server->sendShutDownMsg();
    QMainWindow::closeEvent(event);
}
