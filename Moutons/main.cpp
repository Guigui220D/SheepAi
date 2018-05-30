#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateGame.h"
#include "StatePre.h"
#include <vector>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>

bool timelapse = false;
bool pause = false;
bool dt = false;

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 630), "The Sheep's Crisis");

    State *currentState = new StateGame();

    sf::Clock clk = sf::Clock();

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::P)
                {
                    pause = !pause;
                    clk.restart();
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    timelapse = !timelapse;
                    clk.restart();
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    dt = !dt;
                }
            }
        }

        if (!pause)
        {
            if (timelapse)
            {
                currentState->update(0.2f);
                clk.restart();
            }
            else
            {
                if (dt)
                {
                    currentState->update(clk.restart().asSeconds() * 10);
                }
                else
                {
                    currentState->update(clk.restart().asSeconds());
                }
            }
        }

        window.clear();
        currentState->draw(window);
        window.display();

        if (currentState->isDone())
        {

        }
    }

    delete currentState;

    return 0;
}
