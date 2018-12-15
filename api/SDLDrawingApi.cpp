#include "SDLDrawingApi.h"

SDLDrawingApi::SDLDrawingApi(const std::string &title, unsigned width, unsigned height) : DrawingApi(width, height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error" << std::endl;
        throw std::runtime_error(SDL_GetError());
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }
    window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                                  SDL_WINDOW_SHOWN), SDL_DestroyWindow);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error" << std::endl;
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }
    renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
                   SDL_DestroyRenderer);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window.get());
        std::cerr << "SDL_CreateRenderer Error" << std::endl;
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }
    texture.reset(SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height),
                  SDL_DestroyTexture);
    if (texture == nullptr) {
        std::cerr << "SDL_CreateRenderer Error" << std::endl;
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }

    SDL_SetRenderTarget(renderer.get(), texture.get());
}

void SDLDrawingApi::drawCircle(int x, int y, int radius) {
    SDL_Rect rect;
    rect.x = x - radius;
    rect.y = y - radius;
    rect.w = radius * 2;
    rect.h = radius * 2;
    SDL_RenderFillRect(renderer.get(), &rect);
}

void SDLDrawingApi::drawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer.get(), x1, y1, x2, y2);
}

void SDLDrawingApi::setDrawColor(int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer.get(),
                           static_cast<Uint8>(r),
                           static_cast<Uint8>(g),
                           static_cast<Uint8>(b),
                           255);
}

void SDLDrawingApi::show() {
    SDL_SetRenderTarget(renderer.get(), nullptr);

    SDL_Rect renderQuad;
    renderQuad.x = 0;
    renderQuad.y = 0;
    renderQuad.w = getWidth();
    renderQuad.h = getHeight();

    SDL_Point screenCenter;
    screenCenter.x = getWidth() / 2;
    screenCenter.y = getHeight() / 2;

    SDL_Event event;
    bool done = false;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym != SDLK_ESCAPE) break;
                case SDL_QUIT:
                    done = true;
                default:
                    break;
            }
        }

        SDL_RenderCopyEx(renderer.get(), texture.get(), nullptr, &renderQuad, 0.0, &screenCenter, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer.get());
    }
}

void SDLDrawingApi::clear() {
    SDL_RenderClear(renderer.get());
}

SDLDrawingApi::~SDLDrawingApi() {
    SDL_Quit();
}
