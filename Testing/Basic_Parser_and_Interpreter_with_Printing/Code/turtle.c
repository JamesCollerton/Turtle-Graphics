/*

This is the test code with the embedded print statements. I have not commented it as you can
refer to the working version for very thorough explanations of what is going on at each point.

Feel free to run it and see the type of output it generates!

*/

#include "turtle_functions.h"

// 						Main

int main(int argc, char *argv[])
{
	program *prog = (program *) malloc(sizeof(program));
	player *user = (player *) malloc(sizeof(player));
	SDL_Simplewin sw;

	check_command_line_arguments(argc);

	initialise_program(prog);

	initialise_player(user);

	open_program_file(argv[1], prog);

	parse_text_and_interpret(prog, user);

	Neill_SDL_Init(&sw);

	print_SDL_array(user, &sw);

	free(prog);
	free(user);

	return(0);
}
