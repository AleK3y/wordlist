#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *alloc_str(int length) {
	/*
	 Allocate a string and return its address.
	*/

	return malloc((length+1) * sizeof(char));
}

char *repeat(char sym, int times) {
	/*
	 Create a string made of `sym`s and long `times`.
	*/

	char *concat = alloc_str(times);
	for(int i=0; i<times; i++) {
		concat[i] = sym;
	}
	concat[times] = '\0';		// Set the EOL for the string

	return concat;
}

int index_of(char *arr, char item) {
	/*
	 Find the index of the `item` character.
	*/

	for(int i=0; i<strlen(arr); i++) {
		if(arr[i] == item) {
			return i;
		}
	}
}

void next_sequence(char *string, char *charlist) {
	/*
	 Update `string` with the next character on `charlist`.
	*/

	// Find the position of the first (starting from right) increasable character
	int to_inc;
	for(to_inc=strlen(string)-1; string[to_inc] == charlist[strlen(charlist)-1]; to_inc--);

	// Increase the character at its position
	string[to_inc] = charlist[index_of(charlist, string[to_inc])+1];

	// Set the remaining as the first of the character list
	for(int j=to_inc+1; j<strlen(string); j++) {
		string[j] = charlist[0];
	}
}

bool is_last(char *string, char *charlist) {
	/*
	 Check whether the current string is the last possible combination.
	*/

	char last_char = charlist[strlen(charlist)-1];
	for(int i=0; i<strlen(string); i++) {
		if(string[i] != last_char) {
			return false;
		}
	}

	return true;
}

int main(int argc, char *argv[]) {
	
	// Save the charlist
	char *charlist = alloc_str(strlen(argv[1]));
	strcpy(charlist, argv[1]);
	
	// Save the strings length
	int length = atoi(argv[2]);
	
	// Save the output file name
	char *output_file = alloc_str(strlen(argv[3]));
	strcpy(output_file, argv[3]);

	FILE *file = fopen(output_file, "w");		// Create a file for output
	char *current_string = repeat(charlist[0], length);		// Create the initial string

	// Write the list
	fprintf(file, "%s\n", current_string);
	do {
		next_sequence(current_string, charlist);		// Update the string
		fprintf(file, "%s\n", current_string);
	} while(! is_last(current_string, charlist));		// Stop when it's the last combination

	fclose(file);
}
