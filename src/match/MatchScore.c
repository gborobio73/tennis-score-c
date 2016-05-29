#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "MatchScore.h"
#include "Const.h"
#include "ScoreCalculator.h"
#include "Score.h"
#include "Time.h"
#include <pebble.h>

MatchScore match_score;

static int current_score_idx;

void init_match_schore(int who_starts_serving, int best_of_sets){
    current_score_idx =0;

    //match_score.scores[current_score_idx] = (Score *)malloc(sizeof(Score));
    match_score.scores = malloc(sizeof(Score) * 500);
    match_score.scores[current_score_idx].is_tie_break = false;
    match_score.scores[current_score_idx].who_serves = who_starts_serving;
    match_score.scores[current_score_idx].match_is_over = false;
    match_score.scores[current_score_idx].sets[opp] = 0;
    match_score.scores[current_score_idx].sets[you] = 0;
    match_score.scores[current_score_idx].games[opp] = 0;
    match_score.scores[current_score_idx].games[you] = 0;
    match_score.scores[current_score_idx].points[opp]=love;
    match_score.scores[current_score_idx].points[you]=love;
    match_score.scores[current_score_idx].tie_break_points[opp]=0;
    match_score.scores[current_score_idx].tie_break_points[you]=0;
    match_score.scores[current_score_idx].best_of_sets=best_of_sets;
}

bool is_match_over(){
    return match_score.scores[current_score_idx].match_is_over;
}

void oponentPoint(){  
    if (!is_match_over())
    {
        Score* new_score = calculate_new_score(&match_score.scores[current_score_idx], opp);    
        current_score_idx++;
        APP_LOG(APP_LOG_LEVEL_DEBUG, "*** oponentPoint *** #scores: %d\n", current_score_idx);
        //match_score.scores[current_score_idx]= new_score;

        copy_score_helper(&match_score.scores[current_score_idx], new_score);
    }      
}

void yourPoint() {
    if (!is_match_over())
    {
        //printf("your point start \n");
        Score* new_score = calculate_new_score(&match_score.scores[current_score_idx], you);
        //printf("your point got new score \n");
        current_score_idx++;
        APP_LOG(APP_LOG_LEVEL_DEBUG, "*** yourPoint *** #scores: %d\n", current_score_idx);
        //match_score.scores[current_score_idx]= new_score;

        copy_score_helper(&match_score.scores[current_score_idx], new_score);
        //printf("your point end \n");
    } 
}

Score* get_current_score(){
    //printf("get_current_score_idx start \n");
    //printf("get_current_score_idx start %d\n", current_score_idx);
    return &match_score.scores[current_score_idx];
}

void cancel_last_point(){
    if (!is_match_over() && current_score_idx > 0)
    {
        //free(match_score.scores[current_score_idx]);
        current_score_idx--;
    }    
}

int amount_of_scores(){
    return current_score_idx;
}

void end_match(){
    //printf("end_match start \n");
    // for (int i = 0; i <= current_score_idx; ++i)
    // {
    //     free(match_score.scores[i]);
    // }
    // current_score_idx =0;

    free(match_score.scores);
    //printf("end_match end \n");
}

