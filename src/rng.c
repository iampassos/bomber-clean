#include "rng.h"
#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <process.h>
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
#include <stdlib.h>

void seed_rng(void) {
#if defined(_WIN32) || defined(_WIN64)
  LARGE_INTEGER li;
  QueryPerformanceCounter(&li);
  srand((unsigned int)(li.QuadPart ^ _getpid()));
#else
  struct timeval tv;
  gettimeofday(&tv, NULL);
  srand(tv.tv_usec ^ tv.tv_sec ^ getpid());
#endif
}
