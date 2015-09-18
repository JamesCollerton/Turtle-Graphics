#include "turtle_functions.h"

void whitespace_functions(char *filename, whitespace_info *whitespace_prog)
{
	initialise_whitespace_prog(whitespace_prog);

	open_whitespace_program_file(filename, whitespace_prog);

	initialise_decoder_array(whitespace_prog);

	write_file_from_whitespace(whitespace_prog);
}

void initialise_whitespace_prog(whitespace_info *whitespace_prog)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Initialise Whitespace Program Suite", "Test of initialise_whitespace_prog()", test_initialise_whitespace_prog);

		++first_pass;

	}
	//////////////////////////

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

}

void open_whitespace_program_file(char *filename, whitespace_info *whitespace_prog)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Open Whitespace Program Suite", "Test of open_whitespace_program_file()", test_open_whitespace_program_file);

		++first_pass;

	}
	//////////////////////////

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

	fclose(prog_file);
}

void strip_non_whitespace_components(char *filename)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Strip Non Whitespace Components Suite", "Test of strip_non_whitespace_components()", test_strip_non_whitespace_components);

		++first_pass;

	}
	//////////////////////////

	FILE *whitespace_file = NULL, *stripped_whitespace_file = NULL;
	char ch;

	if( (whitespace_file = fopen(filename, "r")) == NULL || (stripped_whitespace_file = fopen("stripped_whitespace_file.txt", "w")) == NULL ){
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

	fclose(stripped_whitespace_file);
	fclose(whitespace_file);
}

void scan_in_whitespace_components(whitespace_info *whitespace_prog, char ch)
{
	//////////////////////////					Testing

	static int test_first_pass = 0;

	if(test_first_pass == 0){

		set_up_test("Scan in Whitespace Components Suite", "Test of scan_in_whitespace_components()", test_scan_in_whitespace_components);

		++test_first_pass;

	}
	//////////////////////////

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
}

void initialise_decoder_array(whitespace_info *whitespace_prog)
{
	//////////////////////////					Testing

	static int test_first_pass = 0;

	if(test_first_pass == 0){

		set_up_test("Initialise Decoder Array Suite", "Test of initialise_decoder_array()", test_initialise_decoder_array);

		++test_first_pass;

	}
	//////////////////////////

	int i;

	char *commands[TOTAL_NUM_INSTRUCTIONS] = {"{", "}", "FD", "LT", "RT", "SET", "DO", "FROM", "TO", ":=", ";", "+", "-", "*", "/", 
						"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", 
						"R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

	for(i = 0; i < TOTAL_NUM_INSTRUCTIONS; ++i){
		sscanf(commands[i], "%s", whitespace_prog -> decoding_array[i]);
	}
}

void write_file_from_whitespace(whitespace_info *whitespace_prog)
{
	//////////////////////////					Testing

	static int test_first_pass = 0;

	if(test_first_pass == 0){

		set_up_test("Write File from Whitespace Suite", "Test of write_file_from_whitespace()", test_write_file_from_whitespace);

		++test_first_pass;

	}
	//////////////////////////

	FILE *prog_file = NULL;

	if( (prog_file = fopen("ws_to_reg_translation.txt", "w")) == NULL){
		fprintf(stderr, "\nThere was an error opening the file to write.\n\n");
		exit(EXIT_CODE);
	}
	else{
		write_whitespace_prog_to_file(whitespace_prog, &prog_file);
	}

	fclose(prog_file);

}

void write_whitespace_prog_to_file(whitespace_info *whitespace_prog, FILE **prog_file)
{
	//////////////////////////					Testing

	static int test_first_pass = 0;

	if(test_first_pass == 0){

		set_up_test("Write Whitespace Program to File Suite", "Test of write_whitespace_prog_to_file()", test_write_whitespace_prog_to_file);

		++test_first_pass;

	}
	//////////////////////////

	int i;

	for(i = 0; i < whitespace_prog -> ws_num_lines; ++i){
		if(whitespace_prog -> ws_number_indicators[i] == off){
			fprintf(*prog_file, "%s\n", whitespace_prog -> decoding_array[ whitespace_prog -> ws_spaces[i] ]);
		}
		if(whitespace_prog -> ws_number_indicators[i] == on){
			fprintf(*prog_file, "%d\n", WS_TRANS_CONST * whitespace_prog -> ws_tabs[i] + whitespace_prog -> ws_spaces[i]);
		}
	}
}

void write_file_to_whitespace(program *reg_prog)
{

	FILE *prog_file = NULL;

	if( (prog_file = fopen("reg_to_ws_translation.txt", "w")) == NULL){
		fprintf(stderr, "\nThere was an error opening the file to write.\n\n");
		exit(1);
	}
	else{
		write_prog_to_whitespace_file(reg_prog, &prog_file);
	}

	fclose(prog_file);
}

void write_prog_to_whitespace_file(program *reg_prog, FILE **prog_file)
{
	//////////////////////////					Testing

	static int test_first_pass = 0;

	if(test_first_pass == 0){

		set_up_test("Write Program to Whitespace Suite", "Test of write_prog_to_whitespace_file()", test_write_prog_to_whitespace_file);

		++test_first_pass;

	}
	//////////////////////////

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

				if(strcmp(reg_prog -> prog_line[i], commands[j]) == 0){ 						//Should change to same_string.
					for(k = 0; k < j; ++k){
						fprintf(*prog_file, " ");
					}
					fprintf(*prog_file, "\n");
				}
			}

		}

	}

}