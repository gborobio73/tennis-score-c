#pragma once

#include <pebble.h>

#define DIALOG_CHOICE_WINDOW_MESSAGE "End match?"

typedef void (*Callback)(int);
typedef struct ChoiceDialogWindowCallbacks {
    Callback callback;
} ChoiceDialogWindowCallbacks;

ChoiceDialogWindowCallbacks callback;

void dialog_choice_window_push(ChoiceDialogWindowCallbacks);
