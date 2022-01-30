/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include <vector>
#include "Graphique.hpp"
#include "ICharacter.hpp"
#include "Item.hpp"
#include "Display.hpp"

class ICharacter;
class Display;

class Bomb {
    public:
        Bomb(int range, int x, int y, irr::u32 timer, int id);
        ~Bomb();
        void setRange(int range);
        void setTimer(irr::u32 timer);
        void setDelay(irr::u32);
        void setX(int x);
        void setY(int y);
        void setId(int id);
        void spawnItem(std::vector<std::string> &map, std::vector<Item *> &item, int y, int x);
        int getRange() const;
        int getX() const;
        int getY() const;
        int getId() const;
        irr::u32 getTimer() const;
        irr::u32 getDelay() const;
        bool explode(irr::u32 timer, std::vector<std::string> &_map, std::vector<ICharacter *> &charac, std::vector<Item *> &item, Display *display);
        std::string to_string(Graphique *graph);
    private:
        int _range;
        irr::u32 _timer;
        irr::u32 _delay;
        int _x;
        int _y;
        int _id;
};

#endif /* !BOMB_HPP_ */