#ifndef IHEAD_H
#define IHEAD_H

#include <stdio.h>	// just to get the FILE type present
#include <iostream.h>
#include <nistbyteorder.h>
#include <imagetypes.h>

static const int IHDR_SIZE_FIELD_LEN = 8;
static const int IHDR_SIZE = 288;	// len of hdr record (always even bytes)
static const int SHORT_CHARS = 8;	// # of ASCII chars to represent a short
static const int BUFSIZE = 80;		// default buffer size
static const int DATELEN = 26;		// character length of date string
static const int IHD_MAGIC = IHDR_SIZE;

enum IM_COMPRESSION_CODE {UNCOMP=0, CCITT_G3=1, CCITT_G4=2,
                 LZW=3, RL_LZW=4, RL=5, JPEG=6, WSQ=7};

class IHEAD
{
public:
   IHEAD(FILE *);
   IHEAD(const char *);
   IHEAD(const IHEAD &);
   IHEAD() {};
  ~IHEAD() {};

   const IHEAD & write(FILE *) const;
   IHEAD & read(FILE *);

   IHEAD & set_id(const char *);
   IHEAD & set_created();
   IHEAD & set_width(const int);
   IHEAD & set_height(const int);
   IHEAD & set_depth(const int);
   IHEAD & set_density(const int);
   IHEAD & set_compression(const IM_COMPRESSION_CODE);
   IHEAD & set_complen(const int);
   IHEAD & set_align(const int);
   IHEAD & set_unitsize(const int);
   IHEAD & set_sigbit(const char);
   IHEAD & set_byte_order();
   IHEAD & set_byte_order(const char);
   IHEAD & set_pix_offset(const int);
   IHEAD & set_whitepix(const int);
   IHEAD & set_issigned(const int);
   IHEAD & set_rm_cm(const int);
   IHEAD & set_tb_bt(const int);
   IHEAD & set_lr_rl(const int);
   IHEAD & set_parent(const char *);
   IHEAD & set_par_x(const int);
   IHEAD & set_par_y(const int);
   IHEAD & set_datatype(const IMAGEDATATYPE);	// overwrite pix_offset
   IHEAD & set_complexpolarity(const COMPLEX_POLARITY &); // extend the pi_offset field

   char *get_id() const;
   char *get_created() const;
   char *get_parent() const;
   int get_width() const;
   int get_height() const;
   int get_depth() const;
   int get_density() const;
   IM_COMPRESSION_CODE get_compression() const;
   int get_complen() const;
   int get_align() const;
   int get_unitsize() const;
   int get_pix_offset() const;
   int get_whitepix() const;
   int get_issigned() const;
   int get_rm_cm() const;
   int get_tb_bt() const;
   int get_lr_rl() const;
   int get_par_x() const;
   int get_par_y() const;
   char get_sigbit() const;
   char get_byte_order() const;

   IMAGEDATATYPE get_datatype() const;	// peeks at pix_offset
   COMPLEX_POLARITY &get_complexpolarity() const; // peeks at extended pix_offset

   inline int get_precision() const
      { return datatype_pixbits(get_datatype()); }

   inline double get_bytesperpixel() const
      { return datatype_pixbytes(get_datatype()); }

   inline int get_numpixels()     const
      { return get_width() * get_height(); }
         // all ihead images are 2D, depth does not refer to
         // the "z" direction; it would be better named precision.

   inline int get_numbytes()      const
      { return sround((double)get_numpixels() * get_bytesperpixel()); }

   friend ostream & operator << (ostream &, const IHEAD &);

private:

   char id[BUFSIZE];			// identification/comment field
   char created[DATELEN];		// date created
   char width[SHORT_CHARS];		// pixel width of image
   char height[SHORT_CHARS];		// pixel height of image
   char depth[SHORT_CHARS];		// pixel depth of image
   char density[SHORT_CHARS];		// pixels per inch
   char compress[SHORT_CHARS];		// compression code
   char complen[SHORT_CHARS];		// compressed data length
   char align[SHORT_CHARS];		// scanline multiple: 8|16|32
   char unitsize[SHORT_CHARS];		// bit size of image memory units
   char sigbit;				// 0->sigbit first | 1->sigbit last
   char byte_order;			// 0->highlow | 1->lowhigh
   char pix_offset[SHORT_CHARS];	// pixel column offset
   char whitepix[SHORT_CHARS];		// intensity of white pixel
   char issigned;			// 0->unsigned data | 1->signed data
   char rm_cm;				// 0->row maj | 1->column maj
   char tb_bt;				// 0->top2bottom | 1->bottom2top
   char lr_rl;				// 0->left2right | 1->right2left
   char parent[BUFSIZE];		// parent image file
   char par_x[SHORT_CHARS];		// from x pixel in parent
   char par_y[SHORT_CHARS];		// from y pixel in parent
};

extern const char MSBF;
extern const char LSBF;
// extern const char HILOW;	// replaced by PAD_BIGEND and PAD_LITTLEEND
// extern const char LOWHI;	// in ../putil/*.c  ../../../include/utilities.h
extern const char UNSIGNED;
extern const char SIGNED;
extern const char ROW_MAJ;
extern const char COL_MAJ;
extern const char TOP2BOT;
extern const char BOT2TOP;
extern const char LEFT2RIGHT;
extern const char RIGHT2LEFT;

extern int	isiheadfile(const char *);
extern int	valid_compression(const int);
extern IHEAD   *readiheadraster( const char *, void **);
extern void	writeiheadraster(const char *, IHEAD *, const void *);
extern void	ihead_byteorder_prep(IHEAD &, void *);
extern char    *ihead_make_magic();

extern void ppbits2bytes(const UCH *, UCH *, const int);
extern void ppbytes2bits(const UCH *, UCH *, const int);

#endif
