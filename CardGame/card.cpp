#include "card.h"
#include "game.h"
#include <QGraphicsScene>
#include <QPen>
#include <iostream>

extern Game* game;

Card::Card( int code, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    this->code = code; // "7"
    switch (code) {
        case 0:
            description = "Piros Hetes";
            kind = "Piros";
            value = 7;
            picture = "::/source/Piros7.png";
            specialAttribute = "drawtwo";
            setPixmap(QPixmap(":/source/Piros7.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 1:
            description = "Piros Nyolcas";
            kind = "Piros";
            value = 8;
            picture = ":/source/Piros8.png";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Piros8.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 2:
            description = "Piros Kilences";
            kind = "Piros";
            value = 9;
            picture = ":/source/Piros9.png";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Piros9.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 3:
            description = "Piros Tizes";
            kind = "Piros";
            value = 10;
            picture = ":/source/Piros10.png";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Piros10.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 4:
            description = "Piros Alsó";
            kind = "Piros";
            value = 11;
            picture = ":/source/PirosAls.png";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/PirosAls.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 5:
            description = "Piros Felső";
            kind = "Piros";
            value = 12;
            picture = ":/source/PirosFel.png";
            specialAttribute = "askforkind";
            setPixmap(QPixmap(":/source/PirosFel.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 6:
            description = "Piros Király";
            kind = "Piros";
            value = 13;
            picture = ":/source/PirosKir.png";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/PirosKir.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 7:
            description = "Piros Ász";
            kind = "Piros";
            value = 14;
            picture = ":/source/PirosAsz.png";
            specialAttribute = "outofturn";
            setPixmap(QPixmap(":/source/PirosAsz.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 8:
            description = "Tök Hetes";
            kind = "Tök";
            value = 7;
            picture = ":/source/Tok7.png";
            specialAttribute = "drawtwo";
            setPixmap(QPixmap(":/source/Tok7.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 9:
            description = "Tök Nyolcas";
            kind = "Tök";
            value = 8;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Tok8.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 10:
            description = "Tök Kilences";
            kind = "Tök";
            value = 9;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Tok9.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 11:
            description = "Tök Tizes";
            kind = "Tök";
            value = 10;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Tok10.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 12:
            description = "Tök Alsó";
            kind = "Tök";
            value = 11;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/TokAls.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 13:
            description = "Tök Felső";
            kind = "Tök";
            value = 12;
            picture = ":/images/kartya.jpg";
            specialAttribute = "askforkind";
            setPixmap(QPixmap(":/source/TokFel.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 14:
            description = "Tök Király";
            kind = "Tök";
            value = 13;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/TokKir.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 15:
            description = "Tök Ász";
            kind = "Tök";
            value = 14;
            picture = ":/images/kartya.jpg";
            specialAttribute = "outofturn";
            setPixmap(QPixmap(":/source/TokAsz.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 16:
            description = "Zöld Hetes";
            kind = "Zöld";
            value = 7;
            picture = ":/images/kartya.jpg";
            specialAttribute = "drawtwo";
            setPixmap(QPixmap(":/source/Zold7.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 17:
            description = "Zöld Nyolcas";
            kind = "Zöld";
            value = 8;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Zold8.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 18:
            description = "Zöld Kilences";
            kind = "Zöld";
            value = 9;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Zold9.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 19:
            description = "Zöld Tizes";
            kind = "Zöld";
            value = 10;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Zold10.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 20:
            description = "Zöld Alsó";
            kind = "Zöld";
            value = 11;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/ZoldAls.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 21:
            description = "Zöld Felső";
            kind = "Zöld";
            value = 12;
            picture = ":/images/kartya.jpg";
            specialAttribute = "askforkind";
            setPixmap(QPixmap(":/source/ZoldFel.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 22:
            description = "Zöld Király";
            kind = "Zöld";
            value = 13;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/ZoldKir.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 23:
            description = "Zöld Ász";
            kind = "Zöld";
            value = 14;
            picture = ":/images/kartya.jpg";
            specialAttribute = "outofturn";
            setPixmap(QPixmap(":/source/ZoldAsz.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 24:
            description = "Makk Hetes";
            kind = "Makk";
            value = 7;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Makk7.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 25:
            description = "Makk Nyolcas";
            kind = "Makk";
            value = 8;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Makk8.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 26:
            description = "Makk Kilences";
            kind = "Makk";
            value = 9;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Makk9.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 27:
            description = "Makk Tizes";
            kind = "Makk";
            value = 10;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/Makk10.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 28:
            description = "Makk Alsó";
            kind = "Makk";
            value = 11;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/MakkAls.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 29:
            description = "Makk Felső";
            kind = "Makk";
            value = 12;
            picture = ":/images/kartya.jpg";
            specialAttribute = "askforkind";
            setPixmap(QPixmap(":/source/MakkFel.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 30:
            description = "Makk Király";
            kind = "Makk";
            value = 13;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/source/MakkKir.png"));
            owner = "pakli";
            isSelected = false;
            break;
        case 31:
            description = "Makk Ász";
            kind = "Makk";
            value = 14;
            picture = ":/images/kartya.jpg";
            specialAttribute = "outofturn";
            setPixmap(QPixmap(":/source/MakkAsz.png"));
            owner = "pakli";
            isSelected = false;
            break;
        default:
            std::cerr << "Invalid card code!" << std::endl;
    }
}

std::string Card::getKind() {
    return this->kind;
}

int Card::getValue() {
    return this->value;
}

int Card::getCode() {
    return code;
}

std::string Card::getDescription() {
    return description;
}

bool Card::getIsSelected() {
    return isSelected;
}

void Card::setIsSelected(bool b) {
    isSelected = b;
}

bool Card::passesTo(Card *c) {
    qDebug() << this->specialAttribute << " "
        << this->kind << " "
        << c->getKind() << " "
        << this->value << " "
        << c->getValue();
    if(this->specialAttribute == "askforkind"
        || this->kind == c->getKind()
        || this->value == c->getValue()) {
        qDebug() << this->description << " passes to " << c->description;
        return true;
    }
    return false;
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(game->selectedCard == nullptr) {
        game->pickUpCard(this);
        setIsSelected(true);
        qDebug() << QString::fromUtf8(game->selectedCard->description) << " is selected card!";

        qDebug() << QString::fromUtf8(game->activeCard->description) << " is active card!";
    }
    else {
        game->placeCard(this);
    }
}
