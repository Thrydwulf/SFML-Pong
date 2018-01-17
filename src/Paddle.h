//Header Files
#include <SFML/Graphics.hpp>

class Paddle
{
    private:
        sf::Vector2f position;

        sf::RectangleShape paddleShape;

        float paddleSpeed = 1.2f;

    public:
        Paddle(float startX, float startY);

        sf::FloatRect getPosition();

        sf::RectangleShape getShape();

        void moveLeft();

        void moveRight();

        void update();

};