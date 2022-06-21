#ifndef PGM__SH_H
#define PGM__SH_H

#include <ihead.h>


extern IHEAD *readpgmraster(const char *, void **);
// extern void writesunraster(const char *, const IHEAD *,
//                            const void *, const char * = 0);
extern int ispgmrasterfile(const char *);



#endif
