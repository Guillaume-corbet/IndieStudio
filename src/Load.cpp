/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Load
*/

#include "../include/Load.hpp"

namespace pt = boost::property_tree;

Load::Load()
{
}

Load::~Load()
{
}

std::string get_param(std::string buffer, int nb, char end)
{
    std::string param;
    int i = 0;
    int j = 0;


    while (nb > 1) {
        while (buffer.at(i) != ';' && i < buffer.size())
            i = i + 1;
        i = i + 1;
        nb = nb - 1;
    }
    while (buffer.at(i) != end && i < buffer.size()) {
        param.append(&buffer.at(i));
        i = i + 1;
        j = j + 1;
    }
    return (param);
}

std::vector<ICharacter *> Load::LoadPlayer()
{
    int i = 0;
    pt::ptree root;
    std::string path = PATH + static_cast<std::string>("save/player.json");
    std::vector<ICharacter *> result;

    pt::read_json(path, root);;
    for (pt::ptree::value_type &data : root.get_child("players")) {
        result.push_back({});
        if (std::stoi(get_param(data.second.data(), 9, '#')) == 1)
            result.at(i) = new Player (0, 0, std::stoi(get_param(data.second.data(), 8, ';')));
        else if (std::stoi(get_param(data.second.data(), 9, '#')) == 0)
            result.at(i) = new Bot (0, 0, std::stoi(get_param(data.second.data(), 8, ';')));
        result.at(i)->setX(std::stoi(get_param(data.second.data(), 1, ';')));
        result.at(i)->setY(std::stoi(get_param(data.second.data(), 2, ';')));
        result.at(i)->setTimerMove(std::stoi(get_param(data.second.data(), 3, ';')));
        result.at(i)->setPower(std::stoi(get_param(data.second.data(), 4, ';')));
        result.at(i)->setSpeed(std::stoi(get_param(data.second.data(), 5, ';')));
        result.at(i)->setNbBomb(std::stoi(get_param(data.second.data(), 6, ';')));
        result.at(i)->setWall((bool)std::stoi(get_param(data.second.data(), 7, ';')));
        result.at(i)->setId(std::stoi(get_param(data.second.data(), 8, ';')));
        i += 1;
    }

    return (result);
}

std::vector<Item *> Load::LoadItem()
{
    int i = 0;
    pt::ptree root;
    std::string path = PATH + static_cast<std::string>("save/item.json");
    std::vector<Item *> result;

    pt::read_json(path, root);;
    for (pt::ptree::value_type &data : root.get_child("items")) {
        result.push_back(new Item(std::stoi(get_param(data.second.data(), 2, ';')), std::stoi(get_param(data.second.data(), 3, '#'))));
        result.at(i)->setPowerUp(std::stoi(get_param(data.second.data(), 1, ';')));
        i += 1;
    }

    return (result);
}

std::vector<Bomb *> Load::LoadBomb(Graphique *graph)
{
    int i = 0;
    pt::ptree root;
    std::string path = PATH + static_cast<std::string>("save/bomb.json");
    std::vector<Bomb *> result;

    pt::read_json(path, root);;
    for (pt::ptree::value_type &data : root.get_child("bombs")) {
        result.push_back(new Bomb(std::stoi(get_param(data.second.data(), 1, ';')), std::stoi(get_param(data.second.data(), 4, ';')), std::stoi(get_param(data.second.data(), 5, ';')), graph->getDevice()->getTimer()->getTime(), std::stoi(get_param(data.second.data(), 6, '#'))));
        result.at(i)->setDelay(std::stoi(get_param(data.second.data(), 3, ';')));
        i += 1;
    }

    return (result);
}

std::vector<std::string> Load::LoadMap()
{
    std::string line;
    std::string path = PATH + static_cast<std::string>("save/map");
    std::ifstream file;
    std::vector<std::string> map;

    file.open(path);
    if (!file.is_open()) {
        std::cerr << "bomberman: " << path << ": No such file or directory" << std::endl;
        return (map);
    }
    while (std::getline (file,line)) {
        map.push_back(line);
    }
    file.close();
    return (map);
}

std::vector<std::string> Load::LoadMapJson()
{
    pt::ptree root;
    std::vector<std::string> map;
    std::string path = PATH + static_cast<std::string>("save/map.json");

    pt::read_json(path, root);
    for (pt::ptree::value_type &data : root.get_child("maps")) {
        map.push_back(data.second.data());
    }

    return (map);
}