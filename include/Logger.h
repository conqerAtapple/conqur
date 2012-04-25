#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>

#include "atomic.h"

class Logger
{
public:
    typedef std::ostream& (*manip_type)(std::ostream&);

    //TODO: handle MT
    static Logger& getInstance()
    {
        if(instance == NULL)
        {
            instance = new Logger();
        }
        std::cout  << std::endl;
        return *instance;
    }
    
    template<typename T>
    Logger& display (T& m)
    {
        std::cout  << m;
        return *this;
    }
    
    Logger& operator<<(manip_type pfn) 
    {       
        std::cout  << pfn;
        return *this; 
    }    

private:
    Logger()
    {
    }
    static Logger* instance;
    spinlock_t lock;
};

template <typename T>
Logger& operator << (Logger& logger, T t)
{
    logger.display(t) ;
    return logger;
}

#define debug(msg)\
       Logger& logger = Logger::getInstance(); logger  <<  __FUNCTION__ << ":" << __LINE__ << ":::" <<  msg; logger

#define eol std::endl

#endif

