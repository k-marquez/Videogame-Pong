/*
    ISPPJ1 2023
    Practice: IA Pong

    Author: Kevin Márquez
    marquezberriosk@gmail.com

    This file contains the definition of the functions to watch the pong game and decide whether to move, decide the direction of movement, move the paddle, and an wrapper to call this functions.
*/

#include "settings.h"
#include "bot.h"
    
void observe_game(struct Bot* bot1, struct Ball ball)
{
    if (bot1->game_difficulty == DUMMY) //Difficult DUMMY
    {
        if ((ball.x <= TABLE_WIDTH / 3) && (ball.vx < 0))
        {
            bot1->move = 1;
        }
        else
        {
            bot1->move = 0;
        }
    } 
    else if (bot1->game_difficulty == REGULAR) //Difficult REGULAR
    {
        if (ball.x <= (TABLE_WIDTH / 2))
        {
            bot1->move = 1;
        }
        else
        {
            bot1->move = 0;
        }
    }
    else //Difficult PRO
    {
         if (ball.x <= (TABLE_WIDTH / 1.5))
        {
            bot1->move = 1;
        }
        else
        {
            bot1->move = 0;
        }
    }
}

void decide_move(struct Bot* bot1, struct Paddle player1, struct Ball ball)
{
    if (player1.y < ball.y)
    {
        bot1->direction_move = DOWN;
    }
    else if(player1.y > ball.y)
    {
        bot1->direction_move = UP;
    }
    else
    {
        bot1->direction_move = KEEP;
    }
}

void excute_move(struct Bot bot1, struct Paddle* player1)
{
    if (bot1.move == 1)
    {
        switch (bot1.direction_move)
        {
            case UP:
                player1->vy = -PADDLE_SPEED;
                break;
            case DOWN:
                player1->vy = PADDLE_SPEED;
                break;
            case KEEP:
                break;
        }
    }
    else
    {
        player1->vy = 0;
    }
}

void play_bot(struct Bot* bot1, struct Paddle* player1, struct Ball ball)
{
    observe_game(bot1, ball);
    decide_move(bot1, *player1, ball);
    excute_move(*bot1, player1);
};
