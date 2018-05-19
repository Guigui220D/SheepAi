#ifndef STATEPRE_H
#define STATEPRE_H
#include "State.h"

class StatePre : public State
{
    public:
        StatePre();
        virtual ~StatePre();
        void draw(sf::RenderWindow &window) override;
        void update(float delta) override;
    protected:
    private:
        sf::RectangleShape image;
};

#endif // STATEPRE_H
