/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Load
*/

#ifndef LOAD_HPP_
#define LOAD_HPP_

#ifdef __linux__
  #define PATH ""
#elif defined _WIN32 || defined _WIN64
  #define PATH "../../../"
#else
#error "unknown platform"
#endif

#include "../include/boost/property_tree/ptree.hpp"
#include "../include/boost/property_tree/json_parser.hpp"

#include "ICharacter.hpp"
#include "Player.hpp"
#include "Bot.hpp"
#include "Item.hpp"
#include "Bomb.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Load {
    public:
        Load();
        ~Load();
        std::vector<std::string> LoadMap();
        std::vector<ICharacter *> LoadPlayer();
        std::vector<Item *> LoadItem();
        std::vector<Bomb *> LoadBomb(Graphique *graph);
        std::vector<std::string> LoadMapJson();
    protected:
    private:
      std::string _filepath;
};

#endif /* !LOAD_HPP_ */
