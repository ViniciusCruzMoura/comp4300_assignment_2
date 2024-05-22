#pragma once

#include "raylib.h"

class Vec2: public Vector2 {
    public:
        Vec2();
        Vec2(float xin, float yin);

        void normalize();
        float length() const;
        float dist(const Vec2 & rhs) const;

        bool operator == (const Vec2 & rhs) const;
        bool operator != (const Vec2 & rhs) const;

        Vec2 operator + (const Vec2 & rhs) const;
        Vec2 operator - (const Vec2 & rhs) const;
        Vec2 operator / (const float val) const;
        Vec2 operator * (const float val) const;

        void operator += (const Vec2 & rhs);
        void operator -= (const Vec2 & rhs);
        void operator *= (const float val);
        void operator /= (const float val);
};