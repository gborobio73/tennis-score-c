#include "stats_window_common.h"
#include "fonts.h"

static void set_text_layer_config(TextLayer *s_text_layer){
    text_layer_set_background_color(s_text_layer, GColorBlack);
    text_layer_set_text_color(s_text_layer, GColorYellow);    
    text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
}

TextLayer* stats_window_common_create_title(GRect bounds, const char * text){
	TextLayer* s_title_layer = text_layer_create(
        GRect(
            bounds.origin.x, PBL_IF_ROUND_ELSE(15, 10),
            bounds.size.w, 20));

    text_layer_set_text(s_title_layer, text);
    text_layer_set_background_color(s_title_layer, GColorClear);
    text_layer_set_text_color(s_title_layer, GColorWhite);    
    text_layer_set_text_alignment(s_title_layer, GTextAlignmentCenter);
    fonts_set_text_layer_font_stats_small(s_title_layer);

    return s_title_layer;
}

TextLayer* stats_window_common_create_and_add_title(Window *window, const char * text){
	Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    TextLayer* s_title_layer = stats_window_common_create_title(bounds, text);

    layer_add_child(window_layer, text_layer_get_layer(s_title_layer));  

    return s_title_layer;
}

TextLayer* stats_window_common_create_layer(GRect frame, const char * text){
	TextLayer* s_text_layer = text_layer_create(frame);
    
    text_layer_set_text(s_text_layer, text);
    set_text_layer_config(s_text_layer);
    fonts_set_text_layer_font_stats_big(s_text_layer); 	
    
    return s_text_layer;
}

TextLayer* stats_window_common_create_and_add_layer(Window *window, GRect frame, const char * text){	
	TextLayer* s_text_layer = stats_window_common_create_layer(frame, text);
    
    Layer *window_layer = window_get_root_layer(window);    
    
    layer_add_child(window_layer, text_layer_get_layer(s_text_layer));

    return s_text_layer;
}
