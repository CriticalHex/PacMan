#include<iostream>
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
using namespace std;

enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3

//class Ghost
//{
//public:
//    Ghost(int x, int y, int radius, int whichGhost);
//    sf::Texture ghostCreate();
//
//private:
//    int xPos;
//    int yPos;
//    int whichGhost;
//    int Width;
//    int isDead;
//
//};

int main() {
    sf::RenderWindow screen(sf::VideoMode(1000, 1000), "PacMan"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS

    sf::Music music;
    if (!music.openFromFile("sound.wav"))
        return -1; // error
    music.play();
    music.setLoop(true);

    //load in images
    sf::Texture brick;
    brick.loadFromFile("brick.png");
    sf::Sprite wall;
    wall.setTexture(brick);

    sf::Texture pacman;
    pacman.loadFromFile("pac.png");
    sf::IntRect pac(0, 0, 50, 50);
    sf::Sprite playerImg(pacman, pac);
    int ticker = 0;
    int frameNum = 0;
    int rowNum = 0;

    int map[20][20] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
        1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,
        1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,
        1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
        1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,
        9,9,9,1,0,1,0,0,0,0,0,0,0,1,0,1,9,9,9,9,
        1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1,
        0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,
        2,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,
        9,9,9,1,0,1,0,0,0,0,0,0,0,1,0,1,9,9,9,9,
        1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
        1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,
        1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
        1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,
        1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };

    int xpos = 10 * 50;
    int ypos = 18 * 50;
    int vx = 0;
    int vy = 0;
    int radius = 25;
    bool keys[] = { false, false, false, false };

    sf::CircleShape dot(5);
    dot.setFillColor(sf::Color::White);

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

        if (keys[LEFT] == true) {
            rowNum = 3;
            vx = -5;
        }

        else if (keys[RIGHT] == true) {
            rowNum = 1;
            vx = 5;
        }

        //else vx = 0;

        if (keys[UP] == true) {
            rowNum = 0;
            vy = -5;
        }

        else if (keys[DOWN] == true) {
            rowNum = 2;
            vy = 5;
        }

        //else vy = 0;

        ////less working
        ////right
        //if (vx > 0 && (map[(ypos + 3) / 50][(xpos + radius * 2 + 3) / 50] != 1 || map[(ypos + radius * 2 - 3) / 50][(xpos + radius * 2 + 3) / 50] != 1))
        //    xpos += vx;

        ////left
        //if (vx < 0 && (map[(ypos + 3) / 50][(xpos - 3) / 50] != 1 || map[(ypos + radius * 2 - 3) / 50][(xpos - 3) / 50] != 1))
        //    xpos += vx;

        ////down, so positive
        //if (vy > 0 && (map[(ypos + radius * 2 + 3) / 50][(xpos + 3) / 50] != 1 || map[(ypos + radius * 2 + 3) / 50][(xpos + radius * 2 - 3) / 50] != 1))
        //    ypos += vy;

        ////up, so negative
        //if (vy < 0 && (map[(ypos - 3) / 50][(xpos + radius * 2 - 3) / 50] != 1 || map[(ypos - 3) / 50][(xpos + 3) / 50] != 1))
        //    ypos += vy;

        //more working
        //right
        if (vx > 0 && (map[(ypos + 3) / 50][(xpos + radius * 2 + 3) / 50] == 1 || map[(ypos + radius * 2 - 3) / 50][(xpos + radius * 2 + 3) / 50] == 1))
            vx = 0;

        //left
        if (vx < 0 && (map[(ypos + 3) / 50][(xpos - 3) / 50] == 1 || map[(ypos + radius * 2 - 3) / 50][(xpos - 3) / 50] == 1))
            vx = 0;

        //down, so positive
        if (vy > 0 && (map[(ypos + radius * 2 + 3) / 50][(xpos + 3) / 50] > 0 || map[(ypos + radius * 2 + 3) / 50][(xpos + radius * 2 - 3) / 50] > 0))
            vy = 0;

        //up, so negative
        if (vy < 0 && (map[(ypos - 3) / 50][(xpos + radius * 2 - 3) / 50] == 1 || map[(ypos - 3) / 50][(xpos + 3) / 50] == 1))
            vy = 0;

        if (xpos + 25 >= 1000)
            xpos = -25;
        else if (xpos <= -25)
            xpos = 975;

        xpos += vx;
        ypos += vy;
        

        if (vx != 0 || vy != 0) {
            music.setVolume(100.f);
            ticker += 1; 
            if (ticker % 3 == 0)
                frameNum += 1; 
            if (frameNum > 3) 
                frameNum = 0;
        }
        else
            music.setVolume(0.f);
        pac = sf::IntRect(frameNum * 50, rowNum * 50, 50, 50); 
        sf::Sprite playerImg(pacman, pac); 
        playerImg.setPosition(xpos, ypos);

        if (map[(ypos + 25)/50][(xpos + 25)/50] == 0)
            map[ypos/50][xpos/50] = -1;

                //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear


        for (int rows = 0; rows < 20; rows++)
            for (int cols = 0; cols < 20; cols++) {
                if (map[rows][cols] == 1 || map[rows][cols] == 2) {
                    wall.setPosition(cols * 50, rows * 50);
                    screen.draw(wall);
                }
                if (map[rows][cols] == 0) {
                    dot.setPosition(cols * 50 + 20, rows * 50 + 20);
                    screen.draw(dot);
                }
            }

        screen.draw(playerImg);

        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    std::cout << "goodbye!" << std::endl;
} //end of main

//Ghost::Ghost(int x, int y, int radius, int whichGhost) { //wow, constructor!
//    xPos = x;
//    yPos = y;
//    Width = radius + 3;
//    whichGhost = whichGhost;
//    isDead = false;
//}
//
//sf::Texture Ghost::ghostCreate() { //ghost generation function, see that function type?
//    sf::Texture ghost;
//    ghost.loadFromFile("ghost.png");
//    sf::IntRect ghost(0, 0, 50, 50);
//    sf::Sprite ghostImg(pacman, pac);
//    int ticker = 0;
//    int frameNum = 0;
//    int rowNum = 0;
//    platform.setFillColor(colorCode);
//    platform.setPosition(xPos, yPos);
//    return platform;
//}
//
//bool Platforms::ballCollision(int bx, int by) {
//    if ((bx >= xPos) && (bx <= xPos + 100) && (by < yPos + 50) && (by + 10 > yPos)) {
//        return true;
//    }
//    else
//        return false;
//}
//
//void Platforms::kill() {
//    isDead = true;
//}
//
//bool Platforms::checkDead() {
//    return isDead;
//}