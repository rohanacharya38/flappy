#pragma once
#include <SDL.h>
void render_string(SDL_Renderer *renderer, const char *str, const int length, SDL_Texture *img_texture, int init_x_pos, int init_y_pos,int height,int width);
SDL_Rect get_char(const char );
SDL_Texture *load_img(SDL_Renderer *renderer,const char *,SDL_Rect *img_props);