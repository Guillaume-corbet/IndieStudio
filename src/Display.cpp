/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Display
*/

#include "../include/Display.hpp"

Display::Display(Graphique *graph)
{
    _graph = graph;

    rec = _graph->getReceiver();
    sceneManager = _graph->getDevice()->getSceneManager()->createNewSceneManager(false);
    //irr::scene::ISceneManager nouveauSM = sceneManager->createNewSceneManager(false);
    driver = _graph->getDevice()->getVideoDriver();
    env = _graph->getDevice()->getGUIEnvironment();

    explode_time = 250;

    sceneManager->addLightSceneNode(0, irr::core::vector3df(-50, -50, 100), irr::video::SColorf(1.0f, 1.0f, 1.0f), 200);
    sceneManager->addLightSceneNode(0, irr::core::vector3df(25, 25, 100), irr::video::SColorf(1.0f, 1.0f, 1.0f), 200);
    sceneManager->addLightSceneNode(0, irr::core::vector3df(25, -50, 100), irr::video::SColorf(1.0f, 1.0f, 1.0f), 200);
    sceneManager->addLightSceneNode(0, irr::core::vector3df(-50, 25, 100), irr::video::SColorf(1.0f, 1.0f, 1.0f), 200);

    mesh_player = sceneManager->getMesh(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/player.obj"));
    mesh_border = sceneManager->getMesh(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/Crate1.obj"));
    mesh_W = sceneManager->getMesh(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/Crate1.obj"));
    mesh_hardwall = sceneManager->getMesh(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/Crate1.obj"));
    mesh_B = sceneManager->getMesh (static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/Crate1.obj"));
    mesh_I = sceneManager->getMesh(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/Crate1.obj"));
    mesh_E = sceneManager->getMesh(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/Crate1.obj"));
    texture_player = driver->getTexture(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/player.png"));
    texture_border = driver->getTexture(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/border.png"));
    texture_W = _graph->getDriver()->getTexture(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/wall.png"));
    texture_hardwall = _graph->getDriver()->getTexture(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/hard_wall.png"));
    texture_B = _graph->getDriver()->getTexture(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/bombe.png"));
    texture_I = _graph->getDriver()->getTexture(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/item.png"));
    texture_E = _graph->getDriver()->getTexture(static_cast<irr::io::path>(PATH) + static_cast<irr::io::path>("ressources/explode.png"));

    _cam = sceneManager->addCameraSceneNode(0, irr::core::vector3df(-13, -18, 15), irr::core::vector3df(-13, -12, 0));
}

Display::~Display()
{
    /* Freeing and destroying Border Vector */
    while (obj_border.size() != 0) {
        obj_border.at(0)->drop();
        obj_border.erase(obj_border.begin());
    }

    /* Freeing and destroying Wall Vector */
    while (obj_W.size() != 0) {
        obj_W.at(0)->drop();
        obj_W.erase(obj_W.begin());
    }

    /* Freeing and destroying HardWall Vector */
    while (obj_hardwall.size() != 0) {
        obj_hardwall.at(0)->drop();
        obj_hardwall.erase(obj_hardwall.begin());
    }

    /* Freeing and destroying Bomb Vector */
    while (obj_B.size() != 0) {
        obj_B.at(0)->drop();
        obj_B.erase(obj_B.begin());
    }

    /* Freeing and destroying Item Vector */
    while (obj_I.size() != 0) {
        obj_I.at(0)->drop();
        obj_I.erase(obj_I.begin());
    }

    while (obj_E.size() != 0) {
        obj_E.at(0)->drop();
        obj_E.erase(obj_E.begin());
    }

    // mesh_player->drop();
    // mesh_border->drop();
    // mesh_W->drop();
    // mesh_hardwall->drop();
    // mesh_B->drop();
    // mesh_I->drop();
    // texture_player->drop();
    // texture_border->drop();
    // texture_W->drop();
    // texture_hardwall->drop();
    // texture_B->drop();
    // texture_I->drop();
    // _cam->drop();

    //sceneManager->drop();
    //delete(sceneManager);
    std::cout << "display destroyed" << std::endl;
}

void Display::update_map(std::vector<std::string> map)
{
    int border = 0;
    int W = 0;
    int hardwall = 0;
    int B = 0;
    int I = 0;

    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map.at(0).size(); x++) {

            if (map.at(y).at(x) == '@') {
                if (border >= obj_border.size()) {
                    obj_border.push_back(sceneManager->addAnimatedMeshSceneNode(mesh_border));
                    obj_border.at(border)->setMaterialTexture(0, texture_border);
                }
                obj_border.at(border)->setPosition(irr::core::vector3df(-x * 2, -y * 2, 0));
                border++;
            }

            if (map.at(y).at(x) == 'W') {
                if (W >= obj_W.size()) {
                    obj_W.push_back(sceneManager->addAnimatedMeshSceneNode (mesh_W));
                    obj_W.at(W)->setMaterialTexture(0, texture_W);
                }
                obj_W.at(W)->setPosition(irr::core::vector3df(-x * 2, -y * 2, 0));
                W++;
            }

            if (map.at(y).at(x) == '#') {
                if (hardwall >= obj_hardwall.size()) {
                    obj_hardwall.push_back(sceneManager->addAnimatedMeshSceneNode (mesh_hardwall));
                    obj_hardwall.at(hardwall)->setMaterialTexture(0, texture_hardwall);
                }
                obj_hardwall.at(hardwall)->setPosition(irr::core::vector3df(-x * 2, -y * 2, 0));
                hardwall++;
            }

            if (map.at(y).at(x) == 'B') {
                if (B >= obj_B.size()) {
                    obj_B.push_back(sceneManager->addAnimatedMeshSceneNode (mesh_B));
                    obj_B.at(B)->setMaterialTexture(0, texture_B);
                }
                obj_B.at(B)->setPosition(irr::core::vector3df(-x * 2, -y * 2, 0));
                B++;
            }

            if (map.at(y).at(x) == 'I') {
                if (I >= obj_I.size()) {
                    obj_I.push_back(sceneManager->addAnimatedMeshSceneNode (mesh_I));
                    obj_I.at(I)->setMaterialTexture(0, texture_I);
                    obj_I.at(I)->setScale(irr::core::vector3df(0.7));
                }
                obj_I.at(I)->setPosition(irr::core::vector3df(-x * 2, -y * 2, 0));
                I++;
            }
        }
    }

    for (; border < obj_border.size(); border++)
        obj_border.at(border)->setPosition(irr::core::vector3df(-13, -18, 20));
    for (; W < obj_W.size(); W++)
        obj_W.at(W)->setPosition(irr::core::vector3df(-13, -18, 20));
    for (; hardwall < obj_hardwall.size(); hardwall++)
        obj_hardwall.at(hardwall)->setPosition(irr::core::vector3df(-13, -18, 20));
    for (; B < obj_B.size(); B++)
        obj_B.at(B)->setPosition(irr::core::vector3df(-13, -18, 20));
    for (; I < obj_I.size(); I++)
        obj_I.at(I)->setPosition(irr::core::vector3df(-13, -18, 20));
}

void Display::show(std::vector<std::string> map, std::vector<ICharacter *> charac)
{
    irr::core::vector3df tmppos;
    update_map(map);

    while (obj_player.size() > charac.size()) {
        obj_player.at(0)->setPosition(irr::core::vector3df(-13, -18, 20));
        obj_player.erase(obj_player.begin());
    }

    for (int i = 0; i < charac.size(); i++) {
        if (i >= obj_player.size()) {
            obj_player.push_back(sceneManager->addAnimatedMeshSceneNode (mesh_player));
            obj_player.at(i)->setMaterialTexture(0, texture_player);
            obj_player.at(i)->setScale(irr::core::vector3df(0.1));
            obj_player.at(i)->setRotation(irr::core::vector3df(90, 0, 0));
        }
        tmppos = obj_player.at(i)->getAbsolutePosition();
        if (charac.at(i)->getX() * -2 < tmppos.X)
            obj_player.at(i)->setRotation(irr::core::vector3df(90, 0, -90));
        else if (charac.at(i)->getX() * -2 > tmppos.X)
            obj_player.at(i)->setRotation(irr::core::vector3df(90, 0, 90));
        else if (charac.at(i)->getY() * -2 < tmppos.Y)
            obj_player.at(i)->setRotation(irr::core::vector3df(90, 0, 0));
        else if (charac.at(i)->getY() * -2 > tmppos.Y)
            obj_player.at(i)->setRotation(irr::core::vector3df(90, 0, 180));
        obj_player.at(i)->setPosition(irr::core::vector3df(charac.at(i)->getX() * -2, charac.at(i)->getY() * -2, 0));
    }

    irr::u32 tmptime = _graph->getDevice()->getTimer()->getTime();

    for (int i = 0; i < obj_E.size(); i++) {
        if (time_E.at(i) < tmptime) {
            obj_E.at(i)->setPosition(irr::core::vector3df(-13, -18, 20));
        }
    }

    if (_graph->getDevice()->run()) {
        driver->beginScene(true, true, irr::video::SColor(100, 100, 100, 0));
        sceneManager->drawAll();
        env->drawAll();
        driver->endScene();
    }
}

void Display::bombe_flame(int x, int y, int up, int right, int down, int left)
{
    int E = 0;
    irr::u32 tmptime = _graph->getDevice()->getTimer()->getTime();
    for (int X = x - left; X <= x + right; X++, E++) {
        if (E >= obj_E.size()) {
            time_E.push_back(tmptime + explode_time);
            obj_E.push_back(sceneManager->addAnimatedMeshSceneNode (mesh_E));
            obj_E.at(E)->setMaterialTexture(0, texture_E);
            obj_E.at(E)->setScale(irr::core::vector3df(0.7));
            obj_E.at(E)->setPosition(irr::core::vector3df(-X * 2, -y * 2, 0));
        } else if (time_E.at(E) < tmptime) {
            obj_E.at(E)->setPosition(irr::core::vector3df(-X * 2, -y * 2, 0));
            time_E.at(E) = tmptime + explode_time;
        } else {
            X--;
        }
    }

    for (int Y = y - up; Y <= y + down; Y++, E++) {
        if (E >= obj_E.size()) {
            time_E.push_back(tmptime + explode_time);
            obj_E.push_back(sceneManager->addAnimatedMeshSceneNode (mesh_E));
            obj_E.at(E)->setMaterialTexture(0, texture_E);
            obj_E.at(E)->setScale(irr::core::vector3df(0.7));
            obj_E.at(E)->setPosition(irr::core::vector3df(-x * 2, -Y * 2, 0));
        } else if (time_E.at(E) < tmptime) {
            obj_E.at(E)->setPosition(irr::core::vector3df(-x * 2, -Y * 2, 0));
            time_E.at(E) = tmptime + explode_time;
        } else {
            Y--;
        }
    }

    // for (; border < obj_border.size(); border++)
    //     obj_border.at(border)->setPosition(irr::core::vector3df(-13, -18, 20));
}

/*
    map_Kd ./crate_1.jpg --> for .mtl
*/
