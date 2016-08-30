#pragma once

typedef struct{
	int minutes;
	int hours;
} MatchDuration;

typedef struct{	
	int set_results[2][5];	
	int set_duration[5];
	int points[2];
} MatchStatistics;

MatchDuration match_statistics_calculate_match_duration();

void match_statistics_calculate();
MatchStatistics match_statistics_get();
void match_statistics_destroy();
