#include "tool.h"

namespace gamecommon{
    uint64_t GetTimeNow(){
        struct timeval tv; 
        gettimeofday(&tv, nullptr);
        return (tv.tv_sec * 1E6 + tv.tv_usec); 
    }
}