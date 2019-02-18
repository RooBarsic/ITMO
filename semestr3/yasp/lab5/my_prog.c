# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <malloc.h>
# include <time.h>

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

void load_bmp(FILE* input_file, my_bmp_header* header, my_picture* img){
	fread(header, sizeof(my_bmp_header), 1, input_file);
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
}

void save_bmp(FILE* output_file, my_bmp_header* header, my_picture* img){
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
}
/**
 * my_bmp_header* new_header = malloc(sizeof(my_bmp_header));
new_header->bfType = 19778;
new_header->bfileSize = sizeof(my_bmp_header) + (img->width * sizeof(my_pixel) + padding)*img->height;	
new_header->bfReserved = 0;
new_header->bOffBits = 54;			
new_header->biSize = 40;			
new_header->biWidth = img->width;			
new_header->biHeight = img->height;			
new_header->biPlanes = 1;			
new_header->biBitCount 24;		
new_header->biCompression = 0;		
new_header->biSizeImage = (img->width* sizeof(my_pixel)  + padding)*img->height;		
new_header->biXPelsPerMeter = 0;	
new_header->biYPelsPerMeter = 0;	
new_header->biClrUsed = 0; 			
new_header->biClrImportant = 0;	


my_bmp_header* turn_header(my_bmp_header *header){
	my_bmp_header* new_header = (my_bmp_header*)malloc(sizeof(my_bmp_header));
	new_header->biHeight = header->biWidth;
	new_header->biWidth = header->biHeight;
	int padding = (4 - ((new_header->biWidth * sizeof(my_pixel)) % 4)) % 4;
	new_header->biSizeImage = ((new_header->biWidth + padding) * new_header->biHeight);
	new_header->bfileSize = sizeof(my_bmp_header) + new_header->biSizeImage;
	return new_header;
}
* */


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

int main(){
	//FILE* input_file;
    my_bmp_header* header1;
    my_picture* img1;
    //input_file = fopen("./images/p.bmp", "rb");
    header1 = malloc(sizeof(my_bmp_header));
    img1 = malloc(sizeof(my_picture));
    //load_bmp(input_file, header1, img1);
    //fclose(input_file);
    switch(read_from_file("./images/p.bmp", header1, img1)){
		case READ_OK : 
			printf("Изображение получено.\n");
			break;
		case READ_FILE_NOT_FOUND :
			printf("Файл не найден.\n");
			break;
		case READ_INVALID_BITS :
			printf("Странные данные.\n");
			break;
		case READ_INVALID_HEADER :
			printf("Странный заголовок.\n");
			break;
		case READ_FILENAME_NULL :
			printf("Переданно странное имя файла.\n");
			break;
	}
    
    my_picture* img2 = turn_right(img1);
    //my_bmp_header* header2 = turn_header(header1); 
    
    switch(write_to_file("./images/res.bmp", img2)){
		case WRITE_IMAGE_NOT_FOUND:
			printf("Изображение для записи не найдено.\n");
			break;
		case WRITE_OK : 
			printf("Изображение записано.\n");
			break;
		case WRITE_FILE_NOT_FOUND :
			printf("Файл не найден.\n");
			break;
		case WRITE_FILENAME_NULL :
			printf("Переданно странное имя файла.\n");
			break;
	}

    //FILE* output_file = fopen("./images/res.bmp", "wb");
    //pic_header = rotate_header(pic_header);
    //pic_config = rotate_right(pic_config);
    //save_bmp(output_file, header2, img2);
    //fclose(output_file);
}

