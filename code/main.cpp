// inlcudes
#define STB_IMAGE_IMPLEMENTATION
#include "headers/defines.hpp"
#include "headers/stb_image.h"
#include "headers/bird.hpp"
#include "headers/pipes.hpp"
#include "headers/text_input.hpp"
#include "headers/pcg_basic.h"
#include <time.h>
#include <SDL.h>

int main(int argc, char **argv)
{
    pcg32_srandom(time(NULL) ^ (intptr_t)&printf, NULL);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *img_texture = load_img(renderer, "../misc/font.png", NULL);
    SDL_Texture *background_texture = load_img(renderer, "../misc/Background.png", NULL);
    SDL_Texture *ground_texture = load_img(renderer, "../misc/Ground.png", NULL);

    SDL_Rect Ground_Rect = {0, SCREEN_HEIGHT - 15, SCREEN_WIDTH, 15};
    bool is_running = true;
    bird bird1(renderer);
    pipes pipe1(renderer);
    SDL_Event event;
    while (is_running)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, NULL, NULL);
        if (bird1.bird_rect.y < 0 || SDL_HasIntersection(&bird1.bird_rect, &Ground_Rect))
        {
            bird1.die();
        }
        for (int i = 0; i < PIPE_COUNT; i++)
        {
            if (bird1.bird_rect.x == pipe1.pipe_rect_up[i].x)
            {
                bird1.score++;
            }
        }

        for (int i = 0; i < PIPE_COUNT; i++)
        {
            if (SDL_HasIntersection(&bird1.bird_rect, &pipe1.pipe_rect_up[i]) || SDL_HasIntersection(&bird1.bird_rect, &pipe1.pipe_rect_down[i]))
            {
                bird1.die();
            }
        }
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                is_running = false;
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                    is_running = false;
                    break;
                case SDL_SCANCODE_SPACE:
                    if (bird1.is_dead)
                    {
                        bird1.is_dead = false;
                        bird1.bird_respawn();
                        pipe1.respawn();
                    }
                    else
                    {
                        bird1.is_jumping = true;
                    }
                    break;

                default:
                    break;
                }
            }
        }
        if (!bird1.is_dead)
        {
            bird1.update();
            pipe1.update();
            SDL_RenderCopy(renderer, ground_texture, NULL, &Ground_Rect);
            char score_buffer[100];
            snprintf(score_buffer, 100, "SCORE:%d", bird1.score);
            render_string(renderer, score_buffer, strlen(score_buffer), img_texture, 0, 0, 50, 50);
        }
        else
        {
            render_string(renderer, "DEAD", 4, img_texture, 250, 250, 250, 250);
        }
        SDL_RenderPresent(renderer);
    }

    return 0;
}
