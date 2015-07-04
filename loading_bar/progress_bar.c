/*
A simple console-based progress bar. Takes a float in the range 0-1.0 (percent/100)
and updates a simple text progress bar. The progress bar is only re-printed when 
update_progress is called.
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "progress_bar.h"

/*
	Setup the progress bar.
		Inputs:
			bar_char: the character used to fill in the progress bar (cosmetic)
			bar_start: the bracket that denotes the start of the progress bar (cosmetic)
			bar_end: the character that denotes the end of the progress bar (cosmetic)
			bar_width: The total WIDTH of the progress bar, in number of characters
			verbose: Defines if the bar should list a % as well as the graphical bar 
		Outputs: 
			progress_bar_t *new_bar: A pointer to a progress_bar_t struct
*/
progress_bar_t *
setup_progress(char bar_char, char bar_start, char bar_end, int bar_width, bool verbose){
	progress_bar_t *new_bar = malloc(sizeof(progress_bar_t));
	if (new_bar == NULL){
		printf("Something went wrong trying to allocate memory in setup_progress: %s", strerror(errno));
		return NULL;
	}
	new_bar->bar_char = bar_char;
	new_bar->width = bar_width;
	new_bar->verbose = verbose;
	new_bar->bar_string = malloc(bar_width + 1);
	if (new_bar->bar_string == NULL){
		printf("Something went wrong trying to allocate memory in setup_progress: %s", strerror(errno));
		return NULL;	
	}
	memset(new_bar->bar_string, ' ', bar_width + 1);
	//Insert the bar start character and terminate the whole string
	new_bar->bar_string[0] = bar_start;
	new_bar->bar_string[bar_width] = 0;

	if (verbose){
		//Make space for a percent counter at the right side of the progress bar
		new_bar->bar_string[bar_width - 5] = bar_end;
		new_bar->bar_string[bar_width - 1] = '%';
	}else{
		//
		new_bar->bar_string[bar_width - 1] = bar_end; 
	}
	return new_bar;
}

/*
	Update (rewrite) the progress bar with the current progress. Does not save previous
	progress state, so can be safely used to indicate negative progress.
		Inputs:
			percent: The percent to set the bar to. In range 0-1.0, and silently forced 
				to 0 or 1.0 if set outside this range.
			bar: A progress_bar_t for the particular progress bar that you want to update
*/
int
update_progress(double percent, progress_bar_t *bar){
	int progress;
	int display_percent;
	//tmp only has to be big enough to hold a string with 3 digits
	char tmp[]="100";
	if(percent > 1.0f){
		percent = 1.0f;
	}else if (percent < 0.0f){
		percent = 0.0f;
	}
	if (bar->verbose == true){
		progress = floor((bar->width-6)*percent);
		//Use springf to turn our display_percent into a nice string, then copy only the first 3
		//characters to bar_string so we don't prematurely terminate the bar_string
		display_percent = ((int)(percent * 100));
		if (0 > sprintf(tmp, "%3i", display_percent)){
			printf("Something went wrong trying to do strings in update_progress: %s", strerror(errno));
			return errno;
		}
		strncpy(&(bar->bar_string)[(bar->width) - 4], tmp, 3);
	}else{
		progress = floor((bar->width-2)*percent);
	}
	for (int i=1; i <= progress; i++){
		(bar->bar_string)[i] = bar->bar_char;
	}
	
	printf("\r%s", bar->bar_string);
	if (percent == 1.0f){
		printf("\n");
	}
	fflush(stdout);
	return 0;
}

