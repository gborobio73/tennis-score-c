#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Const.h"
#include "Score.h"
#include <pebble.h>

void new_set(Score* new_score, int who_won){
	int who_lost = !who_won;

	new_score->points[opp] =love;
    new_score->points[you] =love;
	new_score->tie_break_points[opp] =0;
    new_score->tie_break_points[you] =0;
    new_score->is_tie_break = false;    
	new_score->games[opp] =0;
    new_score->games[you] =0;
    new_score->sets[who_won] ++;
    if (new_score->sets[who_won] + new_score->sets[who_lost] == new_score->best_of_sets)
    {
    	new_score->match_is_over = true;
    }
}

void new_game (Score* new_score, int who_won){
	int who_lost = !who_won;

	new_score->points[opp] =love;
    new_score->points[you] =love;
	new_score->tie_break_points[opp] =0;
    new_score->tie_break_points[you] =0;
    new_score->is_tie_break = false;
    new_score->who_serves = !(new_score->who_serves);

    if(new_score->games[who_won]  ==6)  {
    	//its over? always?
		//printf("game over. start new set\n" );
    	new_set(new_score, who_won);
    }else if(new_score->games[who_won]  == 5){
    	if(new_score->games[who_lost] ==6){
			new_score->games[who_won] ++;  
			new_score->is_tie_break = true;			
			//printf("is tiebreak\n" );

 		}else if(new_score->games[who_lost]  <=4){
        //its over
        	//printf("game over. who lost had 4 or less games. start new set\n" );
        	new_set(new_score, who_won);
      	}else{
        	new_score->games[who_won] ++;
      	}
    }else{
      	new_score->games[who_won] ++;
    }
}

Score* calculate_new_score(Score* current_score, int who_won){
	
	Score *new_score = malloc(sizeof(Score));
    //printf("New score with address %p\n", (void*)new_score);
    // if (new_score == NULL)
    // {
    // 	APP_LOG(APP_LOG_LEVEL_DEBUG, "*** calculate_new_score *** New score allocated with NULL address");
    // }
    // APP_LOG(APP_LOG_LEVEL_DEBUG, "*** calculate_new_score *** New score allocated with address: %p\n", (void*)new_score);
    copy_score_helper(new_score, current_score);
    
	//work on new_score
    int who_lost = !who_won;
    // printf("who_won %d.\n", who_won);
    // printf("who_lost %d.\n", who_lost);
    if(new_score->is_tie_break){
    	if( new_score->tie_break_points[who_won]<= 5){
			// printf("Continue, who_won had less or equal than 5 %d\n", new_score->tie_break_points[who_won]);
			new_score->tie_break_points[who_won]++;			
			// printf("now has%d\n", new_score->tie_break_points[who_won]);	
		}else{
			if(new_score->tie_break_points[who_won] + 1 - new_score->tie_break_points[who_lost] >=2){
				//printf("End of tie break; new game. who_won had %d, who_lost had %d \n", new_score->tie_break_points[who_won], new_score->tie_break_points[who_lost]);
				new_game(new_score, who_won);				
			}else{
				//printf("Continue, who_won had %d\n", new_score->tie_break_points[who_won]);
				new_score->tie_break_points[who_won]++;				
			}
		}
    }else{
    	//who whon had AD
		if(strcmp(new_score->points[who_won], ad) == 0){
			//end of the game - opp won
			// printf("end of the game - whoWon had Ad.\n");
			new_game(new_score, who_won);
		//who won had 40	
		}else if(strcmp(new_score->points[who_won], forty)==0 ){
			//they were 40 all
			if(strcmp(new_score->points[who_lost], forty)==0){
				// printf("Ad to who whon\n");
				new_score->points[who_won] =ad;

			//who lost had AD
			}else if(strcmp(new_score->points[who_lost], ad) ==0){
				// printf("40 all\n");
				new_score->points[who_won] = forty;
				new_score->points[who_lost] = forty;        
			//who lost had less than 40
			}else{
			  //end of the game        
			  // printf("end of the game - who lost had 30 or less\n");       
			  new_game(new_score, who_won);
			}      
		}else if(strcmp(new_score->points[who_won], thirty)==0){
			new_score->points[who_won] =forty;
		}else if(strcmp(new_score->points[who_won], fifteen)==0){
			new_score->points[who_won]=thirty;
		}else {
			new_score->points[who_won] =fifteen;
		}
    }  

    // APP_LOG(APP_LOG_LEVEL_DEBUG, "*** calculate_new_score *** returning the new score address: %p\n", (void*)new_score);
    return new_score;
}

