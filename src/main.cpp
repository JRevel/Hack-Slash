#include <SDL2/SDL.h>

#include <stdio.h>
#include <iostream>
#include <cstring>

#include "util/input.h"
#include "draw/screen.h"
#include "util/color.h"
#include "draw/gfx/SDL2_framerate.h"
#include "world/player/player.h"
#include "world/monster.h"
#include "world/player/target/target.h"
#include "world/fight/projectile/projectile.h"
#include "world/fight/effect.h"

int main(int argc, char** argv)
{
    int time = 0;

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
    /* Création de la fenêtre */
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                              SDL_WINDOWPOS_UNDEFINED,
                                                              640,
                                                              480,
                                                              SDL_WINDOW_SHOWN);

    Input input;

    Screen screen(window, vec2(640, 480));

    FPSmanager fpsManager;
    SDL_initFramerate(&fpsManager);
    SDL_setFramerate(&fpsManager, 60);

    World world(new Player(vec2(0, 0), 20, 5, 5, 50));
    vec2 lastMousePos = vec2(0, 0);

    if (window)
    {
        while(!input.isClosed())
        {
            time++;
            screen.initDraw();
            screen.clearScreen();
            input.update();
            world.update();
            if(input.buttonPressed(1))
            {
                LivingEntity *target = world.getEntityAt(input.mousePos());
                if(target == NULL)
                {
                    world.getPlayer().setTarget(new SimpleTarget(world.getPlayer(), input.mousePos()));
                }
                else
                {
                    Effect** effects = new Effect*[2];
                    effects[0] = new SplitEffect(new ProjectileEffect(new DamageEffect(1), 5, 25, 1), 25, M_PI*2);
                    effects[1] = new DamageEffect(1);
                    world.getPlayer().setTarget(new AttackTarget(world.getPlayer(), target, new ProjectileEffect(new MultiEffect(effects, 2), 5, 100, 1)));
                }
            }

            if(input.buttonPressed(2))
            {
                lastMousePos = input.mousePos();
                    world.addEntity(new Monster(input.mousePos(), 10, 1, 100, 20, 30));
            }
            if(input.buttonDown(2))
            {
                if((input.mousePos()-lastMousePos).length() > 40)
                {
                    lastMousePos = input.mousePos();
                    world.addEntity(new Monster(input.mousePos(), 10, 1, 100, 20, 30));
                }
            }

            if(input.buttonPressed(3))
            {
                LivingEntity *target = world.getEntityAt(input.mousePos());
                if(target == NULL)
                {
                    world.getPlayer().setTarget(new SimpleTarget(world.getPlayer(), input.mousePos()));
                }
                else
                {
                    world.getPlayer().setTarget(new AttackTarget(world.getPlayer(), target, new SplitEffect(new ProjectileEffect(new DamageEffect(10), 5, 100, 10), 5, M_PI/8)));
                }
            }

            world.draw(screen);
            screen.draw();
            SDL_framerateDelay(&fpsManager);
        }
        SDL_DestroyWindow(window);
    }
    else
    {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
    }

    SDL_Quit();

    return 0;
}
