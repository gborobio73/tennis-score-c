#include <stdbool.h>

#ifndef SCORE_H
#define SCORE_H

typedef char* Point;

typedef struct
{
    int who_serves;
    bool is_tie_break;
    bool match_is_over;
    int sets [2];
    int games [2];
    Point points [2];
    int tie_break_points [2];
    int best_of_sets;

} Score;

void copy_score_helper(Score* , Score* );

#endif