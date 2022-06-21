#ifndef UTIL_INC
#define UTIL_INC


#include <stdio.h>
#include <getopt.h>
#include <mfs.h>

extern FILE *fopen_or_exit(const char *, const char *,
                           const char * = 0);

// global variable, define in and usually set in "putil/argstonames.c"
// the argument parsing routine (usually called "procargs"), and used
// by any program that emits a file that has the capacity to store the
// command line that generated that file.
extern char *thecommandline;
extern char *extract_commandline(const int, char * const *);

extern void fatalerr(const char *, const char *, const char *);
extern void syserr(const char *, const char *, const char *);
extern int exeunt(const char *);
extern char *utempname(const char *);
extern int pjg_filesize(FILE *);

extern char *strconc(const char *, const char *);
extern char *newextlong(char **, const char *);
extern char *current_time(void);
extern void report_time(const char *);
extern void report_time_estimate(const char *, const double);

extern int *sortuniq(const int *, const int, int *);

extern char *str_rm_path(const char *);
extern void strfree(char *);

extern char *strmake(const double, const char *);
extern char *strmake(const float, const char *);
extern char *strmake(const int, const char *);
extern char *strmake(const char *, const int, const int, const int);

extern char * strscans(const char *);
extern double strscand(const char *);
extern float  strscanf(const char *);
extern int    strscani(const char *);




FILE *fopen_with_error(	const char *, const char *, const char *);
FILE *fopen_anycase(	const char *, const char *, const char *, const int = 1);

char *file_exists(	const char *, const char *, const char *, const char *);
char *change_extension(	const char *, const char *);

char **read_strings(const char *, int *);
void free_strings(char **, const int);


// clone a string, exactly like strdup (which is not ANSI C)
char *strclone(const char *);

// return true if needle is in the haystack
int strcontains(const char *haystack, const char *needle);
// return true if needle is NOT in the haystack
int strexcludes(const char *haystack, const char *needle);

// return true if strings are not the same
int strdiff(const char *one, const char *two);
// return true if strings are not the same in the first n chars
int strndiff(const char *one, const char *two, const int n);

// return true if strings are not the same, ignoring case
int strcasediff(const char *one, const char *two);
// return true if strings are identical
int strsame(const char *one, const char *two);
// return true if strings are identical up to the period (if any)
int strcasesame_to_period(const char *one, const char *two);

// concatenate dir + delim + filename into malloced string
char *stradddir(const char *directory, const char *delimiter, const char *tailname);
// remove  dir + delim from pathname/filename into malloced string
char *strsubdir(const char *directory, const char *delimiter = 0);
// force the input string to lower or upper case in place
char *strlower(char *);
char *strupper(char *);
// test for null arguments
void strnullchecks(const char *, const char *, const char *, const int = 61);
// exit if the supplied string does not have the supplied length
void strassertlength(const char *, const int);

#endif
