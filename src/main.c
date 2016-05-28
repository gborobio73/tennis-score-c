#include <pebble.h>

#include "windows/checkbox_window.h"
// #include "windows/dialog_choice_window.h"
// #include "windows/dialog_message_window.h"
// #include "windows/list_message_window.h"
// #include "windows/radio_button_window.h"
// #include "windows/pin_window.h"
// #include "windows/text_animation_window.h"
// #include "windows/progress_bar_window.h"
// #include "windows/progress_layer_window.h"
// #include "windows/dialog_config_window.h"

#include "windows/number_of_sets_window.h"
#include "windows/who_serves_window.h"
#include "match/MatchConfiguration.h"


//#define NUM_WINDOWS 10
#define NUM_WINDOWS 3

#define BEST_OF_3_SETS "3"
#define BEST_OF_5_SETS "5"

#define OPP_SERVES "Opponent serves"
#define YOU_SERVE "You serve"

static Window *s_main_window;
static MenuLayer *s_menu_layer;

static int16_t get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
    menu_cell_basic_header_draw(ctx, cell_layer, "Menu");
}

static uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return NUM_WINDOWS;
}

static void draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *context) {
    switch(cell_index->row) {
      case 0:
          if (match_config_is_best_of_3_sets())
          {
              menu_cell_basic_draw(ctx, cell_layer, "Best of # sets", BEST_OF_3_SETS, NULL);
          }else{
              menu_cell_basic_draw(ctx, cell_layer, "Best of # sets", BEST_OF_5_SETS, NULL);
          }        
          break;
      case 1:
          if (match_config_does_opponent_serve())
          {
              menu_cell_basic_draw(ctx, cell_layer, "Who serves", OPP_SERVES, NULL);
          }else{
              menu_cell_basic_draw(ctx, cell_layer, "Who serves", YOU_SERVE, NULL);
          }            
          break;
      case 2:
          menu_cell_basic_draw(ctx, cell_layer, "Start match", NULL, NULL);
          break;

      // case 0:
      //   menu_cell_basic_draw(ctx, cell_layer, "Checkbox List", NULL, NULL);
      //   break;
      // case 1:
      //   menu_cell_basic_draw(ctx, cell_layer, "Choice Dialog", NULL, NULL);
      //   break;
      // case 2:
      //   menu_cell_basic_draw(ctx, cell_layer, "Message Dialog", NULL, NULL);
      //   break;
      // case 3:
      //   menu_cell_basic_draw(ctx, cell_layer, "List Message", NULL, NULL);
      //   break;
      // case 4:
      //   menu_cell_basic_draw(ctx, cell_layer, "Radio Button", NULL, NULL);
      //   break;
      // case 5:
      //   menu_cell_basic_draw(ctx, cell_layer, "PIN Entry", NULL, NULL);
      //   break;
      // case 6:
      //   menu_cell_basic_draw(ctx, cell_layer, "Text Animation", NULL, NULL);
      //   break;
      // case 7:
      //   menu_cell_basic_draw(ctx, cell_layer, "Progress Bar", NULL, NULL);
      //   break;
      // case 8:
      //   menu_cell_basic_draw(ctx, cell_layer, "Progress Layer", NULL, NULL);
      //   break;
      // case 9:
      //   menu_cell_basic_draw(ctx, cell_layer, "App Config Prompt", NULL, NULL);
      //   break;
      default:
        break;
    }
}

static int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  return PBL_IF_ROUND_ELSE(
    menu_layer_is_index_selected(menu_layer, cell_index) ?
      MENU_CELL_ROUND_FOCUSED_SHORT_CELL_HEIGHT : MENU_CELL_ROUND_UNFOCUSED_TALL_CELL_HEIGHT,
    CHECKBOX_WINDOW_CELL_HEIGHT);
}

// static void pin_complete_callback(PIN pin, void *context) {
//   APP_LOG(APP_LOG_LEVEL_INFO, "Pin was %d %d %d", pin.digits[0], pin.digits[1], pin.digits[2]);
//   pin_window_pop((PinWindow*)context, true);
// }

static void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  switch(cell_index->row) {
    case 0:
      number_of_sets_window_push();
      break;
    case 1:
      who_serves_window_push();
      break;
    case 2:
      // dialog_message_window_push();
      break;

    // case 0:
    //   checkbox_window_push();
    //   break;
    // case 1:
    //   dialog_choice_window_push();
    //   break;
    // case 2:
    //   dialog_message_window_push();
    //   break;
    // case 3:
    //   list_message_window_push();
    //   break;
    // case 4:
    //   radio_button_window_push();
    //   break;
    // case 5: {
    //     PinWindow *pin_window = pin_window_create((PinWindowCallbacks) {
    //       .pin_complete = pin_complete_callback
    //     });
    //     pin_window_push(pin_window, true);
    //   }
    //   break;
    // case 6:
    //   text_animation_window_push();
    //   break;
    // case 7:
    //   progress_bar_window_push();
    //   break;
    // case 8:
    //   progress_layer_window_push();
    //   break;
    // case 9:
    //   dialog_config_window_push();
    //   break;
    default:
      break;
  }
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_menu_layer = menu_layer_create(bounds);
  menu_layer_set_click_config_onto_window(s_menu_layer, window);
#if defined(PBL_COLOR)
  menu_layer_set_normal_colors(s_menu_layer, GColorBlack, GColorWhite);
  menu_layer_set_highlight_colors(s_menu_layer, GColorBrilliantRose, GColorWhite);
#endif
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks) {
      .get_header_height = PBL_IF_RECT_ELSE(get_header_height_callback, NULL),
      .draw_header = PBL_IF_RECT_ELSE(draw_header_callback, NULL),
      .get_num_rows = get_num_rows_callback,
      .draw_row = draw_row_callback,
      .get_cell_height = get_cell_height_callback,
      .select_click = select_callback,
  });
  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

static void window_unload(Window *window) {
  menu_layer_destroy(s_menu_layer);
}

static void init() {
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}
