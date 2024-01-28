#include "gameServer.h"

gameServer::gameServer(int port, QObject *parent)
    : QObject{parent}
{
    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection, this, &gameServer::on_client_connecting);
    _isStarted = _server->listen(QHostAddress::Any, port);
    if(!_isStarted){
        qDebug() << "Server could not start";
    } else{
        qDebug() << "Server started...";
    }
    _initDecks();
    connect(this, &gameServer::nextRound, this, &gameServer::onNextRound);

    connect(this, &gameServer::sevenPlayed, this, &gameServer::drawTwo);
    connect(this, &gameServer::askForKindPlayed, this, &gameServer::askForKind);
    connect(this, &gameServer::acePlayed, this, &gameServer::noTurn);
    _kindModifier = "";
    _gameOnline = false;
}

void gameServer::on_client_connecting()
{
    if (_player1Socket && _player2Socket) {
        qDebug() << "Connection rejected. Maximum clients reached.";
        auto rejectedSocket = _server->nextPendingConnection();
        sendToCl("GAMEISFULL|", rejectedSocket);
        rejectedSocket->close();
        return;
    }
    qDebug() << "a client connected to server";
    auto socket = _server->nextPendingConnection();
    if(!socket) {
        qDebug() << "socket trying to connect is null";
        return;
    }
    if (!_player1Socket) {
        _player1Socket = socket;
        connect(_player1Socket, &QTcpSocket::readyRead, this, &gameServer::clientDataReady);
        connect(_player1Socket, &QTcpSocket::disconnected, this, &gameServer::clientDisconnected);
    } else if (!_player2Socket) {
        _player2Socket = socket;
        connect(_player2Socket, &QTcpSocket::readyRead, this, &gameServer::clientDataReady);
        connect(_player2Socket, &QTcpSocket::disconnected, this, &gameServer::clientDisconnected);
        _gameOnline = true;
    }
    else {
        qDebug() << "Something went wrong when connecting";
        return;
    }
    emit newClientConnected();
}

void gameServer::clientDisconnected()
{
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());
    if(!_gameOnline) {
        if (senderSocket) {
            if (senderSocket == _player1Socket) {
                qDebug() << "Player 1 disconnected.";
                _player1Socket = nullptr;
            } else if (senderSocket == _player2Socket) {
                qDebug() << "Player 2 disconnected.";
                _player2Socket = nullptr;
            }
        }
    }
    else {
        if (senderSocket == _player1Socket) {
            sendToCl("GAMEEND_DC|", _player2Socket);
            _player1Socket = nullptr;
        } else if (senderSocket == _player2Socket) {
            sendToCl("GAMEEND_DC|", _player1Socket);
            _player2Socket = nullptr;
        }
    }
    emit clientDisconnect();
}

void gameServer::clientDataReady()
{
    auto socket = qobject_cast<QTcpSocket *>(sender());
    auto data = QString(socket->readAll());
    handleClientRequest(socket, data);
    emit dataReceived(data);
}

void gameServer::onNextRound()
{
    if(_player1Deck.size() == 0) {
        sendToCl("GAMEEND_YOU|", _player1Socket);
        sendToCl("GAMEEND_ENEMY|", _player2Socket);
    } else if(_player2Deck.size() == 0) {
        sendToCl("GAMEEND_YOU|", _player2Socket);
        sendToCl("GAMEEND_ENEMY|", _player1Socket);
    }
    else {
        if(getWhoseTurn() == _player1Name) {
            setWhoseTurn(_player2Name);
        }
        else {
            setWhoseTurn(_player1Name);
        }
        sendPlayerCards(_player1Socket);
        sendPlayerCards(_player2Socket);
    }
}

