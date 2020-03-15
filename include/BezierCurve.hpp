#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "BezierPoint.hpp"


class BezierCurve : public sf::Drawable {

public:
    BezierCurve():
        points()
    {}

    void add(BezierPoint pt) {
        if(!points.empty()) {
            for(BezierPoint& point: points) {
                point.set_display_handles(false);
            }
            points.back().set_display_front_handle(true);
        }
        points.push_back(pt);
    }

    void set_last_handle(const sf::Vector2f& pos) {
        if(!points.empty()) {
            points.back().set_front_handle(pos);
        }
    }

private:
    std::vector<BezierPoint> points;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        constexpr int bezier_point_count = 50;

        // draw curves
        for(int k = 0; k < (int)points.size() - 1; ++k) {
            sf::VertexArray bezier(sf::LinesStrip, bezier_point_count);
            for(int i = 0; i < bezier_point_count; ++i) {
                auto pt1 = points[k];
                auto pt2 = points[k+1];

                bezier[i].color = sf::Color::Black;

                // cubic bezier curve
                float coef = i / float(bezier_point_count - 1);

                sf::Vector2f inter1_1 = (1 - coef) * pt1.get_pos() + coef * pt1.get_front_handle();
                sf::Vector2f inter1_2 = (1 - coef) * pt1.get_front_handle() + coef * pt2.get_back_handle();
                sf::Vector2f inter1_3 = (1 - coef) * pt2.get_back_handle() + coef * pt2.get_pos();

                sf::Vector2f inter2_1 = (1 - coef) * inter1_1 + coef * inter1_2;
                sf::Vector2f inter2_2 = (1 - coef) * inter1_2 + coef * inter1_3;

                sf::Vector2f inter3_1 = (1 - coef) * inter2_1 + coef * inter2_2;

                bezier[i].position = inter3_1;
            }
            target.draw(bezier, states);
        }

        // draw points
        for(const auto& pt: points) {
            target.draw(pt, states);
        }
    }
};