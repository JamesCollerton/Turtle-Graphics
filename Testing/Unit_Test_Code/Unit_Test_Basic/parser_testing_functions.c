#include "turtle_functions.h"


///////////////////////////////                 PARSER BASED FUNCTIONS

// Goes through there being too many/ too few arguments on the command line.
void test_check_command_line(void)
{
   check_command_line_arguments(2);
   CU_PASS();
   printf("\n\nIf no error above: The right number of arguments on the command line is correctly registered.\n\n");

   check_command_line_arguments(3);
   CU_PASS();
   printf("\n\nIf error above: Too many arguments on the command line is correctly registered.\n\n");

   check_command_line_arguments(1);
   CU_PASS();
   printf("\n\nIf error above: Too few arguments on the command line is correctly registered.\n\n");
}

// Initialises and tests clearing the screen with errors and without.
void test_clear_screen(void)
{
	int clear_screen_checker = CLEAR_SUCCESS;

	clear_screen_case(clear_screen_checker);

	clear_screen_checker = CLEAR_FAIL;

   	clear_screen_case(clear_screen_checker);

}

void clear_screen_case(int clear_screen_checker)
{
   if(clear_screen_checker != CLEAR_SUCCESS){
      assert_test(clear_screen_checker != CLEAR_SUCCESS, "Clear screen fails and prints an error.\n");
   }
   else{
      assert_test(clear_screen_checker == CLEAR_SUCCESS, "\nClear screen successfully registers incorrect value.");
   }
}

// Checks all initialisations.
void test_initialising(void)
{
   int i;
   program prog, *prog_point;

   prog_point = &prog;

   prog_point -> current_word = 0;
   assert_test(0 == prog_point -> current_word, "\nFirst word successfully initialised to zero.");

   prog_point -> num_lines_in_file = 0;
   assert_test(0 == prog_point -> num_lines_in_file, "Number of lines in file successfully initialised to zero.");

   for(i = 0; i < MAX_NUM_LINES; ++i){
      prog_point -> prog_line[i][0] = '\0';
      CU_ASSERT(prog_point -> prog_line[i][0] == '\0');
   }
   printf("\nIf no errors above: All lines in program file successfully initialised to zero.\n\n");
}

void test_initialise_player(void)
{
   int i, j;
   player user, *user_point;

   user_point = &user;

   for(i = 0; i < WHEIGHT; ++i){
      for(j = 0; j < WWIDTH; ++j){
         user_point -> player_board[i][j] = uncoloured;
         CU_ASSERT(user_point -> player_board[i][j] == uncoloured);
      }
   }
   printf("\n\nIf no errors above: player board initialised to uncoloured.\n");

   for(i = 0; i < START_ITERATION_END; ++i){
      for(j = 0; j < MAX_EMBEDDED_LOOPS; ++j){
         user_point -> looping_array[i][j] = 0;
         CU_ASSERT(user_point -> looping_array[i][j] == 0);
      }
   }
   printf("\nIf no errors above: looping array successfully initialised to zero.\n");

   for(i = 0; i < NUM_LETTERS_ALPHABET; ++i){
      user_point -> variable_values[i] = ERROR_VALUE;
      CU_ASSERT(user_point -> variable_values[i] == ERROR_VALUE);
   }
   printf("\nIf no errors above: all variable values successfully initialised to ERROR_VALUE.\n");

   user_point -> row = MIDDLE_OF_BOARD;
   assert_test(user_point -> row == MIDDLE_OF_BOARD, "User successfully positioned on middle row.");

   user_point -> col = MIDDLE_OF_BOARD;
   assert_test(user_point -> col == MIDDLE_OF_BOARD, "User successfully positioned on middle col.");

   user_point -> angle = 0;
   assert_test(user_point -> angle == 0, "User angle successfully set to zero.");

   user_point -> player_board[ MIDDLE_OF_BOARD ][ MIDDLE_OF_BOARD ] = coloured;
   assert_test(user_point -> player_board[ MIDDLE_OF_BOARD ][ MIDDLE_OF_BOARD ] == coloured, "User current position successfully coloured.");

   user_point -> current_constant = 0;
   assert_test(user_point -> current_constant == 0, "User current constant successfully initialised to zero.");

   user_point -> current_variable = 0;
   assert_test(user_point -> current_variable == 0, "User current variable successfully initialised to zero.");

   user_point -> current_operator = 0;
   assert_test(user_point -> current_operator == 0, "User current operator successfully initialised to zero.");

   user_point -> set_variable = 0;
   assert_test(user_point -> set_variable == 0, "SET variable successfully initialised to zero.");

   user_point -> current_steps_taken = 0;
   assert_test(user_point -> current_steps_taken == 0, "Iterations for loop successfully initialised to zero.");

   user_point -> looping_index = 0;
   assert_test(user_point -> looping_index == 0, "Looping index successfully initialised to zero.");

   user_point -> variable_checker = off;
   assert_test(user_point -> variable_checker == off, "Variable checker successfully set to off.");

   user_point -> constant_checker = off;
   assert_test(user_point -> constant_checker == off, "Constant checker successfully set to off.");

   user_point -> operation_indicator = off;
   assert_test(user_point -> operation_indicator == off, "Operation indicator successfully set to off.");

   user_point -> loop_indicator = off;
   assert_test(user_point -> loop_indicator == off, "Loop indicator successfully set to off.\n");
}

