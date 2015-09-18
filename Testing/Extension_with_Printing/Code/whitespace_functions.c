#include "turtle_functions.h"

// This is just a wrapper for all of the functions that involve WhiteSpace.

void whitespace_functions(char *filename, whitespace_info *whitespace_prog)
{
	initialise_whitespace_prog(whitespace_prog);

	open_whitespace_program_file(filename, whitespace_prog);

	initialise_decoder_array(whitespace_prog);

	write_file_from_whitespace(whitespace_prog);
}

// First of all we initialise the WhiteSpace structure. We want to set everything
// to zero or off so they can be incremented or changed by the program.

void initialise_whitespace_prog(whitespace_info *whitespace_prog)
{

	int i;

	for(i = 0; i < MAX_NUM_LINES; ++i){
		whitespace_prog -> ws_spaces[i] = 	0;
		whitespace_prog -> ws_tabs[i] = 	0;
		whitespace_prog -> ws_number_indicators[i] = 	off;
		whitespace_prog -> ws_verbatim_file[i][0] = 	'\0';
	}

	for(i = 0; i < TOTAL_NUM_INSTRUCTIONS; ++i){
		whitespace_prog -> decoding_array[i][0] = '\0';
	}

	whitespace_prog -> ws_num_lines = 0;

	printf("\nAll whitespace components correctly initialised.\n");

}

// Here we scan in all of the WhiteSpace components of the file and strip
// away non-WhiteSpace. This creates a useful file of just the WhiteSpace
// that can be used in other places and is read in later in the program to decode
// the WhiteSpace message.

void open_whitespace_program_file(char *filename, whitespace_info *whitespace_prog)
{

	FILE *prog_file = NULL;

	char ch;

	strip_non_whitespace_components(filename);

	if( (prog_file = fopen("stripped_whitespace_file.txt", "r")) == NULL){
		clear_screen();
		fprintf(stderr, "\nThere was an error reading in the file.\n\n");
		exit(EXIT_CODE);
	}
	else{
		while( ( ch = fgetc(prog_file) ) != EOF ){
			scan_in_whitespace_components(whitespace_prog, ch);
		}
	}

	printf("\nAll whitespace components correctly scanned in.\n");

	for(int i = 0; i < whitespace_prog -> ws_num_lines; ++i){
		printf("\nNumber of spaces on line %d: %4d\n", i, whitespace_prog -> ws_spaces[i]);
		printf("Number of tabs on line %d: %4d\n\n", i, whitespace_prog -> ws_tabs[i]);
	}

	fclose(prog_file);
}

// We strip the non-whitespace components by reading in the file and then only printing to the
// new file if we register them as WhiteSpace characters.

void strip_non_whitespace_components(char *filename)
{

	FILE *whitespace_file = NULL, *stripped_whitespace_file = NULL;
	char ch;

	if( (whitespace_file = fopen(filename, "r")) == NULL || (stripped_whitespace_file = fopen("stripped_whitespace_file.txt", "w")) == NULL ){
		clear_screen();
		fprintf(stderr, "\nThere was an error reading in the file.\n\n");
		exit(1);
	}
	else{
		while( ( ch = fgetc(whitespace_file) ) != EOF){
			if(ch == '\n' || ch =='\t' || ch == ' '){
				fprintf(stripped_whitespace_file, "%c", ch);
			}
		}
	}

	printf("\nAll non whitespace components successfully stripped.\n");

	fclose(stripped_whitespace_file);
	fclose(whitespace_file);
}

// This function is used to scan in the WhiteSpace components. The way the WhiteSpace language works
// is that if there is a tab at the start of a line then that indicates we are looking at a number.
// For numbers we put the number of tabs that there are tens and number of spaces that there are units.
// So 51 would be 6 tabs and then 1 space.

// If no tabs are registered at the start then we assume we are looking at a potential command (DO,
// SET, ...) these are mapped using the number of spaces on the line and a decoding array explained later.

// As WhiteSpace is scanned in a tab and space counter is incremented to show how many tabs and spaces are
// on each line to be decoded later.

// On a newline we detect we are onto the next command and so set the variables within our WhiteSpace arrays
// and then reset the space and tabs counters, telling it to look for a number indicator again.

void scan_in_whitespace_components(whitespace_info *whitespace_prog, char ch)
{

	static int i = 0, space_counter = 0, tab_counter = 0;
	static on_off first_pass = on;

	if(first_pass == on){
		if(ch == '\t'){
			whitespace_prog -> ws_number_indicators[i] = on;
			--tab_counter;
		}
		first_pass = off;
	}

	if( ch == ' ' ){
		++space_counter;
	}
	else if( ch == '\t' ){
		if(first_pass != on){
			++tab_counter;
		}
	}
	else if( ch == '\n' ){

		whitespace_prog -> ws_spaces[i] = space_counter;
		whitespace_prog -> ws_tabs[i] = tab_counter;

		space_counter = 0;
		tab_counter = 0;

		first_pass = on;
		++i;
	}
	if(i > MAX_NUM_LINES){
		fprintf(stderr, "\nThe number of lines in the file has exceeded the recognised amount.\n\n");
		exit(EXIT_CODE);
	}

	whitespace_prog -> ws_num_lines = i;

	printf("\nWhitespace components scanned in to be decoded.\n");
}

