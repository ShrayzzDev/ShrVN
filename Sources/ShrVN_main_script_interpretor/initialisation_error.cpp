#include "initialisation_error.hpp"

Initialisation_Error::Initialisation_Error(const char * msg)
    :m_msg{msg}
{

}

const char *Initialisation_Error::what() const noexcept
{
    return m_msg;
}
