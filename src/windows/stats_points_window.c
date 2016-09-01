#include "../common/texts.h"
#include "../common/const.h"
#include "../match/match_statistics.h"
#include "stats_points_window.h"
#include "stats_time_window.h"
#include "stats_window_common.h"
#include "fonts.h"

#if defined(PBL_PLATFORM_CHALK)
    #define SCORE_TEXT_X 20
    #define SCORE_TEXT_Y 22
#else
    #define SCORE_TEXT_X 0
    #define SCORE_TEXT_Y 10
#endif

static Window *s_stats_points_window;
static TextLayer *s_title_layer;
static TextLayer *s_points_layer[2];

static char buffer_points[2][4];

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    window_stack_pop(true);    
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    stats_time_window_push();    
}

static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
    MatchStatistics statistics = match_statistics_get();
    s_title_layer = stats_window_common_create_and_add_title(window,  "POINTS WON");

    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
    int box_w = 57.5;
    snprintf(buffer_points[opp], sizeof(buffer_points[opp]), "%.3d", statistics.points[opp]);    
    s_points_layer[opp] = stats_window_common_create_and_add_layer(
            window,
            GRect(
            (bounds.size.w / 2) - (box_w / 2), (bounds.size.h / 2) - 41,
            box_w, 40), 
            buffer_points[opp],
            true);

    snprintf(buffer_points[you], sizeof(buffer_points[you]), "%.3d", statistics.points[you]);    
    s_points_layer[you] = stats_window_common_create_and_add_layer(
        window,
        GRect(
            (bounds.size.w / 2) - (box_w / 2), (bounds.size.h / 2) + 1,
            box_w, 40), 
        buffer_points[you],
        true);
    
}

static void window_unload(Window *window) {
    text_layer_destroy(s_title_layer);  
    s_title_layer=NULL;  

	text_layer_destroy(s_points_layer[opp]);  
    s_points_layer[opp]=NULL; 

    text_layer_destroy(s_points_layer[you]);  
    s_points_layer[you]=NULL;  
    
    window_destroy(window);
    s_stats_points_window = NULL;
}

void stats_points_window_push( ) {
    if(!s_stats_points_window) 
    {
        s_stats_points_window = window_create();
        window_set_background_color(s_stats_points_window, PBL_IF_COLOR_ELSE(GColorMidnightGreen, GColorBlack));
        window_set_click_config_provider(s_stats_points_window, click_config_provider);
        window_set_window_handlers(s_stats_points_window, (WindowHandlers) {
            .load = window_load,
            .unload = window_unload,
        });
    }
    window_stack_push(s_stats_points_window, true);
}
