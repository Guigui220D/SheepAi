#include "StateGame.h"
#include <iostream>

StateGame::StateGame()
    : bestMouton(this, sf::Vector2u(3, 2))
{
    texture.loadFromFile("sheep.png");
    font.loadFromFile("Artesana.ttf");
    donut.loadFromFile("donuts.png");
    paddock.loadFromFile("paddock.png");

    food.setRadius(7.5f);
    food.setOrigin(sf::Vector2f(7.5f, 7.5f));
    food.setTexture(&donut);

    scoreText.setCharacterSize(18);
    scoreText.setFont(font);

    info.setCharacterSize(20);
    info.setFont(font);
    info.setPosition(sf::Vector2f(3, 605));

    square.setSize(sf::Vector2f(200, 200));
    square.setTexture(&paddock);

    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            sheeps.push_back(Mouton(this, sf::Vector2u(x, y)));
        }
    }

}

StateGame::~StateGame()
{
    //dtor
}

void StateGame::draw(sf::RenderWindow &window)
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            square.setPosition(sf::Vector2f(x * 200, y * 200));
            square.setFillColor(((x + y) % 2) ? sf::Color::White : sf::Color(210, 210, 210));
            window.draw(square);
        }
    }

    for (int i = 0; i < sheeps.size(); i++)
    {
        food.setPosition(sheeps.at(i).getFoodPos());
        window.draw(food);
        window.draw(sheeps[i]);
        scoreText.setPosition(sf::Vector2f(3 + sheeps.at(i).getPaddock().x * 200, 175 + sheeps.at(i).getPaddock().y * 200));
        scoreText.setString("Score : " + std::to_string(sheeps.at(i).score));
        window.draw(scoreText);
    }

    info.setString("Generation : " + std::to_string(gen) +
                   "     Score max : " + std::to_string(scoremax) +
                   "     Temps restant : " + std::to_string(lifetime - time));
    window.draw(info);
}

void StateGame::update(float delta)
{
    for (int i = 0; i < sheeps.size(); i++)
        sheeps.at(i).act(delta);
    time += delta;
    if (time >= lifetime)
    {
        time = 0.f;
        createNewGeneration();
    }
}

void StateGame::createNewGeneration()
{
    Mouton best1(this, sf::Vector2u());
    int bestScore1 = 0;
    Mouton best2(this, sf::Vector2u());
    int bestScore2 = 0;
    Mouton best3(this, sf::Vector2u());
    int bestScore3 = 0;
    for (int i = 0; i < sheeps.size() - 1; i++)
    {
        if (sheeps.at(i).score > scoremax)
        {
            scoremax = sheeps.at(i).score;
            bestMouton = sheeps.at(i);
        }
        if (sheeps.at(i).score > bestScore1)
        {
            best3 = best2;
            bestScore3 = bestScore2;
            best2 = best1;
            bestScore2 = bestScore1;
            best1 = sheeps.at(i);
            bestScore1 = sheeps.at(i).score;
        }
        else
        {
            if (sheeps.at(i).score > bestScore2)
            {
                best3 = best2;
                bestScore3 = bestScore2;
                best2 = sheeps.at(i);
                bestScore2 = sheeps.at(i).score;
            }
            else
            {
                if (sheeps.at(i).score > bestScore3)
                {
                    best3 = sheeps.at(i);
                    bestScore3 = sheeps.at(i).score;
                }
            }
        }
    }
    sheeps.clear();
    sheeps.push_back(Mouton(this, best1, sf::Vector2u(0, 0)));
    sheeps.push_back(Mouton(this, best1, sf::Vector2u(1, 0)));
    sheeps.push_back(Mouton(this, best1, sf::Vector2u(2, 0)));
    sheeps.push_back(Mouton(this, best1, sf::Vector2u(3, 0)));
    sheeps.push_back(Mouton(this, best2, sf::Vector2u(0, 1)));
    sheeps.push_back(Mouton(this, best2, sf::Vector2u(1, 1)));
    sheeps.push_back(Mouton(this, best2, sf::Vector2u(2, 1)));
    sheeps.push_back(Mouton(this, best3, sf::Vector2u(3, 1)));
    for (int x = 0; x < 3; x++)
    {
        sheeps.push_back(Mouton(this, sf::Vector2u(x, 2)));
    }
    sheeps.push_back(Mouton(this, bestMouton, sf::Vector2u(3, 2)));
    gen++;
}


