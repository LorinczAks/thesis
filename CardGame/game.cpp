#include "game.h"
#include "card.h"
#include "deck.h"
#include <QGraphicsTextItem>
#include <QFont>

#include <QImage>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>

Game::Game(QWidget *parent){
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768); // make the scene 800x600 instead of infinity by infinity (default)
    setBackgroundBrush(QBrush(QImage(":/source/tablecover.jpg")));

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);

    QWidget *widget = new QWidget;
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(widget);
    scrollArea->setStyleSheet("background-image: url(:/source/tablecover.jpg);");
    scrollArea->setGeometry(200, 550, 600, 175);


    QHBoxLayout *layout = new QHBoxLayout(widget);
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setAlignment(Qt::AlignCenter);
    for (int j = 0; j < 15; ++j) {

        Card *tmp_card = new Card(j);
        QGraphicsScene* cardScene = new QGraphicsScene;
        QGraphicsView* view = new QGraphicsView;
        view->setScene(cardScene);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setFixedSize(80,125);
        cardScene->addItem(tmp_card);

        layout->addWidget(view);
    }
    scene->addWidget(scrollArea);
}

void Game::start(){
    //Deck* pakli = new Deck("pakli");


}
