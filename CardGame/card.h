#ifndef CARD_H
#define CARD_H

#include <string>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Card: public QGraphicsPixmapItem
{
public:
    Card(QGraphicsItem * parent=0, int code=0);
    std::string getKind();
    int getValue();
    bool passesTo(Card c);
private:
    int code; // "7 - 0-7 Piros | 8-15 Tök | 16-23 Zöld | 24-31 Makk"
    std::string description; // "Piros Ász"
    std::string kind; // "Makk", "Tök", "Zöld", "Piros"
    int value; // 13
    std::string picture; // "src://images/Winter7.jpg"
    std::string specialAttribute; // "outofturn"
};

#endif // CARD_H
