#pragma once

#include <pebble.h>

typedef void (*Callback)(int);

typedef struct ChoiceDialogWindowCallbacks {
    Callback selected_user_option_callback;
} ChoiceDialogWindowCallbacks;

ChoiceDialogWindowCallbacks callback;

void dialog_choice_window_push(ChoiceDialogWindowCallbacks);
