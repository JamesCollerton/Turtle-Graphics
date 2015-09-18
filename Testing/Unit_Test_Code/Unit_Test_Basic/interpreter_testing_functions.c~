#include "turtle_functions.h"

///////////////////////////////                 INTERPRETER BASED FUNCTIONS

// This is used to test the fd_interpret function. It initialises the variable and constant
// check as being on and off in different combinations and then sees if they are registered by
// the program.
void test_fd_interpret(void)
{
   player user_struct, *user;

   user = &user_struct;

   fd_interpret_case(user, on, off);

   fd_interpret_case(user, off, on);

   fd_interpret_case(user, off, off);

}

void fd_interpret_case(player *user, on_off var_check, on_off const_check)
{

   initialise_user_checkers(user, var_check, const_check);

   interpret_user_checkers(user, var_check, const_check);

}

void initialise_user_checkers(player *user, on_off var_check, on_off const_check)
{
   user -> variable_checker = var_check;
   if(var_check){
      printf("\n\nVariable checker set to be on.\n");
   }

   user -> constant_checker = const_check;
   if(const_check){
      printf("\nConstant checker set to be on.\n");
   }

   if( !(const_check || var_check)){
      printf("\nNeither constant checker nor variable checker set to be on.\n");
   }
}

void interpret_user_checkers(player *user, on_off var_check, on_off const_check)
{
      if(user -> constant_checker == on){

      if(const_check == on){

         CU_PASS();
         printf("\nConstant checker correctly interpreted as on.\n");

      }
      else{

         CU_FAIL();
         printf("\nConstant checker incorrectly interpreted as on.\n");

      }

   }
   else if(user -> variable_checker == on){

      if(var_check == on){

         CU_PASS();
         printf("\nVariable checker correctly interpreted as on.\n");

      }
      else{

         CU_FAIL();
         printf("\nVariable checker incorrectly interpreted as on.\n");

      }

   }
   else{

      if(var_check == off && const_check == off){

         CU_PASS();
         printf("\nError of neither a variable nor constant being set successfully caught.\n\n");

      }
      else{

         CU_FAIL();
         printf("\nError of neither a variable nor constant being set not caught.\n");

      }

   }
}

// This is used to test the check_variable function. A random variable is selected and then
// set to the ERROR_VALUE or an arbitrary value and then put into a function to check the 
// correct thing is registered.
void test_check_variable(void)
{
   player user_struct, *user;

   user = &user_struct;

   //Random variable selected.
   user -> current_variable = rand() % NUM_LETTERS_ALPHABET;

   printf("\n\nValue for current variable set to be error value.\n");
   check_variable_case(user, ERROR_VALUE);

   printf("\nValue for current variable set to be non-error value.\n");
   check_variable_case(user, rand() % ARBITRARY_NUM);

}

void check_variable_case(player *user, int curr_var_val)
{
   user -> variable_values[ user -> current_variable ] = curr_var_val;

   if( user -> variable_values[ user -> current_variable ] == ERROR_VALUE ){
      assert_test(user -> variable_values[ user -> current_variable ] == ERROR_VALUE, "Error value for variable correctly registered.");
   }
   else{
      assert_test(user -> variable_values[ user -> current_variable ] != ERROR_VALUE, "Non-error value for variable correctly registered.\n");
   }
}

// Inputs random angles into the draw_angled_line function and then checks to make sure they are correctly registered in the correct
// range.
void test_draw_angled_line(void)
{
   player user_struct, *user;

   user = &user_struct;

   printf("\n\nAngle set to a random point between 0 and 90.\n");
   draw_angled_line_case(user, rand() % ARBITRARY_NUM, rand() % 90);

   printf("\nAngle set to a random point between 90 and 180.\n");
   draw_angled_line_case(user, rand() % ARBITRARY_NUM, ( rand() % 90 ) + 90);

   printf("\nAngle set to a random point between 180 and 270.\n");
   draw_angled_line_case(user, rand() % ARBITRARY_NUM, ( rand() % 90 ) + 180);

   printf("\nAngle set to a random point between 270 and 360.\n");
   draw_angled_line_case(user, rand() % ARBITRARY_NUM, ( rand() % 90 ) + 270);
}

