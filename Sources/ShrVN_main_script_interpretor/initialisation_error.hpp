#ifndef INITIALISATION_ERROR_HPP
#define INITIALISATION_ERROR_HPP

#include <exception>

class Initialisation_Error : public std::exception
{
    const char * m_msg;
public:
    Initialisation_Error(const char * msg);
    const char * what () const noexcept override;
};

#endif // INITIALISATION_ERROR_HPP
