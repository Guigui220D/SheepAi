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
        static const int OUTER_VISION = 800;
        static const int RANGE = 75;
        Mouton(StateGame* stategame);
        Mouton(StateGame* stategame, Mouton parent);
        virtual ~Mouton();
        void act(float delta);
        std::vector<unsigned char> getLinks();
        void printLinks();

         bool dead = false;
         double food = 30;
         int score = 0;
    private:

        double timeleft = 600;

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
};

#endif // MOUTON_H
