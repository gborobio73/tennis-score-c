#include "match_statistics.h"
#include "match_score.h"
#include "../common/const.h"

static MatchStatistics match_statistics;

MatchStatistics match_statistics_calculate(){
	match_statistics.opp_points =0;
	match_statistics.you_points =0;

	MatchScore match_score = match_score_get_match_score();

	APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_statistics_calculate  *** IDX %d ", match_score.current_score_idx); 

	for (int i = 0; i < match_score.current_score_idx; ++i)
	{
		if (match_score.scores[i].who_won_the_point == opp)
		{
			match_statistics.opp_points ++;
		}else
		{
			match_statistics.you_points ++;
		}
	}
	return match_statistics;
}