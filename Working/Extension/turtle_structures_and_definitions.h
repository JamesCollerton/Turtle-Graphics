// 						PREPROCESSING

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "neillsdl2.h"

#define MAX_NUM_LINES 						100 				// Maximum number of lines we want to allow in LOGO code.
#define MAX_SIZE_OF_LINE 					100				// Maximum size of a line we want to allow in LOGO code.
#define CLEAR_SUCCESS 				  		0 				// Used to make sure the screen is successfully cleared.
#define WWIDTH 					   		1000 				// Width of the window.
#define WHEIGHT 						1000 				// Height of the window.
#define NUM_LETTERS_ALPHABET 				  	26 				// Used for variable declarations.
#define RADIANS_CONST 						0.0174532925 			// Value of radian conversion to angles used in trig.
#define ERROR_VALUE 					   	-1000 				// Error value so uninitialised variables are caught.
#define MAX_STACK_SIZE 						100 				// Max stack size for the polish stack.
#define START_ITERATION_END 				   	5 				// Used for initialising all the components of the looping array (start, end etc.)
#define MAX_EMBEDDED_LOOPS 					100 				// Maximum embedded loops we have allowed.
#define TOTAL_NUM_INSTRUCTIONS 				  	41 				// The total number of possible instructions (used in decoding).
#define MAX_PASSWORD_SIZE 					10 				// The max size we allow the password to be.
#define SCAN_SUCCESS 						1 				// Checks to make sure scanning things has been successful.
#define NUM_INTS_PW_FILE 					1000 				// The number of random 0s and 1s we put in a password file.
#define EXIT_CODE 						1 				// The exit code printed on an exit.
#define RECT_W							1 				// The width of a rectangle to be printed (one pixel).
#define RECT_H 							1				// The height of a rectangle to be printed (one pixel).
#define WHITE 							255 				// The Uint8 colour code for white.
#define PRINT_DELAY						100 				// The delay between printing values.
#define WS_TRANS_CONST 						10 				// The WhiteSpace translation constant for scaling.
#define BINARY 							2 				// To make sure numbers in password files are 0 or 1.
#define MAX_ANIM_SPEED 					   	10000 				// The maximum animation speed we will allow.
#define MIN_ANIM_SPEED						500 				// The minimum animation speed we will allow.
#define MIN_PASSWORD						0 				// The minimum password we can enter.
#define MAX_PASSWORD 						1000 				// The maximum password we can enter.
#define NO_INTEGER 						0 				// If no integer is found on scanning.

#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %sOccured in %s, line %d\n\n", PHRASE, __FILE__, __LINE__); exit(1); }



// 						ENUMERATIONS.

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

enum other_arg_type {regular, secret, translate, combine_files, password_change};
typedef enum other_arg_type other_arg_type;

enum accept_decline {decline, accept};
typedef enum accept_decline accept_decline;

enum initial_final {initial, final};
typedef enum initial_final initial_final;

//								TYPEDEFINES

typedef uncoloured_coloured board_array[WWIDTH][WHEIGHT];

typedef int password_array[NUM_INTS_PW_FILE];

// 								STRUCTURES

struct program{
	char prog_line[MAX_NUM_LINES][MAX_SIZE_OF_LINE];
	int current_word;
	int num_lines_in_file;
};
typedef struct program program;

struct player{

	board_array player_board;

	int animation_speed;

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

struct printing_board{

	board_array player_board;
	struct printing_board *next_board;
	struct printing_board *latest_board;

};
typedef struct printing_board printing_board;

struct whitespace_info{

	int ws_spaces[MAX_NUM_LINES];
	int ws_tabs[MAX_NUM_LINES];
	on_off ws_number_indicators[MAX_NUM_LINES];

	char ws_verbatim_file[MAX_NUM_LINES][MAX_SIZE_OF_LINE];
	int num_chars_per_line[MAX_NUM_LINES];

	int ws_num_lines;

	char decoding_array[TOTAL_NUM_INSTRUCTIONS][MAX_SIZE_OF_LINE];
};
typedef struct whitespace_info whitespace_info;

struct password_info{

	password_array pw_array;
	password_array temp_pw_array;

	accept_decline pw_indicator;
	int password;

};
typedef struct password_info password_info; 
