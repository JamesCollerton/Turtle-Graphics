#include "turtle_functions.h"

void combine_ws_reg_files(program *prog, whitespace_info *whitespace_prog, char *file_one, char *file_two)
{
	initialise_whitespace_prog(whitespace_prog);

	open_program_file(file_one, prog);

	open_whitespace_program_file_verbatim(file_two, whitespace_prog);

	write_combination_to_file(prog, whitespace_prog);
}

void open_whitespace_program_file_verbatim(char *filename, whitespace_info *whitespace_prog)
{
	FILE *prog_file;
	char ch;

	if( (prog_file = fopen(filename, "r")) == NULL){
		clear_screen();
		fprintf(stderr, "\nThere was an error reading in the file.\n\n");
		exit(EXIT_CODE);
	}
	else{
		while( ( ch = fgetc(prog_file) ) != EOF ){
			scan_in_whitespace_components_verbatim(whitespace_prog, ch);
		}
	}

}

void scan_in_whitespace_components_verbatim(whitespace_info *whitespace_prog, char ch)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Scan in Whitespace Components Verbatim Suite", "Test of scan_in_whitespace_components_verbatim()", test_scan_in_whitespace_components_verbatim);

		++first_pass;

	}
	//////////////////////////

	static int i = 0;

	whitespace_prog -> ws_verbatim_file[ whitespace_prog -> ws_num_lines ][i] = ch;
	++i;

	if(ch == '\n'){
		whitespace_prog -> num_chars_per_line[ whitespace_prog -> ws_num_lines ] = i;
		++whitespace_prog -> ws_num_lines;
		i = 0;
	}
}

void write_combination_to_file(program *prog, whitespace_info *whitespace_prog)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Write Combination to File Suite", "Test of write_combination_to_file()", test_write_combination_to_file);

		++first_pass;

	}
	//////////////////////////

	FILE *combined_file;
	int current_line = 0;

	if( (combined_file = fopen("Combined_File.txt", "w")) == NULL){
		clear_screen();
		fprintf(stderr, "\nThere was an error reading in the file.\n\n");
		exit(1);
	}

	while(current_line <= whitespace_prog -> ws_num_lines && current_line <= prog -> num_lines_in_file){
		print_combination_to_file(prog, whitespace_prog, &combined_file, current_line);
		++current_line;
	}

	if(whitespace_prog -> ws_num_lines > current_line){
		while(current_line <= whitespace_prog -> ws_num_lines){
			print_only_ws_to_file(whitespace_prog, &combined_file, current_line);
			++current_line;
		}
	}
	else if(prog -> num_lines_in_file > current_line){
		while(current_line <= prog -> num_lines_in_file){
			print_only_non_ws_to_file(prog, &combined_file, current_line);
			++current_line;
		}
	}

	fclose(combined_file);
}

void print_combination_to_file(program *prog, whitespace_info *whitespace_prog, FILE **combined_file, int current_line)
{
	int i;

	fprintf(*combined_file, "%s", prog -> prog_line[current_line]);

	for(i = 0; i < whitespace_prog -> num_chars_per_line[current_line]; ++i){
		fprintf(*combined_file, "%c", whitespace_prog -> ws_verbatim_file[ current_line ][i]);
	}

}

void print_only_ws_to_file(whitespace_info *whitespace_prog, FILE **combined_file, int current_line)
{
	int i;

	for(i = 0; i < whitespace_prog -> num_chars_per_line[current_line]; ++i){
		fprintf(*combined_file, "%c", whitespace_prog -> ws_verbatim_file[ current_line ][i]);
	}
}

void print_only_non_ws_to_file(program *prog, FILE **combined_file, int current_line)
{
	fprintf(*combined_file, "\n%s\n", prog -> prog_line[current_line]);
}