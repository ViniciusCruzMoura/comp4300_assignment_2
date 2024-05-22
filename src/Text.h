#pragma once

#include <iostream>

class Text {
    std::string m_text;
    Font m_font;
    size_t m_size;
    public:
        Text() {}
        Text(std::string t, Font f, size_t s)
            : m_text(t), m_font(f), m_size(s) {}
};