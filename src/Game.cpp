/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#include "../include/Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

std::vector<std::string> Game::Player_to_vector()
{
    std::vector<std::string> result;

    for (size_t i = 0; i < _charac.size(); i += 1)
        result.push_back(_charac.at(i)->to_string());

    return (result);
}
std::vector<std::string> Game::Item_to_vector()
{
    std::vector<std::string> result;

    for (size_t i = 0; i < _item.size(); i += 1)
        result.push_back(_item.at(i)->to_string());

    return (result);
}
std::vector<std::string> Game::Bomb_to_vector(Graphique *graph)
{

    std::vector<std::string> result;

    for (size_t i = 0; i < _bomb.size(); i += 1)
        result.push_back(_bomb.at(i)->to_string(graph));

    return (result);
}

std::vector<std::string> Game::randMap(std::vector<std::string> map)
{
    int result = 0;

    srand(time(NULL));
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t y = 0; y < map.at(i).size(); y++) {
            result = rand() % 100 + 1;
            if (map.at(i).at(y) == 'W' && result < 10) {
                map.at(i).at(y) = ' ';
            }
        }
    }
    return (map);
}

int Game::startGame(int nbPlayer)
{
    Load *loader = new Load;

    this->setMap(this->randMap(loader->LoadMap()));

    this->_nbPlayer = nbPlayer;
    this->_charac.push_back(new Player(1, 1, 1));
    if (nbPlayer == 2)
        this->_charac.push_back(new Player(11, 1, 2));
    else
        this->_charac.push_back(new Bot(11, 1, 2));
    this->_charac.push_back(new Bot(1, 9, 3));
    this->_charac.push_back(new Bot(11, 9, 4));
    std::cout << nbPlayer << std::endl;
    return (0);
}

int Game::loadGame(Graphique *graph)
{
    Load *loader = new Load;
    _charac = loader->LoadPlayer();
    _item = loader->LoadItem();
    this->setMap(loader->LoadMapJson());
    _bomb = loader->LoadBomb(graph);
    return (0);
}

std::vector<std::string> Game::getMap() const
{
    return (_map);
}

int Game::getNbPlayer()
{
    return (_nbPlayer);
}

void Game::setMap(std::vector<std::string> map)
{
    this->_map = map;
}

void Game::displayMap() const
{
    for (size_t i = 0; i < this->_map.size(); i++)
        std::cout << this->_map.at(i) << std::endl;
}

void Game::saveGame(Graphique *graphique)
{
    std::string result;
    Save save;

    if (_bomb.size() > 0)
        save.SaveBomb(Bomb_to_vector(graphique));
    if (_item.size() > 0)
        save.SaveItem(Item_to_vector());
    if (_charac.size() > 0)
        save.SavePlayer(Player_to_vector());
    save.SaveMap(_map);
}

void Game::gameLoop(Graphique *graphique)
{
    EventReceiver receiver;
    Bomb *bomb;
    Menu menu(graphique);
    Display *display = new(Display)(graphique);
    irr::u32 time_at_pause;
    int result;

    while (graphique->getDevice()->run()) {
        receiver = graphique->getReceiver();
        if (receiver.IsKeyDown(irr::KEY_ESCAPE)) {
            time_at_pause = graphique->getDevice()->getTimer()->getTime();
            result = menu.PauseMenu();
            if (result == -1)
                return;
            else if (result == 1) {
                for (size_t i = 0; i < _bomb.size(); i += 1)
                    _bomb.at(i)->setDelay(time_at_pause - _bomb.at(i)->getTimer());
                this->saveGame(graphique);
                break;
            }
            else {
                for (size_t i = 0; i < _bomb.size(); i += 1) {
                    _bomb.at(i)->setDelay(time_at_pause - _bomb.at(i)->getTimer());
                    _bomb.at(i)->setTimer(graphique->getDevice()->getTimer()->getTime());
                }
            }
        }
        for (size_t i = 0; i < this->_charac.size(); i++) {
            if (graphique->getDevice()->getTimer()->getTime() > this->_charac.at(i)->getTimerMove() + this->_charac.at(i)->getSpeed()) {
                this->_charac.at(i)->move(graphique->getDevice()->getTimer()->getTime(), _map, receiver, _item, _charac);
            }
            bomb = this->_charac.at(i)->putBomb(graphique->getDevice()->getTimer()->getTime(), _map, receiver, _charac);
            if (bomb != NULL) {
                this->_bomb.push_back(bomb);
            }
        }
        for (size_t i = 0; i < this->_bomb.size(); i++) {
            if (this->_bomb.at(i)->explode(graphique->getDevice()->getTimer()->getTime(), _map, _charac, _item, display) == true) {
                this->_bomb.at(i)->~Bomb();
                this->_bomb.erase(this->_bomb.begin() + i);
                i--;
            }
        }
        display->show(_map, _charac);
        if (this->_charac.size() <= 1)
            break;
    }
    if (_charac.at(0)->to_string().at(_charac.at(0)->to_string().size() - 2) == '1') {
        menu.WinMenu();
    }
    else
        menu.LooseMenu();
}