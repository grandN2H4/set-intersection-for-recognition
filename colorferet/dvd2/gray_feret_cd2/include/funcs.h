#ifndef FUNK_RAUM
#define FUNK_RAUM

#include <math.h>
#include <defs.h>
#include <comppad.h>

// sigmoid                   a
// function        y = --------------
//                     1 + e^(c(x-b))

inline double sig(const double x) { return 1.0 / (1.0 + exp(x)); }
inline double sig(const double a, const double b,
                  const double c, const double x)
  { return a / (1.0 + exp(c * (x - b))); }


extern double pow(const double, const int);
extern double siginv(const double, const double, const double, const double);

template <class PP>
inline PP sqr(const PP x) { return x*x; }

template <class PP>
inline PP negate(const PP x) { return -x; }

template <class PP>
extern PP randsign(const PP, const UINT = 0);

template <class PP>
inline PP quadval(const PP *abc, const PP x)
  { return abc[0]*x*x + abc[1]*x + abc[2]; }

template <class PP>
extern PP *quadsolve(const PP, const PP, const PP);

template <class PP>
extern PP quadextrema(const PP *, PP *, int *);

extern double *quadfit(const double x[3], const double fx[3]);

extern double ma_to_mi(const double);
extern double mi_to_ma(const double);
extern double contrast_ratio(const double, const double);
extern double modulation(const double, const double);

// matrix inversion - wrapper of spofa/spodi
extern void do_inverse_f(float   *, const int);
extern void do_inverse_d(double  *, const int);
extern void do_inverse_c(COMPPAD *, const int);


// fill in upper half of matrix given a completed lower half
template <class PP>
extern void fill_by_symmetry(PP *, const int);

template <class PP>
PP *do_transpose(const PP *, PP *, const int, const int);

#endif
