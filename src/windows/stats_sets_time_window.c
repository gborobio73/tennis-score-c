#include "../common/texts.h"
#include "../common/const.h"
#include "../match/match_statistics.h"
#include "../match/match_configuration.h"
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

static Window *s_stats_sets_time_window;
static TextLayer *s_title_layer;

static TextLayer *s_sets_time_layer[5];

static char buffer_sets_time[5][9];

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
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    s_title_layer = stats_window_common_create_title(window,  "SETS DURATION");
    
    MatchStatistics score_detail= match_statistics_get();

    int start_from_y = 15 + PBL_IF_ROUND_ELSE(20, 10);
    if (match_config_is_best_of_3_sets())
    {
        start_from_y = start_from_y + 10;
    }

    float every_y = (bounds.size.h - start_from_y) / match_config_get_best_of_sets();

    for (int i = 0; i < match_config_get_best_of_sets(); ++i)
    {
        int hours = score_detail.set_duration[i] / 3600;
        int minutes = (score_detail.set_duration[i] / 60) % 60; 
        int seconds = score_detail.set_duration[i] % 60;        
        
        snprintf(buffer_sets_time[i], sizeof(buffer_sets_time[i]), "%.2d:%.2d:%.2d\n", hours, minutes, seconds);
        
        APP_LOG(APP_LOG_LEVEL_DEBUG, "*** window_load  *** set %d lasted %d seconds", 
            i, (int)score_detail.set_duration[i]);

        s_sets_time_layer[i] = stats_window_common_create_layer(
            window,
            GRect(
                bounds.origin.x, start_from_y + (i * every_y),
                bounds.size.w, 25), 
            buffer_sets_time[i],
            match_config_is_best_of_3_sets());
    }
}

static void window_unload(Window *window) {
    text_layer_destroy(s_title_layer);  
    s_title_layer=NULL;  
    for (int i = 0; i < match_config_get_best_of_sets(); ++i)
    {
        text_layer_destroy(s_sets_time_layer[i]);  
        s_sets_time_layer[i]=NULL;  
    }
	
    window_destroy(window);
    s_stats_sets_time_window = NULL;
}

void stats_sets_time_window_push( ) {
    if(!s_stats_sets_time_window) 
    {
        s_stats_sets_time_window = window_create();
        window_set_background_color(s_stats_sets_time_window, PBL_IF_COLOR_ELSE(GColorMidnightGreen, GColorBlack));
        window_set_click_config_provider(s_stats_sets_time_window, click_config_provider);
        window_set_window_handlers(s_stats_sets_time_window, (WindowHandlers) {
            .load = window_load,
            .unload = window_unload,
        });
    }
    window_stack_push(s_stats_sets_time_window, true);
}
