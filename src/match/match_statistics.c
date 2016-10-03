#include "match_statistics.h"
#include "match_configuration.h"
#include "match_score.h"
#include "../common/const.h"

static MatchDuration match_time;
static MatchStatistics* match_statistics = NULL;

static void calculate_points(Score score){
	match_statistics->points[score.who_won_the_point] ++;
}

static void initialize_structure(){
	if (match_statistics == NULL)
	{
		match_statistics = malloc(sizeof(MatchStatistics));
	}
	
	match_statistics->points[opp] = 0;
	match_statistics->points[you] = 0;

	for (int i = 0; i < 5; ++i)
	{
		match_statistics->set_results[opp][i] =0;
		match_statistics->set_results[you][i] =0;
		match_statistics->set_duration[i] =0;
	}
}

static bool is_new_set(Score score){
	return 	score.games[opp] == 0 && 
			score.games[you] == 0 &&
			strcmp(score.points[opp], love) ==0 && 
			strcmp(score.points[you], love) ==0;
}

static void calculate_games(Score previous_score, int who_won, int num_scores){
	int games[2];
	match_statistics->set_results[opp][num_scores] = previous_score.games[opp];
	match_statistics->set_results[you][num_scores] = previous_score.games[you];
	match_statistics->set_results[who_won][num_scores]++ ;
}

void match_statistics_calculate(){
	initialize_structure();

	MatchScore match_score = match_score_get_match_score();
	
	int num_scores=0;	
	
	time_t previous_set_duration= match_score.match_started;
	
	for (int i = 1; i <= match_score.current_score_idx && num_scores < match_config_get_best_of_sets(); ++i)
	{		
		if (is_new_set(match_score.scores[i]))
		{
			calculate_games(match_score.scores[i-1], match_score.scores[i].who_won_the_point, num_scores);
			match_statistics->set_duration[num_scores] =match_score.scores[i].time - previous_set_duration;
			
			num_scores ++;
			previous_set_duration = match_score.scores[i].time;
		}

		calculate_points(match_score.scores[i]);
	}
	
}

MatchDuration match_statistics_calculate_match_duration(){
	time_t match_now;
	if (match_score_is_match_over())
	{
		match_now = match_score_get_match_score().match_ended;
	}else{
		match_now = time(NULL);
	}
    int difference_in_seconds = match_now - match_score_get_match_score().match_started ;
    match_time.seconds = difference_in_seconds % 60;
    match_time.minutes = ((difference_in_seconds ) / 60) % 60;
    match_time.hours = difference_in_seconds / 3600; 

    return match_time;
}

MatchStatistics match_statistics_get(){
	return *match_statistics;
}
void match_statistics_destroy(){
	free(match_statistics);
	match_statistics=NULL;

}