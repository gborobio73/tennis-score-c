#pragma once
#include <stdbool.h>
#include "score.h"

typedef struct
{
    Score* scores; 
	int current_score_idx;
	int scores_size;
	time_t match_started;
	time_t match_ended;
} MatchScore;

void match_score_init(int, int, int, int); /* int who_starts_serving, int best_of_sets, int scr_initial_size, int scr_max_size */
void match_score_end_match();
void match_score_oponent_point();
void match_score_your_point();
Score* match_score_get_current_score();
void match_score_cancel_last_point();
bool match_score_is_match_over();
bool match_score_max_size_reached();
MatchScore match_score_get_match_score();
