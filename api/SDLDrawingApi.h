#ifndef SDLDRAWINGAPI_H
#define SDLDRAWINGAPI_H

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include "DrawingApi.h"

class SDLDrawingApi : public DrawingApi {
private:
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderer;
    std::shared_ptr<SDL_Texture> texture;

public:
    SDLDrawingApi(const std::string &title, unsigned width, unsigned height);

    void drawCircle(int x, int y, int radius) override;

    void drawLine(int x1, int y1, int x2, int y2) override;

    void setDrawColor(int r, int g, int b) override;

    void show() override;

    void clear() override;

    ~SDLDrawingApi();
};

#endif // SDLDRAWINGAPI_H
