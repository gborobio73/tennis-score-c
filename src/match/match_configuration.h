#pragma once
#include <stdbool.h>

bool match_config_is_best_of_3_sets();
void match_config_set_best_of_3_sets();
void match_config_set_best_of_5_sets();
int match_config_get_best_of_sets();

bool match_config_does_opponent_serve();
int match_config_get_who_serves();
void match_config_set_opponent_serves();
void match_config_set_you_serve();
