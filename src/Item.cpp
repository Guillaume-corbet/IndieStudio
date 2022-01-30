/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Item
*/

#include "../include/Item.hpp"

Item::Item(int x, int y)
{
    _x = x;
    _y = y;

    std::map<PowerUp, int> probability;
    probability.emplace(BOMB, 10);
    probability.emplace(SPEED, 10);
    probability.emplace(FIRE, 10);
    probability.emplace(WALL, 1);

    int total = 0;
    for (PowerUp i = (PowerUp)0; i < probability.size(); i = (PowerUp)(i + 1))
        total += probability[i];
    int n = rand() % total;

    for (PowerUp i = (PowerUp)0; i < probability.size(); i = (PowerUp)(i + 1)) {
        if (n < probability[i]) {
            _power = i;
            return;
        } else
            n -= probability[i];
    }

    _power = BOMB;
    std::cout << "probability error in Item.cpp" << std::endl;
}

Item::~Item()
{
}

std::string Item::to_string()
{
    std::string result;
    int power_up = static_cast<int>(_power);
    
    result = std::to_string(power_up) + ";" + std::to_string(_x) + ";" + std::to_string(_y) + "#";

    return (result);
}

void Item::setPowerUp(int id)
{
    _power = static_cast<PowerUp>(id);
}

void Item::setX(int x)
{
    this->_x = x;
}

int Item::getX() const
{
    return (_x);
}

void Item::setY(int y)
{
    this->_y = y;
}

int Item::getY() const
{
    return (_y);
}

Item::PowerUp Item::getPower()
{
    return (_power);
}