#ifndef SNAKE_HPP
#define SNAKE_HPP


#include "world.hpp"
#include "window.hpp"
#include "enum.hpp"


struct Anneau {
    int ring_pos;
    Food color;
    Anneau* next = NULL;
    Anneau* prev = NULL;
};

struct Snake {
    int head_pos;
    Direction direction;
    Direction new_direction;
    Anneau* tail;
    Anneau* latest;
    bool isEating;
    int taille = 0;
};





void init_snake(Snake* snake, World* world);
int change_direction(Snake* snake, World* world);
void move_ring(Snake* snake, World* world, int old_pos);
void onEat(Snake* snake, World* world);
void free_snake(Snake* snake);

#endif
