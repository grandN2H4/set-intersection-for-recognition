#ifndef GREYARITH_H
#define GREYARITH_H

#include <greyimage.h>

enum POWOP {POW_NO_OP, POW_DIVSUM, POW_UP, POW_ALOGXB, POW_ALOGBX,
            POW_AX_B, POW_AEXPBX,
            POW_ADDMODROW, POW_AEXPBI, POW_ADDMOD,
            POW_SIG, POW_SIGINV};

enum LINEFUNC {LINE_BAD, LINE_MAXI, LINE_MINI, LINE_STDV,
               LINE_MEDIAN, LINE_MEAN, LINE_SUM, LINE_BIMEAN};

extern GREYIM_MASKEDOPERATOR gimage_subto;
extern GREYIM_MASKEDOPERATOR gimage_addto;
extern GREYIM_MASKEDOPERATOR gimage_divto;
extern GREYIM_MASKEDOPERATOR gimage_multo;

extern GREYIM_MASKEDOPANDGEN gimage_add;
extern GREYIM_MASKEDOPANDGEN gimage_sub;
extern GREYIM_MASKEDOPANDGEN gimage_div;
extern GREYIM_MASKEDOPANDGEN gimage_mul;

extern GREYIM *gimage_scalf(GREYIM *, const double);
extern GREYIM *gimage_addf(GREYIM *, const double);
extern GREYIM *gimage_fixrowsmean(GREYIM *, const double);
extern GREYIM *gimage_fixcolsmean(GREYIM *, const double);

extern GREYIM_ADJUSTOR gimage_fixtwosigma;

// extern GREYIM_OPERATOR gimage_applymask;
// extern GREYIM_OPERATOR gimage_applybinarymask;
extern GREYIM *gimage_applymask(GREYIM *, const GREYIM *, const int = 0);
extern GREYIM *gimage_applybinarymask(GREYIM *, const GREYIM *, const int = 0);
extern GREYIM_OPERATOR gimage_applyfloatingmask;

extern GREYIM_COMPARATOR gimage_nsr; /* ie -SNR */
extern GREYIM_COMPARATOR gimage_snr; /* ie +SNR */
extern GREYIM_COMPARATOR gimage_mse;
extern GREYIM_COMPARATOR gimage_mae;

extern GREYIM_COMPARATOR gimage_dot;

extern void gimage_bimean(const GREYIM *, const GREYIM *, double *, double *);
extern void gimage_stats(const char *, const GREYIM *,
                         const GREYIM * = 0);
extern void gimage_mvr(const GREYIM *, double &, double &, double &,
                       const GREYIM * = 0);

extern GREYIM_UNARYOP gimage_revvideo;
extern GREYIM_UNARYOP gimage_quant6bit;
extern GREYIM * gimage_quant_n_bit(GREYIM *, const int = 6);

extern GREYIM_D_DESCRIPTOR gimage_mean;
extern GREYIM_D_DESCRIPTOR gimage_vari;
extern GREYIM_D_DESCRIPTOR gimage_rms;
extern GREYIM_D_DESCRIPTOR gimage_sumv2;
extern GREYIM_D_DESCRIPTOR gimage_sumv;
extern GREYIM_D_DESCRIPTOR gimage_median;
extern GREYIM_D_DESCRIPTOR gimage_mode;
extern GREYIM_D_DESCRIPTOR gimage_entropy;

extern GREYIM_ROWCOLOP gimage_bimeanrow;
extern GREYIM_ROWCOLOP gimage_bimeancol;
extern GREYIM_ROWCOLOP gimage_stdvonerow;
extern GREYIM_ROWCOLOP gimage_stdvonecol;
extern GREYIM_ROWCOLOP gimage_sumonerow;
extern GREYIM_ROWCOLOP gimage_sumonecol;
extern GREYIM_ROWCOLOP gimage_medonecol;
extern GREYIM_ROWCOLOP gimage_medonerow;
extern GREYIM_ROWCOLOP gimage_maxonerow;
extern GREYIM_ROWCOLOP gimage_maxonecol;
extern GREYIM_ROWCOLOP gimage_minonerow;
extern GREYIM_ROWCOLOP gimage_minonecol;
extern GREYIM_ROWCOLOP gimage_meanonerow;
extern GREYIM_ROWCOLOP gimage_meanonecol;

extern GREYIM_GENERATOR gimage_add_modulo;
extern GREYIM_GENERATOR gimage_add_modulo_row;
extern GREYIM_GENERATOR gimage_sigmoid;
extern GREYIM_GENERATOR gimage_sigmoid_inv;

extern GREYIM *gimage_pow_transform(const GREYIM *, const POWOP,
                                    const double, const double);

typedef double (PIXEL_OPFUNC)(double);
extern GREYIM *gimage_mathop(GREYIM *, PIXEL_OPFUNC, const GREYIM * = 0);
extern GREYIM *gimage_blend(GREYIM *, const GREYIM *, const GREYIM *);

enum GRADKIND {GRAD_FWD_DIFF, GRAD_BKWD_DIFF, GRAD_CENT_DIFF};
extern GREYIM *gimage_grad_x(const GREYIM *, const GRADKIND);
extern GREYIM *gimage_grad_y(const GREYIM *, const GRADKIND);

#endif
