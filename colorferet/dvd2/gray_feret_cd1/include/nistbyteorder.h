#ifndef   QQ_BYTE_ORDER_H
#define   QQ_BYTE_ORDER_H

#include <netinet/in.h>
#if !defined(BYTE_ORDER) || !defined(BIG_ENDIAN)
#error "Architecture leaves BYTE_ORDER #undef-ined  after <netinet/in.h>"
#endif


typedef char ENDIANITY;
extern const ENDIANITY PAD_BIGEND;
extern const ENDIANITY PAD_LITTLEEND;
extern ENDIANITY getmachinebyteorder(void); 

void byteswap_2(void *, const int);
void byteswap_4(void *, const int);
void byteswap_8(void *, const int);

#endif // QQ_BYTE_ORDER_H
