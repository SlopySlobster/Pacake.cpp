#include<iostream>
#include<random>
#include "SFML/Graphics.hpp"
#include "ghost.h" 


using namespace std;

//enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3

int main() {
	//game set up (you'll need these lines in every game)
	sf::RenderWindow screen(sf::VideoMode(1600, 960), "breakout"); //set up screen
	sf::Event event; //set up event queue
	sf::Clock clock; //set up the clock (needed for game timing)
	const float FPS = 60.0f; //FPS
	screen.setFramerateLimit(FPS); //set FPS

	//load in images
	sf::Texture brick;
	brick.loadFromFile("cake.png");
	sf::Sprite wall;
	wall.setTexture(brick);

	sf::Texture pacman;
	pacman.loadFromFile("pac.png");
	sf::IntRect pac(0, 0, 70, 70);
	sf::Sprite playerImg(pacman, pac);

	//animation variables
	int ticker = 0;
	int rowNum = 0;
	int frameNum = 0;
	int direction = 0;


	int map[12][20] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
		1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,
		1,0,1,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,
		1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,1,
		1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,1,
		1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,
		1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,1,1,1,0,1,
		1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,1,
		1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

	};

	//player setup
	int xpos = 85;
	int ypos = 85;
	int vx = 0;
	int vy = 0;
	int radius = 30;
	sf::CircleShape player(radius);
	player.setFillColor(sf::Color(250, 250, 0)); //using RGB value for color here (hex also works)
	player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
	bool keys[] = { false, false, false, false };

	sf::CircleShape dot(5);
	dot.setFillColor(sf::Color(250, 250, 0));


	ghost Blinky;
	ghost Ginky;
	ghost Pinky;
	ghost Inky;
	Blinky.initGhost(80, 80, 0, 0, 0, 1);
	Inky.initGhost(80, 80, 0, 0, 0, 2);
	Pinky.initGhost(80, 80, 0, 0, 0, 3);
	Ginky.initGhost(80, 80, 0, 0, 0, 4);
	Blinky.printInfo();
	Inky.printInfo();
	Pinky.printInfo();
	Ginky.printInfo();
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

		//Movement Algorithm
		if (keys[LEFT] == true)
			vx = -5;

		else if (keys[RIGHT] == true)
			vx = 5;

		else
			vx = 0;

		if (keys[UP] == true)
			vy = -5;

		else if (keys[DOWN] == true)
			vy = 5;

		else {

			vy = 0;
		}

		//RIGHT collision
		if (vx > 0 &&
			//TOP right
			((map[(ypos) / 80][(xpos + (radius * 2) + 5) / 80] == 1) ||
				//BOTTOM right
				(map[(ypos + (radius * 2)) / 80][(xpos + (radius * 2) + 5) / 80] == 1)))
		{
			cout << "right collision" << endl;
			vx = 0;
		}
		//LEFT collision
		if (vx < 0 && ((map[(ypos) / 80][(xpos - 5) / 80] == 1) || (map[((ypos + radius * 2) / 80)][(xpos - 5) / 80] == 1)))
		{
			cout << "left collision" << endl;
			vx = 0;
		}
		//UP collision
		if (vy < 0 && ((map[(ypos - 5) / 80][(xpos) / 80] == 1) || (map[(ypos - 5) / 80][(xpos + radius * 2) / 80] == 1)))
		{
			cout << "up collision" << endl;
			vy = 0;
		}
		//DOWN collision
		if (vy > 0 && ((map[(ypos + radius * 2 + 5) / 80][(xpos) / 80] == 1) || (map[(ypos + radius * 2 + 5) / 80][(xpos + radius * 2) / 80] == 1)))
		{
			cout << "down collision" << endl;
			vy = 0;
		}

		//update pac's position
		xpos += vx;
		ypos += vy;
		player.setPosition(xpos, ypos);


		//animation

		//if (vx != 0 || vy != 0) {
			ticker += 1;
				if (ticker % 10 == 0)
					frameNum += 1;
			if (frameNum > 3)
				frameNum = 0;

		//}
		if (keys[RIGHT] == true) rowNum = 0;
		else if (keys[LEFT] == true)rowNum = 1;
		else if (keys[UP] == true)rowNum = 2;
		else if (keys[DOWN] == true)rowNum = 3;

		pac = sf::IntRect(frameNum * 70, rowNum * 70, 68, 68);
		sf::Sprite playerImg(pacman, pac);
		playerImg.setPosition(xpos, ypos);


		//GHOST AI-----------------------------------
		Blinky.chase1(xpos, ypos, map);
		Inky.chase1((xpos + ypos) / 2, ypos / 1.5, map);
		Pinky.chase1(xpos - 10, ypos - 10, map);
		Ginky.chase1(rand() % xpos, rand() % ypos, map);

		//check if pac's position has a 0(dot), if so, change it to a -1
		if (map[ypos / 80][xpos / 80] == 0)
			map[ypos / 80][xpos / 80] = -1;

		//render section-----------------------------------------
		screen.clear(); //wipes screen, without this things smear

		//this draws the map
		for (int rows = 0; rows < 12; rows++)
			for (int cols = 0; cols < 20; cols++) {
				if (map[rows][cols] == 1) {
					wall.setPosition(cols * 80, rows * 80);
					screen.draw(wall);
				}
				//add an if statement that draws the dot

				if (map[rows][cols] == 0) {
					dot.setPosition((cols * 80) + 40, (rows * 80) + 40);
					screen.draw(dot);

				}

			}

		Blinky.drawGhost(screen);
		Inky.drawGhost(screen);
		Pinky.drawGhost(screen);
		Ginky.drawGhost(screen);
		screen.draw(playerImg); //draw player
		screen.display(); //flips memory drawings onto screen

	}//######################## end game loop ###################################################################################

	cout << "goodbye!" << endl;
} //end of main
