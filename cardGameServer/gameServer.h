#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "card.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class gameServer : public QObject
{
    Q_OBJECT
public:
    explicit gameServer(int port, QObject *parent = nullptr);
    bool isStarted() const;
    bool isGameOnline() const;
    QString getWhoseTurn();
    void setWhoseTurn(QString player);
    void sendToCl(QString message, QTcpSocket* player);
    int receivedData;
    void handleClientRequest(QTcpSocket* sender, const QString& request);
    void sendConStatus(QTcpSocket* targetClient);
    void handleConnection(QTcpSocket* player, const QString& request);
    void sendPlayerCards(QTcpSocket* player);
    void handleCardPlacing(QTcpSocket* player, const QString& request);
    void handleDrawingFromDeck(QTcpSocket* player);
    void handleAskingForKind(QTcpSocket* player, const QString& request);
    void sendShutDownMsg();
signals:
    void newClientConnected();
    void clientDisconnect();
    void dataReceived(QString message);
    void nextRound();
    void sevenPlayed();
    void askForKindPlayed();
    void acePlayed();

private slots:
    void on_client_connecting();

    void clientDisconnected();

    void clientDataReady();

    void onNextRound();
    void drawTwo();
    void askForKind();
    void noTurn();


private:
    QTcpServer *_server;
    bool _isStarted;
    QString whoseTurn;
    bool _gameOnline;
    // methods
    void initDecks();
    // attributes
    QList<Card*> tableDeck;
    QList<Card*> player1Deck;
    QList<Card*> player2Deck;
    Card* activeCard;
    QTcpSocket* player1Socket = nullptr;
    QTcpSocket* player2Socket = nullptr;
    QString player1Name;
    QString player2Name;
    QString kindModifier;
};

#endif // GAMESERVER_H