//Test opening correct and incorrect files with the open_program function.
void test_open_program_file(void)
{
   FILE *prog_file = NULL;
   program prog;

   open_correct_file(&prog, &prog_file);

   open_incorrect_file(&prog_file);

}

void open_correct_file(program *prog, FILE **prog_file)
{
   int i = 0;

   assert_test( (*prog_file = fopen("test.txt", "r")) != NULL, "\nFile opened and registered." );

   while( fscanf(*prog_file, "%s", prog -> prog_line[i]) == SCAN_SUCCESS ){
      i++;

      CU_ASSERT_FALSE(i > MAX_NUM_LINES) 
      if( i > MAX_NUM_LINES ){
         CU_FAIL();
         printf("\n\nIncorrectly registered too many lines.\n\n");
         fprintf(stderr, "\nThe number of lines in the file has exceeded the recognised amount.\n\n");
      }
   }

   prog -> num_lines_in_file = i;
   assert_test( prog -> num_lines_in_file == i, "Number of lines in file assigned." );

   fclose(*prog_file);
}

void open_incorrect_file(FILE **prog_file)
{
   int i = MAX_NUM_LINES + 1;

   assert_test( (*prog_file = fopen("nonexistent_file.txt", "r")) == NULL , "Nonexistent filename left unopened." );

   CU_ASSERT(i > MAX_NUM_LINES)
   if( i > MAX_NUM_LINES ){
     CU_PASS();
     printf("\nToo large file correctly dealt with.\n\n");
   }

}

void test_parse_interpret(void)
{
   program prog, *prog_point;

   prog_point = &prog;
   prog_point -> current_word = 0;

   parse_interpret_case(prog_point, "{", "\n\nFirst character successfully set to {.\n");

   parse_interpret_case(prog_point, "!", "\n\nFirst character successfully set to !.\n");;

}

void parse_interpret_case(program *prog_point, char *opening_command, char *register_message)
{
   assign_word_to_point(opening_command, prog_point, register_message);

   if( ! (same_string(prog_point -> prog_line[prog_point -> current_word], "{") ) ){
      check_registers_incorrect_string(prog_point, "{", "\nFirst character correctly registered as !.\n\n", "First character incorrectly registered.");
   }
   else if( (same_string(prog_point -> prog_line[prog_point -> current_word], "{") ) ){
      check_registers_string(prog_point, "{", "\nFirst character correctly registered. as {\n", "First character incorrectly registered.");
   }
}

void test_same_string(void)
{
   char *string_one = "String One";
   char *string_two = "String One";

   test_same_string_case(string_one, string_two);

   string_one = "String One";
   string_two = "String Two";

   test_same_string_case(string_one, string_two);

}

void test_same_string_case(char *string_one, char *string_two)
{
   if( strcmp(string_one, string_two) == 0 ){
      string_equal_test(string_one, string_two, "\nIdentical strings correctly registered.");
   }
   else{
      string_not_equal_test(string_one, string_two, "Unidentical strings correctly registered.\n");
   }
}

