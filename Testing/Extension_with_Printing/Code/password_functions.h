//									PASSWORD RELATED FUNCTIONS

void password_check(password_info *pw_info);

void initialise_pw_info(password_info *pw_info);

void get_password_input(password_info *pw_info);

void read_in_pw_array(password_info *pw_info, password_array pw_array, initial_final array_ind);

void read_in_password_file(FILE **password_file, password_array pw_array);

void map_arrays(password_info *pw_info, password_array initial_array, password_array final_array);

void compare_arrays(password_info *pw_info, password_array final_array);

void change_password(password_info *pw_info);

void scan_password(int *new_pw);

void alter_password_files(int new_pw, char *filename, initial_final init_fin_ind, int temp_array_1[NUM_INTS_PW_FILE], int temp_array_2[NUM_INTS_PW_FILE]);