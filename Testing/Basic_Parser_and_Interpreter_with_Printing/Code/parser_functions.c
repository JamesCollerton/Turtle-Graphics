#include "turtle_functions.h"

void check_command_line_arguments(int argc)
{
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

	printf("\nCorrect number of arguments from command line registered.\n");
}

void clear_screen(void)
{
	int clear_screen_checker;

	clear_screen_checker = system("clear");

	if(clear_screen_checker != CLEAR_SUCCESS){
		fprintf(stderr, "\nThere was an error clearing the screen.\n\n");
		exit(1);
	}

	printf("\nScreen successfully cleared.\n");
}

void initialise_program(program *prog)
{
	int i;

	prog -> current_word = 0;
	printf("\nCurrent word set to zero.\n");

	prog -> num_lines_in_file = 0;
	printf("\nNumber of lines in file set to zero.\n");

	for(i = 0; i < MAX_NUM_LINES; ++i){
		prog -> prog_line[i][0] = '\0';
	}
	printf("\nAll of program in program structure set to end string characters.\n");
}

void initialise_player(player *user)
{
	int i, j;

	for(i = 0; i < WHEIGHT; ++i){
		for(j = 0; j < WWIDTH; ++j){
			user -> player_board[i][j] = uncoloured;
		}
	}
	printf("\nAll parts of board set to uncoloured.\n");

	for(i = 0; i < START_ITERATION_END; ++i){
		for(j = 0; j < MAX_EMBEDDED_LOOPS; ++j){
			user -> looping_array[i][j] = 0;
		}
	}
	printf("\nAll parts of looping array set to zero.\n");

	for(i = 0; i < NUM_LETTERS_ALPHABET; ++i){
		user -> variable_values[i] = ERROR_VALUE;
	}
	printf("\nAll values in looping array set to zero.\n");

	user -> row = MIDDLE_OF_BOARD;
	user -> col = MIDDLE_OF_BOARD;
	user -> angle = 0;
	user -> player_board[MIDDLE_OF_BOARD][MIDDLE_OF_BOARD] = coloured;
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

	printf("\nRemaining components set to initial values.\n");

}

void open_program_file(char *filename, program *prog)
{
	FILE *prog_file = NULL;
	int i = 0;

	if( (prog_file = fopen(filename, "r")) == NULL){
		clear_screen();
		fprintf(stderr, "\nThere was an error reading in the file.\n\n");
		exit(1);
	}
	else{

		printf("\nFile successfully opened.\n");

		while( fscanf(prog_file, "%s", prog -> prog_line[i]) == 1 ){
			i++;
			if(i > MAX_NUM_LINES){
				clear_screen();
				fprintf(stderr, "\nThe number of commands in the file has exceeded the recognised amount.\n\n");
				exit(1);
			}
		}
	}

	printf("\nCorrect number of commands scanned: %d.\n", i);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	prog -> num_lines_in_file = i;
	fclose(prog_file);
}

void parse_text_and_interpret(program *prog, player *user)
{
	if( ! (same_string(prog -> prog_line[prog -> current_word], "{") ) ){
		clear_screen();
		ERROR("\nNo starting brace.\n\n");
	}

	++prog -> current_word;
	printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

	instrctlist(prog, user);

	print_parsed_text(prog);

}

success_unsuccess same_string(char *string_one, char *string_two)
{
	if( strcmp(string_one, string_two) == 0 ){
		return(successful);
	}
	else{
		return(unsuccessful);
	}
}

void print_parsed_text(program *prog)
{
	int i;

	clear_screen();

	printf("Your text was parsed as follows:\n\n");

	for(i = 0; i < prog -> num_lines_in_file; ++i){
		printf("%s\n", prog -> prog_line[i]);
	}

	printf("\n");
}

void instrctlist(program *prog, player *user)
{
	if( same_string(prog -> prog_line[prog -> current_word], "}")){
		printf("\n} Character registered.\n");

		++prog -> current_word;
		printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

		return;
	}

	instruction(prog, user);

	instrctlist(prog, user);
}

void instruction(program *prog, player *user)
{
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
		ERROR("\nEITHER: Expected an instruction or end bracket OR error with polish expression.\n\n");
	}
}

