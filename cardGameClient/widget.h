#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "card.h"
#include "button.h"
#include "ownClient.h"
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QListWidget>

class Widget : public QGraphicsView {
    Q_OBJECT

public:
    // constructor
    Widget(QWidget *parent = nullptr);
    // methods
    void displayMenu();
    void pickUpCard(Card* card);
    void placeCard(Card* cardToReplace);
    void mousePressEvent(QMouseEvent* event);
    QString getWhoseTurn();
    void setWhoseTurn(QString player);


    // attributes
    QString playerName;
    QList<Card*> playerDeck;
    Card* activeCard = nullptr;
    Card* selectedCard = nullptr;
    QString whoseTurn;
    Button* drawButton;
    QListWidget* chatWidget;
    // visuals
    QGraphicsScene* scene;
    QGraphicsTextItem* whoseTurnText;
    QWidget *plHandWidget;
    QHBoxLayout *plHandLayout;
    QScrollArea *plHandScrollArea;
    OwnClient client;
    //destructor
    ~Widget();
signals:
    // we click the connect button
    void tryToConnect(QString name, QString ip, int port);
    // we place a card of our own onto the active card
    void placeCardSignal(QString cardCode);
    // we click the deck to draw a card
    void drawFromDeck();
    // we ask for hearts
    void askForHearts();
    // we ask for green
    void askForGreen();
    // we ask for pumpkin
    void askForPumpkin();
    // we ask for Nut
    void askForNut();
public slots:
    // we show the waiting for other player screen
    void displayWaiting();
    // we ask for cards from the server
    void requestCards();
    // we show the game gui
    void drawStartingGUI(QString cardsInfo);
    // we update the game gui to show the current cards
    void drawUpdateGUI(QString cardsInfo);
    // we clear the scene and make winner announcement
    void drawEndingGUI(QString winner);
    // we show the connection page
    void drawConnectionGUI();
    // we draw ask for kind panel
    void drawAskForKindGUI();
    // we show the server full
    void displayServerFull();
};

#endif // WIDGET_H