void gameServer::drawTwo()
{
    if(_player1Deck.size() == 0) {
        sendToCl("GAMEEND_YOU|", _player1Socket);
        sendToCl("GAMEEND_ENEMY|", _player2Socket);
        return;
    } else if(_player2Deck.size() == 0) {
        sendToCl("GAMEEND_YOU|", _player2Socket);
        sendToCl("GAMEEND_ENEMY|", _player1Socket);
        return;
    }
    if(_tableDeck.size() < 2) {
        sendPlayerCards(_player1Socket);
        sendPlayerCards(_player2Socket);
        return;
    }
    if(getWhoseTurn() == _player1Name) {
        setWhoseTurn(_player2Name);
        _player2Deck.append(_tableDeck.takeAt(0));
        _player2Deck.append(_tableDeck.takeAt(0));
        sendToCl("DRAWNTWO|", _player2Socket);
    }
    else {
        setWhoseTurn(_player1Name);
        _player1Deck.append(_tableDeck.takeAt(0));
        _player1Deck.append(_tableDeck.takeAt(0));
        sendToCl("DRAWNTWO|", _player1Socket);
    }
    sendPlayerCards(_player1Socket);
    sendPlayerCards(_player2Socket);
}

void gameServer::askForKind()
{
    if(getWhoseTurn() == _player1Name) {
        sendToCl("ASKFORKIND|", _player1Socket);
    }
    else {
        sendToCl("ASKFORKIND|", _player2Socket);
    }
}

void gameServer::noTurn()
{
    if(getWhoseTurn() == _player1Name) {
        sendToCl("NOTURN|", _player2Socket);
    }
    else {
        sendToCl("NOTURN|", _player1Socket);
    }
    sendPlayerCards(_player1Socket);
    sendPlayerCards(_player2Socket);
}

void gameServer::_initDecks()
{
    for(int i = 0; i < 32; i++) {
        try {
            Card* tmp_card = new Card(i);
            _tableDeck.append(tmp_card);
        } catch (const std::bad_alloc& e) {
            qDebug() << "Memory allocation failed: " << e.what();
        }
    }
    std::random_shuffle(_tableDeck.begin(), _tableDeck.end());

    _player1Deck.append(_tableDeck.takeAt(0));
    _player1Deck.append(_tableDeck.takeAt(2));
    _player1Deck.append(_tableDeck.takeAt(4));
    _player1Deck.append(_tableDeck.takeAt(6));
    _player1Deck.append(_tableDeck.takeAt(8));

    _player2Deck.append(_tableDeck.takeAt(1));
    _player2Deck.append(_tableDeck.takeAt(3));
    _player2Deck.append(_tableDeck.takeAt(5));
    _player2Deck.append(_tableDeck.takeAt(7));
    _player2Deck.append(_tableDeck.takeAt(9));

    _activeCard = _tableDeck.takeAt(10);
}


bool gameServer::isStarted() const
{
    return _isStarted;
}

bool gameServer::isGameOnline() const
{
    return _gameOnline;
}

QString gameServer::getWhoseTurn()
{
    return _whoseTurn;
}

void gameServer::setWhoseTurn(QString player)
{
    _whoseTurn = player;
}

void gameServer::sendToCl(QString message, QTcpSocket* player)
{
    player->write(message.toUtf8());
    if(player == _player1Socket) {
        qDebug() << "message: " << message.toUtf8() << " sent to client: " << _player1Name;
    } else {
        qDebug() << "message: " << message.toUtf8() << " sent to client: " << _player2Name;
    }

}

void gameServer::handleClientRequest(QTcpSocket *sender, const QString &request)
{
    if (request == "GET_CONNECTION_STATUS") {
        sendConStatus(sender);
    } else if(request.startsWith("CONNECTPLAYERNAMED_")) {
        handleConnection(sender, request);
    }
    else if(request == "GET_INITIAL_DECKS") {
        setWhoseTurn(_player1Name);
        sendPlayerCards(sender);
    } else if(request.startsWith("TRYINGTOPLACE_")) {
        handleCardPlacing(sender, request);
    } else if(request.startsWith("DRAWFROMDECK")) {
        handleDrawingFromDeck(sender);
    } else if(request.startsWith("ASKFOR")) {
        handleAskingForKind(sender, request);
    }
}

