#include "Graficos.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL_image.h>

using namespace SDL2pp;

void Graficos::iniciar () {
    // Initialize SDL library
    SDL sdl(SDL_INIT_VIDEO);

    // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
    Window window("SDL2pp demo",
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  640, 480,
                  SDL_WINDOW_RESIZABLE);

    // Create accelerated video renderer with default driver
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    Surface surface(IMG_Load(DATA_PATH "/duck.png"));

    // Load sprites image as a new texture
    Texture sprites(renderer, surface);

    // Game state
    bool is_moving_rigth = false; // whether the character is currently running
    bool is_moving_left = false; // whether the character is moving left
    bool is_on_floor = false; // whether the character is on the floor
    int run_phase = -1;      // run animation phase
    float position = 0.0;    // player position

    unsigned int prev_ticks = SDL_GetTicks();
    // Main loop
    while (1) {
        // Timing: calculate difference between this and previous frame
        unsigned int frame_ticks = SDL_GetTicks();
        unsigned int frame_delta = frame_ticks - prev_ticks;
        prev_ticks = frame_ticks;

        // Event processing:
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return ;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: case SDLK_q:
                        return ;
                    case SDLK_RIGHT: is_moving_rigth = true; break;
                    case SDLK_LEFT: is_moving_left = true; break; // Move left
                    case SDLK_DOWN: is_on_floor = true; break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT: is_moving_rigth = false; break;
                    case SDLK_LEFT: is_moving_left = false; break; // Stop moving left
                    case SDLK_DOWN: is_on_floor = false; break;
                }
            }
        }

        // Update game state for this frame:
        // if character is running, move it accordingly
        if (is_moving_rigth) {
            position += frame_delta * 0.2; // Move right
            run_phase = (frame_ticks / 100) % 6;
        }
            // Check if moving left
        else if (is_moving_left) {
            position -= frame_delta * 0.2; // Move left
            run_phase = (frame_ticks / 100) % 6;
        } else {
            run_phase = 0;
        }

        // If player passes past the right side of the window, wrap him
        if (position > renderer.GetOutputWidth())
            position = -50;

        // If player passes past the left side of the window, wrap him
        if (position < -50)
            position = renderer.GetOutputWidth();

        int vcenter = renderer.GetOutputHeight() / 1.1; // Y coordinate of window center

        // Clear screen
        renderer.Clear();

        // Pick sprite from sprite atlas based on whether
        // player is running and run animation phase
        int src_x = 0, src_y = 6; // by default, standing sprite
        if (is_moving_rigth || is_moving_left) {
            // one of 8 run animation sprites
            src_x = 32 * run_phase;
        } else if (is_on_floor){
            src_y = 70; // standing sprite
        }

        // Draw player sprite with flipping based on direction

        if (is_moving_left) {
            renderer.Copy(
                    sprites,
                    Rect(src_x, src_y, 32, 24),
                    Rect((int)position, vcenter - 50, 50, 50),
                    0.0,
                    Point(0, 0),
                    SDL_FLIP_HORIZONTAL
            );
        } else {
            // Standing sprite
            renderer.Copy(
                    sprites,
                    Rect(src_x, src_y, 32, 24),
                    Rect((int)position, vcenter - 50, 50, 50)
            );
        }

        // Show rendered frame
        renderer.Present();

        // Frame limiter: sleep for a little bit to not eat 100% of CPU
        SDL_Delay(1);
    }

    // Here all resources are automatically released and library deinitialized
    return ;
}