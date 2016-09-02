#include "fonts.h"

static GFont s_font_20 = NULL;
static GFont s_font_34 = NULL;
static GFont s_font_stats_big = NULL;
static GFont s_font_stats_small = NULL;
static GFont s_font_stats_medium = NULL;

void fonts_set_text_layer_font_20(TextLayer *s_text_layer){
	if (s_font_20 == NULL)
	{
		s_font_20 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SCORE_FONT_20));
	}	
    text_layer_set_font(s_text_layer, s_font_20);
}

void fonts_set_text_layer_font_34(TextLayer *s_text_layer){
	if (s_font_34 == NULL)
	{
		s_font_34 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SCORE_FONT_34));
	}	
    text_layer_set_font(s_text_layer, s_font_34);
}

void fonts_set_text_layer_font_stats_big(TextLayer *s_text_layer){
	if (s_font_stats_big == NULL)
	{
		s_font_stats_big = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SCORE_FONT_34));
	}	
    text_layer_set_font(s_text_layer, s_font_stats_big);
}

void fonts_set_text_layer_font_stats_small(TextLayer *s_text_layer){
	if (s_font_stats_small == NULL)
	{
		s_font_stats_small = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SCORE_FONT_15));
	}	
    text_layer_set_font(s_text_layer, s_font_stats_small);
}

void fonts_set_text_layer_font_stats_medium(TextLayer *s_text_layer){
	if (s_font_stats_medium)
	{
		s_font_stats_medium = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_STATS_19));
	}	
    text_layer_set_font(s_text_layer, s_font_stats_medium);
}