void draw_angled_line_case(player *user, int number_steps, int angle)
{
   user -> angle = angle;

   int i;

   for(i = 0; i < number_steps; ++i){

      if( 0 <= user -> angle && user -> angle < 90 ){
         CU_ASSERT(0 <= user -> angle && user -> angle < 90);
      }
      else if( 90 <= user -> angle && user -> angle < 180 ){
         CU_ASSERT(90 <= user -> angle && user -> angle < 180);
      }
      else if( 180 <= user -> angle && user -> angle < 270 ){
         CU_ASSERT( 180 <= user -> angle && user -> angle < 270);
      }
      else{
         CU_ASSERT( 270 <= user -> angle && user -> angle < 360);
      }

   }
   printf("\nIf no errors above all angles correctly categorised.\n\n");
}

// Similar thing as above but with the draw_next_square function.
void test_draw_next_square(void)
{
   player user_struct, *user;

   user = &user_struct;

   printf("\n\nAngle set to be in top right corner.\n");
   draw_next_square_case(user, rand() % ARBITRARY_NUM, 90, top_right);

   printf("\n\nAngle set to be in top left corner.\n");
   draw_next_square_case(user, rand() % ARBITRARY_NUM, 180, top_left);

   printf("\n\nAngle set to be in bottom left corner.\n");
   draw_next_square_case(user, rand() % ARBITRARY_NUM, 270, bottom_left);

   printf("\n\nAngle set to be in bottom right corner.\n");
   draw_next_square_case(user, rand() % ARBITRARY_NUM, 360, bottom_right);

}

// Randomly assigns an angle in the correct range and then checks to see where it is registered.
void draw_next_square_case(player *user, int hypotenuse_length, int upper_bound, grid_location grid_loc)
{
   do{
      user -> angle = rand() % upper_bound;
   }while(user -> angle < upper_bound - 90);
   printf("\nAngle set randomly as %d.\n", user -> angle);

   int a, b, temp_angle;

   if( grid_loc != top_right ){

      assert_test( grid_loc != top_right , "Angle correctly registered as not being in top right." );

      temp_angle = upper_bound - user -> angle;

      assert_test( temp_angle = upper_bound - user -> angle , "Temporary angle for trig functions successfully set." );

      a = hypotenuse_length * sin( RADIANS_CONST * temp_angle );
      assert_test( a == (int) (hypotenuse_length * sin( RADIANS_CONST * temp_angle )) , "The 'opposite' (from SOH) successfully assigned." );

      b = hypotenuse_length * cos( RADIANS_CONST * temp_angle );
      assert_test( b == (int) (hypotenuse_length * cos( RADIANS_CONST * temp_angle )) , "The 'adjacent' (from CAH) successfully assigned." );

   }
   else{

      assert_test( grid_loc == top_right , "Angle correctly registered as being in top right." );

      a = hypotenuse_length * sin( RADIANS_CONST * user -> angle );
      assert_test( a == (int) (hypotenuse_length * sin( RADIANS_CONST * user -> angle )), "The 'opposite' (from SOH) successfully assigned." );

      b = hypotenuse_length * cos( RADIANS_CONST * user -> angle );
      assert_test( b == (int) (hypotenuse_length * cos( RADIANS_CONST * user -> angle )) , "The 'adjacent' (from CAH) successfully assigned." );
   }

   if(grid_loc == top_right){
      assert_test( grid_loc == top_right , "Top right grid location successfully registered." );
   }
   else if(grid_loc == top_left){
      assert_test( grid_loc == top_left , "Top left grid location successfully registered." );
   }
   else if(grid_loc == bottom_left){
      assert_test( grid_loc == bottom_left , "Bottom left grid location successfully registered." );
   }
   else{
      assert_test( grid_loc == bottom_right , "Bottom right grid location successfully registered." );
   }
}

