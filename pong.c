/*
    ISPPJ1 2023
    Study Case: Pong

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the functions to init a pong game,
    update it, and render it.
*/

#include <stdio.h>

#include <allegro5/allegro_primitives.h>

#include "fonts.h"
#include "pong.h"

void init_pong(struct Pong* pong, struct Sounds* sounds, ALLEGRO_DISPLAY* display)
{
    init_paddle(&pong->player1, PADDLE_X_OFFSET, PADDLE_Y_OFFSET, PADDLE_WIDTH, PADDLE_HEIGHT);
    init_paddle(&pong->player2, TABLE_WIDTH - PADDLE_WIDTH - PADDLE_X_OFFSET, TABLE_HEIGHT - PADDLE_HEIGHT - PADDLE_Y_OFFSET, PADDLE_WIDTH, PADDLE_HEIGHT);
    init_ball(&pong->ball, TABLE_WIDTH / 2 - BALL_SIZE / 2, TABLE_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE);
    pong->state = OPEN_GAME;
    pong->game_mode = AI_VS_AI; //Could be setting by user
    pong->sound_mode = ON; //Could be setting by user
    
    pong->player1_score = 0;
    pong->player2_score = 0;
    
    pong->serving_player = 0;
    pong->winning_player = 0;
    
    pong->bot1.game_difficulty = PRO; //Difficulty of game, could be setting
    pong->bot1.direction_move = KEEP;
    pong->bot1.move = -1;
    pong->bot1.side = 1;
    
    pong->bot2.game_difficulty = PRO; //Difficulty of game, could be setting
    pong->bot2.direction_move = KEEP;
    pong->bot2.move = -1;
    pong->bot2.side = -1;
    
    pong->window = display;
    pong->sounds = sounds;
    set_default_config(&pong->settings);
    
    srand(time(NULL));
}

