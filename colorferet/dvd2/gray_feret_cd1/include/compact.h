#ifndef COMPACT_H
#define COMPACT_H

#include <defs.h>
#include <comppad.h>

enum COMPACT {DONT_CARE, CAP, MINIMAL_PROCESSING, LINEAR_AX_B, TWO_SIGMA,
              HISTOGRAM_CLIP,
              BIPOLAR, MONOPOLAR, REALPART, IMAGPART, BOTHPART,
              COMPLEX_TORECT, COMPLEX_TOPOLAR};


template <class PP>
extern void df32_to_uc8(const PP *, const int, UCH *, const COMPACT);


extern void i32_to_uc8(const int     *, const int, UCH *, const COMPACT);
extern void c64_to_uc8(const COMPPAD *, const int, UCH *, const COMPACT);
#endif
