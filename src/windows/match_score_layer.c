#include <pebble.h>
#include "../match/const.h"
#include "../match/score.h"
#include "../common/texts.h"
#include "match_score_layer.h"


#if defined(PBL_PLATFORM_CHALK)
	#define SETS_X 27
	#define GAMES_X 68
	#define POINTS_X 109
	#define WHO_SERVES_X 148
	#define OPPONENT_Y 45
	#define YOU_Y 94
#else
  	#define SETS_X 7
	#define GAMES_X 48
	#define POINTS_X 89
	#define WHO_SERVES_X 128
	#define OPPONENT_Y 35
	#define YOU_Y 84
#endif

#define SCORE_BOX_WIDTH 37
#define WHO_SERVES_BOX_WIDTH 14
#define SCORE_BOX_HEIGHT 45

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
	GFont s_font;
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
	text_layer_set_text_color(layer, GColorYellow);
	text_layer_set_background_color(layer, GColorClear);
}

static void draw_who_serves(Score* score){
	if (score->who_serves == opp)
	{
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[opp], WHO_SERVES_MARK);
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[you], EMPTY_TEXT);
	}else{
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[opp], EMPTY_TEXT);
		text_layer_set_text(match_score_layer.s_text_who_serves_layer[you], WHO_SERVES_MARK);
	}
	layer_mark_dirty(text_layer_get_layer(match_score_layer.s_text_who_serves_layer[opp]));
	layer_mark_dirty(text_layer_get_layer(match_score_layer.s_text_who_serves_layer[you]));
}

static void draw_points(Score* score){
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
	layer_mark_dirty(text_layer_get_layer(match_score_layer.s_text_points_layer[opp]));
	layer_mark_dirty(text_layer_get_layer(match_score_layer.s_text_points_layer[you]));
}

static void draw_games(Score* score){
	snprintf(buffer_games_opp, 2, "%d", score->games[opp]);	
	text_layer_set_text(match_score_layer.s_text_games_layer[opp], buffer_games_opp);

	snprintf(buffer_games_you, 2, "%d", score->games[you]);
	text_layer_set_text(match_score_layer.s_text_games_layer[you], buffer_games_you);

	layer_mark_dirty(text_layer_get_layer(match_score_layer.s_text_games_layer[opp]));
	layer_mark_dirty(text_layer_get_layer(match_score_layer.s_text_games_layer[you]));
}

static void draw_sets(Score* score){
	snprintf(buffer_sets_opp, 2, "%d", score->sets[opp]);
	text_layer_set_text(match_score_layer.s_text_sets_layer[opp], buffer_sets_opp);

	snprintf(buffer_sets_you, 2, "%d", score->sets[you]);	
	text_layer_set_text(match_score_layer.s_text_sets_layer[you], buffer_sets_you);	

	layer_mark_dirty(text_layer_get_layer(match_score_layer.s_text_sets_layer[opp]));
	layer_mark_dirty(text_layer_get_layer(match_score_layer.s_text_sets_layer[you]));
}

void match_score_layer_init(Layer *window_layer){
	int heightPx = 45;
	int widthPx = 37;
	
	match_score_layer.s_text_who_serves_layer[opp] = text_layer_create(GRect(WHO_SERVES_X, OPPONENT_Y, WHO_SERVES_BOX_WIDTH, SCORE_BOX_HEIGHT));
	text_layer_set_text(match_score_layer.s_text_who_serves_layer[opp], EMPTY_TEXT);
	set_who_serves_layer_design(match_score_layer.s_text_who_serves_layer[opp]);
	
	match_score_layer.s_text_who_serves_layer[you] = text_layer_create(GRect(WHO_SERVES_X, YOU_Y, WHO_SERVES_BOX_WIDTH, SCORE_BOX_HEIGHT));
	text_layer_set_text(match_score_layer.s_text_who_serves_layer[you], EMPTY_TEXT);
	set_who_serves_layer_design(match_score_layer.s_text_who_serves_layer[you]);
	
	match_score_layer.s_text_points_layer[opp] = text_layer_create(GRect(POINTS_X, OPPONENT_Y, SCORE_BOX_WIDTH, SCORE_BOX_HEIGHT));
	text_layer_set_text(match_score_layer.s_text_points_layer[opp], EMPTY_TEXT);
	set_point_layer_design(match_score_layer.s_text_points_layer[opp]);
	
	match_score_layer.s_text_points_layer[you] = text_layer_create(GRect(POINTS_X, YOU_Y, SCORE_BOX_WIDTH, SCORE_BOX_HEIGHT));
	text_layer_set_text(match_score_layer.s_text_points_layer[you], EMPTY_TEXT);
	set_point_layer_design(match_score_layer.s_text_points_layer[you]);

	match_score_layer.s_text_games_layer[opp] = text_layer_create(GRect(GAMES_X, OPPONENT_Y, SCORE_BOX_WIDTH, SCORE_BOX_HEIGHT));
	text_layer_set_text(match_score_layer.s_text_games_layer[opp], EMPTY_TEXT);
	set_games_layer_design(match_score_layer.s_text_games_layer[opp]);
	
	match_score_layer.s_text_games_layer[you] = text_layer_create(GRect(GAMES_X, YOU_Y, SCORE_BOX_WIDTH, SCORE_BOX_HEIGHT));
	text_layer_set_text(match_score_layer.s_text_games_layer[you], EMPTY_TEXT);
	set_games_layer_design(match_score_layer.s_text_games_layer[you]);

	match_score_layer.s_text_sets_layer[opp] = text_layer_create(GRect(SETS_X, OPPONENT_Y, SCORE_BOX_WIDTH, SCORE_BOX_HEIGHT));
	text_layer_set_text(match_score_layer.s_text_sets_layer[opp], EMPTY_TEXT);
	set_sets_layer_design(match_score_layer.s_text_sets_layer[opp]);
	
	match_score_layer.s_text_sets_layer[you] = text_layer_create(GRect(SETS_X, YOU_Y, SCORE_BOX_WIDTH, SCORE_BOX_HEIGHT));
	text_layer_set_text(match_score_layer.s_text_sets_layer[you], EMPTY_TEXT);
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


void match_score_layer_draw_score(Score* score){
	draw_who_serves(score);
	draw_points(score);
	draw_games(score);	
	draw_sets(score);	
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