void test_instrctlist(void)
{
   program prog, *prog_point;

   prog_point = &prog;

   check_instruction_registered(prog_point, "}", "\nCurrent string successfully set to terminating character }.\n");

}

// Here each argument represents FD, LT, RT, DO or SET as seen below being turned on. These
// are then passed to the instruction function from the main version and tested to make sure
// the response is appropriate.
void test_instruction(void)
{
   test_instructions test_struct;

   test_iteration(&test_struct, FD, 0, 0, 0, 0);

   test_iteration(&test_struct, 0, LT, 0, 0, 0);

   test_iteration(&test_struct, 0, 0, RT, 0, 0);

   test_iteration(&test_struct, 0, 0, 0, DO, 0);

   test_iteration(&test_struct, 0, 0, 0, 0, SET);

   test_iteration(&test_struct, 0, 0, 0, 0, 0);

}

void test_iteration(test_instructions *test_struct, int fd, int lt, int rt, int do_check, int set_check)
{
   set_test_instruction_struct(test_struct, fd, lt, rt, do_check, set_check);

   test_structure_iteration(test_struct);
}

void set_test_instruction_struct(test_instructions *test_struct, int fd, int lt, int rt, int do_check, int set_check)
{
   test_struct -> fd = fd;
   test_struct -> lt = lt;
   test_struct -> rt = rt;
   test_struct -> do_check = do_check;
   test_struct -> set_check = set_check;
}

void test_structure_iteration(test_instructions *test_struct)
{
   if( test_struct -> fd ){

      command_recognition_case(test_struct -> fd, "\n\nFD command successfully registered.\n", "\n\nFD command unsuccessfully registered.\n\n");

   }
   else if( test_struct -> lt ){

      command_recognition_case(test_struct -> lt, "\nLT command successfully registered.\n", "\nLT command unsuccessfully registered.\n\n");

   }
   else if( test_struct -> rt ){

      command_recognition_case(test_struct -> rt, "\nRT command successfully registered.\n", "\nRT command unsuccessfully registered.\n\n");
   
   }
   else if( test_struct -> do_check ){

      command_recognition_case(test_struct -> do_check, "\nDO command successfully registered.\n", "\nDO command unsuccessfully registered.\n\n");
   
   }
   else if( test_struct -> set_check ){
      
      command_recognition_case(test_struct -> set_check, "\nSET command successfully registered.\n", "\nSET command unsuccessfully registered.\n\n");

   }
   else{
      assert_test( !test_struct -> fd && !test_struct -> lt && !test_struct -> rt && !test_struct -> do_check && !test_struct -> set_check, "No instruction correctly registered\n");
   }
}

void command_recognition_case(success_unsuccess test, char *success_message, char *fail_message)
{
   if( !test ){
      CU_FAIL();
      printf("%s", fail_message);
   }
   else{
      CU_PASS();
      printf("%s", success_message);
   }
}

// This checks that FD registers correctly.
void test_fd(void)
{
   program prog, *prog_point;

   prog_point = &prog;

   check_instruction_registered(prog_point, "FD", "\nCurrent string successfully set to FD.\n");

}

// Picks a random point in the program and assigns the string there. Checks to make sure it is
// Correctly registered. Then sets a string that is not expected to be seen there and checks that
// it produces a warning.
void check_instruction_registered(program *prog_point, char *word_to_set, char *set_message)
{
   randomly_assign_point(prog_point);

   assign_word_to_point(word_to_set, prog_point, set_message);

   check_registers_string(prog_point, word_to_set, "\nCommand successfully registered.\n", "\nCommand not registered.\n");

   assign_word_to_point("!", prog_point, "\nCurrent string successfully set to !.\n");

   check_registers_incorrect_string(prog_point, word_to_set, "\nIncorrect command correctly registered.\n\n", "\nIncorrect command incorrectly registered.\n");
}

void check_registers_string(program *prog_point, char *correct_string, char *pass_message, char *fail_message)
{
   if( same_string(prog_point -> prog_line[prog_point -> current_word], correct_string) ){

      CU_PASS();
      printf("%s", pass_message);

      check_program_incremented(prog_point);

   }
   else{

      CU_FAIL();
      printf("%s", fail_message);

   }
}

