#include "headers/text_input.hpp"
#include "headers/stb_image.h"
#include "headers/defines.hpp"
SDL_Texture *load_img(SDL_Renderer *renderer, char *image_path, SDL_Rect *img_prop)
{
    int req_format = STBI_rgb_alpha;
    int width, height, orig_format;
    uint8_t *data = stbi_load(image_path, &width, &height, &orig_format, req_format);
    if (img_prop != NULL)
    {
        printf("%d+%d",height,width);
        img_prop->h = height;
        img_prop->w = width;
    }
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
    if(surf==NULL)
    {
        fprintf(stderr,"NULL surface while loading image");
        return 0;
    }
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
void render_string(SDL_Renderer *renderer, const char *str, const int length, SDL_Texture *img_texture, int init_x_pos, int init_y_pos)
{
    SDL_Rect char_rect;
    SDL_Rect d_rect = {14, 18, init_x_pos, init_y_pos};
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
