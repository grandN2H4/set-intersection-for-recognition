#ifndef LA_LINEAR_ALGEBRA_H
#define LA_LINEAR_ALGEBRA_H

#include <greyimage.h>

class CMAT;

class MMAT	// for basis vectors, and covariance matrices
{
   protected :
      void alloc(const int, const int);
      int ydim;		// dimensionality of one of the vectors
      int xdim;		// the number of vectors.
      float * mat;	// the data, say eigenvectors, or a covariance matrix 

   public :
      MMAT(const GREYIM * const *, const int);
      MMAT(float *, const int, const int);
      MMAT(const char *);		// construct by reading from file
      MMAT(const int, const int = 1);	// construct in place
     ~MMAT();				// bog standard destructor

      int numrows() const { return ydim; }
      int numcols() const { return xdim; }

      // return a pointer to the top of the i-th column
      float * data(const int jcol = 0)
         { return &mat[jcol*ydim]; }
      float * data(const int jcol = 0) const
         { return &mat[jcol*ydim]; }

      // indexing here is column major (not trad C row major)
      // not that the user should know nor care.
      inline float & operator() (const int irow, const int jcol)
         { return mat[jcol * ydim + irow]; }
      inline float & operator() (const int irow) // implies col is 0
         { return mat[irow]; }

      inline float   operator() (const int irow, const int jcol) const
         { return mat[jcol * ydim + irow]; }
      inline float   operator() (const int irow) const // implies col is 0
         { return mat[irow]; }

      // generate new instances from this one.
      MMAT *rowcolsum(const int);
      MMAT *rowsum();
      MMAT *colsum();
      MMAT *eigen(const int, MMAT **              );
      MMAT *eigen(const int, MMAT **, const MMAT &);

      CMAT *tocomplex_real();
      
      // act on this matrix, in place.
      MMAT &inverse();
      MMAT &transpose();
      MMAT &zero();
      MMAT &write(const char *);

      MMAT & operator += (const MMAT &);
      MMAT & operator -= (const MMAT &);
};


class CMAT	// for basis vectors, and covariance matrices
{
   protected :
      void alloc(const int, const int);
      int ydim;		// dimensionality of one of the vectors
      int xdim;		// the number of vectors.
      COMPPAD * mat;	// the data, say eigenvectors, or a covariance matrix 

   public :
      CMAT(const GREYIM * const *, const int);
      CMAT(COMPPAD *, const int, const int);
      CMAT(const char *);		// construct by reading from file
      CMAT(const int, const int = 1);	// construct in place
     ~CMAT();				// bog standard destructor

      int numrows() const { return ydim; }
      int numcols() const { return xdim; }
      COMPPAD * data()    { return mat;  }  // allow access to the data

      // indexing here is column major (not trad C row major)
      // not that the user should know nor care.
      inline COMPPAD & operator() (const int irow, const int jcol)
         { return mat[jcol * ydim + irow]; }
      inline COMPPAD & operator() (const int irow) // implies col is 0
         { return mat[irow]; }

      inline COMPPAD   operator() (const int irow, const int jcol) const
         { return mat[jcol * ydim + irow]; }
      inline COMPPAD   operator() (const int irow) const // implies col is 0
         { return mat[irow]; }

      // act on this matrix, in place.
      CMAT &conjugate();
      CMAT &inverse();
      CMAT &transpose();
      CMAT &zero();
      CMAT &write(const char *);

      CMAT & operator += (const CMAT &);
      CMAT & operator -= (const CMAT &);

      MMAT *realpart();
      MMAT *imagpart();
};

template <class QMAT>
extern QMAT *mmat_mult(const QMAT &, const QMAT &, const char *);

extern CMAT *mmat_mult(const CMAT &, const MMAT &);

extern MMAT *  mmat_cross(const MMAT &, const MMAT &);
extern float   mmat_dot(  const MMAT &, const MMAT &);
extern COMPPAD mmat_dot(  const CMAT &, const CMAT &);

MMAT * mmat_eigenpseudo(const MMAT &, const MMAT &, const MMAT &, MMAT **);


#endif
