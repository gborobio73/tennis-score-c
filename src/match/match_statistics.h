#pragma once

typedef struct
{
	int opp_points;
	int you_points;
} MatchStatistics;

MatchStatistics match_statistics;

MatchStatistics match_statistics_calculate();