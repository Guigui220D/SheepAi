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

        sf::Texture texture;
        sf::Texture donut;
        sf::Texture paddock;
        sf::Font font;

        void createNewGeneration();
    private:
        sf::RectangleShape square;
        sf::CircleShape food;
        sf::Text scoreText;
        sf::Text info;
        float time;
        float lifetime = 100.f;
        int gen = 0;
        int scoremax = 0;
        Mouton bestMouton;
};

#endif // STATEGAME_H
