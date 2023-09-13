#include "card.h"
#include <QGraphicsScene>

Card::Card(QGraphicsItem *parent, std::string s): QGraphicsPixmapItem(parent)
{
    name = s; // "P7"
    description = ""; // "Piros Hetes"
    kind = ""; // "Makk", "Tök", "Zöld", "Piros"
    value = 7; // 7
    picture = ":/images/kartya.jpg"; // "src://images/Winter7.jpg"
    specialAttribute = ""; // "+2"
    setPixmap(QPixmap(":/images/kartya.jpg"));
}
