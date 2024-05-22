#pragma once

#include <fstream>
#include "raylib.h"
#include "Vec2.h"

class CircleShape {
    float m_x; 
    float m_y; 
    float m_radius;
    Color m_fill_color;
    size_t m_points;
    float m_rotation = 0.0f;
    Color m_outline_color;
    float m_outline_thickness;
    public:
        CircleShape(float xin, float yin, float rad)
            : m_x(xin), m_y(yin), m_radius(rad) {}
        CircleShape (float r, size_t p)
            : m_radius(r), m_points(p) {}
        
        void set_fill_color(const Color & color);
        void set_outline_color(const Color & color);
        void set_outline_thickness(const float & thickness);
        void set_origin(const float x, const float y);
        void set_rotation(const float r);
        // void set_position(const float x, const float y);
        const Vec2 get_origin() const;
        const float get_radius() const;
        const Color get_fill_color() const;
        const size_t get_point_count() const;
        const float get_rotation() const;
        const Color get_outline_color() const;
        const float get_outline_thickness() const;
};

