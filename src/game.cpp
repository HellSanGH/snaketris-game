#include "game.hpp"
#include "enum.hpp"
#include <fstream>

void init_game(Game* game, Window* window) {
    World* w = new World;
    Snake* s = new Snake;

    init_world(w, 50, 30);
    game->world = w;

    init_snake(s, game->world);
    game->snake = s;

    game->statut = Play;

    game->score = 0;

    game->x_notif = game->DEFAULT_NOTIF_X;
    game->notif = "";

    game->time_elapsed = 0;


    //All food test
    /*
    int cos1 = (game->world->width * game->world->height) / 2 + (game->world->width / 2) - (2*game->world->width) - 3;
    game->world->grid[cos1] = Red;

    int cos2 = (game->world->width * game->world->height) / 2 + (game->world->width / 2) - (2*game->world->width) - 1;
    game->world->grid[cos2] = Green;

    int cos3 = (game->world->width * game->world->height) / 2 + (game->world->width / 2) - (2*game->world->width) + 1;
    game->world->grid[cos3] = Blue;

    int cos4 = (game->world->width * game->world->height) / 2 + (game->world->width / 2) - (2*game->world->width) + 3;
    game->world->grid[cos4] = Star;
    */
    

    for (int i = 0; i<10; i++) spawn_food(game->world);

    game->view_world = new WorldView;
    game->view_world->Red_food = load_image(window, "food_red.png");
    game->view_world->Green_food = load_image(window, "food_green.png");
    game->view_world->Blue_food = load_image(window, "food_blue.png");
    game->view_world->Star_food = load_image(window, "food_star.png");

    game->snake_view = new SnakeView;
    game->snake_view->Red_ring = load_image(window, "body_red.png");
    game->snake_view->Green_ring = load_image(window, "body_green.png");
    game->snake_view->Blue_ring = load_image(window, "body_blue.png");

    game->snake_view->Dead_ring = load_image(window, "body_dead.png");

    game->snake_view->head_open_up = load_image(window, "head_open_up.png");
    game->snake_view->head_open_down = load_image(window, "head_open_down.png");
    game->snake_view->head_open_right = load_image(window, "head_open_right.png");
    game->snake_view->head_open_left = load_image(window, "head_open_left.png");

    game->snake_view->head_close_up = load_image(window, "head_close_up.png");
    game->snake_view->head_close_down = load_image(window, "head_close_down.png");
    game->snake_view->head_close_right = load_image(window, "head_close_right.png");
    game->snake_view->head_close_left = load_image(window, "head_close_left.png");

    game->snake_view->head_dead = load_image(window, "head_dead.png");    

}









bool keyboard_event(Game* game, Window* window) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        }

        if (event.type == SDL_KEYDOWN) {

            switch (event.key.keysym.sym) {
                case SDLK_q:
                    cout << "Quitter le jeu" << endl;
                    return true;

                case SDLK_r:
                    cout << "Reset du jeu" << endl;
                    free_world(game->world);
                    free_snake(game->snake);
                    free_view(game);
                    init_game(game, window);
                    break;

                case SDLK_s:
                    cout << "Sauvegarde de la partie" << endl;
                    init_save_file(game -> snake, game -> world, game);
                    break;
                
                case SDLK_l:
                    cout << "Charge la partie" << endl;
                    init_game_from_file(game -> snake, game -> world, game, "world.dat");
                    break;

                case SDLK_LEFT:
                    game->snake->new_direction = WEST;
                    break;

                case SDLK_RIGHT:
                    game->snake->new_direction = EAST;
                    break;

                case SDLK_UP:
                    game->snake->new_direction = NORTH;
                    break;

                case SDLK_DOWN:
                    game->snake->new_direction = SOUTH;
                    break;

                case SDLK_SPACE:
                    if (game->statut == Pause) { game->statut = Play; cout << "Fin de la pause" << endl; }
                    else if (game->statut == Play) { game->statut = Pause; cout << "Mise en pause" << endl; }
                    break;
            }
        }
    }

    return false;
}



void change_statut(Game* game) {
    switch (game->statut) {
        case Begin:
            game->statut = Play;
            break;

        case Play:
            game->statut = Pause;
            break;

        case Pause:
            game->statut = Play;
            break;

        case Win:
            break;
        case GameOver:
            game->statut = Begin;
            break;
    }
}

