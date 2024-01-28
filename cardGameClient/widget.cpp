#include "widget.h"
#include "button.h"
#include <QGraphicsProxyWidget>
#include <QLineEdit>

Widget::Widget(QWidget *parent) {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setBackgroundBrush(QBrush(QImage(":source/tablecover.jpg")));

    // make the newly created scene the scene to visualize (since Widget is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);

    selectedCard = nullptr;

    // signals and slots to connect

    // signals from client class to widget slots
    connect(&client, &OwnClient::enemyNotConnected, this, &Widget::displayWaiting);

    connect(&client, &OwnClient::gameCanStart, this, &Widget::requestCards);
    connect(&client, &OwnClient::cardsReady, this, &Widget::drawStartingGUI);
    connect(&client, &OwnClient::nextTurn, this, &Widget::drawUpdateGUI);
    connect(&client, &OwnClient::gameEnded, this, &Widget::drawEndingGUI);
    connect(&client, &OwnClient::cardNotPass, [=]() {
        chatWidget->addItem("A kijátszott kártya nem passzol. Próbálj másikat.");
    });
    connect(&client, &OwnClient::sevenPlayedByEnemy, [=]() {
        chatWidget->addItem("Ellenfeled hetest játszott ki. Húznod kellett kettő lapot a pakliból.");
    });
    connect(&client, &OwnClient::acePlayedByEnemy, [=]() {
        chatWidget->addItem("Ellenfeled ászt játszott ki. Egy körből kimaradsz.");
    });
    connect(&client, &OwnClient::askForKind, this, &Widget::drawAskForKindGUI);
    connect(&client, &OwnClient::enemyAskedForHearts, [=]() {
        chatWidget->addItem("Ellenfeled piros színt kért.");
    });
    connect(&client, &OwnClient::enemyAskedForGreen, [=]() {
        chatWidget->addItem("Ellenfeled zöld színt kért.");
    });
    connect(&client, &OwnClient::enemyAskedForPumpkin, [=]() {
        chatWidget->addItem("Ellenfeled tök színt kért.");
    });
    connect(&client, &OwnClient::enemyAskedForNut, [=]() {
        chatWidget->addItem("Ellenfeled makk színt kért.");
    });
    connect(&client, &OwnClient::cantDrawFromDeck, [=]() {
        chatWidget->addItem("Nincs már lap a pakliban, nem tudsz húzni.");
    });

    connect(&client, &OwnClient::serverFull, this, &Widget::displayServerFull);

    // signals from widget class to client slots
    connect(this, &Widget::tryToConnect, &client, &OwnClient::connectToDevice);
    connect(this, &Widget::placeCardSignal, &client, &OwnClient::sendPlacedCard);
    connect(this, &Widget::drawFromDeck, &client, &OwnClient::sendDrawCardRequest);

    connect(this, &Widget::askForHearts, &client, &OwnClient::askedForHearts);
    connect(this, &Widget::askForGreen, &client, &OwnClient::askedForGreen);
    connect(this, &Widget::askForPumpkin, &client, &OwnClient::askedForPumpkin);
    connect(this, &Widget::askForNut, &client, &OwnClient::askedForNut);

}

