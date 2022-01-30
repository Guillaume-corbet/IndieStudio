/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EventReceiver
*/

#ifndef EVENTRECEIVER_HPP_
#define EVENTRECEIVER_HPP_

#include <irrlicht/irrlicht.h>
#include <irrlicht/driverChoice.h>

class EventReceiver : public irr::IEventReceiver
{
    public:
        EventReceiver();
        virtual bool OnEvent(const irr::SEvent& event);
        virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
        irr::SEvent getEvent() const;
        void setEvent(irr::SEvent event);
        void resetEvent();
    private:
        bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
        irr::SEvent _event;
};

#endif /* !EVENTRECEIVER_HPP_ */
