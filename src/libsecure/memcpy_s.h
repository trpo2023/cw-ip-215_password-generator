#ifndef MEMCPY_S_H_
#define MEMCPY_S_H_

// #include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __STDC_LIB_EXT1__
#define MEMCPY_S_AVAILABLE
#endif

#ifdef MEMCPY_S_AVAILABLE
void memcpy_s(void *dest, size_t dest_size, const void *src, size_t n);
#endif

#ifdef __cplusplus
}
#endif

#endif /* MEMCPY_S_H_ */
