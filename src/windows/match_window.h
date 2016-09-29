#pragma once

#include <pebble.h>

#if defined(PBL_PLATFORM_APLITE) 	/* B/W first pebble max 180 scores */
  	#define SCORES_INITIAL_SIZE 90
	#define SCORES_MAX_SIZE 180
#else								/* pebble round (chalk), time (basalt) and time2 (diorite) */
  	#define SCORES_INITIAL_SIZE 300
	#define SCORES_MAX_SIZE 600
#endif

void match_window_push();
