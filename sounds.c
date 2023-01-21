/*
    ISPPJ1 2023
    Study Case: Pong

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    Author: Kevin Márquez
    marquezberriosk@gmail.com

    Author: Lewis Ochoa
    lewis8a@gmail.com

    This file contains the definition of functions to create sounds and destroy them.
*/

#include <assert.h>

#include "sounds.h"

void create_sounds(struct Sounds* sounds)
{
    sounds->paddle_hit = al_load_sample("sounds/paddle_hit.wav");
    sounds->wall_hit = al_load_sample("sounds/wall_hit.wav");
    sounds->score = al_load_sample("sounds/score.wav");
    sounds->intro = al_load_sample("sounds/intro.wav");
    sounds->game_over = al_load_sample("sounds/game_over.wav");
    sounds->player1_win = al_load_sample("sounds/player1_win.wav");
    sounds->player2_win = al_load_sample("sounds/player2_win.wav");
    sounds->you_win = al_load_sample("sounds/you_win.wav");
    sounds->music = al_load_sample("sounds/music.wav");
    al_reserve_samples(9);

    assert(sounds->paddle_hit != NULL);
    assert(sounds->wall_hit != NULL);
    assert(sounds->score != NULL);
    assert(sounds->intro != NULL);
    assert(sounds->game_over != NULL);
    assert(sounds->player1_win != NULL);
    assert(sounds->player2_win != NULL);
    assert(sounds->you_win != NULL);
    assert(sounds->music != NULL);
}

void destroy_sounds(struct Sounds* sounds)
{
    al_destroy_sample(sounds->paddle_hit);
    al_destroy_sample(sounds->wall_hit);
    al_destroy_sample(sounds->score);
    al_destroy_sample(sounds->intro);
    al_destroy_sample(sounds->game_over);
    al_destroy_sample(sounds->player1_win);
    al_destroy_sample(sounds->player2_win);
    al_destroy_sample(sounds->you_win);
    al_destroy_sample(sounds->music);
}