/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#include "../include/Player.hpp"

Player::Player(int x, int y, int id)
{
    this->_x = x;
    this->_y = y;
    this->_timerMove = 0;
    this->_power = 3;
    this->_speed = 500;
    this->_nbBomb = 1;
    this->_wall = false;
    if (id == 1) {
        this->_command.push_back(irr::KEY_KEY_Z);
        this->_command.push_back(irr::KEY_KEY_S);
        this->_command.push_back(irr::KEY_KEY_D);
        this->_command.push_back(irr::KEY_KEY_Q);
        this->_command.push_back(irr::KEY_KEY_E);
    } else {
        this->_command.push_back(irr::KEY_KEY_O);
        this->_command.push_back(irr::KEY_KEY_L);
        this->_command.push_back(irr::KEY_KEY_M);
        this->_command.push_back(irr::KEY_KEY_K);
        this->_command.push_back(irr::KEY_KEY_P);
    }
    this->_id = id;
}

Player::~Player()
{
}

std::string Player::to_string()
{
    std::string result;

    result = std::to_string(_x) + ";" + std::to_string(_y) + ";" + std::to_string(_timerMove) + ";" + std::to_string(_power) + ";" + std::to_string(_speed) + ";" + std::to_string(_nbBomb) + ";" + std::to_string(_wall) + ";" + std::to_string(_id) + ";" + "1" + "#";
    
    return (result);
}

void Player::setX(int x)
{
    this->_x = x;
}

int Player::getX() const
{
    return (this->_x);
}

void Player::setY(int y)
{
    this->_y = y;
}

int Player::getY() const
{
    return (this->_y);
}

void Player::setTimerMove(irr::u32 timer)
{
    this->_timerMove = timer;
}

irr::u32 Player::getTimerMove() const
{
    return (this->_timerMove);
}

void Player::setPower(int power)
{
    this->_power = power;
}

int Player::getPower() const
{
    return (this->_power);
}

void Player::setSpeed(irr::u32 speed)
{
    this->_speed = speed;
}

irr::u32 Player::getSpeed() const
{
    return (this->_speed);
}

void Player::setId(int id)
{
    this->_id = id;
}

int Player::getId() const
{
    return (this->_id);
}

void Player::setNbBomb(int nbBomb)
{
    this->_nbBomb = nbBomb;
}

int Player::getNbBomb() const
{
    return (this->_nbBomb);
}

void Player::setCommand(std::vector<irr::EKEY_CODE> command)
{
    this->_command = command;
}

std::vector<irr::EKEY_CODE> Player::getCommand() const
{
    return (this->_command);
}

void Player::setWall(bool wall)
{
    this->_wall = wall;
}

bool Player::getWall() const
{
    return (this->_wall);
}

void Player::upgrade(std::vector<Item *> item)
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
            std::cout << "item =" << item.at(i)->getPower() << std::endl;
            item.at(i)->~Item();
            item.erase(item.begin() + i);
        }
    }
}

void Player::move(irr::u32 timer, std::vector<std::string> &map, EventReceiver receiver, std::vector<Item *> item, std::vector<ICharacter *> charac)
{
    int tmp_x = this->_x;
    int tmp_y = this->_y;

    if (receiver.IsKeyDown(this->_command.at(0)))
        tmp_y = tmp_y - 1;
    else if (receiver.IsKeyDown(this->_command.at(1)))
        tmp_y = tmp_y + 1;
    else if (receiver.IsKeyDown(this->_command.at(2)))
        tmp_x = tmp_x + 1;
    else if (receiver.IsKeyDown(this->_command.at(3)))
        tmp_x = tmp_x - 1;
    else
        return;
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
    std::cout << "move to = " << this->_x << ", " << this->_y << std::endl;
}

Bomb *Player::putBomb(irr::u32 timer, std::vector<std::string> &map, EventReceiver receiver, std::vector<ICharacter *> charac)
{
    if (receiver.IsKeyDown(this->_command.at(4)) && this->_nbBomb > 0) {
        if (map.at(this->_y).at(this->_x) == 'B')
            return NULL;
        std::cout << "bomb" << std::endl;
        map.at(this->_y).at(this->_x) = 'B';
        this->_nbBomb = this->_nbBomb - 1;
        return (new Bomb(this->_power, this->_x, this->_y, timer, _id));
    }
    return (NULL);
}