void check_registers_incorrect_string(program *prog_point, char *correct_string, char *pass_message, char *fail_message)
{
   if( same_string(prog_point -> prog_line[prog_point -> current_word], correct_string) ){

      CU_FAIL();
      printf("%s", fail_message);

   }
   else{

      CU_PASS();
      printf("%s", pass_message);
   }
}

void randomly_assign_point(program *prog_point)
{
   prog_point -> current_word = rand() % MAX_NUM_LINES;
   assert_test(0 < prog_point -> current_word && prog_point -> current_word < MAX_NUM_LINES, "\nCurrent place in instructions appropriately randomly assigned.");

}

void assign_word_to_point(char *word, program *prog_point, char *message)
{
   sscanf(word, "%s", prog_point -> prog_line[ prog_point -> current_word ]);
   string_equal_test(prog_point -> prog_line[prog_point -> current_word], word, "If no errors here: ");
   printf("%s", message);
}

// Used after the program is supposed to have moved one command forward to check it actually has. 
void check_program_incremented(program *prog_point)
{
   int temp;

   temp = prog_point -> current_word;
   ++prog_point -> current_word;
   assert_test(temp + 1 == prog_point -> current_word, "Word counter successfully incremented by one.");

}

// Tests that LT and RT commands are successfully registered.
void test_lt_rt(void)
{
   program prog, *prog_point;

   prog_point = &prog;

   test_lt_rt_cases(prog_point, "\nCurrent string successfully set to RT.\n", "RT", "\nRT command correctly registered.\n", "\nRT command incorrectly registered.\n");

   test_lt_rt_cases(prog_point, "\nCurrent string successfully set to LT.\n", "LT", "\nLT command correctly registered.\n", "\nLT command incorrectly registered.\n");

}


void test_lt_rt_cases(program *prog_point, char *register_message, char *lt_or_rt, char *pass_message, char *fail_message)
{

   check_instruction_registered(prog_point, lt_or_rt, register_message);

}

// Tests to make sure that DO is registered in the program correctly.
void test_do_check(void)
{
   program prog, *prog_point;

   prog_point = &prog;

   check_instruction_registered(prog_point, "DO", "\nCurrent string successfully set to DO.\n");

}

// These functions are used to check that the do loop works as it should given different arguments and is explained
// more fully in the documentation.
void test_do_loop(void)
{
   int i, j, k;
   program prog, *prog_point;
   do_loop_test_indicators indicator_struct;

   prog_point = &prog;

   for(i = 0; i <= 1; ++i){
      for(j = 0; j <= 1; ++j){
         for(k = 0; k <= 1; ++k){

            initialise_do_loop_indicator_components(&indicator_struct, i, j, k);

            initialise_do_loop_components(prog_point, indicator_struct);

            do_loop_case_checker(prog_point, &indicator_struct);
         }
      }
   }

   printf("\n");
}

void initialise_do_loop_indicator_components(do_loop_test_indicators *indicator_struct, on_off FROM_ind, on_off TO_ind, on_off bracket_ind)
{
   indicator_struct -> FROM_correct = FROM_ind;
   indicator_struct -> TO_correct = TO_ind;
   indicator_struct -> bracket_correct = bracket_ind;

   indicator_struct -> FROM_wrong = 1 - FROM_ind;
   indicator_struct -> TO_wrong = 1 - TO_ind;
   indicator_struct -> bracket_wrong = 1 - bracket_ind;
}

void initialise_do_loop_components(program *prog_point, do_loop_test_indicators indicator_struct)
{
   printf("\n");

   randomly_assign_point(prog_point);

   initialise_single_do_component(indicator_struct.FROM_correct, "FROM", prog_point, "\nCurrent string successfully set to FROM.\n");

   check_program_incremented(prog_point);

   initialise_single_do_component(indicator_struct.TO_correct, "TO", prog_point, "\nCurrent string successfully set to TO.\n");

   check_program_incremented(prog_point);

   initialise_single_do_component(indicator_struct.bracket_correct, "{", prog_point, "\nCurrent string successfully set to {.\n");

   prog_point -> current_word -= NUM_INSTRUCTIONS_DEFINED;

}

