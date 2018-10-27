#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window (sf::VideoMode(640, 480), "SFM Application");

    sf::CircleShape shape;
    shape.setRadius(40.0f);
    shape.setPosition(100.0f, 100.0f);
    shape.setFillColor(sf::Color::Cyan);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}