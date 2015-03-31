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
                    std::cout << "MOVE" << std::endl;
                    world.getPlayer().setTarget(new SimpleTarget(world.getPlayer(), input.mousePos()));
                }
                else
                {
                    std::cout << "ATTACK" << std::endl;

                    world.getPlayer().setTarget(new AttackTarget(world.getPlayer(), target, new ProjectileEffect(NULL, 5, 100, 1)));
                }
            }

            if(input.buttonPressed(2))
            {
                world.addEntity(new Monster(input.mousePos(), 10, 1, 100, 1, 30));
            }

            if(input.buttonPressed(3))
            {
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
