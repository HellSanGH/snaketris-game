#ifndef GAME_HPP
#define GAME_HPP


#include "world.hpp"
#include "window.hpp"
#include "snake.hpp"
#include "view.hpp"
#include "enum.hpp"



struct Game {
    World* world;
    SDL_Color none_color = {100, 100, 100, 255};
    SDL_Color red_color = {255, 0, 0, 255};
    SDL_Color green_color = {0, 255, 0, 255};
    SDL_Color blue_color = {0, 0, 255, 255};
    SDL_Color star_color = {255, 255, 0, 255};

    Snake* snake;
    Statut statut;

    WorldView* view_world;
    SnakeView* snake_view;
    int score = 0;

    float DEFAULT_NOTIF_X = 200;
    float x_notif;
    string notif;

    int time_elapsed = 0;
};



void init_game(Game* game, Window* window);
bool keyboard_event(Game* game, Window* window);
void change_statut(Game* game);
void free_view(Game* game);
void snake_move(Snake* snake, World* world, Game* game, Window* window);
char direction_to_char(Snake* snake);

void game_over(Game* game, Window* window);

void init_empty_game(Game* game);

string init_save_file(Snake* snake, World* world, Game* game);

void text_to_world(World* world, char ch, int i);

Food char_to_ring_color(char color);

void string_to_direction(Snake* snake, string dir);

void init_game_from_file(Snake* snake, World* world, Game* game, string filename);

#endif
