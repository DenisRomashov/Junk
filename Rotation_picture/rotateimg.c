#include "rotateimg.h"

int round( double x )
{
	int tmp = (int)x;
	if( x - tmp >= 0.5 ) tmp++;
	return tmp;
}

pixel_t* pixelAt(image_t* image, uint32_t x, uint32_t y)
{
	return (pixel_t*)( image->data + 3*y*image->descr.width + 3*x );
}

uint32_t get_angle_0_to_360( int32_t angle )
{
	if( angle < 0 ) angle += ( -angle / 360 + 1 ) * 360;
	else if( angle > 359 ) angle %= 360;
	return angle;
}

image_descr_t get_new_descr( image_descr_t descr, uint32_t angle )
{
	image_descr_t temp;
	angle = ( angle <= 180 ) ? ( angle % 180 ) : abs( (int)angle - 360 );
	if( angle > 90 ) angle = 180 - angle;
	temp.width = round(2*(sqrt(pow((double)descr.width,2) + pow((double)descr.height, 2 )) / 2 * sin( atan( (double)descr.width / descr.height ) + angle * M_PI/180.0 ) )); 
	temp.height = round(2*(sqrt(pow( (double)descr.width, 2 ) + pow( (double)descr.height, 2 )) / 2 * sin( atan( (double)descr.height / descr.width ) + angle * M_PI/180.0 ) ));
	return temp;
}

image_t* image_create( image_descr_t descr )
{
	image_t* temp = (image_t*)malloc(sizeof(image_t));
	temp->descr = descr;
	temp->data = (char *)malloc( 3*descr.width*descr.height*sizeof(char) );
	return temp;
}

pixel_t* find_match( image_t* prev, image_descr_t next, uint32_t angle, int32_t x, int32_t y )
{
	double OB = sqrt( pow(next.width/2.0-x,2) + pow(next.height/2.0-y, 2));
	double OH = next.width/2.0 - x;
	double aBOH = (OB != 0) ? acos(abs(OH)/OB) : 0;
	double dx = (next.width - prev->descr.width) / 2.0;
	double dy = (next.height - prev->descr.height) / 2.0;
	int newX, newY;
	if(((y>=next.height/2.0) && (x<next.width/2.0)) || ((y<next.height/2.0) && (x>=next.width/2.0))) aBOH = -aBOH;
	if( OH > 0 )
	{
		newX = round( next.width/2.0 - cos(aBOH + angle*M_PI/180)*OB - dx );
		newY = round( next.height/2.0 - sin(aBOH + angle*M_PI/180)*OB - dy );
	}
	else
	{
		newX = round( next.width/2.0 - cos(aBOH + angle*M_PI/180+M_PI)*OB - dx );
		newY = round( next.height/2.0 - sin(aBOH + angle*M_PI/180+M_PI)*OB - dy );
	}

	if( (newX >= 0) && (newY >= 0 ) && (newX < prev->descr.width) && (newY < prev->descr.height) )
		return pixelAt( prev, newX, newY );
	else 
		return NULL;
}

image_t* rotate( image_t* image, int32_t angle )
{
	uint32_t x, y;
	image_t* result;
	pixel_t* pixel;
	pixel_t* npixel;
	angle = get_angle_0_to_360( angle );
	result = image_create(get_new_descr(image->descr, angle));
	for( x = 0; x < result->descr.width; x++ )
	{
		for( y = 0; y < result->descr.height; y++ )
		{
			npixel = pixelAt( result, x, y );
			pixel = find_match( image, result->descr, angle, x, y );
			if( pixel ) *npixel = *pixel; else *npixel = bg_pixel;
		}
	}
	return result;
}
