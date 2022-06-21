#ifndef INCLUDED_GREYGEOM
#define INCLUDED_GREYGEOM

#include <greyimage.h>

enum  IMAGE_GEO_OP {IM_GEO_NONE, IM_GEO_REWRAP,
                    IM_GEO_TRANSLATE, IM_GEO_REFLECT,
                    IM_GEO_TILE, IM_GEO_CUT,
		    IM_GEO_MELLIN,
                    IM_GEO_ROTATE_PUSH,
                    IM_GEO_ROTATE_PULL,
                    IM_GEO_ROTATE_PULL_BILINEAR,
                    IM_GEO_ROTATE90, IM_GEO_TRANSPOSE};


extern GREYIM_PRODUCER gimage_transpose;
extern GREYIM *gimage_rotate(const GREYIM *, const double *,
                             const IMAGE_GEO_OP);
extern GREYIM *gimage_tile(const GREYIM *);
extern GREYIM_PRODUCER gimage_rotate90;
extern GREYIM_GENERATOR gimage_mellin;
extern GREYIM *gimage_pad(const GREYIM *, const int, const int, const double);
extern GREYIM *gimage_translate(const GREYIM *, const int, const int);
extern GREYIM *gimage_padto(const GREYIM *, const int, const int);
extern GREYIM *gimage_revrc(const GREYIM *, const int, const int);

extern GREYIM *gimage_subsample(const GREYIM *, const double *);

extern GREYIM *gimage_fuse(GREYIM *, const GREYIM *, const GREYIM *);

extern GREYIM *gimage_copy(const GREYIM *,
                        const int, const int, const int, const int,
                        const int, const int, const int, const int);
extern GREYIM *gimage_snip(const GREYIM *,
                        const int, const int, const int, const int);
extern void gimage_copy_checks(const int, const int, const int, const int,
                        const int, const int, const int, const int,
                        const int, const int);
extern GREYIM *gimage_copyto(const GREYIM *, GREYIM *,
                   const int, const int, const int, const int,
                   const int, const int);

extern GREYIM *gimage_opticalform_brute(const GREYIM *);

#endif
