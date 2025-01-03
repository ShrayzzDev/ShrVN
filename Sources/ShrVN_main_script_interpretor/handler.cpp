#include "handler.hpp"
#include <iostream>

Handler::Handler()
{

}

void Handler::Subscribe(IListener *listener)
{
    m_listeners.push_back(listener);
}

void Handler::NotifyListeners()
{
    for (auto & listener : m_listeners)
        listener->Update();
}
