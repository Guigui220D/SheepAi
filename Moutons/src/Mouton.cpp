#include "Mouton.h"
#include <iostream>
#include <math.h>
#include "StateGame.h"

Mouton::Mouton(StateGame* stategame, sf::Vector2u paddock)
{
    game = stategame;
    setSize(sf::Vector2f(30, 30));
    setOrigin(sf::Vector2f(15, 15));
    setPosition(sf::Vector2f(paddock.x * 200 + rand() % 200, paddock.y * 200 + rand() % 200));
    foodPos = sf::Vector2f(paddock.x * 200 + rand() % 100 + 50, paddock.y * 200 + rand() % 100 + 50);
    setRotation(rand() % 360);
    m_paddock = paddock;
    setTexture(&game->texture);
    setFillColor(sf::Color(rand() % 240 + 10, rand() % 240 + 10, rand() % 240 + 10));

    initRandLinks();


}

Mouton::Mouton(StateGame* stategame, Mouton parent, sf::Vector2u paddock, int mut)
{
    game = stategame;
    setSize(sf::Vector2f(30, 30));
    setOrigin(sf::Vector2f(15, 15));
    setFillColor(sf::Color::White);
    setPosition(sf::Vector2f(paddock.x * 200 + rand() % 200, paddock.y * 200 + rand() % 200));
    foodPos = sf::Vector2f(paddock.x * 200 + rand() % 100 + 50, paddock.y * 200 + rand() % 100 + 50);
    setRotation(rand() % 360);
    m_paddock = paddock;
    setTexture(&game->texture);
    setFillColor(sf::Color(rand() % 240 + 10, rand() % 240 + 10, rand() % 240 + 10));

    initLinks(&parent, mut);
}


Mouton::~Mouton()
{


}

void Mouton::printLinks()
{
    for (int i = 0; i < INPUTS * 2; i++)
        std::cout << '[' << i << "] : " << (int)links[i] << '\n';
}

void Mouton::act(float delta)
{
    ldelta = delta;
    handleAllInputs();
    if (getPosition().x < (m_paddock.x * 200 + 10))
        setPosition((m_paddock.x * 200 + 10), getPosition().y);
    if (getPosition().x > (m_paddock.x * 200 + 190))
        setPosition((m_paddock.x * 200 + 190), getPosition().y);
    if (getPosition().y < (m_paddock.y * 200 + 10))
        setPosition(getPosition().x, (m_paddock.y * 200 + 10));
    if (getPosition().y > (m_paddock.y * 200 + 190))
        setPosition(getPosition().x, (m_paddock.y * 200 + 190));
    int f = 0;

    if (getDistance(foodPos) <= RANGE)
    {
        score += 1;
        foodPos = sf::Vector2f(m_paddock.x * 200 + rand() % 100 + 50, m_paddock.y * 200 + rand() % 100 + 50);
    }

}

void Mouton::doAction(unsigned char action)
{
    //This does an action using its id
    switch (action)
    {
    case 1:
        setPosition(getPosition() + sf::Vector2f(75 * ldelta * cos(toRads(getRotation())), 75 * ldelta * sin(toRads(getRotation()))));
        break;
    case 2:
        setPosition(getPosition() + sf::Vector2f(-75 * ldelta * cos(toRads(getRotation())), -75 * ldelta * sin(toRads(getRotation()))));
        break;
    case 3:
        setRotation(getRotation() + 20 * ldelta);
        break;
    case 4:
        setRotation(getRotation() - 20 * ldelta);
        break;
    default:
        break;
    }
}

void Mouton::handleInput(unsigned char input)
{
    //Executes an action using an input id
    doAction(links[input]);
}

void Mouton::handleAllInputs()
{
    //Check all inputs, and do what is needed
    for (char i = 0; i < INPUTS * 2; i++)
    {
        if (getInputState(i))
            handleInput(i);
    }
}

