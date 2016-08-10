#include <pebble.h>
#include "Score.h"
#include "Const.h"
#include "ScoreTextLayer.h"

static TextLayer *s_score_text_layer;

static char* resolve_text(char* point){
  if(strcmp(point, love) == 0){
    return "love";
  }
  if(strcmp(point, fifteen) == 0){
    return "fifteen";
  }
  if(strcmp(point, thirty) == 0){
    return "thirty";
  }
  if(strcmp(point, forty) == 0){
    return "forty";
  }
  // if(strcmp(point, ad) == 0){
    return "advantage";
  // }
}


static void draw_text_score_layer(TextLayer *layer){
  // Improve the layout to be more like a watchface
  //GColorClear
  text_layer_set_background_color(layer, GColorClear);
  text_layer_set_text_color(layer, GColorWhite);
  text_layer_set_text(layer, "COURT NO. 1");
  
  static GFont s_font;
  s_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SCORE_FONT_18));
  text_layer_set_font(layer, s_font);

  // text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_LECO_26_BOLD_NUMBERS_AM_PM));
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
}

void score_text_layer_update_text(Score* score) {

    char* c=malloc(50);
    if (score->is_tie_break)
    {
      strcat(c, "tiebreak");
    }
    else if (strcmp(score->points[you], ad)==0)
    {
      strcat(c, "your advantage");
    }
    else if (strcmp(score->points[opp], ad)==0)
    {
      strcat(c, "opp. advantage");
    }
    else if (strcmp(score->points[you], score->points[opp])== 0)
    {
      if (strcmp(score->points[you], forty) == 0)
      {
          strcat(c, "deuce");
      }
      else if(strcmp(score->points[you], love) == 0)
      {
          strcat(c, "COURT NO. 1");
      }
      else
      {
          strcat(c, resolve_text(score->points[you]));
          strcat(c, " all");
      }      
    }
    else{
      char* a = resolve_text(score->points[score->who_serves]);
      char* b = resolve_text(score->points[!score->who_serves]);
      strcat(c, a);
      strcat(c, " ");
      strcat(c, b);
    }
    
    // APP_LOG(APP_LOG_LEVEL_DEBUG, "*** score_text_layer_update_text *** %s", c);
    text_layer_set_text(s_score_text_layer, c);
}

void score_text_layer_init(Layer *window_layer){
    //GRect bounds = layer_get_bounds(window_layer);
    //144, 168
    s_score_text_layer = text_layer_create(
      GRect(5, 5, 136, 30));
    draw_text_score_layer(s_score_text_layer);
    layer_add_child(window_layer, text_layer_get_layer(s_score_text_layer));
}

void score_text_layer_destroy(){
    text_layer_destroy(s_score_text_layer);  
    s_score_text_layer=NULL;  
}
