#ifndef VIEW_HPP
#define VIEW_HPP


#include "world.hpp"
#include "window.hpp"
#include "enum.hpp"


struct Game;

struct WorldView {
    SDL_Texture* Red_food;
    SDL_Texture* Green_food;
    SDL_Texture* Blue_food;
    SDL_Texture* Star_food;
};

struct SnakeView {
    SDL_Texture* head_open_up;
    SDL_Texture* head_open_down;
    SDL_Texture* head_open_right;
    SDL_Texture* head_open_left;

    SDL_Texture* head_close_up;
    SDL_Texture* head_close_down;
    SDL_Texture* head_close_right;
    SDL_Texture* head_close_left;

    SDL_Texture* head_dead;

    SDL_Texture* Red_ring;
    SDL_Texture* Green_ring;
    SDL_Texture* Blue_ring;
    SDL_Texture* Star_ring;

    SDL_Texture* Dead_ring;
};

void display_game(Window* window, Game* game);

#endif