// Tries different inputs, both valid and invalid, in the drawing_process function and tests their outputs.
void test_drawing_process(void)
{
   player user_struct, *user;

   user = &user_struct;

   printf("\n\nDefined location, defined hypotenuse length, defined number steps.\n");
   drawing_process_case(user, rand() % WHEIGHT, rand () % WWIDTH, rand() % ARBITRARY_NUM, rand() % ARBITRARY_NUM);

   printf("\n\nUndefined location (over cols), defined hypotenuse length, defined number steps.\n");
   drawing_process_case(user, rand() % WHEIGHT, WWIDTH, rand() % ARBITRARY_NUM, rand() % ARBITRARY_NUM);

   printf("\n\nUndefined location (over rows), defined hypotenuse length, defined number steps.\n");
   drawing_process_case(user, WHEIGHT, rand() % WWIDTH, rand() % ARBITRARY_NUM, rand() % ARBITRARY_NUM);

   printf("\n\nUndefined location (under cols), defined hypotenuse length, defined number steps.\n");
   drawing_process_case(user, rand() % WHEIGHT, -ARBITRARY_NUM, rand() % ARBITRARY_NUM, rand() % ARBITRARY_NUM);

   printf("\n\nUndefined location (under rows), defined hypotenuse length, defined number steps.\n");
   drawing_process_case(user, -ARBITRARY_NUM, rand() % WWIDTH, rand() % ARBITRARY_NUM, rand() % ARBITRARY_NUM);

   printf("\n\nDefined location, hypotenuse length == number steps - 1.\n");
   drawing_process_case(user, rand() % WHEIGHT, rand() % WWIDTH, ARBITRARY_NUM - 1, ARBITRARY_NUM);

}


void drawing_process_case(player *user, int new_user_row, int new_user_col, int hypotenuse_length, int number_steps)
{
   if( new_user_row > WHEIGHT || new_user_row < 0 || new_user_col > WWIDTH || new_user_col < 0){
      assert_test( new_user_row > WHEIGHT || new_user_row < 0 || new_user_col > WWIDTH || new_user_col < 0 , "Location outside of defined area detected." );
   }
   else{
      assert_test( new_user_col <= WWIDTH && new_user_row <= WHEIGHT && new_user_col >= 0 && new_user_row >= 0, "Successfully detected to be inside defined area." );

      if(hypotenuse_length == number_steps - 1){
         assert_test( hypotenuse_length == number_steps - 1 , "Taken the desired number of steps in the correct direction registered." );

         user -> row = new_user_row;
         assert_test( user -> row == new_user_row, "New user position row set." );

         user -> col = new_user_col;
         assert_test( user -> col == new_user_col , "New user position col set.\n" );
      }

   }
}

// Sets a random angle less than 90 and checks to see it is correctly registered in the lt_rt function
// depending on whether or not we treat it as a variable or constant.
void test_lt_rt_interpret(void)
{
   player user_struct, *user;

   user = &user_struct;

   printf("\n\nConstant checker is turned on.\n");
   examine_lt_rt_case(user, on, off, rand() % 90);

   printf("\n\nVariable checker is turned on.\n");
   examine_lt_rt_case(user, off, on, rand() % 90);
}

void examine_lt_rt_case(player *user, on_off const_checker, on_off var_checker, int angle)
{
   printf("\nChecking the LT case.\n");
   lt_rt_interpret_case(user, const_checker, var_checker, angle, lt_dir);

   printf("\nChecking the RT case.\n");
   lt_rt_interpret_case(user, const_checker, var_checker, angle, rt_dir);

   printf("\n");
}

void lt_rt_interpret_case(player *user, on_off const_checker, on_off var_checker, int angle, rt_lt dir)
{
   rt_lt direction = dir;

   user -> constant_checker = const_checker;
   user -> variable_checker = var_checker;
   user -> angle = angle;

   if(user -> constant_checker == on){

      assert_test( user -> constant_checker == on , "Constant checker registered as on." );

      lt_rt_test(user, direction);

   }
   else if(user -> variable_checker == on){

      assert_test( user -> variable_checker == on , "New user position col set." );

      lt_rt_test(user, direction);

   }
}

