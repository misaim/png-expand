#include "pngheader.h"

unsigned char charArrayCompare(unsigned char *a, unsigned char *b, int length)
{
	int i = 0;
	unsigned char output = 0;
	for (i = 0; i < length; i++)
	{
		if (a[i] != b[i])
		{
			output = 1;
			break;
		}
	}
	return output;
}

void headerRead(pngContainer *input, FILE *inputfp)
{
	unsigned char signature[] = {0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a};
	unsigned char window[8];
	unsigned char calculatedCRC[4];

	// File signature.
	fread(window, 1, 8, inputfp);
	if (!charArrayCompare(signature, window, 8))
	{
		printf("File Signature match!\n");
	}

	fread(window, 1, 4, inputfp);
	input->length = arrayToCRC(window);
	arrayCopy(window, input->IHDR, 4);

	fread(window, 1, 4, inputfp);
	arrayCopy(window, input->IHDR+IHDRTYPE, 4);

	fread(window, 1, 4, inputfp);
	input->width = arrayToCRC(window);
	arrayCopy(window, input->IHDR+IHDRWIDTH, 4);

	fread(window, 1, 4, inputfp);
	input->height = arrayToCRC(window);
	arrayCopy(window, input->IHDR+IHDRHEIGHT, 4);

	// Settings
	fread(window, 1, 5, inputfp);
	arrayCopy(window, input->IHDR+IHDRSETTINGS, 5);
	arrayCopy(window, input->settings, 5);

	//CRC
	fread(window, 1, 4, inputfp);
	arrayCopy(window, input->crcIHDR, 4);

	intToCharArray(calculatedCRC, crc(input->IHDR, 17));
	printf("CRC status (0 good): %d\n", charArrayCompare(calculatedCRC, input->crcIHDR, 4));

	printf("length: %d\n", input->length);
	printf("Width: %d\n", input->width);
	printf("height: %d\n", input->height);

}

void arrayCopy(unsigned char *a, unsigned char *b, int length)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		b[i] = a[i];
	}
	return;
}

void bytePrint(unsigned char *a, int length)
{
	printf("Printing %d raw bytes: \n", length);
	int i = 0;
	for (i = 0; i < length; i++)
	{
		printf("%02x ", a[i]);
	}
	printf("\n");
}

void intToCharArray(unsigned char *array, int input)
{
  array[0] = (input&0xff000000) >> 24;
  array[1] = (input&0x00ff0000) >> 16;
  array[2] = (input&0x0000ff00) >> 8;
  array[3] = (input&0x000000ff);

  return;
}
/*
unsigned char headerCheck(pngHeader inputHeader)
{
	unsigned char result = 0x00;
	if (inputHeader.fileSignature != 0x89504E470D0A1A0A)
	{
		result = result ^ 0b00000001;
		printf("Incorrect signature!\n");
	}
	if (inputHeader.lengthIHDR != 0x0D)
	{
		result = result ^ 0b00000010;
		printf("Incorrect IHDR - Should be 13 (0x0d), is %d\n", inputHeader);
	}
	if (inputHeader.depth != 0x08)
	{
		result = result ^ 0b00000100;
		printf("Incorrect color depth - requires 0x08.\n");
	}
	if (inputHeader.type != 0x06)
	{
		result = result ^ 0b00001000;
	}
	if (inputHeader.compression != 0x00)
	{
		result = result ^ 0b00010000;
	}
	if (inputHeader.filter != 0x00)
	{
		result = result ^ 0b00100000;
	}
	if (inputHeader.interlace != 0x00 && inputHeader.interlace != 0x01)
	{
		result = result ^ 0b01000000;
	}
	if (inputHeader.crcIHDR != 0x1FF3FF61)
	{
		result = result ^ 0b10000000;
	}
	return result;
}*/
