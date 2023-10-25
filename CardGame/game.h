#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

class Game: public QGraphicsView{
public:
    // constructor
    Game(QWidget * parent=NULL);

    // methods
    void start();

    // attributes
    QGraphicsScene * scene;
    //CardTable* table; TODO
    QString whosTurn;

};

#endif // GAME_H
