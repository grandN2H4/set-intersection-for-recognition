#ifndef MFS_H
#define MFS_H

#include <iostream.h>
#include <fstream.h>

class MFS
{
   private :

      int numin;
      int alloc;
      char **values;

      MFS & more(const int);
      MFS & init(const int, const char * const *);

   public :

      MFS() : numin(0), alloc(0), values(0) {};
      MFS(const MFS &);
      MFS(const int);
      MFS(const int, const char *const *);
      MFS(const char *);
     ~MFS();

      MFS & free();
      MFS & write(const char *);
      MFS & write(ostream &);

      inline int num() const { return numin; }
      inline int maxin() const { return alloc; }
      inline int isfull()  const { return numin >= alloc; }
      inline int isempty() const { return alloc == 0; }
      inline char * operator [] (const int ii) const { return values[ii]; }
      inline char *&operator [] (const int ii)       { return values[ii]; }
//    inline char *&operator () (const int ii)       { return values[ii]; }

      char *operator += (const char *);
      MFS  &operator += (const MFS  &);
      MFS  &operator  = (const MFS  &);
};

extern MFS &argstonames(const int, char * const *, const int, const int = 1);
extern MFS &pastemfs(MFS * const *, const int);
extern MFS &readmfsfile(const char *);

#endif // MFS_H
