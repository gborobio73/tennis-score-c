#pragma once

#include "match_score.h"

typedef struct
{
	int opp_points;
	int you_points;
} MatchStatisticsPoints;

MatchStatisticsPoints match_statistics_calculate_points();