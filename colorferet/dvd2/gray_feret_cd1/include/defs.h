#ifndef DEFSH_H
#define DEFSH_H

#include <iostream.h>
#include <math.h>	// for M_PI

// general purpose defines
typedef const double CDB;

#ifndef UCHAR_H
#define UCHAR_H
typedef unsigned char UCH;
#endif

#ifndef UUINT_H
#define UUINT_H
typedef unsigned int UINT;
#endif

#ifndef UULNG_H
#define UULNG_H
typedef unsigned long ULNG;
#endif

#ifndef UUSHT_H
#define UUSHT_H
typedef unsigned short USHORT;
#endif

enum {FALSE=0, TRUE=1};
enum LINEAROP {BAD, ROWS, COLS, LINE};

inline int sround(const UCH	x) { return (int)x; }
inline int sround(const short	x) { return (int)x; }
inline int sround(const int	x) { return x; }
inline int sround(const float	x) { return (int)(x < 0.0 ? x-0.5 : x+0.5); }
inline int sround(const double	x) { return (int)(x < 0.0 ? x-0.5 : x+0.5); }

#pragma interface
template <class PP>
inline PP max(const PP a, const PP b) { return (a > b) ? a : b; }

#pragma interface
template <class PP>
inline PP min(const PP a, const PP b) { return (a < b) ? a : b; }

// template <class PP>
// inline UCH cap(const PP a) { return (UCH)max(0, min(255, sround(a))); }

#pragma interface
template <class PP>
inline PP tabs(const PP x) { return (x < 0) ? -x : x; }

// return the first argument with the sign of the second
#pragma interface
template <class PP>
inline PP tsgn(const PP x, const PP y) { return (y < 0) ? -tabs(x) : tabs(x); }

inline double rad2deg(const double r)
   { return 180.0 * r / M_PI; }

inline double deg2rad(const double d)
   { return d * M_PI / 180.0; }

#endif // DEFSH_H
