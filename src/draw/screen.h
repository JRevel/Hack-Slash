#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "../util/vec.h"
#include "../util/color.h"

class Screen
{
private:
    vec2 m_dims;
    SDL_Renderer *m_renderer;

    SDL_Texture *m_texture;
    Uint32 *m_pixels;

public:
    Screen(SDL_Window *window, vec2 dims);
    ~Screen();
    void initDraw();
    void draw();
    void setPixel(vec2 dim, const Color &col);
    void clearScreen();

    void drawRect(vec2 pos, vec2 dim, const Color &col);
    void drawLine(vec2 A, vec2 B, const Color &col);
    void drawCircle(vec2 pos, float r, const Color &col);
};

#endif // SCREEN_H_INCLUDED
