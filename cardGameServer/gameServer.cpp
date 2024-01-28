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
    initDecks();
    connect(this, &gameServer::nextRound, this, &gameServer::onNextRound);

    connect(this, &gameServer::sevenPlayed, this, &gameServer::drawTwo);
    connect(this, &gameServer::askForKindPlayed, this, &gameServer::askForKind);
    connect(this, &gameServer::acePlayed, this, &gameServer::noTurn);
    kindModifier = "";
    _gameOnline = false;
}

void gameServer::on_client_connecting()
{
    if (player1Socket && player2Socket) {
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
    if (!player1Socket) {
        player1Socket = socket;
        connect(player1Socket, &QTcpSocket::readyRead, this, &gameServer::clientDataReady);
        connect(player1Socket, &QTcpSocket::disconnected, this, &gameServer::clientDisconnected);
    } else if (!player2Socket) {
        player2Socket = socket;
        connect(player2Socket, &QTcpSocket::readyRead, this, &gameServer::clientDataReady);
        connect(player2Socket, &QTcpSocket::disconnected, this, &gameServer::clientDisconnected);
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
            if (senderSocket == player1Socket) {
                qDebug() << "Player 1 disconnected.";
                player1Socket = nullptr;
            } else if (senderSocket == player2Socket) {
                qDebug() << "Player 2 disconnected.";
                player2Socket = nullptr;
            }
        }
    }
    else {
        if (senderSocket == player1Socket) {
            sendToCl("GAMEEND_DC|", player2Socket);
            player1Socket = nullptr;
        } else if (senderSocket == player2Socket) {
            sendToCl("GAMEEND_DC|", player1Socket);
            player2Socket = nullptr;
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
    if(player1Deck.size() == 0) {
        sendToCl("GAMEEND_YOU|", player1Socket);
        sendToCl("GAMEEND_ENEMY|", player2Socket);
    } else if(player2Deck.size() == 0) {
        sendToCl("GAMEEND_YOU|", player2Socket);
        sendToCl("GAMEEND_ENEMY|", player1Socket);
    }
    else {
        if(getWhoseTurn() == player1Name) {
            setWhoseTurn(player2Name);
        }
        else {
            setWhoseTurn(player1Name);
        }
        sendPlayerCards(player1Socket);
        sendPlayerCards(player2Socket);
    }
}

void gameServer::drawTwo()
{
    if(player1Deck.size() == 0) {
        sendToCl("GAMEEND_YOU|", player1Socket);
        sendToCl("GAMEEND_ENEMY|", player2Socket);
        return;
    } else if(player2Deck.size() == 0) {
        sendToCl("GAMEEND_YOU|", player2Socket);
        sendToCl("GAMEEND_ENEMY|", player1Socket);
        return;
    }
    if(tableDeck.size() < 2) {
        sendPlayerCards(player1Socket);
        sendPlayerCards(player2Socket);
        return;
    }
    if(getWhoseTurn() == player1Name) {
        setWhoseTurn(player2Name);
        player2Deck.append(tableDeck.takeAt(0));
        player2Deck.append(tableDeck.takeAt(0));
        sendToCl("DRAWNTWO|", player2Socket);
    }
    else {
        setWhoseTurn(player1Name);
        player1Deck.append(tableDeck.takeAt(0));
        player1Deck.append(tableDeck.takeAt(0));
        sendToCl("DRAWNTWO|", player1Socket);
    }
    sendPlayerCards(player1Socket);
    sendPlayerCards(player2Socket);
}

void gameServer::askForKind()
{
    if(getWhoseTurn() == player1Name) {
        sendToCl("ASKFORKIND|", player1Socket);
    }
    else {
        sendToCl("ASKFORKIND|", player2Socket);
    }
}

void gameServer::noTurn()
{
    if(getWhoseTurn() == player1Name) {
        sendToCl("NOTURN|", player2Socket);
    }
    else {
        sendToCl("NOTURN|", player1Socket);
    }
    sendPlayerCards(player1Socket);
    sendPlayerCards(player2Socket);
}

void gameServer::initDecks()
{
    for(int i = 0; i < 32; i++) {
        try {
            Card* tmp_card = new Card(i);
            tableDeck.append(tmp_card);
        } catch (const std::bad_alloc& e) {
            qDebug() << "Memory allocation failed: " << e.what();
        }
    }
    std::random_shuffle(tableDeck.begin(), tableDeck.end());

    player1Deck.append(tableDeck.takeAt(0));
    player1Deck.append(tableDeck.takeAt(2));
    player1Deck.append(tableDeck.takeAt(4));
    player1Deck.append(tableDeck.takeAt(6));
    player1Deck.append(tableDeck.takeAt(8));

    player2Deck.append(tableDeck.takeAt(1));
    player2Deck.append(tableDeck.takeAt(3));
    player2Deck.append(tableDeck.takeAt(5));
    player2Deck.append(tableDeck.takeAt(7));
    player2Deck.append(tableDeck.takeAt(9));

    activeCard = tableDeck.takeAt(10);
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
    return whoseTurn;
}

void gameServer::setWhoseTurn(QString player)
{
    whoseTurn = player;
}

void gameServer::sendToCl(QString message, QTcpSocket* player)
{
    player->write(message.toUtf8());
    if(player == player1Socket) {
        qDebug() << "message: " << message.toUtf8() << " sent to client: " << player1Name;
    } else {
        qDebug() << "message: " << message.toUtf8() << " sent to client: " << player2Name;
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
        setWhoseTurn(player1Name);
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
    if(player1Socket) {
        message += "1";
    }
    if(player2Socket) {
        message += "2";
    }

    // Send the message to the target client
    targetClient->write(message.toUtf8());
}

void gameServer::handleConnection(QTcpSocket *player, const QString& request)
{
    QStringList tokens = request.split('_');
    if(player1Socket == player) {
        player1Name = tokens[1];
    }
    if(player2Socket == player) {
        player2Name = tokens[1];
    }
    //qDebug() << player << " connected, with name: " << tokens[1];
}

void gameServer::sendPlayerCards(QTcpSocket *player)
{
    QString message = QString::number(activeCard->getCode());
    message += "-";
    message += getWhoseTurn();
    if(player == player1Socket) {
        for(auto i = 0; i < player1Deck.size(); i++) {
            message += "-";
            message += QString::number(player1Deck[i]->getCode());
        }
        //qDebug() << "sent cards message: " << message << " to " << player1Name;
    }
    else if(player == player2Socket) {
        for(auto i = 0; i < player2Deck.size(); i++) {
            message += "-";
            message += QString::number(player2Deck[i]->getCode());
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
    if(kindModifier == "hearts") {
        if(tmpCard->passesTo(new Card(5))) {
            //qDebug() << tmpCard->getDescription() << " passes to " << activeCard->getDescription();
            tableDeck.append(activeCard);
            std::random_shuffle(tableDeck.begin(), tableDeck.end());

            if(player == player1Socket) {
                for(auto i = 0; i < player1Deck.size(); i++) {
                    if(player1Deck[i]->getCode() == tmpCard->getCode()) {
                        activeCard = player1Deck[i];
                        player1Deck.removeAll(player1Deck[i]);
                    }
                }
            }
            else if(player == player2Socket) {
                for(auto i = 0; i < player2Deck.size(); i++) {
                    if(player2Deck[i]->getCode() == tmpCard->getCode()) {
                        activeCard = player2Deck[i];
                        player2Deck.removeAll(player2Deck[i]);
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
            kindModifier = "";
        } else {
            sendToCl("PLACING_FAILURE|", player);
        }
    } else if(kindModifier == "green") {
        if(tmpCard->passesTo(new Card(21))) {
            //qDebug() << tmpCard->getDescription() << " passes to " << activeCard->getDescription();
            tableDeck.append(activeCard);
            std::random_shuffle(tableDeck.begin(), tableDeck.end());

            if(player == player1Socket) {
                for(auto i = 0; i < player1Deck.size(); i++) {
                    if(player1Deck[i]->getCode() == tmpCard->getCode()) {
                        activeCard = player1Deck[i];
                        player1Deck.removeAll(player1Deck[i]);
                    }
                }
            }
            else if(player == player2Socket) {
                for(auto i = 0; i < player2Deck.size(); i++) {
                    if(player2Deck[i]->getCode() == tmpCard->getCode()) {
                        activeCard = player2Deck[i];
                        player2Deck.removeAll(player2Deck[i]);
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
            kindModifier = "";
        } else {
            sendToCl("PLACING_FAILURE|", player);
        }
    } else if(kindModifier == "pumpkin") {
        if(tmpCard->passesTo(new Card(13))) {
            //qDebug() << tmpCard->getDescription() << " passes to " << activeCard->getDescription();
            tableDeck.append(activeCard);
            std::random_shuffle(tableDeck.begin(), tableDeck.end());

            if(player == player1Socket) {
                for(auto i = 0; i < player1Deck.size(); i++) {
                    if(player1Deck[i]->getCode() == tmpCard->getCode()) {
                        activeCard = player1Deck[i];
                        player1Deck.removeAll(player1Deck[i]);
                    }
                }
            }
            else if(player == player2Socket) {
                for(auto i = 0; i < player2Deck.size(); i++) {
                    if(player2Deck[i]->getCode() == tmpCard->getCode()) {
                        activeCard = player2Deck[i];
                        player2Deck.removeAll(player2Deck[i]);
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
            kindModifier = "";
        } else {
            sendToCl("PLACING_FAILURE|", player);
        }
    } else if(kindModifier == "nut") {
        if(tmpCard->passesTo(new Card(29))) {
            //qDebug() << tmpCard->getDescription() << " passes to " << activeCard->getDescription();
            tableDeck.append(activeCard);
            std::random_shuffle(tableDeck.begin(), tableDeck.end());

            if(player == player1Socket) {
                for(auto i = 0; i < player1Deck.size(); i++) {
                    if(player1Deck[i]->getCode() == tmpCard->getCode()) {
                        activeCard = player1Deck[i];
                        player1Deck.removeAll(player1Deck[i]);
                    }
                }
            }
            else if(player == player2Socket) {
                for(auto i = 0; i < player2Deck.size(); i++) {
                    if(player2Deck[i]->getCode() == tmpCard->getCode()) {
                        activeCard = player2Deck[i];
                        player2Deck.removeAll(player2Deck[i]);
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
            kindModifier = "";
        } else {
            sendToCl("PLACING_FAILURE|", player);
        }
    } else {
        if(tmpCard->passesTo(activeCard)) {
            //qDebug() << tmpCard->getDescription() << " passes to " << activeCard->getDescription();
            tableDeck.append(activeCard);
            std::random_shuffle(tableDeck.begin(), tableDeck.end());

            if(player == player1Socket) {
                for(auto i = 0; i < player1Deck.size(); i++) {
                    if(player1Deck[i]->getCode() == tmpCard->getCode()) {
                        activeCard = player1Deck[i];
                        player1Deck.removeAll(player1Deck[i]);
                    }
                }
            }
            else if(player == player2Socket) {
                for(auto i = 0; i < player2Deck.size(); i++) {
                    if(player2Deck[i]->getCode() == tmpCard->getCode()) {
                        activeCard = player2Deck[i];
                        player2Deck.removeAll(player2Deck[i]);
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
    if(tableDeck.size() == 0) {
        sendToCl("NOCARDSINDECK|", player);
        return;
    }
    if(player1Socket == player) {
        player1Deck.append(tableDeck.takeAt(0));
    } else if(player2Socket == player) {
        player2Deck.append(tableDeck.takeAt(0));
    }
    emit nextRound();
}

void gameServer::handleAskingForKind(QTcpSocket *player, const QString &request)
{
    if(request == "ASKFOR_HEARTS") {
        kindModifier = "hearts";
        if(player1Socket == player) {
            sendToCl("ASKEDFOR_HEARTS|", player2Socket);
        } else if(player2Socket == player) {
            sendToCl("ASKEDFOR_HEARTS|", player1Socket);
        }
    } else if(request == "ASKFOR_GREEN") {
        kindModifier = "green";
        if(player1Socket == player) {
            sendToCl("ASKEDFOR_GREEN|", player2Socket);
        } else if(player2Socket == player) {
            sendToCl("ASKEDFOR_GREEN|", player1Socket);
        }
    } else if(request == "ASKFOR_PUMPKIN") {
        kindModifier = "pumpkin";
        if(player1Socket == player) {
            sendToCl("ASKEDFOR_PUMPKIN|", player2Socket);
        } else if(player2Socket == player) {
            sendToCl("ASKEDFOR_PUMPKIN|", player1Socket);
        }
    } else if(request == "ASKFOR_NUT") {
        kindModifier = "nut";
        if(player1Socket == player) {
            sendToCl("ASKEDFOR_NUT|", player2Socket);
        } else if(player2Socket == player) {
            sendToCl("ASKEDFOR_NUT|", player1Socket);
        }
    }

    emit nextRound();
}

void gameServer::sendShutDownMsg()
{
    sendToCl("GAMEEND_SHUTDOWN|", player1Socket);
    sendToCl("GAMEEND_SHUTDOWN|", player2Socket);
}
