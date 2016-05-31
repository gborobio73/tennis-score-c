#pragma once
#include <stdbool.h>
#include "Score.h"

#define SCORES_INITIAL_SIZE 500;

typedef struct
{
    Score* scores; 
	int current_score_idx;
	int scores_size;
} MatchScore;

void match_schore_init(int, int);
void match_schore_end_match();
void match_schore_oponent_point();
void match_schore_your_point();
Score* match_schore_get_current_score();
void match_schore_cancel_last_point();
int match_schore_amount_of_scores();
bool match_score_is_match_over();
