#include "card.h"
#include "widget.h"
#include <QGraphicsScene>
#include <QPen>
#include <iostream>

extern Widget* w;

Card::Card( int code, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    this->code = code;
    switch (code) {
    case 0:
        description = "Piros Hetes";
        kind = "Piros";
        value = 7;
        setPixmap(QPixmap(":source//Piros7.png"));
        isSelected = false;
        break;
    case 1:
        description = "Piros Nyolcas";
        kind = "Piros";
        value = 8;
        setPixmap(QPixmap(":source//Piros8.png"));
        isSelected = false;
        break;
    case 2:
        description = "Piros Kilences";
        kind = "Piros";
        value = 9;
        setPixmap(QPixmap(":source//Piros9.png"));
        isSelected = false;
        break;
    case 3:
        description = "Piros Tizes";
        kind = "Piros";
        value = 10;
        setPixmap(QPixmap(":source//Piros10.png"));
        isSelected = false;
        break;
    case 4:
        description = "Piros Alsó";
        kind = "Piros";
        value = 11;
        setPixmap(QPixmap(":source//PirosAls.png"));
        isSelected = false;
        break;
    case 5:
        description = "Piros Felsõ";
        kind = "Piros";
        value = 12;
        setPixmap(QPixmap(":source//PirosFel.png"));
        isSelected = false;
        break;
    case 6:
        description = "Piros Király";
        kind = "Piros";
        value = 13;
        setPixmap(QPixmap(":source//PirosKir.png"));
        isSelected = false;
        break;
    case 7:
        description = "Piros Ász";
        kind = "Piros";
        value = 14;
        setPixmap(QPixmap(":source//PirosAsz.png"));
        isSelected = false;
        break;
    case 8:
        description = "Tök Hetes";
        kind = "Tök";
        value = 7;
        setPixmap(QPixmap(":source//Tok7.png"));
        isSelected = false;
        break;
    case 9:
        description = "Tök Nyolcas";
        kind = "Tök";
        value = 8;
        setPixmap(QPixmap(":source//Tok8.png"));
        isSelected = false;
        break;
    case 10:
        description = "Tök Kilences";
        kind = "Tök";
        value = 9;
        setPixmap(QPixmap(":source//Tok9.png"));
        isSelected = false;
        break;
    case 11:
        description = "Tök Tizes";
        kind = "Tök";
        value = 10;
        setPixmap(QPixmap(":source//Tok10.png"));
        isSelected = false;
        break;
    case 12:
        description = "Tök Alsó";
        kind = "Tök";
        value = 11;
        setPixmap(QPixmap(":source//TokAls.png"));
        isSelected = false;
        break;
    case 13:
        description = "Tök Felsõ";
        kind = "Tök";
        value = 12;
        setPixmap(QPixmap(":source//TokFel.png"));
        isSelected = false;
        break;
    case 14:
        description = "Tök Király";
        kind = "Tök";
        value = 13;
        setPixmap(QPixmap(":source//TokKir.png"));
        isSelected = false;
        break;
    case 15:
        description = "Tök Ász";
        kind = "Tök";
        value = 14;
        setPixmap(QPixmap(":source//TokAsz.png"));
        isSelected = false;
        break;
    case 16:
        description = "Zöld Hetes";
        kind = "Zöld";
        value = 7;
        setPixmap(QPixmap(":source//Zold7.png"));
        isSelected = false;
        break;
    case 17:
        description = "Zöld Nyolcas";
        kind = "Zöld";
        value = 8;
        setPixmap(QPixmap(":source//Zold8.png"));
        isSelected = false;
        break;
    case 18:
        description = "Zöld Kilences";
        kind = "Zöld";
        value = 9;
        setPixmap(QPixmap(":source//Zold9.png"));
        isSelected = false;
        break;
    case 19:
        description = "Zöld Tizes";
        kind = "Zöld";
        value = 10;
        setPixmap(QPixmap(":source//Zold10.png"));
        isSelected = false;
        break;
    case 20:
        description = "Zöld Alsó";
        kind = "Zöld";
        value = 11;
        setPixmap(QPixmap(":source//ZoldAls.png"));
        isSelected = false;
        break;
    case 21:
        description = "Zöld Felsõ";
        kind = "Zöld";
        value = 12;
        setPixmap(QPixmap(":source//ZoldFel.png"));
        isSelected = false;
        break;
    case 22:
        description = "Zöld Király";
        kind = "Zöld";
        value = 13;
        setPixmap(QPixmap(":source//ZoldKir.png"));
        isSelected = false;
        break;
    case 23:
        description = "Zöld Ász";
        kind = "Zöld";
        value = 14;
        setPixmap(QPixmap(":source//ZoldAsz.png"));
        isSelected = false;
        break;
    case 24:
        description = "Makk Hetes";
        kind = "Makk";
        value = 7;
        setPixmap(QPixmap(":source//Makk7.png"));
        isSelected = false;
        break;
    case 25:
        description = "Makk Nyolcas";
        kind = "Makk";
        value = 8;
        setPixmap(QPixmap(":source//Makk8.png"));
        isSelected = false;
        break;
    case 26:
        description = "Makk Kilences";
        kind = "Makk";
        value = 9;
        setPixmap(QPixmap(":source//Makk9.png"));
        isSelected = false;
        break;
    case 27:
        description = "Makk Tizes";
        kind = "Makk";
        value = 10;
        setPixmap(QPixmap(":source//Makk10.png"));
        isSelected = false;
        break;
    case 28:
        description = "Makk Alsó";
        kind = "Makk";
        value = 11;
        setPixmap(QPixmap(":source//MakkAls.png"));
        isSelected = false;
        break;
    case 29:
        description = "Makk Felsõ";
        kind = "Makk";
        value = 12;
        setPixmap(QPixmap(":source//MakkFel.png"));
        isSelected = false;
        break;
    case 30:
        description = "Makk Király";
        kind = "Makk";
        value = 13;
        setPixmap(QPixmap(":source//MakkKir.png"));
        isSelected = false;
        break;
    case 31:
        description = "Makk Ász";
        kind = "Makk";
        value = 14;
        setPixmap(QPixmap(":source//MakkAsz.png"));
        isSelected = false;
        break;
    default:
        std::cerr << "Invalid card code!" << std::endl;
    }
}

Card::~Card() {
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



void Card::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(w->selectedCard == nullptr &&
        w->playerDeck.contains(this) &&
        w->getWhoseTurn() == w->playerName) {
        w->pickUpCard(this);
        setOpacity(0.7);
        setIsSelected(true);
    }
    else if(w->selectedCard != nullptr && w->getWhoseTurn() == w->playerName) {
        w->placeCard(this);
    }
}


