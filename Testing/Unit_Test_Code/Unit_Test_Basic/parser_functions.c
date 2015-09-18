#include "turtle_functions.h"

void check_command_line_arguments(int argc)
{ 
	//There needs to be two arguments, the executable and the .txt file
	if(argc < 2){
		clear_screen();
		fprintf(stderr, "\nNot enough arguments were entered at the command line.\n\n");
		exit(1);
	}
	if(argc > 2){
		clear_screen();
		fprintf(stderr, "\nToo many arguments were entered at the command line.\n\n");
		exit(1);
	}

}

void clear_screen(void)
{
	//////////////////////////					Testing

	set_up_test("Clear Screen Suite", "Test of clear_screen()", test_clear_screen);

	//////////////////////////

	int clear_screen_checker;

	clear_screen_checker = system("clear");

	if(clear_screen_checker != CLEAR_SUCCESS){
		fprintf(stderr, "\nThere was an error clearing the screen.\n\n");
		exit(1);
	}

}

void initialise_program(program *prog)
{
	//////////////////////////					Testing

	set_up_test("Initialise Program Suite", "Test of initialise_program()", test_initialising);

	//////////////////////////

	int i;

	prog -> current_word = 0;
	prog -> num_lines_in_file = 0;

	for(i = 0; i < MAX_NUM_LINES; ++i){
		prog -> prog_line[i][0] = '\0';
	}

}

void initialise_player(player *user)
{
	//////////////////////////					Testing

	set_up_test("Initialise Player Suite", "Test of initialise_player()", test_initialise_player);

	//////////////////////////

	int i, j;

	for(i = 0; i < WHEIGHT; ++i){
		for(j = 0; j < WWIDTH; ++j){
			user -> player_board[i][j] = uncoloured;
		}
	}

	for(i = 0; i < START_ITERATION_END; ++i){
		for(j = 0; j < MAX_EMBEDDED_LOOPS; ++j){
			user -> looping_array[i][j] = 0;
		}
	}

	for(i = 0; i < NUM_LETTERS_ALPHABET; ++i){
		user -> variable_values[i] = ERROR_VALUE;
	}

	user -> row = MIDDLE_OF_BOARD;
	user -> col = MIDDLE_OF_BOARD;
	user -> angle = 0;
	user -> player_board[ MIDDLE_OF_BOARD ][ MIDDLE_OF_BOARD ] = coloured;
	user -> current_constant = 0;
	user -> current_variable = 0;
	user -> current_operator = 0;
	user -> set_variable = 0;
	user -> current_steps_taken = 0;
	user -> looping_index = 0;
	user -> variable_checker = off;
	user -> constant_checker = off;
	user -> operation_indicator = off;
	user -> loop_indicator = off;

}

void open_program_file(char *filename, program *prog)
{
	//////////////////////////					Testing

	set_up_test("Open Program Suite", "Test of open_program_file()", test_open_program_file);

	//////////////////////////

	FILE *prog_file = NULL;
	int i = 0;

	if( (prog_file = fopen(filename, "r")) == NULL){
		clear_screen();
		fprintf(stderr, "\nThere was an error reading in the file.\n\n");
		exit(1);
	}
	else{
		while( fscanf(prog_file, "%s", prog -> prog_line[i]) == SCAN_SUCCESS ){
			i++;
			if(i > MAX_NUM_LINES){
				clear_screen();
				fprintf(stderr, "\nThe number of lines in the file has exceeded the recognised amount.\n\n");
				exit(1);
			}
		}
	}

	prog -> num_lines_in_file = i;

}

void parse_text_and_interpret(program *prog, player *user)
{

	if( ! (same_string(prog -> prog_line[prog -> current_word], "{") ) ){
		clear_screen();
		ERROR("\nNo starting brace.\n\n");
	}

	++prog -> current_word;

	instrctlist(prog, user);

	//////////////////////////					 Testing

	set_up_test("Parsing and Interpreting Suite", "Test of parse_text_and_interpret()", test_parse_interpret);

	//////////////////////////

}

success_unsuccess same_string(char *string_one, char *string_two)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Same String Suite", "Test of same_string()", test_same_string);

		++first_pass;

	}
	//////////////////////////

	if( strcmp(string_one, string_two) == 0 ){

		return(successful);
	}
	else{
		return(unsuccessful);
	}

}

