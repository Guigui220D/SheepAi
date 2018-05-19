#include "Coco.h"
#include "StateGame.h"

Coco::Coco(StateGame* stategame)
{
    game = stategame;
    setFillColor(sf::Color(175, 123, 32));
    setRadius(15);
    setOrigin(sf::Vector2f(15, 15));
}

Coco::Coco(StateGame* stategame, sf::Vector2f pos)
{
    game = stategame;
    setFillColor(sf::Color(175, 123, 32));
    setRadius(15);
    setOrigin(sf::Vector2f(15, 15));
    setPosition(pos);
}

Coco::~Coco()
{
    //dtor
}
