#include <pebble.h>
#include "../match/score.h"
#include "../common/const.h"
#include "../common/texts.h"
#include "score_text_layer.h"

static TextLayer *s_score_text_layer;
static char* text;

#if defined(PBL_PLATFORM_CHALK)
    #define SCORE_TEXT_X 20
    #define SCORE_TEXT_Y 22
#else
    #define SCORE_TEXT_X 0
    #define SCORE_TEXT_Y 10
#endif

static char* resolve_text(char* point){
    if(strcmp(point, love) == 0){
      return LOVE_SCORE;
    }
    if(strcmp(point, fifteen) == 0){
      return FIFTEEN_SCORE;
    }
    if(strcmp(point, thirty) == 0){
      return THIRTY_SCORE;
    }
    if(strcmp(point, forty) == 0){
      return FORTY_SCORE;
    }
    return AD_SCORE;
}


static void draw_text_score_layer(TextLayer *layer){
    text_layer_set_background_color(layer, GColorClear);
    text_layer_set_text_color(layer, GColorWhite);
    text_layer_set_text(layer, STATIC_SCORE_TEXT);
    
    static GFont s_font;
    s_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SCORE_FONT_15));
    text_layer_set_font(layer, s_font);

    text_layer_set_text_alignment(layer, GTextAlignmentCenter);
}

void score_text_layer_update_text(Score* score) {
    text[0]='\0';
    if (score->match_is_over)
    {
        #if defined(PBL_PLATFORM_APLITE) 
            strcat(text, MATCHOVER_SCORE);
        #else
            strcat(text, MATCHOVER_SCROLL);
        #endif
    }
    else if (score->is_tie_break){
        strcat(text, TIEBREAK_SCORE);
    }
    else if (strcmp(score->points[you], ad)==0)
    {
        strcat(text, ADVANTAGE_YOU);
    }
    else if (strcmp(score->points[opp], ad)==0)
    {
        strcat(text, ADVANTAGE_OPP);
    }
    else if (strcmp(score->points[you], score->points[opp])== 0)
    {
        if (strcmp(score->points[you], forty) == 0)
        {
            strcat(text, DEUCE_SCORE);
        }
        else if(strcmp(score->points[you], love) == 0)
        {
            strcat(text, STATIC_SCORE_TEXT);
        }
        else
        {
            strcat(text, resolve_text(score->points[you]));
            strcat(text, ALL_SCORE);
        }      
    }
    else
    {
        char* a = resolve_text(score->points[score->who_serves]);
        char* b = resolve_text(score->points[!score->who_serves]);
        strcat(text, a);
        strcat(text, SPACE_SCORE);
        strcat(text, b);      
    }
    
    text_layer_set_text(s_score_text_layer, text);
    layer_mark_dirty(text_layer_get_layer(s_score_text_layer));
}

void score_text_layer_init(Layer *window_layer){
    s_score_text_layer = text_layer_create(GRect(SCORE_TEXT_X, SCORE_TEXT_Y, 136, 27));
    draw_text_score_layer(s_score_text_layer);
    layer_add_child(window_layer, text_layer_get_layer(s_score_text_layer));    
    
    text = malloc(50* sizeof(char));
}

void score_text_layer_destroy(){
    text_layer_destroy(s_score_text_layer);  
    s_score_text_layer=NULL;  
    free(text);
}
