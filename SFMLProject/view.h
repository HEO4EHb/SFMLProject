#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
sf::View view;
void setPlayercoordinateforview(float x, float y) 
{ //������� ��� ���������� ��������� ������
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (x < 100) tempX = 100;//������� �� ���� ����� �������
	if (y < 100) tempY = 100;//������� �������
	if (y > 554) tempY = 554;//������ �������	

	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 

}
View setPlayerCoordinateForView(float x, float y)
{
	view.setCenter(x + 100, y);
	return view;
}