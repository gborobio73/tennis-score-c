#include "Const.h"
#include "Score.h"

void copy_score_helper(Score* destination_score, Score* source_score){

	destination_score->is_tie_break = source_score->is_tie_break;
    destination_score->match_is_over = source_score->match_is_over;
    destination_score->who_serves = source_score->who_serves;
    destination_score->best_of_sets = source_score->best_of_sets;

    destination_score->sets[opp] = source_score->sets[opp];
    destination_score->sets[you] = source_score->sets[you];
    
    destination_score->games[opp] = source_score->games[opp];
    destination_score->games[you] = source_score->games[you];
    
    destination_score->points[opp] =source_score->points[opp];
    destination_score->points[you] =source_score->points[you];
	destination_score->tie_break_points[opp] =source_score->tie_break_points[opp];
    destination_score->tie_break_points[you] =source_score->tie_break_points[you];
}
