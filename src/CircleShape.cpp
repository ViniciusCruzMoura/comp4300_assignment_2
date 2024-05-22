#include "CircleShape.h"

void CircleShape::set_fill_color(const Color & color) {
    m_fill_color = color;
}
void CircleShape::set_outline_color(const Color & color) {
    m_outline_color = color;
}
void CircleShape::set_outline_thickness(const float & thickness) {
    m_outline_thickness = thickness;
}
void CircleShape::set_origin(const float x, const float y) {
    m_x = x;
    m_y = y;
}
void CircleShape::set_rotation(const float r) {
    m_rotation = r;
}
const Vec2 CircleShape::get_origin() const {
    return Vec2(m_x, m_y);
}
const float CircleShape::get_radius() const {
    return m_radius;
}
const Color CircleShape::get_fill_color() const {
    return m_fill_color;
}
const size_t CircleShape::get_point_count() const {
    return m_points;
}
const float CircleShape::get_rotation() const {
    return m_rotation;
}
const Color CircleShape::get_outline_color() const {
    return m_outline_color;
}
const float CircleShape::get_outline_thickness() const {
    return m_outline_thickness;
}