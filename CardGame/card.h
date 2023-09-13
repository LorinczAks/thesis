#ifndef CARD_H
#define CARD_H

#include <string>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Card: public QGraphicsPixmapItem
{
public:
    Card(QGraphicsItem * parent=0, std::string="PA");
    std::string getKind();
    int getValue();
    bool passesTo(Card c);
private:
    std::string name; // "P7"
    std::string description; // "Piros Hetes"
    std::string kind; // "Makk", "Tök", "Zöld", "Piros"
    int value; // 7
    std::string picture; // "src://images/Winter7.jpg"
    std::string specialAttribute; // "+2"
};

#endif // CARD_H
