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
static ScrollLayer* s_scroll_layer;

static TextLayer *s_sets_time_layer[5];
static TextLayer *s_sets_num_layer[5];

static char buffer_sets_time[5][9];
static char buffer_sets_num[5][2];

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    window_stack_pop(true);    
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    
}

static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static TextLayer* create_set_num_layer(GRect bounds, const char * text){
    TextLayer* s_text_layer = text_layer_create(bounds);

    text_layer_set_text(s_text_layer, text);
    text_layer_set_background_color(s_text_layer, GColorClear);
    text_layer_set_text_color(s_text_layer, GColorWhite);    
    text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
    fonts_set_text_layer_font_stats_small(s_text_layer);

    return s_text_layer;
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    s_title_layer = stats_window_common_create_title(bounds,  "SETS DURATION");
    
    s_scroll_layer = scroll_layer_create(bounds);
    scroll_layer_set_click_config_onto_window(s_scroll_layer, window);
    scroll_layer_set_content_size(s_scroll_layer, GSize(bounds.size.w, bounds.size.h * 1.7));
    
    scroll_layer_add_child(s_scroll_layer, text_layer_get_layer(s_title_layer));

    MatchStatistics score_detail= match_statistics_get();

    int start_from_y = 20 + PBL_IF_ROUND_ELSE(20, 10);

    int box_h = 40;
    float every_y = box_h +2;

    for (int i = 0; i < 5; ++i)
    {
        int hours = score_detail.set_duration[i] / 3600;
        int minutes = (score_detail.set_duration[i] / 60) % 60; 
        int seconds = score_detail.set_duration[i] % 60;        
        
        snprintf(buffer_sets_time[i], sizeof(buffer_sets_time[i]), "%.2d:%.2d:%.2d\n", hours, minutes, seconds);
        
        APP_LOG(APP_LOG_LEVEL_DEBUG, "*** window_load  *** set %d lasted %d seconds", 
            i, (int)score_detail.set_duration[i]);

        int padding = 28;
        int box_x = padding / 2 ;
        int box_w = bounds.size.w - padding;
        s_sets_time_layer[i] = stats_window_common_create_layer(
            GRect(
                box_x, start_from_y + (i * every_y),
                box_w, box_h), 
            buffer_sets_time[i],
            match_config_is_best_of_3_sets());

        
        int num_x = 2;
        int num_y = start_from_y + (i * every_y) + (box_h / 4);        
        snprintf(buffer_sets_num[i], sizeof(buffer_sets_num[i]), "%d\n", i + 1);
        s_sets_num_layer[i] =create_set_num_layer(GRect(num_x, num_y, 13, 20), buffer_sets_num[i]);

        scroll_layer_add_child(s_scroll_layer, text_layer_get_layer(s_sets_time_layer[i]));
        scroll_layer_add_child(s_scroll_layer, text_layer_get_layer(s_sets_num_layer[i]));
        layer_add_child(window_layer, scroll_layer_get_layer(s_scroll_layer));
    }
}

static void window_unload(Window *window) {
    text_layer_destroy(s_title_layer);  
    s_title_layer=NULL;  
    for (int i = 0; i < 5; ++i)        
    {
        text_layer_destroy(s_sets_time_layer[i]);  
        s_sets_time_layer[i]=NULL;  

        text_layer_destroy(s_sets_num_layer[i]);  
        s_sets_num_layer[i]=NULL;          
    }
	
    scroll_layer_destroy(s_scroll_layer);
    
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
