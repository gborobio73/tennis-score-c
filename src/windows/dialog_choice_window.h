#pragma once

#include <pebble.h>

typedef void (*Callback)(int);

typedef struct ChoiceDialogWindowCallbacks {
    Callback callback;
} ChoiceDialogWindowCallbacks;

ChoiceDialogWindowCallbacks callback;

void dialog_choice_window_push(ChoiceDialogWindowCallbacks);
