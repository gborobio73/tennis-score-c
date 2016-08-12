#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/const.h"
#include "score.h"
#include "match_configuration.h"
#include <pebble.h>

static void new_set(Score* new_score, int who_won){
	new_score->points[opp] =love;
    new_score->points[you] =love;
	new_score->tie_break_points[opp] =0;
    new_score->tie_break_points[you] =0;
    new_score->is_tie_break = false;    
	new_score->games[opp] =0;
    new_score->games[you] =0;
    new_score->sets[who_won] ++;
    
    if ((match_config_is_best_of_3_sets() && new_score->sets[who_won] ==2 )
    	||
    	new_score->sets[who_won] ==3 ) /* best of 5*/
    {
    	new_score->match_is_over = true;
    }
   
}

static void new_game (Score* new_score, int who_won){
	int who_lost = !who_won;

	new_score->points[opp] =love;
    new_score->points[you] =love;
	new_score->tie_break_points[opp] =0;
    new_score->tie_break_points[you] =0;
    new_score->is_tie_break = false;
    new_score->who_serves = !(new_score->who_serves);

    if(new_score->games[who_won] ==6) 
    { 
    	new_set(new_score, who_won); /* it was either tiebreak or 6 to 5, or less */
    }
    else if(new_score->games[who_won]  == 5)
    {
    	if(new_score->games[who_lost] ==6)
    	{
			new_score->games[who_won] ++;  
			new_score->is_tie_break = true;						
 		}
 		else if(new_score->games[who_lost] <=4)
 		{
        	new_set(new_score, who_won); /* end of set: 6 to 4 or less */
      	}
      	else
      	{
        	new_score->games[who_won] ++;
      	}
    }
    else
    {
      	new_score->games[who_won] ++;
    }
}

static bool tiebreak_should_change_serve(Score* new_score, int who_won, int who_lost){
	int total_points =new_score->tie_break_points[who_won] + new_score->tie_break_points[who_lost];
	return total_points % 2; /* total points is odd, serve change */ 
}

static void calculate_tiebreak_new_score(Score* new_score, int who_won, int who_lost){
	if(new_score->tie_break_points[who_won]<= 5)
	{			
		new_score->tie_break_points[who_won]++;						
		if (tiebreak_should_change_serve(new_score, who_won, who_lost)) 
		{ 
			new_score->who_serves = !(new_score->who_serves);
		}
	}
	else
	{
		if(new_score->tie_break_points[who_won] + 1 - new_score->tie_break_points[who_lost] >=2)
		{
			new_game(new_score, who_won); /* tiebreak end*/
		}
		else
		{
			new_score->tie_break_points[who_won]++;		
			if (tiebreak_should_change_serve(new_score, who_won, who_lost)) 
			{ 
			 	new_score->who_serves = !(new_score->who_serves);
			}		
		}
	}
}

void score_calculator_calculate_new_from_to(Score* current_score, int who_won, Score* new_score){
	
	score_copy_to_from(new_score, current_score);
    
	int who_lost = !who_won;
    
    if(new_score->is_tie_break)
    {
    	calculate_tiebreak_new_score(new_score, who_won, who_lost);
    }
    else
    {
   		if(strcmp(new_score->points[who_won], ad) == 0)
   		{
			new_game(new_score, who_won); /* opponent won game, had AD */			
		}
		else if(strcmp(new_score->points[who_won], forty)==0 )
		{			
			if(strcmp(new_score->points[who_lost], forty)==0)
			{				
				new_score->points[who_won] =ad; /* they were deuce */
			}
			else if(strcmp(new_score->points[who_lost], ad) ==0)
			{
				new_score->points[who_won] = forty; /* who lost had AD */
				new_score->points[who_lost] = forty;        
			}
			else
			{
			  new_game(new_score, who_won); /* who lost had less than 40 */
			}      
		}
		else if(strcmp(new_score->points[who_won], thirty)==0)
		{
			new_score->points[who_won] =forty;
		}
		else if(strcmp(new_score->points[who_won], fifteen)==0)
		{
			new_score->points[who_won]=thirty;
		}
		else 
		{
			new_score->points[who_won] =fifteen;
		}
    }  
}