#include	<stdio.h>
#include	<string.h>
#include 	<stdlib.h>
#include	<unistd.h>

#define BUF_SIZE 1024

void checkForWord(char* buf, const char* old, const char* new);

int main(int argc, char* argv[]){
	FILE*	file_in	 = fopen(argv[1], "r");
	FILE* 	file_out = fopen(argv[2], "w");
	
	// Array for words read in
	char	buffer[BUF_SIZE];
	
	// Variables to hold words to use in replacing
	char*	to_replace = "examine";
	char*	replace_with = "check";
	
	// If the file from the command line is wrong, exit this program.
	if (file_in == NULL) {
		printf("Error opening file.");
		exit(0);
	}
	
	fprintf(file_out,"%s", "This is the updated version.\n\n");
	
	// Get the files contents line by line
	while (fgets(buffer, BUF_SIZE, file_in) != NULL) {
		// Check the line for the word desired to be replaced
		checkForWord(buffer, to_replace, replace_with);
		// Write the correct line to new file
		fputs(buffer, file_out);
	}
	
	fclose(file_in);
	fclose(file_out);
	
	return 0;
}

void checkForWord(char* buf, const char* old, const char* new) {
	char* 	pos, temp[BUF_SIZE];
	int 	index = 0;
	int 	wordLength = strlen(old);
	
	// While loop incase the line has multiple occurences of the word
	 while ((pos = strstr(buf, old)) != NULL) {
		 // Copy the current line into the temporary array
		 strcpy(temp, buf);
		 // Finds the position of the old word
		 index = pos - buf;
		 // Deletes the the rest of the line
		 buf[index] = '\0';
		 // Concatenates the new word into the line
		 strcat(buf, new);
		 // Concatenates the rest of the line from the temporary array
		 strcat(buf, temp + index + wordLength);
	 }
	
}





