// This initialises the decoder array within the program. We see that different commands are stored 
// at different indices of an array. The way the decoding works is to count the number of spaces we have
// and then look to that element of the array, writing the results to a file. We then use that
// file as usual and parse and interpret it.

void initialise_decoder_array(whitespace_info *whitespace_prog)
{

	int i;

	char *commands[TOTAL_NUM_INSTRUCTIONS] = {"{", "}", "FD", "LT", "RT", "SET", "DO", "FROM", "TO", ":=", ";", "+", "-", "*", "/", 
						"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", 
						"R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

	for(i = 0; i < TOTAL_NUM_INSTRUCTIONS; ++i){
		if(sscanf(commands[i], "%s", whitespace_prog -> decoding_array[i]) != SCAN_SUCCESS){
			clear_screen();
			fprintf(stderr, "\nThere was a problem scanning in the decoder array.\n\n");
			exit(EXIT_CODE);
		}
	}

	printf("\nDecoder array set.\n");
}

// This is used once we have read in all of the WhiteSpace and writes a file translating the
// WhiteSpace back to regular that can be used in the same functions we created for the main
// part of the project. It opens a file and then calls the necessary function.

void write_file_from_whitespace(whitespace_info *whitespace_prog)
{

	FILE *prog_file = NULL;

	if( (prog_file = fopen("ws_to_reg_translation.txt", "w")) == NULL){
		fprintf(stderr, "\nThere was an error opening the file to write.\n\n");
		exit(EXIT_CODE);
	}
	else{
		printf("\nWriting whitespace program to a file.\n");

		write_whitespace_prog_to_file(whitespace_prog, &prog_file);
	}

	fclose(prog_file);

}

// This writes the WhiteSpace to a file. If the number indicator is off then it decodes the
// tabs and spaces as if it were a command, if it is on it decodes it as if it were a number.
// This means interpreting the tabs and spaces as tens and units which is shown below.

void write_whitespace_prog_to_file(whitespace_info *whitespace_prog, FILE **prog_file)
{

	int i;

	for(i = 0; i < whitespace_prog -> ws_num_lines; ++i){
		if(whitespace_prog -> ws_number_indicators[i] == off){

			printf("\nDetected whitespace command, writing to a file.\n");

			fprintf(*prog_file, "%s\n", whitespace_prog -> decoding_array[ whitespace_prog -> ws_spaces[i] ]);
		}
		if(whitespace_prog -> ws_number_indicators[i] == on){

			printf("\nDetected whitespace number, writing to a file.\n");

			fprintf(*prog_file, "%d\n", WS_TRANS_CONST * whitespace_prog -> ws_tabs[i] + whitespace_prog -> ws_spaces[i]);

		}
	}
}

// This is used for translation from regular to WhiteSpace. We open the file to put the WhiteSpace in.

void write_file_to_whitespace(program *reg_prog)
{

	FILE *prog_file = NULL;

	if( (prog_file = fopen("reg_to_ws_translation.txt", "w")) == NULL){
		fprintf(stderr, "\nThere was an error opening the file to write.\n\n");
		exit(1);
	}
	else{

		printf("\nWriting the program to whitespace.\n");

		write_prog_to_whitespace_file(reg_prog, &prog_file);
	}

	fclose(prog_file);
}

// Now we have a list of the commands and an open file we can use. We have scanned
// in the regular file and put it in the appropriate structure. We then scan every
// element of the structure for integers. If we find one then we translate it to
// the WhiteSpace representation 

// If we don't find one then we search in the commands list for the appropriate matching
// string and print that to the file using spaces.

void write_prog_to_whitespace_file(program *reg_prog, FILE **prog_file)
{

	int i, j, k, temp_num, num_tens, num_units;

	char *commands[TOTAL_NUM_INSTRUCTIONS] = {"{", "}", "FD", "LT", "RT", "SET", "DO", "FROM", "TO", ":=", ";", "+", "-", "*", "/", 
						  "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", 
						  "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

	for(i = 0; i < reg_prog -> num_lines_in_file; ++i){

		if(sscanf(reg_prog -> prog_line[i], "%d", &temp_num) != 0){

			fprintf(*prog_file, "\t");

			num_tens = temp_num / WS_TRANS_CONST;
			num_units = temp_num - WS_TRANS_CONST * num_tens;

			for(k = 0; k < num_tens; ++k){

				fprintf(*prog_file, "\t");

			}
			for(k = 0; k < num_units; ++k){

				fprintf(*prog_file, " ");
			}

			fprintf(*prog_file, "\n");
		}

		else{
			
			for(j = 0; j < TOTAL_NUM_INSTRUCTIONS; ++j){

				if(same_string(reg_prog -> prog_line[i], commands[j])){ 						

					for(k = 0; k < j; ++k){

						fprintf(*prog_file, " ");
					}

					fprintf(*prog_file, "\n");
				}
			}

		}

	}

}
