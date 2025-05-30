#include "window.hpp"
#include "world.hpp"
#include "game.hpp"
#include "snake.hpp"
#include "view.hpp"
#include <random>


int main(int argc, char** argv) {
    srand(time(NULL));
    Game g;
    Window w;

    init_window(&w, 800, 600, "Snaketris");
    init_game(&g, &w);
    
    const int SNAKE_SPEED = 100; // The lower the faster.
    static int snake_clock = SNAKE_SPEED;

    bool quit = false;
    Uint32 last_tick = SDL_GetTicks();


    while (!quit) {
        if (!(g.statut == Pause)) { Uint32 current_tick = SDL_GetTicks();
            if (current_tick - last_tick >= 1000) {
                g.time_elapsed++;
                last_tick += 1000;
            }
        } else last_tick = SDL_GetTicks();

        quit = keyboard_event(&g, &w);

        if (!(g.statut == GameOver)) {
            display_game(&w, &g);
            if (!(g.statut == Pause)) {
                snake_clock--;
                if (snake_clock == 0) {
                    snake_move(g.snake, g.world, &g, &w);
                    snake_clock = SNAKE_SPEED;
                }
            }
        } else game_over(&g, &w);
        

    }

    close_window(&w);
    free_world(g.world);
    free_snake(g.snake);
    free_view(&g);

    return 0;
}
