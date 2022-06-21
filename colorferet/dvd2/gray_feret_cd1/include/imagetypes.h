#ifndef INCLUDED_IM_TYPES
#define INCLUDED_IM_TYPES

#include <comppad.h>
#include <defs.h>

enum IM_FILE_FORMAT {IM_NONE, IM_SUNRASTER,
                     IM_NIST_IHEAD, IM_MS_BITMAP};


class IHEAD; // forward declaration

typedef IHEAD * (RASTERREADER)(const char *, void **);
typedef void    (RASTERWRITER)(const char *, IHEAD *,
                               const void *, const char * = 0,
                               const IM_FILE_FORMAT = IM_NIST_IHEAD);

extern RASTERREADER readraster;
extern RASTERWRITER writeraster;

const int imagetypes_num_supported_types = 8;

enum IMAGEDATATYPE {IDATATYPE_NONE, IDATATYPE_BINARY, IDATATYPE_UC,
                    IDATATYPE_SHORT, IDATATYPE_INT, IDATATYPE_FLOAT,
                    IDATATYPE_COMPLEX, IDATATYPE_DOUBLE};

extern const char *image_typestrings[imagetypes_num_supported_types];
extern const char *image_typecodes[imagetypes_num_supported_types];



extern IMAGEDATATYPE scantypestring(const char *);

extern double	datatype_pixbytes(const IMAGEDATATYPE);
extern int	datatype_pixbits(const IMAGEDATATYPE);

extern void imagetypes_badtype(const char *);

#endif
