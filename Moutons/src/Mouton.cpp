#include "Mouton.h"
#include <iostream>
#include <math.h>
#include "StateGame.h"

Mouton::Mouton(StateGame* stategame)
{
    game = stategame;
    setSize(sf::Vector2f(50, 50));
    setOrigin(sf::Vector2f(25, 25));
    setPosition(sf::Vector2f(rand() % 1200, rand() % 1000));
    setFillColor(sf::Color::White);
    initRandLinks();
    //printLinks();

    setTexture(&game->texture);
}

Mouton::Mouton(StateGame* stategame, Mouton parent)
{
    game = stategame;
    setSize(sf::Vector2f(50, 50));
    setOrigin(sf::Vector2f(25, 25));
    setFillColor(sf::Color::White);
    setPosition(parent.getPosition());
    initLinks(&parent, 11 - score);
    //printLinks();

    setTexture(&game->texture);
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
    setFillColor(sf::Color(255, 255 - (score / 10) * 255, 255));
    ldelta = delta;
    handleAllInputs();
    if (getPosition().x < 0)
        setPosition(0, getPosition().y);
    if (getPosition().x > 1200)
        setPosition(1200, getPosition().y);
    if (getPosition().y < 0)
        setPosition(getPosition().x, 0);
    if (getPosition().y > 1000)
        setPosition(getPosition().x, 1000);
    int f = 0;
    for (int i = 0; i < game->coconuts.size(); i++)
    {
        if (getDistance(game->coconuts.at(i - f).getPosition()) < (RANGE + 5))
        {
            game->coconuts.erase(game->coconuts.begin() + i - f);
            f++;
            food += 50;
            if (score < 10)
                score += 1;
            game->coconuts.push_back(Coco(game, sf::Vector2f(rand() % 1200, rand() % 1000)));
        }
    }
    food -= delta;
    timeleft -= delta;
    if (food <= 0)
    {
        dead = true;
        game->sheeps.push_back(Mouton(game));
        return;
    }
    if (timeleft <= 0)
    {
        dead = true;
        return;
    }
    if (food > 150)
    {
        game->sheeps.push_back(Mouton(game, *this));
        food -= 120;
    }

    //std::cout << food << '\n';
    //if (getInputState(6))
    //std::cout << "Coco in my range" << std::endl;
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
    //Coconuts
    case 0: //Coconut in front
        for (int i = 0; i < game->coconuts.size(); i++)
        {
            Coco* coconut = &game->coconuts[i];
            if (abs(getAngularPos(coconut->getPosition())) < INNER_VISION && getDistance(coconut->getPosition()) > RANGE)
            {
                res = true;
                break;
            }
        }
        break;
    case 1: //Coconut at the right
        for (int i = 0; i < game->coconuts.size(); i++)
        {
            Coco* coconut = &game->coconuts[i];
            double agpos = getAngularPos(coconut->getPosition());
            if (agpos > 0 && agpos > INNER_VISION && agpos < OUTER_VISION && getDistance(coconut->getPosition()) > RANGE)
            {
                res = true;
                break;
            }
        }
        break;
    case 2: //Coconut at the left
        for (int i = 0; i < game->coconuts.size(); i++)
        {
            Coco* coconut = &game->coconuts[i];
            double agpos = getAngularPos(coconut->getPosition());
            if (agpos < 0 && agpos < -INNER_VISION && agpos > -OUTER_VISION && getDistance(coconut->getPosition()) > RANGE)
            {
                res = true;
                break;
            }
        }
        break;
    case 3:
        for (int i = 0; i < game->coconuts.size(); i++)
        {
            Coco* coconut = &game->coconuts[i];
            if (getDistance(coconut->getPosition()) < RANGE)
            {
                res = true;
                break;
            }
        }
        break;
    //Sheeps
    case 4: //sheep in front
        for (int i = 0; i < game->sheeps.size(); i++)
        {
            Mouton* sheep = &game->sheeps[i];
            if (abs(getAngularPos(sheep->getPosition())) < INNER_VISION && getDistance(sheep->getPosition()) > RANGE)
            {
                res = true;
                break;
            }
        }
        break;
    case 5: //Coconut at the right
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
        break;
    case 6: //Coconut at the left
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
        break;
    case 7:
        for (int i = 0; i < game->coconuts.size(); i++)
        {
            Mouton* sheep = &game->sheeps[i];
            if (getDistance(sheep->getPosition()) < RANGE)
            {
                res = true;
                break;
            }
        }
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
