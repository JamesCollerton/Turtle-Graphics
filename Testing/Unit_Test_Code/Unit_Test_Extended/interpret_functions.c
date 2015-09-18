#include "turtle_functions.h"

void fd_interpret(player *user, printing_board *first_board)
{

	if(user -> constant_checker == on){

		draw_angled_line(user, user -> current_constant, first_board);
	}
	else if(user -> variable_checker == on){

		//printf("\nRegistered to be moving forward by variable %c\n", user -> current_variable + 'A');

		check_variable(user);
		draw_angled_line(user, user -> variable_values[ user -> current_variable ], first_board);
	}

}

void check_variable(player *user)
{
	if( user -> variable_values[ user -> current_variable ] == ERROR_VALUE ){
		clear_screen();
		ERROR("\nYou did not assign a value to the variable before trying to use it.\n\n");
	}
}

void draw_angled_line(player *user, int number_steps, printing_board *first_board)
{
	int i;

	int first_pass = 0;

	check_number_steps(number_steps);

	for(i = 0; i < number_steps; ++i){

		if( 0 <= user -> angle && user -> angle < 90 ){

			if(first_pass == 0){
				//printf("\nDrawing line, user angle registered to be between 0 and 90. Actual Value: %d.\n", user -> angle );
				//printf("\nMoving forward by: %d (Note: Will be integer as must move forward discrete steps).\n", number_steps );
				++first_pass;
			}

			draw_next_square(i, user, 90, top_right, number_steps, first_board);
		}
		else if( 90 <= user -> angle && user -> angle < 180 ){

			if(first_pass == 0){
				//printf("\nDrawing line, user angle registered to be between 90 and 180. Actual Value: %d.\n", user -> angle );
				//printf("\nMoving forward by: %d (Note: Will be integer as must move forward discrete steps).\n", number_steps );
				++first_pass;
			}

			draw_next_square(i, user, 180, top_left, number_steps, first_board);
		}
		else if( 180 <= user -> angle && user -> angle < 270 ){

			if(first_pass == 0){
				//printf("\nDrawing line, user angle registered to be between 180 and 270. Actual Value: %d.\n", user -> angle );
				//printf("\nMoving forward by: %d (Note: Will be integer as must move forward discrete steps).\n", number_steps );
				++first_pass;
			}

			draw_next_square(i, user, 270, bottom_left, number_steps, first_board);
		}
		else{

			if(first_pass == 0){
				//printf("\nDrawing line, user angle registered to be between 270 and 360. Actual Value: %d.\n", user -> angle );
				//printf("\nMoving forward by: %d (Note: Will be integer as must move forward discrete steps).\n", number_steps );
				++first_pass;
			}

			draw_next_square(i, user, 360, bottom_right, number_steps, first_board);
		}

	}

}

void check_number_steps(int number_steps)
{
	if(number_steps < 0){
		clear_screen();
		ERROR("\nYou cannot walk forwards by a negative amount.\n\n");
	}
}

void draw_next_square(int hypotenuse_length, player *user, int upper_bound, grid_location grid_loc, int number_steps, printing_board *first_board)
{
	int a, b, temp_angle;

	if( grid_loc != top_right ){

		temp_angle = upper_bound - user -> angle;

		a = hypotenuse_length * sin( RADIANS_CONST * temp_angle );
		b = hypotenuse_length * cos( RADIANS_CONST * temp_angle ); 
	}
	else{

		a = hypotenuse_length * sin( RADIANS_CONST * user -> angle );
		b = hypotenuse_length * cos( RADIANS_CONST * user -> angle );
	}

	if(grid_loc == top_right){

		drawing_process(user, user -> row - abs(a), user -> col + abs(b), number_steps, hypotenuse_length, first_board);

	}
	else if(grid_loc == top_left){

		drawing_process(user, user -> row - abs(a), user -> col - abs(b), number_steps, hypotenuse_length, first_board);

	}
	else if(grid_loc == bottom_left){

		drawing_process(user, user -> row + abs(b), user -> col - abs(a), number_steps, hypotenuse_length, first_board);

	}
	else{

		drawing_process(user, user -> row + abs(a), user -> col + abs(b), number_steps, hypotenuse_length, first_board);

	}
}

void drawing_process(player *user, int new_user_row, int new_user_col, int number_steps, int hypotenuse_length, printing_board *first_board)
{
	static int current_move = 0;

	if(new_user_row > WWIDTH || new_user_col > WHEIGHT || new_user_row < 0 || new_user_col < 0){
		clear_screen();
		ERROR("\nThe design you are trying to draw exceeds the dimensions of the canvas.\n\n");
	}

	user -> player_board[ new_user_row ][ new_user_col ] = coloured;

	if(current_move % user -> animation_speed == 0){

		assign_board_to_list(user, first_board);

	}
		
	if(hypotenuse_length == number_steps - 1){
		user -> row = new_user_row;
		user -> col = new_user_col;
	}

	++current_move;
}

