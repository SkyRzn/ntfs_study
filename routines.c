#include "routines.h"
#include <stdio.h>


void dump(const unsigned char *data, int len)
{
	int i;
	char c;
	for (i = 0; i < len; i++) {
		printf("%02x ", data[i]);
		if (i > 0 && (i+1) % 8 == 0)
			printf("  ");
		if (i > 0 && (i+1) % 48 == 0)
			printf("\n");
	}
	printf("\n");
	for (i = 0; i < len; i++) {
		c = data[i];
		if (c < 32 || c > 127)
			c = '.';
		printf("%c  ", c);
		if (i > 0 && (i+1) % 8 == 0)
			printf("  ");
		if (i > 0 && (i+1) % 48 == 0)
			printf("\n");
	}
	printf("\n");
}

void print_utf8(uint16_t *data, int len)
{
	int i;
	for (i = 0; i < len; i++)
		printf("%lc", data[i]);
}

