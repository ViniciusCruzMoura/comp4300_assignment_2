#pragma once

#include "CircleShape.h"

class CTransform {
    public:
        Vec2 pos = {0.0, 0.0};
        Vec2 velocity = {0.0, 0.0};;
        float angle = 0;

        CTransform(const Vec2 & p, const Vec2 & v, float a)
            : pos(p), velocity(v), angle(a) {}
};

class CShape {
    public:
        CircleShape circle;
        CShape(float radius, int points, const Color & fill, const Color & outline, float thickness)
            : circle(radius, points) {
            
            circle.set_fill_color(fill);
            circle.set_outline_color(outline);
            circle.set_outline_thickness(thickness);
            circle.set_origin(radius, radius);
        }
};

class CCollision {
    public:
        float radius = 0;
        CCollision(float r)
            : radius(r) {}
};

class CScore {
    public:
        int score = 0;
        CScore(int s)
            : score(s) {}
};

class CLifespan {
    public:
        int remaining = 0;
        int total = 0;
        CLifespan(int t)
            : remaining(t), total(t) {}
};

class CInput {
    public:
        bool up = false;
        bool left = false;
        bool right = false;
        bool down = false;
        bool shoot = false;
        
        CInput() {}
};