success_unsuccess fd(program *prog, player *user)
{
	if( same_string(prog -> prog_line[prog -> current_word], "FD") ){
		printf("\nFD registered.\n");

		++prog -> current_word;
		printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

		varnum(prog, user);

		return(successful);
	}
	else{
		return(unsuccessful);
	}
}

success_unsuccess lt_rt(program *prog, player *user, rt_lt direction, char *command)
{
	if( same_string(prog -> prog_line[prog -> current_word], command) ){
		printf("\n%s registered.\n", command);

		++prog -> current_word;
		printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

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
	if( same_string(prog -> prog_line[prog -> current_word], "DO") ){
		printf("\nDO registered.\n");

		++prog -> current_word;
		printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

		do_loop(prog, user);

		return(successful);
	}
	else{
		return(unsuccessful);
	}
}

void do_loop(program *prog, player *user)
{

	var(prog, user);
	loop_subject_var_interpret(user);

	if( same_string(prog -> prog_line[prog -> current_word], "FROM") ){
		printf("\nFROM registered.\n");

		++prog -> current_word;
		printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

		varnum(prog, user);
		loop_start_var_interpreter(user);

		if( same_string(prog -> prog_line[prog -> current_word], "TO") ){
			printf("\nTO registered.\n");

			++prog -> current_word;
			printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

			varnum(prog, user);
			loop_end_var_interpreter(user);

				if( same_string( prog -> prog_line[prog -> current_word], "{" ) ){
					printf("\n{ registered.\n");

					++prog -> current_word;
					printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

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

	if( same_string(prog -> prog_line[prog -> current_word], "SET") ){
		printf("\nSET registered.\n");

		++prog -> current_word;
		printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

		set_loop(prog, user);
		return(successful);

	}
	else{
		return(unsuccessful);
	}
}

void set_loop(program *prog, player *user)
{
	polish_stack pol_stack;

	initialise_pol_stack(&pol_stack);

	var(prog, user);
	interpret_set_variable(user);

	if( same_string(prog -> prog_line[prog -> current_word], ":=") ){
		printf("\n:= Character registered.\n");

		++prog -> current_word;
		printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

		polish(prog, user, &pol_stack);

	} 
	else{

		clear_screen();
		ERROR("\nExpected to see :=.\n\n");

	}
}

void initialise_pol_stack(polish_stack *pol_stack)
{
	int i;

	for(i = 0; i < MAX_STACK_SIZE; ++i){
		pol_stack -> numbers_stack[i] = 0;
	}
	printf("\nPolish stack initialised.\n");

	pol_stack -> current_index = 0;

}

void polish(program *prog, player *user, polish_stack *pol_stack)
{
	if( same_string(prog -> prog_line[prog -> current_word], ";") ){
		printf("\n; character has been registered.\n");

		check_and_assign_variable(pol_stack, user);
		
		++prog -> current_word;
		printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);
		
		return;
	}
	else if( op(prog, user) ){
		op_interpret(prog, user, pol_stack);

		++prog -> current_word;
		printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

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
	if( same_string(prog -> prog_line[prog -> current_word], "+") ){
		printf("\n+ symbol registered.\n");
		user -> current_operator = '+';
		return (successful);
	}
	else if( same_string(prog -> prog_line[prog -> current_word], "-") ){
		printf("\n- symbol registered.\n");
		user -> current_operator = '-';
		return (successful);
	}
	else if( same_string(prog -> prog_line[prog -> current_word], "/") ){
		printf("\n/ symbol registered.\n");
		user -> current_operator = '/';
		return (successful);
	}
	else if( same_string(prog -> prog_line[prog -> current_word], "*") ){
		printf("\n* symbol registered.\n");
		user -> current_operator = '*';
		return (successful);
	}
	else{
		return(unsuccessful);
	}
}

void varnum(program *prog, player *user)
{
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

		printf("\nConstant registered as: %f.\n", number);

		++prog -> current_word;
		printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

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

		printf("\nVariable registered as: %c.\n", variable);

		++prog -> current_word;
		printf("\nProgram word incremented, now at word: %d, command: %s.\n", prog -> current_word, prog -> prog_line[prog -> current_word]);

	}
}

void print_SDL_array(player *user, SDL_Simplewin *sw)
{
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
   				Neill_SDL_SetDrawColour(sw, 255, 255, 255);
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