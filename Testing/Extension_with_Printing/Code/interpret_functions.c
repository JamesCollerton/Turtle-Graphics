// All of these functions tend to be focussed on interpreting the .txt file.

#include "turtle_functions.h"

// This is used to interpret the FD command. Now we begin to use the constant and variable checker functions from before.
// If the constant checker is on then we feed the constant value to the draw_angled_line function, otherwise we feed the variable
// value. If we feed in the variable value we first need to check if it is valid.

void fd_interpret(player *user, printing_board *first_board)
{

	if(user -> constant_checker == on){

		draw_angled_line(user, user -> current_constant, first_board);
	}
	else if(user -> variable_checker == on){

		check_variable(user);
		draw_angled_line(user, user -> variable_values[ user -> current_variable ], first_board);
	}

}

// Now we use the ERROR_VALUE we assigned to all of the variables before. If the variable is at this value then you have tried
// to use a variable before you have assigned it and we treat this as an error.

void check_variable(player *user)
{
	if( user -> variable_values[ user -> current_variable ] == ERROR_VALUE ){
		clear_screen();
		ERROR("\nYou did not assign a value to the variable before trying to use it.\n\n");
	}
}

// Here we draw the angled line. I tried to do something fancy with the trig here in order to be able to print pixel by pixel to 
// make all of the printing really smooth. It treats all of the different quadrants seperately and does different trig depending
// on where you are on the cartesian plane.

// I left these numbers in as they aren't really magic numbers, they're multiples of degrees in a right angle and the code makes
// a lot more sense with them left in there.

void draw_angled_line(player *user, int number_steps, printing_board *first_board)
{
	int i;

	check_number_steps(number_steps);

	for(i = 0; i < number_steps; ++i){

		if( 0 <= user -> angle && user -> angle < 90 ){

			draw_next_square(i, user, 90, top_right, number_steps, first_board);

		}
		else if( 90 <= user -> angle && user -> angle < 180 ){

			draw_next_square(i, user, 180, top_left, number_steps, first_board);

		}
		else if( 180 <= user -> angle && user -> angle < 270 ){

			draw_next_square(i, user, 270, bottom_left, number_steps, first_board);

		}
		else{

			draw_next_square(i, user, 360, bottom_right, number_steps, first_board);

		}

	}

}

// This checks to make sure you're not trying to walk backwards as I interpreted this as not being allowed.

void check_number_steps(int number_steps)
{
	if(number_steps < 0){
		clear_screen();
		ERROR("\nYou cannot walk forwards by a negative amount.\n\n");
	}
}

// Here are the rules for drawing the next square. The way I implemented it was as follows: Say you want to walk 10 steps
// at an angle of 20 degrees. Then you treat this as a triangle with a hypotenuse of 10 and an inside angle of 20 degrees.
// You then cut this triangle into smaller triangles, one with hypotenuse 1, one with hypotenuse 2, one with hypotenuse 3,
// etc. all the way up until 10. For each of these triangles you colour the pixels that make up the hypotenuse, and in doing
// so you colour on a pixel by pixel basis.

// This is basically a method of rewriting SDL_DrawLine so you don't have to colour straight line by straight line but 
// can create a smoother animation. HOWEVER, having done this I realised that it was a bit useless as the CPU can't
// handle making a linked list at the rate I had prescribed and so being able to draw pixel by pixel was, in fact, not that
// helpful. Still, the maths is there and if you printed it as you interpreted it then it would draw lines very smoothly.

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

// This checks to make sure you're not outside of the canvas and errors if you are. It also colours the current space
// on the canvas.

// If you have walked forward the amount that you said you wanted to (in the above example that would be 10 steps) then
// it sets your current position to be there.

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
		printf("\nAssigning a board to the linked list to print at move %d.\n", current_move);

	}
		
	if(hypotenuse_length == number_steps - 1){
		user -> row = new_user_row;
		user -> col = new_user_col;
	}

	++current_move;
}

// This function is called and adds boards to a linked list every 500 or so boards. A board is malloced and
// then put on the end of the latest board. The next board from there is set to NULL.

void assign_board_to_list(player *user, printing_board *first_board)
{

	printing_board *board_to_add = (printing_board *) malloc(sizeof(printing_board));

	if(board_to_add == NULL){
		clear_screen();
		fprintf(stderr, "\nThere was an error mallocing space to add to the linked list of boards.\n\n");
		exit(EXIT_CODE);
	}

	first_board -> latest_board -> next_board = board_to_add;
	first_board -> latest_board = board_to_add;
	printf("\nThe next board has been set and the latest board added to the end of the list.\n");

	board_to_add -> next_board = NULL;
	board_to_add -> latest_board = board_to_add;
	printf("\nThe board on the end of the list has been correctly initialised.\n");

	copy_board_into_list(user, board_to_add);
}

// Copies the components of the current player board into the board in the linked list.

void copy_board_into_list(player *user, printing_board *board_to_add)
{
	int i, j;

	for(i = 0; i < WHEIGHT; ++i){
		for(j = 0; j < WWIDTH; ++j){
			board_to_add -> player_board[i][j] = user -> player_board[i][j];
		}
	}
	printf("\nThe board has been copied into the list.\n");
}

// Again we interpret turning left and turning right. If the constant checker is on then we turn right or left by that
// Constant amount, otherwise we turn right or left by a variable amount.

void lt_rt_interpret(player *user, rt_lt direction)
{

	if(user -> constant_checker == on){

		lt_rt_interpret_case(user, direction, user -> current_constant);

	}
	else if(user -> variable_checker == on){

		check_variable(user);

		lt_rt_interpret_case(user, direction, user -> variable_values[ user -> current_variable ]);

	}

}

