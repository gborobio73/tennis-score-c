#pragma once

#include <pebble.h>

TextLayer* stats_window_common_create_title(Window *window, const char * text);
TextLayer* stats_window_common_create_layer(Window *window, GRect frame, const char * text, bool text_big);