void instrctlist(program *prog, player *user)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Instrctlist Suite", "Test of instrctlist()", test_instrctlist);

		++first_pass;

	}
	
	//////////////////////////

	if( same_string(prog -> prog_line[prog -> current_word], "}")){

		++prog -> current_word;

		return;
	}

	instruction(prog, user);

	instrctlist(prog, user);
}

void instruction(program *prog, player *user)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Instruction Suite", "Test of instruction()", test_instruction);

		++first_pass;

	}
	//////////////////////////

	if( fd(prog, user) ){
		fd_interpret(user);
		return;
	}
	else if( lt_rt(prog, user, lt_dir, "LT") ){
		return;
	}
	else if( lt_rt(prog, user, rt_dir, "RT") ){
		return;
	}
	else if( do_check(prog, user) ){
		return;
	}
	else if( set_check(prog, user) ){
		return;
	}
	else{
		clear_screen();
		ERROR("\nExpected an instruction.\n\n");
	}
}

success_unsuccess fd(program *prog, player *user)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("FD Suite", "Test of fd()", test_fd);

		++first_pass;

	}
	//////////////////////////

	if( same_string(prog -> prog_line[prog -> current_word], "FD") ){

		++prog -> current_word;
		varnum(prog, user);

		return(successful);
	}
	else{
		return(unsuccessful);
	}
}

success_unsuccess lt_rt(program *prog, player *user, rt_lt direction, char *command)
{

	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Turn Suite", "Test of lt_rt()", test_lt_rt);

		++first_pass;

	}
	//////////////////////////

	if( same_string(prog -> prog_line[prog -> current_word], command) ){

		++prog -> current_word;
		varnum(prog, user);
		lt_rt_interpret(user, direction);

		return(successful);
	}
	else{
		return(unsuccessful);
	}
}

success_unsuccess do_check(program *prog, player *user)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Do Suite", "Test of do_check()", test_do_check);

		++first_pass;

	}
	//////////////////////////

	if( same_string(prog -> prog_line[prog -> current_word], "DO") ){

		++prog -> current_word;
		do_loop(prog, user);

		return(successful);
	}
	else{
		return(unsuccessful);
	}
}

void do_loop(program *prog, player *user)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Do Loop Suite", "Test of do_loop()", test_do_loop);

		++first_pass;

	}
	//////////////////////////

	var(prog, user);
	loop_subject_var_interpret(user);

	if( same_string(prog -> prog_line[prog -> current_word], "FROM") ){

		++prog -> current_word;
		varnum(prog, user);
		loop_start_var_interpreter(user);

		if( same_string(prog -> prog_line[prog -> current_word], "TO") ){

			++prog -> current_word;
			varnum(prog, user);
			loop_end_var_interpreter(user);

				if( same_string( prog -> prog_line[prog -> current_word], "{" ) ){

					++prog -> current_word;
					loop_interior_interpreter(user, prog);

					do{

						prog -> current_word = user -> looping_array[ start_word ][ user -> looping_index ];
						instrctlist(prog, user);
						end_loop(user);

					}while(!check_loop_finish(user));					

				}
				else{

					clear_screen();
					ERROR("\nExpected an opening bracket.\n\n");

				}
		
		}
		else{

			clear_screen();
			ERROR("\nExpected a TO statement.\n\n");

		}

	}
	else{

		clear_screen();
		ERROR("\nExpected a FROM statement.\n\n");
	
	}
}

success_unsuccess set_check(program *prog, player *user)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Set Check Suite", "Test of set_check()", test_set_check);

		++first_pass;

	}
	//////////////////////////

	if( same_string(prog -> prog_line[prog -> current_word], "SET") ){

		++prog -> current_word;
		set_loop(prog, user);
		return(successful);

	}
	else{
		return(unsuccessful);
	}
}

void set_loop(program *prog, player *user)
{

	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Set Loop Suite", "Test of set_loop()", test_set_loop);

		++first_pass;

	}
	//////////////////////////

	polish_stack pol_stack;

	initialise_pol_stack(&pol_stack);

	var(prog, user);
	interpret_set_variable(user);

	if( same_string(prog -> prog_line[prog -> current_word], ":=") ){

		++prog -> current_word;
		polish(prog, user, &pol_stack);

	} 
	else{

		clear_screen();
		ERROR("\nExpected to see :=.\n\n");

	}
}

