#include "observableobject.h"

Handler ObservableObject::m_handler;

ObservableObject::ObservableObject()
{

}

void ObservableObject::Notify()
{
    m_handler.NotifyListeners();
}

void ObservableObject::Subscribe(IListener *listener)
{
    m_handler.Subscribe(listener);
}
