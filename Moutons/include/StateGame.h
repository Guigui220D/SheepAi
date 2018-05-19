#ifndef STATEGAME_H
#define STATEGAME_H
#include "State.h"
#include <vector>
#include "Mouton.h"
#include "Coco.h"

class StateGame : public State
{
    public:
        StateGame();
        virtual ~StateGame();
        void draw(sf::RenderWindow &window) override;
        void update(float delta) override;
        std::vector<Mouton> sheeps;
        std::vector<Coco> coconuts;
        sf::Texture texture;
    protected:
    private:
};

#endif // STATEGAME_H
