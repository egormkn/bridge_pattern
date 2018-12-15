#ifndef SFMLDRAWINGAPI_H
#define SFMLDRAWINGAPI_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "DrawingApi.h"

class SFMLDrawingApi : public DrawingApi {

private:
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<sf::RenderTexture> texture;
    sf::Color color;

public:
    SFMLDrawingApi(const std::string &title, unsigned width, unsigned height);

    void drawCircle(int x, int y, int radius) override;

    void drawLine(int x1, int y1, int x2, int y2) override;

    void setDrawColor(int r, int g, int b) override;

    void show() override;

    void clear() override;
};

#endif // SFMLDRAWINGAPI_H
