#ifndef WORLD_HPP

#define WORLD_HPP
#include <iostream>
#include <fstream>
#include "enum.hpp"

using namespace std;



struct World {
    int width;
    int height;
    Food* grid;
};


void init_world(World* world, int w, int h);
void free_world(World* world);
void spawn_food(World* world);
void display(World* world);


#endif