#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "MatchScore.h"
#include "Const.h"
#include "ScoreCalculator.h"
#include "Score.h"
#include "TimeLayer.h"
#include <pebble.h>

MatchScore match_score;

void match_score_resize_if_needed(){
    
    if (match_score.current_score_idx == match_score.scores_size - 1)// !!! resize
    {
        // APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_score_resize_if_needed *** resizing!");
        match_score.scores_size *= 2;
        match_score.scores = realloc(match_score.scores, sizeof(Score) * match_score.scores_size);
        // APP_LOG(APP_LOG_LEVEL_DEBUG, "*** match_score_resize_if_needed *** resized to %d", match_score.scores_size);
    }
}


void match_schore_init(int who_starts_serving, int best_of_sets){
    match_score.current_score_idx =0;
    match_score.scores_size =SCORES_INITIAL_SIZE;

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

void match_schore_oponent_point(){  
    if (!match_score_is_match_over())
    {
        match_score_resize_if_needed();        
        score_calculator_calculate_new_from_to(
            &match_score.scores[match_score.current_score_idx], 
            opp, 
            &match_score.scores[match_score.current_score_idx + 1]);    
        match_score.current_score_idx++;
    }      
}

void match_schore_your_point() {
    if (!match_score_is_match_over())
    {
        match_score_resize_if_needed();        
        score_calculator_calculate_new_from_to(
            &match_score.scores[match_score.current_score_idx], 
            you, 
            &match_score.scores[match_score.current_score_idx + 1]);
        match_score.current_score_idx++;
    } 
}

Score* match_schore_get_current_score(){
    //printf("match_schore_get_current_score_idx start \n");
    //printf("match_schore_get_current_score_idx start %d\n", current_score_idx);
    return &match_score.scores[match_score.current_score_idx];
}

void match_schore_cancel_last_point(){
    if (!match_score_is_match_over() && match_score.current_score_idx > 0)
    {
        //free(match_score.scores[current_score_idx]);
        match_score.current_score_idx--;
    }    
}

int match_schore_amount_of_scores(){
    return match_score.current_score_idx;
}

void match_schore_end_match(){
    //printf("match_schore_end_match start \n");
    // for (int i = 0; i <= current_score_idx; ++i)
    // {
    //     free(match_score.scores[i]);
    // }
    // current_score_idx =0;

    free(match_score.scores);
    match_score.current_score_idx =0;
    match_score.scores_size =SCORES_INITIAL_SIZE;
    //printf("match_schore_end_match end \n");
}

