#include "raylib.h"

const int screenWidth = 600;
const int ScreenHeight = 400;

void DrawPongGame();
void UpdatePongGame();
void BallFunction();
void PlayerFunction();

float velocity = 7;

Vector2 ballVelocity = {4.2, 4.2};

Rectangle Player1Rec = {21, 140, 7, 50};
Rectangle Player2Rec = {570, 140, 7, 50};

Rectangle BallRec = {295, 160, 9, 9};

int Player1Score = 0;
int Player2Score = 0;

int main(){
    InitWindow(screenWidth, ScreenHeight, "bong");
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        UpdatePongGame();
        DrawPongGame();
    }
}

void DrawPongGame()
{
    BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangleRec(Player1Rec, BLACK);
        DrawRectangleRec(Player2Rec, BLACK);
        DrawRectangleRec(BallRec, BLACK);

        const char *score1 = TextFormat("%i", Player1Score);
        const char *score2 = TextFormat("%i", Player2Score);

        DrawText(score1, screenWidth / 4, 20, 20, BLACK);
        DrawText(score2, screenWidth * 3 / 4, 20, 20, BLACK);
    EndDrawing();
}

void UpdatePongGame()
{
    PlayerFunction();
    BallFunction();
}

void BallFunction()
{
    if (BallRec.y > 390 || BallRec.y < 0){
        ballVelocity.y *= -1;
    }

    if (BallRec.x > 580){
        ballVelocity.x *= -1;
        Player1Score += 1;
    }

    if(BallRec.x < 0){
        ballVelocity.x *= -1;
        Player2Score += 1;
    }

    BallRec.x += ballVelocity.x;
    BallRec.y += ballVelocity.y;

    if(CheckCollisionRecs(BallRec, Player1Rec) || CheckCollisionRecs(BallRec, Player2Rec)){
        ballVelocity.x *= -1;
    }
}

void PlayerFunction()
{
    if(IsKeyDown(KEY_W) && Player1Rec.y > 0){
        Player1Rec.y -= velocity;
    }

    if(IsKeyDown(KEY_S) && Player1Rec.y < ScreenHeight - Player1Rec.height){
        Player1Rec.y += velocity;
    }

    if(IsKeyDown(KEY_UP) && Player2Rec.y > 0){
        Player2Rec.y -= velocity;
    }

    if(IsKeyDown(KEY_DOWN) && Player2Rec.y < ScreenHeight - Player2Rec.height){
        Player2Rec.y += velocity;
    }
}

