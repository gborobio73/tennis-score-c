#include "../common/texts.h"
#include "../common/const.h"
#include "../match/match_statistics.h"
#include "stats_time_window.h"
#include "stats_sets_time_window.h"
#include "stats_window_common.h"
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

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    window_stack_pop(true);    
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    stats_sets_time_window_push();
}

static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {    
    Layer *window_layer = window_get_root_layer(window);
    
    s_title_layer = stats_window_common_create_and_add_title(window,  "MATCH DURATION");

    GRect bounds = layer_get_bounds(window_layer);

    MatchDuration match_time = match_statistics_calculate_match_duration();
    static char match_time_buffer [9];
    snprintf(match_time_buffer, sizeof(match_time_buffer), "%.2d:%.2d:%.2d\n", 
        match_time.hours, match_time.minutes, match_time.seconds);
    // snprintf(match_time_buffer, sizeof(match_time_buffer), "%.2d:%.2d:%.2d\n", 
    //     4, 27, 35);

    int padding = PBL_IF_ROUND_ELSE(64, 28);
    int box_x = padding / 2 ;
    int box_w = bounds.size.w - padding;
    int box_h = 40;

    s_match_time_layer = stats_window_common_create_and_add_layer(
            window,
            GRect(
                box_x, (bounds.size.h / 2) - (box_h / 2),
                box_w, box_h), 
            match_time_buffer);

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
