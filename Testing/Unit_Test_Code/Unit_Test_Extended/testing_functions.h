//												TESTING FUNCTION DECLARATIONS

int initialise_CUnit(CU_pSuite *pSuite, char *suite_name);

int close_CUnit(void);

void set_up_test(char *suite_name, char *test_name, CU_TestFunc function);

void string_not_equal_test(char *string_one, char *string_two, char *message);

//											TESTING FUNCTIONS

void test_assign_board_to_list(void);

void test_assign_board_to_list_case(printing_board *board_to_add, printing_board *first_board);

void test_copy_board_into_list(void);

void test_check_initialisation(void);

void test_check_initialisation_case(program *prog, player *user, whitespace_info *whitespace_prog, printing_board *first_board, password_info *pw_info);

void test_check_animation_preferences(void);

void test_check_animation_preferences_case(int start, up_down dir_ind);

void test_examine_fourth_argument(void);

void test_examine_fourth_argument_case(char *argument, other_arg_type *argument_indicator);

void test_free_all_print_boards(void);

void test_free_all_print_boards_case(printing_board *current_board);

void test_initialise_whitespace_prog(void);

void test_open_whitespace_program_file(void);

void test_open_whitespace_program_file_case(FILE *prog_file);

void test_strip_non_whitespace_components(void);

void test_strip_non_whitespace_components_case(FILE *whitespace_file, FILE *stripped_whitespace_file);

void test_scan_in_whitespace_components(void);

void test_scan_in_whitespace_components_case(whitespace_info *whitespace_prog, char ch);

void test_initialise_decoder_array(void);

void test_write_file_from_whitespace(void);

void test_write_file_from_whitespace_case(FILE *prog_file);

void test_write_whitespace_prog_to_file(void);

void test_write_whitespace_prog_to_file_case(whitespace_info *whitespace_prog, on_off number_ind);

void test_write_prog_to_whitespace_file(void);

void test_write_prog_to_whitespace_file_case(int input_num, char *command);

void test_scan_in_whitespace_components_verbatim(void);

void test_scan_in_whitespace_components_verbatim_case(whitespace_info *whitespace_prog, char ch);

void test_write_combination_to_file(void);

void test_write_combination_to_file_case(FILE *combined_file, int num_1, int num_2, whitespace_info *whitespace_prog, program *prog);

void test_read_in_pw_array(void);

void test_read_in_pw_array_case(initial_final array_ind);

void test_map_arrays(void);

void test_compare_arrays(void);

void test_compare_arrays_case(password_array temp_array, password_array final_array);

void test_change_password(void);

void test_change_password_case(FILE *prog_file, password_array temp_array_1, password_array temp_array_2, int new_pw, initial_final init_fin_ind);