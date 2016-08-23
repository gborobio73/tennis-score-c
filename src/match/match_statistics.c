#include "match_statistics.h"
#include "match_score.h"
#include "../common/const.h"

static MatchStatisticsPoints match_statistics_points;

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