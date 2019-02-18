# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <malloc.h>
# include <time.h>
# include "my_structs.h"
# include "my_funcs.h"
# include "my_funcs.c"


int main(){
    my_bmp_header* header1;
    my_picture* img1;
    header1 = malloc(sizeof(my_bmp_header));
    img1 = malloc(sizeof(my_picture));
    switch(read_from_file("./image/p.bmp", header1, img1)){
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
    
    switch(write_to_file("./image/res.bmp", img2)){
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
}

