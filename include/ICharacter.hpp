/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ICharacter
*/

#ifndef ICHARACTER_HPP_
#define ICHARACTER_HPP_

#include <iostream>
#include <vector>
#include <irrlicht/irrlicht.h>
#include "Bomb.hpp"
#include "Item.hpp"

class Bomb;

class ICharacter {
    public:
        virtual ~ICharacter(){};
        virtual void move(irr::u32 timer,std::vector<std::string> &map, EventReceiver receiver,std::vector<Item *> item, std::vector<ICharacter *> charac) = 0;
        virtual Bomb *putBomb(irr::u32 timer, std::vector<std::string> &map, EventReceiver receiver, std::vector<ICharacter *> charac) = 0;
        virtual void upgrade(std::vector<Item *> item) = 0;
        virtual void setTimerMove(irr::u32 timer) = 0;
        virtual irr::u32 getTimerMove() const = 0;
        virtual void setPower(int power) = 0;
        virtual int getPower() const = 0;
        virtual void setSpeed(irr::u32 speed) = 0;
        virtual irr::u32 getSpeed() const = 0;
        virtual void setX(int x) = 0;
        virtual int getX() const = 0;
        virtual void setY(int y) = 0;
        virtual int getY() const = 0;
        virtual int getId() const = 0;
        virtual void setId(int id) = 0;
        virtual void setNbBomb(int nbBomb) = 0;
        virtual int getNbBomb() const = 0;
        virtual void setCommand(std::vector<irr::EKEY_CODE> command) = 0;
        virtual std::vector<irr::EKEY_CODE> getCommand() const = 0;
        virtual void setWall(bool wall) = 0;
        virtual bool getWall() const = 0;
        virtual std::string to_string() = 0;
    protected:
    private:
};

#endif /* !ICHARACTER_HPP_ */
