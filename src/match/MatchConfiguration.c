#include "Const.h"

static int best_of_sets =3;
static int who_serves =opp;

int match_config_is_best_of_3_sets(){
	return best_of_sets == 3;
}
void match_config_set_best_of_3_sets(){
	best_of_sets = 3;
}

void match_config_set_best_of_5_sets(){
	best_of_sets = 5;
}

void match_config_set_opponents_serves(){
	who_serves =opp;
}
void match_config_you_serve(){
	who_serves =you;
}
