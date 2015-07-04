/*
A simple demo showing how to use progress_bar. Creates a progress bar 70 characters
wide that increments by 1% every 200ms.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "progress_bar.h"

#define MILLISEC 1000


int
main(){
	progress_bar_t *mybar = setup_progress('=', '[', ']',70, true);
	printf("\n");
	for (int i=0;i<=100;i=i+1){
		update_progress(((double)i)/100, mybar);
		usleep(200*MILLISEC);
	}
}