void snake_move(Snake* snake, World* world, Game* game, Window* window){
    int old_pos = change_direction(snake, world);
    switch (snake->direction) {
        case NORTH:
            if (snake->head_pos -  world->width < 0) game -> statut = GameOver;
            else{
                snake->head_pos -= world->width;
                }
            break;
        
        case SOUTH:
            if (snake->head_pos + world->width > world->width * world->height) game -> statut = GameOver;
            else{
                snake->head_pos += world->width;
                }
            break;

        case WEST:
            if (snake->head_pos % world -> width == 0) game -> statut = GameOver;
            else {
                snake->head_pos -= 1;
            }
            break;

        case EAST:
            if (snake->head_pos % world -> width == world-> width -1) game -> statut = GameOver;
            else {
                snake->head_pos += 1;
            }
            break;
    }
    if (game->statut != GameOver) move_ring(snake, world, old_pos);

    if (world->grid[snake->head_pos] == Red || world->grid[snake->head_pos] == Green || world->grid[snake->head_pos] == Blue || world->grid[snake->head_pos] == Star) {
        onEat(snake, world);
        snake->isEating = true;

        if (!(world->grid[snake->head_pos] == Star)) {
            game->notif = "+1";
            game->x_notif = 0;
            game->score++;
        } else {
            game->notif = "+3";
            game->x_notif = 0;
            cout << game->score << std::endl;
            game->score += 3;
            cout << game->score << std::endl << std::endl;
        }

        world->grid[snake->head_pos] = None;

    } else snake->isEating = false;
    
    if (snake-> latest != NULL){
        Anneau* ptr = snake->latest;
        while (ptr -> next != NULL && ptr->next -> ring_pos != snake->head_pos){
            ptr = ptr -> next;
        }
        if (ptr -> next != NULL){
            if (ptr->next -> ring_pos == snake->head_pos)game -> statut = GameOver;
        }
        
    }
}

void free_view(Game* game) {
    /*delete &game->view_world->Red_food;
    delete &game->view_world->Green_food;
    delete &game->view_world->Blue_food;
    delete &game->view_world->Star_food;
    delete game->view_world;

    delete &game->snake_view->Red_ring;
    delete &game->snake_view->Green_ring;
    delete &game->snake_view->Blue_ring;

    delete &game->snake_view->Dead_ring;

    delete &game->snake_view->head_open_up;
    delete &game->snake_view->head_open_down;
    delete &game->snake_view->head_open_right;
    delete &game->snake_view->head_open_left;

    delete &game->snake_view->head_close_up;
    delete &game->snake_view->head_close_down;
    delete &game->snake_view->head_close_right;
    delete &game->snake_view->head_close_left;

    delete &game->snake_view->head_dead;

    delete game->snake_view;*/
}




void game_over(Game* game, Window* window){
    set_color(&window->foreground, &game->red_color);
    draw_text(window, "Game Over!", 300, 270);
    int border_thickness = 0;
    int cell_width = window->width / game->world->width - border_thickness;
    int cell_height = window->height / game->world->height - border_thickness;
    int head_x = game->snake->head_pos % game->world->width;
    int head_y = game->snake->head_pos / game->world->width;
    draw_texture(window, game->snake_view->head_dead, head_x * (cell_width + border_thickness) + border_thickness / 2, head_y * (cell_height + border_thickness) + border_thickness / 2, cell_width, cell_height);

    if (game->snake->latest != NULL) {
        Anneau* current = game->snake->latest;

        int cell_width = window->width / game->world->width - border_thickness;
        int cell_height = window->height / game->world->height - border_thickness;
        int ring_x = current->ring_pos % game->world->width;
        int ring_y = current->ring_pos / game->world->width;
        draw_texture(window, game->snake_view->Dead_ring, ring_x * (cell_width + border_thickness) + border_thickness / 2, ring_y * (cell_height + border_thickness) + border_thickness / 2, cell_width, cell_height);

        while (current != NULL) {
            int cell_width = window->width / game->world->width - border_thickness;
            int cell_height = window->height / game->world->height - border_thickness;
            int ring_x = current->ring_pos % game->world->width;
            int ring_y = current->ring_pos / game->world->width;
            draw_texture(window, game->snake_view->Dead_ring, ring_x * (cell_width + border_thickness) + border_thickness / 2, ring_y * (cell_height + border_thickness) + border_thickness / 2, cell_width, cell_height);
            current = current->next;
        }
    }

    refresh_window(window);
}




void init_empty_game(Game* game){ // originalement devait m'aider après avoir fait free_world et free_snake mais n'a pas fonctionné dans le chargement
    World* w = new World;         //  comme je le voulais pour une raison que j'ignore
    Snake* s = new Snake;

    init_world(w, 50, 30);
    game->world = w;

    init_snake(s, game->world);
    game->snake = s;

    game->statut = Begin;

    game->score = 0;

}

char direction_to_char(Snake* snake){
    switch (snake->direction){
        case NORTH:
            return 'N';
        case SOUTH:
            return 'S';
        case WEST:
            return 'W';
        case EAST:
            return 'E';
        default:
            return 'E';
    }
}

