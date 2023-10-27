#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <QList>

class Deck
{
public:
    Deck(QString owner);

    QList<Card*> getContent();

    void addCards(Card* card);
private:
    QList<Card*> content;
    QString owner; // player1 | player2 | pakli | dobott
};

#endif // DECK_H
