#include "Const.h"
#include <stdbool.h>

static int best_of_sets =3;
static int who_serves =opp;

bool match_config_is_best_of_3_sets(){
	return best_of_sets == 3;
}
void match_config_set_best_of_3_sets(){
	best_of_sets = 3;
}

void match_config_set_best_of_5_sets(){
	best_of_sets = 5;
}

bool match_config_does_opponent_serve(){
	return who_serves == opp;
}
void match_config_set_opponent_serves(){
	who_serves =opp;
}
void match_config_set_you_serve(){
	who_serves =you;
}
