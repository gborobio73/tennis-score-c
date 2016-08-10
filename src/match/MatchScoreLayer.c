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

static void set_text_layer_design(TextLayer* layer){
	text_layer_set_text_alignment(layer, GTextAlignmentCenter);
	//text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	
	// Load the custom font
	static GFont s_font;
	s_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SCORE_FONT_34));
	text_layer_set_font(layer, s_font);

	//text_layer_set_background_color(layer, GColorClear);
	text_layer_set_text_color(layer, GColorYellow);
	text_layer_set_background_color(layer, GColorBlack);
}

static void set_point_layer_design(TextLayer* layer){
	set_text_layer_design(layer);
	text_layer_set_text_color(layer, GColorBlack);
	text_layer_set_background_color(layer, GColorYellow );
}

static void set_games_layer_design(TextLayer* layer){
	set_text_layer_design(layer);
}

static void set_sets_layer_design(TextLayer* layer){
	set_text_layer_design(layer);
}

static void set_who_serves_layer_design(TextLayer* layer){
	set_text_layer_design(layer);
}

void match_score_layer_init(Layer *window_layer){
	int fromTopOppPx = 39;
	int fromTopYouPx = 86;
	int heightPx = 45;
	int widthPx = 35;
	//Who serves
	match_score_layer.s_text_who_serves_layer[opp] = text_layer_create(GRect(116, fromTopOppPx, 24, heightPx));
	text_layer_set_text(match_score_layer.s_text_who_serves_layer[opp], ".");
	set_who_serves_layer_design(match_score_layer.s_text_who_serves_layer[opp]);
	
	match_score_layer.s_text_who_serves_layer[you] = text_layer_create(GRect(116, fromTopYouPx, 24, heightPx));
	text_layer_set_text(match_score_layer.s_text_who_serves_layer[you], ".");
	set_who_serves_layer_design(match_score_layer.s_text_who_serves_layer[you]);
	//--
	
	match_score_layer.s_text_points_layer[opp] = text_layer_create(GRect(79, fromTopOppPx, widthPx, heightPx));
	text_layer_set_text(match_score_layer.s_text_points_layer[opp], ".");
	set_point_layer_design(match_score_layer.s_text_points_layer[opp]);
	
	match_score_layer.s_text_points_layer[you] = text_layer_create(GRect(79, fromTopYouPx, widthPx, heightPx));
	text_layer_set_text(match_score_layer.s_text_points_layer[you], ".");
	set_point_layer_design(match_score_layer.s_text_points_layer[you]);

	match_score_layer.s_text_games_layer[opp] = text_layer_create(GRect(42, fromTopOppPx, widthPx, heightPx));
	text_layer_set_text(match_score_layer.s_text_games_layer[opp], ".");
	set_games_layer_design(match_score_layer.s_text_games_layer[opp]);
	
	match_score_layer.s_text_games_layer[you] = text_layer_create(GRect(42, fromTopYouPx, widthPx, heightPx));
	text_layer_set_text(match_score_layer.s_text_games_layer[you], ".");
	set_games_layer_design(match_score_layer.s_text_games_layer[you]);

	match_score_layer.s_text_sets_layer[opp] = text_layer_create(GRect(5, fromTopOppPx, widthPx, heightPx));
	text_layer_set_text(match_score_layer.s_text_sets_layer[opp], ".");
	set_sets_layer_design(match_score_layer.s_text_sets_layer[opp]);
	
	match_score_layer.s_text_sets_layer[you] = text_layer_create(GRect(5, fromTopYouPx, widthPx, heightPx));
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

MatchScoreLayer match_score_layer_get(){
	return match_score_layer;
} 

static void draw_who_serves(Score* score){
	if (score->who_serves == opp)
	{
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[opp], "X");
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[you], "");
	}else{
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[opp], "");
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[you], "X");
	}
}
static void draw_points_games_and_sets(Score* score){
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

void match_score_layer_destroy(){
	text_layer_destroy(match_score_layer.s_text_points_layer[opp]);	 
	text_layer_destroy(match_score_layer.s_text_points_layer[you]);	 
	text_layer_destroy(match_score_layer.s_text_games_layer[opp]);	 
	text_layer_destroy(match_score_layer.s_text_games_layer[you]);	 
	text_layer_destroy(match_score_layer.s_text_sets_layer[opp]);	 
	text_layer_destroy(match_score_layer.s_text_sets_layer[you]);	 
	text_layer_destroy(match_score_layer.s_text_who_serves_layer[opp]);	 
	text_layer_destroy(match_score_layer.s_text_who_serves_layer[you]);	 
}