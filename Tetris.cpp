#include <iostream>
#include <SDL2\SDL.h>
#include "Screen.h"
#include <math.h>
#include <time.h>
#include <cstdlib>

using namespace std;
struct Variables
{
    bool breakKey{1};
    bool flag{false};
    SDL_Event event;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int keyInput = 0;
    int time = SDL_GetTicks();
    int elapsed = 0;
    bool stopGame = 0;
};

int main(int argc, char *argv[])
{
    srand(time(NULL));
    Screen screen;
    Variables variables;
    if (screen.init() == false)
    {
        cout << "SDL initialization failed." << endl;
    }
    screen.start();
    while (!variables.flag)
    {
        if (variables.breakKey)
        {
            if (!variables.stopGame)
            {
                variables.elapsed = SDL_GetTicks();
                if ((variables.elapsed - variables.time) > 499)
                {
                    if (!screen.moveElement(2))
                    {
                        variables.stopGame = 1;
                    }
                    variables.time = variables.elapsed;
                }
                if (variables.keyInput > 0)
                {
                    screen.moveElement(variables.keyInput);
                    variables.keyInput = 0;
                }
            }
        }
        while (SDL_PollEvent(&variables.event))
        {
            if (variables.event.type == SDL_QUIT)
            {
                variables.flag = true;
            }
            else if (variables.event.type == SDL_KEYDOWN)
            {
                switch (variables.event.key.keysym.sym)
                {
                case SDLK_DOWN:
                    variables.keyInput = 2;
                    break;
                case SDLK_LEFT:
                    variables.keyInput = 1;
                    break;
                case SDLK_RIGHT:
                    variables.keyInput = 3;
                    break;
                case SDLK_p:
                    variables.breakKey = !variables.breakKey;
                    break;
                case SDLK_q:
                    variables.keyInput = 4;
                    break;
                case SDLK_e:
                    variables.keyInput = 5;
                    break;
                default:
                    cout << "undifained key" << endl;
                    break;
                }
            }
        }
    }
    screen.close();
    return 0;
}
