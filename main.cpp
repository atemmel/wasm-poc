#include <GL/gl.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

auto r = SDL_Rect{
    .x = 10,
    .y = 10,
    .w = 100,
    .h = 100,
};

auto width = 1024;
auto height = 768;
auto vx = 5;
auto vy = 5;

SDL_Window *window;

auto main_loop(SDL_Renderer *renderer) -> bool {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#endif
            return false;
        }
    }

    r.x += vx;
    r.y += vy;

    if (r.w + r.x >= width or r.x <= 0) {
        r.x -= vx;
        vx = -vx;
    }

    if (r.h + r.y >= height or r.y <= 0) {
        r.y -= vy;
        vy = -vy;
    }

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 69, 69, 69, 255);
    SDL_RenderPresent(renderer);
    return true;
}

auto run_main_loop(void *renderer) -> void {
    main_loop((SDL_Renderer *)renderer);
}

auto main(int argc, char **argv) -> int {
    printf("Hello!\n");
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 69, 69, 69, 255);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(run_main_loop, (void *)renderer, 0, true);
#else
    while (main_loop(renderer)) {
        SDL_Delay(16);
    };
#endif

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