void gameServer::sendConStatus(QTcpSocket *targetClient)
{
    // Form a message indicating connection status (similar to broadcastConnectionStatus)
    QString message = "CONNECTED_";
    if(_player1Socket) {
        message += "1";
    }
    if(_player2Socket) {
        message += "2";
    }

    // Send the message to the target client
    targetClient->write(message.toUtf8());
}

void gameServer::handleConnection(QTcpSocket *player, const QString& request)
{
    QStringList tokens = request.split('_');
    if(_player1Socket == player) {
        _player1Name = tokens[1];
    }
    if(_player2Socket == player) {
        _player2Name = tokens[1];
    }
    //qDebug() << player << " connected, with name: " << tokens[1];
}

void gameServer::sendPlayerCards(QTcpSocket *player)
{
    QString message = QString::number(_activeCard->getCode());
    message += "-";
    message += getWhoseTurn();
    if(player == _player1Socket) {
        for(auto i = 0; i < _player1Deck.size(); i++) {
            message += "-";
            message += QString::number(_player1Deck[i]->getCode());
        }
        //qDebug() << "sent cards message: " << message << " to " << _player1Name;
    }
    else if(player == _player2Socket) {
        for(auto i = 0; i < _player2Deck.size(); i++) {
            message += "-";
            message += QString::number(_player2Deck[i]->getCode());
        }
        //qDebug() << "sent cards message: " << message << " to " << player2Name;
    }
    message += "|";
    sendToCl(message, player);
}

