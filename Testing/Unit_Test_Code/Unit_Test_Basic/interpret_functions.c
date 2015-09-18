#include "turtle_functions.h"

void fd_interpret(player *user)
{

	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("FD Suite (Interpreting)", "Test of fd_interpret()", test_fd_interpret);

		++first_pass;

	}
	//////////////////////////

	if(user -> constant_checker == on){

		draw_angled_line(user, user -> current_constant);

	}
	else if(user -> variable_checker == on){

		check_variable(user);
		draw_angled_line(user, user -> variable_values[ user -> current_variable ]);

	}
	else{

		clear_screen();
		ERROR("\nNeither a constant nor variable was assigned before attempting to move forward.\n\n");

	}

}

void check_variable(player *user)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Check Variable Suite", "Test of check_variable()", test_check_variable);

		++first_pass;

	}
	//////////////////////////

	if( user -> variable_values[ user -> current_variable ] == ERROR_VALUE ){
		clear_screen();
		ERROR("\nYou did not assign a value to the variable before trying to use it.\n\n");
	}
}

void draw_angled_line(player *user, int number_steps)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Draw Angled Line Suite", "Test of draw_angled_line()", test_draw_angled_line);

		++first_pass;

	}
	//////////////////////////

	int i;

	for(i = 0; i < number_steps; ++i){

		if( 0 <= user -> angle && user -> angle < 90 ){
			draw_next_square(i, user, 90, top_right, number_steps);
		}
		else if( 90 <= user -> angle && user -> angle < 180 ){
			draw_next_square(i, user, 180, top_left, number_steps);
		}
		else if( 180 <= user -> angle && user -> angle < 270 ){
			draw_next_square(i, user, 270, bottom_left, number_steps);
		}
		else{
			draw_next_square(i, user, 360, bottom_right, number_steps);
		}

	}

}

void draw_next_square(int hypotenuse_length, player *user, int upper_bound, grid_location grid_loc, int number_steps)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Draw Next Square Suite", "Test of draw_next_square()", test_draw_next_square);

		++first_pass;

	}
	//////////////////////////

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

		drawing_process(user, user -> row - abs(a), user -> col + abs(b), number_steps, hypotenuse_length);

	}
	else if(grid_loc == top_left){

		drawing_process(user, user -> row - abs(a), user -> col - abs(b), number_steps, hypotenuse_length);

	}
	else if(grid_loc == bottom_left){

		drawing_process(user, user -> row + abs(b), user -> col - abs(a), number_steps, hypotenuse_length);

	}
	else{

		drawing_process(user, user -> row + abs(a), user -> col + abs(b), number_steps, hypotenuse_length);

	}
}

void drawing_process(player *user, int new_user_row, int new_user_col, int number_steps, int hypotenuse_length)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Drawing Process Suite", "Test of drawing_process()", test_drawing_process);

		++first_pass;

	}
	//////////////////////////

	if( new_user_row > WHEIGHT || new_user_row < 0 || new_user_col > WWIDTH || new_user_col < 0){
		clear_screen();
		ERROR("\nThe pattern you have attempted to draw falls outside the dimensions of the window.\n\n");
	}
	else{
		user -> player_board[ new_user_row ][ new_user_col ] = coloured;
	}
		
	if(hypotenuse_length == number_steps - 1){
		user -> row = new_user_row;
		user -> col = new_user_col;
	}
}

void lt_rt_interpret(player *user, rt_lt direction)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("LT/ RT Interpreting Suite", "Test of lt_rt_interpret()", test_lt_rt_interpret);

		++first_pass;

	}
	//////////////////////////

	if(user -> constant_checker == on){

		if(direction == lt_dir){
			user -> angle += user -> current_constant;
			adjust_angle(user);
		}
		else{
			user -> angle -= user -> current_constant;
			adjust_angle(user);
		}

	}
	else if(user -> variable_checker == on){

		check_variable(user);

		if(direction == lt_dir){
			user -> angle += user -> variable_values[ user -> current_variable ];
			adjust_angle(user);
		}
		else{
			user -> angle -= user -> variable_values[ user -> current_variable ];
			adjust_angle(user);
		}

	}
}

void adjust_angle(player * user)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Adjust Angle Suite", "Test of adjust_angle()", test_adjust_angle);

		++first_pass;

	}
	//////////////////////////

	if(user -> angle < 0){
		user -> angle = 360 + user -> angle;
	}
}

