#pragma once
#define PIPE_COUNT 4
#include <SDL.h>
struct pipes
{
private:
    SDL_Rect pipe_texture_rect_up;
    SDL_Rect pipe_texture_rect_down;
    SDL_Texture *pipe_texture;
    int pipe_gap;
    SDL_Renderer *mrenderer;

public:
    SDL_Rect pipe_rect_up[PIPE_COUNT];
    SDL_Rect pipe_rect_down[PIPE_COUNT];
    pipes(SDL_Renderer *renderer);
    int update();
    int create(int i);
    int respawn();
};
