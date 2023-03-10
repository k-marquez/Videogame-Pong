/*
    ISPPJ1 2023
    Study Case: Pong

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    Author: Kevin Márquez
    marquezberriosk@gmail.com

    Author: Lewis Ochoa
    lewis8a@gmail.com

    This file contains the definition of some macros with values to set the pong game.
*/

#pragma once

#ifndef MIN
#define MIN(a, b) ((a < b) ? a : b)
#endif

#ifndef MAX
#define MAX(a, b) ((a > b) ? a : b)
#endif

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 500
#define TABLE_WIDTH 432
#define TABLE_HEIGHT 243
#define PADDLE_WIDTH 5
#define PADDLE_HEIGHT 20
#define PADDLE_X_OFFSET 10
#define PADDLE_Y_OFFSET 30
#define PADDLE_SPEED 200
#define BALL_SIZE 4
#define MID_LINE_WIDTH 2
#define FPS 60.0
#define MAX_POINTS 5

struct Custom_Settings
{
    int window_width;
    int window_height;
    int paddle_speed;
    int max_points;
};

void configure_pong(struct Custom_Settings * settings,
                    int ww,
                    int wh,
                    int ps,
                    int mp);
                    
void set_default_config(struct Custom_Settings * settings);
