#pragma once

#include "EntityManager.h"
#include "RenderWindow.h"
#include "Text.h"

class Game {
    RenderWindow m_windows;
    EntityManager m_entities;
    Font m_font;
    Text m_text;

    // PlayerConfig m_player_config;
    // EnemyConfig m_enemy_config;
    // BulletConfig m_bullet_config;

    int m_score = 0;
    int m_current_frame = 0;
    int m_last_enemy_spawn_time = 0;
    
    bool m_paused = false;
    bool m_running = true;

    std::shared_ptr<Entity> m_player;

    void init(const std::string & config);
    void set_pause(bool paused);

    //systems
    void s_movement();
    void s_user_input();
    void s_lifespan();
    void s_render();
    void s_enemy_spawner();
    void s_collision();

    void spawn_player();
    void spawn_enemy();
    void spawn_small_enemies(std::shared_ptr<Entity> entity);
    void spawn_bullet(std::shared_ptr<Entity> entity, const Vec2 & mouse_pos);
    void spawn_special_weapon(std::shared_ptr<Entity> entity);

    public:        
        Game(const std::string & config);
        void run();
};