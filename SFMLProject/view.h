#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
sf::View view;
void setPlayercoordinateforview(float x, float y) 
{ //функция для считывания координат игрока
	float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < 100) tempX = 100;//убираем из вида левую сторону
	if (y < 100) tempY = 100;//верхнюю сторону
	if (y > 554) tempY = 554;//нижнюю сторону	

	view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты. 

}
View setPlayerCoordinateForView(float x, float y)
{
	view.setCenter(x + 100, y);
	return view;
}