//												Function prototypes

// Parser Functions

void check_command_line_arguments(int argc);

void clear_screen(void);

void initialise_program(program *prog);

void initialise_player(player *user);

void open_program_file(char *filename, program *prog);

void parse_text_and_interpret(program *prog, player *user);

success_unsuccess same_string(char *string_one, char *string_two);

void print_parsed_text(program *prog);

void instrctlist(program *prog, player *user);

void instruction(program *prog, player *user);

success_unsuccess fd(program *prog, player *user);

success_unsuccess lt_rt(program *prog, player *user, rt_lt direction, char *command);

success_unsuccess do_check(program *prog, player *user);

void do_loop(program *prog, player *user);

success_unsuccess set_check(program *prog, player *user);

void set_loop(program *prog, player *user);

void initialise_pol_stack(polish_stack *pol_stack);

void polish(program *prog, player *user, polish_stack *pol_stack);

success_unsuccess op(program *prog, player *user);

void varnum(program *prog, player *user);

void var(program *prog, player *user);

void print_SDL_array(player *user, SDL_Simplewin *sw);


// Interpreting Functions

void fd_interpret(player *user);

void draw_angled_line(player *user, int number_steps);

void draw_next_square(int hypotenuse_length, player *user, int upper_bound, grid_location grid_loc, int number_steps);

void check_variable(player *user);

void drawing_process(player *user, int new_user_row, int new_user_col, int number_steps, int hypotenuse_length);

void lt_rt_interpret(player *user, rt_lt direction);

void adjust_angle(player * user);

void op_interpret(program *prog, player *user, polish_stack *pol_stack);

void polish_varnum_interpret(program *prog, player *user, polish_stack *pol_stack);

void push_to_stack(polish_stack *pol_stack, int constant_for_push);

void interpret_set_variable(player *user);

void check_and_assign_variable(polish_stack *pol_stack, player *user);

void loop_subject_var_interpret(player *user);

void loop_start_var_interpreter(player *user);

void loop_end_var_interpreter(player *user);

void loop_interior_interpreter(player *user, program *prog);

void end_loop(player *user);

success_unsuccess check_loop_finish(player *user);