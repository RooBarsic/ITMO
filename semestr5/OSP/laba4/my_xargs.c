#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_SIZE 256
#define MAX_RESULT_SIZE 1024

int main(int argc, char *argv[]) {
	char* command = (char*)malloc(MAX_COMMAND_SIZE * sizeof(char));
	char* arguments = (char*)malloc(MAX_COMMAND_SIZE * sizeof(char));
	for (int i = 1; i < argc; i++) {
		strcat(command, argv[i]);
		strcat(command, " ");
	}
	while (scanf("%s", arguments) != EOF) {
		char* result = (char*)malloc(MAX_RESULT_SIZE * sizeof(char));
		strcpy(result, command);
		strcat(result, " ");
		strcat(result, arguments);
		system(result);
	}
	return EXIT_SUCCESS;
}
