#pragma once

#include <SFML/Graphics.hpp>

class BezierPoint : public sf::Drawable {

public:
    BezierPoint(sf::Vector2f pos) : 
        pos(pos), 
        front_handle(pos), 
        back_handle(pos),
        pos_shape({2 * radius, 2 * radius}),
        front_handle_shape(radius),
        back_handle_shape(radius),
        front_handle_line(sf::Lines, 2),
        back_handle_line(sf::Lines, 2),
        symmetric(true),
        display_front_handle(true),
        display_back_handle(true)
    {
        for(auto* shape: std::initializer_list<sf::Shape*>({&pos_shape, &front_handle_shape, &back_handle_shape})) {
            shape->setFillColor(sf::Color::White);
            shape->setOutlineColor(sf::Color::Blue);
            shape->setOutlineThickness(2.f);
            shape->setOrigin({radius, radius});
        }
        pos_shape.setFillColor(sf::Color::Blue);

        pos_shape.setPosition(pos);
        front_handle_shape.setPosition(front_handle);
        back_handle_shape.setPosition(back_handle);

        front_handle_line[0].position = pos;
        front_handle_line[1].position = front_handle;
        back_handle_line[0].position = pos;
        back_handle_line[1].position = back_handle;
        for(int i = 0; i < 2; ++i) {
            front_handle_line[i].color = sf::Color::Blue;
            back_handle_line[i].color = sf::Color::Blue;
        }
    }

    void set_display_front_handle(bool new_display) {
        display_front_handle = new_display;
        pos_shape.setFillColor((display_front_handle && display_back_handle) ? 
            sf::Color::Blue : sf::Color::White);
    }
    void set_display_back_handle(bool new_display) {
        display_back_handle = new_display;
        pos_shape.setFillColor((display_front_handle && display_back_handle) ? 
            sf::Color::Blue : sf::Color::White);
    }
    void set_display_handles(bool new_display) {
        set_display_front_handle(new_display);
        set_display_back_handle(new_display);
    }

    sf::Vector2f get_pos() {
        return pos;
    }
    sf::Vector2f get_front_handle() {
        return front_handle;
    }
    sf::Vector2f get_back_handle() {
        return back_handle;
    }

    void set_pos(const sf::Vector2f& new_pos) {
        sf::Vector2f delta = new_pos - pos;
        pos = new_pos;
        _set_front_handle(front_handle + new_pos - pos);
        _set_back_handle(back_handle + new_pos - pos);
    }
    void set_front_handle(const sf::Vector2f& new_pos) {
        if(symmetric) {
            _set_back_handle(back_handle - new_pos + front_handle);
        }
        _set_front_handle(new_pos);
    }
    void set_back_handle(const sf::Vector2f& new_pos) {
        if(symmetric) {
            _set_front_handle(front_handle - new_pos + back_handle);
        }
        _set_back_handle(new_pos);
    }

    constexpr static float radius = 4.f;
    
private:
    void _set_back_handle(const sf::Vector2f& new_pos) {
        back_handle = new_pos;
        back_handle_shape.setPosition(new_pos);
        back_handle_line[1].position = new_pos;
    }
    void _set_front_handle(const sf::Vector2f& new_pos) {
        front_handle = new_pos;
        front_handle_shape.setPosition(new_pos);
        front_handle_line[1].position = new_pos;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {   
        if(display_front_handle) target.draw(front_handle_line, states);
        if(display_back_handle) target.draw(back_handle_line, states);

        target.draw(pos_shape, states);

        if(display_front_handle) target.draw(front_handle_shape, states);
        if(display_back_handle) target.draw(back_handle_shape, states);
    }

    sf::Vector2f pos;
    sf::Vector2f front_handle;
    sf::Vector2f back_handle;

    bool symmetric;

    bool display_front_handle;
    bool display_back_handle;

    sf::RectangleShape pos_shape;
    sf::CircleShape front_handle_shape;
    sf::CircleShape back_handle_shape;

    sf::VertexArray front_handle_line;
    sf::VertexArray back_handle_line;
};