#include "dialog_choice_window.h"
#include "../common/texts.h"
#include "../common/const.h"

#if defined(PBL_PLATFORM_CHALK)
    #define SCORE_TEXT_X 20
    #define SCORE_TEXT_Y 22
#else
    #define SCORE_TEXT_X 0
    #define SCORE_TEXT_Y 10
#endif

static Window *s_statistics_window;
static TextLayer *s_title_layer;
static TextLayer *s_opp_points_layer;
static TextLayer *s_your_points_layer;

static void set_text_layer_config(TextLayer *s_text_layer){
    text_layer_set_background_color(s_text_layer, GColorClear);
    text_layer_set_text_color(s_text_layer, GColorWhite);
    text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
    text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    s_title_layer = text_layer_create(GRect((bounds.size.w / 2) - 40, (bounds.size.h / PBL_IF_ROUND_ELSE(4, 5)) - 20,80, 40));
    text_layer_set_text(s_title_layer, "POINTS WON");
    set_text_layer_config(s_title_layer);
    layer_add_child(window_layer, text_layer_get_layer(s_title_layer));    

    s_opp_points_layer = text_layer_create(GRect((bounds.size.w / 2) - 40, (bounds.size.h / 2) - 30,80, 40));
    text_layer_set_text(s_opp_points_layer, "opp 150");
    set_text_layer_config(s_opp_points_layer);
    text_layer_set_font(s_opp_points_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
    layer_add_child(window_layer, text_layer_get_layer(s_opp_points_layer));    

    s_your_points_layer = text_layer_create(GRect((bounds.size.w / 2) - 40, (bounds.size.h / 2) + 15,80, 40));
    text_layer_set_text(s_your_points_layer, "you 124");
    set_text_layer_config(s_your_points_layer);
    text_layer_set_font(s_your_points_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
    layer_add_child(window_layer, text_layer_get_layer(s_your_points_layer));    

    //PBL_IF_ROUND_ELSE((bounds.size.w - bitmap_bounds.size.w) / 2
}

static void window_unload(Window *window) {
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "*** dialog_choice_window window_unload *** unloading window"); 
    text_layer_destroy(s_title_layer);  
    s_title_layer=NULL;  

    window_destroy(window);
    s_statistics_window = NULL;
}

void statistics_window_push( ) {
    if(!s_statistics_window) 
    {
        s_statistics_window = window_create();
        window_set_background_color(s_statistics_window, PBL_IF_COLOR_ELSE(GColorMidnightGreen, GColorBlack));
        window_set_window_handlers(s_statistics_window, (WindowHandlers) {
            .load = window_load,
            .unload = window_unload,
        });
    }
    window_stack_push(s_statistics_window, true);
}
