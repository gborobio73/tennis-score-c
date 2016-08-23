#pragma once

#include "match_score.h"

typedef struct
{
	int opp_points;
	int you_points;
} MatchStatistics;

MatchStatistics match_statistics_calculate();