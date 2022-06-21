#ifndef PADDY_LINEAR_ALGEBRA_H
#define PADDY_LINEAR_ALGEBRA_H

#include <greyimage.h>
#include <la.h>
#include <la_cova.h>

extern GREYIM_PRODUCER gimage_inverse;


extern int diag_mat(
             const int order,
             float *mat,
             const int n_find,
             const int verbose,
             float **evals,
             float **evecs,
             int   **didnt_converge_indices);

float * basis_read( const char *, int *, int *, float **, float **);
void    basis_write(const char  *, const int,     const int,
                    const float *, const float *, const float *);


extern float slamch_cside();
extern int   ilaenv_cside(const int);

#endif
