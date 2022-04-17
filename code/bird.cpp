
#include "headers/defines.hpp"
#include "headers/bird.hpp"
#include "headers/text_input.hpp"
bird::bird(SDL_Renderer *renderer)
{
    mrenderer=renderer;
    bird_texture = load_img(mrenderer, "../misc/bird.png", &bird_rect);
    bird_rect.h = 32;
    bird_rect.w = 32;
    bird_texture_rect = {16,16,16,16};
    is_dead=false;
    bird_respawn();
}
int bird::die()
{
    bird_rect.y = SCREEN_HEIGHT - PADDING;
    is_dead=true;
    // bird_texture = load_img("../misc/dead.png", renderer);
    return 0;
}
int bird::bird_respawn()
{
    bird_rect.x = XPOSITION;
    bird_rect.y = (SCREEN_HEIGHT) / 2;
    is_jumping = false;
    return 0;
}
int bird::update()
{
    if (is_jumping)
    {
        bird_texture_rect.x = 0;
        if (jmp_duration > 3)
        {
            jmp_duration = 0;
            is_jumping = false;
        }
        else
        {
            bird_texture_rect.x = 8;
            bird_rect.y -= 10;
            jmp_duration++;
        }
    }
    bird_rect.y += 1;
    
    SDL_RenderCopy(mrenderer, bird_texture, &bird_texture_rect, &bird_rect);
    return 0;
}