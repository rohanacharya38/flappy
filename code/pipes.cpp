#include "headers/pipes.hpp"
#include "headers/text_input.hpp"
#include "headers/defines.hpp"
#include <random>
pipes::pipes(SDL_Renderer *renderer)
{
    mrenderer = renderer;
    pipe_gap = (SCREEN_WIDTH - 100) / PIPE_COUNT;
    pipe_texture_rect_down = {0, 0, 32, 320};
    pipe_texture_rect_up = {32, 0, 32, 320};
    pipe_texture = load_img(mrenderer, "../misc/pipes.png", NULL);
    respawn();
}
int pipes::create(int i)
{

    int pipe_height = (rand() % (SCREEN_HEIGHT - 2 * PADDING) + PADDING);
    pipe_rect_up[i] = {SCREEN_WIDTH, pipe_height - SCREEN_HEIGHT, PIPE_WIDTH, SCREEN_HEIGHT};
    pipe_rect_down[i] = {pipe_rect_up[i].x, pipe_height + 200, PIPE_WIDTH, SCREEN_HEIGHT};
    return 0;
}
int pipes::update()
{
    for (int i = 0; i < PIPE_COUNT; i++)
    {
        pipe_rect_up[i].x--;
        pipe_rect_down[i].x--;
        pipe_rect_up[i].x < 0 ? create(i) : 0;
        SDL_RenderCopy(mrenderer, pipe_texture, &pipe_texture_rect_up, pipe_rect_up + i);
        SDL_RenderCopy(mrenderer, pipe_texture, &pipe_texture_rect_down, pipe_rect_down + i);
    }
    return 0;
}
int pipes::respawn()
{
    for (int i = 0; i < PIPE_COUNT; i++)
    {
        create(i);
    }
    pipe_rect_up[0].x -= 500;
    pipe_rect_up[1].x -= pipe_rect_up[0].x + pipe_gap;
    pipe_rect_down[0].x = pipe_rect_up[0].x;
    pipe_rect_down[1].x = pipe_rect_up[1].x;
    return 0;
}