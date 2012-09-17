#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>

#include "atomic.h"
#include "logger.h"

class Logger
{
public:

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
         Logger& logger = Logger::getInstance(); logger  <<  __FUNCTION__ << ":" << __LINE__ << ":::" <<  msg; logger \       
        


typedef int tracepoint;

struct trace_desc {
  tracepoint *point;
  unsigned long jump_from;
  unsigned long jump_to;
} __attribute__((packed));

void enable(tracepoint *point) ;

#define eol std::endl


#endif

