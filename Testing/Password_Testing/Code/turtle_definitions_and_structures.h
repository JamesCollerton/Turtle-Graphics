#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NUM_LINES 						100
#define MAX_SIZE_OF_LINE 					100
#define CLEAR_SUCCESS 				  		0
#define WWIDTH 					   		1000
#define WHEIGHT 						1000
#define NUM_LETTERS_ALPHABET 				  	26
#define RADIANS_CONST 						0.0174532925
#define ERROR_VALUE 					   	-1000
#define MAX_STACK_SIZE 						100
#define START_ITERATION_END 				   	5
#define MAX_EMBEDDED_LOOPS 					100
#define MIDDLE_OF_BOARD 					500
#define TOTAL_NUM_INSTRUCTIONS 				  	41
#define MAX_PASSWORD_SIZE 					10
#define SCAN_SUCCESS 						1
#define NUM_INTS_PW_FILE 					1000
#define EXIT_CODE 						1
#define GAPS_BETWEEN_PRINTING 					1000
#define RECT_W							1
#define RECT_H 							1
#define WHITE 							255
#define PRINT_DELAY						100
#define WS_TRANS_CONST 						10
#define BINARY 							2
#define MAX_ANIM_SPEED 					   	10000
#define MIN_ANIM_SPEED						500
#define MIN_PASSWORD						0
#define MAX_PASSWORD 						1000
#define UPDATE_NUM 						100 

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
	int true_password;

};
typedef struct password_info password_info; 
