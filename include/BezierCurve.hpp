#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "BezierPoint.hpp"


class BezierCurve : public sf::Drawable {

public:
    BezierCurve():
        points(),
        curve_segments()
    {}

    void add(BezierPoint new_pt) {
        if(!points.empty()) {
            for(BezierPoint& point: points) {
                point.set_display_handles(false);
            }
            points.back().set_display_front_handle(true);

            curve_segments.push_back(_compute_bezier_curve(points.back(), new_pt));
        }
        points.push_back(new_pt);
    }

    void set_last_handle(const sf::Vector2f& pos) {
        if(!points.empty()) {
            points.back().set_front_handle(pos);
            if(points.size() > 1) {
                curve_segments.back() = _compute_bezier_curve(points.rbegin()[1], points.back());
            }
        }
    }

private:
    std::vector<BezierPoint> points;
    std::vector<sf::VertexArray> curve_segments;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // draw curves
        for(auto& segment: curve_segments) {
            target.draw(segment, states);
        }

        // draw points
        for(const auto& pt: points) {
            target.draw(pt, states);
        }
    }

    sf::VertexArray _compute_bezier_curve(BezierPoint pt1, BezierPoint pt2, int point_count=50) {
        sf::VertexArray bezier(sf::LinesStrip, point_count);

        for(int i = 0; i < point_count; ++i) {
            bezier[i].color = sf::Color::Black;

            // cubic bezier curve
            float coef = i / float(point_count - 1);

            sf::Vector2f inter1_1 = (1 - coef) * pt1.get_pos() + coef * pt1.get_front_handle();
            sf::Vector2f inter1_2 = (1 - coef) * pt1.get_front_handle() + coef * pt2.get_back_handle();
            sf::Vector2f inter1_3 = (1 - coef) * pt2.get_back_handle() + coef * pt2.get_pos();

            sf::Vector2f inter2_1 = (1 - coef) * inter1_1 + coef * inter1_2;
            sf::Vector2f inter2_2 = (1 - coef) * inter1_2 + coef * inter1_3;

            sf::Vector2f inter3_1 = (1 - coef) * inter2_1 + coef * inter2_2;

            bezier[i].position = inter3_1;
        }

        return bezier;
    }
};