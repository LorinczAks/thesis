#include "deck.h"

Deck::Deck(QString owner)
{
    this->owner = owner;
    /*
    owner = "pakli";
    Card* tmp;
    for(int i = 0; i < 32; i++) {
        tmp = new Card(i);
        content << tmp;
    }
    */
}


QList<Card*> Deck::getContent() {
    return content;
}

void Deck::addCards(Card* card) {
    content << card;
}
