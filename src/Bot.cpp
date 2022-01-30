/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bot
*/

#include "../include/Bot.hpp"

Bot::Bot(int x, int y, int id)
{
    this->_x = x;
    this->_y = y;
    this->_timerMove = 0;
    this->_power = 3;
    this->_speed = 500;
    this->_nbBomb = 1;
    this->_wall = false;
    this->_id = id;
}

Bot::~Bot()
{
}

std::string Bot::to_string()
{
    std::string result;

    result = std::to_string(_x) + ";" + std::to_string(_y) + ";" + std::to_string(_timerMove) + ";" + std::to_string(_power) + ";" + std::to_string(_speed) + ";" + std::to_string(_nbBomb) + ";" + std::to_string(_wall) + ";" + std::to_string(_id) + ";" + "0" + "#";
    
    return (result);
}

void Bot::setX(int x)
{
    this->_x = x;
}

int Bot::getX() const
{
    return (this->_x);
}

void Bot::setY(int y)
{
    this->_y = y;
}

int Bot::getY() const
{
    return (this->_y);
}

void Bot::setTimerMove(irr::u32 timer)
{
    this->_timerMove = timer;
}

irr::u32 Bot::getTimerMove() const
{
    return (this->_timerMove);
}

void Bot::setPower(int power)
{
    this->_power = power;
}

int Bot::getPower() const
{
    return (this->_power);
}

void Bot::setSpeed(irr::u32 speed)
{
    this->_speed = speed;
}

irr::u32 Bot::getSpeed() const
{
    return (this->_speed);
}

void Bot::setId(int id)
{
    this->_id = id;
}

int Bot::getId() const
{
    return (this->_id);
}

void Bot::setNbBomb(int nbBomb)
{
    this->_nbBomb = nbBomb;
}

int Bot::getNbBomb() const
{
    return (this->_nbBomb);
}

void Bot::setCommand(std::vector<irr::EKEY_CODE> command)
{
    this->_command = command;
}

std::vector<irr::EKEY_CODE> Bot::getCommand() const
{
    return (this->_command);
}

void Bot::setWall(bool wall)
{
    this->_wall = wall;
}

bool Bot::getWall() const
{
    return (this->_wall);
}

void Bot::upgrade(std::vector<Item *> item)
{
    for (size_t i = 0; i < item.size(); i++) {
        if (item.at(i)->getX() == this->_x && item.at(i)->getY() == this->_y) {
            if (item.at(i)->getPower() == Item::PowerUp::SPEED)
                this->_speed = this->_speed - 50;
            else if (item.at(i)->getPower() == Item::PowerUp::FIRE)
                this->_power = this->_power + 1;
            else if (item.at(i)->getPower() == Item::PowerUp::WALL)
                this->_wall = true;
            else if (item.at(i)->getPower() == Item::PowerUp::BOMB)
                this->_nbBomb = this->_nbBomb + 1;
        }
    }
}

bool Bot::isInDanger(std::vector<std::string> map, int x, int y)
{
    for (size_t i = 0; i < 5 && (x + i) < map.at(y).size(); i++) {
        if (map.at(y).at(x + i) == 'B') {
            return (true);
        }
    }
    for (int i = 0; i < 5 && (x - i) >= 0; i++) {
        if (map.at(y).at(x - i) == 'B') {
            return (true);
        }
    }
    for (size_t i = 0; i < 5 && (y + i) < map.size(); i++) {
        if (map.at(y + i).at(x) == 'B') {
            return (true);
        }
    }
    for (int i = 0; i < 5 && (y - i) >= 0; i++) {
        if (map.at(y - i).at(x) == 'B') {
            return (true);
        }
    }
    return (false);
}

bool Bot::isFreeCase(std::vector<std::string> map, int x, int y)
{
    if (map.at(_y + y).at(_x + x) != 'W' && map.at(_y + y).at(_x + x) != '@' && map.at(_y + y).at(_x + x) != '#' && map.at(_y + y).at(_x + x) != 'B')
        return (true);
    return (false);
}

bool Bot::isFreeCaseCo(std::vector<std::string> map, int x, int y)
{
    if (map.at(y).at(x) != 'W' && map.at(y).at(x) != '@' && map.at(y).at(x) != '#' && map.at(y).at(x) != 'B') {
        return (true);
    }
    return (false);
}

