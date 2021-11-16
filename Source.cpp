#include<iostream>
#include<SFML\Graphics.hpp>

enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3

int main() {
    sf::RenderWindow screen(sf::VideoMode(1000, 1000), "PacMan"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS

    //load in images
    sf::Texture brick;
    brick.loadFromFile("brick.png");
    sf::Sprite wall;
    wall.setTexture(brick);

    int map[20][20] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
        1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,
        1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,
        1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
        1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,
        0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,
        1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1,
        0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,
        1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,
        0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,
        1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
        1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,
        1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
        1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,
        1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };

    int xpos = 8*52;
    int ypos = 20*45+4;
    int vx = 0;
    int vy = 0;
    sf::CircleShape player(20);
    player.setFillColor(sf::Color(250, 250, 0)); //using RGB value for color here (hex also works)
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false };

    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();
            //KEYBOARD INPUT 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;

        }//end event loop---------------------------------------------------------------

        if (keys[LEFT] == true)
            vx = -5;

        else if (keys[RIGHT] == true)
            vx = 5;

        else vx = 0;

        if (keys[UP] == true)
            vy = -5;

        else if (keys[DOWN] == true)
            vy = 5;

        else vy = 0;

        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);

                //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear


        for (int rows = 0; rows < 20; rows++)
            for (int cols = 0; cols < 20; cols++) {
                if (map[rows][cols] == 1) {
                    wall.setPosition(cols * 50, rows * 50);
                    screen.draw(wall);
                }
            }

        screen.draw(player);

        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    std::cout << "goodbye!" << std::endl;
} //end of main