#include <SFML/Graphics.hpp>

#include "BezierPoint.hpp"
#include "BezierCurve.hpp"


int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(desktop, "Bezier curves", sf::Style::Close, settings);

    // tmp bezier curve
    BezierPoint pt1({300.f, 700.f});
    pt1.set_front_handle({120.f, 550.f});
    BezierPoint pt2({600.f, 300.f});
    pt2.set_back_handle({800.f, 700.f});

    BezierCurve curve;
    curve.add(pt1);
    curve.add(pt2);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        window.clear(sf::Color::White);
        window.draw(curve);
        window.display();
    }

    return 0;
}