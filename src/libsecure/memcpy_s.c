#include <string.h>

#ifdef __STDC_LIB_EXT1__
#define MEMCPY_S_AVAILABLE
#endif

#ifdef MEMCPY_S_AVAILABLE
void* memcpy_s(void *dest, size_t dest_size, const void *src, size_t count)
{
    if (count > dest_size)
    {
        return;
    }
    memcpy(dest, src, count);
}
#endif
