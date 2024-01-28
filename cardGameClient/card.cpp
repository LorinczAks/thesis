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
        description = "Piros Als�";
        kind = "Piros";
        value = 11;
        setPixmap(QPixmap(":source//PirosAls.png"));
        isSelected = false;
        break;
    case 5:
        description = "Piros Fels�";
        kind = "Piros";
        value = 12;
        setPixmap(QPixmap(":source//PirosFel.png"));
        isSelected = false;
        break;
    case 6:
        description = "Piros Kir�ly";
        kind = "Piros";
        value = 13;
        setPixmap(QPixmap(":source//PirosKir.png"));
        isSelected = false;
        break;
    case 7:
        description = "Piros �sz";
        kind = "Piros";
        value = 14;
        setPixmap(QPixmap(":source//PirosAsz.png"));
        isSelected = false;
        break;
    case 8:
        description = "T�k Hetes";
        kind = "T�k";
        value = 7;
        setPixmap(QPixmap(":source//Tok7.png"));
        isSelected = false;
        break;
    case 9:
        description = "T�k Nyolcas";
        kind = "T�k";
        value = 8;
        setPixmap(QPixmap(":source//Tok8.png"));
        isSelected = false;
        break;
    case 10:
        description = "T�k Kilences";
        kind = "T�k";
        value = 9;
        setPixmap(QPixmap(":source//Tok9.png"));
        isSelected = false;
        break;
    case 11:
        description = "T�k Tizes";
        kind = "T�k";
        value = 10;
        setPixmap(QPixmap(":source//Tok10.png"));
        isSelected = false;
        break;
    case 12:
        description = "T�k Als�";
        kind = "T�k";
        value = 11;
        setPixmap(QPixmap(":source//TokAls.png"));
        isSelected = false;
        break;
    case 13:
        description = "T�k Fels�";
        kind = "T�k";
        value = 12;
        setPixmap(QPixmap(":source//TokFel.png"));
        isSelected = false;
        break;
    case 14:
        description = "T�k Kir�ly";
        kind = "T�k";
        value = 13;
        setPixmap(QPixmap(":source//TokKir.png"));
        isSelected = false;
        break;
    case 15:
        description = "T�k �sz";
        kind = "T�k";
        value = 14;
        setPixmap(QPixmap(":source//TokAsz.png"));
        isSelected = false;
        break;
    case 16:
        description = "Z�ld Hetes";
        kind = "Z�ld";
        value = 7;
        setPixmap(QPixmap(":source//Zold7.png"));
        isSelected = false;
        break;
    case 17:
        description = "Z�ld Nyolcas";
        kind = "Z�ld";
        value = 8;
        setPixmap(QPixmap(":source//Zold8.png"));
        isSelected = false;
        break;
    case 18:
        description = "Z�ld Kilences";
        kind = "Z�ld";
        value = 9;
        setPixmap(QPixmap(":source//Zold9.png"));
        isSelected = false;
        break;
    case 19:
        description = "Z�ld Tizes";
        kind = "Z�ld";
        value = 10;
        setPixmap(QPixmap(":source//Zold10.png"));
        isSelected = false;
        break;
    case 20:
        description = "Z�ld Als�";
        kind = "Z�ld";
        value = 11;
        setPixmap(QPixmap(":source//ZoldAls.png"));
        isSelected = false;
        break;
    case 21:
        description = "Z�ld Fels�";
        kind = "Z�ld";
        value = 12;
        setPixmap(QPixmap(":source//ZoldFel.png"));
        isSelected = false;
        break;
    case 22:
        description = "Z�ld Kir�ly";
        kind = "Z�ld";
        value = 13;
        setPixmap(QPixmap(":source//ZoldKir.png"));
        isSelected = false;
        break;
    case 23:
        description = "Z�ld �sz";
        kind = "Z�ld";
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
        description = "Makk Als�";
        kind = "Makk";
        value = 11;
        setPixmap(QPixmap(":source//MakkAls.png"));
        isSelected = false;
        break;
    case 29:
        description = "Makk Fels�";
        kind = "Makk";
        value = 12;
        setPixmap(QPixmap(":source//MakkFel.png"));
        isSelected = false;
        break;
    case 30:
        description = "Makk Kir�ly";
        kind = "Makk";
        value = 13;
        setPixmap(QPixmap(":source//MakkKir.png"));
        isSelected = false;
        break;
    case 31:
        description = "Makk �sz";
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


