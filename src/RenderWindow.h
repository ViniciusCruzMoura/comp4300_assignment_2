#pragma once

class RenderWindow {
    std::string m_title = "Window - Sample Title";
    size_t m_width = 800;
    size_t m_height = 450;
    size_t m_framerate_limit = 30;
    public:
        RenderWindow() {};
        // RenderWindow(std::string title, size_t height, size_t width) {
        //     m_title = title;
        //     m_height = height;
        //     m_width = width;
        // };
        // void init() {
        //     InitWindow(m_width, m_height, m_title.c_str());
        //     SetTargetFPS(m_framerate_limit);
        // };
        const bool is_open() const {
            return !WindowShouldClose();
        };
        void close() {
            CloseWindow();
        };
        void create(size_t w, size_t h, std::string t) {
            m_width = w;
            m_height = h;
            m_title = t;
            InitWindow(m_width, m_height, m_title.c_str());
        };
        void set_framerate_limit(size_t fps) {
            m_framerate_limit = fps;
            SetTargetFPS(m_framerate_limit);
        };
        const size_t get_framerate_limit() const {
            return m_framerate_limit;
            // return GetFPS();
        }
        const std::string get_title() const {
            return m_title;
        };
        void set_title(std::string title) {
            m_title = title;
        };
        const int get_width() const {
            return m_width;
        };
        void set_width(int width) {
            m_width = width;
        };
        const int get_height() const{
            return m_height;
        };
        void set_height(int height) {
            m_height = height;
        };
        const Vec2 get_size() const {
            return Vec2(static_cast<float>(m_width), static_cast<float>(m_height));
        }
};