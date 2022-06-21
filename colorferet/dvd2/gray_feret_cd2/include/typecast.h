#ifndef TYPECAST_H
#define TYPECAST_H

#include <compact.h>
#include <greyimage.h>

typedef GREYIM *(TYPECASTFUNC) (const GREYIM *,           const COMPACT);
typedef GREYIM *(TYPEINTOFUNC) (const GREYIM *, GREYIM *, const COMPACT);

typedef GREYIM_ABORT_ONE TYPETESTABORT;
typedef GREYIM_PREDICATE TYPETESTPREDI;


extern GREYIM *gimage_totype(const GREYIM *,
                             const COMPACT, const IMAGEDATATYPE);
extern GREYIM *gimage_forcetype(   GREYIM **,
                             const COMPACT, const IMAGEDATATYPE);

extern TYPECASTFUNC gimage_toint;		// make new type image
extern TYPECASTFUNC gimage_tofloat;
extern TYPECASTFUNC gimage_todouble;
extern TYPECASTFUNC gimage_tocomplex;
extern TYPECASTFUNC gimage_touc;
extern TYPECASTFUNC gimage_tobinary;

extern TYPEINTOFUNC gimage_intoint;		// insert in existing image
extern TYPEINTOFUNC gimage_intofloat;
extern TYPEINTOFUNC gimage_intodouble;
extern TYPEINTOFUNC gimage_intocomplex;
extern TYPEINTOFUNC gimage_intouc;
extern TYPEINTOFUNC gimage_intobinary;

extern TYPETESTABORT gimage_complex;		// exit program is wrong type
extern TYPETESTABORT gimage_float;
extern TYPETESTABORT gimage_double;
extern TYPETESTABORT gimage_int;
extern TYPETESTABORT gimage_short;
extern TYPETESTABORT gimage_uc;
extern TYPETESTABORT gimage_none;
extern TYPETESTABORT gimage_binary;

extern TYPETESTPREDI gimage_iscomplex;		// gimage type predicates
extern TYPETESTPREDI gimage_isdouble;
extern TYPETESTPREDI gimage_isfloat;
extern TYPETESTPREDI gimage_isint;
extern TYPETESTPREDI gimage_isshort;
extern TYPETESTPREDI gimage_isuc;
extern TYPETESTPREDI gimage_isnone;
extern TYPETESTPREDI gimage_isbinary;

extern int tiscomplex(const IMAGEDATATYPE );	// low level predicates
extern int tisfloat(const IMAGEDATATYPE );
extern int tisdouble(const IMAGEDATATYPE );
extern int tisint(const IMAGEDATATYPE );
extern int tisshort(const IMAGEDATATYPE );
extern int tisuc(const IMAGEDATATYPE );
extern int tisnone(const IMAGEDATATYPE );
extern int tisbinary(const IMAGEDATATYPE );

extern int gimage_issametype(const GREYIM *, const GREYIM *);
extern int tissametype(const IMAGEDATATYPE, const IMAGEDATATYPE);
extern int tissuperiortype(const IMAGEDATATYPE, const IMAGEDATATYPE);
extern int gimage_issuperiortype(const GREYIM *, const GREYIM *);
extern void *gimage_typeassert(const GREYIM *, const IMAGEDATATYPE);

/*
extern VEK<COMPPAD>  & gimage_vekcomplex(const GREYIM *inp);
extern VEK<double>   & gimage_vekdouble(const GREYIM *inp);
extern VEK<float>    & gimage_vekfloat(const GREYIM *inp);
extern VEK<int>      & gimage_vekint(const GREYIM *inp);
extern VEK<short>    & gimage_vekshort(const GREYIM *inp);
extern VEK<UCH>      & gimage_vekuc(const GREYIM *inp);
*/

inline COMPPAD  *gimage_ptrcomplex(const GREYIM *inp)
  { return (COMPPAD *)gimage_typeassert(inp, IDATATYPE_COMPLEX); }
inline double   *gimage_ptrdouble(const GREYIM *inp)
  { return (double  *)gimage_typeassert(inp, IDATATYPE_DOUBLE ); }
inline float    *gimage_ptrfloat(const GREYIM *inp)
  { return (float   *)gimage_typeassert(inp, IDATATYPE_FLOAT  ); }
inline int      *gimage_ptrint(const GREYIM *inp)
  { return (int     *)gimage_typeassert(inp, IDATATYPE_INT    ); }
inline short    *gimage_ptrshort(const GREYIM *inp)
  { return (short   *)gimage_typeassert(inp, IDATATYPE_SHORT  ); }
inline UCH      *gimage_ptruc(const GREYIM *inp)
  { return (UCH     *)gimage_typeassert(inp, IDATATYPE_UC     ); }
inline UCH      *gimage_ptrbinary(const GREYIM *inp)
  { return (UCH     *)gimage_typeassert(inp, IDATATYPE_BINARY ); }

inline COMPPAD *gimage_ptrcomplex(const GREYIM *inp, const int x, const int y)
  { return gimage_ptrcomplex(inp) + y*inp->w() + x; }
inline double  *gimage_ptrdouble( const GREYIM *inp, const int x, const int y)
  { return gimage_ptrdouble (inp) + y*inp->w() + x; }
inline float   *gimage_ptrfloat(  const GREYIM *inp, const int x, const int y)
  { return gimage_ptrfloat  (inp) + y*inp->w() + x; }
inline int     *gimage_ptrint(    const GREYIM *inp, const int x, const int y)
  { return gimage_ptrint    (inp) + y*inp->w() + x; }
inline short   *gimage_ptrshort(  const GREYIM *inp, const int x, const int y)
  { return gimage_ptrshort  (inp) + y*inp->w() + x; }
inline UCH     *gimage_ptruc(     const GREYIM *inp, const int x, const int y)
  { return gimage_ptruc     (inp) + y*inp->w() + x; }
inline UCH     *gimage_ptrbinary( const GREYIM *inp, const int x, const int y)
  { return gimage_ptrbinary (inp) + y*inp->w() + x; }

#endif
