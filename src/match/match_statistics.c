#include "match_statistics.h"
#include "match_score.h"
#include "../common/const.h"

static MatchStatisticsPoints match_statistics_points;
static MatchTime match_time;

MatchTime match_statistics_calculate_match_duration(){
	time_t match_now;
	if (match_score_is_match_over())
	{
		match_now = match_score_get_match_score().match_ended;
	}else{
		match_now = time(NULL);
	}
    int difference_in_seconds = match_now - match_score_get_match_score().match_started ;
    match_time.minutes = ((difference_in_seconds ) / 60) % 60;
    match_time.hours = difference_in_seconds / 3600; 

    return match_time;
}

MatchStatisticsPoints match_statistics_calculate_points(){
	match_statistics_points.opp_points =123;
	match_statistics_points.you_points =147;

	MatchScore match_score = match_score_get_match_score();

	APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_statistics_calculate  *** IDX %d ", match_score.current_score_idx); 

	for (int i = 0; i < match_score.current_score_idx; ++i)
	{
		if (match_score.scores[i].who_won_the_point == opp)
		{
			match_statistics_points.opp_points ++;
		}
		else
		{
			match_statistics_points.you_points ++;
		}
	}
	return match_statistics_points;
}