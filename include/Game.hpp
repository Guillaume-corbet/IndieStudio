/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "Load.hpp"
#include "Save.hpp"
#include "ICharacter.hpp"
#include "Player.hpp"
#include "Bot.hpp"
#include "Graphique.hpp"
#include "EventReceiver.hpp"
#include "Item.hpp"
#include "Bomb.hpp"
#include "Display.hpp"
#include "Menu.hpp"
#include <ctime>

class Save;

class Game {
    public:
        Game();
        ~Game();
        std::vector<std::string> randMap(std::vector<std::string> map);
        int startGame(int nbPlayer);
        int loadGame(Graphique *graph);
        void loadMap();
        void saveGame(Graphique *graphique);
        std::vector<std::string> getMap() const;
        void setMap(std::vector<std::string> map);
        void displayMap() const;
        void gameLoop(Graphique *graphique);
        int getNbPlayer();
        std::vector<std::string> Player_to_vector();
        std::vector<std::string> Item_to_vector();
        std::vector<std::string> Bomb_to_vector(Graphique *graph);

    protected:
    private:
        std::vector<std::string> _map;
        std::vector<ICharacter *> _charac;
        std::vector<Bomb *> _bomb;
        std::vector<Item *> _item;
        int _nbPlayer;
};

#endif /* !GAME_HPP_ */