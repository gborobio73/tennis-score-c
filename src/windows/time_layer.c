#include <pebble.h>
#include "../match/match_score.h"
#include "../match/match_statistics.h"

#if defined(PBL_PLATFORM_CHALK)
    #define CURRENT_TIME_X 27
    #define MATCH_TIME_X 89    
#else
    #define CURRENT_TIME_X 7
    #define MATCH_TIME_X 69    
#endif

static TextLayer *s_time_layer;
static TextLayer *s_match_time_layer;

static uint32_t resolve_font(){
    return PBL_IF_ROUND_ELSE(RESOURCE_ID_SCORE_FONT_20, RESOURCE_ID_SCORE_FONT_24);
}

static void draw_time_layer(TextLayer *layer){
    text_layer_set_background_color(layer, GColorClear); 
    text_layer_set_text_color(layer, GColorWhite); 
    text_layer_set_text(layer, "00:00");

    static GFont s_font;
    s_font = fonts_load_custom_font(resource_get_handle(resolve_font()));
    text_layer_set_font(layer, s_font);

    text_layer_set_text_alignment(layer, GTextAlignmentCenter);
}

static int resolve_Y(Layer *window_layer){
    GRect bounds = layer_get_bounds(window_layer);
    return PBL_IF_ROUND_ELSE(bounds.size.h - 42, bounds.size.h - 37);
}

void time_layer_update_time() {
    
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);

    static char s_buffer[8];
    strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);

    text_layer_set_text(s_time_layer, s_buffer);
}

void time_layer_update_match_duration()
{
    MatchStatsTime match_time = match_statistics_calculate_match_duration();

    static char match_time_buffer [6];
    snprintf(match_time_buffer, sizeof(match_time_buffer), "%.2d:%.2d\n", match_time.hours, match_time.minutes);
    text_layer_set_text(s_match_time_layer, match_time_buffer);
    layer_mark_dirty(text_layer_get_layer(s_match_time_layer));
}

void time_layer_init(Layer *window_layer){
    
    s_time_layer = text_layer_create(GRect(CURRENT_TIME_X, resolve_Y(window_layer), 58, 28));
    draw_time_layer(s_time_layer);
    layer_add_child(window_layer, text_layer_get_layer(s_time_layer));

    s_match_time_layer = text_layer_create(GRect(MATCH_TIME_X, resolve_Y(window_layer), 58, 28));
    draw_time_layer(s_match_time_layer);
    layer_add_child(window_layer, text_layer_get_layer(s_match_time_layer));
}

void time_layer_destroy(){
    text_layer_destroy(s_time_layer);  
    text_layer_destroy(s_match_time_layer);
    s_time_layer=NULL;  
}
