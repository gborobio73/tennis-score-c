#pragma once

typedef struct
{
	int opp_points;
	int you_points;
} MatchStatsPoints;

typedef struct{
	int minutes;
	int hours;
} MatchStatsTime;

MatchStatsTime match_statistics_calculate_match_duration();
MatchStatsPoints match_statistics_calculate_points();