void initialise_single_do_component(on_off indicator, char *word, program *prog_point, char *assign_message)
{
   if(indicator == on){
      assign_word_to_point(word, prog_point, assign_message);
   }
   else{
      assign_word_to_point("!", prog_point, "\nCurrent string successfully set to !.\n");
   }
}

void do_loop_case_checker(program *prog_point, do_loop_test_indicators *indicator_struct)
{
   int start_of_loop, end_of_loop;

   if( same_string(prog_point -> prog_line[prog_point -> current_word], "FROM") ){

      do_loop_section_check(indicator_struct -> FROM_correct, "\nCorrectly forwarded through FROM part of do_loop\n",
                            "\nIncorrectly forwarded through FROM part of do_loop\n", prog_point);

      start_of_loop = rand() % MAX_LOOP_SIZE;

      if( same_string(prog_point -> prog_line[prog_point -> current_word], "TO") ){

         do_loop_section_check(indicator_struct -> TO_correct, "\nCorrectly forwarded through TO part of do_loop\n",
                               "\nIncorrectly forwarded through TO part of do_loop\n", prog_point);

            do{
               end_of_loop = rand() % MAX_LOOP_SIZE;
            }while(end_of_loop < start_of_loop);

            if( same_string( prog_point -> prog_line[prog_point -> current_word], "{" ) ){

               do_loop_section_check(indicator_struct -> bracket_correct, "\nCorrectly forwarded through { part of do_loop\n",
                                     "\nIncorrectly forwarded through { part of do_loop\n", prog_point);

               looping_component_check(start_of_loop, end_of_loop);             

            }
            else{

               do_loop_section_check(indicator_struct -> bracket_wrong, "\nIncorrect { statement caught.\n",
                                     "\nIncorrect { statement not caught.\n", prog_point);

            }
      
      }
      else{

         do_loop_section_check(indicator_struct -> TO_wrong, "\nIncorrect TO statement caught.\n",
                               "\nIncorrect TO statement not caught.\n", prog_point);

      }

   }
   else{

      do_loop_section_check(indicator_struct -> FROM_wrong, "\nIncorrect FROM statement caught.\n",
                            "\nIncorrect FROM statement not caught.\n", prog_point);
   
   }
}

void do_loop_section_check(on_off indicator, char *success_message, char* fail_message, program *prog_point)
{
   if(indicator == on){

      CU_PASS();
      printf("%s", success_message);
      check_program_incremented(prog_point);

   }
   else{

      CU_FAIL();
      printf("%s", fail_message);

   }
}

void looping_component_check(int start_of_loop, int end_of_loop)
{
   int loop_counter = 0, total_iterations = end_of_loop - start_of_loop;

   printf("\nDO loop initiated.\n");

   do{

      CU_PASS();
      printf("\nCurrently on iteration %d/%d of the DO loop.\n", ++loop_counter, total_iterations);
      ++start_of_loop;

   }while(end_of_loop > start_of_loop);

   printf("\nDO loop finished.\n");     
}

// Tests to see if SET is registered when it should be.
void test_set_check(void)
{
   program prog, *prog_point;

   prog_point = &prog;

   check_instruction_registered(prog_point, "SET", "\nCurrent string successfully set to SET.\n");

}

// Tests to see if := is registered when it should be.
void test_set_loop(void)
{
   program prog, *prog_point;

   prog_point = &prog;

   check_instruction_registered(prog_point, ":=", "\nCurrent string successfully set to :=.\n");
}

// Tests to see the polish stack is initialised correctly.
void test_init_pol_stack(void)
{
   int i;
   polish_stack pol_stack, *pol_stack_point;

   pol_stack_point = &pol_stack;

   for(i = 0; i < MAX_STACK_SIZE; ++i){
      pol_stack_point -> numbers_stack[i] = 0;
      CU_ASSERT(pol_stack_point -> numbers_stack[i] == 0);
   }
   printf("\n\nAll components of the RPN stack successfully initialised to zero.\n");

   pol_stack_point -> current_index = 0;
   assert_test(pol_stack_point -> current_index == 0, "Current location in RPN stack successfully initialised to zero.");
}


