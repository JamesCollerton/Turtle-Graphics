//										WHITESPACE RELATED FUNCTIONS

void whitespace_functions(char *filename, whitespace_info *whitespace_prog);

void initialise_whitespace_prog(whitespace_info *whitespace_prog);

void initialise_program(program *prog);

void open_whitespace_program_file(char *filename, whitespace_info *whitespace_prog);

void strip_non_whitespace_components(char *filename);

void scan_in_whitespace_components(whitespace_info *whitespace_prog, char ch);

void initialise_decoder_array(whitespace_info *whitespace_prog);

void write_file_from_whitespace(whitespace_info *whitespace_prog);

void write_whitespace_prog_to_file(whitespace_info *whitespace_prog, FILE **prog_file);

void write_file_to_whitespace(program *reg_prog);

void write_prog_to_whitespace_file(program *reg_prog, FILE **prog_file);
