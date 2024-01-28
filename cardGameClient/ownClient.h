#ifndef OWNCLIENT_H
#define OWNCLIENT_H

#include <QObject>
#include <QTcpSocket>

class OwnClient : public QObject
{
    Q_OBJECT
public:
    explicit OwnClient(QObject *parent = nullptr);

    void disconnect();
    QAbstractSocket::SocketState state();
    void send(QString message);
    void requestConnectionStatus();
    void handleConnectionStatus(const QString& message);

    bool bothConnected;
    bool firstRound;

signals:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState);
    void errorOccurred(QAbstractSocket::SocketError);
    void dataReady(QByteArray);
    // when we successfully connect to the server
    void connectedToGameServer();
    // when we have to wait for other player to connect
    void enemyNotConnected();
    // when the game starts
    void gameCanStart();
    // card info received from server
    void cardsReady(QString cardsInfo);
    // unable to draw from deck
    void cantDrawFromDeck();
    // game server is full
    void serverFull();

    // when its next turn
    void nextTurn(QString cardsInfo);
    // when the game ends
    void gameEnded(QString winner);
    // when the card we try to place doesn't pass
    void cardNotPass();
    // enemy played a seven
    void sevenPlayedByEnemy();
    // enemy played an ace
    void acePlayedByEnemy();
    // you played an ask for kind
    void askForKind();
    // enemy asked for kind hearts
    void enemyAskedForHearts();
    // enemy asked for kind green
    void enemyAskedForGreen();
    // enemy asked for kind pumpkin
    void enemyAskedForPumpkin();
    // enemy asked for kind nut
    void enemyAskedForNut();

public slots:
    void socket_stateChanged(QAbstractSocket::SocketState state);
    void socket_readyRead();
    // we try to connect to the server
    void connectToDevice(QString name, QString ip, int port);
    // we send the placed card to the server
    void sendPlacedCard(QString cardCode);
    // we send a draw card request to the server
    void sendDrawCardRequest();
    // we tell the server we ask for hearts
    void askedForHearts();
    // we tell the server we ask for green
    void askedForGreen();
    // we tell the server we ask for pumpkin
    void askedForPumpkin();
    // we tell the server we ask for nut
    void askedForNut();
private:
    bool gameIsStarted;
    QTcpSocket _socket;
    QString name;
    QString _ip;
    int _port;
};

#endif // OWNCLIENT_H
