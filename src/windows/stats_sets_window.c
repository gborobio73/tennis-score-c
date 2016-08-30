#include "../common/texts.h"
#include "../common/const.h"
#include "../match/match_statistics.h"
#include "../match/match_configuration.h"
#include "stats_points_window.h"
#include "stats_window_common.h"
#include "fonts.h"

#if defined(PBL_PLATFORM_CHALK)
    #define SCORE_TEXT_X 20
    #define SCORE_TEXT_Y 22
#else
    #define SCORE_TEXT_X 0
    #define SCORE_TEXT_Y 10
#endif

static Window *s_stats_sets_window;
static TextLayer *s_title_layer;

static TextLayer *s_opp_sets_layer[5];
static TextLayer *s_you_sets_layer[5];

static char buffer_games_opp[5][2];
static char buffer_games_you[5][2];

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    window_stack_pop(true);    
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    stats_points_window_push();
}

static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);

    s_title_layer = stats_window_common_create_title(window,  "SETS");

    GRect bounds = layer_get_bounds(window_layer);

    MatchStatistics score_detail= match_statistics_get();

    float left = match_config_get_best_of_sets() * 26 / 2;
    
    for (int i = 0; i < match_config_get_best_of_sets(); ++i)
    {
        snprintf(buffer_games_opp[i], 2, "%d", score_detail.set_results[opp][i]);

        s_opp_sets_layer[i] = stats_window_common_create_layer(
            window,
            GRect(
                (bounds.size.w / 2) - (left - i * 27), (bounds.size.h / 2) - 41,                
                25, 40), 
            buffer_games_opp[i],
            true);
    }

    for (int i = 0; i < match_config_get_best_of_sets(); ++i)
    {
        snprintf(buffer_games_you[i], 2, "%d", score_detail.set_results[you][i]);
        
        s_you_sets_layer[i] = stats_window_common_create_layer(
            window,
            GRect(
                (bounds.size.w / 2) - (left - i * 27), (bounds.size.h / 2) + 1,                
                25, 40), 
            buffer_games_you[i], true);
    }
}

static void window_unload(Window *window) {
    text_layer_destroy(s_title_layer);  
    s_title_layer=NULL;  
    for (int i = 0; i < match_config_get_best_of_sets(); ++i)
    {
        text_layer_destroy(s_opp_sets_layer[i]);  
        s_opp_sets_layer[i]=NULL;  

        text_layer_destroy(s_you_sets_layer[i]);  
        s_you_sets_layer[i]=NULL;  
    }
	
    window_destroy(window);
    s_stats_sets_window = NULL;
}

void stats_sets_window_push( ) {
    if(!s_stats_sets_window) 
    {
        s_stats_sets_window = window_create();
        window_set_background_color(s_stats_sets_window, PBL_IF_COLOR_ELSE(GColorMidnightGreen, GColorBlack));
        window_set_click_config_provider(s_stats_sets_window, click_config_provider);
        window_set_window_handlers(s_stats_sets_window, (WindowHandlers) {
            .load = window_load,
            .unload = window_unload,
        });
    }
    window_stack_push(s_stats_sets_window, true);
}
