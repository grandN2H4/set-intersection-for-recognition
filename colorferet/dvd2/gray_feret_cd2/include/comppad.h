#ifndef COMPLX_H
#define COMPLX_H

#include <iostream.h>
#include <math.h>

class COMPLEX_POLARITY
{
   public :
      enum CPO {UNKNOWN, RECT, POLAR} ;
      CPO pr;
      COMPLEX_POLARITY() : pr(UNKNOWN) {}
      COMPLEX_POLARITY(const COMPLEX_POLARITY &);
      COMPLEX_POLARITY(const char);

      friend ostream & operator << (ostream &, const COMPLEX_POLARITY &);
      char polarcode() const;
};


class COMPPAD;
typedef COMPPAD (COMPLEXFUNC_C2C)(const COMPPAD &);
typedef float   (COMPLEXFUNC_C2F)(const COMPPAD &);

class COMPPAD
{
   private :
      float real;
      float imag;

   public :
      inline float    re() const { return real; }
      inline float    im() const { return imag; }
      inline float & are()       { return real; }
      inline float & aim()       { return imag; }

   enum REALITY  {REALONLY, IMAGONLY, FULLYCOMPLEX};
   enum POLARITY {UNKNOWN, RECT, POLAR};

   COMPPAD () {};
  ~COMPPAD () {};

   COMPPAD(const COMPPAD &x) : real(x.re()), imag(x.im()) {}
   COMPPAD(const float  r, const float  i = 0.0) : real(       r), imag(       i) {}
   COMPPAD(const double r, const double i = 0.0) : real((float)r), imag((float)i) {}

   // ---------------------------------------------------------------------------------- 
   // ---------------------------------------------------------------------------------- 
   inline COMPPAD & operator = (const float   rr)
      { real = rr;     imag = 0.0;    return *this; }
   inline COMPPAD & operator = (const COMPPAD &x)
      { real = x.real; imag = x.imag; return *this; }

   // ---------------------------------------------------------------------------------- 
   // ---------------------------------------------------------------------------------- 
   inline float pow()  const { return real*real + imag*imag; }
   inline float mod()  const { return (float)sqrt((double)pow()); }
   inline float pha1() const { return atan ((double)imag/(double)real); }
   inline float pha2() const { return atan2((double)imag,(double)real); }

   inline COMPPAD & operator - (void) { real = -real; imag = -imag; return *this; }
   inline COMPPAD & operator ! (void) { real = -real;               return *this; }
   inline COMPPAD & operator ~ (void) { imag = -imag;               return *this; }

   // ---------------------------------------------------------------------------------- 
   // ---------------------------------------------------------------------------------- 
   inline COMPPAD   operator + (const COMPPAD &x) const
      { return COMPPAD(real + x.re(), imag + x.im()); }
   inline COMPPAD   operator - (const COMPPAD &x) const
      { return COMPPAD(real - x.re(), imag - x.im()); }
   inline COMPPAD   operator * (const COMPPAD &x) const
      { return COMPPAD(real*x.real - imag*x.imag, imag*x.real + real*x.imag); }
   inline COMPPAD   operator / (const COMPPAD &x) const
      { COMPPAD t = x; ~t; t *= *this; return t /= x.pow(); }

   // ---------------------------------------------------------------------------------- 
   // ---------------------------------------------------------------------------------- 
   inline COMPPAD & operator += (const COMPPAD &x)
      { real += x.re(); imag += x.im(); return *this; }
   inline COMPPAD & operator -= (const COMPPAD &x)
      { real -= x.re(); imag -= x.im(); return *this; }
   inline COMPPAD & operator *= (const COMPPAD &x)
      { const float tmp = real; real = tmp * x.real - imag * x.imag;
                                imag = tmp * x.imag + imag * x.real; return *this; }
   inline COMPPAD & operator /= (const COMPPAD &x)
      { COMPPAD t = x; ~t; *this *= t; return *this /= x.pow(); }

   // ---------------------------------------------------------------------------------- 
   // ---------------------------------------------------------------------------------- 
   inline COMPPAD operator * (const float s) const
      { return COMPPAD(real * s, imag * s); }

   // ---------------------------------------------------------------------------------- 
   // ---------------------------------------------------------------------------------- 
   inline COMPPAD & operator += (const float x) { real += x;            return *this; }
   inline COMPPAD & operator -= (const float x) { real -= x;            return *this; }
   inline COMPPAD & operator *= (const float x) { real *= x; imag *= x; return *this; }
   inline COMPPAD & operator /= (const float x) { real /= x; imag /= x; return *this; }

   // operations on complex numbers in polar form r.exp(i.phi)
   inline COMPPAD & modulate(  const float a) { real *= a; return *this; }
   inline COMPPAD & phaseshift(const float p) { imag += p; return *this; }

   friend ostream & operator << (ostream &, const COMPPAD &);
   friend istream & operator >> (istream &,       COMPPAD &);
};

extern COMPLEXFUNC_C2F pow;
extern COMPLEXFUNC_C2F modulus;
extern COMPLEXFUNC_C2F pha1;
extern COMPLEXFUNC_C2F pha2;
extern COMPLEXFUNC_C2C sqrt;
extern COMPLEXFUNC_C2C topolar;
extern COMPLEXFUNC_C2C frompolar;
enum COMPLEX_OP {COMPLEX_REALPART, COMPLEX_IMAGPART, COMPLEX_BOTHPART};

/*
inline COMPPAD operator - (const float s, COMPPAD &x) { return COMPPAD(s-x.re(), -x.im()); }
inline COMPPAD operator - (COMPPAD &x, const float s) { return COMPPAD(x.re()-s,  x.im()); }
*/

#endif	// COMPLX_H
