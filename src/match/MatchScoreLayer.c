#include <pebble.h>
#include "Const.h"
#include "MatchScoreLayer.h"
#include "Score.h"

static char buffer_games_opp[2];
static char buffer_games_you[2];
static char buffer_sets_opp[2];
static char buffer_sets_you[2];

static char buffer_tie_break_points_opp[3];
static char buffer_tie_break_points_you[3];

MatchScoreLayer match_score_layer;

void set_text_layer_design(TextLayer* layer){
	text_layer_set_text_alignment(layer, GTextAlignmentCenter);
	text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	//text_layer_set_background_color(layer, GColorClear);
	text_layer_set_text_color(layer, GColorWhite);
	text_layer_set_background_color(layer, GColorBlue);
}

void set_point_layer_design(TextLayer* layer){
	set_text_layer_design(layer);
	text_layer_set_background_color(layer, GColorBlue);
}

void set_games_layer_design(TextLayer* layer){
	set_text_layer_design(layer);
	text_layer_set_background_color(layer, GColorGreen);
}

void set_sets_layer_design(TextLayer* layer){
	set_text_layer_design(layer);
	text_layer_set_background_color(layer, GColorOrange);
}

void set_who_serves_layer_design(TextLayer* layer){
	set_text_layer_design(layer);
	text_layer_set_background_color(layer, GColorShockingPink);
}

void init_match_score_layer(Layer *window_layer){
	//Who serves
	match_score_layer.s_text_who_serves_layer[opp] = text_layer_create(GRect(123, 51, 24, 32));
	text_layer_set_text(match_score_layer.s_text_who_serves_layer[opp], ".");
	set_who_serves_layer_design(match_score_layer.s_text_who_serves_layer[opp]);
	
	match_score_layer.s_text_who_serves_layer[you] = text_layer_create(GRect(123, 84, 24, 32));
	text_layer_set_text(match_score_layer.s_text_who_serves_layer[you], ".");
	set_who_serves_layer_design(match_score_layer.s_text_who_serves_layer[you]);
	//--
	
	match_score_layer.s_text_points_layer[opp] = text_layer_create(GRect(82, 51, 40, 32));
	text_layer_set_text(match_score_layer.s_text_points_layer[opp], ".");
	set_point_layer_design(match_score_layer.s_text_points_layer[opp]);
	
	match_score_layer.s_text_points_layer[you] = text_layer_create(GRect(82, 84, 40, 32));
	text_layer_set_text(match_score_layer.s_text_points_layer[you], ".");
	set_point_layer_design(match_score_layer.s_text_points_layer[you]);

	match_score_layer.s_text_games_layer[opp] = text_layer_create(GRect(41, 51, 40, 32));
	text_layer_set_text(match_score_layer.s_text_games_layer[opp], ".");
	set_games_layer_design(match_score_layer.s_text_games_layer[opp]);
	
	match_score_layer.s_text_games_layer[you] = text_layer_create(GRect(41, 84, 40, 32));
	text_layer_set_text(match_score_layer.s_text_games_layer[you], ".");
	set_games_layer_design(match_score_layer.s_text_games_layer[you]);

	match_score_layer.s_text_sets_layer[opp] = text_layer_create(GRect(0, 51, 40, 32));
	text_layer_set_text(match_score_layer.s_text_sets_layer[opp], ".");
	set_sets_layer_design(match_score_layer.s_text_sets_layer[opp]);
	
	match_score_layer.s_text_sets_layer[you] = text_layer_create(GRect(0, 84, 40, 32));
	text_layer_set_text(match_score_layer.s_text_sets_layer[you], ".");
	set_sets_layer_design(match_score_layer.s_text_sets_layer[you]);
	
	layer_add_child(window_layer, text_layer_get_layer(match_score_layer.s_text_points_layer[opp]));
  	layer_add_child(window_layer, text_layer_get_layer(match_score_layer.s_text_points_layer[you]));
  	layer_add_child(window_layer, text_layer_get_layer(match_score_layer.s_text_games_layer[opp]));
  	layer_add_child(window_layer, text_layer_get_layer(match_score_layer.s_text_games_layer[you]));
  	layer_add_child(window_layer, text_layer_get_layer(match_score_layer.s_text_sets_layer[opp]));
  	layer_add_child(window_layer, text_layer_get_layer(match_score_layer.s_text_sets_layer[you]));
  	layer_add_child(window_layer, text_layer_get_layer(match_score_layer.s_text_who_serves_layer[opp]));
  	layer_add_child(window_layer, text_layer_get_layer(match_score_layer.s_text_who_serves_layer[you]));
}

MatchScoreLayer get_match_score_layer(){
	return match_score_layer;
} 

void draw_who_serves(Score* score){
	if (score->who_serves == opp)
	{
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[opp], "X");
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[you], "");
	}else{
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[opp], "");
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[you], "X");
	}
}
void draw_points_games_and_sets(Score* score){
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "score->games[opp]: %s", buffer_games_opp);
	if (score->is_tie_break == true)
	{
		snprintf(buffer_tie_break_points_opp, 3, "%d", score->tie_break_points[opp]);	
		text_layer_set_text(match_score_layer.s_text_points_layer[opp], buffer_tie_break_points_opp);

		snprintf(buffer_tie_break_points_you, 3, "%d", score->tie_break_points[you]);	
		text_layer_set_text(match_score_layer.s_text_points_layer[you], buffer_tie_break_points_you);
	}else{
		text_layer_set_text(match_score_layer.s_text_points_layer[opp], score->points[opp]);
		text_layer_set_text(match_score_layer.s_text_points_layer[you], score->points[you]);		
	}	

	snprintf(buffer_games_opp, 2, "%d", score->games[opp]);	
	text_layer_set_text(match_score_layer.s_text_games_layer[opp], buffer_games_opp);

	snprintf(buffer_games_you, 2, "%d", score->games[you]);
	text_layer_set_text(match_score_layer.s_text_games_layer[you], buffer_games_you);
	
	snprintf(buffer_sets_opp, 2, "%d", score->sets[opp]);
	text_layer_set_text(match_score_layer.s_text_sets_layer[opp], buffer_sets_opp);

	snprintf(buffer_sets_you, 2, "%d", score->sets[you]);	
	text_layer_set_text(match_score_layer.s_text_sets_layer[you], buffer_sets_you);	
}

void match_score_layer_draw_score(Score* score){
	draw_who_serves(score);
	draw_points_games_and_sets(score);	
}

void destroy_match_score_layer(){
	text_layer_destroy(match_score_layer.s_text_points_layer[opp]);	 
	text_layer_destroy(match_score_layer.s_text_points_layer[you]);	 
	text_layer_destroy(match_score_layer.s_text_games_layer[opp]);	 
	text_layer_destroy(match_score_layer.s_text_games_layer[you]);	 
	text_layer_destroy(match_score_layer.s_text_sets_layer[opp]);	 
	text_layer_destroy(match_score_layer.s_text_sets_layer[you]);	 
	text_layer_destroy(match_score_layer.s_text_who_serves_layer[opp]);	 
	text_layer_destroy(match_score_layer.s_text_who_serves_layer[you]);	 
}