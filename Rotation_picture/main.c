#include "rotateimg.h"

#pragma pack(push, 2)
typedef struct {
	
	char signature[2];
	int size;
	short emptyField1;
	short emptyField2;
	int data;
	int lengthHead;
	int width;
	int heidth;
	short countColorPlace;
	short bit;
	char methodArch[4];
	int lengthRastrMas;
	int gorisResolution;
	int vertResolution;
	int countColorPic;
	int countMainColor;
} bmp_header_t;

uint32_t comp( bmp_header_t* header )
{
	return ( 4 - (header->width*3 % 4))% 4;
}

pixel_t* bmp_pixel_at(bmp_header_t* header, char* data, uint32_t x, uint32_t y)
{
	return (pixel_t*)(data + (header->width*sizeof(pixel_t)+comp(header))*y + sizeof(pixel_t)*x);
}

image_t* image_read(FILE* file)
{
	bmp_header_t imgHead;

	fread_s(&imgHead, sizeof(bmp_header_t), 1, sizeof(bmp_header_t), file);
	if (imgHead.signature[0] == 'B' && imgHead.signature[1] == 'M' && imgHead.bit == 24 )
	{
		char *writeto, *stopat;
		image_t* imStruct = (image_t*)malloc(sizeof(image_t));
		imStruct->data = (char*)malloc( imgHead.width*imgHead.heidth*3*sizeof(char));
		stopat = imStruct->data + imgHead.width*imgHead.heidth*3*sizeof(char);
		fseek(file, imgHead.data, SEEK_SET);
		for( writeto = imStruct->data; writeto < stopat; writeto += imgHead.width )
		{
			fread_s( writeto, sizeof(char)*3*imgHead.width*imgHead.heidth, 1, sizeof(char)*3*imgHead.width*imgHead.heidth, file );
			fseek( file, comp(&imgHead), SEEK_CUR );
		}
		imStruct->descr.width = imgHead.width;
		imStruct->descr.height = imgHead.heidth;
		return imStruct;
	}
	else return NULL;
}

void image_write(FILE* file, image_t* image)
{
	uint32_t x, y;
	pixel_t* pixel;
	char* ndata;
	
	uint32_t comp = ( 4 - (image->descr.width*3 % 4))% 4;
	bmp_header_t imgHead = { 
		{'B', 'M'} , 
		sizeof(bmp_header_t)+image->descr.width*image->descr.height*3 + comp*image->descr.height, 
		0, 
		0, 
		sizeof(bmp_header_t), 
		40, 
		image->descr.width, 
		image->descr.height, 
		1, 
		24, 
		{0,0,0,0}, 
		36720, 
		3780, 
		3780, 
		0,
		0 
	};

	ndata = (char*)malloc((3*image->descr.width + comp)*image->descr.height*sizeof(char));
	for( y = 0; y < image->descr.height; y++ )
	{
		for( x = 0; x < image->descr.width; x++ )
		{
			*bmp_pixel_at( &imgHead, ndata, x, y) = *pixelAt(image,x,y);
		}
	}

	fwrite(&imgHead, sizeof(char)* 54, 1, file);
	fseek(file, imgHead.data, SEEK_SET);
	fwrite(ndata, sizeof(char)* ((3 * image->descr.width * image->descr.height) + (comp*image->descr.height)), 1, file);
}

int main()
{
	FILE* in;
	FILE* out;
	image_t* image;
	image_t* nimage;
	char fname[20];
	int angle;

	if ((fopen_s(&in, "1.bmp", "rb")) != 0)
	{
		perror("1.bmp");
		return -10;
	}

	printf("Input angle: ");
	scanf("%d", &angle);
	sprintf( fname, "1_%d.bmp", angle );

	if ((fopen_s(&out, fname, "wb")) != 0)
	{
		perror(fname);
		return -5;
	}

	image = image_read(in);

	if( !image )
	{
		fprintf(stderr, "Not a valid image");
		return -2;
	}

	nimage = rotate( image, angle );
	image_write( out, nimage );

	return 0;
}
