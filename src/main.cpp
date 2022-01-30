/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include "../include/Game.hpp"
#include "../include/Menu.hpp"

Game *getMenu(Graphique *graphique)
{
    int result = 0;
    int player = 0;
    Game *game = new Game();
    Menu *menu = new Menu(graphique);

    result = menu->mainMenu();
    std::cout << result << std::endl;
    if (result == 0) {
        player = menu->playerNum();
        game->startGame(player + 1);
    }
    else if (result == 1) {
        game->loadGame(graphique);
    }
    else {
        game = NULL;
    }
    delete(menu);
    return (game);
}

int main(void)
{
    Game *game = NULL;
    Graphique *graphique = new Graphique();

    while (1) {
        game = getMenu(graphique);
        if (game == NULL) {
            break;
        }
        if (game->getNbPlayer()) {
            game->gameLoop(graphique);
            delete(game);
        }
    }
    std::cout << "exit game loop" << std::endl;
    delete(graphique);
    return (0);
}