void gameServer::handleCardPlacing(QTcpSocket *player, const QString& request)
{
    QStringList tokens = request.split('_');
    Card *tmpCard = new Card(tokens[1].toInt());
    if(_kindModifier == "hearts") {
        if(tmpCard->passesTo(new Card(5))) {
            //qDebug() << tmpCard->getDescription() << " passes to " << _activeCard->getDescription();
            _tableDeck.append(_activeCard);
            std::random_shuffle(_tableDeck.begin(), _tableDeck.end());

            if(player == _player1Socket) {
                for(auto i = 0; i < _player1Deck.size(); i++) {
                    if(_player1Deck[i]->getCode() == tmpCard->getCode()) {
                        _activeCard = _player1Deck[i];
                        _player1Deck.removeAll(_player1Deck[i]);
                    }
                }
            }
            else if(player == _player2Socket) {
                for(auto i = 0; i < _player2Deck.size(); i++) {
                    if(_player2Deck[i]->getCode() == tmpCard->getCode()) {
                        _activeCard = _player2Deck[i];
                        _player2Deck.removeAll(_player2Deck[i]);
                    }
                }
            }
            if(tokens[1] == "0"
                || tokens[1] == "8"
                || tokens[1] == "16"
                || tokens[1] == "24") {
                emit sevenPlayed();
            }
            else if(tokens[1] == "5"
                     || tokens[1] == "13"
                     || tokens[1] == "21"
                     || tokens[1] == "29") {
                emit askForKindPlayed();
            }
            else if(tokens[1] == "7"
                     || tokens[1] == "15"
                     || tokens[1] == "23"
                     || tokens[1] == "31") {
                emit acePlayed();
            }
            else {
                emit nextRound();
            }
            _kindModifier = "";
        } else {
            sendToCl("PLACING_FAILURE|", player);
        }
    } else if(_kindModifier == "green") {
        if(tmpCard->passesTo(new Card(21))) {
            //qDebug() << tmpCard->getDescription() << " passes to " << _activeCard->getDescription();
            _tableDeck.append(_activeCard);
            std::random_shuffle(_tableDeck.begin(), _tableDeck.end());

            if(player == _player1Socket) {
                for(auto i = 0; i < _player1Deck.size(); i++) {
                    if(_player1Deck[i]->getCode() == tmpCard->getCode()) {
                        _activeCard = _player1Deck[i];
                        _player1Deck.removeAll(_player1Deck[i]);
                    }
                }
            }
            else if(player == _player2Socket) {
                for(auto i = 0; i < _player2Deck.size(); i++) {
                    if(_player2Deck[i]->getCode() == tmpCard->getCode()) {
                        _activeCard = _player2Deck[i];
                        _player2Deck.removeAll(_player2Deck[i]);
                    }
                }
            }
            if(tokens[1] == "0"
                || tokens[1] == "8"
                || tokens[1] == "16"
                || tokens[1] == "24") {
                emit sevenPlayed();
            }
            else if(tokens[1] == "5"
                     || tokens[1] == "13"
                     || tokens[1] == "21"
                     || tokens[1] == "29") {
                emit askForKindPlayed();
            }
            else if(tokens[1] == "7"
                     || tokens[1] == "15"
                     || tokens[1] == "23"
                     || tokens[1] == "31") {
                emit acePlayed();
            }
            else {
                emit nextRound();
            }
            _kindModifier = "";
        } else {
            sendToCl("PLACING_FAILURE|", player);
        }
    } else if(_kindModifier == "pumpkin") {
        if(tmpCard->passesTo(new Card(13))) {
            //qDebug() << tmpCard->getDescription() << " passes to " << _activeCard->getDescription();
            _tableDeck.append(_activeCard);
            std::random_shuffle(_tableDeck.begin(), _tableDeck.end());

            if(player == _player1Socket) {
                for(auto i = 0; i < _player1Deck.size(); i++) {
                    if(_player1Deck[i]->getCode() == tmpCard->getCode()) {
                        _activeCard = _player1Deck[i];
                        _player1Deck.removeAll(_player1Deck[i]);
                    }
                }
            }
            else if(player == _player2Socket) {
                for(auto i = 0; i < _player2Deck.size(); i++) {
                    if(_player2Deck[i]->getCode() == tmpCard->getCode()) {
                        _activeCard = _player2Deck[i];
                        _player2Deck.removeAll(_player2Deck[i]);
                    }
                }
            }
            if(tokens[1] == "0"
                || tokens[1] == "8"
                || tokens[1] == "16"
                || tokens[1] == "24") {
                emit sevenPlayed();
            }
            else if(tokens[1] == "5"
                     || tokens[1] == "13"
                     || tokens[1] == "21"
                     || tokens[1] == "29") {
                emit askForKindPlayed();
            }
            else if(tokens[1] == "7"
                     || tokens[1] == "15"
                     || tokens[1] == "23"
                     || tokens[1] == "31") {
                emit acePlayed();
            }
            else {
                emit nextRound();
            }
            _kindModifier = "";
        } else {
            sendToCl("PLACING_FAILURE|", player);
        }
    } else if(_kindModifier == "nut") {
        if(tmpCard->passesTo(new Card(29))) {
            //qDebug() << tmpCard->getDescription() << " passes to " << _activeCard->getDescription();
            _tableDeck.append(_activeCard);
            std::random_shuffle(_tableDeck.begin(), _tableDeck.end());

            if(player == _player1Socket) {
                for(auto i = 0; i < _player1Deck.size(); i++) {
                    if(_player1Deck[i]->getCode() == tmpCard->getCode()) {
                        _activeCard = _player1Deck[i];
                        _player1Deck.removeAll(_player1Deck[i]);
                    }
                }
            }
            else if(player == _player2Socket) {
                for(auto i = 0; i < _player2Deck.size(); i++) {
                    if(_player2Deck[i]->getCode() == tmpCard->getCode()) {
                        _activeCard = _player2Deck[i];
                        _player2Deck.removeAll(_player2Deck[i]);
                    }
                }
            }
            if(tokens[1] == "0"
                || tokens[1] == "8"
                || tokens[1] == "16"
                || tokens[1] == "24") {
                emit sevenPlayed();
            }
            else if(tokens[1] == "5"
                     || tokens[1] == "13"
                     || tokens[1] == "21"
                     || tokens[1] == "29") {
                emit askForKindPlayed();
            }
            else if(tokens[1] == "7"
                     || tokens[1] == "15"
                     || tokens[1] == "23"
                     || tokens[1] == "31") {
                emit acePlayed();
            }
            else {
                emit nextRound();
            }
            _kindModifier = "";
        } else {
            sendToCl("PLACING_FAILURE|", player);
        }
    } else {
        if(tmpCard->passesTo(_activeCard)) {
            //qDebug() << tmpCard->getDescription() << " passes to " << _activeCard->getDescription();
            _tableDeck.append(_activeCard);
            std::random_shuffle(_tableDeck.begin(), _tableDeck.end());

            if(player == _player1Socket) {
                for(auto i = 0; i < _player1Deck.size(); i++) {
                    if(_player1Deck[i]->getCode() == tmpCard->getCode()) {
                        _activeCard = _player1Deck[i];
                        _player1Deck.removeAll(_player1Deck[i]);
                    }
                }
            }
            else if(player == _player2Socket) {
                for(auto i = 0; i < _player2Deck.size(); i++) {
                    if(_player2Deck[i]->getCode() == tmpCard->getCode()) {
                        _activeCard = _player2Deck[i];
                        _player2Deck.removeAll(_player2Deck[i]);
                    }
                }
            }
            if(tokens[1] == "0"
                || tokens[1] == "8"
                || tokens[1] == "16"
                || tokens[1] == "24") {
                emit sevenPlayed();
            }
            else if(tokens[1] == "5"
                       || tokens[1] == "13"
                       || tokens[1] == "21"
                       || tokens[1] == "29") {
                emit askForKindPlayed();
            }
            else if(tokens[1] == "7"
                     || tokens[1] == "15"
                     || tokens[1] == "23"
                     || tokens[1] == "31") {
                emit acePlayed();
            }
            else {
                emit nextRound();
            }
        }
        else {
            sendToCl("PLACING_FAILURE|", player);
        }
        delete tmpCard;
    }
}

