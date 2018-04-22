#ifndef _NTFS_ROUTINES_H_
#define _NTFS_ROUTINES_H_


#include <stdint.h>


void dump(const unsigned char *data, int len);
void print_utf8(uint16_t *data, int len);


#endif

