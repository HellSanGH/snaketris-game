#include "view.hpp"
#include "enum.hpp"
#include "game.hpp"
#include <fstream>


void display_game(Window* window, Game* game) {

    int y = 0;
    int x = 0;
    int border_thickness = 0;

    int cell_width = window->width / game->world->width - border_thickness;
    int cell_height = window->height / game->world->height - border_thickness;

    // AFFICHAGE DU MONDE
    for (int i = 0; i < (game->world->height) * (game->world->width); i++) {
        set_color(&window->foreground, &game->none_color);
        draw_fill_rectangle(window, x + border_thickness / 2, y + border_thickness / 2, cell_width, cell_height);
        switch (game->world->grid[i]) {
            case None:
                break;
            case Red:
                draw_texture(window, game->view_world->Red_food, x + border_thickness / 2, y + border_thickness / 2, cell_width, cell_height);
                break;
            case Green:
                draw_texture(window, game->view_world->Green_food, x + border_thickness / 2, y + border_thickness / 2, cell_width, cell_height);
                break;
            case Blue:
                draw_texture(window, game->view_world->Blue_food, x + border_thickness / 2, y + border_thickness / 2, cell_width, cell_height);
                break;
            case Star:
                draw_texture(window, game->view_world->Star_food, x + border_thickness / 2, y + border_thickness / 2, cell_width, cell_height);
                break;
        }


        // draw_fill_rectangle(window, x + border_thickness / 2, y + border_thickness / 2, cell_width, cell_height);

        x += cell_width + border_thickness;
        if ((i + 1) % game->world->width == 0) {
            y += cell_height + border_thickness;
            x = 0;
        }
    }
    //==================================================================


    // AFFICHAGE DU SERPENT : ANNEAUX
    if (game->snake->latest != NULL) {
        Anneau* ring = game->snake->latest;
        while (ring != NULL) {
            /*switch (ring->color) {
            case Red:
                set_color(&window->foreground, &game->red_color);
                break;
            case Green:
                set_color(&window->foreground, &game->green_color);
                break;
            case Blue:
                set_color(&window->foreground, &game->blue_color);
                break;
            default:
                set_color(&window->foreground, &game->none_color);
                break;
            }
            */
            int ring_x = ring->ring_pos % game->world->width;
            int ring_y = ring->ring_pos / game->world->width;
    
            /*draw_fill_rectangle(
                window,
                ring_x * (cell_width + border_thickness) + border_thickness / 2,
                ring_y * (cell_height + border_thickness) + border_thickness / 2,
                cell_width,
                cell_height
            );
            */
           SDL_Texture* toDisplay;

           switch (ring->color) {
            case Red:
                toDisplay = game->snake_view->Red_ring;
                break;
            case Green:
                toDisplay = game->snake_view->Green_ring;
                break;
            case Blue:
                toDisplay = game->snake_view->Blue_ring;
                break;
            default:
                toDisplay = game->snake_view->Red_ring;
                break;
            }
    
            draw_texture(window, toDisplay,
                ring_x * (cell_width + border_thickness) + border_thickness / 2,
                ring_y * (cell_height + border_thickness) + border_thickness / 2,
                cell_width,
                cell_height);

            ring = ring->next;
        }
    }
    
    
    // AFFICHAGE DE LA TÊTE
    SDL_Color snake_color = {255, 255, 255, 255};
    set_color(&window->foreground, &snake_color);
    
    int head_x = game->snake->head_pos % game->world->width;
    int head_y = game->snake->head_pos / game->world->width;
    
    
    /*draw_fill_rectangle(
        window,
        head_x * (cell_width + border_thickness) + border_thickness / 2,
        head_y * (cell_height + border_thickness) + border_thickness / 2,
        cell_width,
        cell_height
    );
    */
   SDL_Texture* head_display;
   if (game->snake->isEating) {
        switch (game->snake->direction) {
            case NORTH:
                head_display = game->snake_view->head_open_up;
                break;
            case SOUTH:
                head_display = game->snake_view->head_open_down;
                break;
            case EAST:
                head_display = game->snake_view->head_open_right;
                break;
            case WEST:
                head_display = game->snake_view->head_open_left;
                break;
            default:
                head_display = game->snake_view->head_open_up;
                break;
        }
    } else {
        switch (game->snake->direction) {
            case NORTH:
                head_display = game->snake_view->head_close_up;
                break;
            case SOUTH:
                head_display = game->snake_view->head_close_down;
                break;
            case EAST:
                head_display = game->snake_view->head_close_right;
                break;
            case WEST:
                head_display = game->snake_view->head_close_left;
                break;
            default:
                head_display = game->snake_view->head_close_up;
                break;
        }
    }
   draw_texture(window, head_display, head_x * (cell_width + border_thickness) + border_thickness / 2, head_y * (cell_height + border_thickness) + border_thickness / 2, cell_width, cell_height);
    

    //==================================================================








    
    set_color(&window->foreground, &snake_color);
    string score_text = "Score: " + to_string(game->score);
    draw_text(window, score_text, 20, 30);

    set_color(&window->foreground, &snake_color);
    string time_text = "Time Elapsed: " + to_string(game->time_elapsed);
    draw_text(window, time_text, 580, 30);

    set_color(&window->foreground, &snake_color);
    draw_text(window, "Controls", 20, 330);
    draw_text(window, "Arrows : Move", 20, 360);
    draw_text(window, "Q : Quit", 20, 390);
    draw_text(window, "L : Load", 20, 420);
    draw_text(window, "S : Save", 20, 450);
    draw_text(window, "R : New game", 20, 480);
    draw_text(window, "Space : Pause/Unpause", 20, 510);

    if (game->x_notif < game->DEFAULT_NOTIF_X) {
        set_color(&window->foreground, &game->star_color);
        draw_text(window, game->notif, 130, 40-(game->x_notif/20)); // range: 10 - 50
        game->x_notif++;
    }

    refresh_window(window);
    //display(game->world);

    SDL_Delay(1);
}



