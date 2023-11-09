#include "game.h"
#include "card.h"
#include "button.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QDebug>

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

    selectedCard = nullptr;
}

void Game::start(){
    //Deck* pakli = new Deck("pakli");
    initDecks();
    drawGUI();
}

void Game::drawGUI() {
    scene->clear();

    // visualize player's hand
    QWidget *widget = new QWidget;
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(widget);
    scrollArea->setStyleSheet("background-image: url(:/source/tablecover.jpg);");
    scrollArea->setGeometry(200, 550, 600, 175);


    QHBoxLayout *layout = new QHBoxLayout(widget);
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setAlignment(Qt::AlignCenter);
    for (int j = 0; j < playerDeck.size(); ++j) {
        QGraphicsScene* cardScene = new QGraphicsScene;
        QGraphicsView* view = new QGraphicsView;
        view->setScene(cardScene);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setFixedSize(80,125);
        cardScene->addItem(playerDeck[j]);

        layout->addWidget(view);
    }
    scene->addWidget(scrollArea);

    // visualize deck and enemy player's hand
    QPixmap deckImage(":/source/hatlap.jpg");
    QGraphicsPixmapItem *deckItem = scene->addPixmap(deckImage);
    deckItem->setPos(450, 50); // Set the position of the deck item
    deckItem->setScale(0.085);
    QGraphicsPixmapItem *cardBackItem = scene->addPixmap(deckImage);
    cardBackItem->setPos(800, 300); // Set the position of the card back item
    cardBackItem->setScale(0.085);

    // visualize active card
    Card *activeCardItem = activeCard;
    activeCardItem->setPos(450, 300); // Set the position of the card back item
    activeCardItem->setScale(1);
    scene->addItem(activeCardItem);

    // visualize turn info text
    whoseTurnText = new QGraphicsTextItem();
    setWhoseTurn(QString("player 1"));
    whoseTurnText->setFont(QFont("Arial", 20));
    whoseTurnText->setPos(20, 50);
    scene->addItem(whoseTurnText);
    setWhoseTurn(QString("gumi"));

}

void Game::initDecks() {
    for(int i = 0; i < 32; i++) {
        Card* tmp_card = new Card(i);
        tableDeck.append(tmp_card);
    }
    std::random_shuffle(tableDeck.begin(), tableDeck.end());
    playerDeck.append(tableDeck.takeAt(0));
    playerDeck.append(tableDeck.takeAt(1));
    playerDeck.append(tableDeck.takeAt(2));
    playerDeck.append(tableDeck.takeAt(3));
    playerDeck.append(tableDeck.takeAt(4));
    // TODO give cards to enemy player

    activeCard = tableDeck.takeAt(10);
}

void Game::displayMenu() {
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Makao"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 300;
    playButton->setPos(bxPos, byPos);
    connect(playButton, &Button::clicked, this, &Game::start);
    scene->addItem(playButton);

    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 430;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, &Button::clicked, this, &Game::close);
    scene->addItem(quitButton);
}

QString Game::getWhoseTurn() {
    return whoseTurn;
}

void Game::setWhoseTurn(QString player) {
    whoseTurn = player;
    whoseTurnText->setPlainText(player + QString("'s turn"));
}

void Game::pickUpCard(Card *card) {
    if (selectedCard == nullptr) {
        selectedCard = card;
        originalPos = card->pos();
        return;
    }
}

void Game::placeCard(Card *cardToReplace) {
    qDebug()
    << QString::fromUtf8(selectedCard->getDescription())
    << "-t akarunk rani erre: "
    << QString::fromUtf8(cardToReplace->getDescription());
    if(cardToReplace == activeCard) {
        qDebug() << "belemegy";
        if(selectedCard->passesTo(cardToReplace)) {
            qDebug() << "and they pass";
            qDebug() << QString::fromUtf8(selectedCard->getDescription()) << " card placed!";
            selectedCard->setPos(cardToReplace->pos());
            tableDeck.append(cardToReplace);
            playerDeck.removeAll(selectedCard);
            activeCard = selectedCard;
            selectedCard = nullptr;
            drawGUI();
        }
    }
}

void Game::mouseMoveEvent(QMouseEvent *event) {
    if(selectedCard) {
        selectedCard->setPos(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton){
        if (selectedCard){
            selectedCard->setPos(originalPos);
            selectedCard->setIsSelected(false);
            selectedCard = nullptr;
            return;
        }
    }

    QGraphicsView::mousePressEvent(event);
}
