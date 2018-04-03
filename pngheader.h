
#ifndef PNG_CUSTOM_H
#define PNG_CUSTOM_H

#include <stdio.h>
#include <inttypes.h>
#include "pngcrc.h"
#define HEADERLENGTH 37 //33: 8 sig + 4 len + 4 'IDHR' + 13 data + 4 crc

#define IHDRTYPE 0
#define IHDRWIDTH 4
#define IHDRHEIGHT 8
#define IHDRSETTINGS 12

struct pngContainer
{
	unsigned char signature[8];
	unsigned char IHDR[21]; // 4 + 4 + 13
	unsigned char settings[5];
	unsigned char crcIHDR[4];
	int length;
	int width;
	int height;
};
typedef struct pngContainer pngContainer;

unsigned char charArrayCompare(unsigned char *a, unsigned char *b, int length);
void headerRead(pngContainer *input, FILE *inputfp);
void arrayCopy(unsigned char *a, unsigned char *b, int length);
void bytePrint(unsigned char *a, int length);
void intToCharArray(unsigned char *array, int input);

#endif
