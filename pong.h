/*
    ISPPJ1 2023
    Study Case: Pong

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    Author: Kevin Márquez
    marquezberriosk@gmail.com

    Author: Lewis Ochoa
    lewis8a@gmail.com

    This file contains the definition of a pong game and the declaration
    of the functions to init it, update it, and render it.
*/

#pragma once

#include "paddle.h"
#include "ball.h"
#include "sounds.h"
#include "bot.h"
#include "settings.h"

enum PongState
{
    OPEN_GAME,
    SETTINGS,
    SET_SCREAM_SIZE,
    SET_PADDLE_SPEED,
    SET_MAX_POINTS,
    SET_SOUNDS,
    SELECT_MOD,
    SELECT_AI,
    START,
    SERVE,
    PLAY,
    DONE
};

enum GameMode
{
    PLAYER_VS_PLAYER,
    AI_VS_PLAYER,
    AI_VS_AI,
};

enum SoundMode
{
   ON,
   OFF
};

struct Pong
{
    struct Paddle player1;
    struct Paddle player2;
    struct Ball ball;
    struct Bot bot1;
    struct Bot bot2;

    enum PongState state;
    enum GameMode game_mode;
    enum SoundMode sound_mode;
    enum SoundMode music;

    int player1_score;
    int player2_score;
    int serving_player;
    int winning_player;

    struct Sounds* sounds;
    struct Custom_Settings settings;
    
    ALLEGRO_DISPLAY* window;
};


void init_pong(struct Pong* pong, struct Sounds* sounds, ALLEGRO_DISPLAY* display);

void handle_input_pong(struct Pong* pong, ALLEGRO_KEYBOARD_STATE* state);

void update_pong(struct Pong* pong, double dt);

void render_pong(struct Pong pong, struct Fonts fonts);

void player_is_winner(struct Pong* pong, short* player_winner);