void initialise_pol_stack(polish_stack *pol_stack)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Initialising Polish Stack Suite", "Test of initialise_pol_stack()", test_init_pol_stack);

		++first_pass;

	}
	//////////////////////////

	int i;

	for(i = 0; i < MAX_STACK_SIZE; ++i){
		pol_stack -> numbers_stack[i] = 0;
	}

	pol_stack -> current_index = 0;

}

void polish(program *prog, player *user, polish_stack *pol_stack)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Polish Suite", "Test of polish()", test_polish);

		++first_pass;

	}
	//////////////////////////

	if( same_string(prog -> prog_line[prog -> current_word], ";") ){

		check_and_assign_variable(pol_stack, user);
		++prog -> current_word;
		
		return;
	}
	else if( op(prog, user) ){

		op_interpret(prog, user, pol_stack);
		++prog -> current_word;
		polish(prog, user, pol_stack);

	}
	else{

		varnum(prog, user);
		polish_varnum_interpret(prog, user, pol_stack);
		polish(prog, user, pol_stack);

	}
}

success_unsuccess op(program *prog, player *user)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Operand Suite", "Test of op()", test_op);

		++first_pass;

	}
	//////////////////////////

	if( same_string(prog -> prog_line[prog -> current_word], "+") ){
		user -> current_operator = '+';
		return (successful);
	}
	else if( same_string(prog -> prog_line[prog -> current_word], "-") ){
		user -> current_operator = '-';
		return (successful);
	}
	else if( same_string(prog -> prog_line[prog -> current_word], "/") ){
		user -> current_operator = '/';
		return (successful);
	}
	else if( same_string(prog -> prog_line[prog -> current_word], "*") ){
		user -> current_operator = '*';
		return (successful);
	}
	else{
		return(unsuccessful);
	}
}

void varnum(program *prog, player *user)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Varnum Suite", "Test of varnum()", test_varnum);

		++first_pass;

	}
	//////////////////////////

	float number; 
	int scan_checker = 0;

	scan_checker = sscanf(prog -> prog_line[ prog -> current_word ], "%f", &number);

	if(scan_checker == 0){
		var(prog, user);
	}
	else{

		user -> current_constant = number;
		user -> constant_checker = on;
		user -> variable_checker = off;
		++prog -> current_word;

	}

}

void var(program *prog, player *user)
{
	char variable;

	if( sscanf( prog -> prog_line[ prog -> current_word ], "%[A-Z]c", &variable) == 0){

		clear_screen();
		ERROR("\nExpected a variable or number.\n\n");

	}
	else{

		user -> current_variable = variable - 'A';
		user -> variable_checker = on;
		user -> constant_checker = off;
		++prog -> current_word;

	}

	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Var Suite", "Test of var()", test_var);

		++first_pass;

	}
	//////////////////////////
}

void print_SDL_array(player *user, SDL_Simplewin *sw)
{
	//////////////////////////					Testing
	// static int first_pass = 0;

	// if(first_pass == 0){

	// ++first_pass;

	// set_up_test("SDL Suite", "Test of print_SDL_array()", test_SDL_print);

	// }
	//////////////////////////

	int i, j;
	SDL_Rect rectangle;

   	rectangle.w = 1;
   	rectangle.h = 1;

   	sw -> skip_checker = off;

   	for(i = 0; i < WHEIGHT; ++i){
   		for(j = 0; j < WWIDTH; ++j){

   			if(user -> player_board[i][j] == coloured){

   				rectangle.y = i;
   				rectangle.x = j;
   				Neill_SDL_SetDrawColour(sw, WHITE, WHITE, WHITE);
   				SDL_RenderFillRect(sw->renderer, &rectangle);
   				
   			}

   		}
   	}

   	SDL_RenderPresent(sw->renderer);
    SDL_UpdateWindowSurface(sw->win);
    
    do{
    	Neill_SDL_Events(sw);
    }while(sw->skip_checker != on);
}