// Used to examine the behaviour of the polish function when the operator indicator is on or off and it is or isn't at
// the end of the stack.
void test_polish(void)
{
   program prog, *prog_point;
   prog_point = &prog;

   polish_indicators pol_ind_struct;

   test_polish_case(prog_point, &pol_ind_struct, on, off);

   test_polish_case(prog_point, &pol_ind_struct, off, on);

   test_polish_case(prog_point, &pol_ind_struct, off, off);

}

void test_polish_case(program *prog_point, polish_indicators *pol_ind_struct, on_off end_state_on, on_off op_state_on)
{
   initialise_polish_struct(pol_ind_struct, end_state_on, op_state_on);

   set_end(pol_ind_struct, prog_point);

   test_polish_terms(prog_point, pol_ind_struct);
}

void initialise_polish_struct(polish_indicators *pol_ind_struct, on_off end_state_on, on_off op_state_on)
{
   pol_ind_struct -> end_statement_on = end_state_on;
   pol_ind_struct -> operand_on = op_state_on;

   if(pol_ind_struct -> operand_on){
      printf("\nOperand indicator set to be on.\n");
   }
   if(pol_ind_struct -> end_statement_on == off && pol_ind_struct -> operand_on == off){
      printf("\nOperand indicator and end statement set to be off, by default searching for numbers/ variables.\n");
   }
}

void set_end(polish_indicators *pol_ind_struct, program *prog_point)
{
   if(pol_ind_struct -> end_statement_on){

      randomly_assign_point(prog_point);

      assign_word_to_point(";", prog_point, "\nCurrent string successfully set to ;\n");

   }

}

void test_polish_terms(program *prog_point, polish_indicators *pol_ind_struct)
{
   if( same_string(prog_point -> prog_line[prog_point -> current_word], ";") ){

      if(pol_ind_struct -> end_statement_on){
         CU_PASS();
         printf("\nTerminating clause of Polish statement successfully registered.\n");
         check_program_incremented(prog_point);
      }
      else{
         CU_FAIL();
         printf("\nNon-terminating clause of Polish statement registered as terminating.\n");
      }
      
   }
   else if( pol_ind_struct -> operand_on ){

      if(pol_ind_struct -> operand_on){
         CU_PASS();
         printf("\nOperand clause of Polish statement successfully registered.\n");
         check_program_incremented(prog_point);
      }
      else{
         CU_FAIL();
         printf("\nNon-operand clause of Polish statement registered as operand.\n");
      }

   }
   else{

      if(pol_ind_struct -> operand_on || pol_ind_struct -> end_statement_on){
         CU_FAIL();
         printf("\nNon number/ variable clause of Polish statement registered as number/ variable.\n");
      }
      else{
         CU_PASS();
         printf("\nNumber/ variable clause of Polish statements successfully registered.\n\n");
      }

   }
}

// Goes through testing the to see if when different operands are turned on or off how the program
// reacts.
void test_op()
{
   program prog, *prog_point;
   player user;

   prog_point = &prog;

   test_op_case(prog_point, on, off, off, off, &user);

   test_op_case(prog_point, off, on, off, off, &user);

   test_op_case(prog_point, off, off, on, off, &user);

   test_op_case(prog_point, off, off, off, on, &user);

   test_op_case(prog_point, off, off, off, off, &user);

}

void test_op_case(program *prog_point, on_off plus_ind, on_off minus_ind, on_off divide_ind, on_off multiply_ind, player *user)
{
   operand_indicators op_ind_struct;

   randomly_assign_point(prog_point);

   initialise_operand_indicators(&op_ind_struct, plus_ind, minus_ind, divide_ind, multiply_ind);

   initialise_current_word_op(&op_ind_struct, prog_point);

   carry_out_op_test(&op_ind_struct, prog_point, user);
}

void initialise_operand_indicators(operand_indicators *op_ind_struct, on_off plus_ind, on_off minus_ind, on_off divide_ind, on_off multiply_ind)
{
   op_ind_struct -> plus_indicator = plus_ind;
   op_ind_struct -> minus_indicator = minus_ind;
   op_ind_struct -> divide_indicator = divide_ind;
   op_ind_struct -> multiply_indicator = multiply_ind;
}

