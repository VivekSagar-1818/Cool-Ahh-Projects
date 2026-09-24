#include <iostream>
using namespace std;
#include "raylib.h"

int main(){

    cout << "GET READY TO PLAY PONG!" << endl;

    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Pong Game!");
    SetTargetFPS(60);


    float alpha = 1.0f;
    const float fadeSpeed = 0.5f;
    bool introFinished = false;
    bool fadingIn = false;
    float paddle1X = 15;
    float paddle2X = screenWidth - 35;
    float paddle1Y = screenHeight / 2 - 75;            // Defining
    float paddle2Y = screenHeight / 2 - 75;

    int Player1Score = 0;
    int Player2Score = 0;

    
    int ballRadius = 20;
    struct Ball {
        float x;
        float y;
        float speedX;
        float speedY;
        int radius;
    };

    Ball ball;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speedX = 5;                    //Defining Ball OOP
    ball.speedY = -5;
    ball.radius = 10;
    int Score1 = 0;
    int Score2 = 0;

    while (!WindowShouldClose()) {
        if (!introFinished) {
            if (fadingIn) {
                alpha += fadeSpeed * GetFrameTime();
                if (alpha >= 1.0f) {
                    alpha = 1.0f;                           //Fading Intro
                    introFinished = true;
                }
            } else {
                alpha -= fadeSpeed * GetFrameTime();
                if (alpha <= 0.0f) {
                    alpha = 0.0f;
                    fadingIn = true;
                }
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);

        if (!introFinished) {
            DrawText("PONG GAME!", 450, 350, 50, Fade(WHITE, alpha));
        } else {

            // Updation
            ball.x += ball.speedX;
            ball.y += ball.speedY;

            if ( ball.y + ball.radius >= GetScreenHeight() || ball.y - ball.radius <= 0){
                ball.speedY *= -1;
            }
            if ( ball.x + ball.radius >= GetScreenWidth() || ball.x - ball.radius <= 0){
                ball.speedX *= -1;
            }


            //Collision
            if (CheckCollisionCircleRec( Vector2{ball.x, ball.y} , ball.radius , Rectangle{paddle1X , paddle1Y , 20 , 225})){
                ball.speedX *= -1;
                
            }

            if (CheckCollisionCircleRec( Vector2{ball.x, ball.y} , ball.radius , Rectangle{paddle2X , paddle2Y , 20 , 225})){
                ball.speedX *= -1;
                
            }

            //Score

            if ( ball.x + ball.radius >= GetScreenWidth()){
                Player1Score ++;
            }
            if ( ball.x - ball.radius <= 0){
                Player2Score ++;
            }
            

            //Drawing
            DrawCircle(ball.x, ball.y, ball.radius, WHITE);

            DrawLine( screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
            DrawRectangle(paddle1X, paddle1Y, 20, 225, WHITE);
            DrawRectangle(paddle2X, paddle2Y, 20, 225, WHITE);

            DrawText( TextFormat("%i",Player1Score) , 275 , 100 , 100 , YELLOW);
            DrawText( TextFormat("%i",Player2Score) , 875 , 100 , 100 ,YELLOW);
            

            if (IsKeyDown(KEY_W) && paddle1Y > 0) {
                paddle1Y -= 10;
            }
            if (IsKeyDown(KEY_S) && paddle1Y < screenHeight - 225) {
                paddle1Y += 10;
            }
            if (IsKeyDown(KEY_UP) && paddle2Y > 0) {
                paddle2Y -= 10;
            }
            if (IsKeyDown(KEY_DOWN) && paddle2Y < screenHeight - 225) {
                paddle2Y += 10;
            }
        }

        EndDrawing();
    }

    CloseWindow();
 
    return 0;
}
