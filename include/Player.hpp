/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "ICharacter.hpp"
#include "Graphique.hpp"

class Player : public ICharacter {
    public:
        Player(int x, int y, int nb);
        ~Player();
        void setX(int x);
        void setY(int y);
        void setTimerMove(irr::u32 timer);
        void setPower(int power);
        void setSpeed(irr::u32 speed);
        void setId(int id);
        void setNbBomb(int nbBomb);
        void setWall(bool wall);
        void setCommand(std::vector<irr::EKEY_CODE> command);
        void upgrade(std::vector<Item *> item);
        void move(irr::u32 timer, std::vector<std::string> &map, EventReceiver receiver, std::vector<Item *> item, std::vector<ICharacter *> charac);
        int getX() const;
        int getY() const;
        int getPower() const;
        int getId() const;
        int getNbBomb() const;
        bool getWall() const;
        irr::u32 getTimerMove() const;
        irr::u32 getSpeed() const;
        std::vector<irr::EKEY_CODE> getCommand() const;
        Bomb *putBomb(irr::u32 timer, std::vector<std::string> &map, EventReceiver receiver, std::vector<ICharacter *> charac);
        std::string to_string();
    protected:
    private:
        int _x;
        int _y;
        irr::u32 _timerMove;
        int _power;
        irr::u32 _speed;
        int _nbBomb;
        bool _wall;
        std::vector<irr::EKEY_CODE> _command;
        int _id;
};

#endif /* !PLAYER_HPP_ */
