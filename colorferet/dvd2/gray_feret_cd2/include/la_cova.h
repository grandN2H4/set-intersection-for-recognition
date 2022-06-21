#ifndef LA_COAV_H
#define LA_COAV_H

#include <la.h>

enum COVAR_STYLE {COVAR_INNER_PRODUCT, COVAR_OUTER_PRODUCT};

extern MMAT *mk_inner_product_covar(const MMAT &, MMAT **);
extern MMAT *mk_outer_product_covar(const MMAT &, MMAT **);
#endif
