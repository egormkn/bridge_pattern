#include "SFMLDrawingApi.h"

SFMLDrawingApi::SFMLDrawingApi(const std::string &title, unsigned width, unsigned height) : DrawingApi(width, height) {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
    int center_x = (sf::VideoMode::getDesktopMode().width - width) / 2;
    int center_y = (sf::VideoMode::getDesktopMode().height - height) / 2;
    window->setPosition(sf::Vector2i(center_x, center_y));
    texture = std::make_unique<sf::RenderTexture>();
    if (!texture->create(width, height)) {
        throw std::runtime_error("Unable to create texture");
    }
    color = sf::Color(255, 255, 255);
}

void SFMLDrawingApi::drawCircle(int x, int y, int radius) {
    sf::CircleShape shape(radius);
    shape.setFillColor(color);
    shape.setPosition(x - radius, y - radius);
    texture->draw(shape);
}

void SFMLDrawingApi::drawLine(int x1, int y1, int x2, int y2) {
    sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x1, y1), color),
            sf::Vertex(sf::Vector2f(x2, y2), color)
    };
    texture->draw(line, 2, sf::Lines);
}

void SFMLDrawingApi::setDrawColor(int r, int g, int b) {
    color = sf::Color(static_cast<sf::Uint8>(r), static_cast<sf::Uint8>(g), static_cast<sf::Uint8>(b));
}

void SFMLDrawingApi::show() {
    texture->display();
    sf::Sprite sprite(texture->getTexture());

    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                default:
                    break;
            }
        }

        window->clear();
        window->draw(sprite);
        window->display();
    }
}

void SFMLDrawingApi::clear() {
    texture->clear(color);
}
