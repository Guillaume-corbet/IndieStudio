/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Menu
*/

#include "../include/Menu.hpp"

Menu::Menu(Graphique *graph)
{
    _graph = graph;
}

Menu::~Menu()
{
}

int Menu::abstractMenu(std::vector<std::string> buttons, irr::io::path texture)
{
    int select = 0;
    int last_move = 0;
    int buttonSizeX = 400;
    int buttonSizeY = 80;
    irr::s32 id;
    irr::SEvent event;
    irr::io::path font_path;

    font_path.append(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/bigfont.png"));
    std::wstring tmp;
    irr::gui::IGUISkin* skin = _graph->getDevice()->getGUIEnvironment()->getSkin();
    irr::gui::IGUIFont* font = _graph->getDevice()->getGUIEnvironment()->getFont(font_path);
    _graph->getDevice()->getGUIEnvironment()->addImage( _graph->getDriver()->getTexture(texture), irr::core::position2d<int>(0,0));
    texture = "";
    texture.append(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/arrow.png"));
    irr::gui::IGUIImage* arrow = _graph->getDevice()->getGUIEnvironment()->addImage( _graph->getDriver()->getTexture(texture), irr::core::position2d<int>((_graph->getWindowSize().Width - buttonSizeX) / 2 - 70, (_graph->getWindowSize().Height - buttonSizeY) / 2 + select * 100 - 10));

    if (font)
        skin->setFont(font);
    skin->setFont(_graph->getDevice()->getGUIEnvironment()->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);

    //create buttons
    for (unsigned i = 0; i < buttons.size(); i += 1) {
        tmp = std::wstring(buttons.at(i).begin(), buttons.at(i).end());
        _graph->getDevice()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>((_graph->getWindowSize().Width - buttonSizeX) / 2, (_graph->getWindowSize().Height - buttonSizeY) / 2 + i * 100,
        (_graph->getWindowSize().Width - buttonSizeX) / 2 + buttonSizeX, (_graph->getWindowSize().Height - buttonSizeY) / 2 + buttonSizeY + i * 100),
        0, (irr::s32)i, tmp.c_str());
    }

    while (_graph->getDevice()->run() && _graph->getReceiver().IsKeyDown(irr::KEY_RETURN) && _graph->getReceiver().getEvent().MouseInput.isLeftPressed());
    while (_graph->getDevice()->run() && !_graph->getReceiver().IsKeyDown(irr::KEY_RETURN)) {
        //event on clic
        if (_graph->getReceiver().getEvent().EventType == irr::EET_GUI_EVENT) {
            if (_graph->getReceiver().getEvent().GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                _graph->getReceiver().resetEvent();
                id = _graph->getReceiver().getEvent().GUIEvent.Caller->getID();
                while (_graph->getReceiver().getEvent().MouseInput.isLeftPressed() && _graph->getDevice()->run());
                _graph->getDevice()->getGUIEnvironment()->clear();
                return ((int)id);
            }
        }
        //select with arrows
        if ((!_graph->getReceiver().IsKeyDown(irr::KEY_DOWN) && !_graph->getReceiver().IsKeyDown(irr::KEY_UP)))
            last_move = 0;
        else if (last_move == 0) {
            if (_graph->getReceiver().IsKeyDown(irr::KEY_DOWN))
                last_move = 1;
            else if (_graph->getReceiver().IsKeyDown(irr::KEY_UP))
                last_move = -1;

            select += last_move;
            if (select < 0)
                select = buttons.size() - 1;
            else if (select >= buttons.size())
                select = 0;
            arrow->setRelativePosition(irr::core::position2d<int>((_graph->getWindowSize().Width - buttonSizeX) / 2 - 70, (_graph->getWindowSize().Height - buttonSizeY) / 2 + select * 100 - 10));
        }
        //display
        if (_graph->getDevice()->isWindowActive() && _graph->getDriver()) {
            _graph->getDriver()->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
            _graph->getDevice()->getGUIEnvironment()->drawAll();
            _graph->getDriver()->endScene();
        }
    }

    _graph->getDevice()->getGUIEnvironment()->clear();

    if (!_graph->getDevice()->run())
        return(-1);

    return (select);
}

int Menu::mainMenu()
{
    int select = 0;
    std::vector<std::string> buttons;
    irr::io::path path = static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/Bomberman.jpg");

    buttons.push_back("Play");
    buttons.push_back("Load");
    buttons.push_back("Quit");

    select = abstractMenu(buttons, path);
    if (select == -1 || buttons.at(select) == "Quit")
        return (-1);

    return (select);
}

int Menu::playerNum()
{
    int select = 0;
    std::vector<std::string> buttons;
    irr::io::path path = static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/Bomberman.jpg");

    buttons.push_back("1");
    buttons.push_back("2");
    buttons.push_back("Quit");
    select = abstractMenu(buttons, path);
    if (select == -1 || buttons.at(select) == "Quit")
        return (-1);
    return (select);
}

int Menu::PauseMenu()
{
    int select = 0;
    std::vector<std::string> buttons;
    irr::io::path path = static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/Bomberman_pause.jpg");


    buttons.push_back("Resume");
    buttons.push_back("Save and quit");
    buttons.push_back("Quit");
    select = abstractMenu(buttons, path);

    if (select == -1 || buttons.at(select) == "Quit")
        return (-1);

    return (select);
}

int Menu::WinMenu()
{
    int select = 0;
    std::vector<std::string> buttons;
    irr::io::path path = static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/menu_win.jpg");

    buttons.push_back("Replay");
    buttons.push_back("Quit");
    select = abstractMenu(buttons, path);

    if (select == -1 || buttons.at(select) == "Quit")
        return (-1);

    return (select);
}

int Menu::LooseMenu()
{
    int select = 0;
    std::vector<std::string> buttons;
    irr::io::path path = static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/menu_loose.jpg");

    buttons.push_back("Replay");
    buttons.push_back("Quit");
    select = abstractMenu(buttons, path);

    if (select == -1 || buttons.at(select) == "Quit")
        return (-1);

    return (select);
}