#include "dialog_choice_window.h"
#include "../common/texts.h"
#include "../common/const.h"

#if defined(PBL_PLATFORM_APLITE)
  #define BACKGROUD_COLOR GColorMidnightGreen;
#else
  #define BACKGROUD_COLOR GColorMidnightGreen;
#endif

static Window *s_dialog_window;
static TextLayer *s_label_layer;
static BitmapLayer *s_icon_layer;
static ActionBarLayer *s_action_bar_layer;

static GBitmap *s_icon_bitmap, *s_tick_bitmap, *s_cross_bitmap;
static Window *s_match_window;

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    window_stack_pop(true);
    callback.selected_user_option_callback(OK);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    window_stack_pop(true);
    callback.selected_user_option_callback(CANCEL);
}

static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    s_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TENNIS_BALL);

    const GEdgeInsets icon_insets = {.top = 7, .right = 28, .bottom = 56, .left = 14};
    s_icon_layer = bitmap_layer_create(grect_inset(bounds, icon_insets));
    bitmap_layer_set_bitmap(s_icon_layer, s_icon_bitmap);
    bitmap_layer_set_compositing_mode(s_icon_layer, GCompOpSet);
    layer_add_child(window_layer, bitmap_layer_get_layer(s_icon_layer));

    const GEdgeInsets label_insets = {.top = 112, .right = ACTION_BAR_WIDTH, .left = ACTION_BAR_WIDTH / 2};
    s_label_layer = text_layer_create(grect_inset(bounds, label_insets));
    text_layer_set_text(s_label_layer, QUESTION_END_MATCH);
    text_layer_set_background_color(s_label_layer, GColorClear);
    text_layer_set_text_alignment(s_label_layer, GTextAlignmentCenter);
    text_layer_set_font(s_label_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_text_color(s_label_layer, GColorWhite);
    layer_add_child(window_layer, text_layer_get_layer(s_label_layer));

    s_tick_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TICK);
    s_cross_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CROSS);

    s_action_bar_layer = action_bar_layer_create();
    action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_UP, s_tick_bitmap);
    action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_DOWN, s_cross_bitmap);
    action_bar_layer_add_to_window(s_action_bar_layer, window);
    action_bar_layer_set_click_config_provider(s_action_bar_layer, click_config_provider);
}

static void window_unload(Window *window) {
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "*** dialog_choice_window window_unload *** unloading window"); 
    text_layer_destroy(s_label_layer);
    action_bar_layer_destroy(s_action_bar_layer);
    bitmap_layer_destroy(s_icon_layer);

    gbitmap_destroy(s_icon_bitmap);
    gbitmap_destroy(s_tick_bitmap);
    gbitmap_destroy(s_cross_bitmap);

    window_destroy(window);
    s_dialog_window = NULL;
}

void dialog_choice_window_push( ChoiceDialogWindowCallbacks cb ) {
    callback = cb; 
    if(!s_dialog_window) 
    {
        s_dialog_window = window_create();
        window_set_background_color(s_dialog_window, PBL_IF_COLOR_ELSE(GColorMidnightGreen, GColorDarkGray));
        window_set_window_handlers(s_dialog_window, (WindowHandlers) {
            .load = window_load,
            .unload = window_unload,
        });
    }
    window_stack_push(s_dialog_window, true);
}
