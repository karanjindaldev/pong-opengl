#pragma once

#include <iostream>

#include "Ball.hpp"

class GameManager{
public:
    int player1_score = 0;
    int player2_score = 0;

    bool startGame = false;

private:
    void IncrementScore(float X){
        if(X>=1.0f){
            player1_score++;
        }
        else{
            player2_score++;
        }
    }

    void PrintScore(){
        std::cout<<"Player 1 score: "<<player1_score<<'\n';
        std::cout<<"Player 2 score: "<<player2_score<<'\n';
    }

    void GameReset(Ball& ball){
        startGame = false;
        ball.X = 0;
        ball.Y = 0;
        ball.velX = 1.0f;
        ball.velY = 1.0f;
    }

public:
    void CheckState(Ball& ball){
        if(ball.X>(1+ball.width/2) || ball.X<(-1-ball.width/2)){
            IncrementScore(ball.X);
            GameReset(ball);
            PrintScore();
        }
    }
};