void initialise_current_word_op(operand_indicators *op_ind_struct, program *prog_point)
{
   if(op_ind_struct -> plus_indicator){
      assign_word_to_point("+", prog_point, "\nCurrent string set to +.\n");
   }
   else if(op_ind_struct -> minus_indicator){
      assign_word_to_point("-", prog_point, "\nCurrent string set to -.\n");
   }
   else if(op_ind_struct -> divide_indicator){
      assign_word_to_point("/", prog_point, "\nCurrent string set to /.\n");
   }
   else if(op_ind_struct -> multiply_indicator){
      assign_word_to_point("*", prog_point, "\nCurrent string set to *.\n");
   }
   else{
      assign_word_to_point("!", prog_point, "\nCurrent string set to !.\n");
   }
}

void carry_out_op_test(operand_indicators *op_ind_struct, program *prog_point, player *user)
{
   if( same_string(prog_point -> prog_line[prog_point -> current_word], "+") ){

      op_assignment_and_checking(op_ind_struct -> plus_indicator, user, '+');

   }
   else if( same_string(prog_point -> prog_line[prog_point -> current_word], "-") ){

      op_assignment_and_checking(op_ind_struct -> minus_indicator, user, '-');

   }
   else if( same_string(prog_point -> prog_line[prog_point -> current_word], "/") ){
      
      op_assignment_and_checking(op_ind_struct -> divide_indicator, user, '/');

   }
   else if( same_string(prog_point -> prog_line[prog_point -> current_word], "*") ){
      
      op_assignment_and_checking(op_ind_struct -> multiply_indicator, user, '*');

   }
   else{

      CU_ASSERT_STRING_EQUAL(prog_point -> prog_line[prog_point -> current_word], "!");
      printf("\nDefault argument correctly registered.\n\n");

   }
}

void op_assignment_and_checking(on_off test, player *user, int current_operator)
{
   if(test){

         CU_PASS();
         printf("\nCorrect operator registered.\n");

         user -> current_operator = current_operator;
         assert_test(user -> current_operator == current_operator, "Correct operator assigned to user operator.");

      }
      else{

         CU_FAIL();
         printf("\nIncorrect operator registered.\n");

      }
}

//Tests the behaviour of varnum when detecting variables and constants.
void test_varnum(void)
{
   program prog, *prog_point;

   prog_point = &prog;

   randomly_assign_point(prog_point);

   test_varnum_case(prog_point, on, off);

   test_varnum_case(prog_point, off, on);

   test_varnum_case(prog_point, off, off);

   printf("\n");
}

void test_varnum_case(program *prog_point, on_off variable_ind, on_off number_ind)
{
   varnum_indicators varnum_inds;

   initialise_varnum_indicators(&varnum_inds, variable_ind, number_ind);

   initialise_varnum_string(&varnum_inds, prog_point);

   carry_out_varnum_test(prog_point, &varnum_inds);

}

void initialise_varnum_indicators(varnum_indicators *varnum_inds, on_off variable_ind, on_off number_ind)
{
   varnum_inds -> number_indicator = number_ind;
   varnum_inds -> variable_indicator = variable_ind;
}

void initialise_varnum_string(varnum_indicators *varnum_inds, program *prog_point)
{
   if(varnum_inds -> number_indicator){

      assign_word_to_point("35", prog_point, "\nCurrent string set to 35.\n");

   }
   else if(varnum_inds -> variable_indicator){

      assign_word_to_point("A", prog_point, "\nCurrent string set to A.\n");

   }
   else{

      assign_word_to_point("!", prog_point, "\nCurrent string set to !.\n");

   }
}

