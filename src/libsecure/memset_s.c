#include <string.h>

#ifdef __STDC_LIB_EXT1__
#define MEMSET_S_AVAILABLE
#endif

#ifdef MEMSET_S_AVAILABLE
void *memset_s(void *dest, size_t dest_size, int ch, size_t count)
{
    if (count > dest_size)
    {
        return NULL;
    }
    return memset(dest, ch, count);
}
#endif
