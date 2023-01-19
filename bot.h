/*
    ISPPJ1 2023
    Practice: IA Pong

    Author: Kevin Márquez
    marquezberriosk@gmail.com
    
    This file contains the definition of a bot to play and the declaration
    of the functions to watch de game, decide where to move, move the paddle,
    and a wrapper to call the others.
*/

#pragma once

#include "paddle.h"
#include "ball.h"

enum MoveDirection
{
    UP,
    DOWN,
    KEEP
};

enum GameDifficulty
{
    DUMMY,
    REGULAR,
    PRO
};


struct Bot
{
    enum GameDifficulty game_difficulty;
    enum MoveDirection direction_move;
    
    short side;
    short move;
};

void observe_game(struct Bot* bot1, struct Ball ball);

void decide_move(struct Bot* bot1, struct Paddle player1, struct Ball ball);

void excute_move(struct Bot bot1, struct Paddle* player1);

void play_bot(struct Bot* bot1, struct Paddle* player1, struct Ball ball);
