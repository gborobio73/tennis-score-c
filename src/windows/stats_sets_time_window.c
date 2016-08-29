#include "../common/texts.h"
#include "../common/const.h"
#include "../match/match_statistics.h"
#include "../match/match_configuration.h"
#include "stats_time_window.h"
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

static char buffer_sets_time[5][15];

static void set_text_layer_config(TextLayer *s_text_layer){
    text_layer_set_background_color(s_text_layer, GColorClear);
    text_layer_set_text_color(s_text_layer, GColorWhite);    
    text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
}

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

    s_title_layer = text_layer_create(GRect((bounds.size.w / 2) - 60, PBL_IF_ROUND_ELSE(20, 10),120, 40));
    text_layer_set_text(s_title_layer, "SETS DURATION");
    set_text_layer_config(s_title_layer);
    fonts_set_text_layer_font_20(s_title_layer);
    layer_add_child(window_layer, text_layer_get_layer(s_title_layer));    

    float top = (match_config_get_best_of_sets() * 20 / 2);
    for (int i = 0; i < match_config_get_best_of_sets(); ++i)
    {
        s_sets_time_layer[i] = text_layer_create(
            GRect(
            (bounds.size.w / 2) - 40, 
            (bounds.size.h / 2) - (top - i * 20),
            80, 40));
        
        snprintf(buffer_sets_time[i], 15, "SET %d", i);
        // APP_LOG(APP_LOG_LEVEL_DEBUG, "*** window_load  *** opp %s ", buffer_games_opp[i]); 
        text_layer_set_text(s_sets_time_layer[i], buffer_sets_time[i]);
        set_text_layer_config(s_sets_time_layer[i]);
        fonts_set_text_layer_font_20(s_sets_time_layer[i]); 
        text_layer_set_text_alignment(s_sets_time_layer[i], GTextAlignmentLeft);
        layer_add_child(window_layer, text_layer_get_layer(s_sets_time_layer[i]));
    }

    // MatchStatistics score_detail= match_statistics_get();

    // float left = match_config_get_best_of_sets() * 25 / 2;
    
    // for (int i = 0; i < match_config_get_best_of_sets(); ++i)
    // {
    //     s_opp_sets_layer[i] = text_layer_create(GRect((bounds.size.w / 2) - (left - i * 25), (bounds.size.h / 2) - 30,25, 40));
        
    //     snprintf(buffer_games_opp[i], 2, "%d", score_detail.set_results[opp][i]);
    //     // APP_LOG(APP_LOG_LEVEL_DEBUG, "*** window_load  *** opp %s ", buffer_games_opp[i]); 
    //     text_layer_set_text(s_opp_sets_layer[i], buffer_games_opp[i]);
    //     set_text_layer_config(s_opp_sets_layer[i]);
    //     fonts_set_text_layer_font_34(s_opp_sets_layer[i]); 
    //     layer_add_child(window_layer, text_layer_get_layer(s_opp_sets_layer[i]));
    // }

    // for (int i = 0; i < match_config_get_best_of_sets(); ++i)
    // {
    //     s_you_sets_layer[i] = text_layer_create(GRect((bounds.size.w / 2) - (left - i * 25), (bounds.size.h / 2) + 15,25, 40));
        
    //     snprintf(buffer_games_you[i], 2, "%d", score_detail.set_results[you][i]);
    //     // APP_LOG(APP_LOG_LEVEL_DEBUG, "*** window_load  *** you %s ", buffer_games_you[i]); 
    //     text_layer_set_text(s_you_sets_layer[i], buffer_games_you[i]);
    //     set_text_layer_config(s_you_sets_layer[i]);
    //     fonts_set_text_layer_font_34(s_you_sets_layer[i]); 
    //     layer_add_child(window_layer, text_layer_get_layer(s_you_sets_layer[i]));
    // }
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
