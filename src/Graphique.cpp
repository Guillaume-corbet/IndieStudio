/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Graphique
*/

#include "../include/Graphique.hpp"

Graphique::Graphique()
{
    _WindowSize.set(1920, 1080);
    _device = irr::createDevice(irr::video::EDT_OPENGL, _WindowSize, 32, false, false, false, &_receiver);
    _driver = _device->getVideoDriver();
}

Graphique::~Graphique()
{
    if (this->_device->run())
        this->_device->closeDevice();
    // _device->drop();
}

irr::core::dimension2du Graphique::getWindowSize() const
{
    return (_WindowSize);
}

irr::video::IVideoDriver *Graphique::getDriver() const
{
    return (this->_driver);
}

irr::IrrlichtDevice *Graphique::getDevice() const
{
    return (this->_device);
}

void Graphique::setDevice(irr::IrrlichtDevice *device)
{
    this->_device = device;
}

EventReceiver Graphique::getReceiver() const
{
    return (_receiver);
}

void Graphique::setReceiver(EventReceiver receiver)
{
    this->_receiver = receiver;
}