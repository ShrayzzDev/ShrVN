#ifndef OBSERVABLEOBJECT_H
#define OBSERVABLEOBJECT_H

#include "handler.hpp"


class ObservableObject
{
    static Handler m_handler;
public:
    ObservableObject();
    void Notify();
    static void Subscribe(IListener *listener);
    void virtual ReactEvent() = 0;
};

#endif // OBSERVABLEOBJECT_H