// Here we turn left or right depending on the command. If we are turning left then we increment the user's angle by
// the amount, if we are turning right then we decrement the angle by the amount.

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

// This is used to adjust the player's angle. If the user's angle is less than zero then that can cause confusion with
// some earlier functions. However this angle has identical properties to the same angle +360 (as it is periodic) and so
// we just increment by 360 until it is back into the positive. Similar things happen if the angle is over 360, so we just
// modulus by 360 to bring it back into the desired range.

// Again these numbers are left in as the code makes a lot more sense when you see the value 360.

void adjust_angle(player * user)
{
	if(user -> angle < 0){
		do{
			user -> angle = 360 + user -> angle;
		}while(user -> angle < 0);
	}

	if(user -> angle > 360){
		user -> angle = user -> angle % 360;
	}
}

// This is the op interpret part of the program. If the pol_stack is at 0 or 1 then we are trying to use diadic operators
// with only one variable and so it errors. I have interpreted the minus symbol to mean subtract and not negative.

// The last two elements of the stack are popped and the operation is carried out on them, with the result being replaced
// back on the stack.

void op_interpret(program *prog, player *user, polish_stack *pol_stack)
{
	float result;

	if(pol_stack -> current_index == 0 || pol_stack -> current_index == 1){
		clear_screen();
		ERROR("\nYou are trying to use binary operators within RPN with only one operand/ operator defined first.\n\n");
	}

	if(user -> current_operator == '+'){

		result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] + pol_stack -> numbers_stack[ pol_stack -> current_index - 1];

	}
	else if(user -> current_operator == '-'){

		result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] - pol_stack -> numbers_stack[ pol_stack -> current_index - 1];

	}
	else if(user -> current_operator == '/'){

		result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] / pol_stack -> numbers_stack[ pol_stack -> current_index - 1];

	}
	else if(user -> current_operator == '*'){

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

}

// This is used to interpret a varnum within the polish part of the program. If it is a number then the number is pushed to the stack,
// if it is a variable then the variable is pushed to the stack.

void polish_varnum_interpret(program *prog, player *user, polish_stack *pol_stack)
{
	if(user -> constant_checker == on){

		push_to_stack(pol_stack, user -> current_constant);


	}
	else if(user -> variable_checker == on){

		check_variable(user);
		push_to_stack(pol_stack, user -> variable_values[ user -> current_variable ]);

	}
}

// This is used to push a number to the stack at the current index. The index is then incremented for the next number.

void push_to_stack(polish_stack *pol_stack, float constant_for_push)
{

	pol_stack -> numbers_stack[ pol_stack -> current_index++ ] = constant_for_push;

}

// This puts the set variable in the user structure to the current variable after SET has been parsed.

void interpret_set_variable(player *user)
{
	user -> set_variable = user -> current_variable;
}

// If the polish stack has not simplified down to a single value then the RPN expression is not complete. 

// Otherwise the last number in the polish stack is the result of the RPN operations and needs to be put as
// the variable number.

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

// When we detect we have entered a DO loop we increment where we are in the loop stack by one and put in
// the necessary part of the array the variable number, so we know which variable we are looping through.

void loop_subject_var_interpret(player *user)
{

	++user -> looping_index;
	if(user -> looping_index > MAX_EMBEDDED_LOOPS){
		clear_screen();
		ERROR("\nYou have exceeded the maximum number of embedded loops.\n\n");
	}

	user -> looping_array[variable][ user -> looping_index ] = user -> current_variable;

}

// This is used to fill in more of the DO loop array. If the start of the loop has been detected to be a constant then
// the appropriate part of the looping array is set as that. Similar if the start of the loop is a variable.

// The value of the variable in the main part of the program is then set to be the start value of the loop as well.

void loop_start_var_interpreter(player *user)
{
	if( user -> constant_checker == on ){

		user -> looping_array[ start_number ][ user -> looping_index ] = user -> current_constant;

	}
	else if( user -> variable_checker == on ){

		user -> looping_array[ start_number ][ user -> looping_index ] = user -> variable_values[ user -> current_variable ];

	}

	user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] = user -> looping_array[ start_number ][ user -> looping_index ];

}

// This is used to fill in when the end of the DO loop is. It follows the exact same logic as in loop_start_var_interpreter except
// that if it detects we're trying to start at a number below the end it errors.

void loop_end_var_interpreter(player *user)
{
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

// Once we have entered a loop we make a mark of where in the program we are and initialise how many times we have been through this 
// current loop to zero.

void loop_interior_interpreter(player *user, program *prog)
{
	user -> looping_array[ start_word ][ user -> looping_index ] = prog -> current_word;
	user -> looping_array[ current_iteration ][ user -> looping_index ] = 0;
}

// This is used every time we have been through the loop to update the looping array. We add one to how many times we have been through the array
// and update the value of the variable we have been looping through.

void end_loop(player *user)
{

	++user -> looping_array[ current_iteration ][ user -> looping_index ];
	user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] = user -> looping_array[ start_number ][ user -> looping_index ] + 
											      user -> looping_array[ current_iteration ][ user -> looping_index ];

}

// This is used to check if the loop has finished or not. If the variable value we are at is equal to the number it will be at the end
// (e.g. if it is DO A FROM 1 TO 10 and A had been 10 this iteration) then it pops one off the looping stack (decrements one from the 
// looping index) and keeps going.

success_unsuccess check_loop_finish(player *user)
{
	if( user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] == user -> looping_array[ end_number ][ user -> looping_index ] + 1){

		--user -> looping_index;

		return(successful);
	}
	else{
		return(unsuccessful);
	}
}
