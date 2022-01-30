/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EventReceiver
*/

#include "../include/EventReceiver.hpp"

EventReceiver::EventReceiver()
{
    for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

irr::SEvent EventReceiver::getEvent() const
{
    return (_event);
}

void EventReceiver::resetEvent()
{
    _event.GUIEvent.EventType = (irr::gui::EGUI_EVENT_TYPE)0;
}

void EventReceiver::setEvent(irr::SEvent event)
{
    _event = event;
}

bool EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

bool EventReceiver::OnEvent(const irr::SEvent& event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    _event = event;
    return false;
}