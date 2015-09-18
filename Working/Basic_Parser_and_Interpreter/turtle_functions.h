// 						PREPROCESSING

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "neillsdl2.h"

#define MAX_NUM_LINES 				100 			// Maximum number of lines we want to allow in a LOGO program.
#define MAX_SIZE_OF_LINE 			100			// Maximum size of a line we want to allow in a LOGO program.
#define CLEAR_SUCCESS 				  0			// Used to make sure clearing the screen works.
#define WWIDTH 				       1000 			// Width of the SDL window.
#define WHEIGHT 			       1000			// Height of the SDL window.
#define NUM_LETTERS_ALPHABET 			 26 			// Used so all variables are in the desired range.
#define RADIANS_CONST 		       0.0174532925 			// The radians constant used in trig functions.
#define ERROR_VALUE 			      -1000 			// The error value used so that uninitialised variables are caught.
#define MAX_STACK_SIZE 				100 			// The max stack size for a polish stack.
#define START_ITERATION_END 			  5 			// Used to initialise all the different parts of the looping stack (start, end, current iteration, variable etc.)
#define MAX_EMBEDDED_LOOPS 			100 			// The maximum embedded loops I decided you were allowed to have.
#define SCAN_SUCCESS 				  1			// Used so we know that scanning something has been successful.
#define WHITE 					255 			// To make the colour drawn to screen white.
#define RECT_H 					  1 			// The height of the rectangle we want to draw (one pixel).
#define RECT_W 					  1 			// The width of the rectangle we want to draw (one pixel).

#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %sOccured in %s, line %d\n\n", PHRASE, __FILE__, __LINE__); exit(1); }

// 						TYPEDEFS AND ENUMERATIONS

enum success_unsuccess {unsuccessful, successful};
typedef enum success_unsuccess success_unsuccess;

enum uncoloured_coloured {uncoloured, coloured};
typedef enum uncoloured_coloured uncoloured_coloured;

enum on_off {off, on};
typedef enum on_off on_off;

enum grid_location {top_right, bottom_right, bottom_left, top_left};
typedef enum grid_location grid_location;

enum rt_lt {rt_dir, lt_dir};
typedef enum rt_lt rt_lt;

enum looping_array {start_word, start_number, end_number, current_iteration, variable};
typedef enum looping_array looping_array;

typedef uncoloured_coloured board_array[WWIDTH][WHEIGHT];

struct program{
	char prog_line[MAX_NUM_LINES][MAX_SIZE_OF_LINE];
	int current_word;
	int num_lines_in_file;
};
typedef struct program program;

struct player{

	board_array player_board;

	int row;
	int col;
	int angle;

	float variable_values[NUM_LETTERS_ALPHABET];
	float current_constant;
	int current_variable;
	int current_operator;
	int current_steps_taken;

	on_off variable_checker;
	on_off constant_checker;
	on_off operation_indicator;
	on_off loop_indicator;

	int set_variable;
	int looping_index;
	int looping_array[START_ITERATION_END][MAX_EMBEDDED_LOOPS];
};
typedef struct player player;

struct polish_stack{

	float numbers_stack[MAX_STACK_SIZE];
	int current_index;

};
typedef struct polish_stack polish_stack;


//											FUNCTION PROTOTYPES

//											PARSING FUNCTIONS

void check_mallocs(program *prog, player *user);

void check_command_line_arguments(int argc);

void clear_screen(void);

void initialise_program(program *prog);

void initialise_player(player *user);

void open_program_file(char *filename, program *prog);

void parse_text_and_interpret(program *prog, player *user);

success_unsuccess same_string(char *string_one, char *string_two);

void instrctlist(program *prog, player *user);

void instruction(program *prog, player *user);

success_unsuccess fd(program *prog, player *user);

success_unsuccess lt_rt(program *prog, player *user, rt_lt direction, char *command);

success_unsuccess do_check(program *prog, player *user);

void do_loop(program *prog, player *user);

success_unsuccess set_check(program *prog, player *user);

void set_loop(program *prog, player *user);

void polish(program *prog, player *user, polish_stack *pol_stack);

success_unsuccess op(program *prog, player *user);

void varnum(program *prog, player *user);

void var(program *prog, player *user);

void print_SDL_array(player *user, SDL_Simplewin *sw);

void initialise_pol_stack(polish_stack *pol_stack);

//											INTERPRETING FUNCTIONS

void fd_interpret(player *user);

void draw_angled_line(player *user, int number_steps);

void check_number_steps(int number_steps);

void draw_next_square(int hypotenuse_length, player *user, int upper_bound, grid_location grid_loc, int number_steps);

void check_variable(player *user);

void drawing_process(player *user, int new_user_row, int new_user_col, int number_steps, int hypotenuse_length);

void lt_rt_interpret(player *user, rt_lt direction);

void lt_rt_interpret_case(player *user, rt_lt direction, float increment_constant);

void adjust_angle(player * user);

void op_interpret(program *prog, player *user, polish_stack *pol_stack);

void polish_varnum_interpret(program *prog, player *user, polish_stack *pol_stack);

void push_to_stack(polish_stack *pol_stack, float constant_for_push);

void interpret_set_variable(player *user);

void check_and_assign_variable(polish_stack *pol_stack, player *user);

void loop_subject_var_interpret(player *user);

void loop_start_var_interpreter(player *user);

void loop_end_var_interpreter(player *user);

void loop_interior_interpreter(player *user, program *prog);

void end_loop(player *user);

success_unsuccess check_loop_finish(player *user);
