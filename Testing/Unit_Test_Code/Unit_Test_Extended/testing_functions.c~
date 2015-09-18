#include "turtle_functions.h"

int initialise_CUnit(CU_pSuite *pSuite, char *suite_name)
{
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   *pSuite = CU_add_suite(suite_name, NULL, NULL);
   if (NULL == *pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   return 0;
}

int close_CUnit(void)
{
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

void set_up_test(char *suite_name, char *test_name, CU_TestFunc function)
{
   CU_pSuite pSuite = NULL;

   initialise_CUnit(&pSuite, suite_name);

   if ((NULL == CU_add_test(pSuite, test_name, function))){
      CU_cleanup_registry();
      CU_get_error();
    }

   close_CUnit();
}

void assert_test(int test, char *message)
{
    CU_ASSERT(test);
    if(test){
        printf("\n%s\n", message);
    }
    else{
        printf("\nWARNING FAILED: %s\n", message);
    }

}

void string_equal_test(char *string_one, char *string_two, char *message)
{
    CU_ASSERT_STRING_EQUAL(string_one, string_two);
    if( strcmp(string_one, string_two) == 0 ){
        printf("\n%s\n", message);
    }
    else{
        printf("\nWARNING FAILED: %s\n", message);
    }
}

void string_not_equal_test(char *string_one, char *string_two, char *message)
{
    CU_ASSERT_STRING_NOT_EQUAL(string_one, string_two);
    if( strcmp(string_one, string_two) != 0 ){
        printf("\n%s\n", message);
    }
    else{
        printf("\nWARNING FAILED: %s\n", message);
    }
}

//                                        EXTENSION TESTING FUNCTIONS.

void test_assign_board_to_list(void)
{
  printing_board first_board;

  printing_board *board_to_add = (printing_board *) malloc(sizeof(printing_board));

  printf("\n\nBoard set to NULL.\n");
  test_assign_board_to_list_case(NULL, &first_board);

  printf("\nBoard space malloced.\n");
  test_assign_board_to_list_case(board_to_add, &first_board);
}

void test_assign_board_to_list_case(printing_board *board_to_add, printing_board *first_board)
{

  if(board_to_add == NULL){
    assert_test(board_to_add == NULL, "Board correctly identified as NULL.");
  }
  else{

    first_board -> latest_board -> next_board = board_to_add;
    assert_test(first_board -> latest_board -> next_board == board_to_add, "Latest board correctly added to list.");

    first_board -> latest_board = board_to_add;
    assert_test(first_board -> latest_board == board_to_add, "Latest board correctly assigned.");

    board_to_add -> next_board = NULL;
    assert_test(board_to_add -> next_board == NULL, "Next board in list correctly set to NULL.");

    board_to_add -> latest_board = board_to_add;
    assert_test(board_to_add -> latest_board == board_to_add, "Latest board correctly set to itself.\n");
  }

}

void test_copy_board_into_list(void)
{
    printing_board b_to_add, *board_to_add;
    board_to_add = &b_to_add;

    player Player, *user;
    user = &Player;

    int i, j;

    for(i = 0; i < WHEIGHT; ++i){
        for(j = 0; j < WWIDTH; ++j){
            board_to_add -> player_board[i][j] = user -> player_board[i][j];
            CU_ASSERT(board_to_add -> player_board[i][j] == user -> player_board[i][j]);
        }
    }

    printf("\n\nIf no errors above, all elements correctly copied into new grid.\n\n");
}

void test_check_initialisation(void)
{
    program *prog = (program *) malloc(sizeof(program));
    player *user = (player *) malloc(sizeof(player));
    whitespace_info *whitespace_prog = (whitespace_info *) malloc(sizeof(whitespace_info));
    printing_board *first_board = (printing_board *) malloc(sizeof(printing_board));
    password_info *pw_info = (password_info *) malloc(sizeof(password_info));

    printf("\n\nAll mallocs successful.\n");
    test_check_initialisation_case(prog, user, whitespace_prog, first_board, pw_info);

    printf("\nProg malloc failed.\n");
    test_check_initialisation_case(NULL, user, whitespace_prog, first_board, pw_info); 

    printf("\nUser malloc failed.\n");
    test_check_initialisation_case(prog, NULL, whitespace_prog, first_board, pw_info); 

    printf("\nWhitespace_Prog malloc failed.\n");
    test_check_initialisation_case(prog, user, NULL, first_board, pw_info); 

    printf("\nFirst_Board malloc failed.\n");
    test_check_initialisation_case(prog, user, whitespace_prog, NULL, pw_info);

    printf("\nPw_info malloc failed.\n");
    test_check_initialisation_case(prog, user, whitespace_prog, first_board, NULL);      
}

void test_check_initialisation_case(program *prog, player *user, whitespace_info *whitespace_prog, printing_board *first_board, password_info *pw_info)
{
    if(prog == NULL || user == NULL || whitespace_prog == NULL || first_board == NULL || pw_info == NULL){
        assert_test( (prog == NULL || user == NULL || whitespace_prog == NULL || first_board == NULL || pw_info == NULL), "Malloc failed correctly identified.\n");
    }
    else{
        assert_test( !(prog == NULL || user == NULL || whitespace_prog == NULL || first_board == NULL || pw_info == NULL), "All mallocs succeeded identified.\n");
    }
}

void test_check_animation_preferences(void)
{

    printf("\n\nStart animation preference at 0, incrementing.\n");
    test_check_animation_preferences_case(UNDER_AN_SPEED, up);

    printf("\nStart animation preference at 10,100, decrementing.\n");
    test_check_animation_preferences_case(OVER_AN_SPEED, down);

}

//This increments or decrements the animation speed to simulate a user entering different speeds.
void test_check_animation_preferences_case(int start, up_down dir_ind)
{
    player User, *user;
    user = &User;

    int animation_speed = start;

    do{

        if(dir_ind == up){
            ++animation_speed;
        }
        else{
            --animation_speed;
        }
        

    }while( animation_speed < MIN_ANIM_SPEED || animation_speed > MAX_ANIM_SPEED );

    assert_test( !(animation_speed < MIN_ANIM_SPEED || animation_speed > MAX_ANIM_SPEED) , "Animation speed in valid range.");

    user -> animation_speed = animation_speed;
    assert_test( user -> animation_speed == animation_speed, "Animation speed successfully set.\n");
}

void test_examine_fourth_argument(void)
{
    other_arg_type argument_indicator;

    printf("\n\nFourth argument set to COMBINE.\n");
    test_examine_fourth_argument_case("COMBINE", &argument_indicator);

    printf("\nFourth argument set to WRONG.\n");
    test_examine_fourth_argument_case("WRONG", &argument_indicator);
}

void test_examine_fourth_argument_case(char *argument, other_arg_type *argument_indicator)
{
    if(same_string("COMBINE", argument) ){
        string_equal_test("COMBINE", argument, "Argument successfully registered as COMBINE.");
        *argument_indicator = combine_files;
        assert_test( *argument_indicator == combine_files, "Argument indicator successfully set to combine_files.\n");
    }
    else{
        string_equal_test("WRONG", argument, "Argument successfully registered as WRONG.\n");
    }
}

void test_free_all_print_boards(void)
{
    printing_board current_board;

    printf("\n\nCurrent board set to NULL.\n");
    test_free_all_print_boards_case(NULL);

    printf("\nCurrent board valid.\n");
    test_free_all_print_boards_case(&current_board);
}

void test_free_all_print_boards_case(printing_board *current_board)
{
    printing_board *board_after;

    while(current_board != NULL){

        board_after = current_board -> next_board;
        assert_test(board_after == current_board -> next_board, "Board after switched to next board.");

        current_board = board_after;
        assert_test(current_board == board_after, "Current board switched to board after.");

        current_board = NULL;
        assert_test(current_board == NULL, "Current board set to null.");

    }

    assert_test(current_board == NULL, "Current board registered as null.\n");
}

void test_initialise_whitespace_prog(void)
{
    whitespace_info Whitespace_prog, *whitespace_prog;
    whitespace_prog = &Whitespace_prog;

    int i;

    for(i = 0; i < MAX_NUM_LINES; ++i){

        whitespace_prog -> ws_spaces[i] =   0;
        CU_ASSERT(whitespace_prog -> ws_spaces[i] == 0);

        whitespace_prog -> ws_tabs[i] =     0;
        CU_ASSERT(whitespace_prog -> ws_tabs[i] == 0);

        whitespace_prog -> ws_number_indicators[i] =    off;
        CU_ASSERT(whitespace_prog -> ws_number_indicators[i] == off);

        whitespace_prog -> ws_verbatim_file[i][0] =     '\0';
        CU_ASSERT(whitespace_prog -> ws_verbatim_file[i][0] == '\0');

    }

    for(i = 0; i < TOTAL_NUM_INSTRUCTIONS; ++i){

        whitespace_prog -> decoding_array[i][0] = '\0';
        CU_ASSERT(whitespace_prog -> decoding_array[i][0] == '\0');

    }
    printf("\n\nIf no errors above, all spaces, tabs, number indicators, the verbatim file and the decoder array are all correctly set.\n");

    whitespace_prog -> ws_num_lines = 0;
    assert_test(whitespace_prog -> ws_num_lines == 0, "Number of whitespace lines correctly set to zero.\n");
}

void test_open_whitespace_program_file(void)
{
    FILE *prog_file = NULL;

    prog_file = fopen("stripped_whitespace_file.txt", "r");

    printf("\n\nProgram file set to NULL.\n");
    test_open_whitespace_program_file_case(NULL);

    printf("\n\nProgram should be opened.\n");
    test_open_whitespace_program_file_case(prog_file);

    fclose(prog_file);
}

void test_open_whitespace_program_file_case(FILE *prog_file)
{

    if( prog_file == NULL){
        assert_test(prog_file == NULL, "Program correctly registered as unopened.\n");
    }
    else{
        assert_test(prog_file != NULL, "Program correctly registered as opened.\n");
    }

}

void test_strip_non_whitespace_components(void)
{
    FILE *whitespace_file = fopen("pseudo_torus.txt", "r"), *stripped_whitespace_file = fopen("stripped_whitespace_file.txt", "w");

    printf("\n\nBoth files should open.\n");
    test_strip_non_whitespace_components_case(whitespace_file, stripped_whitespace_file);

    printf("\n\nWhitespace file set to NULL.\n");
    test_strip_non_whitespace_components_case(NULL, stripped_whitespace_file);

    printf("\n\nStripped whitespace file set to NULL.\n");
    test_strip_non_whitespace_components_case(whitespace_file, NULL);

    fclose(stripped_whitespace_file);
    fclose(whitespace_file);
}

void test_strip_non_whitespace_components_case(FILE *whitespace_file, FILE *stripped_whitespace_file)
{

    if( whitespace_file == NULL || stripped_whitespace_file == NULL ){
        assert_test(whitespace_file == NULL || stripped_whitespace_file == NULL, "Program correctly registered as unopened.\n");
    }
    else{
        assert_test(!(whitespace_file == NULL || stripped_whitespace_file == NULL), "Program correctly registered as opened.\n");
    }

}

void test_scan_in_whitespace_components(void)
{
    whitespace_info whitespace_prog;

    printf("\n\nCharacter set as space.\n");
    test_scan_in_whitespace_components_case(&whitespace_prog, ' ');

    printf("\nCharacter set as tab.\n");
    test_scan_in_whitespace_components_case(&whitespace_prog, '\t');

    printf("\nCharacter set as newline.\n");
    test_scan_in_whitespace_components_case(&whitespace_prog, '\n');

}

void test_scan_in_whitespace_components_case(whitespace_info *whitespace_prog, char ch)
{
    static int i = 0, space_counter = 0, tab_counter = 0;
    static on_off first_pass = on;

    if(first_pass == on){
        assert_test(first_pass == on, "First time having visited this line registered.");

        if(ch == '\t'){
            assert_test(ch == '\t', "Tab as first character on the line registered.");

            whitespace_prog -> ws_number_indicators[i] = on;
            assert_test(whitespace_prog -> ws_number_indicators[i] == on, "The whitespace number indicator turned on.");

            --tab_counter;
            printf("\nTab counter adjusted\n");
        }

        first_pass = off;
        assert_test(first_pass == off, "First pass indicator turned off.");

    }

    if( ch == ' ' ){
        assert_test(ch == ' ' , "Space registered");

        ++space_counter;
        printf("\nSpace counter incremented.\n");

    }
    else if( ch == '\t' ){
        assert_test(ch == '\t' , "Tab registered.");

        if(first_pass != on){
            assert_test(first_pass != on, "First pass checked again to see if it's on.");

            ++tab_counter;
            printf("\nTab counter incremented.\n");

        }
    }
    else if( ch == '\n' ){
        assert_test(ch == '\n', "Newline character registered.");

        whitespace_prog -> ws_spaces[i] = space_counter;
        assert_test(whitespace_prog -> ws_spaces[i] == space_counter, "Space counter set in whitespace structure.");

        whitespace_prog -> ws_tabs[i] = tab_counter;
        assert_test(whitespace_prog -> ws_tabs[i] == tab_counter, "Tab counter set in whitespace structure.");

        space_counter = 0;
        assert_test(space_counter == 0, "Space counter reset.");

        tab_counter = 0;
        assert_test(tab_counter == 0, "Tab counter reset.");

        first_pass = on;
        assert_test(first_pass == on, "First pass for the next line set.");

        ++i;
        printf("\nLine in whitespace file incremented\n");
    }
    if(i > MAX_NUM_LINES){
        assert_test(i > MAX_NUM_LINES, "Too many lines in file registered.");
    }

    whitespace_prog -> ws_num_lines = i;
    assert_test(whitespace_prog -> ws_num_lines == i, "Program correctly registered as opened.\n");
}

void test_initialise_decoder_array(void)
{
    whitespace_info Whitespace_prog, *whitespace_prog;
    whitespace_prog = &Whitespace_prog;

    int i;

    char *commands[TOTAL_NUM_INSTRUCTIONS] = {"{", "}", "FD", "LT", "RT", "SET", "DO", "FROM", "TO", ":=", ";", "+", "-", "*", "/", 
                        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", 
                        "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

    printf("\n");

    for(i = 0; i < TOTAL_NUM_INSTRUCTIONS; ++i){
        sscanf(commands[i], "%s", whitespace_prog -> decoding_array[i]);
        string_equal_test(commands[i], whitespace_prog -> decoding_array[i], "Instruction successfully scanned into decoding array.");
    }

    printf("\n");
}

void test_write_file_from_whitespace(void)
{
    FILE *prog_file = fopen("ws_to_reg_translation.txt", "w");

    printf("\n\nFile set as unopened.\n");
    test_write_file_from_whitespace_case(NULL);

    printf("\nFile set as opened.\n");
    test_write_file_from_whitespace_case(prog_file);

    fclose(prog_file);
}

void test_write_file_from_whitespace_case(FILE *prog_file)
{

    if( prog_file == NULL){
        assert_test(prog_file == NULL, "File incorrectly opened registered.");
    }
    else{
        assert_test(prog_file != NULL, "File correctly opened registered.\n");
    }

}

void test_write_whitespace_prog_to_file(void)
{
    whitespace_info whitespace_prog;

    printf("\n\nAll number indicators set to on.\n");
    test_write_whitespace_prog_to_file_case(&whitespace_prog, on);

    printf("\nAll number indicators set to off.\n");
    test_write_whitespace_prog_to_file_case(&whitespace_prog, on);

    printf("\nIf no errors above then all cases dealt with correctly.\n\n");
}

void test_write_whitespace_prog_to_file_case(whitespace_info *whitespace_prog, on_off number_ind)
{
    int i;

    whitespace_prog -> ws_num_lines = rand() % MAX_NUM_LINES;

    for(i = 0; i < whitespace_prog -> ws_num_lines; ++i){

        whitespace_prog -> ws_number_indicators[i] = number_ind;

        if(whitespace_prog -> ws_number_indicators[i] == off){
            CU_ASSERT(whitespace_prog -> ws_number_indicators[i] == off);
        }

        if(whitespace_prog -> ws_number_indicators[i] == on){
            CU_ASSERT(whitespace_prog -> ws_number_indicators[i] == on);
        }
    }
}

void test_write_prog_to_whitespace_file(void)
{
    int i, j;

    char *commands[TOTAL_NUM_INSTRUCTIONS] = {"{", "}", "FD", "LT", "RT", "SET", "DO", "FROM", "TO", ":=", ";", "+", "-", "*", "/", 
                                              "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", 
                                              "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

    printf("\n");

    for(i = 0; i < 100; ++i){
        for(j = 0; j < TOTAL_NUM_INSTRUCTIONS; ++j){
            printf("\nNumber set to: %d, Command set to: %s\n", i, commands[j]);
            test_write_prog_to_whitespace_file_case(i, commands[j]);
        }
    }

}

void test_write_prog_to_whitespace_file_case(int input_num, char *command)
{
    int j, k, num_tens, num_units;

    char *commands[TOTAL_NUM_INSTRUCTIONS] = {"{", "}", "FD", "LT", "RT", "SET", "DO", "FROM", "TO", ":=", ";", "+", "-", "*", "/", 
                                              "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", 
                                              "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
            
            num_tens = input_num / WS_TRANS_CONST;
            num_units = input_num- WS_TRANS_CONST * num_tens;

            for(k = 0; k < num_tens; ++k);
            printf("\nNumber of tens: %d\n", k);

            for(k = 0; k < num_units; ++k);
            printf("\nNumber of units: %d\n", k);

            assert_test(WS_TRANS_CONST * num_tens + num_units == input_num, "Input number correctly translated.");
          
            for(j = 0; j < TOTAL_NUM_INSTRUCTIONS; ++j){

                if(strcmp(command, commands[j]) == 0){
                    for(k = 0; k < j; ++k){
                        
                    }
                    printf("\nCommand index: %d.\n", k);
                    printf("\nCharacter: %s\n", commands[j]);

                    string_equal_test(commands[j], command, "Command matches index.\n");
                }
            }


}

void test_scan_in_whitespace_components_verbatim(void)
{
    whitespace_info whitespace_prog;

    printf("\n\nSpace to be scanned.\n");
    test_scan_in_whitespace_components_verbatim_case(&whitespace_prog, ' ');

    printf("\nNewline to be scanned.\n");
    test_scan_in_whitespace_components_verbatim_case(&whitespace_prog, '\n');
}

void test_scan_in_whitespace_components_verbatim_case(whitespace_info *whitespace_prog, char ch)
{
    static int i = 0, temp;

    whitespace_prog -> ws_num_lines = 0;
    assert_test(whitespace_prog -> ws_num_lines == 0, "Number of lines initialised to zero.");

    whitespace_prog -> ws_verbatim_file[ whitespace_prog -> ws_num_lines ][i] = ch;
    assert_test(whitespace_prog -> ws_verbatim_file[ whitespace_prog -> ws_num_lines ][i] == ch, "Character correctly put in.");

    temp = i;
    ++i;
    assert_test(i == temp + 1, "Place in array correctly printed.\n");

    if(ch == '\n'){
        assert_test(ch == '\n', "New line correctly registered.");

        whitespace_prog -> num_chars_per_line[ whitespace_prog -> ws_num_lines ] = i;
        assert_test(whitespace_prog -> num_chars_per_line[ whitespace_prog -> ws_num_lines ] == i, "Number of characters in line successfully set.");

        temp = whitespace_prog -> ws_num_lines;
        ++whitespace_prog -> ws_num_lines;
        assert_test(temp + 1 == whitespace_prog -> ws_num_lines, "Line correctly incremented.");

        i = 0;
        assert_test(i == 0, "Place in character array set back to zero.\n");
    }
}

void test_write_combination_to_file(void)
{
    whitespace_info whitespace_prog;
    program prog;

    FILE *combined_file = fopen("Combined_File.txt", "w");

    printf("\n\nNo file to be opened set, more lines in regular than whitespace file.\n");
    test_write_combination_to_file_case(NULL, ARBITRARY_NUM, ARBITRARY_NUM + 1, &whitespace_prog, &prog);

    printf("\nFile to be opened set, more lines in regular than whitespace file.\n");
    test_write_combination_to_file_case(combined_file, ARBITRARY_NUM, ARBITRARY_NUM + 1, &whitespace_prog, &prog);

    printf("\nNo file to be opened set, more lines in whitespace than regular file.\n");
    test_write_combination_to_file_case(combined_file, ARBITRARY_NUM + 1, ARBITRARY_NUM, &whitespace_prog, &prog);

    fclose(combined_file);
}

void test_write_combination_to_file_case(FILE *combined_file, int num_1, int num_2, whitespace_info *whitespace_prog, program *prog)
{
    int current_line = 0;

    whitespace_prog -> ws_num_lines = num_1;
    prog -> num_lines_in_file = num_2;

    if( combined_file  == NULL){
        assert_test(combined_file  == NULL, "No file open registered correctly.");
    }

    while(current_line <= whitespace_prog -> ws_num_lines && current_line <= prog -> num_lines_in_file){
        CU_ASSERT(current_line <= whitespace_prog -> ws_num_lines && current_line <= prog -> num_lines_in_file);
        ++current_line;
    }

    if(whitespace_prog -> ws_num_lines > current_line){
        while(current_line <= whitespace_prog -> ws_num_lines){
            CU_ASSERT(whitespace_prog -> ws_num_lines > prog -> num_lines_in_file);
            ++current_line;
        }
    }
    else if(prog -> num_lines_in_file > current_line){
        while(current_line <= prog -> num_lines_in_file){
            CU_ASSERT(whitespace_prog -> ws_num_lines < prog -> num_lines_in_file);
            ++current_line;
        }
    }

    printf("\nIf no errors above then success.\n\n");

}

void test_read_in_pw_array(void)
{
    printf("\n\nInitial file set to be opened.\n");
    test_read_in_pw_array_case(initial);

    printf("\nFinal file set to be opened.\n");
    test_read_in_pw_array_case(final);

    printf("\nUndefined file set to be opened.\n");
    test_read_in_pw_array_case(ARBITRARY_NUM);
}

void test_read_in_pw_array_case(initial_final array_ind)
{
    FILE *password_file = NULL;

    if(array_ind == initial){
        assert_test(array_ind == initial, "Initial file registered.");

        password_file = fopen("Password_Files/password_file_1.txt", "r");
    }
    else if(array_ind == final){
        assert_test(array_ind == final, "Final file registered.");

        password_file = fopen("Password_Files/password_file_2.txt", "r");
    }

    if( password_file == NULL){
        assert_test(password_file == NULL, "No file open registered correctly.\n");
    }
    else{
        fclose(password_file);
    }

}

void test_map_arrays(void)
{
    password_info PW_info, *pw_info;
    pw_info = &PW_info;

    password_array initial_array;

    int i;

    for(i = 0; i < NUM_INTS_PW_FILE; ++i){
        pw_info -> temp_pw_array[i] = initial_array[ (i + pw_info -> password) % NUM_INTS_PW_FILE ];
        CU_ASSERT(pw_info -> temp_pw_array[i] == initial_array[ (i + pw_info -> password) % NUM_INTS_PW_FILE ]);
    }

     printf("\n\nIf no errors above then arrays mapped correctly.\n\n");
}

void test_compare_arrays(void)
{
    password_array temp_array, final_array;

    printf("\n\nDifferent arrays set.\n");
    test_compare_arrays_case(temp_array, final_array);

    printf("\nSame arrays set.\n");
    test_compare_arrays_case(temp_array, temp_array);
}

void test_compare_arrays_case(password_array temp_array, password_array final_array)
{
    password_info PW_info, *pw_info;
    pw_info = &PW_info;

    int i;

    for(i = 0; i < NUM_INTS_PW_FILE; ++i){
        if(temp_array[i] != final_array[i]){
            assert_test(temp_array[i] != final_array[i], "Different arrays correctly registered.");
            return;
        }
    }

    pw_info -> pw_indicator = accept;
    assert_test(pw_info -> pw_indicator == accept, "Same arrays registered.\n");
}

void test_change_password(void)
{
    FILE *prog_file = fopen("test_write_password.txt", "w");
    password_array temp_array_1, temp_array_2;
    int new_pw = rand() % MAX_PASSWORD;

    printf("\n\nProgram file opened, set to initial.\n");
    test_change_password_case(prog_file, temp_array_1, temp_array_2, new_pw, initial);

    printf("\nProgram file opened, set to final.\n");
    test_change_password_case(prog_file, temp_array_1, temp_array_2, new_pw, final);

    printf("\nProgram file unopened, set to initial.\n");
    test_change_password_case(NULL, temp_array_1, temp_array_2, new_pw, initial);

    fclose(prog_file);
}

void test_change_password_case(FILE *prog_file, password_array temp_array_1, password_array temp_array_2, int new_pw, initial_final init_fin_ind)
{

    if( prog_file == NULL ){
        assert_test(prog_file == NULL, "Program successfully registered as unopened.");
    }

    for(int i = 0; i < NUM_INTS_PW_FILE; ++i){

        if(init_fin_ind == initial){
            temp_array_1[i] = rand() % BINARY;
            CU_ASSERT(temp_array_1[i] < BINARY);
        }

        else if(init_fin_ind == final){
            temp_array_2[i] = temp_array_1[ (i + new_pw) % NUM_INTS_PW_FILE ];
            CU_ASSERT(temp_array_2[i] == temp_array_1[ (i + new_pw) % NUM_INTS_PW_FILE ])
        }
    }

    printf("\nIf no errors above then success.\n\n");
}
