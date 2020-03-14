#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;


int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Bezier curves", sf::Style::Close, settings);

    // tmp bezier curve
    sf::Vector2f pt1(300.f, 700.f);
    sf::Vector2f pt1_control(120.f, 550.f);
    sf::Vector2f pt2(600.f, 300.f);
    sf::Vector2f pt2_control(800.f, 700.f);

    sf::CircleShape pt1_shape, pt2_shape;
    sf::CircleShape pt1_control_shape, pt2_control_shape;

    for(auto* shape: {&pt1_shape, &pt2_shape, &pt1_control_shape, &pt2_control_shape}) {
        shape->setRadius(4.f);
        shape->setFillColor(sf::Color::White);
        shape->setOutlineColor(sf::Color::Black);
        shape->setOutlineThickness(2.f);
        shape->setOrigin({shape->getRadius(), shape->getRadius()});
    }
    for(auto* shape: {&pt1_shape, &pt2_shape}) {
        shape->setOutlineColor(sf::Color::Black);
    }
    for(auto* shape: {&pt1_control_shape, &pt2_control_shape}) {
        shape->setOutlineColor(sf::Color::Red);
    }

    pt1_shape.setPosition(pt1);
    pt2_shape.setPosition(pt2);
    pt1_control_shape.setPosition(pt1_control);
    pt2_control_shape.setPosition(pt2_control);

    while(window.isOpen())
    {
        sf::VertexArray control_lines(sf::Lines, 4);
        control_lines[0].position = pt1;
        control_lines[1].position = pt1_control;
        control_lines[2].position = pt2;
        control_lines[3].position = pt2_control;
        for(int i = 0; i < 4; ++i) {
            control_lines[i].color = sf::Color::Red;
        }

        // cubic bezier between pt1 and pt2 with controls pt1_control and pt2_control
        constexpr int bezier_point_count = 50;
        sf::VertexArray bezier(sf::LinesStrip, bezier_point_count);
        for(int i = 0; i < bezier_point_count; ++i) {
            bezier[i].color = sf::Color::Blue;
            float coef = i / float(bezier_point_count - 1);

            sf::Vector2f inter1_1 = (1 - coef) * pt1 + coef * pt1_control;
            sf::Vector2f inter1_2 = (1 - coef) * pt1_control + coef * pt2_control;
            sf::Vector2f inter1_3 = (1 - coef) * pt2_control + coef * pt2;

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
        window.draw(control_lines);
        for(auto* shape: {&pt1_shape, &pt2_shape, &pt1_control_shape, &pt2_control_shape}) {
            window.draw(*shape);
        }

        window.display();
    }

    return 0;
}