void lt_rt_test(player *user, rt_lt direction)
{
   int temp = user -> angle;

   if(direction == lt_dir){
      assert_test( direction == lt_dir , "LT interpreted to be on." );

      user -> angle += user -> current_constant;
      assert_test( user -> angle = temp + user -> current_constant , "Angle incremented correctly." );
   }
   else{
      assert_test( direction == rt_dir , "RT interpreted to be on." );

      user -> angle -= user -> current_constant;
      assert_test( user -> angle = temp + user -> current_constant , "Angle incremented correctly." );
   }
}

// Used for testing the adjust_angle functions with a negative and positive angle.
void test_adjust_angle(void)
{
   player user_struct, *user;

   user = &user_struct;

   printf("\n\nAngle set as negative.\n");
   adjust_angle_case(user, -ARBITRARY_NUM);

   printf("\nAngle set as positive.\n");
   adjust_angle_case(user, ARBITRARY_NUM);

}

void adjust_angle_case(player *user, int angle)
{
   int temp = angle;

   user -> angle = angle;

   if(user -> angle < 0){
      assert_test( user -> angle < 0 , "Angle correctly registered as negative." );

      user -> angle = 360 + user -> angle;
      assert_test( user -> angle = 360 + temp, "Angle correctly adjusted for being negative." );
   }
   else{
      assert_test( user -> angle >= 0 , "Angle correctly registered as positive.\n\n" );
   }

}

// Cycles through all the below cases for the op interpreting function.
void test_op_interpret(void)
{
   player user_struct, *user;
   program prog, *prog_point;
   polish_stack pol_stack, *pol_stack_point;

   pol_stack_point = &pol_stack;

   prog_point = &prog;

   user = &user_struct;

   printf("\n\nDefined place in stack, addition operator.\n");
   op_interpret_case(prog_point, user, pol_stack_point, '+', rand() % MAX_STACK_SIZE);

   printf("\n\nDefined place in stack, subtraction operator.\n");
   op_interpret_case(prog_point, user, pol_stack_point, '-', rand() % MAX_STACK_SIZE);

   printf("\n\nDefined place in stack, division operator.\n");
   op_interpret_case(prog_point, user, pol_stack_point, '/', rand() % MAX_STACK_SIZE);

   printf("\n\nDefined place in stack, multiplication operator.\n");
   op_interpret_case(prog_point, user, pol_stack_point, '*', rand() % MAX_STACK_SIZE);

   printf("\n\nUndefined place in stack, addition operator.\n");
   op_interpret_case(prog_point, user, pol_stack_point, '+', 0);

   printf("\n\nUndefined place in stack, addition operator.\n");
   op_interpret_case(prog_point, user, pol_stack_point, '+', 1);

   printf("\n");
}

void op_interpret_case(program *prog, player *user, polish_stack *pol_stack, int operator_symbol, int current_index)
{
   float result;
   int temp;

   pol_stack -> current_index = current_index;
   user -> current_operator = operator_symbol;

   if(pol_stack -> current_index == 0 || pol_stack -> current_index == 1){
      assert_test( pol_stack -> current_index == 0 || pol_stack -> current_index == 1 , "Being at an undefined place in the stack registered." );
      return;
   }

   if(user -> current_operator == '+'){
      assert_test( user -> current_operator == '+' , "Addition symbol as operator correctly registered." );

      result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] + pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ];
      assert_test( result == pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] + pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ] , "Addition correctly performed." );
   }
   else if(user -> current_operator == '-'){
      assert_test( user -> current_operator == '-' , "Subtraction symbol as operator correctly registered." );

      result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] - pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ];
      assert_test( result == pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] - pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ] , "Subtraction correctly performed." );
   }
   else if(user -> current_operator == '/'){
      assert_test( user -> current_operator == '/' , "Division symbol as operator correctly registered." );

      result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] / pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ];
      assert_test( (int) result == (int) (pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] / pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ]) , "Division correctly performed." );
   }
   else if(user -> current_operator == '*'){
      assert_test( user -> current_operator == '*' , "Multiplication symbol as operator correctly registered." );

      result = pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] * pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ];
      assert_test( result == pol_stack -> numbers_stack[ pol_stack -> current_index - 2 ] * pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ] , "Multiplication correctly performed." );
   }
   else{
      return;
   }

   user -> operation_indicator = on;
   assert_test( user -> operation_indicator = on , "Operation indicator turned on to signal to look for operator." );

   pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ] = result;
   assert_test( (int) (pol_stack -> numbers_stack[ pol_stack -> current_index - 1 ]) == (int) (result) , "Top value in stack replaced with result of operation." );

   pol_stack -> numbers_stack[ pol_stack -> current_index ] = 0;
   assert_test( pol_stack -> numbers_stack[ pol_stack -> current_index ] == 0 , "Old top of stack reinitialised to zero." );

   temp = pol_stack -> current_index;
   pol_stack -> current_index -= 1;
   assert_test( pol_stack -> current_index + 1 == temp , "Place in stack taken down by one to be at last result." );
}

