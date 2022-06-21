#ifndef LINED_INC
#define LINED_INC

extern int bresenham(const int, const int,
                     const int, const int, int *, int *);
extern int realline(const double, const double,
                    const double, const double, const int, double **, double **);

template <class PP>
PP bilinear(const PP *,
            const int, const int, const double, const double);

template <class PP>
PP unilinear(const PP *, const int, const double);


class XYCO
{
public :
   double x;
   double y;

   XYCO() {};
   XYCO(const double xx, const double yy) : x(xx), y(yy) {};
  ~XYCO() {};
};


// the following routines remap pixels in arbitrary ways.
// could be rotation, affine, or something really weird.

// PUSH all the pixels of the input to the location in the output
// as specified by the locations in the coordinate array.
template <class PP>
void do_arb_push(const PP *, PP *, const int, const int,
                 const int, const int, const XYCO *);

// this is identical to "do_arb_push" except only nonzero pixels are moved
// which is efficient if the background is zero anyway and the image is
// dilute in non zeroes.
template <class PP>
void do_bin_push(const PP *, PP *, const int, const int,
                 const int, const int, const XYCO *);

// PULL pixels from the source into each location of the destination.
// the array of coordinates indicates where a destination pixel will
// be PULLED from.
template <class PP>
void do_arb_pull(const PP *, PP *, const int, const int,
                 const int, const int, const XYCO *);

// compute where a destination pixel will be PULLED from and PULL
// a bilinearly interpolated value from the source array
template <class PP>
void do_interp_pull(const PP *, PP *, const int, const int,
                    const int, const int, const XYCO *);

#endif
