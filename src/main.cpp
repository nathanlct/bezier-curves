#include <SFML/Graphics.hpp>

#include "BezierPoint.hpp"
#include "BezierCurve.hpp"


int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(desktop, "Bezier curves", sf::Style::Default, settings);
    
    BezierCurve curve;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    switch(event.mouseButton.button) {
                        case sf::Mouse::Left:
                            curve.add(BezierPoint({(float)event.mouseButton.x, 
                                                   (float)event.mouseButton.y}));
                            break;
                        default:
                            break;
                    }
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