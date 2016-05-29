#include "Score.h"
#ifndef MATCHSCORE_H
#define MATCHSCORE_H

typedef struct
{
    Score* scores; // 5 * 13 *16
	//Score* scores [1040]; // 5 * 13 *16
} MatchScore;

void init_match_schore(int, int);
void end_match();
void oponentPoint();
void yourPoint();
Score* get_current_score();
void cancel_last_point();
int amount_of_scores();

#endif

/*

Score** score;

score -> 	| * score |
			| * score |
			| * score |
			| * score |
			| * score |
*/