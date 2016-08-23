#include "fonts.h"

void fonts_set_text_layer_font_20(TextLayer *s_text_layer){
	GFont s_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SCORE_FONT_20));
    text_layer_set_font(s_text_layer, s_font);
}

void fonts_set_text_layer_font_34(TextLayer *s_text_layer){
	GFont s_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SCORE_FONT_34));
    text_layer_set_font(s_text_layer, s_font);
}