void Widget::displayMenu() {
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Makaó"));
    QFont titleFont("Arial", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    Button* playButton = new Button(200, 50, QString("Játék"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 300;
    playButton->setPos(bxPos, byPos);
    connect(playButton, &Button::clicked, this, &Widget::drawConnectionGUI);
    scene->addItem(playButton);

    Button* quitButton = new Button(200, 50, QString("Kilépés"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 430;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, &Button::clicked, this, &Widget::close);
    scene->addItem(quitButton);
}

void Widget::displayWaiting()
{
    scene->clear();
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Várakozás a másik játékosra"));
    QFont titleFont("Arial", 30);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 300;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);
}

void Widget::pickUpCard(Card *card)
{
    if (selectedCard == nullptr) {
        selectedCard = card;
        return;
    }
}

void Widget::placeCard(Card *cardToReplace)
{
    if(cardToReplace == activeCard) {
        emit placeCardSignal(QString::number(selectedCard->getCode()));
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton){
        if (selectedCard){
            selectedCard->setIsSelected(false);
            selectedCard->setOpacity(1.0);
            selectedCard = nullptr;
            return;
        }
    }
    QGraphicsView::mousePressEvent(event);
}

QString Widget::getWhoseTurn()
{
    return whoseTurn;
}

void Widget::setWhoseTurn(QString player)
{
    whoseTurn = player;
}

Widget::~Widget() {
    scene->clear();
}


void Widget::requestCards()
{
    client.send(QString("GET_INITIAL_DECKS"));
}

void Widget::drawStartingGUI(QString cardsInfo)
{
    scene->clear();
    QStringList cards = cardsInfo.split('-');

    // visualize whose turn it is
    whoseTurnText = new QGraphicsTextItem();
    whoseTurnText->setPlainText(cards[1] + QString(" köre"));
    whoseTurnText->setFont(QFont("Arial", 20));
    whoseTurnText->setPos(20, 50);
    scene->addItem(whoseTurnText);
    setWhoseTurn(cards[1]);

    // visualize chatbox
    chatWidget = new QListWidget();
    chatWidget->setGeometry(20, 100, 300, 350);
    chatWidget->setMaximumWidth(300);
    chatWidget->setWordWrap(true);
    scene->addWidget(chatWidget);

    // visualize player's hand
    for (int j = 2; j < cards.size(); ++j) {
        playerDeck.append(new Card(cards[j].toInt()));
    }
    plHandWidget = new QWidget;
    plHandScrollArea = new QScrollArea;
    plHandScrollArea->setWidgetResizable(true);
    plHandScrollArea->setWidget(plHandWidget);
    plHandScrollArea->setStyleSheet("background-image: url(:source/tablecover.jpg);");
    plHandScrollArea->setGeometry(200, 550, 600, 175);
    plHandLayout = new QHBoxLayout(plHandWidget);

    for (int j = 0; j < playerDeck.size(); ++j) {
        QGraphicsScene* cardScene = new QGraphicsScene;
        QGraphicsView* view = new QGraphicsView;
        view->setScene(cardScene);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setFixedSize(80,125);
        cardScene->addItem(playerDeck[j]);
        plHandLayout->addWidget(view);
    }

    scene->addWidget(plHandScrollArea);

    // visualize enemy player's hand and deck
    QPixmap deckImage(":source/hatlap.jpg");
    // enemy player's hand
    QGraphicsPixmapItem *enemyHandItem = scene->addPixmap(deckImage);
    enemyHandItem->setPos(450, 50);
    enemyHandItem->setScale(0.08);
    // deck
    QGraphicsPixmapItem *deckItem = scene->addPixmap(deckImage);
    deckItem->setPos(800, 300);
    deckItem->setScale(0.08);

    // make the deck a clickable button
    drawButton = new Button(82, 127, QString(""));
    drawButton->setPos(800, 300);
    connect(drawButton, &Button::clicked, this, &Widget::drawFromDeck);
    drawButton->setOpacity(0.01);

    if(getWhoseTurn() == playerName) {
        scene->addItem(drawButton);
    }

    // visualize active card
    activeCard = new Card(cards[0].toInt());
    activeCard->setPos(450, 300);
    scene->addItem(activeCard);
}

void Widget::drawUpdateGUI(QString cardsInfo)
{
    // clearing used items
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (dynamic_cast<QGraphicsPixmapItem*>(item) != nullptr) {
            scene->removeItem(item);

        }
    }
    // deleting the cards from our hand, the scrollable area
    QList<QGraphicsView*> views = plHandScrollArea->findChildren<QGraphicsView*>();
    for (QGraphicsView* view : views) {
        plHandLayout->removeWidget(view);
        delete view;
    }

    playerDeck.clear();
    selectedCard = nullptr;
    delete drawButton;


    QStringList cards = cardsInfo.split('-');
    // visualize whose turn it is
    whoseTurnText->setPlainText(cards[1] + QString(" köre"));
    whoseTurnText->setFont(QFont("Arial", 20));
    whoseTurnText->setPos(20, 50);
    scene->addItem(whoseTurnText);
    setWhoseTurn(cards[1]);

    for (int j = 2; j < cards.size(); ++j) {
        playerDeck.append(new Card(cards[j].toInt()));
    }

    for (int j = 0; j < playerDeck.size(); ++j) {
        QGraphicsScene* cardScene = new QGraphicsScene;
        QGraphicsView* view = new QGraphicsView;
        view->setScene(cardScene);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setFixedSize(80,125);
        cardScene->addItem(playerDeck[j]);
        plHandLayout->addWidget(view);
    }


    // visualize enemy player's hand and deck
    QPixmap deckImage(":source/hatlap.jpg");
    // enemy player's hand
    QGraphicsPixmapItem *enemyHandItem = scene->addPixmap(deckImage);
    enemyHandItem->setPos(450, 50);
    enemyHandItem->setScale(0.08);
    // deck
    QGraphicsPixmapItem *deckItem = scene->addPixmap(deckImage);
    deckItem->setPos(800, 300);
    deckItem->setScale(0.08);
    // draw from deck button
    drawButton = new Button(82, 127, QString(""));
    int bxPos = 800;
    int byPos = 300;
    drawButton->setRect(0,0,82,127);
    drawButton->setPos(bxPos, byPos);
    connect(drawButton, &Button::clicked, this, &Widget::drawFromDeck);
    drawButton->setOpacity(0.01);

    if(getWhoseTurn() == playerName) {
        scene->addItem(drawButton);
    }

    // visualize active card
    delete activeCard;
    activeCard = new Card(cards[0].toInt());
    activeCard->setPos(450, 300);
    scene->addItem(activeCard);
}

void Widget::drawEndingGUI(QString winner)
{
    scene->clear();
    QGraphicsTextItem* winnerText = new QGraphicsTextItem();
    if(winner == "GAMEEND_YOU") {
        winnerText->setPlainText("Nyertél!");
    }
    else if(winner == "GAMEEND_ENEMY") {
        winnerText->setPlainText("Ellenfeled nyert. Több szerencsét legközelebb.");
    }
    else if(winner == "GAMEEND_DC"){
        winnerText->setPlainText("Lekapcsolódott az ellenfél, indítson új szervert a játékhoz");
    }
    else if(winner == "GAMEEND_SHUTDOWN"){
        winnerText->setPlainText("A szerver leállt, indítson új szervert a játékhoz");
    }
    winnerText->setFont(QFont("Arial", 20));
    int txPos = this->width()/2 - winnerText->boundingRect().width()/2;
    int tyPos = 300;
    winnerText->setPos(txPos, tyPos);
    scene->addItem(winnerText);
}

void Widget::drawConnectionGUI()
{
    scene->clear();

    QGraphicsTextItem* nameLabel = new QGraphicsTextItem("Név:");
    QGraphicsTextItem* ipLabel = new QGraphicsTextItem("IP:");
    QGraphicsTextItem* portLabel = new QGraphicsTextItem("Port:");

    // setup the labels' font
    QFont font = nameLabel->font();
    font.setBold(true);
    nameLabel->setFont(font);
    ipLabel->setFont(font);
    portLabel->setFont(font);

    nameLabel->setDefaultTextColor(Qt::white);
    ipLabel->setDefaultTextColor(Qt::white);
    portLabel->setDefaultTextColor(Qt::white);

    // Set positions for labels
    nameLabel->setPos(350, 250);
    ipLabel->setPos(350, 300);
    portLabel->setPos(350, 350);

    // Add labels to the scene
    scene->addItem(nameLabel);
    scene->addItem(ipLabel);
    scene->addItem(portLabel);

    // Create text input fields
    QLineEdit* nameInput = new QLineEdit();
    QLineEdit* ipInput = new QLineEdit();
    QLineEdit* portInput = new QLineEdit();

    // Create graphics proxy widgets for text input fields
    QGraphicsProxyWidget* nameProxy = scene->addWidget(nameInput);
    QGraphicsProxyWidget* ipProxy = scene->addWidget(ipInput);
    QGraphicsProxyWidget* portProxy = scene->addWidget(portInput);

    // Set positions for text input fields
    nameProxy->setPos(400, 250);
    ipProxy->setPos(400, 300);
    portProxy->setPos(400, 350);

    Button* connectButton = new Button(200, 50, QString("Csatlakozás"));
    connectButton->setPos(400, 500);
    connect(connectButton, &Button::clicked, [=]() {
        QString name = nameInput->text();
        QString ip = ipInput->text();
        int port = portInput->text().toInt();


        client.connectToDevice(name, ip, port);
        playerName = name;
    });
    scene->addItem(connectButton);
}

void Widget::drawAskForKindGUI()
{
    // background
    QGraphicsRectItem *rectItem = new QGraphicsRectItem(350, 250, 300, 200);
    rectItem->setPen(QPen(Qt::black));
    rectItem->setBrush(QBrush(Qt::white));
    scene->addItem(rectItem);

    QGraphicsTextItem *textItem = new QGraphicsTextItem("Milyen színt kérsz?", rectItem);
    textItem->setPos(355, 255);
    scene->addItem(textItem);


    Button* kindRedButton = new Button(100, 50, QString("Piros"), rectItem);
    kindRedButton->setPos(380, 300);
    scene->addItem(kindRedButton);
    connect(kindRedButton, &Button::clicked, this, &Widget::askForHearts);

    Button* kindGreenButton = new Button(100, 50, QString("Zöld"), rectItem);
    kindGreenButton->setPos(530, 300);
    scene->addItem(kindGreenButton);
    connect(kindGreenButton, &Button::clicked, this, &Widget::askForGreen);

    Button* kindPumpkinButton = new Button(100, 50, QString("Tök"), rectItem);
    kindPumpkinButton->setPos(380, 380);
    kindPumpkinButton->setRect(0,0,100,50);
    scene->addItem(kindPumpkinButton);
    connect(kindPumpkinButton, &Button::clicked, this, &Widget::askForPumpkin);

    Button* kindNutButton = new Button(100, 50, QString("Makk"), rectItem);
    kindNutButton->setPos(530, 380);
    scene->addItem(kindNutButton);
    connect(kindNutButton, &Button::clicked, this, &Widget::askForNut);


    connect(kindRedButton, &Button::clicked, [=]() {
        delete rectItem;
    });
    connect(kindGreenButton, &Button::clicked, [=]() {
        delete rectItem;
    });
    connect(kindPumpkinButton, &Button::clicked, [=]() {
        delete rectItem;
    });
    connect(kindNutButton, &Button::clicked, [=]() {
        delete rectItem;
    });
}

void Widget::displayServerFull()
{
    scene->clear();
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Ez a szerver megtelt.\nPróbáljon csatlakozni egy másik szerverhez."));
    QFont titleFont("Arial", 30);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 300;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);
}
