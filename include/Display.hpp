/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Display
*/

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <vector>
#include <string>
#include "../include/EventReceiver.hpp"
#include "../include/Graphique.hpp"
#include "ICharacter.hpp"

#ifdef __linux__
  #define PATH ""
#elif defined _WIN32 || defined _WIN64
  #define PATH "../../../"
#else
#error "unknown platform"
#endif

class ICharacter;

class Display
{
    public:
        Display(Graphique *graph);
        ~Display();
        void show(std::vector<std::string> map, std::vector<ICharacter *> charac);
        void bombe_flame(int x, int y, int up, int right, int down, int left);
    private:
        void update_map(std::vector<std::string> map);
        void setActiveCamera(irr::scene::ICameraSceneNode *Active);
        Graphique *_graph;
        irr::scene::ICameraSceneNode *_cam;

        irr::SKeyMap keyMap[5];

        int explode_time;
        std::vector<irr::u32> time_E;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> obj_player;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> obj_border;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> obj_W;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> obj_hardwall;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> obj_B;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> obj_I;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> obj_E;
        irr::scene::IAnimatedMesh *mesh_player;
        irr::scene::IAnimatedMesh *mesh_border;
        irr::scene::IAnimatedMesh *mesh_W;
        irr::scene::IAnimatedMesh *mesh_hardwall;
        irr::scene::IAnimatedMesh *mesh_B;
        irr::scene::IAnimatedMesh *mesh_I;
        irr::scene::IAnimatedMesh *mesh_E;
        irr::video::ITexture *texture_player;
        irr::video::ITexture *texture_border;
        irr::video::ITexture *texture_W;
        irr::video::ITexture *texture_hardwall;
        irr::video::ITexture *texture_B;
        irr::video::ITexture *texture_I;
        irr::video::ITexture *texture_E;

        irr::core::vector3df camPos;

        EventReceiver rec;
        irr::scene::ISceneManager *sceneManager;
        irr::video::IVideoDriver *driver;
        irr::scene::ICameraSceneNode *Camera[2] = {0, 0};
        irr::gui::IGUIEnvironment* env;
};

#endif