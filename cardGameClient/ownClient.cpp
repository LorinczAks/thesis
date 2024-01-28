#include <QMetaEnum>
#include <QTimer>
#include <QRegularExpression>
#include "ownClient.h"

OwnClient::OwnClient(QObject *parent)
    : QObject{parent}
{
    gameIsStarted = false;
    firstRound = true;
    connect(&_socket, &QTcpSocket::connected, this, &OwnClient::connected);
    connect(&_socket, &QTcpSocket::disconnected, this, &OwnClient::disconnected);
    connect(&_socket, &QTcpSocket::errorOccurred, this, &OwnClient::errorOccurred);
    connect(&_socket, &QTcpSocket::stateChanged, this, &OwnClient::socket_stateChanged);
    connect(&_socket, &QTcpSocket::readyRead, this, &OwnClient::socket_readyRead);


    QTimer *connectionStatusTimer = new QTimer(this);
    connect(connectionStatusTimer, &QTimer::timeout, this, &OwnClient::requestConnectionStatus);
    connectionStatusTimer->start(1000);
}

void OwnClient::connectToDevice(QString name, QString ip, int port)
{
    if (_socket.isOpen()) {
        if (ip == _ip && port == _port) {
            return;
        }
        _socket.close();
    }
    _ip = ip;
    _port = port;
    _socket.connectToHost(_ip, _port);
    QString message = QString("CONNECTPLAYERNAMED_");
    message += name;
    send(message);
}

void OwnClient::sendPlacedCard(QString cardCode) {
    QString message = "TRYINGTOPLACE_";
    message += cardCode;
    send(message);
}

void OwnClient::sendDrawCardRequest() {
    send("DRAWFROMDECK");
}

void OwnClient::askedForHearts() {
    send("ASKFOR_HEARTS");
}

void OwnClient::askedForGreen() {
    send("ASKFOR_GREEN");
}

void OwnClient::askedForPumpkin() {
    send("ASKFOR_PUMPKIN");
}

void OwnClient::askedForNut() {
    send("ASKFOR_NUT");
}

void OwnClient::disconnect() {
    _socket.close();
}

QAbstractSocket::SocketState OwnClient::state() {
    return _socket.state();
}

void OwnClient::send(QString message) {
    _socket.write(message.toUtf8());
}

void OwnClient::requestConnectionStatus() {
    if(!gameIsStarted) {
        send("GET_CONNECTION_STATUS");
    }
}

void OwnClient::handleConnectionStatus(const QString &message) {
    QStringList tokens = message.split('_');
    if (tokens.size() == 2 && (tokens[1] == "21" || tokens[1] == "12")) {
        if(!gameIsStarted) {
            emit gameCanStart();
            gameIsStarted = true;
        }
    }
    if (tokens.size() == 2 && (tokens[1] == "1" || tokens[1] == "2")) {
        emit enemyNotConnected();
    }
}

void OwnClient::socket_stateChanged(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState) {
        _socket.close();
    }
    emit stateChanged(state);
}

void OwnClient::socket_readyRead()
{
    auto data = _socket.readAll();
    QStringList message_tokens = QString::fromUtf8(data).split("|");

    QRegularExpression regex("\\d+-\\w+(-\\d+)*");

    for(QString message : message_tokens) {
        QRegularExpressionMatch match = regex.match(message);
        if (message.startsWith("CONNECTED_")) {
            handleConnectionStatus(data);
        }
        else if(match.hasMatch()) {
            if(firstRound) {
                firstRound = false;
                emit cardsReady(message);
            }
            else {
                emit nextTurn(message);
            }
        }
        else if(message.startsWith("PLACING_FAILURE")) {
            emit cardNotPass();
        }
        else if(message.startsWith("DRAWNTWO")) {
            emit sevenPlayedByEnemy();
        }
        else if(message.startsWith("NOTURN")) {
            emit acePlayedByEnemy();
        }
        else if(message.startsWith("ASKFORKIND")) {
            emit askForKind();
        }
        else if(message.startsWith("ASKEDFOR_HEARTS")) {
            emit enemyAskedForHearts();
        }
        else if(message.startsWith("ASKEDFOR_GREEN")) {
            emit enemyAskedForGreen();
        }
        else if(message.startsWith("ASKEDFOR_PUMPKIN")) {
            emit enemyAskedForPumpkin();
        }
        else if(message.startsWith("ASKEDFOR_NUT")) {
            emit enemyAskedForNut();
        }
        else if(message.startsWith("GAMEEND_")) {
            emit gameEnded(message);
        }
        else if(message.startsWith("NOCARDSINDECK")) {
            emit cantDrawFromDeck();
        }
        else if(message.startsWith("GAMEISFULL")) {
            emit serverFull();
        }
    }

    emit dataReady(data);
}

