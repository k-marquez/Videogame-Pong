#include "settings.h"

void configure_pong(struct Custom_Settings * settings,
                    int ww,
                    int wh,
                    int ps,
                    int mp)
{
    settings->window_width = ww;
    settings->window_height = wh;
    settings->paddle_speed = ps;
    settings->max_points = mp;
}

void set_default_config(struct Custom_Settings * settings)
{
    settings->window_width = WINDOW_WIDTH;
    settings->window_height = WINDOW_HEIGHT;
    settings->paddle_speed = PADDLE_SPEED;
    settings->max_points = MAX_POINTS;
}