// Different cases cycled through that could be fed into the polish_varnum function in the integrated design.
void test_polish_varnum_interpret(void)
{
   player user_struct, *user;

   user = &user_struct;

   printf("\n\nConstant checker set to be on, variable checker set to be off.\n");
   polish_varnum_interpret_case(user, on, off);

   printf("\n\nConstant checker set to be off, variable checker set to be on.\n");
   polish_varnum_interpret_case(user, off, on);

   printf("\n\nConstant checker set to be off, variable checker set to be off.\n");
   polish_varnum_interpret_case(user, off, off);
}

void polish_varnum_interpret_case(player *user, on_off const_checker, on_off var_checker)
{
   user -> constant_checker = const_checker;
   user -> variable_checker = var_checker;

   if(user -> constant_checker == on){
      assert_test( user -> constant_checker == on, "Constant checker successfully registered as on." );
   }
   else if(user -> variable_checker == on){
      assert_test( user -> variable_checker == on, "Variable checker successfully registered as on." );
   }
   else{
      assert_test( user -> variable_checker == off && user -> constant_checker == off, "Both variable and constant checkers registered to be off.\n" );
   }
}

// Sets up a random value to be pushed to the stack and checks if it is successful.
void test_push_to_stack(void)
{
   int constant_for_push = rand();

   polish_stack pol_stack, *pol_stack_point;

   pol_stack_point = &pol_stack;

   pol_stack_point -> current_index = rand() % MAX_STACK_SIZE;

   pol_stack_point -> numbers_stack[ pol_stack_point -> current_index++ ] = constant_for_push;
   assert_test( pol_stack_point -> numbers_stack[ pol_stack_point -> current_index - 1 ] = constant_for_push, "\nConstant successfully pushed to the top of the stack.\n" );
}

// Checks all values from A-Z to see if they successfully map onto places in the variable array.
void test_interpret_set_variable(void)
{
   int i;

   player user_struct, *user;

   user = &user_struct;

   printf("\n");

   for(i = 'A'; i <= 'Z'; ++ i){

      user -> current_variable = i;
      printf("\nThe variable under consideration is %c.\n", i);

      user -> set_variable = user -> current_variable;
      assert_test( user -> set_variable == user -> current_variable, "The current variable has been succesfully entered into the SET category." );

   }

   printf("\n");
}

//Sets up different cases for checking and assigning the variables as below.
void test_check_and_assign_variable(void)
{
   polish_stack pol_stack, *pol_stack_point;
   player user_struct, *user;

   user = &user_struct;

   pol_stack_point = &pol_stack;

   printf("\n\nOperation indicator set to be off, stack not at 1.\n");
   check_and_assign_variable_case(pol_stack_point, user, rand() % MAX_STACK_SIZE, off);

   printf("\n\nOperation indicator set to be off, stack at 1.\n");
   check_and_assign_variable_case(pol_stack_point, user, 1, off);

   printf("\n\nOperation indicator set to be on, stack at 1.\n");
   check_and_assign_variable_case(pol_stack_point, user, 1, on);

   printf("\n");
} 

