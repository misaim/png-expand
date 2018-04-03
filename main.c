//Version: 001

#include <stdio.h>

#include "pngheader.h"
#include "pngcrc.h"

int main( int argc, char* args[] )
{
	int i = 0;

	pngContainer inputImage;

	make_crc_table();

	FILE *fp;
	fp = fopen("grass1.png", "rb");
	headerRead(&inputImage, fp);

	unsigned char header[4];
	fread(&header, 1, 4, fp);
	fread(&header, 1, 4, fp);
	printf("Next header: %c%c%c%c\n", header[0], header[1], header[2], header[3]);

	fclose(fp);

	return 0;
}
