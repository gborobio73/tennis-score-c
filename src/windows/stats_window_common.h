#pragma once

#include <pebble.h>

TextLayer* stats_window_common_create_and_add_title(Window *window, const char * text);
TextLayer* stats_window_common_create_title(GRect bounds, const char * text);
TextLayer* stats_window_common_create_and_add_layer(Window *window, GRect frame, const char * text);
TextLayer* stats_window_common_create_layer(GRect frame, const char * text);
