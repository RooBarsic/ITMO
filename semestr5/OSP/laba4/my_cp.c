#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFF_SIZE 1024 
#define OK 1
#define WRONG_KEY 2
#define NOT_KEY 3
#define CREATING_MODE 4
#define APPENDING_MODE 5

int V_FLAG = 0, N_FLAG = 0, H_FLAG = 0;

int checkKey(char *arg, char key){
	int len = strlen(arg);
	if((len == 2) && (arg[0] == '-')){
		if(arg[1] == key){
			return OK;
		}
		else {
			return WRONG_KEY;
		}
	}
	if((len > 0) && (arg[0] == '-')){
		return WRONG_KEY;
	}
	return NOT_KEY;
}

void printHelp(){
	printf("=================  Name  ===================== \n");
    printf("cp - Use this command to copy files \n");
    printf("================= Syntax  ==================== \n");
    printf("cp [-vn ] [source_file1 ...] [target_file] \n");
    printf("================= Keys  ====================== \n");
    printf("-n -- do not rewrite target file if it's exist. \n");
    printf("-v -- show comments during the process (verbose mode). \n");
    printf("-h -- help \n");
    printf("============================================== \n \n");
}

void closeTargetFile(int targetFile, char *filename) {
	errno = 0;
	if (close(targetFile) == -1) {
		write(1, filename, strlen(filename));
		write(1, ": ", strlen(": "));
		if (errno != 0) {
			write(1, strerror(errno), strlen(strerror(errno)));
			write(1, "\n", strlen("\n"));
		}
	}
	if (V_FLAG == 1){
		write(1, "*done\n", strlen("*done\n"));
	}
}

unsigned int getFileSize(int file) {
	unsigned int sz = 0;
	struct stat buf;
	fstat(file, &buf);
	sz = buf.st_size;
	return sz;
}

