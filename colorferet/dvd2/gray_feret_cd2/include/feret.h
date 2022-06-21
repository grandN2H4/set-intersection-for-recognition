#ifndef __FERET_OR_FIRKIN
#define __FERET_OR_FIRKIN

#include <ihead.h>

extern float *writeferetraster(const char *, float *);
extern IHEAD *readferetraster(const char *, void **);
extern int isferetfile(const char *);

extern const int feretwidth;
extern const int feretheight;

#endif
