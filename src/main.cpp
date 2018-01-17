//Header Files
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <cstdlib>
#include "Paddle.h"
#include "Ball.h"

int main()
{
    //Create main window
    int windowWidth = 1024;
    int windowHeight = 768;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong");

    //Keep track of lives and score the player has
    int lives = 3;
    int score = 0;

    //Create paddle and ball
    Paddle paddle(windowWidth / 2, windowHeight - 20);
    Ball ball(windowWidth / 2, 1);

    //HUD that keeps track of the lives and score
    sf::Text hud;

    //Retrieve the font from the resources file
    sf::Font font;
    //http://www.dafont.com/theme.php?cat=302
    font.loadFromFile("../resources/DS-DIGIT.TTF");

    //Load Sound effects
    //http://cs.au.dk/~dsound/DigitalAudio.dir/Greenfoot/Pong.dir/Pong.html
    sf::SoundBuffer hitTop;
    if (!hitTop.loadFromFile("../resources/sounds/ping_pong_8bit_beeep.wav"))
    {
        return -1;
    }
    sf::SoundBuffer hitWall;
    if (!hitWall.loadFromFile("../resources/sounds/ping_pong_8bit_plop.wav"))
    {
        return -1;
    }
    sf::SoundBuffer miss;
    if (!miss.loadFromFile("../resources/sounds/ping_pong_8bit_peeeeeep.wav"))
    {
        return -1;
    }

    sf::Sound scoreSound;
    scoreSound.setBuffer(hitTop);
    sf::Sound wallSound;
    wallSound.setBuffer(hitWall);
    sf::Sound missSound;
    missSound.setBuffer(miss);

    //set the font, character size, and fill color of the HUD
    hud.setFont(font);
    hud.setCharacterSize(75);
    hud.setFillColor(sf::Color::White);

    //START: MAIN GAME LOOP
    while (window.isOpen())
    {
        /*Handle Player input*/

        //Catch events thrown by OS
        sf::Event event;
        while (window.pollEvent(event))
        {
            //Close window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        //Handle paddle controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            //Move paddle left
            if(paddle.getPosition().left > 0)
            {
                paddle.moveLeft();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            //Move paddle right
            if(paddle.getPosition().left + 100 < windowWidth)
            {
                paddle.moveRight();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            //Quit game key
            window.close();
        }

        /*Handle ball collisions*/

        //Handle ball hitting the bottom of the screen
        if(ball.getPosition().top > windowHeight)
        {
            ball.hitBottom();
            missSound.play();
            if(--lives < 0)
            {
                lives = 3;
                score = 0;
            }
        }
        //Handle ball hitting the top of the screen
        if(ball.getPosition().top < 0)
        {
            ball.reboundBatOrTop();
            scoreSound.play();
            score++;
        }
        //Handle ball hitting the sides of the screen
        if(ball.getPosition().left < 0 || ball.getPosition().left + 25 > windowWidth)
        {
            ball.reboundSides();
            wallSound.play();
        }
        //Handle ball rebounds off the player's paddle
        if(ball.getPosition().intersects(paddle.getPosition()))
        {
            ball.reboundBatOrTop();
            wallSound.play();
        }

        //Update ball and paddle
        ball.update();
        paddle.update();

        //Update HUD text
        std::stringstream ss;
        ss << "Score:" << score << "\tLives:" << lives;
        hud.setString(ss.str());

        //Clear previous frame
        window.clear(sf::Color::Black); //(26, 128, 182, 255)

        //Draw the updated positions of the ball and paddle
        window.draw(ball.getShape());
        window.draw(paddle.getShape());

        //Draw the HUD text
        window.draw(hud);

        //Display drawn frame on window
        window.display();
    }//END MAIN GAME LOOP

    return 0;
}