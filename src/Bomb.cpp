/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include "../include/Bomb.hpp"

Bomb::Bomb(int range, int x, int y, irr::u32 timer, int id)
{
    _x = x;
    _y = y;
    _range = range;
    _timer = timer;
    _delay = 3000;
    this->_id = id;
}

Bomb::~Bomb()
{
}

std::string Bomb::to_string(Graphique *graph)
{
    std::string result;

    result = std::to_string(_range) + ";" + std::to_string(static_cast<int>(_timer)) + ";" + std::to_string(static_cast<int>(graph->getDevice()->getTimer()->getTime() - _timer)) + ";" + std::to_string(_x) + ";" + std::to_string(_y) + ";" + std::to_string(_id) + "#";

    return (result);
}

void Bomb::setRange(int range)
{
    this->_range = range;
}

int Bomb::getRange() const
{
    return (this->_range);
}

void Bomb::setTimer(irr::u32 timer)
{
    this->_timer = timer;
}

irr::u32 Bomb::getTimer() const
{
    return (this->_timer);
}

void Bomb::setDelay(irr::u32 delay)
{
    this->_delay = delay;
}

irr::u32 Bomb::getDelay() const
{
    return (this->_delay);
}

void Bomb::setX(int x)
{
    this->_x = x;
}

int Bomb::getX() const
{
    return (this->_x);
}

void Bomb::setY(int y)
{
    this->_y = y;
}

int Bomb::getY() const
{
    return (this->_y);
}

void Bomb::setId(int id)
{
    this->_id = id;
}

int Bomb::getId() const
{
    return (this->_id);
}

void Bomb::spawnItem(std::vector<std::string> &map, std::vector<Item *> &item, int y, int x)
{
    int spawn = std::rand() % 3 + 1;

    if (spawn == 1) {
        item.push_back(new Item(x, y));
        map.at(y).at(x) = 'I';
    } else
        map.at(y).at(x) = ' ';
}

bool Bomb::explode(irr::u32 timer, std::vector<std::string> &map, std::vector<ICharacter *> &charac, std::vector<Item *> &item, Display *display)
{
    int up;
    int right;
    int down;
    int left;

    if (timer > _timer + _delay) {
        map.at(_y).at(_x) = ' ';

        for (up = 0; (map.at(_y - up).at(_x) == ' ' || map.at(_y - up).at(_x) == 'I') && up < _range; up++);
        for (right = 0; (map.at(_y).at(_x + right) == ' ' || map.at(_y).at(_x + right) == 'I') && right < _range; right++);
        for (down = 0; (map.at(_y + down).at(_x) == ' ' || map.at(_y + down).at(_x) == 'I') && down < _range; down++);
        for (left = 0; (map.at(_y).at(_x - left) == ' ' || map.at(_y).at(_x - left) == 'I') && left < _range; left++);

        if (map.at(_y - up).at(_x) == 'W') {
            map.at(_y - up).at(_x) = ' ';
            spawnItem(map, item, _y - up, _x);
        }
        if (map.at(_y).at(_x + right) == 'W') {
            map.at(_y).at(_x + right) = ' ';
            spawnItem(map, item, _y, _x + right);
        }
        if (map.at(_y + down).at(_x) == 'W') {
            map.at(_y + down).at(_x) = ' ';
            spawnItem(map, item, _y + down, _x);
        }
        if (map.at(_y).at(_x - left) == 'W') {
            map.at(_y).at(_x - left) = ' ';
            spawnItem(map, item, _y, _x - left);
        }

        for (size_t i = 0; i < charac.size(); i++) {
            if (charac.at(i)->getId() == _id)
                charac.at(i)->setNbBomb(charac.at(i)->getNbBomb() + 1);
            if ((charac.at(i)->getX() == _x && charac.at(i)->getY() >= _y - up && charac.at(i)->getY() <= _y + down) ||
            (charac.at(i)->getY() == _y && charac.at(i)->getX() >= _x - left && charac.at(i)->getX() <= _x + right)) {
                std::cout << "bombe " << _x << ":" << _y << " kill player " << charac.at(i)->getX() << ":" << charac.at(i)->getY() << std::endl;
                charac.at(i)->~ICharacter();
                charac.erase(charac.begin() + i);
                i--;
            }
        }

        display->bombe_flame(_x, _y, up, right, down, left);

        std::cout << "explosion" << std::endl;
        return (true);
    }
    return (false);
}
