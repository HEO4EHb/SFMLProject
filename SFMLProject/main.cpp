#include <iostream> 
#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
using namespace sf;
class Enemy {
public:
	float x, y, w, h, dx, dy, speed = 0.08; // х и у, высота ширина, ускорение (по х и по у), сама скорость
	IntRect rect;
	int health, dir = 2; // (direction) 
	bool life;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return FloatRect(x, y, w, h);
	}

	Enemy(String F, float X, float Y, float W, float H) //координата Х и У, ширина и высота
	{
		health = 2;
		life = true;
		File = F;//file name 
		w = W; h = H;//width and height
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(32, 32, w, h));

	}
	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (dir)//direction
		{
		case 0: dx = speed; dy = 0;   break;// вправо
		case 1: dx = -speed; dy = 0;   break;// влево
		case 2: dx = 0; dy = speed;   break;// вниз
		case 3: dx = 0; dy = -speed;   break;// вверх
		}

		x += dx * time;//s.move(-0.1 * time, 0) тоже самое по факту     
		y += dy * time;//s.move(-0.1 * time, 0)0.1 это speed		

		
		sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
		interactionWithMap();
		if (health <= 0)
		{
			
			life = false; speed = 0;
		}

	}


	void interactionWithMap()
	{
		Clock clock;
		clock.restart();
		float time = clock.getElapsedTime().asMicroseconds();
		time = time / 600;
		float CurrentFrame = 0;
		// Я УМЕНЬШИЛ ТАК НАЗЫВАЕМЫЙ ХИТБОКС ПОТОМУ ЧТО ИНАЧЕ ЛИНК НЕ ПРОХОДИТ ЧЕРЕЗ УЗКИЕ ПРОЁМЫ
		for (int i = y / 30; i < (y + h) / 30; i++)
			for (int j = x / 30; j < (x + w) / 30; j++)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 's')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy > 0)// вниз
					{
						y = i * 30 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						dir = 2;
						speed = -0.08;
						sprite.setTextureRect(IntRect(32, 0, w, h));
					}
					if (dy < 0)
					{
						y = i * 30 + 30;// вверх
						dir = 3;
						speed = -0.08;
						sprite.setTextureRect(IntRect(32, 32, w, h));
					}
					if (dx > 0)
					{
						x = j * 30 - w;// вправо
						dir = 0;
						speed = -0.08;
						sprite.setTextureRect(IntRect(32, 64, w, h));
					}
					if (dx < 0)
					{
						dir = 1;
						x = j * 30 + 30;
						dir = 1;
						speed = -0.08;
						sprite.setTextureRect(IntRect(32, 96, w, h));
					}
				}
			}
	}




};

class Player {
public:
	float x, y, w, h, dx, dy, speed = 0; // х и у, высота ширина, ускорение (по х и по у), сама скорость
	IntRect rect;
	int health, dir = 0; // (direction) 
	bool life;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return FloatRect(x, y, w, h); 
	}

	Player(String F, int X, int Y, int W, int H) //координата Х и У, ширина и высота
	{
		health = 6;
		life = true;
		File = F;//file name 
		w = W; h = H;//width and height
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		rect = IntRect(0, 0, w, h);

	}



	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (dir)//direction
		{
		case 0: dx = speed; dy = 0;   break;// вправо
		case 1: dx = -speed; dy = 0;   break;// влево
		case 2: dx = 0; dy = speed;   break;// вниз
		case 3: dx = 0; dy = -speed;   break;// вверх
		}

		x += dx * time;//s.move(-0.1 * time, 0) тоже самое по факту     
		y += dy * time;//s.move(-0.1 * time, 0)0.1 это speed

		speed = 0;//зануляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
		interactionWithMap();
		if (health <= 0)
		{
			life = false; speed = 0;
		}
		if (life)
		{
			setPlayerCoordinateForView(x, y);
		}
	}

	/*float GetPlayerCoordinateX() //
	{
		return x;
	}
	float GetPlayerCoordinateY()
	{
		return y;
	}*/
	void interactionWithMap()
	{
		// Я УМЕНЬШИЛ ТАК НАЗЫВАЕМЫЙ ХИТБОКС ПОТОМУ ЧТО ИНАЧЕ ЛИНК НЕ ПРОХОДИТ ЧЕРЕЗ УЗКИЕ ПРОЁМЫ
		for (int i = y / 30; i < (y + h) / 30; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 30; j < (x + w) / 30; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 's')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy > 0)//если мы шли вниз,
					{
						y = i * 30 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					}
					if (dy < 0)
					{
						y = i * 30 + 30;
					}
					if (dx > 0)
					{
						x = j * 30 - w;// вправо то координата Х равна стена (символ 0) минус ширина персонажа
					}
					if (dx < 0)
					{
						x = j * 30 + 30;// влево
					}
				}
				if (TileMap[i][j] == 'h') {
					health += 1;//если взяли сердечко,то переменная health=health+20;
					TileMap[i][j] = ' ';//убрали сердечко
				}

			}
	}
};



