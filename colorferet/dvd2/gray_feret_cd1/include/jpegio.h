#ifndef NIST_JPEG_WRAP_H
#define NIST_JPEG_WRAP_H

#include <rasterfile.h>
#include <ihead.h>

#define JPEG_JFIF_MAGIC -520103681	// taken from od -t d4 on a good
					// .jpg file on monaco Mar 23 2000

#ifdef OLD_ATEF_CODE
#define JPEG_JFIF_MAGIC 0xffd8ffe0	// taken from atef:/etc/magic
					// Jan 30 2000.
#endif

extern IHEAD *readjpegraster(const char *, void **);
extern void writejpegraster(const char *, const IHEAD *,
                         const void *, const char * = 0);
extern int isjpegrasterfile(const char *);

UCH *read_JPEG_file(const char *, int *, int *);


extern "C"
{
#include <jpeglib.h>
}

#endif
