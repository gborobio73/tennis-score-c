/**
 * Example implementation of the radio button list UI pattern.
 */

#include "match_window.h"
#include "dialog_choice_window.h"
#include "../match/MatchConfiguration.h"
#include "../match/MatchScore.h"
#include "../match/MatchScoreLayer.h"
#include "../match/MatchScore.h"
#include "../match/Score.h"
#include "../match/TimeLayer.h"
#include "../match/ScoreTextLayer.h"


static Window *s_match_window;

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  time_layer_update_time();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_window select_click_handler *** SELECT");
  match_schore_cancel_last_point();
  Score* score = match_schore_get_current_score(); 
  match_score_layer_draw_score(score);
  score_text_layer_update_text(score);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_window up_click_handler *** UP");
  match_schore_oponent_point();
  Score* score = match_schore_get_current_score(); 
  match_score_layer_draw_score(score);
  score_text_layer_update_text(score);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_window down_click_handler *** DOWN");
  match_schore_your_point();
  Score* score = match_schore_get_current_score(); 
  match_score_layer_draw_score(score);
  score_text_layer_update_text(score);
}

void choice_window_callback(int option_choosed){
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_window my_callback *** callback done: option choosed %d", option_choosed);
  if (option_choosed == 0)
  {
    window_stack_pop(true);
  }
}

static void back_click_handler(ClickRecognizerRef recognizer, void *context) {  
  dialog_choice_window_push((ChoiceDialogWindowCallbacks) {.callback = choice_window_callback} );
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  
  match_score_layer_init(window_layer);

  match_schore_init(match_config_get_who_serves(), match_config_get_best_of_sets());
  Score* score = match_schore_get_current_score();

  match_score_layer_draw_score(score);

  time_layer_init(window_layer);
  score_text_layer_init(window_layer);

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void window_unload(Window *window) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_window window_unload *** unload match window"); 

    window_destroy(window);
    window = NULL;
    s_match_window = NULL;

    match_score_layer_destroy();
    time_layer_destroy();
    score_text_layer_destroy();

    match_schore_end_match();

    tick_timer_service_unsubscribe();
}

void match_window_push() {
    if(!s_match_window) {    
      s_match_window = window_create();
      window_set_background_color(s_match_window, PBL_IF_COLOR_ELSE(GColorMidnightGreen, GColorBlack));
      window_set_click_config_provider(s_match_window, click_config_provider);
      window_set_window_handlers(s_match_window, (WindowHandlers) {
          .load = window_load,
          .unload = window_unload,
      });
    }
    window_stack_push(s_match_window, true);
    
  // window = window_create();
  // window_set_click_config_provider(window, click_config_provider);
  // window_set_window_handlers(window, (WindowHandlers) {
  //   .load = window_load,
  //   .unload = window_unload,
  // });
  // const bool animated = true;
  // window_stack_push(window, animated);
}
