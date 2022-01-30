/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bot
*/

#ifndef BOT_HPP_
#define BOT_HPP_

#include "ICharacter.hpp"

class Bot : public ICharacter {
    public:
        Bot(int x, int y, int id);
        ~Bot();
        void setX(int x);
        int getX() const;
        void setY(int y);
        int getY() const;
        void setTimerMove(irr::u32 timer);
        irr::u32 getTimerMove() const;
        void setPower(int power);
        int getPower() const;
        void setSpeed(irr::u32 speed);
        irr::u32 getSpeed() const;
        void setId(int id);
        int getId() const;
        void setNbBomb(int nbBomb);
        int getNbBomb() const;
        void setCommand(std::vector<irr::EKEY_CODE> command);
        std::vector<irr::EKEY_CODE> getCommand() const;
        void setWall(bool wall);
        bool getWall() const;
        int randomMove(std::vector<std::string> map);
        void move(irr::u32 timer, std::vector<std::string> &map, EventReceiver receiver, std::vector<Item *> item, std::vector<ICharacter *> charac);
        Bomb *putBomb(irr::u32 timer, std::vector<std::string> &map, EventReceiver receiver, std::vector<ICharacter *> charac);
        void upgrade(std::vector<Item *> item);
        bool isFreeCase(std::vector<std::string> map, int x, int y);
        bool isFreeCaseCo(std::vector<std::string> map, int x, int y);
        int firstMove(std::vector<std::string> map);
        bool isInDanger(std::vector<std::string> map, int x, int y);
        int iaEscapeBomb(std::vector<std::string> map);
        int iaSearchItem(std::vector<std::string> map);
        bool isPlayerHere(std::vector<ICharacter *> charac, int x, int y);
        int iaChasePlayer(std::vector<std::string> map, std::vector<ICharacter *> charac);
        bool iaPutBomb(std::vector<std::string> map, std::vector<ICharacter *> charac);
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

#endif /* !BOT_HPP_ */
