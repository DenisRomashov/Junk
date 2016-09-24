#ifndef _ROTATEIMG_
#define _ROTATEIMG_

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdint.h>

typedef struct {
	uint32_t width;
	uint32_t height;
} image_descr_t;

typedef struct {
	image_descr_t descr;
	char* data;
} image_t;

typedef struct {
	char r;
	char g;
	char b;
} pixel_t;

const pixel_t bg_pixel = { 255, 255, 255 };

int round( double x );

image_t* image_read(FILE* file);
void image_write(FILE* file, image_t* image);

pixel_t* pixelAt(image_t* image, uint32_t x, uint32_t y);

uint32_t get_angle_0_to_360( int32_t angle );
image_descr_t get_new_descr( image_descr_t descr, uint32_t angle );
image_t* image_create( image_descr_t descr );
pixel_t* find_match( image_t* prev, image_descr_t next, uint32_t angle );
image_t* rotate( image_t* image, int32_t angle );

#endif
