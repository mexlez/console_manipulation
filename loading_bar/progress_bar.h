/*
	A struct designed to contain all of the necessary info for a basic progress bar. The
	bar_string is the actual string that is written out, and should be used with malloc:
	mybar->bar_output = malloc(mybar->width + 1)
*/
typedef struct progress_bar{
	int width;
	char bar_char;
	bool verbose;
	char *bar_string;
} progress_bar_t;

int update_progress(double percent, progress_bar_t *bar);
progress_bar_t *setup_progress(char bar_char, char bar_start, char bar_end, int bar_width, bool verbose);
