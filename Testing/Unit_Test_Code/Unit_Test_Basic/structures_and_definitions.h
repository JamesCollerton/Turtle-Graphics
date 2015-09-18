//											ALL STRUCTURES AND DEFINITIONS.

//////////////////////////								Testing Preprocessing
#include "CUnit/Basic.h"

#define NUM_INSTRUCTIONS_DEFINED 	2
#define MAX_LOOP_SIZE 			20
#define CLEAR_FAIL 			1
#define FD 				1
#define LT 				1
#define RT 				1
#define DO 				1
#define SET 				1
#define ARBITRARY_NUM 			25
/////////////////////////

//											Regular Preprocessing
#define MAX_NUM_LINES 			100
#define MAX_SIZE_OF_LINE 		100
#define CLEAR_SUCCESS 			0
#define WWIDTH 				1000
#define WHEIGHT 			1000
#define NUM_LETTERS_ALPHABET 		26
#define RADIANS_CONST 			0.0174532925
#define ERROR_VALUE 			-1000
#define MAX_STACK_SIZE 			100
#define START_ITERATION_END 		5
#define MAX_EMBEDDED_LOOPS 		100
#define MIDDLE_OF_BOARD 		500
#define SCAN_SUCCESS 			1
#define WHITE 				255

#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %sOccured in %s, line %d\n\n", PHRASE, __FILE__, __LINE__); exit(1); }

// 											Enumerations & Typedefs.

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



// 											Structures.

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











//////////////////////////					Testing structures
struct test_instructions{
	success_unsuccess fd;
	success_unsuccess lt;
	success_unsuccess rt;
	success_unsuccess do_check;
	success_unsuccess set_check;
};
typedef struct test_instructions test_instructions;

struct do_loop_test_indicators{
	on_off FROM_correct;
	on_off TO_correct;
	on_off bracket_correct;

	on_off FROM_wrong;
	on_off TO_wrong;
	on_off bracket_wrong;
};
typedef struct do_loop_test_indicators do_loop_test_indicators;

struct polish_indicators{
	on_off end_statement_on;
	on_off operand_on;
};
typedef struct polish_indicators polish_indicators;

struct operand_indicators{
	on_off plus_indicator;
	on_off minus_indicator;
	on_off divide_indicator;
	on_off multiply_indicator;
};
typedef struct operand_indicators operand_indicators;

struct varnum_indicators{
	on_off number_indicator;
	on_off variable_indicator;
};
typedef struct varnum_indicators varnum_indicators;
/////////////////////////
