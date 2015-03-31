#include <SDL2/SDL.h>
#include <cstring>
#include <iostream>
#include <cmath>
#include "gfx/SDL2_gfxPrimitives.h"
#define _USE_MATH_DEFINES

#include "screen.h"
#include "../util/color.h"

Screen::Screen(SDL_Window *window, vec2 dims)
{
    m_dims = dims;
    m_renderer = SDL_CreateRenderer(window, -1, 0);

    m_texture = SDL_CreateTexture(m_renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, (int)dims.x, (int)dims.y);

    m_pixels = new Uint32[(int)(dims.x*dims.y)];
    clearScreen();
}

Screen::~Screen()
{
    delete[] m_pixels;
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
}

void Screen::clearScreen()
{
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
}

void Screen::initDraw()
{
    SDL_UpdateTexture(m_texture, NULL, m_pixels, 640 * sizeof(Uint32));
}

void Screen::draw()
{
    SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(vec2 pos, const Color &col)
{
    if(pos.x >= 0 && pos.y >= 0 && pos.x < m_dims.x && pos.y < m_dims.y)
        m_pixels[(int)(pos.x+m_dims.x*pos.y)] = col.toUint();
}

void Screen::drawRect(vec2 pos, vec2 dim, const Color &col)
{
    rectangleRGBA(m_renderer, pos.x, pos.y, pos.x + dim.x, pos.y + dim.y, col.r(), col.g(), col.b(), col.a());
}

void Screen::drawLine(vec2 A, vec2 B, const Color &col)
{
    lineRGBA(m_renderer, A.x, A.y, B.x, B.y, col.r(), col.g(), col.b(), col.a());
}

void Screen::drawCircle(vec2 O, float r, const Color &col)
{
    circleRGBA(m_renderer, O.x, O.y, r, col.r(), col.g(), col.b(), col.a());
}
