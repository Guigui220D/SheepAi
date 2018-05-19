#include "StatePre.h"

StatePre::StatePre()
{
    image = sf::RectangleShape();
    image.setSize(sf::Vector2f(100, 100));
    image.setFillColor(sf::Color::Red);
}

StatePre::~StatePre()
{
    //dtor
}

void StatePre::draw(sf::RenderWindow &window)
{
    window.draw(image);
}

void StatePre::update(float delta)
{

}
