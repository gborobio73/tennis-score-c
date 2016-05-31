#include <pebble.h>
//#include <TimeLayer.h>

static TextLayer *s_time_layer;
static TextLayer *s_match_time_layer;
static time_t match_started;

void draw_time_layer(TextLayer *layer){
  // Improve the layout to be more like a watchface
  //GColorClear
  text_layer_set_background_color(layer, GColorArmyGreen);
  text_layer_set_text_color(layer, GColorWhite);
  text_layer_set_text(layer, "00:00");
  text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_LECO_26_BOLD_NUMBERS_AM_PM));
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
}

void time_layer_update_time() {
    // Get a tm structure
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);

    // Write the current hours and minutes into a buffer
    static char s_buffer[8];
    strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                            "%H:%M" : "%I:%M", tick_time);

    // Display this time on the TextLayer
    text_layer_set_text(s_time_layer, s_buffer);

    time_t match_now = time(NULL);
    int difference_in_seconds = match_now - match_started ;
    int minutes = ((difference_in_seconds ) / 60) % 60 ;//(totalSeconds / 60) % 60
    int hours = difference_in_seconds / 3600; 

    static char match_time_buffer [6];
    snprintf(match_time_buffer, sizeof(match_time_buffer), "%.2d:%.2d\n", hours, minutes);
    APP_LOG(APP_LOG_LEVEL_DEBUG, match_time_buffer);
    text_layer_set_text(s_match_time_layer, match_time_buffer);
}

void time_layer_init(Layer *window_layer){
    GRect bounds = layer_get_bounds(window_layer);
    //144, 168
    s_time_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(0, 0), bounds.size.w * 0.67, 30));
    draw_time_layer(s_time_layer);
    layer_add_child(window_layer, text_layer_get_layer(s_time_layer));

    s_match_time_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(bounds.size.h - 30, bounds.size.h - 30), bounds.size.w * 0.67, 30));
    draw_time_layer(s_match_time_layer);
    layer_add_child(window_layer, text_layer_get_layer(s_match_time_layer));

    match_started = time(NULL);
}

void time_layer_destroy(){
    text_layer_destroy(s_time_layer);  
    text_layer_destroy(s_match_time_layer);
    s_time_layer=NULL;  
}
