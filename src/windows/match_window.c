#include "match_window.h"
#include "dialog_choice_window.h"
#include "../match/match_configuration.h"
#include "../match/match_score.h"
#include "../match/match_score_layer.h"
#include "../match/match_score.h"
#include "../match/score.h"
#include "../match/time_layer.h"
#include "../match/score_text_layer.h"
#include "../match/const.h"

static Window *s_match_window;

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    time_layer_update_time();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    match_schore_cancel_last_point();
    Score* score = match_schore_get_current_score(); 
    match_score_layer_draw_score(score);
    score_text_layer_update_text(score);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    match_schore_oponent_point();
    Score* score = match_schore_get_current_score(); 
    match_score_layer_draw_score(score);
    score_text_layer_update_text(score);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    match_schore_your_point();
    Score* score = match_schore_get_current_score(); 
    match_score_layer_draw_score(score);
    score_text_layer_update_text(score);
}

void selected_user_option(int option_choosed){
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_window selected_user_option *** callback done: option choosed %d", option_choosed);
    if (option_choosed == OK)
    {
      window_stack_pop(true);
    }
}

static void back_click_handler(ClickRecognizerRef recognizer, void *context) {  
    if (match_score_is_match_over())
    {
        window_stack_pop(true);
    }else
    {
        dialog_choice_window_push((ChoiceDialogWindowCallbacks) {.selected_user_option_callback = selected_user_option} );
    } 
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
}
