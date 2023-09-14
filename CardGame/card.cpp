#include "card.h"
#include <QGraphicsScene>
#include <iostream>

Card::Card(QGraphicsItem *parent, int code): QGraphicsPixmapItem(parent)
{
    code = code; // "7"
    switch (code) {
        case 0:
            description = "Piros Hetes";
            kind = "Piros";
            value = 7;
            picture = ":/images/kartya.jpg";
            specialAttribute = "drawtwo";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 1:
            description = "Piros Nyolcas";
            kind = "Piros";
            value = 8;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 2:
            description = "Piros Kilences";
            kind = "Piros";
            value = 9;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 3:
            description = "Piros Tizes";
            kind = "Piros";
            value = 10;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 4:
            description = "Piros Alsó";
            kind = "Piros";
            value = 11;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 5:
            description = "Piros Felső";
            kind = "Piros";
            value = 12;
            picture = ":/images/kartya.jpg";
            specialAttribute = "askforkind";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 6:
            description = "Piros Király";
            kind = "Piros";
            value = 13;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 7:
            description = "Piros Ász";
            kind = "Piros";
            value = 14;
            picture = ":/images/kartya.jpg";
            specialAttribute = "outofturn";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 8:
            description = "Tök Hetes";
            kind = "Tök";
            value = 7;
            picture = ":/images/kartya.jpg";
            specialAttribute = "drawtwo";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 9:
            description = "Tök Nyolcas";
            kind = "Tök";
            value = 8;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 10:
            description = "Tök Kilences";
            kind = "Tök";
            value = 9;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 11:
            description = "Tök Tizes";
            kind = "Tök";
            value = 10;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 12:
            description = "Tök Alsó";
            kind = "Tök";
            value = 11;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 13:
            description = "Tök Felső";
            kind = "Tök";
            value = 12;
            picture = ":/images/kartya.jpg";
            specialAttribute = "askforkind";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 14:
            description = "Tök Király";
            kind = "Tök";
            value = 13;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 15:
            description = "Tök Ász";
            kind = "Tök";
            value = 14;
            picture = ":/images/kartya.jpg";
            specialAttribute = "outofturn";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 16:
            description = "Zöld Hetes";
            kind = "Zöld";
            value = 7;
            picture = ":/images/kartya.jpg";
            specialAttribute = "drawtwo";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 17:
            description = "Zöld Nyolcas";
            kind = "Zöld";
            value = 8;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 18:
            description = "Zöld Kilences";
            kind = "Zöld";
            value = 9;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 19:
            description = "Zöld Tizes";
            kind = "Zöld";
            value = 10;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 20:
            description = "Zöld Alsó";
            kind = "Zöld";
            value = 11;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 21:
            description = "Zöld Felső";
            kind = "Zöld";
            value = 12;
            picture = ":/images/kartya.jpg";
            specialAttribute = "askforkind";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 22:
            description = "Zöld Király";
            kind = "Zöld";
            value = 13;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 23:
            description = "Zöld Ász";
            kind = "Zöld";
            value = 14;
            picture = ":/images/kartya.jpg";
            specialAttribute = "outofturn";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 24:
            description = "Makk Hetes";
            kind = "Makk";
            value = 7;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 25:
            description = "Makk Nyolcas";
            kind = "Makk";
            value = 8;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 26:
            description = "Makk Kilences";
            kind = "Makk";
            value = 9;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 27:
            description = "Makk Tizes";
            kind = "Makk";
            value = 10;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 28:
            description = "Makk Alsó";
            kind = "Makk";
            value = 11;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 29:
            description = "Makk Felső";
            kind = "Makk";
            value = 12;
            picture = ":/images/kartya.jpg";
            specialAttribute = "askforkind";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 30:
            description = "Makk Király";
            kind = "Makk";
            value = 13;
            picture = ":/images/kartya.jpg";
            specialAttribute = "";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        case 31:
            description = "Makk Ász";
            kind = "Makk";
            value = 14;
            picture = ":/images/kartya.jpg";
            specialAttribute = "outofturn";
            setPixmap(QPixmap(":/images/kartya.jpg"));
            break;
        default:
            std::cerr << "Invalid card code!" << std::endl;
    }
}

std::string getKind() {
    return kind;
}

int getValue() {
    return value;
}
