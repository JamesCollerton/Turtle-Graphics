/*

This is the unit testing framework for the extension. Again, comments are only added to the new functions in
testing_functions.c and are kept minimal as I would hope that most of the information is given in the prints.

Please check the .txt output files in the necessary folders to see the outputs of these tests.

*/

#include "turtle_functions.h"

// 						Main

int main(int argc, char *argv[])
{

	program *prog = (program *) malloc(sizeof(program));
	player *user = (player *) malloc(sizeof(player));
	whitespace_info *whitespace_prog = (whitespace_info *) malloc(sizeof(whitespace_info));
	printing_board *first_board = (printing_board *) malloc(sizeof(printing_board));
	password_info *pw_info = (password_info *) malloc(sizeof(password_info));

	SDL_Simplewin sw;
	other_arg_type argument_indicator;

	check_initialisation(prog, user, whitespace_prog, first_board, pw_info);
	password_check(pw_info);

	if(pw_info -> pw_indicator == accept){

		check_command_line_arguments(user, argc, &argument_indicator, argv, pw_info);
		initialisation(prog, user, first_board);

		if(argument_indicator == secret){

			whitespace_functions(argv[1], whitespace_prog);
			open_program_file("ws_to_reg_translation.txt", prog);

		}
		else if(argument_indicator == combine_files){

			combine_ws_reg_files(prog, whitespace_prog, argv[1], argv[2]);

		}
		else if(argument_indicator != password_change){

			open_program_file(argv[1], prog);

		}

		if(argument_indicator == regular || argument_indicator == secret){

			parse_text_and_interpret(prog, user, first_board);

			printing(user, first_board, &sw);

		}
		else if(argument_indicator != password_change){

			write_file_to_whitespace(prog);

		}

	}

	free_components(first_board, prog, user, whitespace_prog, pw_info);

	return(0);
}
