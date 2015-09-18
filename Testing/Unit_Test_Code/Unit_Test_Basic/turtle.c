/*

These are the unit test versions of my code compiled with CUnit. CUnit isn't on the lab
computers so these won't compile here. However please have a look at the code and the outputted
.txt files to see what was tested!

Rather than comment everything again, I kept commenting very minimal and instead it should be
mainly explained through the various print statements.

*/

#include "turtle_functions.h"

// 						Main

int main(int argc, char *argv[])
{
	program prog;
	player user;
	SDL_Simplewin sw;

	check_command_line_arguments(argc);

	initialise_program(&prog);

	initialise_player(&user);

	open_program_file(argv[1], &prog);

	parse_text_and_interpret(&prog, &user);

	clear_screen();

	Neill_SDL_Init(&sw);

	print_SDL_array(&user, &sw);

	return(0);
}
