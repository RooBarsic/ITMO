# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <malloc.h>
# include <time.h>

#ifndef MY_STRUCTS_H
    #define MY_STRUCTS_H


struct _pixel {
	unsigned char b, g, r;
};
typedef struct _pixel my_pixel;

struct _picture{
	uint32_t width;
	uint32_t height;
	my_pixel *data;
};
typedef struct _picture my_picture;

struct __attribute__((packed)) _bmp_header{
	uint16_t bfType;            // - type 2 byte simvoli BM
	uint32_t bfileSize;			// - 4 byte file.size
	uint32_t bfReserved;		// - 4 byte reserved for smth
	uint32_t bOffBits;			// - 4 byte smeshenie ot nachala faila do image
	uint32_t biSize;			// - 4 byte razmer strukturi d byte
	uint32_t biWidth;			// - width
	uint32_t biHeight;			// - height
	uint16_t biPlanes;			// - 2 byte alwaus 1
	uint16_t biBitCount;		// - 2 byte - number bits/pixel
	uint32_t biCompression;		// - 4 byte - type of compression for image
	uint32_t biSizeImage;		// - 4 byte - image size in bytes
	uint32_t biXPelsPerMeter;	// - 4 byte - x info for devise
	uint32_t biYPelsPerMeter;	// - 4 byte - y info for device
	uint32_t biClrUsed;			// - 4 byte - number of colour index
	uint32_t biClrImportant;	// - 4 byte - number of index for printing image
};
typedef struct _bmp_header my_bmp_header;

typedef enum {
    READ_OK = 0,
    READ_FILE_NOT_FOUND,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_FILENAME_NULL
} my_read_error_code;

typedef enum {
    WRITE_OK = 0,
    WRITE_IMAGE_NOT_FOUND,
    WRITE_FILE_NOT_FOUND,
    WRITE_FILENAME_NULL
} my_write_error_code;

#endif
