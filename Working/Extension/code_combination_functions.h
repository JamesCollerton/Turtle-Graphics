//									COMBINING FILES FUNCTIONS

void combine_ws_reg_files(program *prog, whitespace_info *whitespace_prog, char *file_one, char *file_two);

void open_whitespace_program_file_verbatim(char *filename, whitespace_info *whitespace_prog);

void scan_in_whitespace_components_verbatim(whitespace_info *whitespace_prog, char ch);

void write_combination_to_file(program *prog, whitespace_info *whitespace_prog);

void print_combination_to_file(program *prog, whitespace_info *whitespace_prog, FILE **combined_file, int current_line);

void print_only_ws_to_file(whitespace_info *whitespace_prog, FILE **combined_file, int current_line);

void print_only_non_ws_to_file(program *prog, FILE **combined_file, int current_line);