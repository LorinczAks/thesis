#include "deck.h"

Deck::Deck()
{
    Card tmp;
    for(int i = 0; i < 32; i++) {
        tmp = new Card(i);
        content.push_back(tmp);
    }
}
