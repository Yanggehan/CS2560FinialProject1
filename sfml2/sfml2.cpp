#include "pch.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include <sstream>
#include <time.h>
using namespace sf;
int score1 = 0; // score
int z = 0;//Whether it failed
float timer1 = 0.0f, delay1 = 0.02f;


bool intersects(Sprite a, Sprite b)
{
	return a.getGlobalBounds().intersects(b.getGlobalBounds());//return true or false for collide;

}

int main()
{
	srand(time(0));
	sf::Clock clock;//make a clock
	
	RenderWindow window(VideoMode(847, 530), "Game");//Window that we can play the game in  
	window.setFramerateLimit(60);//set Framerate Limit

	Texture t1, t2, t3, t4; //made 4 texture for block ball borad and backgroud
	sf::Music music,music2;// 2 music
	music.openFromFile("BGM.ogg");
	music.setVolume(50);
	music.play();
	music2.openFromFile("A.ogg");
	music2.setVolume(50);
	
	t1.loadFromFile("images/block03.png");
	t2.loadFromFile("images/timg.jpg");
	t3.loadFromFile("images/ball.png");
	t4.loadFromFile("images/board2.png");


	sf::Font arial2;//made the fond
	arial2.loadFromFile("arial.ttf");//open the arial.ttf
	std::ostringstream  ss2;// made text
	ss2 << "you are failed ";
	sf::Text  text; // set the text
	text.setCharacterSize(30);//size
	text.setPosition({ 100,250 });// position
	text.setFont(arial2);//font
	text.setString(ss2.str());//text

	Sprite Background(t2), Ball(t3), Paddle(t4); // set the sprite
	Paddle.setPosition(400, 440);// set the position
	Ball.setPosition(200, 300);

	Sprite block[1000];
	Sprite block2[1000];//made some empty block
	//made the block like a triangle.
	int n = 0;
	for (int i =16; i >= 1; i--) {

		for (int j = 1; j <= 15-i; j++)
		{
			block2[n].setPosition(i * 43, j * 10);
		}

		for (int k = 0; k < 2 * i - 1; k++) {
			block[n].setTexture(t1);
			block[n].setPosition(i * 43, k * 10);

			n++;
		}
	}
	float dx =5, dy = 5;
	//float x = 300, y = 300;

	while (window.isOpen())
	{
		float time1 = clock.getElapsedTime().asSeconds();//set the time 


		clock.restart();

		timer1 += time1;
		//Allow us to check when a user does something 
		sf::Event e;
		while (window.pollEvent(e))
		{
			//If user presses x in the top right, Windows, top left, Mac,  close the window 
			if (e.type == Event::Closed)
				window.close();
		}

		//x += dx;

		if (timer1 > delay1)

		{
			timer1 = 0; //reset timer 
			Ball.move(dx, 0);
			/*sf::Vector2f pos = object.getPosition();
						object.setPosition(pos.x + offsetX, pos.y + offsetY);
						posion + dx*/
			//Vector2f b = sBall.getPosition();
			for (int i = 0; i < n; i++)
				if (intersects(Ball, block[i]))// check the intersects between ball and block
				{
					block[i]=block2[i];
					dx = -dx;
					score1 += 1;
					music2.play();
				}

			//y += dy;
			Ball.move(0, dy);

			for (int i = 0; i < n; i++)
				if (intersects(Ball, block[i]))
				{
					block[i] = block2[i];
					dy = -dy;
					score1 += 1;
					music2.play();
				}

			Vector2f a = Ball.getPosition(); // get the sprite value (x,y)

			if (a.x < 0 || a.x>847)
			 dx = -dx;
			
			if (a.y < 0 )
				dy = -dy;
			if ( a.y> 530)
			{//dy = -dy;
				z = 1;
			}
			//if (intersects(Paddle, Ball)) dy = -(rand() % 5 +1);
			if (intersects(Paddle, Ball))
			{
				//dx = -dx;
				dy = -dy;
			}
			
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Right)) Paddle.move(7, 0);
		if (Keyboard::isKeyPressed(Keyboard::Left)) Paddle.move(-7, 0);

		


		window.clear();
		window.draw(Background);
		window.draw(Ball);
		window.draw(Paddle);
		sf::Font arial;
		arial.loadFromFile("arial.ttf");
		std::ostringstream ss;
		ss << "play1 score: " << score1;
		//ss2 << "you are lose ";
		sf::Text gamescore1;
		gamescore1.setCharacterSize(30);
		gamescore1.setPosition({ 10,460 });
		gamescore1.setFont(arial);
		gamescore1.setString(ss.str());
		window.draw(gamescore1);
		/*text.setCharacterSize(30);
		text.setPosition({ 200,250 });
		text.setFont(arial);
		text.setString(ss2.str());
		app.draw(text);*/
		if (z == 1)
		{
			window.draw(text);
		}
		
		for (int i = 0; i < n; i++)
			window.draw(block[i]);

		window.display();
	}

	return 0;
}