void check_and_assign_variable_case(polish_stack *pol_stack, player *user, int current_index, on_off op_ind)
{
   pol_stack -> current_index = current_index;
   user -> operation_indicator = op_ind;
   pol_stack -> numbers_stack[ pol_stack -> current_index - 1] = rand();

   if(pol_stack -> current_index != 1){
      assert_test(pol_stack -> current_index != 1 , "The current index of the stack has been registered to not be one." );
   }
   else{

      if( user -> operation_indicator == on){
         assert_test( user -> operation_indicator == on , "The operation indicator has been detected to be on." );

         user -> variable_values[ user -> set_variable ] = pol_stack -> numbers_stack[ pol_stack -> current_index];
         assert_test( user -> variable_values[ user -> set_variable ] == pol_stack -> numbers_stack[ pol_stack -> current_index] , "The desired variable has been updated after an operation.");
      }
      else{
         assert_test(user -> operation_indicator == off , "The operation indicator has been detected to be off." );

         user -> variable_values[ user -> set_variable ] = pol_stack -> numbers_stack[ pol_stack -> current_index - 1];
         assert_test(user -> variable_values[ user -> set_variable ] == pol_stack -> numbers_stack[ pol_stack -> current_index - 1], "The desired variable has not been updated after an operation." );
      }

   }
}

// Tests to see if looping indexes set to be too high are caught by the program.
void test_loop_subject_var_interpret(void)
{
   player user_struct, *user;

   user = &user_struct;

   printf("\n\nValid loop index.\n");
   loop_subject_var_interpret_case(user, rand() % MAX_EMBEDDED_LOOPS);

   printf("\n\nInvalid loop index.\n");
   loop_subject_var_interpret_case(user, MAX_EMBEDDED_LOOPS + 1);
}

void loop_subject_var_interpret_case(player *user, int looping_index)
{

   user -> looping_index = looping_index;

   ++user -> looping_index;
   assert_test(user -> looping_index == looping_index + 1 , "The user looping index has been incremented." );

   if( user -> looping_index > MAX_EMBEDDED_LOOPS ){
      assert_test(user -> looping_index > MAX_EMBEDDED_LOOPS, "Too many embedded loops detected.\n" );
   }
   else{
      assert_test(user -> looping_index <= MAX_EMBEDDED_LOOPS && user -> looping_index > 0, "Valid number of loops detected." );
   }
}

// Looks to see if the looping functions can deal with having both constants and variables used as their TO and FROM
// parts.
void test_loop_start_var_interpreter(void)
{
   player user_struct, *user;

   user = &user_struct;

   printf("\n\nConstant checker set to on, variable checker set to off.\n");
   loop_start_var_interpreter_case(user, on, off);

   printf("\nConstant checker set to off, variable checker set to on.\n");
   loop_start_var_interpreter_case(user, off, on);
}

void loop_start_var_interpreter_case(player *user, on_off const_checker, on_off var_checker)
{
   int variable;

   initialise_start_var_interpreter_case(user, const_checker, var_checker, &variable);

   if( user -> constant_checker == on ){
      assert_test(user -> constant_checker == on , "Constant checker detected to be on." );

      user -> looping_array[ start_number ][ user -> looping_index ] = user -> current_constant;
      assert_test((int) (user -> looping_array[ start_number ][ user -> looping_index ]) == (int) (user -> current_constant), "Start of loop correctly assigned." );

   }
   else if( user -> variable_checker == on ){
      assert_test(user -> variable_checker == on, "Variable checker detected to be on." );

      user -> looping_array[ start_number ][ user -> looping_index ] = user -> variable_values[ user -> current_variable ];
      assert_test((int) (user -> looping_array[ start_number ][ user -> looping_index ]) == (int) (user -> variable_values[ user -> current_variable ]), "Start of loop correctly assigned." );
   }

   user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] = user -> looping_array[ start_number ][ user -> looping_index ];
   assert_test(user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] == user -> looping_array[ start_number ][ user -> looping_index ], "Variable set to same value as start of loop.\n" );
}

void initialise_start_var_interpreter_case(player *user, on_off const_checker, on_off var_checker, int *variable)
{
   user -> constant_checker = const_checker;
   user -> variable_checker = var_checker;
   user -> looping_index = rand() % MAX_EMBEDDED_LOOPS;
   user -> current_variable = rand() % NUM_LETTERS_ALPHABET;

   *variable = rand() % NUM_LETTERS_ALPHABET;
}