void handle_input_pong(struct Pong* pong, ALLEGRO_KEYBOARD_STATE* state)
{
    if (pong->state == OPEN_GAME)
    {
        if (al_key_down(state, ALLEGRO_KEY_1))
            pong->state = SELECT_MOD;
        else if (al_key_down(state, ALLEGRO_KEY_2))
            pong->state = SETTINGS;
    }
    else if (pong->state == SETTINGS)
    {
        if (al_key_down(state, ALLEGRO_KEY_1))
        {
            pong->state = SET_SCREAM_SIZE;
        }
        else if (al_key_down(state, ALLEGRO_KEY_2))
        {
            pong->state = SET_SOUNDS;
        }
        else if (al_key_down(state, ALLEGRO_KEY_3))
        {
            pong->state = SET_PADDLE_SPEED;
        }
        else if (al_key_down(state, ALLEGRO_KEY_4))
        {
            pong->state = SET_MAX_POINTS;
        }
        else if (al_key_down(state, ALLEGRO_KEY_5))
        {
            pong->state = OPEN_GAME;
        }
    }
    else if (pong->state == SET_SCREAM_SIZE)
    {
        if (al_key_down(state, ALLEGRO_KEY_1))
        {
            pong->settings.window_width = 1024;
            pong->settings.window_height = 600;
            al_resize_display(pong->window, pong->settings.window_width, pong->settings.window_height);
            pong->state = OPEN_GAME;
        }
        else if (al_key_down(state, ALLEGRO_KEY_2))
        {
            pong->settings.window_width = 1024;
            pong->settings.window_height = 576;
            al_resize_display(pong->window, pong->settings.window_width, pong->settings.window_height);
            pong->state = OPEN_GAME;
        }
        else if (al_key_down(state, ALLEGRO_KEY_3))
        {
            pong->settings.window_width = 800;
            pong->settings.window_height = 600;
            al_resize_display(pong->window, pong->settings.window_width, pong->settings.window_height);
            pong->state = OPEN_GAME;
        }
        else if (al_key_down(state, ALLEGRO_KEY_4))
        {
            pong->settings.window_width = 640;
            pong->settings.window_height = 512;
            al_resize_display(pong->window, pong->settings.window_width, pong->settings.window_height);
            pong->state = OPEN_GAME;
        }
        else if (al_key_down(state, ALLEGRO_KEY_5))
        {
            pong->settings.window_width = 640;
            pong->settings.window_height = 480;
            al_resize_display(pong->window, pong->settings.window_width, pong->settings.window_height);
            pong->state = OPEN_GAME;
        }
        else if (al_key_down(state, ALLEGRO_KEY_4))
        {
            pong->state = SETTINGS;
        }
    }
    else if (pong->state == SET_SOUNDS)
    {
        if (al_key_down(state, ALLEGRO_KEY_1))
        {
            pong->sound_mode = ON;
            pong->state = OPEN_GAME;
        }
        else if (al_key_down(state, ALLEGRO_KEY_2))
        {
            pong->sound_mode = OFF;
            pong->state = OPEN_GAME;
        }

    }
    else if (pong->state == SELECT_MOD)
    {
        if (al_key_down(state, ALLEGRO_KEY_1))
        {
            pong->game_mode = PLAYER_VS_PLAYER;
            pong->state = START;
        }
        else if (al_key_down(state, ALLEGRO_KEY_2))
        {
            pong->game_mode = AI_VS_PLAYER;
            pong->state = SELECT_AI;
        }
        else if (al_key_down(state, ALLEGRO_KEY_3))
        {
            pong->game_mode = AI_VS_AI;
            pong->state = SELECT_AI;
        }
        else if (al_key_down(state, ALLEGRO_KEY_4))
        {
            pong->state = OPEN_GAME;
        }
    }
    else if (pong->state == SELECT_AI)
    {
        if (al_key_down(state, ALLEGRO_KEY_1))
        {
            pong->bot1.game_difficulty = DUMMY;
            if(pong->game_mode == AI_VS_AI)
                pong->bot2.game_difficulty = DUMMY;
            pong->state = START;
        }
        else if (al_key_down(state, ALLEGRO_KEY_2))
        {
            pong->bot1.game_difficulty = REGULAR;
            if(pong->game_mode == AI_VS_AI)
                pong->bot2.game_difficulty = REGULAR;
            pong->state = START;
        }
        else if (al_key_down(state, ALLEGRO_KEY_3))
        {
            pong->bot1.game_difficulty = PRO;
            if(pong->game_mode == AI_VS_AI)
                pong->bot2.game_difficulty = PRO;
            pong->state = START;
        }

    }
    else if (pong->state == START)
    {
        if (al_key_down(state, ALLEGRO_KEY_ENTER))
        {
            pong->state = SERVE;
            pong->serving_player = rand() % 2 + 1;
        }
    }
    else if (pong->state == SERVE)
    {
        if (al_key_down(state, ALLEGRO_KEY_ENTER))
        {
            pong->state = PLAY;

            pong->ball.vx = rand() % 60 + 140;

            if (pong->serving_player == 2)
            {
                pong->ball.vx *= -1;
            }

            pong->ball.vy = rand() % 100 - 50;
        }
    }
    else if (pong->state == PLAY)
    {
        if (pong->game_mode == PLAYER_VS_PLAYER)
        {        
            if (al_key_down(state, ALLEGRO_KEY_S))
            {
                pong->player1.vy = PADDLE_SPEED;
            }
            else if (al_key_down(state, ALLEGRO_KEY_W))
            {
                pong->player1.vy = -PADDLE_SPEED;
            }
            else
            {
                pong->player1.vy = 0;
            }
        }

        if (pong->game_mode != AI_VS_AI)
        {
            if (al_key_down(state, ALLEGRO_KEY_DOWN))
            {
                pong->player2.vy = PADDLE_SPEED;
            }
            else if (al_key_down(state, ALLEGRO_KEY_UP))
            {
                pong->player2.vy = -PADDLE_SPEED;
            }
            else
            {
                pong->player2.vy = 0;
            }
        }
    }
    else
    {
        if (al_key_down(state, ALLEGRO_KEY_ENTER))
        {
            pong->state = SELECT_MOD;
            init_ball(&pong->ball, TABLE_WIDTH / 2 - BALL_SIZE / 2, TABLE_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE);

            pong->player1_score = 0;
            pong->player2_score = 0;

            if (pong->winning_player == 1)
            {
                pong->serving_player = 2;
            }
            else
            {
                pong->serving_player = 1;
            }
        }
    }
}