int Bot::iaEscapeBomb(std::vector<std::string> map)
{
    int result = 5;
    int min = 999;

    if (isInDanger(map, _x, _y) == true) {
        for (size_t i = 1; (_x + i) < map.at(_y).size() && isFreeCaseCo(map, _x + i, _y) == true; i++) {
            if (isInDanger(map, _x + i, _y) == false) {
                if (i < min) {
                    min = i;
                    result = 1;
                }
            } else {
                for (size_t j = 1; (_y + j) < map.size() && isFreeCaseCo(map, _x + i, _y + j) == true; j++) {
                    if (isInDanger(map, _x + i, _y + j) == false) {
                        if ((i + j) < min) {
                            min = i + j;
                            result = 1;
                        }
                    } else {
                        for (size_t k = 1; (_x + i + k) < map.size() && isFreeCaseCo(map, _x + i + k, _y + j) == true; k++) {
                            if (isInDanger(map, _x + i + k, _y + j) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 1;
                                }
                            }
                        }
                        for (int k = 1; (_x + i - k) >= 0 && isFreeCaseCo(map, _x + i - k, _y + j) == true; k++) {
                            if (isInDanger(map, _x + i - k, _y + j) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 1;
                                }
                            }
                        }
                    }
                }
                for (int j = 1; (_y - j) >= 0 && isFreeCaseCo(map, _x + i, _y - j) == true; j++) {
                    if (isInDanger(map, _x + i, _y - j) == false) {
                        if ((i + j) < min) {
                            min = i + j;
                            result = 1;
                        }
                    } else {
                        for (size_t k = 1; (_x + i + k) < map.size() && isFreeCaseCo(map, _x + i + k, _y - j) == true; k++) {
                            if (isInDanger(map, _x + i + k, _y - j) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 1;
                                }
                            }
                        }
                        for (int k = 1; (_x + i - k) >= 0 && isFreeCaseCo(map, _x + i - k, _y - j) == true; k++) {
                            if (isInDanger(map, _x + i - k, _y - j) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (size_t i = 1; (_y + i) < map.size() && isFreeCaseCo(map, _x, _y + i) == true; i++) {
            if (isInDanger(map, _x, _y + i) == false) {
                if (i < min) {
                    min = i;
                    result = 2;
                }
            } else {
                for (size_t j = 1; (_x + j) < map.at(_y + i).size() && isFreeCaseCo(map, _x + j, _y + i) == true; j++) {
                    if (isInDanger(map, _x + j, _y + i) == false) {
                        if ((i + j) < min) {
                            min = i + j;
                            result = 2;
                        }
                    } else {
                        for (size_t k = 1; (_y + i + k) < map.size() && isFreeCaseCo(map, _x + j, _y + i + k) == true; k++) {
                            if (isInDanger(map, _x + j, _y + i + k) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 2;
                                }
                            }
                        }
                        for (int k = 1; (_y + i - k) >= 0 && isFreeCaseCo(map, _x + j, _y + i - k) == true; k++) {
                            if (isInDanger(map, _x + j, _y + i - k) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 2;
                                }
                            }
                        }
                    }
                }
                for (int j = 1; (_x - j) >= 0 && isFreeCaseCo(map, _x - j, _y + i) == true; j++) {
                    if (isInDanger(map, _x - j, _y + i) == false) {
                        if ((i + j) < min) {
                            min = i + j;
                            result = 2;
                        }
                    } else {
                        for (size_t k = 1; (_y + i + k) < map.size() && isFreeCaseCo(map, _x - j, _y + i + k) == true; k++) {
                            if (isInDanger(map, _x - j, _y + i + k) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 2;
                                }
                            }
                        }
                        for (int k = 1; (_y + i - k) >= 0 && isFreeCaseCo(map, _x - j, _y + i - k) == true; k++) {
                            if (isInDanger(map, _x - j, _y + i - k) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 2;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i = 1; (_x - i) >= 0 && isFreeCaseCo(map, _x - i, _y) == true; i++) {
            if (isInDanger(map, _x - i, _y) == false) {
                if (i < min) {
                    min = i;
                    result = 3;
                }
            } else {
                for (size_t j = 1; (_y + j) < map.size() && isFreeCaseCo(map, _x - i, _y + j) == true; j++) {
                    if (isInDanger(map, _x - i, _y + j) == false) {
                        if ((i + j) < min) {
                            min = i + j;
                            result = 3;
                        }
                    } else {
                        for (size_t k = 1; (_x - i + k) < map.size() && isFreeCaseCo(map, _x - i + k, _y + j) == true; k++) {
                            if (isInDanger(map, _x - i + k, _y + j) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 3;
                                }
                            }
                        }
                        for (int k = 1; (_x - i - k) >= 0 && isFreeCaseCo(map, _x - i - k, _y + j) == true; k++) {
                            if (isInDanger(map, _x - i - k, _y + j) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 3;
                                }
                            }
                        }
                    }
                }
                for (int j = 1; (_y - j) >= 0 && isFreeCaseCo(map, _x - i, _y - j) == true; j++) {
                    if (isInDanger(map, _x - i, _y - j) == false) {
                        if ((i + j) < min) {
                            min = i + j;
                            result = 3;
                        }
                    } else {
                        for (size_t k = 1; (_x - i + k) < map.size() && isFreeCaseCo(map, _x - i + k, _y - j) == true; k++) {
                            if (isInDanger(map, _x - i + k, _y - j) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 3;
                                }
                            }
                        }
                        for (int k = 1; (_x - i - k) >= 0 && isFreeCaseCo(map, _x - i - k, _y - j) == true; k++) {
                            if (isInDanger(map, _x - i - k, _y - j) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 3;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i = 1; (_y - i) >= 0 && isFreeCaseCo(map, _x, _y - i) == true; i++) {
            if (isInDanger(map, _x, _y - i) == false) {
                if (i < min) {
                    min = i;
                    result = 4;
                }
            } else {
                for (size_t j = 1; (_x + j) < map.at(_y - i).size() && isFreeCaseCo(map, _x + j, _y - i) == true; j++) {
                    if (isInDanger(map, _x + j, _y - i) == false) {
                        if ((i + j) < min) {
                            min = i + j;
                            result = 4;
                        }
                    } else {
                        for (size_t k = 1; (_y - i + k) < map.size() && isFreeCaseCo(map, _x + j, _y - i + k) == true; k++) {
                            if (isInDanger(map, _x + j, _y - i + k) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 4;
                                }
                            }
                        }
                        for (int k = 1; (_y - i - k) >= 0 && isFreeCaseCo(map, _x + j, _y - i - k) == true; k++) {
                            if (isInDanger(map, _x + j, _y - i - k) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 4;
                                }
                            }
                        }
                    }
                }
                for (int j = 1; (_x - j) >= 0 && isFreeCaseCo(map, _x - j, _y - i) == true; j++) {
                    if (isInDanger(map, _x - j, _y - i) == false) {
                        if ((i + j) < min) {
                            min = i + j;
                            result = 4;
                        }
                    } else {
                        for (size_t k = 1; (_y - i + k) < map.size() && isFreeCaseCo(map, _x - j, _y - i + k) == true; k++) {
                            if (isInDanger(map, _x - j, _y - i + k) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 4;
                                }
                            }
                        }
                        for (int k = 1; (_y - i - k) >= 0 && isFreeCaseCo(map, _x - j, _y - i - k) == true; k++) {
                            if (isInDanger(map, _x - j, _y - i - k) == false) {
                                if ((i + j + k) < min) {
                                    min = i + j + k;
                                    result = 4;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return (result);
}

int Bot::iaSearchItem(std::vector<std::string> map)
{
    int result = 5;
    int min = 999;

    for (size_t i = 1; (_x + i) < map.at(_y).size() && isFreeCaseCo(map, _x + i, _y) == true && isInDanger(map, _x + i, _y) == false; i++) {
        if (map.at(_y).at(_x + i) == 'I') {
            if (i < min) {
                min = i;
                result = 1;
            }
        } else {
            for (size_t j = 1; (_y + j) < map.size() && isFreeCaseCo(map, _x + i, _y + j) == true && isInDanger(map, _x + i, _y + j) == false; j++) {
                if (map.at(_y + j).at(_x + i) == 'I') {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 1;
                    }
                } else {
                    for (size_t k = 1; (_x + i + k) < map.size() && isFreeCaseCo(map, _x + i + k, _y + j) == true && isInDanger(map, _x + i + k, _y + j) == false; k++) {
                        if (map.at(_y + j).at(_x + i + k) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 1;
                            }
                        }
                    }
                    for (int k = 1; (_x + i - k) >= 0 && isFreeCaseCo(map, _x + i - k, _y + j) == true && isInDanger(map, _x + i - k, _y + j) == false; k++) {
                        if (map.at(_y + j).at(_x + i - k) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 1;
                            }
                        }
                    }
                }
            }
            for (int j = 1; (_y - j) >= 0 && isFreeCaseCo(map, _x + i, _y - j) == true && isInDanger(map, _x + i, _y - j) == false; j++) {
                if (map.at(_y - j).at(_x + i) == 'I') {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 1;
                    }
                } else {
                    for (size_t k = 1; (_x + i + k) < map.size() && isFreeCaseCo(map, _x + i + k, _y - j) == true && isInDanger(map, _x + i + k, _y - j) == false; k++) {
                        if (map.at(_y - j).at(_x + i + k) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 1;
                            }
                        }
                    }
                    for (int k = 1; (_x + i - k) >= 0 && isFreeCaseCo(map, _x + i - k, _y - j) == true && isInDanger(map, _x + i - k, _y - j) == false; k++) {
                        if (map.at(_y - j).at(_x + i - k) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    for (size_t i = 1; (_y + i) < map.size() && isFreeCaseCo(map, _x, _y + i) == true && isInDanger(map, _x, _y + i) == false; i++) {
        if (map.at(_y + i).at(_x) == 'I') {
            if (i < min) {
                min = i;
                result = 2;
            }
        } else {
            for (size_t j = 1; (_x + j) < map.at(_y + i).size() && isFreeCaseCo(map, _x + j, _y + i) == true && isInDanger(map, _x + j, _y + i) == false; j++) {
                if (map.at(_y + i).at(_x + j) == 'I') {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 2;
                    }
                } else {
                    for (size_t k = 1; (_y + i + k) < map.size() && isFreeCaseCo(map, _x + j, _y + i + k) == true && isInDanger(map, _x + j, _y + i + k) == false; k++) {
                        if (map.at(_y + i + k).at(_x + j) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 2;
                            }
                        }
                    }
                    for (int k = 1; (_y + i - k) >= 0 && isFreeCaseCo(map, _x + j, _y + i - k) == true && isInDanger(map, _x + j, _y + i - k) == false; k++) {
                        if (map.at(_y + i - k).at(_x + j) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 2;
                            }
                        }
                    }
                }
            }
            for (int j = 1; (_x - j) >= 0 && isFreeCaseCo(map, _x - j, _y + i) == true && isInDanger(map, _x - j, _y + i) == false; j++) {
                if (map.at(_y + i).at(_x - j) == 'I') {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 2;
                    }
                } else {
                    for (size_t k = 1; (_y + i + k) < map.size() && isFreeCaseCo(map, _x - j, _y + i + k) == true && isInDanger(map, _x - j, _y + i + k) == false; k++) {
                        if (map.at(_y + i + k).at(_x - j) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 2;
                            }
                        }
                    }
                    for (int k = 1; (_y + i - k) >= 0 && isFreeCaseCo(map, _x - j, _y + i - k) == true && isInDanger(map, _x - j, _y + i - k) == false; k++) {
                        if (map.at(_y + i - k).at(_x - j) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 2;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 1; (_x - i) >= 0 && isFreeCaseCo(map, _x - i, _y) == true && isInDanger(map, _x - i, _y) == false; i++) {
        if (map.at(_y).at(_x - i) == 'I') {
            if (i < min) {
                min = i;
                result = 3;
            }
        } else {
            for (size_t j = 1; (_y + j) < map.size() && isFreeCaseCo(map, _x - i, _y + j) == true && isInDanger(map, _x - i, _y + j) == false; j++) {
                if (map.at(_y + j).at(_x - i) == 'I') {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 3;
                    }
                } else {
                    for (size_t k = 1; (_x - i + k) < map.size() && isFreeCaseCo(map, _x - i + k, _y + j) == true && isInDanger(map, _x - i + k, _y + j) == false; k++) {
                        if (map.at(_y + j).at(_x - i + k) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 3;
                            }
                        }
                    }
                    for (int k = 1; (_x - i - k) >= 0 && isFreeCaseCo(map, _x - i - k, _y + j) == true && isInDanger(map, _x - i - k, _y + j) == false; k++) {
                        if (map.at(_y + j).at(_x - i - k) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 3;
                            }
                        }
                    }
                }
            }
            for (int j = 1; (_y - j) >= 0 && isFreeCaseCo(map, _x - i, _y - j) == true && isInDanger(map, _x - i, _y - j) == false; j++) {
                if (map.at(_y - j).at(_x - i) == 'I') {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 3;
                    }
                } else {
                    for (size_t k = 1; (_x - i + k) < map.size() && isFreeCaseCo(map, _x - i + k, _y - j) == true && isInDanger(map, _x - i + k, _y - j) == false; k++) {
                        if (map.at(_y - j).at(_x - i + k) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 3;
                            }
                        }
                    }
                    for (int k = 1; (_x - i - k) >= 0 && isFreeCaseCo(map, _x - i - k, _y - j) == true && isInDanger(map, _x - i - k, _y - j) == false; k++) {
                        if (map.at(_y - j).at(_x - i - k) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 3;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 1; (_y - i) >= 0 && isFreeCaseCo(map, _x, _y - i) == true && isInDanger(map, _x, _y - i) == false; i++) {
        if (map.at(_y - i).at(_x) == 'I') {
            if (i < min) {
                min = i;
                result = 4;
            }
        } else {
            for (size_t j = 1; (_x + j) < map.at(_y - i).size() && isFreeCaseCo(map, _x + j, _y - i) == true && isInDanger(map, _x + j, _y - i) == false; j++) {
                if (map.at(_y - i).at(_x + j) == 'I') {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 4;
                    }
                } else {
                    for (size_t k = 1; (_y - i + k) < map.size() && isFreeCaseCo(map, _x + j, _y - i + k) == true && isInDanger(map, _x + j, _y - i + k) == false; k++) {
                        if (map.at(_y - i + k).at(_x + j) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 4;
                            }
                        }
                    }
                    for (int k = 1; (_y - i - k) >= 0 && isFreeCaseCo(map, _x + j, _y - i - k) == true && isInDanger(map, _x + j, _y - i - k) == false; k++) {
                        if (map.at(_y - i - k).at(_x + j) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 4;
                            }
                        }
                    }
                }
            }
            for (int j = 1; (_x - j) >= 0 && isFreeCaseCo(map, _x - j, _y - i) == true  && isInDanger(map, _x - j, _y - i) == false; j++) {
                if (map.at(_y - i).at(_x - j) == 'I') {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 4;
                    }
                } else {
                    for (size_t k = 1; (_y - i + k) < map.size() && isFreeCaseCo(map, _x - j, _y - i + k) == true && isInDanger(map, _x - j, _y - i + k) == false; k++) {
                        if (map.at(_y - i + k).at(_x - j) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 4;
                            }
                        }
                    }
                    for (int k = 1; (_y - i - k) >= 0 && isFreeCaseCo(map, _x - j, _y - i - k) == true && isInDanger(map, _x - j, _y - i - k) == false; k++) {
                        if (map.at(_y - i - k).at(_x - j) == 'I') {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 4;
                            }
                        }
                    }
                }
            }
        }
    }
    return (result);
}

bool Bot::isPlayerHere(std::vector<ICharacter *> charac, int x, int y)
{
    for (size_t i = 0; i < charac.size(); i++) {
        if (charac.at(i)->getX() == x && charac.at(i)->getY() == y)
            return (true);
    }
    return (false);
}

int Bot::iaChasePlayer(std::vector<std::string> map, std::vector<ICharacter *> charac)
{
    int result = 5;
    int min = 999;

    for (size_t i = 1; (_x + i) < map.at(_y).size() && isFreeCaseCo(map, _x + i, _y) == true && isInDanger(map, _x + i, _y) == false; i++) {
        if (isPlayerHere(charac, _x + i, _y) == true) {
            if (i < min) {
                min = i;
                result = 1;
            }
        } else {
            for (size_t j = 1; (_y + j) < map.size() && isFreeCaseCo(map, _x + i, _y + j) == true && isInDanger(map, _x + i, _y + j) == false; j++) {
                if (isPlayerHere(charac, _x + i, _y + j) == true) {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 1;
                    }
                } else {
                    for (size_t k = 1; (_x + i + k) < map.size() && isFreeCaseCo(map, _x + i + k, _y + j) == true && isInDanger(map, _x + i + k, _y + j) == false; k++) {
                        if (isPlayerHere(charac, _x + i + k, _y + j) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 1;
                            }
                        }
                    }
                    for (int k = 1; (_x + i - k) >= 0 && isFreeCaseCo(map, _x + i - k, _y + j) == true && isInDanger(map, _x + i - k, _y + j) == false; k++) {
                        if (isPlayerHere(charac, _x + i - k, _y + j) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 1;
                            }
                        }
                    }
                }
            }
            for (int j = 1; (_y - j) >= 0 && isFreeCaseCo(map, _x + i, _y - j) == true && isInDanger(map, _x + i, _y - j) == false; j++) {
                if (isPlayerHere(charac, _x + i, _y - j) == true) {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 1;
                    }
                } else {
                    for (size_t k = 1; (_x + i + k) < map.size() && isFreeCaseCo(map, _x + i + k, _y - j) == true && isInDanger(map, _x + i + k, _y - j) == false; k++) {
                        if (isPlayerHere(charac, _x + i + k, _y - j) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 1;
                            }
                        }
                    }
                    for (int k = 1; (_x + i - k) >= 0 && isFreeCaseCo(map, _x + i - k, _y - j) == true && isInDanger(map, _x + i - k, _y - j) == false; k++) {
                        if (isPlayerHere(charac, _x + i - k, _y - j) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    for (size_t i = 1; (_y + i) < map.size() && isFreeCaseCo(map, _x, _y + i) == true && isInDanger(map, _x, _y + i) == false; i++) {
        if (isPlayerHere(charac, _x, _y + i) == true) {
            if (i < min) {
                min = i;
                result = 2;
            }
        } else {
            for (size_t j = 1; (_x + j) < map.at(_y + i).size() && isFreeCaseCo(map, _x + j, _y + i) == true && isInDanger(map, _x + j, _y + i) == false; j++) {
                if (isPlayerHere(charac, _x + j, _y + i) == true) {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 2;
                    }
                } else {
                    for (size_t k = 1; (_y + i + k) < map.size() && isFreeCaseCo(map, _x + j, _y + i + k) == true && isInDanger(map, _x + j, _y + i + k) == false; k++) {
                        if (isPlayerHere(charac, _x + j, _y + i + k) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 2;
                            }
                        }
                    }
                    for (int k = 1; (_y + i - k) >= 0 && isFreeCaseCo(map, _x + j, _y + i - k) == true && isInDanger(map, _x + j, _y + i - k) == false; k++) {
                        if (isPlayerHere(charac, _x + j, _y + i - k) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 2;
                            }
                        }
                    }
                }
            }
            for (int j = 1; (_x - j) >= 0 && isFreeCaseCo(map, _x - j, _y + i) == true && isInDanger(map, _x - j, _y + i) == false; j++) {
                if (isPlayerHere(charac, _x - j, _y + i) == true) {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 2;
                    }
                } else {
                    for (size_t k = 1; (_y + i + k) < map.size() && isFreeCaseCo(map, _x - j, _y + i + k) == true && isInDanger(map, _x - j, _y + i + k) == false; k++) {
                        if (isPlayerHere(charac, _x - j, _y + i + k) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 2;
                            }
                        }
                    }
                    for (int k = 1; (_y + i - k) >= 0 && isFreeCaseCo(map, _x - j, _y + i - k) == true && isInDanger(map, _x - j, _y + i - k) == false; k++) {
                        if (isPlayerHere(charac, _x - j, _y + i - k) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 2;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 1; (_x - i) >= 0 && isFreeCaseCo(map, _x - i, _y) == true && isInDanger(map, _x - i, _y) == false; i++) {
        if (isPlayerHere(charac, _x - i, _y) == true) {
            if (i < min) {
                min = i;
                result = 3;
            }
        } else {
            for (size_t j = 1; (_y + j) < map.size() && isFreeCaseCo(map, _x - i, _y + j) == true && isInDanger(map, _x - i, _y + j) == false; j++) {
                if (isPlayerHere(charac, _x - i, _y + j) == true) {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 3;
                    }
                } else {
                    for (size_t k = 1; (_x - i + k) < map.size() && isFreeCaseCo(map, _x - i + k, _y + j) == true && isInDanger(map, _x - i + k, _y + j) == false; k++) {
                        if (isPlayerHere(charac, _x - i + k, _y + j) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 3;
                            }
                        }
                    }
                    for (int k = 1; (_x - i - k) >= 0 && isFreeCaseCo(map, _x - i - k, _y + j) == true && isInDanger(map, _x - i - k, _y + j) == false; k++) {
                        if (isPlayerHere(charac, _x - i + k, _y + j) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 3;
                            }
                        }
                    }
                }
            }
            for (int j = 1; (_y - j) >= 0 && isFreeCaseCo(map, _x - i, _y - j) == true && isInDanger(map, _x - i, _y - j) == false; j++) {
                if (isPlayerHere(charac, _x - i, _y - j) == true) {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 3;
                    }
                } else {
                    for (size_t k = 1; (_x - i + k) < map.size() && isFreeCaseCo(map, _x - i + k, _y - j) == true && isInDanger(map, _x - i + k, _y - j) == false; k++) {
                        if (isPlayerHere(charac, _x - i + k, _y - j) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 3;
                            }
                        }
                    }
                    for (int k = 1; (_x - i - k) >= 0 && isFreeCaseCo(map, _x - i - k, _y - j) == true && isInDanger(map, _x - i - k, _y - j) == false; k++) {
                        if (isPlayerHere(charac, _x - i - k, _y - j) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 3;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 1; (_y - i) >= 0 && isFreeCaseCo(map, _x, _y - i) == true && isInDanger(map, _x, _y - i) == false; i++) {
        if (isPlayerHere(charac, _x, _y - i) == true) {
            if (i < min) {
                min = i;
                result = 4;
            }
        } else {
            for (size_t j = 1; (_x + j) < map.at(_y - i).size() && isFreeCaseCo(map, _x + j, _y - i) == true && isInDanger(map, _x + j, _y - i) == false; j++) {
                if (isPlayerHere(charac, _x + j, _y - i) == true) {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 4;
                    }
                } else {
                    for (size_t k = 1; (_y - i + k) < map.size() && isFreeCaseCo(map, _x + j, _y - i + k) == true && isInDanger(map, _x + j, _y - i + k) == false; k++) {
                        if (isPlayerHere(charac, _x + j, _y - i + k) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 4;
                            }
                        }
                    }
                    for (int k = 1; (_y - i - k) >= 0 && isFreeCaseCo(map, _x + j, _y - i - k) == true && isInDanger(map, _x + j, _y - i - k) == false; k++) {
                        if (isPlayerHere(charac, _x + j, _y - i - k) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 4;
                            }
                        }
                    }
                }
            }
            for (int j = 1; (_x - j) >= 0 && isFreeCaseCo(map, _x - j, _y - i) == true  && isInDanger(map, _x - j, _y - i) == false; j++) {
                if (isPlayerHere(charac, _x - j, _y - i) == true) {
                    if ((i + j) < min) {
                        min = i + j;
                        result = 4;
                    }
                } else {
                    for (size_t k = 1; (_y - i + k) < map.size() && isFreeCaseCo(map, _x - j, _y - i + k) == true && isInDanger(map, _x - j, _y - i + k) == false; k++) {
                        if (isPlayerHere(charac, _x - j, _y - i + k) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 4;
                            }
                        }
                    }
                    for (int k = 1; (_y - i - k) >= 0 && isFreeCaseCo(map, _x - j, _y - i - k) == true && isInDanger(map, _x - j, _y - i - k) == false; k++) {
                        if (isPlayerHere(charac, _x - j, _y - i - k) == true) {
                            if ((i + j + k) < min) {
                                min = i + j + k;
                                result = 4;
                            }
                        }
                    }
                }
            }
        }
    }
    return (result);
}

int Bot::firstMove(std::vector<std::string> map)
{
    if (this->isFreeCase(map, 1, 0) == true)
        return (1);
    else if (this->isFreeCase(map, 0, 1) == true)
        return (2);
    else if (this->isFreeCase(map, -1, 0) == true)
        return (3);
    return (4);
}

int Bot::randomMove(std::vector<std::string> map)
{
    int result = 0;

    if (isInDanger(map, _x + 1, _y) == true && isInDanger(map, _x, _y + 1) == true && isInDanger(map, _x - 1, _y) == true && isInDanger(map, _x, _y - 1) == true)
        return (5);
    while (result == 0) {
        result = rand() % 4 + 1;
        if (result == 1) {
            if (isInDanger(map, _x + 1, _y) == false)
                break;
        } else if (result == 2) {
            if (isInDanger(map, _x, _y + 1) == false)
                break;
        } else if (result == 3) {
            if (isInDanger(map, _x - 1, _y) == false)
                break;
        } else {
            if (isInDanger(map, _x, _y - 1) == false)
                break;
        }
        result = 0;
    }
    return (result);
}

void Bot::move(irr::u32 timer, std::vector<std::string> &map, EventReceiver receiver, std::vector<Item *> item, std::vector<ICharacter *> charac)
{
    int tmp_x = this->_x;
    int tmp_y = this->_y;
    int result = 0;

    result = this->iaEscapeBomb(map);
    if (result == 5) {
        result = this->iaSearchItem(map);
        if (result == 5) {
            result = this->iaChasePlayer(map, charac);
            if (result == 5) {
                result = randomMove(map);
                std::cout << "result " << result << std::endl;
            }
        }
    }
    if (this->_timerMove == 0)
        result = this->firstMove(map);
    if (result == 1)
        tmp_x = tmp_x + 1;
    else if (result == 2)
        tmp_y = tmp_y + 1;
    else if (result == 3)
        tmp_x = tmp_x - 1;
    else if (result == 4)
        tmp_y = tmp_y - 1;
    if (map.at(tmp_y).at(tmp_x) == '#' || map.at(tmp_y).at(tmp_x) == 'B' || map.at(tmp_y).at(tmp_x) == '@')
        return;
    if (map.at(tmp_y).at(tmp_x) == 'W' && _wall == false)
        return;
    if (map.at(tmp_y).at(tmp_x) == 'I') {
        this->upgrade(item);
        map.at(tmp_y).at(tmp_x) = ' ';
    }
    this->_x = tmp_x;
    this->_y = tmp_y;
    this->_timerMove = timer;
}

bool Bot::iaPutBomb(std::vector<std::string> map, std::vector<ICharacter *> charac)
{
    bool isEnnemy = false;

    for (size_t i = 1; i <= _power && (_x + i) < map.at(_y).size(); i++) {
        for (size_t j = 0; j < charac.size(); j++) {
            if ((_x + i) == charac.at(j)->getX() && _y == charac.at(j)->getY())
                isEnnemy = true;
        }
    }
    for (size_t i = 1; i <= _power && (_y + i) < map.size(); i++) {
        for (size_t j = 0; j < charac.size(); j++) {
            if (_x == charac.at(j)->getX() && (_y + i) == charac.at(j)->getY())
                isEnnemy = true;
        }
    }
    for (int i = 1; i <= _power && (_x - i) >= 0; i++) {
        for (size_t j = 0; j < charac.size(); j++) {
            if ((_x - i) == charac.at(j)->getX() && _y == charac.at(j)->getY())
                isEnnemy = true;
        }
    }
    for (int i = 1; i <= _power && (_y - i) >= 0; i++) {
        for (size_t j = 0; j < charac.size(); j++) {
            if (_x == charac.at(j)->getX() && (_y - i) == charac.at(j)->getY())
                isEnnemy = true;
        }
    }
    if (isInDanger(map, _x, _y) == false && ((isInDanger(map, _x + 1, _y) == false && isFreeCaseCo(map, _x + 1, _y) == true) || (isInDanger(map, _x, _y + 1) == false && isFreeCaseCo(map, _x, _y + 1) == true) || (isInDanger(map, _x - 1, _y) == false && isFreeCaseCo(map, _x - 1, _y) == true) || (isInDanger(map, _x, _y - 1) == false && isFreeCaseCo(map, _x, _y - 1) == true)))
        if (map.at(_y).at(_x + 1) == 'W' || map.at(_y + 1).at(_x) == 'W' || map.at(_y).at(_x - 1) == 'W' || map.at(_y - 1).at(_x) == 'W') {
            return (true);
        } else {
            return (isEnnemy);
        }
    return (false);
}

Bomb *Bot::putBomb(irr::u32 timer, std::vector<std::string> &map, EventReceiver receiver, std::vector<ICharacter *> charac)
{
    if (map.at(this->_y).at(this->_x) == 'B' || this->_nbBomb < 1)
        return NULL;
    if (iaPutBomb(map, charac) == true) {
        std::cout << "bomb" << std::endl;
        map.at(this->_y).at(this->_x) = 'B';
        this->_nbBomb = this->_nbBomb - 1;
        return (new Bomb(this->_power, this->_x, this->_y, timer, _id));
    }
    return NULL;
}