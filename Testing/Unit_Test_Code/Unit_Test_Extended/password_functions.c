#include "turtle_functions.h"

void password_check(password_info *pw_info)
{
	
	password_array initial_array, finish_array;

	initialise_pw_info(pw_info);

	get_password_input(pw_info);

	read_in_pw_array(pw_info, initial_array, initial);

	read_in_pw_array(pw_info, finish_array, final);

	map_arrays(pw_info, initial_array, finish_array);

	compare_arrays(pw_info, finish_array);

}

void initialise_pw_info(password_info *pw_info)
{

	pw_info -> pw_indicator = decline;
	pw_info -> password = 0;

}

void get_password_input(password_info *pw_info)
{
	int temp_pw;

	clear_screen();
	printf("\n\nPlease enter the password: ");

	if( scanf("%d", &temp_pw) != SCAN_SUCCESS ){
		clear_screen();
		fprintf(stderr, "\nThere was an error scanning the password.\n\n");
		exit(EXIT_CODE);
	}

	pw_info -> password = temp_pw;

}

void read_in_pw_array(password_info *pw_info, password_array pw_array, initial_final array_ind)
{
	//////////////////////////					Testing

	static int test_first_pass = 0;

	if(test_first_pass == 0){

		set_up_test("Read in Password Array Suite", "Test of read_in_pw_array()", test_read_in_pw_array);

		++test_first_pass;

	}
	//////////////////////////

	FILE *password_file;

	if(array_ind == initial){
		password_file = fopen("Password_Files/password_file_1.txt", "r");
	}
	else{
		password_file = fopen("Password_Files/password_file_2.txt", "r");
	}

	if( password_file == NULL){
		clear_screen();
		fprintf(stderr, "\nThere was an error reading in the file.\n\n");
		exit(EXIT_CODE);
	}

	read_in_password_file(&password_file, pw_array);

	fclose(password_file);
}

void read_in_password_file(FILE **password_file, password_array pw_array)
{

	int temp, i = 0;

	while( fscanf(*password_file, "%d", &temp) == SCAN_SUCCESS){

		pw_array[i] = temp;
		++i;

		if(i > NUM_INTS_PW_FILE){
			clear_screen();
			fprintf(stderr, "\nPassword file has too many characters.\n\n");
			exit(EXIT_CODE);
		}
	}

}

void map_arrays(password_info *pw_info, password_array initial_array, password_array final_array)
{
	//////////////////////////					Testing

	static int test_first_pass = 0;

	if(test_first_pass == 0){

		set_up_test("Map Arrays Suite", "Test of map_arrays()", test_map_arrays);

		++test_first_pass;

	}
	//////////////////////////

	int i;

	for(i = 0; i < NUM_INTS_PW_FILE; ++i){
		pw_info -> temp_pw_array[i] = initial_array[ (i + pw_info -> password) % NUM_INTS_PW_FILE ];
	}

}

void compare_arrays(password_info *pw_info, password_array final_array)
{
	//////////////////////////					Testing

	static int test_first_pass = 0;

	if(test_first_pass == 0){

		set_up_test("Compare Arrays Suite", "Test of compare_arrays()", test_compare_arrays);

		++test_first_pass;

	}
	//////////////////////////

	int i;

	for(i = 0; i < NUM_INTS_PW_FILE; ++i){
		if(pw_info -> temp_pw_array[i] != final_array[i]){
			fprintf(stderr, "\n\nPassword not recognised.\n\n");
			exit(EXIT_CODE);
			return;
		}
	}

	pw_info -> pw_indicator = accept;
	clear_screen();
	printf("\nPassword Accepted.\n");
}

void change_password(password_info *pw_info)
{

	int new_pw;
	int temp_array_1[NUM_INTS_PW_FILE], temp_array_2[NUM_INTS_PW_FILE];

	do{
		scan_password(&new_pw);
	}while(new_pw > MAX_PASSWORD || new_pw < MIN_PASSWORD);

	alter_password_files(new_pw, "Password_Files/password_file_1.txt", initial, temp_array_1, temp_array_2);

	alter_password_files(new_pw, "Password_Files/password_file_2.txt", final, temp_array_1, temp_array_2);

}

void scan_password(int *new_pw)
{
	clear_screen();
	printf("\nPlease enter your new password (integer between 0 - 1000): ");

	if( scanf("%d", new_pw) != SCAN_SUCCESS ){
		clear_screen();
		fprintf(stderr, "\nThere was an error scanning the password.\n\n");
		exit(EXIT_CODE);
	}

}

void alter_password_files(int new_pw, char *filename, initial_final init_fin_ind, int temp_array_1[NUM_INTS_PW_FILE], int temp_array_2[NUM_INTS_PW_FILE])
{
	//////////////////////////					Testing

	static int test_first_pass = 0;

	if(test_first_pass == 0){

		set_up_test("Change Password Suite", "Test of change_password()", test_change_password);

		++test_first_pass;

	}
	//////////////////////////

	FILE *prog_file;

	if( (prog_file = fopen(filename, "w")) == NULL ){
		clear_screen();
		fprintf(stderr, "\nThere was an error reading in the password file.\n\n");
		exit(EXIT_CODE);
	}

	for(int i = 0; i < NUM_INTS_PW_FILE; ++i){

		if(init_fin_ind == initial){
			temp_array_1[i] = rand() % BINARY;
			fprintf(prog_file, "%d ", temp_array_1[i]);
		}

		else if(init_fin_ind == final){
			temp_array_2[i] = temp_array_1[ (i + new_pw) % NUM_INTS_PW_FILE ];
			fprintf(prog_file, "%d ", temp_array_2[i]);
		}
	}

	fclose(prog_file);

}