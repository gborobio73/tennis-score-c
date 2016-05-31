#pragma once

#include <pebble.h>
#include "Score.h"

typedef struct 
{
	TextLayer *s_text_points_layer[2];
	TextLayer *s_text_games_layer[2];
	TextLayer *s_text_sets_layer[2];
	TextLayer *s_text_who_serves_layer[2];
	
} MatchScoreLayer;

void match_score_layer_init(Layer* );
void match_score_layer_destroy();

MatchScoreLayer match_score_layer_get(); 

void match_score_layer_draw_score(Score* );
