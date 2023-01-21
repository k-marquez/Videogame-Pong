/*
    ISPPJ1 2023
    Study Case: Pong

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    Author: Kevin Márquez
    marquezberriosk@gmail.com

    Author: Lewis Ochoa
    lewis8a@gmail.com

    This file contains the definition of a struct to load fonts and the
    declaratrion of functions to create them and destroy them.
*/

#pragma once

#include <allegro5/allegro_ttf.h>

struct Fonts
{
    ALLEGRO_FONT* large_font;
    ALLEGRO_FONT* score_font;
    ALLEGRO_FONT* title_font;
    ALLEGRO_FONT* menu_font;
    ALLEGRO_FONT* credit_font;
};

void create_fonts(struct Fonts* fonts);

void destroy_fonts(struct Fonts* fonts);
