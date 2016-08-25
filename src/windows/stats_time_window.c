#include "../common/texts.h"
#include "../common/const.h"
#include "../match/match_statistics.h"
#include "stats_time_window.h"
#include "fonts.h"

#if defined(PBL_PLATFORM_CHALK)
    #define SCORE_TEXT_X 20
    #define SCORE_TEXT_Y 22
#else
    #define SCORE_TEXT_X 0
    #define SCORE_TEXT_Y 10
#endif

static Window *s_stats_time_window;
static TextLayer *s_title_layer;
static TextLayer *s_match_time_layer;

static void set_text_layer_config(TextLayer *s_text_layer){
    text_layer_set_background_color(s_text_layer, GColorClear);
    text_layer_set_text_color(s_text_layer, GColorWhite);    
    text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    window_stack_pop(true);    
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    
}

static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {    
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    s_title_layer = text_layer_create(GRect((bounds.size.w / 2) - 60, (bounds.size.h / PBL_IF_ROUND_ELSE(4, 4)) - 20,120, 40));
    text_layer_set_text(s_title_layer, "MATCH DURATION");
    set_text_layer_config(s_title_layer);
    fonts_set_text_layer_font_20(s_title_layer);
    layer_add_child(window_layer, text_layer_get_layer(s_title_layer));    

    MatchTime match_time = match_statistics_calculate_match_duration();
    static char match_time_buffer [6];
    snprintf(match_time_buffer, sizeof(match_time_buffer), "%.2d:%.2d\n", match_time.hours, match_time.minutes);

    s_match_time_layer = text_layer_create(GRect((bounds.size.w / 2) - 40, (bounds.size.h / 2) - 20,80, 40));
    text_layer_set_text(s_match_time_layer, match_time_buffer);
    set_text_layer_config(s_match_time_layer);
    fonts_set_text_layer_font_34(s_match_time_layer);
    layer_add_child(window_layer, text_layer_get_layer(s_match_time_layer));    
}

static void window_unload(Window *window) {
    text_layer_destroy(s_title_layer);  
    s_title_layer=NULL;  

	text_layer_destroy(s_match_time_layer);  
    s_match_time_layer=NULL;  

    window_destroy(window);
    s_stats_time_window = NULL;
}

void stats_time_window_push( ) {
    if(!s_stats_time_window) 
    {
        s_stats_time_window = window_create();
        window_set_background_color(s_stats_time_window, PBL_IF_COLOR_ELSE(GColorMidnightGreen, GColorBlack));
        window_set_click_config_provider(s_stats_time_window, click_config_provider);
        window_set_window_handlers(s_stats_time_window, (WindowHandlers) {
            .load = window_load,
            .unload = window_unload,
        });
    }
    window_stack_push(s_stats_time_window, true);
}
