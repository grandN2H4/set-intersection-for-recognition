#ifndef INCLUDED_GREYIM_DEFINITION
#define INCLUDED_GREYIM_DEFINITION	// allows derivative types to include
					// the required headers if they have not
					// been included already.
#include <ihead.h>
#include <string.h>

class GREYIM
{
   protected :
      int width;	// width of the image, say the "x" direction
      int height;	// height of the image, say the "y" direction
      int depth;	// depth of the image, say the "z" direction
			// which for 2D images is 1.

      int precision;	// the number of bits per pixel

      void *rasterdata;	// a pointer to plain old bytes
      IHEAD *header;	// a pointer to NIST old IHEAD header
      IMAGEDATATYPE thedatatype;	// a enumerated type flag.

   public :

      inline void *data() const { return rasterdata; }

      GREYIM() : width(0), height(0), depth(0), precision(0),
         rasterdata(0), header(0), thedatatype(IDATATYPE_NONE) {};

      GREYIM(const int, const int, const int, const IMAGEDATATYPE, const int = 0);
      GREYIM(const char *);
      GREYIM(const GREYIM &);
      GREYIM(const GREYIM *);
     ~GREYIM();

      inline int p() const { return precision; }
      inline int w() const { return width; }
      inline int h() const { return height; }
      inline int d() const { return depth; }
      inline int n() const { return width*height*depth; }
      inline IMAGEDATATYPE datatype() const { return thedatatype; }
      inline IHEAD *head() const { return header; }

      GREYIM &sethead(const IHEAD *);
      GREYIM &setdata(const void  *);
      GREYIM &setzero();
      GREYIM &read   (const char  *);
      GREYIM &write  (const char   *, const IM_COMPRESSION_CODE = UNCOMP);
      GREYIM &rewrap(const int, const int);

//    GREYIM &compress(const IM_COMPRESSION_CODE);
//    GREYIM &decompress();
};

#include <greyops.h>
#include <typecast.h>

extern GREYIM *gimage_sethead(GREYIM *, const IHEAD *);
extern GREYIM *gimage_read(const char *);
extern GREYIM *gimage_write(const char *, GREYIM *, const IM_COMPRESSION_CODE = UNCOMP);


extern GREYIM *gimage_mallocate(const IMAGEDATATYPE,
                                const int, const int, const int = 1);
extern GREYIM *gimage_allocate( const IMAGEDATATYPE,
                                const int, const int, const int = 1);
extern void gimage_free(GREYIM *);
extern GREYIM_PRODUCER gimage_dup;

extern double  gimage_pixbytes(const GREYIM *);
extern GREYIM_I_DESCRIPTOR gimage_pixbits;
extern GREYIM_I_DESCRIPTOR gimage_imagebytes;
extern GREYIM_I_DESCRIPTOR gimage_imagepixels;
extern GREYIM_I_DESCRIPTOR gimage_rowbytes;
extern GREYIM_I_DESCRIPTOR gimage_colbytes;

extern GREYIM *gimage_dump(const GREYIM *, const int);
extern GREYIM *gimage_bitmap(const GREYIM *, const int);

extern const GREYIM * gimage_congruent(const GREYIM *, const GREYIM *,
                                       const char * = "gimage_congruent");
extern const GREYIM * gimage_sameimage(const GREYIM *, const GREYIM *,
                                       const char * = "gimage_sameimage");
extern const GREYIM * gimage_samesize(const GREYIM *, const GREYIM *,
                                      const char * = "gimage_samesize");
extern const GREYIM * gimage_sametype(const GREYIM *, const GREYIM *,
                                      const char * = "gimage_sametype");
extern const GREYIM * gimage_superiortype(const GREYIM *, const GREYIM *,
                                      const char * = "gimage_superiortype");
extern const GREYIM * gimage_assertsquare(const GREYIM *,
                                      const char * = "gimage_assertsquare");

extern void gimage_badtype(const char *);

#endif
