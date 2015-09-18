// 									INTERPRETING FUNCTIONS

void fd_interpret(player *user, printing_board *first_board);

void draw_angled_line(player *user, int number_steps, printing_board *first_board);

void check_number_steps(int number_steps);

void draw_next_square(int hypotenuse_length, player *user, int upper_bound, grid_location grid_loc, int number_steps, printing_board *first_board);

void check_variable(player *user);

void drawing_process(player *user, int new_user_row, int new_user_col, int number_steps, int hypotenuse_length, printing_board *first_board);

void assign_board_to_list(player *user, printing_board *first_board);

void copy_board_into_list(player *user, printing_board *next_board);

void lt_rt_interpret(player *user, rt_lt direction);

void lt_rt_interpret_case(player *user, rt_lt direction, float increment_constant);

void adjust_angle(player * user);

void op_interpret(program *prog, player *user, polish_stack *pol_stack);

void polish_varnum_interpret(program *prog, player *user, polish_stack *pol_stack);

void push_to_stack(polish_stack *pol_stack, float constant_for_push);

void interpret_set_variable(player *user);

void check_and_assign_variable(polish_stack *pol_stack, player *user);

void loop_subject_var_interpret(player *user);

void loop_start_var_interpreter(player *user);

void loop_end_var_interpreter(player *user);

void loop_interior_interpreter(player *user, program *prog);

void end_loop(player *user);

success_unsuccess check_loop_finish(player *user);