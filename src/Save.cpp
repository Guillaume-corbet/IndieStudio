/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Save
*/

#include "../include/Save.hpp"

namespace pt = boost::property_tree;

Save::Save()
{
}

Save::~Save()
{
}

void Save::SaveBomb(std::vector<std::string> bomb)
{
    pt::ptree root;
    pt::ptree bomb_node;
    std::string path = PATH + static_cast<std::string>("save/bomb.json");

    for (size_t i = 0; i < bomb.size(); i += 1) {
        bomb_node.put("bomb" + std::to_string(i), bomb.at(i));
    }
    root.add_child("bombs", bomb_node);
    pt::write_json(path, root);
}

void Save::SaveItem(std::vector<std::string> item)
{
    pt::ptree root;
    pt::ptree item_node;
    std::string path = PATH + static_cast<std::string>("save/item.json");

    for (size_t i = 0; i < item.size(); i += 1) {
        item_node.put("item" + std::to_string(i), item.at(i));
    }
    root.add_child("items", item_node);
    pt::write_json(path, root);
}

void Save::SavePlayer(std::vector<std::string> player)
{
    pt::ptree root;
    pt::ptree player_node;
    std::string path = PATH + static_cast<std::string>("save/player.json");

    for (size_t i = 0; i < player.size(); i += 1) {
        player_node.put("player" + std::to_string(i), player.at(i));
    }
    root.add_child("players", player_node);
    pt::write_json(path, root);
}

void Save::SaveMap(std::vector<std::string> map)
{
    pt::ptree root;
    pt::ptree map_node;
    std::string path = PATH + static_cast<std::string>("save/map.json");

    std::cout << std::endl << map.size() << std::endl;
    for (size_t i = 0; i < map.size(); i += 1) {
        map_node.put("map" + std::to_string(i), map.at(i));
    }
    root.add_child("maps", map_node);
    pt::write_json(path, root);
}