string init_save_file(Snake* snake, World* world, Game* game){
    Anneau* ptr = snake->latest;
    
    string filename = "world.dat";
    ofstream fic(filename);

    fic << world -> height << endl;
    fic << world -> width << endl;
    fic << game -> score << endl;
    fic << game -> time_elapsed << endl;
    fic << snake -> taille << endl;
    fic << snake -> head_pos << endl;
    fic << direction_to_char(snake) << endl;
    // display(world);      //juste une vérification
    for (int i = 0; i < snake->taille; i++){
        fic << ptr -> ring_pos << endl;
        switch (ptr->color){
                case Red:
                    fic << 'R' << endl;
                    break;
                case Green:
                    fic << 'G' << endl;
                    break;
                case Blue:
                    fic << 'B' << endl;
                    break;
                default:
                    break;
        }
        if (i < snake->taille-1) ptr = ptr -> next;
    }
    
    string monde = "";

    for (int i = 0; i<world->height*world->width; i++){
        switch (world->grid[i]){
            case None:
                monde = monde + ".";
                break;
            case Star:
                monde = monde + "2";
                break;
            case Red:
                monde = monde + "#";
                break;
            case Green:
                monde = monde + "$";
                break;
            case Blue:
                monde = monde + "1";
                break;
        }
    }
    
    // monde[snake->head_pos] = 'S';         // version alternative inutilisée, supprime si tu veux
    // if (snake-> latest != NULL){
    //     Anneau* ptr = snake->latest;
    //     while (ptr != NULL){
    //         switch (ptr->color){
    //             case Red:
    //                 monde[ptr -> ring_pos] = 'R';
    //                 break;
    //             case Green:
    //                 monde[ptr -> ring_pos] = 'G';
    //                 break;
    //             case Blue:
    //                 monde[ptr -> ring_pos] = 'B';
    //                 break;
    //             default:
    //                 break;
    //         }
    //         ptr = ptr -> next;
    //     }
    // }

    for (int i = 0; i<world->height*world->width; i++){
        if (i%world->width == 0) fic << endl;
        fic << monde[i];
    }

    return filename;
}
void text_to_world(World* world, char ch, int i) {
    switch (ch) {
        case '.':
            world -> grid[i] = None;
            break;
        case '#':
            world -> grid[i] = Red;
            break;
        case '$':
            world -> grid[i] = Green;
            break;
        case '1':
            world -> grid[i] = Blue;
            break;
        case '2':
            world -> grid[i] = Star;
            break;
    }
}


Food char_to_ring_color(char color){
    switch (color){
        case 'R':
            return Red;
            break;
        case 'G':
            return Green;
            break;
        case 'B':
            return Blue;
            break;
        default:
            return None;
            break;
    }
}




void char_to_direction(Snake* snake, char direct){
    switch (direct){
        case 'N':
            snake -> direction = NORTH;       // les deux sont nécessaires si l'on ne veut pas s'embêter avec la direction pré-chargement
            snake -> new_direction = NORTH;
            break;
        case 'S':
            snake -> direction = SOUTH;
            snake -> new_direction = SOUTH;
            break;
        case 'W':
            snake -> direction = WEST;
            snake -> new_direction = WEST;
            break;
        case 'E':
            snake -> direction = EAST;
            snake -> new_direction = EAST;
            break;
    }
}
void init_game_from_file(Snake* snake, World* world, Game* game, string filename){
    //init_empty_game(game);

    Anneau* ptr = new Anneau;
    snake->latest = ptr;
    char saved_direction;
    char type;

    ifstream fic(filename);
    if (!fic){
        cout << "ERREUR: Impossible d'ouvrir le fichier" << endl;
        return;
    }


    fic >> world->height >> world->width >> game->score >> game->time_elapsed >> snake->taille >> snake->head_pos;


    fic >> std::ws >> saved_direction;
    char_to_direction(snake, saved_direction);


    for (int i = 0; i < snake->taille; i++) {
        if (i == 0) {
            fic >> ptr->ring_pos;
            fic >> type;
            ptr->color = char_to_ring_color(type);
        } else {
            Anneau* ptr_2 = new Anneau;
            fic >> ptr_2->ring_pos;
            fic >> type;
            ptr_2->color = char_to_ring_color(type);
            ptr_2->prev = ptr;
            ptr->next = ptr_2;
            ptr = ptr_2;
        }

        if (i == snake->taille - 1) {
            snake->tail = ptr;
        }
    }

    int i = 0;
    char c;
    while (fic >> std::noskipws >> c && i < world->width * world->height) {
        if (c == '\n' || c == '\r') continue; 
        text_to_world(world, c, i);
        i++;
    }
    
    

    fic.close();
}

