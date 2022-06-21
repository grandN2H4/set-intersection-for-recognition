#ifndef _PJG_LOOKER_
#define _PJG_LOOKER_


class LOOKT
{
   private :
      double *fvals;
      double *xvals;
      int n;

   public :
      LOOKT(const char *, int);		// read a look up table from file
					// optionally check monotonicity

     ~LOOKT() { delete [] xvals; delete [] fvals; n = 0; }

      double f(   const double);        // y = f(x)
      double finv(const double);        // x = f^-1(y)

      void check_monotonicity();
};

#endif
