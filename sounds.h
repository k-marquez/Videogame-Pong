/*
    ISPPJ1 2023
    Study Case: Pong

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    Author: Kevin Márquez
    marquezberriosk@gmail.com

    Author: Lewis Ochoa
    lewis8a@gmail.com

    This file contains the definition of a struct to load sounds and the
    declaratrion of functions to create them and destroy them.
*/

#pragma once

#include <allegro5/allegro_audio.h>

struct Sounds
{
    ALLEGRO_SAMPLE* paddle_hit;
    ALLEGRO_SAMPLE* wall_hit;
    ALLEGRO_SAMPLE* score;
    ALLEGRO_SAMPLE* intro;
    ALLEGRO_SAMPLE* game_over;
    ALLEGRO_SAMPLE* player1_win;
    ALLEGRO_SAMPLE* player2_win;
    ALLEGRO_SAMPLE* you_win;
    ALLEGRO_SAMPLE* music;
};

void create_sounds(struct Sounds* sounds);

void destroy_sounds(struct Sounds* sounds);
