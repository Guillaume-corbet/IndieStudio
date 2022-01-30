/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Le menu Stylééééééééééééé
*/

#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>
#include "../include/EventReceiver.hpp"
#include "../include/Graphique.hpp"

#ifdef __linux__
  #define PATH ""
#elif defined _WIN32 || defined _WIN64
  #define PATH "../../../"
#else
#error "unknown platform"
#endif

class Menu
{
    public:
        Menu(Graphique *graph);
        ~Menu();
        int mainMenu();
        int playerNum();
        int PauseMenu();
        int WinMenu();
        int LooseMenu();

    private:
        int abstractMenu(std::vector<std::string> buttons, irr::io::path texture);
        Graphique *_graph;
        

};

#endif