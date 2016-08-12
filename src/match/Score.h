#pragma once

#include <stdbool.h>
#include <pebble.h>

typedef struct
{
    int who_serves;
    bool is_tie_break;
    bool match_is_over;
    int sets [2];
    int games [2];
    char* points [2];
    int tie_break_points [2];
    int best_of_sets;
    time_t time;

} Score;

void score_copy_to_from(Score* , Score*);
