#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <IListener.hpp>
#include <vector>



class Handler
{
    std::vector<IListener*> m_listeners;
public:
    Handler();
    void Subscribe(IListener *listener);
    void NotifyListeners();
};

#endif // HANDLER_HPP
