#ifndef COCO_H
#define COCO_H
#include "SFML/Graphics.hpp"

class StateGame;

class Coco : public sf::CircleShape
{
    public:
        Coco(StateGame* stategame);
        Coco(StateGame* stategame, sf::Vector2f pos);
        virtual ~Coco();
    private:
        StateGame* game;
};

#endif // COCO_H
