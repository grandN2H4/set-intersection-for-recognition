#ifndef GREYFUNCS_H
#define GREYFUNCS_H

class GREYIM;

// take two images, affect the first one using the second: for
// example apply some binary operator to the two arguments, side
// effecting the first one, leaving the second untouched
// and returning the first.
typedef GREYIM * (GREYIM_OPERATOR)(GREYIM *, const GREYIM *);
typedef GREYIM * (GREYIM_MASKEDOPERATOR)(GREYIM *, const GREYIM *, const GREYIM * = 0);

// take two images, use them to produce a new one: for example
// apply some binary operator to the two arguments, generate
// the result in a new image, leave the inputs untouched,
// and returning the new result.
typedef GREYIM * (GREYIM_OPANDGEN)(const GREYIM *, const GREYIM *);
typedef GREYIM * (GREYIM_MASKEDOPANDGEN)(const GREYIM *, const GREYIM *, const GREYIM * = 0);

// apply some transformation that requires no parameters to
// the input thereby side-effecting it then return it too
typedef GREYIM * (GREYIM_UNARYOP)(GREYIM *);

// apply some transformation that requires no parameters to
// the input producing a new image that is returned; the input
// is untouched
typedef GREYIM * (GREYIM_PRODUCER)(const GREYIM *);



// take some input, generate some new version of it, the operation
// being defined by the supplied parameter vector, return the new
// image. the inputs are left untouched.
typedef GREYIM *(GREYIM_GENERATOR)(const GREYIM *, const double *);

// operate on the input, using the parameters supplied, the changed
// input is returned, the parameters are left untouched.
typedef GREYIM *(GREYIM_ADJUSTOR )(      GREYIM *, const double *);



// combine the two arguments, and return a scalar quantity,
// leaving both inputs untouched
typedef double (GREYIM_COMPARATOR)(const GREYIM *, const GREYIM *);

// extract a scalar quantity from the argument, and return it
// leaving the input untouched, optionally supply a masking image
typedef double (GREYIM_D_DESCRIPTOR)(const GREYIM *, const GREYIM * = 0);

// extract a scalar quantity from the argument, and return it
// leaving the input untouched - as above except for the return type
typedef int    (GREYIM_I_DESCRIPTOR)(const GREYIM *);

// operate on the data of one specified row or column of the argument
// leaving the input untouched, returning a scalar representation.
typedef double (GREYIM_ROWCOLOP)(const GREYIM *, const int);



// compare the two arguments and exit the program on some condition
// otherwise return the first input. the arguments are untouched.
typedef const GREYIM *(GREYIM_ABORT_TWO)(const GREYIM *, const GREYIM *);

// assert some property of the input, exit if the assertion fails
// otherwise return the input untouched
// was previously:
typedef const GREYIM *(GREYIM_ABORT_ONE)(const GREYIM *);
// typedef       GREYIM *(GREYIM_ABORT_ONE)(      GREYIM *);

// test some property of the input, return a code indicating
// veracity. leave the input untouched.
typedef int (GREYIM_PREDICATE)(const GREYIM *);

#endif