void assign_board_to_list(player *user, printing_board *first_board)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Assign Board To List Suite", "Test of assign_board_to_list()", test_assign_board_to_list);

		++first_pass;

	}
	//////////////////////////

	printing_board *board_to_add = (printing_board *) malloc(sizeof(printing_board));

	if(board_to_add == NULL){
		clear_screen();
		fprintf(stderr, "\nThere was an error mallocing space to add to the linked list of boards.\n\n");
		exit(EXIT_CODE);
	}

	first_board -> latest_board -> next_board = board_to_add;
	first_board -> latest_board = board_to_add;

	board_to_add -> next_board = NULL;
	board_to_add -> latest_board = board_to_add;

	copy_board_into_list(user, board_to_add);
}

void copy_board_into_list(player *user, printing_board *board_to_add)
{
	//////////////////////////					Testing

	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Copy Board into List Suite", "Test of copy_board_into_list()", test_copy_board_into_list);

		++first_pass;

	}
	//////////////////////////

	int i, j;

	for(i = 0; i < WHEIGHT; ++i){
		for(j = 0; j < WWIDTH; ++j){
			board_to_add -> player_board[i][j] = user -> player_board[i][j];
		}
	}
}

void lt_rt_interpret(player *user, rt_lt direction)
{

	if(user -> constant_checker == on){

		lt_rt_interpret_case(user, direction, user -> current_constant);

	}
	else if(user -> variable_checker == on){

		check_variable(user);

		lt_rt_interpret_case(user, direction, user -> variable_values[ user -> current_variable ]);

	}

	//printf("\nNew angle %d (Note: Will be integer as angles measured as discrete degrees).\n", user -> angle);
}

void lt_rt_interpret_case(player *user, rt_lt direction, float increment_constant)
{
	if(direction == lt_dir){
		user -> angle += increment_constant;
		adjust_angle(user);
	}
	else{
		user -> angle -= increment_constant;
		adjust_angle(user);
	}
}

void adjust_angle(player * user)
{
	if(user -> angle < 0){
		do{
			user -> angle = 360 + user -> angle;
		}while(user -> angle < 0);
	}

	if(user -> angle > 360){
		//printf("\nNew angle %d (Note: Will be integer as angles measured as discrete degrees).\n", user -> angle);
		user -> angle = user -> angle % 360;
	}
}

void op_interpret(program *prog, player *user, polish_stack *pol_stack)
{
	float result;

	if(pol_stack -> current_index == 0 || pol_stack -> current_index == 1){
		clear_screen();
		ERROR("\nYou are trying to use binary operators within RPN with only one operand/ operator defined first.\n\n");
	}

	//printf("\n\nStack stands at :\n");
	//for(int i = 0; i < pol_stack -> current_index; ++i){
		//printf(" %f ", pol_stack -> numbers_stack[ i ]);
	//}
	//printf("\nAt position: %d\n\n", pol_stack -> current_index);

	if(user -> current_operator == '+'){

		//printf("\nLast two numbers on the polish stack (%f and %f) added together.\n", pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ], pol_stack -> numbers_stack[ pol_stack -> current_index - 1]);

		result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] + pol_stack -> numbers_stack[ pol_stack -> current_index - 1];
	}
	else if(user -> current_operator == '-'){

		//printf("\nLast two numbers on the polish stack (%f and %f) subtracted from each other.\n", pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ], pol_stack -> numbers_stack[ pol_stack -> current_index - 1]);

		result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] - pol_stack -> numbers_stack[ pol_stack -> current_index - 1];
	}
	else if(user -> current_operator == '/'){

		//printf("\nLast two numbers on the polish stack (%f and %f) divided.\n", pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ], pol_stack -> numbers_stack[ pol_stack -> current_index - 1]);

		result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] / pol_stack -> numbers_stack[ pol_stack -> current_index - 1];
	}
	else if(user -> current_operator == '*'){

		//printf("\nLast two numbers on the polish stack (%f and %f) multiplied together.\n", pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ], pol_stack -> numbers_stack[ pol_stack -> current_index - 1]);

		result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] * pol_stack -> numbers_stack[ pol_stack -> current_index - 1];
	}
	else{
		clear_screen();
		ERROR("\nThe operand you have input has not been registered by the interpreter.\n\n");
	}

	user -> operation_indicator = on;
	pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] = result;
	pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ] = 0;
	pol_stack -> current_index -= 1;

	//printf("\nValue %f pushed to Polish stack at position %d.\n", result,  pol_stack -> current_index - 1);
	//printf("\n\nStack stands at :\n");
	for(int i = 0; i < pol_stack -> current_index; ++i){
		//printf(" %f ", pol_stack -> numbers_stack[ i ]);
	}
	//printf("\nAt position: %d\n\n", pol_stack -> current_index);
}

