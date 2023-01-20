/*
    ISPPJ1 2023
    Practice: AI Pong

    Author: Kevin Márquez
    marquezberriosk@gmail.com

    Author: Lewis Ochoa
    lewis8a@gmail.com

    This file contains the definition of the functions to watch the pong game and decide whether to move, decide the direction of movement, move the paddle, and an wrapper to call this functions.
*/

#include "settings.h"
#include "bot.h"
    
void observe_game(struct Bot* bot, struct Ball ball)
{
    if (bot->game_difficulty == DUMMY) //Difficult DUMMY
    {
        if ((ball.x <= TABLE_WIDTH / 3) && (ball.vx < 0) && (bot->side == 1))
        {
            bot->move = 1;
        }
        else if (ball.x >= (TABLE_WIDTH - TABLE_WIDTH / 3) && (ball.vx > 0) &&
                 (bot->side == -1))
        {
            bot->move = 1;
        }
        else
        {
            bot->move = 0;
        }
    } 
    else if (bot->game_difficulty == REGULAR) //Difficult REGULAR
    {
        if ((ball.x <= TABLE_WIDTH / 2) && (ball.vx < 0) && (bot->side == 1))
        {
            bot->move = 1;
        }
        else if (ball.x >= (TABLE_WIDTH - TABLE_WIDTH / 2) && (ball.vx > 0) &&
                 (bot->side == -1))
        {
            bot->move = 1;
        }
        else
        {
            bot->move = 0;
        }
    }
    else //Difficult PRO
    {
        if ((ball.x <= TABLE_WIDTH / 1.5) && (ball.vx < 0) && (bot->side == 1))
        {
            bot->move = 1;
        }
        else if (ball.x >= (TABLE_WIDTH - TABLE_WIDTH / 1.5) &&
                 (ball.vx > 0) && (bot->side == -1))
        {
            bot->move = 1;
        }
        else
        {
            bot->move = 0;
        }
    }
}

void decide_move(struct Bot* bot, struct Paddle player, struct Ball ball)
{
    if (player.y < ball.y)
    {
        bot->direction_move = DOWN;
    }
    else if(player.y > ball.y)
    {
        bot->direction_move = UP;
    }
    else
    {
        bot->direction_move = KEEP;
    }
}

void excute_move(struct Bot bot, struct Paddle* player)
{
    if (bot.move == 1)
    {
        switch (bot.direction_move)
        {
            case UP:
                player->vy = -PADDLE_SPEED;
                break;
            case DOWN:
                player->vy = PADDLE_SPEED;
                break;
            case KEEP:
                break;
        }
    }
    else
    {
        player->vy = 0;
    }
}

void play_bot(struct Bot* bot, struct Paddle* player, struct Ball ball)
{
    observe_game(bot, ball);
    decide_move(bot, *player, ball);
    excute_move(*bot, player);
};