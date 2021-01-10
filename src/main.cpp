#include <iostream>
#include <raylib.h>
#include "const.h"
#include <math.h>
#include <time.h>

bool isWindowOpen = false;

void CameraUpdate(Camera3D& cam){
    if(IsKeyDown(KEY_S)){
        cam.target.z++;
        cam.position.z++;
    }
    if(IsKeyDown(KEY_W)){
        cam.target.z--;
        cam.position.z--;    
    }
    if(IsKeyDown(KEY_D)){
        cam.target.x++;
        cam.position.x++;
    }
    if(IsKeyDown(KEY_A)){
        cam.target.x--;
        cam.position.x--;
    }
}

int main(int argc, char** argv){
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Terrain Generator");
    isWindowOpen = IsWindowReady();
    srand(time(NULL));
    
    float zCoord[COLUMNS][ROWS];

    for(int x = 0; x < COLUMNS; x+=RECTANGLE_SCALE)
        for(int y = 0; y < ROWS; y+=RECTANGLE_SCALE)
            if(rand() % 2 == 0)
                zCoord[x][y] = (int) rand() % 50;
            else
                zCoord[x][y] = ((int) rand() % 50) * -1 ;
    
    Camera3D camera = { 0 };
    camera.position = (Vector3){ WIN_WIDTH / 2, (WIN_HEIGHT / 2) - 180.0f , 240.0f };  // Camera position
    camera.target = (Vector3){ WIN_WIDTH / 2, (WIN_HEIGHT / 2) + 180.0f , 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = WIN_WIDTH * (180 / M_PI);                                // Camera field-of-view Y
    camera.type = CAMERA_PERSPECTIVE;                   // Camera mode type
    
    


    if(!isWindowOpen){
        std::cerr << "Window initialize error!\n";
    }
    else{
        SetTargetFPS(DEFAULT_FPS);
    }

    while(!WindowShouldClose()){
        BeginDrawing();
        BeginMode3D(camera);
        ClearBackground(BLACK);
        
        
        for(int y = 0; y < ROWS; y+= RECTANGLE_SCALE){
            for(int x = 0; x < COLUMNS; x+= RECTANGLE_SCALE){
                DrawLine3D({x, y, zCoord[x][y]}, {x + RECTANGLE_SCALE, y + RECTANGLE_SCALE, zCoord[x+1][y+1]}, PURPLE);
                DrawLine3D({x, y, zCoord[x][y]}, {x + RECTANGLE_SCALE, y, zCoord[x+1][y+1]}, PURPLE);
                DrawLine3D({x, y, zCoord[x][y]}, {x, y + RECTANGLE_SCALE, zCoord[x+1][y+1]}, PURPLE);                
            } 
        }


        CameraUpdate(camera);
        EndMode3D();
        EndMode2D();
        EndDrawing();
        std::cout << camera.position.z << std::endl;
        
    }


    return 0;
}