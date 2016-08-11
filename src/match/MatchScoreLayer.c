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

typedef struct 
{
	TextLayer *s_text_points_layer[2];
	TextLayer *s_text_games_layer[2];
	TextLayer *s_text_sets_layer[2];
	TextLayer *s_text_who_serves_layer[2];
	
} MatchScoreLayer;

static MatchScoreLayer match_score_layer;

static void set_text_layer_big_font(TextLayer* layer){
	static GFont s_font;
	s_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SCORE_FONT_34));
	text_layer_set_font(layer, s_font);
}

static void set_text_layer_colors(TextLayer* layer){
	text_layer_set_text_color(layer, GColorYellow);
	text_layer_set_background_color(layer, GColorBlack);
}

static void set_text_layer_colors_inverted(TextLayer* layer){
	text_layer_set_text_color(layer, GColorBlack);
	text_layer_set_background_color(layer, GColorYellow );
}

static void set_point_layer_design(TextLayer* layer){
	text_layer_set_text_alignment(layer, GTextAlignmentCenter);
	set_text_layer_big_font(layer);
	set_text_layer_colors_inverted(layer);	
}

static void set_games_layer_design(TextLayer* layer){
	text_layer_set_text_alignment(layer, GTextAlignmentCenter);	
	set_text_layer_big_font(layer);
	set_text_layer_colors(layer);	
}

static void set_sets_layer_design(TextLayer* layer){
	text_layer_set_text_alignment(layer, GTextAlignmentCenter);	
	set_text_layer_big_font(layer);
	set_text_layer_colors(layer);	
}	

static void set_who_serves_layer_design(TextLayer* layer){
	text_layer_set_text_alignment(layer, GTextAlignmentCenter);	
	set_text_layer_big_font(layer);
	//set_text_layer_colors(layer);	
	text_layer_set_text_color(layer, GColorYellow);
	text_layer_set_background_color(layer, GColorClear);
}

void match_score_layer_init(Layer *window_layer){
	int fromTopOppPx = 35;//37; //39;
	int fromTopYouPx = 84;//86;
	int heightPx = 45;
	int widthPx = 37;// 35;
	//Who serves
	match_score_layer.s_text_who_serves_layer[opp] = text_layer_create(GRect(128, fromTopOppPx, 14, heightPx));//116 - 24
	text_layer_set_text(match_score_layer.s_text_who_serves_layer[opp], ".");
	set_who_serves_layer_design(match_score_layer.s_text_who_serves_layer[opp]);
	
	match_score_layer.s_text_who_serves_layer[you] = text_layer_create(GRect(128, fromTopYouPx, 14, heightPx));//116
	text_layer_set_text(match_score_layer.s_text_who_serves_layer[you], ".");
	set_who_serves_layer_design(match_score_layer.s_text_who_serves_layer[you]);
	//--

	match_score_layer.s_text_points_layer[opp] = text_layer_create(GRect(89, fromTopOppPx, widthPx, heightPx));
	text_layer_set_text(match_score_layer.s_text_points_layer[opp], ".");
	set_point_layer_design(match_score_layer.s_text_points_layer[opp]);
	
	match_score_layer.s_text_points_layer[you] = text_layer_create(GRect(89, fromTopYouPx, widthPx, heightPx));//79
	text_layer_set_text(match_score_layer.s_text_points_layer[you], ".");
	set_point_layer_design(match_score_layer.s_text_points_layer[you]);

	match_score_layer.s_text_games_layer[opp] = text_layer_create(GRect(48, fromTopOppPx, widthPx, heightPx));//42
	text_layer_set_text(match_score_layer.s_text_games_layer[opp], ".");
	set_games_layer_design(match_score_layer.s_text_games_layer[opp]);
	
	match_score_layer.s_text_games_layer[you] = text_layer_create(GRect(48, fromTopYouPx, widthPx, heightPx));//42
	text_layer_set_text(match_score_layer.s_text_games_layer[you], ".");
	set_games_layer_design(match_score_layer.s_text_games_layer[you]);

	match_score_layer.s_text_sets_layer[opp] = text_layer_create(GRect(7, fromTopOppPx, widthPx, heightPx));//5
	text_layer_set_text(match_score_layer.s_text_sets_layer[opp], ".");
	set_sets_layer_design(match_score_layer.s_text_sets_layer[opp]);
	
	match_score_layer.s_text_sets_layer[you] = text_layer_create(GRect(7, fromTopYouPx, widthPx, heightPx));//5
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

static void draw_who_serves(Score* score){
	if (score->who_serves == opp)
	{
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[opp], "*");
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[you], "");
	}else{
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[opp], "");
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[you], "*");
	}
}
static void draw_points_games_and_sets(Score* score){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "score->games[opp]: %s", buffer_games_opp);
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