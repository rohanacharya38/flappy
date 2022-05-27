#pragma once
#include <SDL.h>
class bird
{
private:
    int gravity, jmp_duration;
    SDL_Rect bird_texture_rect;
    SDL_Texture *bird_texture; 
    SDL_Renderer *mrenderer;

public:
    bool is_jumping;
    bool is_dead;
    int score;
    SDL_Rect bird_rect;
    bird(SDL_Renderer *renderer);
    int die();
    int update();
    int bird_respawn();
};
