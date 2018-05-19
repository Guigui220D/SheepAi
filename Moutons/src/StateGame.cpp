#include "StateGame.h"
#include <iostream>

StateGame::StateGame()
{
   sheeps = std::vector<Mouton>();
   sheeps.push_back(Mouton(this));
   sheeps.push_back(Mouton(this));
   //sheeps.push_back(Mouton(this, sf::Vector2f(100, 200)));

   coconuts = std::vector<Coco>();
   for (int i = 0; i < 3; i++)
        coconuts.push_back(Coco(this, sf::Vector2f(rand() % 1200, rand() % 1000)));

    texture = sf::Texture();
    texture.loadFromFile("sheep.png");
}

StateGame::~StateGame()
{
    //dtor
}

void StateGame::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < sheeps.size(); i++)
        window.draw(sheeps[i]);
    for (int i = 0; i < coconuts.size(); i++)
        window.draw(coconuts[i]);
}

void StateGame::update(float delta)
{
    for (int i = 0; i < sheeps.size(); i++)
        sheeps.at(i).act(delta);
    int f = 0;
    for (int i = 0; i < sheeps.size(); i++)
    {
        if (sheeps.at(i - f).dead)
        {
            sheeps.erase(sheeps.begin() + (i - f));
            f++;
        }
    }
    if (sheeps.size() == 0)
    {
        sheeps.push_back(Mouton(this));
        sheeps.push_back(Mouton(this));
        std::cout << "All sheeps are dead\n";
    }
    if (sheeps.size() >= 10)
    {
        double j = 1000000;
        int id = 0;
        for (int i = 0; i < sheeps.size(); i++)
        {
            if (sheeps.at(i).food < j)
            {
                j = sheeps.at(i).food;
                id = i;
            }

        }
        sheeps.erase(sheeps.begin() + id);
    }
}
