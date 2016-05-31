/**
 * Example implementation of the radio button list UI pattern.
 */

#include "match_window.h"
#include "../match/MatchConfiguration.h"
#include "../match/MatchScore.h"
#include "../match/MatchScoreLayer.h"
#include "../match/MatchScore.h"
#include "../match/Score.h"
#include "../match/TimeLayer.h"

static Window *s_main_window;
static MenuLayer *s_menu_layer;

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  time_layer_update_time();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  match_schore_cancel_last_point();
  Score* score = match_schore_get_current_score(); 
  match_score_layer_draw_score(score);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  match_schore_oponent_point();
  Score* score = match_schore_get_current_score(); 
  match_score_layer_draw_score(score);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  match_schore_your_point();
  Score* score = match_schore_get_current_score(); 
  match_score_layer_draw_score(score);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  
  match_score_layer_init(window_layer);

  match_schore_init(match_config_get_who_serves(), match_config_get_best_of_sets());
  Score* score = match_schore_get_current_score();

  match_score_layer_draw_score(score);

  time_layer_init(window_layer);
}

static void window_unload(Window *window) {
    menu_layer_destroy(s_menu_layer);

    window_destroy(window);
    s_main_window = NULL;

    match_score_layer_destroy();
    time_layer_destroy();

    match_schore_end_match();
}

void match_window_push() {
    if(!s_main_window) {      
      s_main_window = window_create();
      window_set_click_config_provider(s_main_window, click_config_provider);
      window_set_window_handlers(s_main_window, (WindowHandlers) {
          .load = window_load,
          .unload = window_unload,
      });
    }
    window_stack_push(s_main_window, true);

    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  // window = window_create();
  // window_set_click_config_provider(window, click_config_provider);
  // window_set_window_handlers(window, (WindowHandlers) {
  //   .load = window_load,
  //   .unload = window_unload,
  // });
  // const bool animated = true;
  // window_stack_push(window, animated);
}
