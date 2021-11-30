#include "tool.h"

uint64_t GetTimeNow(){
    struct timeval tv; 
    gettimeofday(&tv, nullptr);
    return (tv.tv_sec * 1e6 + tv.tv_usec); 
}