int openTargetFile(char *filename, int mode) {
	int targetFile, createdFlags;
	errno = 0;
	if (access(filename, F_OK) != -1 && N_FLAG == 1) {
		write(1, filename, strlen(filename));
		write(1, ": File exists (consider removing -n key)\n",
		strlen(": File exists (consider removing -n key)\n"));
		exit(EXIT_FAILURE);
	} else {
		if (mode == CREATING_MODE){
			createdFlags = O_WRONLY | O_APPEND | O_CREAT | O_TRUNC;
		} else {
			createdFlags = O_WRONLY | O_APPEND | O_CREAT;
		}
		targetFile = open(filename, createdFlags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		errno = 0;
		if (targetFile == -1) {
			write(1, filename, strlen(filename));
			write(1, ": ", strlen(": "));
			if (errno != 0) {
				write(1, strerror(errno), strlen(strerror(errno)));
				write(1, "\n", strlen("\n"));
			}
			exit(EXIT_FAILURE);
		}
	}
	return targetFile;
}

int checkSrt(char *str, char *mask){
	int str_len = strlen(str);
	int mask_len = strlen(mask);
	int a = 0, b = 0;
	while((a < str_len) && (b < mask_len)){
		if(str[a] != mask[b]){
			return 0;
		}
		a++;
		b++;
	}
	return 1;
}

void cpFromStdin(char *fileName, int mode) {
	int kolButes;
	char *buff = (char *) malloc(BUFF_SIZE * sizeof(char));
	int targetFile = openTargetFile(fileName, mode);
	while ((kolButes = read(STDIN_FILENO, buff, BUFF_SIZE)) > 0) {
		if(checkSrt(buff, "finish") == 1){
			break;
		}
		errno = 0;
		if (write(targetFile, buff, kolButes) != kolButes) {
			write(1, fileName, strlen(fileName));
			write(1, ": ", strlen(": "));
			if (errno != 0) {
				write(1, strerror(errno), strlen(strerror(errno)));
				write(1, "\n", strlen("\n"));
			}
			exit(EXIT_FAILURE);
		}
	}
	closeTargetFile(targetFile, fileName);
}

int readFile(char *filename) {
	int file;
	errno = 0;
	file = open(filename, O_RDONLY);
	if (file == -1) {
		write(1, filename, strlen(filename));
		write(1, ": ", strlen(": "));
		if (errno != 0) {
			write(1, strerror(errno), strlen(strerror(errno)));
			write(1, "\n", strlen("\n"));
		}
		exit(EXIT_FAILURE);
	}
	if (V_FLAG == 1) {
		write(1, filename, strlen(filename));
		write(1, ": *copying to targetFile file\n", strlen(": *copying to destination file\n"));
	}
	return file;
} 

void cpFromFile(char *inputFileName, char *targetFileName, int mode) {
	char *buffer = (char *) malloc(BUFF_SIZE * sizeof(char));
	int inputFile = readFile(inputFileName);
	int fileSize = getFileSize(inputFile);
	int targetFile = openTargetFile(targetFileName, mode);
	errno = 0;
	if (read(inputFile, buffer, BUFF_SIZE) != fileSize) {
		write(1, inputFileName, strlen(inputFileName));
		write(1, ": ", strlen(": "));
		if (errno != 0) {
			write(1, strerror(errno), strlen(strerror(errno)));
			write(1, "\n", strlen("\n"));
		}
		exit(EXIT_FAILURE);
	}
	if (write(targetFile, buffer, fileSize) != fileSize) {
		write(1, targetFileName, strlen(targetFileName));
		write(1, ": ", strlen(": "));
		if (errno != 0) {
			write(1, strerror(errno), strlen(strerror(errno)));
			write(1, "\n", strlen("\n"));
		}
		exit(EXIT_FAILURE);
	}
	errno = 0;
	if (close(inputFile) == -1) {
		write(1, inputFileName, strlen(inputFileName));
		write(1, ": ", strlen(": "));
		if (errno != 0) {
			write(1, strerror(errno), strlen(strerror(errno)));
			write(1, "\n", strlen("\n"));
		}
	}
	closeTargetFile(targetFile, targetFileName);
} 

int main(int argc, char** argv){
	int iter = 1;
	while(iter < argc){
		//int len = strlen(argv[iter]);
		//printf(" iter = %i %s len = %i \n", iter, argv[iter], len);
		if(checkKey(argv[iter], 'v') == OK){
			V_FLAG = 1;
		}
		else if(checkKey(argv[iter], 'n') == OK){
			N_FLAG = 1;
		}
		else if(checkKey(argv[iter], 'h') == OK){
			H_FLAG = 1;
		}
		else if(checkKey(argv[iter], 'v') == WRONG_KEY){
			int len = strlen(argv[iter]);
			for(int i = 1; i < len; i++){
				write(1, "cp: illegal option --", strlen("cp: illegal option --"));
				write(1, argv[iter] + i, 1);
				write(1, " \n", strlen(" \n"));
			}
			printHelp();
			exit(EXIT_FAILURE);			
		}
		else {
			break;
		}
		iter++;
	}
	//printf(" v = %i n = %i h = %i iter = %i argc = %i \n", V_FLAG, N_FLAG, H_FLAG, iter, argc); 
	
	if(H_FLAG == 1){
		printHelp();
	}
	else if(iter + 1 <= argc){
		char* targetFileName = argv[argc - 1];
		if((N_FLAG == 1) && (access(targetFileName, F_OK) != -1)){
				write(1, targetFileName, strlen(targetFileName));
				write(1, ": File exists (consider removing -n key)\n", strlen(": File exists (consider removing -n key)\n"));
				exit(EXIT_FAILURE);
		}
		int mode = CREATING_MODE;
		for(int i = iter; i + 1 < argc; i++){
			//printf(" str = %s \n", argv[i]);
			int len = strlen(argv[i]);
			if((len == 1) && (argv[i][0] == '-')){
			}
			else {
				if(!access(argv[i], 0)){
					write(1, "cp: cannot access ", strlen("cp: cannot access "));
					write(1, argv[i], strlen(argv[i]));
					write(1, "\n", strlen("\n"));
					exit(EXIT_FAILURE);										
				}
				if(access(argv[i], 3) == -1){
					write(1, argv[i], strlen(argv[i]));
					write(1, ": Permission denied", strlen(": Permission denied"));
					write(1, "\n", strlen("\n"));
					exit(EXIT_FAILURE);					
				}
			}
		}
		for(int i = iter; i + 1 < argc; i++){
			//printf(" str = %s \n", argv[i]);
			int len = strlen(argv[i]);
			if((len == 1) && (argv[i][0] == '-')){
				cpFromStdin(targetFileName, mode);
			}
			else {
				cpFromFile(argv[i], targetFileName, mode);
			}
			mode = APPENDING_MODE;
		}
		exit(EXIT_SUCCESS);
	}
	else {
		printHelp();
		write(1, "Wrong command arguments \n", strlen("Wrong command arguments \n"));
		exit(EXIT_FAILURE);
	}
	
}
