#pragma once

typedef struct
{
	int opp_points;
	int you_points;
} MatchStatisticsPoints;

typedef struct{
	int minutes;
	int hours;
} MatchTime;

MatchTime match_statistics_calculate_match_duration();
MatchStatisticsPoints match_statistics_calculate_points();