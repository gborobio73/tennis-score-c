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

static void draw_statistics_layer(TextLayer *layer){
    text_layer_set_background_color(layer, GColorClear);
    text_layer_set_text_color(layer, GColorWhite);
    text_layer_set_text(layer, "STATISTICS");
    
    static GFont s_font;
    s_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SCORE_FONT_15));
    text_layer_set_font(layer, s_font);

    text_layer_set_text_alignment(layer, GTextAlignmentCenter);
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    s_title_layer = text_layer_create(GRect(SCORE_TEXT_X, SCORE_TEXT_Y, 136, 27));
    draw_statistics_layer(s_title_layer);
    layer_add_child(window_layer, text_layer_get_layer(s_title_layer));    

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
