# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <malloc.h>
# include <time.h>
# include "my_structs.h"
# include "my_funcs.h"

my_picture* turn_right(my_picture* img){
	my_picture* new_img = malloc(sizeof(my_picture));
	new_img->width = img->height;
	new_img->height = img->width;
	new_img->data = malloc(sizeof(my_picture) * new_img->width * new_img->height);
	for(uint32_t i = 0; i < new_img->height; i++){
		for(uint32_t j = 0; j < new_img->width; j++){
			*(new_img->data + i*new_img->width + j) = *(img->data + j * img->width + (img->height - 1) - i);
		}
	}
	return new_img;
}

my_read_error_code read_from_file(char* input_file_name, my_bmp_header* header, my_picture* img){
	if(input_file_name == NULL) return READ_FILENAME_NULL;
	FILE* input_file = fopen(input_file_name, "rb");
	if(input_file == NULL) return READ_FILE_NOT_FOUND;
	
	fread(header, sizeof(my_bmp_header), 1, input_file);
	if(header->bfType == 0) {
		fclose(input_file);
		return READ_INVALID_HEADER;
	}
	
	if(header->biSizeImage == 0) header->biSizeImage = header->bfileSize;
	int padding = (4 - ((header->biWidth * sizeof(my_pixel)) % 4)) % 4;
	img->width = header->biWidth;
	img->height = header->biHeight;
	img->data = malloc((img->width * sizeof(my_pixel) + padding) * img->height);
	fseek(input_file, padding, SEEK_CUR);
	
	for(uint32_t i = 0; i < img->height; i++){
		fread(img->data + i * img->width, sizeof(my_pixel), img->width, input_file);
		fseek(input_file, padding, SEEK_CUR);
	}
	
	fclose(input_file);
	if(img->data == NULL) return READ_INVALID_BITS;
	return READ_OK;
}

my_write_error_code write_to_file(char* output_file_name, my_picture* img){
	if(img == NULL) return WRITE_IMAGE_NOT_FOUND;
	
	if(output_file_name == NULL) return WRITE_FILENAME_NULL;
	FILE* output_file = fopen(output_file_name, "wb");
	if(output_file == NULL) return WRITE_FILE_NOT_FOUND;
	
	int padding = (4 - ((img->width * sizeof(my_pixel)) % 4)) % 4;
	my_bmp_header* new_header = malloc(sizeof(my_bmp_header));
	new_header->bfType = 0x4D42;
	new_header->bfileSize = sizeof(my_bmp_header) + (img->width * sizeof(my_pixel) + padding)*img->height;	
	new_header->bfReserved = 0;
	new_header->bOffBits = sizeof(my_bmp_header);			
	new_header->biSize = 40;			
	new_header->biWidth = img->width;			
	new_header->biHeight = img->height;			
	new_header->biPlanes = 1;			
	new_header->biBitCount = 24;		
	new_header->biCompression = 0;		
	new_header->biSizeImage = (img->width* sizeof(my_pixel)  + padding)*img->height;		
	new_header->biXPelsPerMeter = 0;	
	new_header->biYPelsPerMeter = 0;	
	new_header->biClrUsed = 0; 			
	new_header->biClrImportant = 0;	
	fwrite(new_header, sizeof(my_bmp_header), 1, output_file);
    for (uint32_t i = 0; i < img->height; ++i) {
        fwrite(img->data + i*img->width, sizeof(my_pixel), img->width, output_file);
		fseek(output_file, padding, SEEK_CUR);
    }
    
    fclose(output_file);
    return WRITE_OK;
}
