#include <pebble.h>

#include "windows/match_window.h"
#include "windows/dialog_choice_window.h"
#include "match/match_configuration.h"
#include "common/texts.h"

#define NUM_MENU_ITEMS 3

static Window *s_main_window;
static MenuLayer *s_menu_layer;

static int16_t get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
    menu_cell_basic_header_draw(ctx, cell_layer, MENU);
}

static uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return NUM_MENU_ITEMS;
}

static void draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *context) {
    switch(cell_index->row) {
      case 0:
          if (match_config_is_best_of_3_sets())
          {
              menu_cell_basic_draw(ctx, cell_layer, BEST_OF, BEST_OF_3_SETS, NULL);
          }else{
              menu_cell_basic_draw(ctx, cell_layer, BEST_OF, BEST_OF_5_SETS, NULL);
          }        
          break;
      case 1:
          if (match_config_does_opponent_serve())
          {
              menu_cell_basic_draw(ctx, cell_layer, WHO_SERVES, OPP_SERVES, NULL);
          }else{
              menu_cell_basic_draw(ctx, cell_layer, WHO_SERVES, YOU_SERVE, NULL);
          }            
          break;
      case 2:
          menu_cell_basic_draw(ctx, cell_layer, START_MATCH, NULL, NULL);
          break;
      default:
        break;
    }
}

static int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  return PBL_IF_ROUND_ELSE(
    menu_layer_is_index_selected(menu_layer, cell_index) ?
      MENU_CELL_ROUND_FOCUSED_SHORT_CELL_HEIGHT : MENU_CELL_ROUND_UNFOCUSED_TALL_CELL_HEIGHT,
      44);
}

static void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  switch(cell_index->row) {
    case 0:
        if (match_config_is_best_of_3_sets())
        {
            match_config_set_best_of_5_sets();            
        }else{
            match_config_set_best_of_3_sets();
        }  
        layer_mark_dirty(menu_layer_get_layer(menu_layer));
        break;
    case 1:
        if (match_config_does_opponent_serve())
        {
            match_config_set_you_serve();            
        }else{
            match_config_set_opponent_serves();
        }  
        layer_mark_dirty(menu_layer_get_layer(menu_layer));
        break;
    case 2:
      match_window_push();
      break;
    default:
      break;
  }
}

static void window_load(Window *window) {

    #if defined(PBL_PLATFORM_APLITE) 
        APP_LOG(APP_LOG_LEVEL_DEBUG, "APLITE defined");
    #elif defined(PBL_PLATFORM_BASALT) 
        APP_LOG(APP_LOG_LEVEL_DEBUG, "BASALT defined");
    #elif defined(PBL_PLATFORM_CHALK)
        APP_LOG(APP_LOG_LEVEL_DEBUG, "CHALK defined");    
    #elif defined(PBL_PLATFORM_DIORITE)
        APP_LOG(APP_LOG_LEVEL_DEBUG, "DIORITE defined");    
    #else
        
    #endif  

    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    s_menu_layer = menu_layer_create(bounds);
    menu_layer_set_click_config_onto_window(s_menu_layer, window);
  #if defined(PBL_COLOR)
    menu_layer_set_normal_colors(s_menu_layer, GColorMidnightGreen, GColorWhite);
    menu_layer_set_highlight_colors(s_menu_layer, GColorYellow, GColorBlack);
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