void gameServer::handleDrawingFromDeck(QTcpSocket *player)
{
    if(_tableDeck.size() == 0) {
        sendToCl("NOCARDSINDECK|", player);
        return;
    }
    if(_player1Socket == player) {
        _player1Deck.append(_tableDeck.takeAt(0));
    } else if(_player2Socket == player) {
        _player2Deck.append(_tableDeck.takeAt(0));
    }
    emit nextRound();
}

void gameServer::handleAskingForKind(QTcpSocket *player, const QString &request)
{
    if(request == "ASKFOR_HEARTS") {
        _kindModifier = "hearts";
        if(_player1Socket == player) {
            sendToCl("ASKEDFOR_HEARTS|", _player2Socket);
        } else if(_player2Socket == player) {
            sendToCl("ASKEDFOR_HEARTS|", _player1Socket);
        }
    } else if(request == "ASKFOR_GREEN") {
        _kindModifier = "green";
        if(_player1Socket == player) {
            sendToCl("ASKEDFOR_GREEN|", _player2Socket);
        } else if(_player2Socket == player) {
            sendToCl("ASKEDFOR_GREEN|", _player1Socket);
        }
    } else if(request == "ASKFOR_PUMPKIN") {
        _kindModifier = "pumpkin";
        if(_player1Socket == player) {
            sendToCl("ASKEDFOR_PUMPKIN|", _player2Socket);
        } else if(_player2Socket == player) {
            sendToCl("ASKEDFOR_PUMPKIN|", _player1Socket);
        }
    } else if(request == "ASKFOR_NUT") {
        _kindModifier = "nut";
        if(_player1Socket == player) {
            sendToCl("ASKEDFOR_NUT|", _player2Socket);
        } else if(_player2Socket == player) {
            sendToCl("ASKEDFOR_NUT|", _player1Socket);
        }
    }

    emit nextRound();
}

void gameServer::sendShutDownMsg()
{
    sendToCl("GAMEEND_SHUTDOWN|", _player1Socket);
    sendToCl("GAMEEND_SHUTDOWN|", _player2Socket);
}
