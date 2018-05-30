#ifndef MOUTON_H
#define MOUTON_H
#include "SFML/Graphics.hpp"
#include <vector>

class StateGame;
class Coco;

class Mouton : public sf::RectangleShape
{
    public:
        static const int INPUTS = 17;
        static const int OUTPUTS = 5;
        static const int INNER_VISION = 5;
        static const int OUTER_VISION = 90;
        static const int RANGE = 12;
        Mouton(StateGame* stategame, sf::Vector2u paddock);
        Mouton(StateGame* stategame, Mouton parent, sf::Vector2u paddock, int mut = 2);
        virtual ~Mouton();
        void act(float delta);
        std::vector<unsigned char> getLinks();
        void printLinks();
        inline sf::Vector2f getFoodPos() { return foodPos; };
        inline sf::Vector2u getPaddock() { return m_paddock; };
        inline void setPaddock(sf::Vector2u p) { m_paddock = p; };

        int score = 0;
    private:

        sf::Vector2f foodPos;

        void doAction(unsigned char action);
        void handleInput(unsigned char input);
        void handleAllInputs();
        bool getInputState(unsigned char input);
        std::vector<unsigned char> links;
        void initRandLinks();
        void initLinks(Mouton* parent, unsigned char force);

        double getAngularPos(sf::Vector2f thing);
        double getDistance(sf::Vector2f thing);

        double toRads(double degrees);
        double toDegrees(double rads);

        float ldelta;

        StateGame* game;

        sf::Vector2u m_paddock;
};

#endif // MOUTON_H
