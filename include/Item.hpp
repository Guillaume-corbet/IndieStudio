/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Item
*/

//#include <vector>
#include <string>
#include <iostream>

#include <map>
#include <stdlib.h>

#ifndef ITEM_HPP_
#define ITEM_HPP_

class Item
{
    public:
        enum PowerUp {
            BOMB = 0,
            SPEED,
            FIRE,
            WALL
        };
        Item(int x, int y);
        ~Item();
        void setX(int x);
        int getX() const;
        void setY(int y);
        int getY() const;
        void setPowerUp(int PowerUp);
        PowerUp getPower();
        std::string to_string();
    private:
        PowerUp _power;
        int _x;
        int _y;
};

#endif /* !ITEM_HPP_ */
