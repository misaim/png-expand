#ifndef PNG_CRC_H
#define PNG_CRC_H

#include "pngheader.h"

void make_crc_table(void);
unsigned long update_crc(unsigned long crc, unsigned char *buf, int len);
unsigned long crc(unsigned char *buf, int len);
unsigned long arrayToCRC(unsigned char *array);

#endif