void op_interpret(program *prog, player *user, polish_stack *pol_stack)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("OP Interpret Suite", "Test of op_interpret()", test_op_interpret);

		++first_pass;

	}
	//////////////////////////

	float result;

	if(pol_stack -> current_index == 0 || pol_stack -> current_index == 1){
		clear_screen();
		ERROR("\nYou are trying to use binary operators within RPN with only one operand.\n\n");
	}

	if(user -> current_operator == '+'){
		result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] + pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ];
	}
	else if(user -> current_operator == '-'){
		result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] - pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ];
	}
	else if(user -> current_operator == '/'){
		result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] / pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ];
	}
	else if(user -> current_operator == '*'){
		result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] * pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ];
	}
	else{
		clear_screen();
		ERROR("\nThe operand you have input has not been registered by the interpreter.\n\n");
	}

	user -> operation_indicator = on;
	pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ] = result;
	pol_stack -> numbers_stack[ pol_stack -> current_index ] = 0;
	pol_stack -> current_index -= 1;
}

void polish_varnum_interpret(program *prog, player *user, polish_stack *pol_stack)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Polish Varnum Interpret Suite", "Test of polish_varnum_interpret()", test_polish_varnum_interpret);

		++first_pass;

	}
	//////////////////////////

	if(user -> constant_checker == on){

		push_to_stack(pol_stack, user -> current_constant);

	}
	else if(user -> variable_checker == on){

		check_variable(user);
		push_to_stack(pol_stack, user -> variable_values[ user -> current_variable ]);

	}
}

void push_to_stack(polish_stack *pol_stack, int constant_for_push)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Push to Stack Suite", "Test of push_to_stack()", test_push_to_stack);

		++first_pass;

	}
	//////////////////////////

	pol_stack -> numbers_stack[ pol_stack -> current_index++ ] = constant_for_push;

}

void interpret_set_variable(player *user)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Interpret Set Variable Suite", "Test of interpret_set_variable()", test_interpret_set_variable);

		++first_pass;

	}
	//////////////////////////

	user -> set_variable = user -> current_variable;
}

void check_and_assign_variable(polish_stack *pol_stack, player *user)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Check and Assign Variable Suite", "Test of check_and_assign_variable()", test_check_and_assign_variable);

		++first_pass;

	}
	//////////////////////////

	if(pol_stack -> current_index != 1){
		clear_screen();
		ERROR("\nThe RPN expression you entered is not complete.\n\n");
	}
	else{

		if( user -> operation_indicator == on){
			user -> variable_values[ user -> set_variable ] = pol_stack -> numbers_stack[ pol_stack -> current_index];
		}
		else{
			user -> variable_values[ user -> set_variable ] = pol_stack -> numbers_stack[ pol_stack -> current_index - 1];
		}

	}
}

void loop_subject_var_interpret(player *user)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Loop Subject Var Interpret Suite", "Test of loop_subject_var_interpret()", test_loop_subject_var_interpret);

		++first_pass;

	}
	//////////////////////////

	++user -> looping_index;

	if( user -> looping_index > MAX_EMBEDDED_LOOPS ){
		clear_screen();
		ERROR("\nThe maximum number of embedded loops has been exceeded.\n\n");
	}
	else{
		user -> looping_array[variable][ user -> looping_index ] = user -> current_variable;
	}

}

void loop_start_var_interpreter(player *user)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Loop Start Var Interpreter Suite", "Test of loop_start_var_interpreter()", test_loop_start_var_interpreter);

		++first_pass;

	}
	//////////////////////////

	if( user -> constant_checker == on ){
		user -> looping_array[ start_number ][ user -> looping_index ] = user -> current_constant;
	}
	else if( user -> variable_checker == on ){
		user -> looping_array[ start_number ][ user -> looping_index ] = user -> variable_values[ user -> current_variable ];
	}

	user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] = user -> looping_array[ start_number ][ user -> looping_index ];

}

void loop_end_var_interpreter(player *user)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Loop End Var Interpreter Suite", "Test of loop_end_var_interpreter()", test_loop_end_var_interpreter);

		++first_pass;

	}
	//////////////////////////

	if( user -> constant_checker == on ){
		user -> looping_array[ end_number ][ user -> looping_index ] = user -> current_constant;
	}
	else if( user -> variable_checker == on ){
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
}

success_unsuccess check_loop_finish(player *user)
{
	//////////////////////////					Testing
	static int first_pass = 0;

	if(first_pass == 0){

		set_up_test("Check Loop Finish Suite", "Test of check_loop_finish()", test_check_loop_finish);

		++first_pass;

	}
	//////////////////////////

	if( user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] == user -> looping_array[ end_number ][ user -> looping_index ] + 1){
		--user -> looping_index;
		return(successful);
	}
	else{
		return(unsuccessful);
	}
}