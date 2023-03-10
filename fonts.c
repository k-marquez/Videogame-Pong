/*
    ISPPJ1 2023
    Study Case: Pong

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    Author: Kevin Márquez
    marquezberriosk@gmail.com

    Author: Lewis Ochoa
    lewis8a@gmail.com

    This file contains the definition of functions to create fonts and destroy them.
*/

#include "settings.h"
#include "fonts.h"

void create_fonts(struct Fonts* fonts)
{
    fonts->large_font = al_load_ttf_font("fonts/font.ttf", 16, ALLEGRO_TTF_MONOCHROME);
    fonts->score_font = al_load_ttf_font("fonts/font.ttf", 32, ALLEGRO_TTF_MONOCHROME);
    fonts->title_font = al_load_ttf_font("fonts/font.ttf", 64, ALLEGRO_TTF_MONOCHROME);
    fonts->menu_font = al_load_ttf_font("fonts/font.ttf", 14, ALLEGRO_TTF_MONOCHROME);
    fonts->credit_font = al_load_ttf_font("fonts/font.ttf", 8, ALLEGRO_TTF_MONOCHROME);
}

void destroy_fonts(struct Fonts* fonts)
{
    al_destroy_font(fonts->large_font);
    al_destroy_font(fonts->score_font);
}
