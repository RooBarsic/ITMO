# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <malloc.h>
# include <time.h>
# include "my_structs.h"

#ifndef MY_FUNCS_H
    #define MY_FUNCS_H

	void load_bmp(FILE* input_file, my_bmp_header* header, my_picture* img);
	void save_bmp(FILE* output_file, my_bmp_header* header, my_picture* img);
	my_picture* turn_right(my_picture* img);
	my_read_error_code read_from_file(char* input_file_name, my_bmp_header* header, my_picture* img);
	my_write_error_code write_to_file(char* output_file_name, my_picture* img);

#endif