bool Mouton::getInputState(unsigned char input)
{
    //Get input states
    int inp = input / 2;
    int iinv = input % 2;
    bool invert = false;
    if (iinv != 0)
        invert = true;
    bool res = false;
    switch (inp)
    {
    //Food
    case 0: //Food in front
        if (abs(getAngularPos(foodPos)) < INNER_VISION && getDistance(foodPos) > RANGE)
            res = true;
        break;
    case 1: //Food at the right
        {
            double agpos = getAngularPos(foodPos);
            if (agpos > 0 && agpos > INNER_VISION && agpos < OUTER_VISION && getDistance(foodPos) > RANGE)
                res = true;
        }
        break;
    case 2: //Food at the left
        {
            double agpos = getAngularPos(foodPos);
            if (agpos < 0 && agpos < -INNER_VISION && agpos > -OUTER_VISION && getDistance(foodPos) > RANGE)
                res = true;
        }
        break;
    case 3: //Food near
        if (getDistance(foodPos) < RANGE)
            res = true;
        break;
    //Sheeps
    case 4: //sheep in front
        /*
        for (int i = 0; i < game->sheeps.size(); i++)
        {
            Mouton* sheep = &game->sheeps[i];
            if (abs(getAngularPos(sheep->getPosition())) < INNER_VISION && getDistance(sheep->getPosition()) > RANGE)
            {
                res = true;
                break;
            }
        }
        */
        break;
    case 5: //Coconut at the right
        /*
        for (int i = 0; i < game->coconuts.size(); i++)
        {
            Mouton* sheep = &game->sheeps[i];
            double agpos = getAngularPos(sheep->getPosition());
            if (agpos > 0 && agpos > INNER_VISION && agpos < OUTER_VISION && getDistance(sheep->getPosition()) > RANGE)
            {
                res = true;
                break;
            }
        }
        */
        break;
    case 6: //Coconut at the left
        /*
        for (int i = 0; i < game->coconuts.size(); i++)
        {
            Mouton* sheep = &game->sheeps[i];
            double agpos = getAngularPos(sheep->getPosition());
            if (agpos < 0 && agpos < -INNER_VISION && agpos > -OUTER_VISION && getDistance(sheep->getPosition()) > RANGE)
            {
                res = true;
                break;
            }
        }
        */
        break;
    case 7:
        /*
        for (int i = 0; i < game->coconuts.size(); i++)
        {
            Mouton* sheep = &game->sheeps[i];
            if (getDistance(sheep->getPosition()) < RANGE)
            {
                res = true;
                break;
            }
        }
        */
        break;
    case 8:
        res = false;
        break;
    default:
        break;
    }
    return (res ^ invert);
}

double Mouton::getDistance(sf::Vector2f thing)
{
    sf::Vector2f diff = getPosition() - thing;
    return sqrt(diff.x * diff.x + diff.y * diff.y);
}

double Mouton::getAngularPos(sf::Vector2f thing)
{
    sf::Vector2f rpos = thing - getPosition();
    rpos = sf::Vector2f(rpos.x * cos(toRads(-getRotation())) - rpos.y * sin(toRads(-getRotation()))
                        , rpos.x * sin(toRads(-getRotation())) + rpos.y * cos(toRads(-getRotation())));
    double dist = getDistance(thing);
    double xdist = rpos.x / dist;
    double pangl = toDegrees(acos(xdist));
    if (rpos.y < 0)
    {
        pangl = -pangl;
    }
    return pangl;
}

double Mouton::toDegrees(double rads)
{
    return (rads / (2 * M_PI)) * 360;
}

double Mouton::toRads(double degrees)
{
    return (degrees / 360) * (2 * M_PI);
}

std::vector<unsigned char> Mouton::getLinks()
{
    return links;
}

void Mouton::initRandLinks()
{
    for (int i = 0; i <= INPUTS * 2; i++)
        links.push_back(0);
    for (int i = 0; i <= 12; i++)
        links[rand() % (INPUTS * 2)] = rand() % OUTPUTS;
}

void Mouton::initLinks(Mouton* parent, unsigned char force)
{
    links = parent->getLinks();
    for (int i = 0; i <= force; i++)
        links[rand() % (INPUTS * 2)] = rand() % OUTPUTS;
}
