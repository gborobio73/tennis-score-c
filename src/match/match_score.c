#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "match_score.h"
#include "../common/const.h"
#include "score_calculator.h"
#include "score.h"
#include <pebble.h>

MatchScore match_score;

static int scores_initial_size;
static int scores_max_size;

bool match_score_max_size_reached(){
    // APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_score_max_size_reached  *** current %d, max size %d", 
    //     match_score.current_score_idx, scores_max_size);
    return match_score.current_score_idx == scores_max_size -1;
}

void match_score_resize_if_needed(){  
    if (match_score.current_score_idx == match_score.scores_size - 1)
    {
        if (match_score_max_size_reached())/* reached max size */
        {
            match_score.scores[match_score.current_score_idx].match_is_over = true;
        }
        else
        {   /* resize */
            APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_score_resize_if_needed  *** RESIZE "); 
            match_score.scores_size *= 2;
            match_score.scores = realloc(match_score.scores, sizeof(Score) * match_score.scores_size);     
            APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_score_resize_if_needed  *** RESIZED ");        
        }        
    }  
}

void match_score_set_end_time_if_needed(){
    if (match_score_is_match_over())
    {
        match_score.match_ended = time(NULL);
    }
}

void match_score_init(int who_starts_serving, int best_of_sets, int initial_size, int max_size){
    scores_initial_size = initial_size;
    scores_max_size = max_size;

    match_score.current_score_idx =0;
    match_score.scores_size =scores_initial_size;
    match_score.match_started =time(NULL);

    match_score.scores = malloc(sizeof(Score) * match_score.scores_size);
    match_score.scores[match_score.current_score_idx].is_tie_break = false;
    match_score.scores[match_score.current_score_idx].who_serves = who_starts_serving;
    match_score.scores[match_score.current_score_idx].match_is_over = false;
    match_score.scores[match_score.current_score_idx].sets[opp] = 0;
    match_score.scores[match_score.current_score_idx].sets[you] = 0;
    match_score.scores[match_score.current_score_idx].games[opp] = 0;
    match_score.scores[match_score.current_score_idx].games[you] = 0;
    match_score.scores[match_score.current_score_idx].points[opp]=love;
    match_score.scores[match_score.current_score_idx].points[you]=love;
    match_score.scores[match_score.current_score_idx].tie_break_points[opp]=0;
    match_score.scores[match_score.current_score_idx].tie_break_points[you]=0;
    match_score.scores[match_score.current_score_idx].best_of_sets=best_of_sets;
    match_score.scores[match_score.current_score_idx].time = time(NULL);
}

bool match_score_is_match_over(){
    return match_score.scores[match_score.current_score_idx].match_is_over;
}

void match_score_oponent_point(){  
    match_score_resize_if_needed();
    if (!match_score_is_match_over())
    {             
        score_calculator_calculate_new_from_to(
            &match_score.scores[match_score.current_score_idx], 
            opp, 
            &match_score.scores[match_score.current_score_idx + 1]);    
        match_score.current_score_idx++;

        match_score_set_end_time_if_needed();
    }      
}

void match_score_your_point() {
    match_score_resize_if_needed(); 
    if (!match_score_is_match_over())
    {               
        score_calculator_calculate_new_from_to(
            &match_score.scores[match_score.current_score_idx], 
            you, 
            &match_score.scores[match_score.current_score_idx + 1]);
        match_score.current_score_idx++;

        match_score_set_end_time_if_needed();
    } 
}

Score* match_score_get_current_score(){
    return &match_score.scores[match_score.current_score_idx];
}

void match_score_cancel_last_point(){
    if (match_score.current_score_idx > 0)
    {
        match_score.current_score_idx--;
    }    
}

void match_score_end_match(){
    free(match_score.scores);
    match_score.current_score_idx =0;
    match_score.scores_size =scores_initial_size;
}

MatchScore match_score_get_match_score(){
	return match_score;
}