void test_loop_end_var_interpreter(void)
{
   player user_struct, *user;

   user = &user_struct;

   printf("\n\nConstant checker set to on, variable checker set to off, valid start and end.\n");
   loop_end_var_interpreter_case(user, on, off, ARBITRARY_NUM, ARBITRARY_NUM - 1);

   printf("\nConstant checker set to off, variable checker set to on, valid start and end.\n");
   loop_end_var_interpreter_case(user, off, on, ARBITRARY_NUM, ARBITRARY_NUM - 1);

   printf("\nConstant checker set to off, variable checker set to on, invalid start and end.\n");
   loop_end_var_interpreter_case(user, off, on, ARBITRARY_NUM - 1, ARBITRARY_NUM);
}

void loop_end_var_interpreter_case(player *user, on_off const_checker, on_off var_checker, int end, int start)
{

   initialise_loop_end_var_interpreter_case(user, const_checker, var_checker, end, start);

   if( user -> constant_checker == on ){
      assert_test(user -> constant_checker == on , "Constant checker detected to be on.");

      user -> looping_array[ end_number ][ user -> looping_index ] = user -> current_constant;
      assert_test( (int) (user -> looping_array[ end_number ][ user -> looping_index ]) == (int) (user -> current_constant), "End of loop correctly assigned.");
   }
   else if( user -> variable_checker == on ){
      assert_test(user -> variable_checker == on, "Variable checker detected to be on.");

      user -> looping_array[ end_number ][ user -> looping_index ] = user -> variable_values[ user -> current_variable ];
      assert_test( (int) (user -> looping_array[ end_number ][ user -> looping_index ] ) == (int) (user -> variable_values[ user -> current_variable] ), "Variable checker detected to be on.");
   }

   if( user -> looping_array[ end_number ][ user -> looping_index ] < user -> looping_array[ start_number ][ user -> looping_index ]){
      assert_test(user -> looping_array[ end_number ][ user -> looping_index ] < user -> looping_array[ start_number ][ user -> looping_index ], "Start of loop registered to be after end.\n");
   }
}

void initialise_loop_end_var_interpreter_case(player *user, on_off const_checker, on_off var_checker, int end, int start)
{
   user -> constant_checker = const_checker;
   user -> variable_checker = var_checker;
   user -> looping_index = rand() % MAX_EMBEDDED_LOOPS;
   user -> current_constant = rand();
   user -> current_variable = rand() % NUM_LETTERS_ALPHABET;
   user -> variable_values[ user -> current_variable ] = rand();

   user -> looping_array[ end_number ][ user -> looping_index ] = end;
   user -> looping_array[ start_number ][ user -> looping_index ] = start;
}

// Checks to make sure the loop finishing logic holds.
void test_check_loop_finish(void)
{
   player user_struct, *user;

   user = &user_struct;

   printf("\n\nLoop not set to be ended.\n");
   check_loop_finish_case(user, ARBITRARY_NUM, ARBITRARY_NUM);

   printf("\n\nLoop set to be ended.\n");
   check_loop_finish_case(user, ARBITRARY_NUM + 1, ARBITRARY_NUM);
}

void check_loop_finish_case(player *user, int curr_var_num, int curr_loop_num)
{
   int temp, variable = rand() % NUM_LETTERS_ALPHABET;
   user -> looping_index = rand() % MAX_EMBEDDED_LOOPS;

   user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] = curr_var_num;
   user -> looping_array[ end_number ][ user -> looping_index ] = curr_loop_num;

   if( user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] == user -> looping_array[ end_number ][ user -> looping_index ] + 1){
      
      assert_test( user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] == user -> looping_array[ end_number ][ user -> looping_index ] + 1 , "End of loop detected.");

      temp = user -> looping_index;
      --user -> looping_index;

      assert_test(temp - 1 == user -> looping_index , "Moved down one step in loops.\n");

      return;
   }
   else{

      assert_test( user -> variable_values[ user -> looping_array[variable][ user -> looping_index ] ] != user -> looping_array[ end_number ][ user -> looping_index ] + 1 , "Not end of loop detected.");
      return;
   }
}