void update_pong(struct Pong* pong, double dt)
{
    if (pong->state == PLAY)
    {
        update_paddle(&pong->player1, dt);
        update_paddle(&pong->player2, dt);
        update_ball(&pong->ball, dt);

        struct Hitbox ball_hitbox;
        build_ball_hitbox(pong->ball, &ball_hitbox);

        struct Hitbox player1_hitbox;
        build_paddle_hitbox(pong->player1, &player1_hitbox);

        struct Hitbox player2_hitbox;
        build_paddle_hitbox(pong->player2, &player2_hitbox);

        if (ball_hitbox.x1 > TABLE_WIDTH)
        {
            if(pong->sound_mode == ON)
                al_play_sample(pong->sounds->score, /* gain */ 1.0, /* center */ 1.0, /* speed */ 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            ++pong->player1_score;
            pong->serving_player = 2;

            if (pong->player1_score == MAX_POINTS)
            {
                pong->winning_player = 1;
                pong->state = DONE;
            }
            else
            {
                pong->state = SERVE;
                init_ball(&pong->ball, TABLE_WIDTH / 2 - BALL_SIZE / 2, TABLE_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE);
            }
        }
        else if (ball_hitbox.x2 < 0)
        {
            if(pong->sound_mode == ON)
                al_play_sample(pong->sounds->score, /* gain */ 1.0, /* center */ -1.0, /* speed */ 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            ++pong->player2_score;
            pong->serving_player = 1;

            if (pong->player2_score == MAX_POINTS)
            {
                pong->winning_player = 2;
                pong->state = DONE;
            }
            else
            {
                pong->state = SERVE;
                init_ball(&pong->ball, TABLE_WIDTH / 2 - BALL_SIZE / 2, TABLE_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE);
            }
        }

        if (ball_hitbox.y1 <= 0)
        {

            if(pong->sound_mode == ON)
                al_play_sample(pong->sounds->wall_hit, /* gain */ 1.0, /* center */ 0.0, /* speed */ 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            pong->ball.y = 0;
            pong->ball.vy *= -1;
        }
        else if (ball_hitbox.y2 >= TABLE_HEIGHT)
        {
            if(pong->sound_mode == ON)
                al_play_sample(pong->sounds->wall_hit, /* gain */ 1.0, /* center */ 0.0, /* speed */ 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            pong->ball.y = TABLE_HEIGHT - pong->ball.height;
            pong->ball.vy *= -1;
        }
        
        if (collides(ball_hitbox, player1_hitbox))
        {
            if(pong->sound_mode == ON)
                al_play_sample(pong->sounds->paddle_hit, /* gain */ 1.0, /* center */ -1.0, /* speed */ 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            pong->ball.x = player1_hitbox.x2;
            pong->ball.vx *= -1.03;

            if (pong->ball.vy < 0)
            {
                pong->ball.vy = -(rand() % 140 + 10);
            }
            else
            {
                pong->ball.vy = rand() % 140 + 10;
            }
        }
        else if (collides(ball_hitbox, player2_hitbox))
        {
            if(pong->sound_mode == ON)
                al_play_sample(pong->sounds->paddle_hit, /* gain */ 1.0, /* center */ 1.0, /* speed */ 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            pong->ball.x = player2_hitbox.x1 - pong->ball.width;
            pong->ball.vx *= -1.03;

            if (pong->ball.vy < 0)
            {
                pong->ball.vy = -(rand() % 140 + 10);
            }
            else
            {
                pong->ball.vy = rand() % 140 + 10;
            }
        }
    }
}

void render_pong(struct Pong pong, struct Fonts fonts)
{
    if (pong.state != OPEN_GAME && pong.state != SETTINGS && pong.state != SELECT_MOD && pong.state != SELECT_AI && pong.state != SET_MAX_POINTS && pong.state != SET_PADDLE_SPEED && pong.state != SET_SCREAM_SIZE && pong.state != SET_SOUNDS )
    {
        char score[3];
        sprintf(score, "%d", pong.player1_score);
        al_draw_text(fonts.score_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2 - 50, TABLE_HEIGHT / 6, ALLEGRO_ALIGN_CENTER, score);
        sprintf(score, "%d", pong.player2_score);
        al_draw_text(fonts.score_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2 + 50, TABLE_HEIGHT / 6, ALLEGRO_ALIGN_CENTER, score);
        al_draw_filled_rectangle(
        TABLE_WIDTH / 2 - MID_LINE_WIDTH / 2, 0,
        TABLE_WIDTH / 2 + MID_LINE_WIDTH / 2, TABLE_HEIGHT,
        al_map_rgb(255, 255, 255)
    );
        render_paddle(pong.player1,0);
        render_paddle(pong.player2,1);
        render_ball(pong.ball);
    }

    if (pong.state == OPEN_GAME)
    {
        al_draw_text(fonts.title_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 8, ALLEGRO_ALIGN_CENTER, "PONG");
        al_draw_text(fonts.large_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "1. Play");
        al_draw_text(fonts.large_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 1.7, ALLEGRO_ALIGN_CENTER, "2. Settings");
        al_draw_text(fonts.credit_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2.8, TABLE_HEIGHT / 1.1, ALLEGRO_ALIGN_CENTER, "Created by: Alejandro Mujica - Kevin Marquez - Lewis Ochoa");
    }
    else if (pong.state == SETTINGS)
    {
        al_draw_text(fonts.title_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 8, ALLEGRO_ALIGN_CENTER, "PONG");
        al_draw_text(fonts.large_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 2.5, ALLEGRO_ALIGN_CENTER, "Settings");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 4, TABLE_HEIGHT / 1.9, ALLEGRO_ALIGN_CENTER, "1. Screen size");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH - TABLE_WIDTH / 4, TABLE_HEIGHT / 1.9, ALLEGRO_ALIGN_CENTER, "3. Paddle speed");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 4, TABLE_HEIGHT / 1.7, ALLEGRO_ALIGN_CENTER, "2. Sounds");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH - TABLE_WIDTH / 4, TABLE_HEIGHT / 1.7, ALLEGRO_ALIGN_CENTER, "4. Max points");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 1.5, ALLEGRO_ALIGN_CENTER, "5. Back");
        al_draw_text(fonts.credit_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2.8, TABLE_HEIGHT / 1.1, ALLEGRO_ALIGN_CENTER, "Created by: Alejandro Mujica - Kevin Marquez - Lewis Ochoa");
    }
    else if(pong.state == SET_SCREAM_SIZE)
    {
        al_draw_text(fonts.title_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 8, ALLEGRO_ALIGN_CENTER, "PONG");
        al_draw_text(fonts.large_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 2.5, ALLEGRO_ALIGN_CENTER, "Screen size");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 4, TABLE_HEIGHT / 1.9, ALLEGRO_ALIGN_CENTER, "1. 1024x600");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH - TABLE_WIDTH / 4, TABLE_HEIGHT / 1.9, ALLEGRO_ALIGN_CENTER, "4. 640x512");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 4, TABLE_HEIGHT / 1.7, ALLEGRO_ALIGN_CENTER, "2. 1024x576");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH - TABLE_WIDTH / 4, TABLE_HEIGHT / 1.7, ALLEGRO_ALIGN_CENTER, "5. 640x480");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 4, TABLE_HEIGHT / 1.5, ALLEGRO_ALIGN_CENTER, "3. 800x600");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH - TABLE_WIDTH / 4, TABLE_HEIGHT / 1.5, ALLEGRO_ALIGN_CENTER, "6. Back menu");
        al_draw_text(fonts.credit_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2.8, TABLE_HEIGHT / 1.1, ALLEGRO_ALIGN_CENTER, "Created by: Alejandro Mujica - Kevin Marquez - Lewis Ochoa");
    }
    else if(pong.state == SET_SOUNDS)
    {
        al_draw_text(fonts.title_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 8, ALLEGRO_ALIGN_CENTER, "PONG");
        al_draw_text(fonts.large_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 2.5, ALLEGRO_ALIGN_CENTER, "Sounds");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 1.7, ALLEGRO_ALIGN_CENTER, "1. Enable sounds");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 1.5, ALLEGRO_ALIGN_CENTER, "2. Disable sounds");
        al_draw_text(fonts.credit_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2.8, TABLE_HEIGHT / 1.1, ALLEGRO_ALIGN_CENTER, "Created by: Alejandro Mujica - Kevin Marquez - Lewis Ochoa");
    }
    else if (pong.state == SELECT_MOD)
    {
        al_draw_text(fonts.title_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 8, ALLEGRO_ALIGN_CENTER, "PONG");
        al_draw_text(fonts.large_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 2.7, ALLEGRO_ALIGN_CENTER, "Select game mode");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 1.9, ALLEGRO_ALIGN_CENTER, "1. Player VS Player");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 1.7, ALLEGRO_ALIGN_CENTER, "2. Player VS AI");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 1.5, ALLEGRO_ALIGN_CENTER, "3. AI VS AI");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 1.3, ALLEGRO_ALIGN_CENTER, "4. Back to menu");
    }
    else if (pong.state == SELECT_AI)
    {
        al_draw_text(fonts.title_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 8, ALLEGRO_ALIGN_CENTER, "PONG");
        al_draw_text(fonts.large_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 2.5, ALLEGRO_ALIGN_CENTER, "Select AI difficulty");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 1.7, ALLEGRO_ALIGN_CENTER, "1. Dummy");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 1.5, ALLEGRO_ALIGN_CENTER, "2. Regular");
        al_draw_text(fonts.menu_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 1.3, ALLEGRO_ALIGN_CENTER, "3. Pro");
    }
    else if (pong.state == START)
    {
        al_draw_text(fonts.large_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Press enter to start");
    }
    else if (pong.state == SERVE)
    {
        al_draw_text(fonts.large_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Press enter to serve");
    }
    else if (pong.state == DONE)
    {
        char winner_message[14];
        sprintf(winner_message, "Player %d won!", pong.winning_player);
        al_draw_text(fonts.large_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 3, ALLEGRO_ALIGN_CENTER, winner_message);
        al_draw_text(fonts.large_font, al_map_rgb(255, 255, 255), TABLE_WIDTH / 2, TABLE_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Press enter to restart");
    }
}
