#include "stdio.h"
#include "stdlib.h"

#define IMG_MAX_SIZE 1000


int checkImg(FILE* img);
int verifyChecksum(FILE* fp, int size, int checksum);
int createChecksum(char* byteptr, int size);

typedef struct _IMG_HEADER
{
	int length;
	int width;
	int checksum;
}IMG_HEADER;


int main(int argc, char* args[])
{
	FILE* img = NULL;
	char path[20];
	
	printf("Welcome to bmp validator\n");
	printf("Which picture should be validated? ");
	scanf("%19s", path);

	img = fopen(path, "rb");
	if(img == NULL)
	{
		printf("Failed to open picture\n");
		return -1;
	}
	
	if(checkImg(img))
		printf("Checksum successfully verified\n");
	else
		printf("Checksum corrupted\n");

	return fclose(img);
}


int checkImg(FILE* img)
{
	IMG_HEADER hdr;
	int size = 0;

	if(fread(&hdr, 1, sizeof(hdr), img) != sizeof(hdr))
		return 0;
		
	size = hdr.length * hdr.width;

	//limit max size	
	if(size > IMG_MAX_SIZE)
		return 0;

	//negative size (or smaller than IMG_HEADER) makes no sense
	if(size < sizeof(IMG_HEADER))
		return 0;
	
	return verifyChecksum(img, size, hdr.checksum);
}


int verifyChecksum(FILE* fp, int size, int checksum)
{
	unsigned char grafic[IMG_MAX_SIZE];

	int i = fread(grafic, 1, size, fp);

	return checksum == createChecksum(grafic, i);
}


int createChecksum(char* byteptr, int size)
{
	int i;
	int sum = 0;

	for(i = 0; i < size; i++)
	{
		sum += byteptr[i];

		if(i % 3)
			sum *= byteptr[i];
		if(i % 4)
			sum += byteptr[i];
		if(i % 5)
			sum ^= byteptr[i];
	}

	return sum;
}
