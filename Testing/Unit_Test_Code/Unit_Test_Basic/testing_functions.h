//												Testing Functions

int initialise_CUnit(CU_pSuite *pSuite, char *suite_name);

int close_CUnit(void);

void set_up_test(char *suite_name, char *test_name, CU_TestFunc function);

void assert_test(int test, char *message);

void string_equal_test(char *string_one, char *string_two, char *message);

void string_not_equal_test(char *string_one, char *string_two, char *message);

void test_check_command_line(void);

void test_clear_screen(void);

void clear_screen_case(int clear_screen_checker);

void test_initialising(void);

void test_initialise_player(void);

void test_open_program_file(void);

void open_correct_file(program *prog, FILE **prog_file);

void open_incorrect_file(FILE **prog_file);

void test_parse_interpret(void);

void parse_interpret_case(program *prog_point, char *opening_command, char *register_message);

void test_same_string(void);

void test_same_string_case(char *string_one, char *string_two);

void test_instrctlist(void);

void test_instruction(void);

void test_iteration(test_instructions *test_struct, int fd, int lt, int rt, int do_check, int set_check);

void set_test_instruction_struct(test_instructions *test_struct, int fd, int lt, int rt, int do_loop, int set_loop);

void test_structure_iteration(test_instructions *test_struct);

void command_recognition_case(success_unsuccess test, char *success_message, char *fail_message);

void test_fd(void);

void check_instruction_registered(program *prog_point, char *word_to_set, char *set_message);

void check_program_incremented(program *prog_point);

void randomly_assign_point(program *prog_point);

void check_registers_string(program *prog_point, char *correct_string, char *pass_message, char *fail_message);

void check_registers_incorrect_string(program *prog_point, char *correct_string, char *pass_message, char *fail_message);

void assign_word_to_point(char *word, program *prog_point, char *message);

void test_lt_rt(void);

void test_lt_rt_cases(program *prog_point, char *register_message, char *lt_or_rt, char *pass_message, char *fail_message);

void test_do_check(void);

void test_do_loop(void);

void initialise_do_loop_components(program *prog_point, do_loop_test_indicators indicator_struct);

void initialise_single_do_component(on_off indicator, char *word, program *prog_point, char *assign_message);

void initialise_do_loop_indicator_components(do_loop_test_indicators *indicator_struct, on_off FROM_ind, on_off TO_ind, on_off bracket_ind);

void do_loop_case_checker(program *prog_point, do_loop_test_indicators *indicator_struct);

void do_loop_section_check(on_off indicator, char *success_message, char* fail_message, program *prog_point);

void looping_component_check(int start_of_loop, int end_of_loop);

void test_set_check(void);

void test_set_loop(void);

void test_init_pol_stack(void);

void test_polish(void);

void test_polish_case(program *prog_point, polish_indicators *pol_ind_struct, on_off end_state_on, on_off op_state_on);

void initialise_polish_struct(polish_indicators *pol_ind_struct, on_off end_state_on, on_off op_state_on);

void set_end(polish_indicators *pol_ind_struct, program *prog_point);

void test_polish_terms(program *prog_point, polish_indicators *pol_ind_struct);

void test_op(void);

void test_op_case(program *prog_point, on_off plus_ind, on_off minus_ind, on_off divide_ind, on_off multiply_ind, player *user);

void initialise_operand_indicators(operand_indicators *op_ind_struct, on_off plus_ind, on_off minus_ind, on_off divide_ind, on_off multiply_ind);

void initialise_current_word_op(operand_indicators *op_ind_struct, program *prog_point);

void carry_out_op_test(operand_indicators *op_ind_struct, program *prog_point, player *user);

void op_assignment_and_checking(on_off test, player *user, int current_operator);

void test_varnum(void);

void test_varnum_case(program *prog_point, on_off variable_ind, on_off number_ind);

void initialise_varnum_indicators(varnum_indicators *varnum_inds, on_off variable_ind, on_off number_ind);

void initialise_varnum_string(varnum_indicators *varnum_inds, program *prog_point);

void carry_out_varnum_test(program *prog_point, varnum_indicators *varnum_inds);

void test_var(void);

void test_var_case(program *prog_point, on_off variable_indicator);

void test_SDL_print(void);

void print_SDL_array_test_ver(player *user, SDL_Simplewin *sw, int k, int l);





















// 				Interpreter Based Functions

void test_fd_interpret(void);

void fd_interpret_case(player *user, on_off var_check, on_off const_check);

void initialise_user_checkers(player *user, on_off var_check, on_off const_check);

void interpret_user_checkers(player *user, on_off var_check, on_off const_check);

void test_check_variable(void);

void check_variable_case(player *user, int curr_var_val);

void test_draw_angled_line(void);

void draw_angled_line_case(player *user, int number_steps, int angle);

void test_draw_next_square(void);

void draw_next_square_case(player *user, int hypotenuse_length, int upper_bound, grid_location grid_loc);

void test_drawing_process(void);

void drawing_process_case(player *user, int new_user_row, int new_user_col, int hypotenuse_length, int number_steps);

void test_lt_rt_interpret(void);

void examine_lt_rt_case(player *user, on_off const_checker, on_off var_checker, int angle);

void lt_rt_interpret_case(player *user, on_off const_checker, on_off var_checker, int angle, rt_lt dir);

void lt_rt_test(player *user, rt_lt direction);

void test_adjust_angle(void);

void adjust_angle_case(player *user, int angle);

void test_op_interpret(void);

void op_interpret_case(program *prog, player *user, polish_stack *pol_stack, int operator_symbol, int current_index);

void test_polish_varnum_interpret(void);

void polish_varnum_interpret_case(player *user, on_off const_checker, on_off var_checker);

void test_push_to_stack(void);

void test_interpret_set_variable(void);

void test_check_and_assign_variable(void);

void check_and_assign_variable_case(polish_stack *pol_stack, player *user, int current_index, on_off op_ind);

void test_loop_subject_var_interpret(void);

void loop_subject_var_interpret_case(player *user, int looping_index);

void test_loop_start_var_interpreter(void);

void initialise_start_var_interpreter_case(player *user, on_off const_checker, on_off var_checker, int *variable);

void loop_start_var_interpreter_case(player *user, on_off const_checker, on_off var_checker);

void test_loop_end_var_interpreter(void);

void loop_end_var_interpreter_case(player *user, on_off const_checker, on_off var_checker, int end, int start);

void initialise_loop_end_var_interpreter_case(player *user, on_off const_checker, on_off var_checker, int end, int start);

void test_check_loop_finish(void);

void check_loop_finish_case(player *user, int curr_var_num, int curr_loop_num);

////////////////////////////