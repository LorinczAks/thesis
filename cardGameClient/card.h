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
    ~Card();
    // methods
    std::string getKind();
    int getValue();
    int getCode();
    std::string getDescription();
    bool getIsSelected();
    void setIsSelected(bool b);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
private:
    int code; // "7 - 0-7 Piros | 8-15 T�k | 16-23 Z�ld | 24-31 Makk"
    std::string description; // "Piros �sz"
    std::string kind; // "Makk", "T�k", "Z�ld", "Piros"
    int value; // 13
    bool isSelected;
};

#endif // CARD_H
