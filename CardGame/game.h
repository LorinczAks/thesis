#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <card.h>

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructor
    Game(QWidget * parent=NULL);

    // methods
    void displayMenu();
    QString getWhoseTurn();
    void setWhoseTurn(QString player);
    void pickUpCard(Card* card);
    void placeCard(Card* cardToReplace);

    // attributes
    QGraphicsScene * scene;
    Card* selectedCard;
    QPointF originalPos;
    Card* activeCard;

    // events
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);
public slots:
    void start();
private:

    void drawGUI();
    void initDecks();
    QString whoseTurn;
    QGraphicsTextItem* whoseTurnText;
    QList<Card*> tableDeck;
    QList<Card*> playerDeck;
};

#endif // GAME_H
