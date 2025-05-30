#include "world.hpp"
#include <fstream>
#include "enum.hpp"
#include <random>


void init_world(World* world, int w, int h) {
    world->grid = new Food[h*w];
    for (int i = 0; i < w * h; i++) world->grid[i] = None;
    world->height = h;
    world->width = w;
}

void free_world(World* world) {
    delete[] world->grid;
    world->grid = NULL;
}

void display(World* world) {
    for (int i = 0; i < world->width * world->height; i++) {

        if (i%world->width == 0) cout << endl;

        switch (world->grid[i]) {
            case None:
                cout << ".";
                break;
            
            case Red:
                cout << "#";
                break;

            case Green:
                cout << "$";
                break;

            case Blue:
                cout << "1";
                break;

            case Star:
                cout << "2";
                break;
        }

    }

}


void spawn_food(World* world) {
    int dim = world->height * world->width;
    int new_food_coords = rand() % dim;
    int food_color_id = rand() % 4;

    if (!
        (world->grid[new_food_coords] == Red ||
        world->grid[new_food_coords] == Green ||
        world->grid[new_food_coords] == Blue ||
        world->grid[new_food_coords] == Star)) {
        switch (food_color_id) {
        case 0:
            world->grid[new_food_coords] = Red;
            break;
        case 1:
            world->grid[new_food_coords] = Green;
            break;
        case 2:
            world->grid[new_food_coords] = Blue;
            break;
        case 3:
            world->grid[new_food_coords] = Star;
            break;
        default:
            break;
        }
    } else spawn_food(world);
}