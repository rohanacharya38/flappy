#pragma once
#include <SDL.h>
void render_string(SDL_Renderer *renderer,const char *string, const int length, SDL_Texture *font_img_texture,int init_x_pos  ,int init_y_pos);
SDL_Rect get_char(const char );
SDL_Texture *load_img(SDL_Renderer *renderer,char *,SDL_Rect *img_props);