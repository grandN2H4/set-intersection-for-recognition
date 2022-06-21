#ifndef SUNSH_H
#define SUNSH_H

#include <rasterfile.h>
#include <ihead.h>

typedef struct rasterfile RAS;

extern IHEAD *readsunraster(const char *, void **);
extern void writesunraster(const char *, const IHEAD *,
                         const void *, const char * = 0);
extern int issunrasterfile(const char *);
extern int sunnumpadbits(const int, const int);

extern void sun_read_byteorder_correct(RAS &);
extern void sun_write_byteorder_correct(RAS &);

extern int readsuncolormap(const char *, UCH **);
extern void writesuncolormap(const char *, UCH *, const int);

#endif