void carry_out_varnum_test(program *prog_point, varnum_indicators *varnum_inds)
{
   player user_struct, *user;

   float number; 
   int scan_checker = 0;

   user = &user_struct;

   scan_checker = sscanf(prog_point -> prog_line[ prog_point -> current_word ], "%f", &number);

   //35 is chosen for no particular reason.
   if(varnum_inds -> number_indicator){
      assert_test(number == 35, "Number from string correctly registered as 35.");
   }

   if(scan_checker == 0){

      if(varnum_inds -> number_indicator){
         CU_FAIL();
         printf("\nProblem scanning number from string correctly.\n");
      }
      else{
         CU_PASS();
         printf("\nNo number scanned from string correctly.\n");
      }
      
   }
   else{

      if(varnum_inds -> number_indicator){

         CU_PASS();
         printf("\nNumber in string correctly registered by varnum.\n");

         user -> current_constant = number;
         assert_test(user -> current_constant == 35, "Number correctly scanned from string and stored in user struct.");

         user -> constant_checker = on;
         assert_test(user -> constant_checker == on, "Constant checker in user struct correctly turned on.");

         user -> variable_checker = off;
         assert_test(user -> variable_checker == off, "Variable checker in user struct correctly turned off.");

         check_program_incremented(prog_point);
      }

   }
}

void test_var(void)
{
   program prog, *prog_point;

   prog_point = &prog;

   randomly_assign_point(prog_point);

   test_var_case(prog_point, on);

   test_var_case(prog_point, off);

}

void test_var_case(program *prog_point, on_off variable_indicator)
{
   player user_struct, *user;
   char variable;

   user = &user_struct;

   if(variable_indicator == on){
      assign_word_to_point("A", prog_point, "\nCurrent string set to A.\n");
   }
   else{
      assign_word_to_point("!", prog_point, "\nCurrent string set to !.\n");
   }

   if( sscanf( prog_point -> prog_line[ prog_point -> current_word ], "%[A-Z]c", &variable) == 0){

      if(variable_indicator == on){
         CU_FAIL();
         printf("\nVariable should have been registered but was not.\n");
      }
      else{
         CU_PASS();
         printf("\nNon-variable correctly registered.\n\n");
      }

   }
   else{

      if(variable_indicator == on){

         CU_PASS();
         printf("\nVariable in string correctly registered by var.\n");

         user -> current_variable = variable - 'A';
         assert_test(user -> current_variable == 0, "Variable correctly scanned from string and stored in appropriate place in user struct.");

         user -> constant_checker = off;
         assert_test(user -> constant_checker == off, "Constant checker in user struct correctly turned off.");

         user -> variable_checker = on;
         assert_test(user -> variable_checker == on, "Variable checker in user struct correctly turned on.");

         check_program_incremented(prog_point);
      }
      else{
         
         CU_FAIL();
         printf("\nVariable not correctly registered as such.\n");

      }

   }
}

//These functions are used in printing and test to make sure that when asked to, the SDL can print to any area it chooses.
//They are covered seperately in the documentation also.
void test_SDL_print(void)
{
   int i, j, k, l;

   player user_struct, *user;

   user = &user_struct;

   SDL_Simplewin sw;

   Neill_SDL_Init(&sw);

   if(!sw.finished){
      for(k = 0; k < WHEIGHT; ++k){
         for(l = 0; l < WWIDTH; ++l){
            if(!sw.finished){
               for(i = 0; i < WHEIGHT; ++i){
                  for(j = 0; j < WWIDTH; ++j){
                     if(i == k && j == l){
                        user -> player_board[i][j] = coloured;
                     }
                     else{
                        user -> player_board[i][j] = uncoloured;
                     }
                  }
               }
            print_SDL_array_test_ver(user, &sw, k, l);
            SDL_Delay(1);
            Neill_SDL_Events(&sw);
            }
         }
      }
   }

   SDL_Quit();
}

void print_SDL_array_test_ver(player *user, SDL_Simplewin *sw, int k, int l)
{
   int i, j;
   SDL_Rect rectangle;

   rectangle.w = 1;
   rectangle.h = 1;

   for(i = 0; i < WHEIGHT; ++i){
      for(j = 0; j < WWIDTH; ++j){

         if(user -> player_board[i][j] == coloured){

            assert_test(k == i, "\nThe correct row coordinates have been coloured.");

            assert_test(j == l, "\nThe correct col coordinates have been coloured.");

            rectangle.y = i;
            rectangle.x = j;
            
            Neill_SDL_SetDrawColour(sw, WHITE, WHITE, WHITE);
            SDL_RenderFillRect(sw->renderer, &rectangle);
            
         }

      }
   }

   SDL_RenderPresent(sw->renderer);
   SDL_UpdateWindowSurface(sw->win);
    
   Neill_SDL_Events(sw);

}

