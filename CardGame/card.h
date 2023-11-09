#ifndef CARD_H
#define CARD_H

#include <string>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Card: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Card(int code =0, QGraphicsItem* parent=0);
    std::string getKind();
    int getValue();
    int getCode();
    std::string getDescription();
    bool getIsSelected();
    void setIsSelected(bool b);
    bool passesTo(Card* c);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
private:
    int code; // "7 - 0-7 Piros | 8-15 Tök | 16-23 Zöld | 24-31 Makk"
    std::string description; // "Piros Ász"
    std::string kind; // "Makk", "Tök", "Zöld", "Piros"
    int value; // 13
    std::string picture; // "src://images/Winter7.jpg"
    std::string specialAttribute; // "outofturn"
    std::string owner; // "player1, player2, pakli, kijátszott"
    bool isSelected;
};

#endif // CARD_H
