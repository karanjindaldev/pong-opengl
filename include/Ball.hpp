#pragma once

#include <algorithm>

#include <iostream>

class Ball{
private:
    float leftX = 0.0f;
    float rightX = 0.0f;
    float downY = 0.0f;
    float upY = 0.0f;

public:
    float X = 0.0f;
    float Y = 0.0f;
    float velX = 1.0f;
    float velY = 1.0f;

    float width = 0.027f;
    float height = 0.048f;

    void Move(const float deltaTime){
        this->X+=this->velX*deltaTime;
        this->Y+=this->velY*deltaTime;

        this->Y = std::min(std::max(-0.976f, this->Y), 0.976f);

        leftX = X-width/2;
        rightX = X+width/2;
        downY = Y-height/2;
        upY = Y+height/2;
    }

    void DetectWallCollision(){
        if(this->Y>=(1-height/2)|| this->Y<=-(1-height/2)){
            this->velY=-this->velY;
        }
    }

    void AABBCollision(float playerX, float player_upY, float player_downY, bool player1){
        if(player1){
            if(X-width/2 > playerX){
                return;
            }
        }
        else{
            if(X+width/2 < playerX){
                return;
            }
        }

        if(Y+height/2 < player_downY || Y-height/2 > player_upY){
                return;
        }

        velX = -velX;
    }
};