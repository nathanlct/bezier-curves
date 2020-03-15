#include <SFML/Graphics.hpp>

#include "BezierPoint.hpp"


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

    while(window.isOpen())
    {
        // cubic bezier between pt1 and pt2 with controls pt1_control and pt2_control
        constexpr int bezier_point_count = 50;
        sf::VertexArray bezier(sf::LinesStrip, bezier_point_count);
        for(int i = 0; i < bezier_point_count; ++i) {
            bezier[i].color = sf::Color::Blue;
            float coef = i / float(bezier_point_count - 1);

            sf::Vector2f inter1_1 = (1 - coef) * pt1.get_pos() + coef * pt1.get_front_handle();
            sf::Vector2f inter1_2 = (1 - coef) * pt1.get_front_handle() + coef * pt2.get_back_handle();
            sf::Vector2f inter1_3 = (1 - coef) * pt2.get_back_handle() + coef * pt2.get_pos();

            sf::Vector2f inter2_1 = (1 - coef) * inter1_1 + coef * inter1_2;
            sf::Vector2f inter2_2 = (1 - coef) * inter1_2 + coef * inter1_3;

            sf::Vector2f inter3_1 = (1 - coef) * inter2_1 + coef * inter2_2;

            bezier[i].position = inter3_1;
        }

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

        window.draw(bezier);
        window.draw(pt1);
        window.draw(pt2);

        window.display();
    }

    return 0;
}