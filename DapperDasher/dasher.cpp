/*
    Dapper Dasher Simple Game Project
    Richard Carter
*/

#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

// check if scarfy is on the ground
bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // update running time
    data.runningTime += deltaTime;

    if(data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;

        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }

    return data;
}

int main()
{
    // window dimensions
    double windowDimensions[2]{512, 380}; // width and height
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");
    
    // movement variables
    bool isInAir{false};
    const int jumpVel{-600}; // pixels per second
    const int nebVel{-600}; // neb x velocity p/s
    int velocity{0};

    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{};
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{};
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};

    // acceleration due to gravity (pixels/frame)/frame
    const int gravity{1'000};

    // sprite sheets
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfNebulae{10};
    AnimData nebulae[sizeOfNebulae];
    
    for(int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].pos.x = windowDimensions[0] + (i * 300);
    }

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {  
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // detla time (time since last frame)
        float dT{GetFrameTime()}; 
        
        fgX -= 80 * dT;
        mgX -= 40 * dT;
        bgX -= 20 * dT;

        if(fgX <= -foreground.width*2)
        {
            fgX = 0.0;
        }

        if(mgX <= -midground.width*2)
        {
            mgX = 0.0;
        }

        if(bgX <= -background.width*2)
        {
            bgX = 0.0;
        }

        Vector2 bg1Pos{bgX,0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width * 2,0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        Vector2 mg1Pos{mgX,0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgX + midground.width * 2,0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        Vector2 fg1Pos{fgX,0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgX + foreground.width * 2,0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        

        

        // ground check
        if(isOnGround(scarfyData, windowDimensions[1]))
        {
            isInAir = false;
            velocity = 0;
        }
        else
        {
            isInAir = true;

            // apply gravity
            velocity += gravity * dT;
        }

        // check for jumping
        if(IsKeyPressed(KEY_SPACE) && isInAir == false)
        {
            velocity += jumpVel;
        }

        for(int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebVel * dT;
        }

        // update scarfy position
        scarfyData.pos.y += velocity * dT;
       
        if(!isInAir) // freeze animation frame
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        // update nebulae
        for(int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 8);
        }

        // draw nebulae
        for(int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

       
        // stop drawing
        EndDrawing();
    }
    
    // Clean closing procedures 
    UnloadTexture(foreground);
    UnloadTexture(midground);
    UnloadTexture(background);
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}