int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Game works!");
	view.reset(sf::FloatRect(0, 0, 640, 480));

	float CurrentFrame = 0;// кадры
	Clock clock;


	Player p("Link_Movement.png", 100, 200, 30, 30);// координата Х,У, ширина, высота.
	Enemy enemy("RedOctorok_Movement.png", 50, 100, 33.0, 31.0);// координата Х,У, ширина, высота.


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 600;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		Image map_image;//объект изображения для карты
		map_image.loadFromFile("images/tileset.png");
		Texture map;
		map.loadFromImage(map_image);
		Sprite s_map;
		s_map.setTexture(map);

		if (p.life)
		{
			if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
				p.dir = 1; p.speed = 0.1;
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 97, 32, 32));
				//GetPlayerCoordinateforview(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
				p.dir = 0; p.speed = 0.1;
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 32, 32, 32));
				//GetPlayerCoordinateforview(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
				p.dir = 3; p.speed = 0.1;
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 65, 32, 32));
				//GetPlayerCoordinateforview(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
			}

			if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
				p.dir = 2; p.speed = 0.1;
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32));
				//GetPlayerCoordinateforview(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
			}
			if ((Keyboard::isKeyPressed(Keyboard::Z)))
			{
				switch (p.dir)//direction
				{
				case 0:p.sprite.setTextureRect(IntRect(72, 35, 59, 32)); p.speed = 0; break; // вправо							
				case 1:p.sprite.setTextureRect(IntRect(66, 99, 59, 32));   p.speed = 0;  break;// влево				
				case 2:p.sprite.setTextureRect(IntRect(148, 0, 32, 59));   p.speed = 0;  break;// вниз
				case 3: p.sprite.setTextureRect(IntRect(158, 65, 32, 59));  p.speed = 0;  break;// вверх
				}
			}

		}


		p.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
		enemy.update(time);
		if (p.getRect().intersects(enemy.getRect()))
		{
			switch (p.dir)//direction
			{
			case 0:p.sprite.setTextureRect(IntRect(92, 69, 30, 29)); p.speed = 0; p.x -= 2; break; // вправо							
			case 1:p.sprite.setTextureRect(IntRect(96, 0, 30, 29));   p.speed = 0; p.x += 2;  break;// влево				
			case 2:p.sprite.setTextureRect(IntRect(62, 0,29, 31));   p.speed = 0;  break;// вниз
			case 3: p.sprite.setTextureRect(IntRect(59, 67,29, 31));  p.speed = 0;  break;// вверх
			}
			if ((Keyboard::isKeyPressed(Keyboard::Z)))
			{
				enemy.health -= 1;
			}

		}

		window.setView(view);
		window.clear();


		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(32, 0, 31, 31));
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(64, 0, 31, 31));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(96, 448, 31, 31));
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(160, 64, 32, 31));
				if ((TileMap[i][j] == '2')) s_map.setTextureRect(IntRect(64, 448, 31, 31));
				if ((TileMap[i][j] == '4')) s_map.setTextureRect(IntRect(128, 448, 31, 31));
				if ((TileMap[i][j] == '3')) s_map.setTextureRect(IntRect(34, 448, 31, 31));
				if ((TileMap[i][j] == '5')) s_map.setTextureRect(IntRect(160, 448, 31, 31));
				if ((TileMap[i][j] == '1')) s_map.setTextureRect(IntRect(128, 0, 31, 31));
				s_map.setPosition(j * 31, i * 31);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
				window.draw(s_map);//рисуем квадратики на экран
			}
		window.draw(enemy.sprite);
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}