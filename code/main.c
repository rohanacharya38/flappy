//inlcudes
#include "threading.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
//
//

//defines
#define SCREEN_WIDTH 1350
#define SCREEN_HEIGHT 700
#define RECT_COUNT 190
#define sWIDTH 6
#define PADDING 1

//emum for bool
typedef enum
{
    false,
    true
} bool;
void render_string(const char *, const int, SDL_Texture *, SDL_Renderer *);
SDL_Rect get_char_rect_cood(const char);
SDL_Texture *load_img(char *, SDL_Renderer *);
int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *img_texture = load_img("../misc/font.png", renderer);
 
    bool is_running = true;
    SDL_Event event;
    while (is_running)
    {
       
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                is_running = false;
        }
    }

    return 0;
}
SDL_Texture *load_img(char *image_path, SDL_Renderer *renderer)
{
    int req_format = STBI_rgb_alpha;
    int width, height, orig_format;
    uint8_t *data = stbi_load(image_path, &width, &height, &orig_format, req_format);
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    int depth, pitch;
    depth = 32;
    pitch = 4 * width;

    SDL_Surface *surf = SDL_CreateRGBSurfaceFrom((void *)data, width, height, depth, pitch,
                                                 rmask, gmask, bmask, amask);

    SDL_Texture *ret = SDL_CreateTextureFromSurface(renderer, surf);
    return ret;
}

SDL_Rect get_char_rect_cood(const char ch)
{
    SDL_Rect tmp = {0, 0, 14, 18};
    tmp.x = ((ch - 32) % 18) * tmp.w;
    tmp.y = ((ch - 32) / 18) * tmp.h;
    return tmp;
}
void render_string(const char *str, const int length, SDL_Texture *img_texture, SDL_Renderer *renderer)
{
    SDL_Rect char_rect;
    SDL_Rect d_rect = {.w = 14, .h = 18, .x = 0, .y = 0};
    for (int i = 0; i < length; i++)
    {
        if (str[i] == '\n')
        {
            d_rect.y += d_rect.h;
            d_rect.x = 0;
            continue;
        }
        char_rect = get_char_rect_cood(str[i]);
        SDL_RenderCopy(renderer, img_texture, &char_rect, &d_rect);
        d_rect.x += d_rect.w;
    }
}
