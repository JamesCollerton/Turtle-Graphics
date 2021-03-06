/*
James Collerton
46114

Turtle - Extension

This is my extended version of the turtle program. There are two extensions that are detailed in the documentation,
a password based on hashing and a WhiteSpace translator.

The default password is '1'.

To use the below:

	./turtle: Prompts for password, then lets you change the password.
	./turtle filename: Opens regular .txt file and interprets as usual.
	./turtle WhiteSpace_file SECRET: Opens WhiteSpace file and parses and interprets it.
	./turtle filename TRANSLATE: Translates a regular file to WhiteSpace and saves is as reg_to_ws_translation.txt
	./turtle filename WhiteSpace_file COMBINE: Combines two files so that when run one way it will draw the
						   the regular picture, when run the other way it will draw the
					  	   WhiteSpace picture.


*/

#include "turtle_functions.h"

// 						Main

// Very similar to the original main. Mallocs space for all of the necessary components
// and then checks to see that they have been successfully allocated. Then it checks 
// the password entry. If it is accepted it carries out the different functionalities
// depending on the identity of the extra argument.

// If we've typed SECRET it translates the WhiteSpace back to regular and then opens the
// regular file (ws_to_reg_translation.txt) to be parsed. If we are doing anything but that
// or combining files it opens up the program file to be parsed and printed to screen.

// Then in the regular and SECRET cases we want to print something to screen and so we do that.
// otherwise if we're not changing the password we write a file to WhiteSpace

// Finally we free all of the components and return 0.

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
