/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Graphique
*/

#ifndef GRAPHIQUE_HPP_
#define GRAPHIQUE_HPP_

#include <irrlicht/irrlicht.h>
#include <irrlicht/IEventReceiver.h>
#include "../include/EventReceiver.hpp"

class Graphique {
    public:
        Graphique();
        ~Graphique();
        irr::IrrlichtDevice *getDevice() const;
        void setDevice(irr::IrrlichtDevice *device);
        irr::video::IVideoDriver *getDriver() const;
        EventReceiver getReceiver() const;
        void setReceiver(EventReceiver receiver);
        irr::core::dimension2du getWindowSize() const;

    protected:
    private:
        irr::IrrlichtDevice* _device;
        EventReceiver _receiver;
        irr::video::IVideoDriver* _driver;
        irr::core::dimension2du _WindowSize;
};

#endif /* !GRAPHIQUE_HPP_ */
