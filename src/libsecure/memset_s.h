#ifndef MEMSET_S_H_
#define MEMSET_S_H_

// #include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __STDC_LIB_EXT1__
#define MEMSET_S_AVAILABLE
#endif

#ifdef MEMSET_S_AVAILABLE
void* memset_s(void* dest, size_t destsz, int c, size_t count);
#endif

#ifdef __cplusplus
}
#endif

#endif /* MEMSET_S_H */
