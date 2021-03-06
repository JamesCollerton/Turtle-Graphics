#include "turtle_functions.h"

// This is a wrapper for containing all of the password related functions.

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

// This initialises the password array. By default we decline the Password
// and set the password to zero. 

void initialise_pw_info(password_info *pw_info)
{

	pw_info -> pw_indicator = decline;
	pw_info -> password = 0;

	printf("\nPassword components successfully initialised.\n");

}

// Here we scan the password from the terminal. If nothing has been
// scanned we print an error.

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
	printf("\nPassword scanned as: %d.\n", pw_info -> password);

}

// This is used to read in the two password arrays. As explained in the documentation
// the password works by mapping two arrays to each other, an initial and a final array.
// If we pass this function an initial argument it opens up the first one, if we pass it
// the second argument then it opens up the final one.

// If opening fails then we print an error.

void read_in_pw_array(password_info *pw_info, password_array pw_array, initial_final array_ind)
{

	FILE *password_file;

	if(array_ind == initial){
		password_file = fopen("Password_Files/password_file_1.txt", "r");
		printf("\nPassword file 1 scanned in.\n");
	}
	else{
		password_file = fopen("Password_Files/password_file_2.txt", "r");
		printf("\nPassword file 2 scanned in.\n");
	}

	if( password_file == NULL){
		clear_screen();
		fprintf(stderr, "\nThere was an error reading in the file.\n\n");
		exit(EXIT_CODE);
	}

	read_in_password_file(&password_file, pw_array);

	fclose(password_file);
}

// This is used to scan in the components of the file. While there are characters
// to be scanned it takes them in, then if we detect we have too many it errors out.

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

// Having scanned in the two arrays we now map them one to the other as explained in the documentation.
// This is done using the technique explained there. The password is used to shift the index of one
// array along by a set amount to try and map the arrays to each other.

void map_arrays(password_info *pw_info, password_array initial_array, password_array final_array)
{

	int i;

	for(i = 0; i < NUM_INTS_PW_FILE; ++i){
		pw_info -> temp_pw_array[i] = initial_array[ (i + pw_info -> password) % NUM_INTS_PW_FILE ];
	}

	printf("\nInitial array mapped to final array.\n");

}

// Now we compare the arrays. If the elements are all identical after being mapped to each other then
// we have the correct password.

void compare_arrays(password_info *pw_info, password_array final_array)
{

	int i;

	for(i = 0; i < NUM_INTS_PW_FILE; ++i){
		if(pw_info -> temp_pw_array[i] != final_array[i]){
			clear_screen();
			fprintf(stderr, "\n\nPassword not recognised.\n\n");
			exit(EXIT_CODE);
			return;
		}
	}

	pw_info -> pw_indicator = accept;
	clear_screen();
	printf("\nPassword Accepted.\n");

}

// If we enter no other arguments at the command line then we can change the password. The way this works is that
// a user is prompted for their new password and then the two files are rewritten using that as the index shift.

void change_password(password_info *pw_info)
{

	int new_pw;
	int temp_array_1[NUM_INTS_PW_FILE], temp_array_2[NUM_INTS_PW_FILE];

	do{
		scan_password(&new_pw);
	}while(new_pw > MAX_PASSWORD || new_pw < MIN_PASSWORD);

	printf("\nNew password scanned as %d.\n", new_pw);

	alter_password_files(new_pw, "Password_Files/password_file_1.txt", initial, temp_array_1, temp_array_2);

	alter_password_files(new_pw, "Password_Files/password_file_2.txt", final, temp_array_1, temp_array_2);

}

// The player is asked for their new password. If nothing is scanned in it errors out.

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

// This function alters the password files depending on the new password entered.
// If we have sent it the initial argument then we want to change the first array
// and we randomly generate 1000 0s or 1s in a file. If we then give it the final
// argument we generate another file which is mapped according to the password.

void alter_password_files(int new_pw, char *filename, initial_final init_fin_ind, int temp_array_1[NUM_INTS_PW_FILE], int temp_array_2[NUM_INTS_PW_FILE])
{

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

	printf("\nRandomly set initial new password file and encoded the next %d.\n", new_pw);

	fclose(prog_file);

}
