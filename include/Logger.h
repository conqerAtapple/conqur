#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdio.h>

#define trace()\
    printf("[TRACE] [%s : %d] \n", __PRETTY_FUNCTION__, __LINE__);

#define debug(fmt, msg...)\
    printf("[TRACE] [%s : %d]:::"fmt"\n", __PRETTY_FUNCTION__, __LINE__, ##msg);

#endif

