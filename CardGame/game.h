#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <card.h>

class Game: public QGraphicsView{
public:
    // constructor
    Game(QWidget * parent=NULL);

    // methods
    void displayMenu();
    QString getWhoseTurn();
    void setWhoseTurn(QString player);

    // attributes
    QGraphicsScene * scene;
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
