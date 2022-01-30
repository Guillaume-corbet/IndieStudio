/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Save
*/

#ifndef SAVE_HPP_
#define SAVE_HPP_

#ifdef __linux__
  #define PATH ""
#elif defined _WIN32 || defined _WIN64
  #define PATH "../../../"
#else
#error "unknown platform"
#endif 

#include "../include/boost/property_tree/ptree.hpp"
#include "../include/boost/property_tree/json_parser.hpp"

#include "Player.hpp"
#include "Item.hpp"
#include "Bomb.hpp"

#include <vector>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

class Save {
    public:
        Save();
        ~Save();
        void SaveBomb(std::vector<std::string> bomb);
        void SaveItem(std::vector<std::string> item);
        void SavePlayer(std::vector<std::string> player);
        void SaveMap(std::vector<std::string> map);
    protected:
    private:
        std::string _filepath;
};

#endif