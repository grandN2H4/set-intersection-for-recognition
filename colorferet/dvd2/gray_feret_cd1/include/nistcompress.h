#ifndef NIST_COMP_H
#define NIST_COMP_H

// this line added Nov 29 2000
#undef REALLY_WANT_NIST_COMPRESSION_ROUTINES






#ifdef REALLY_WANT_NIST_COMPRESSION_ROUTINES

#include <defs.h>

extern int grp4comp  (const UCH *, int, int, int, UCH *);
extern void grp4decomp(UCH *, int, int, int, UCH *, int *);

extern int jpegcomp  (const UCH *, const int, const int, const int, const int, UCH *);
extern void jpegdecomp(UCH *, const int, const int, const int, UCH *);

#endif
#endif // NIST_COMP_H
