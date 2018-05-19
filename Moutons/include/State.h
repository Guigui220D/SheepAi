#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>

class State
{
    public:
        State();
        virtual ~State();
        virtual void draw(sf::RenderWindow &window);
        virtual void update(float delta);
        virtual void reset();
        virtual bool isDone();
    protected:
    private:
};

#endif // STATE_H
