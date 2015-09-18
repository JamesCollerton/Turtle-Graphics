// 										PARSER FUNCTION PROTOTYPES

void check_initialisation(program *prog, player *user, whitespace_info *whitespace_prog, printing_board *first_board, password_info *pw_info);

void check_command_line_arguments(player *user, int argc, other_arg_type *argument_indicator, char *argv[], password_info *pw_info);

void clear_screen(void);

void examine_third_argument(char *third_argument, other_arg_type *argument_indicator);

void check_animation_preferences(player *user);

void examine_fourth_argument(char *fourth_argument, other_arg_type *argument_indicator);

void initialisation(program *prog, player *user, printing_board *first_board);

void initialise_program(program *prog);

void initialise_player(player *user);

void initialise_printing_board(printing_board *first_board);

void open_program_file(char *filename, program *prog);

void parse_text_and_interpret(program *prog, player *user, printing_board *first_board);

success_unsuccess same_string(char *string_one, char *string_two);

void print_parsed_text(program *prog);

void instrctlist(program *prog, player *user, printing_board *first_board);

void instruction(program *prog, player *user, printing_board *first_board);

success_unsuccess fd(program *prog, player *user);

success_unsuccess lt_rt(program *prog, player *user, rt_lt direction, char *command);

success_unsuccess do_check(program *prog, player *user, printing_board *first_board);

void do_loop(program *prog, player *user, printing_board *first_board);

success_unsuccess set_check(program *prog, player *user);

void set_loop(program *prog, player *user);

void polish(program *prog, player *user, polish_stack *pol_stack);

success_unsuccess op(program *prog, player *user);

void varnum(program *prog, player *user);

void var(program *prog, player *user);

void printing(player *user, printing_board *current_board, SDL_Simplewin *sw);

void print_boards(player *user, printing_board *first_board, SDL_Simplewin *sw);

void print_SDL_board(player *user, printing_board *current_board, SDL_Simplewin *sw, on_off final_indicator);

void free_components(printing_board *first_board, program *prog, player *user, whitespace_info *whitespace_prog, password_info *pw_info);

void free_all_print_boards(printing_board *first_board);

void initialise_pol_stack(polish_stack *pol_stack);