void polish_varnum_interpret(program *prog, player *user, polish_stack *pol_stack)
{
	if(user -> constant_checker == on){

		//printf("\nValue %f pushed to Polish stack.\n", user -> current_constant );

		push_to_stack(pol_stack, user -> current_constant);

	}
	else if(user -> variable_checker == on){

		//printf("\nValue %f pushed to Polish stack.\n", user -> variable_values[ user -> current_variable ] );

		check_variable(user);
		push_to_stack(pol_stack, user -> variable_values[ user -> current_variable ]);

	}
}

void push_to_stack(polish_stack *pol_stack, float constant_for_push)
{

	pol_stack -> numbers_stack[ pol_stack -> current_index++ ] = constant_for_push;

}

void interpret_set_variable(player *user)
{
	user -> set_variable = user -> current_variable;
}

void check_and_assign_variable(polish_stack *pol_stack, player *user)
{
	if(pol_stack -> current_index != 1){
		clear_screen();
		ERROR("\nThe RPN expression you entered is not complete.\n\n");
	}
	else{

		if( user -> operation_indicator == on ){

			user -> variable_values[ user -> set_variable ] = pol_stack -> numbers_stack[0];
		}
		else{
			
			user -> variable_values[ user -> set_variable ] = pol_stack -> numbers_stack[0];
		}

	}
}

void loop_subject_var_interpret(player *user)
{

	++user -> looping_index;
	if(user -> looping_index > MAX_EMBEDDED_LOOPS){
		clear_screen();
		ERROR("\nYou have exceeded the maximum number of embedded loops.\n\n");
	}

	//printf("\nCURRENTLY INSIDE LOOP: %d.\n", user -> looping_index);

	user -> looping_array[variable][ user -> looping_index ] = user -> current_variable;

}

void loop_start_var_interpreter(player *user)
{
	if( user -> constant_checker == on ){
		//printf("\nThe start of the loop has been registered to be: %d.\n", (int) user -> current_constant);
		user -> looping_array[ start_number ][ user -> looping_index ] = user -> current_constant;
	}
	else if( user -> variable_checker == on ){

		//printf("\nThe start of the loop has been registered to be variable %c with value %d.\n", user -> current_variable + 'A', (int) (user -> variable_values[ user -> current_variable]) );
		user -> looping_array[ start_number ][ user -> looping_index ] = user -> variable_values[ user -> current_variable ];
	}

	user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] = user -> looping_array[ start_number ][ user -> looping_index ];

}

void loop_end_var_interpreter(player *user)
{
	if( user -> constant_checker == on ){
		//printf("\nThe end of the loop has been registered to be: %d.\n", (int) user -> current_constant);
		user -> looping_array[ end_number ][ user -> looping_index ] = user -> current_constant;
	}
	else if( user -> variable_checker == on ){
		//printf("\nThe end of the loop has been registered to be variable %c with value %d.\n", user -> current_variable + 'A', (int) (user -> variable_values[ user -> current_variable]) );
		user -> looping_array[ end_number ][ user -> looping_index ] = user -> variable_values[ user -> current_variable ];
	}

	if( user -> looping_array[ end_number ][ user -> looping_index ] < user -> looping_array[ start_number ][ user -> looping_index ]){
		clear_screen();
		ERROR("\nThe upper bound to your DO loop is below the initial value.\n\n");
	}
}

void loop_interior_interpreter(player *user, program *prog)
{
	user -> looping_array[ start_word ][ user -> looping_index ] = prog -> current_word;
	user -> looping_array[ current_iteration ][ user -> looping_index ] = 0;
}

void end_loop(player *user)
{

	++user -> looping_array[ current_iteration ][ user -> looping_index ];
	user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] = user -> looping_array[ start_number ][ user -> looping_index ] + 
																						  user -> looping_array[ current_iteration ][ user -> looping_index ];

	//printf("\nNow on iteration %d/%d for loop %d.\n", user -> looping_array[ current_iteration ][ user -> looping_index ], user -> looping_array[ end_number ][ user -> looping_index ], user -> looping_index);
}

success_unsuccess check_loop_finish(player *user)
{
	if( user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] == user -> looping_array[ end_number ][ user -> looping_index ] + 1){
		//printf("\nLOOP %d REGISTERED TO HAVE FINISHED.\n", user -> looping_index);
		--user -> looping_index;
		return(successful);
	}
	else{
		return(unsuccessful);
	}
}