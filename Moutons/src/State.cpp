#include "State.h"

State::State()
{
    //ctor
}

State::~State()
{
    //dtor
}

void State::draw(sf::RenderWindow &window) {}

void State::update(float delta) {}

void State::reset() {}

bool State::isDone()
{
    return false;
}
