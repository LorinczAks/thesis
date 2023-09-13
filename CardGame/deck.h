#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

class Deck
{
public:
    Deck();
private:
    std::vector<Card> content;
};

#endif // DECK_H
