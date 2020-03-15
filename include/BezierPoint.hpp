#pragma once

#include <SFML/Graphics.hpp>

class BezierPoint : public sf::Drawable {

public:
    BezierPoint(sf::Vector2f pos) : 
        pos(pos), 
        front_handle(pos), 
        back_handle(pos),
        pos_shape(radius),
        front_handle_shape(radius),
        back_handle_shape(radius),
        handles(sf::Lines, 4),
        symmetric(true)
    {
        for(auto* shape: {&pos_shape, &front_handle_shape, &back_handle_shape}) {
            shape->setRadius(radius);
            shape->setFillColor(sf::Color::White);
            shape->setOutlineColor(sf::Color::Red);
            shape->setOutlineThickness(2.f);
            shape->setOrigin({radius, radius});
        }
        pos_shape.setOutlineColor(sf::Color::Black);

        pos_shape.setPosition(pos);
        front_handle_shape.setPosition(front_handle);
        back_handle_shape.setPosition(back_handle);

        handles[0].position = pos;
        handles[1].position = front_handle;
        handles[2].position = pos;
        handles[3].position = back_handle;
        for(int i = 0; i < 4; ++i) {
            handles[i].color = sf::Color::Red;
        }
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
        front_handle += delta;
        back_handle += delta;
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

    constexpr static float radius = 3.f;
    
private:
    void _set_back_handle(const sf::Vector2f& new_pos) {
        back_handle = new_pos;
        back_handle_shape.setPosition(new_pos);
        handles[3].position = new_pos;
    }
    void _set_front_handle(const sf::Vector2f& new_pos) {
        front_handle = new_pos;
        front_handle_shape.setPosition(new_pos);
        handles[1].position = new_pos;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(handles, states);
        target.draw(pos_shape, states);
        target.draw(front_handle_shape, states);
        target.draw(back_handle_shape, states);
    }

    sf::Vector2f pos;
    sf::Vector2f front_handle;
    sf::Vector2f back_handle;

    bool symmetric;

    sf::CircleShape pos_shape;
    sf::CircleShape front_handle_shape;
    sf::CircleShape back_handle_shape;

    sf::VertexArray handles;
};
