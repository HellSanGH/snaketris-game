#include "snake.hpp"
#include "enum.hpp"
#include "window.hpp"
#include <fstream>

void init_snake(Snake* snake, World* world) {
    snake->head_pos = (world->width * world->height) / 2 + (world->width / 2);
    snake->direction = EAST;
    snake->new_direction = EAST;
    /*
    Anneau* first = new Anneau;
    first->ring_pos = snake->head_pos - 1;
    first->color = Red;
    first->next = NULL;
    first->prev = NULL;
    */

    snake->tail = NULL;
    snake->latest = NULL;
    snake->isEating = false;

}


int change_direction(Snake* snake, World* world) {
    int old_pos = snake->head_pos;
    if (!(
        (snake->new_direction == EAST && snake->direction == WEST) ||
        (snake->new_direction == WEST && snake->direction == EAST) ||
        (snake->new_direction == NORTH && snake->direction == SOUTH) ||
        (snake->new_direction == SOUTH && snake->direction == NORTH)
        )
    ) snake->direction = snake->new_direction;
    return old_pos;
}


void move_ring(Snake* snake, World* world, int old_head_pos) {
    if (snake->tail != NULL) {
        Anneau* current = snake->tail;

        while (current->prev != NULL) {
            current->ring_pos = current->prev->ring_pos;
            current = current->prev;
        }   
        current->ring_pos = old_head_pos;
    }
}


void onEat(Snake* snake, World* world) {
    cout << "Snaketris just ate a FOOD with ID " << world->grid[snake->head_pos] << ".\n";

    Anneau* new_ring = new Anneau;
    new_ring->ring_pos = snake->head_pos;
    
    if (world->grid[snake->head_pos] != Star){


        snake -> taille ++;
        new_ring->color = world->grid[snake->head_pos];
        new_ring->prev = NULL;
        new_ring->next = NULL;
    
        if (snake->latest == NULL) {
            snake->latest = new_ring;
            snake->tail = new_ring;
        } else {
            new_ring->next = snake->latest;
            snake->latest->prev = new_ring;
            snake->latest = new_ring;
        }
    } else {  // Si la nourriture est une étoile:
        // cout << "true" << endl;
        if (snake->latest != NULL) {             // Si le snake a au moins un anneau
            Anneau* final_ring = snake-> latest;  // final_ring est le dernier anneau qui n'a pas besoin d'être modifié 
            while (final_ring -> next != NULL){                                                    // (il parcourt les anneaux un à un à chaque boucle)
                Anneau* ring = final_ring;       // ring à comme point de départ l'anneau final_ring
                while (ring -> next != NULL){
                    ring = ring -> next;
                    Food chain = ring -> color;   // chain est la couleur de l'anneau ring
                    // cout << " Type: " << chain;
                    if (ring -> next != NULL){
                        // cout << "real" << endl;
                        if (ring -> prev -> color == chain && ring -> next  -> color == chain){  // si l'anneau précédent et suivant ring sont de la couleur de ring
                            ring -> next -> prev = ring -> prev;                           // alors on supprime l'anneau ring 
                            ring -> next -> ring_pos = ring -> ring_pos;
                            ring = ring -> next;
                            delete ring -> prev -> next;
                            ring -> prev -> next = ring;
                            while (ring -> next != NULL){        // et on modifie la position de tous les prochains anneaux pour qu'ils soient décalés d'un cran
                                ring -> next -> ring_pos = ring -> ring_pos;
                                ring = ring -> next;
                            }
                        } 
                        // else {      // juste pour tester
                        //     cout << endl;
                        // }
                    }
                }
                final_ring = final_ring -> next;      // final_ring peut alors bouger d'un cran
            }    
        }
    }


    cout << "The snake is now like this :\n";
    cout << "HEAD";
    Anneau* cache_print = snake->latest;
    while (cache_print != NULL) {
        cout << " " << cache_print->color;
        cache_print = cache_print->next;
    }
    cout << std::endl;
    cout << "The head is at pos " << snake->head_pos << " and the new ring at " << new_ring->ring_pos << "\n";
    
    spawn_food(world);
}




void free_snake(Snake* snake) {
    Anneau* current = snake->latest;
    while (current != NULL) {
        Anneau* next = current->next;
        delete current;
        current = next;
    }
    delete snake;
}
