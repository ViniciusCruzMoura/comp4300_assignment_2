#include "Game.h"

Game::Game(const std::string & config) {
    init(config);
};

void Game::init(const std::string & path) {
    // std:ifstream fin(path);

    m_windows.create(800, 450, "Engine GEPT-1");
    m_windows.set_framerate_limit(30);
    
    spawn_player();
}

void Game::run() {
    while(m_running) {
        m_entities.update();

        if (!m_paused) {
            s_enemy_spawner();
            s_movement();
            s_collision();
        }
        s_user_input();
        s_render();

        m_current_frame++;
        
        // std::cout << m_current_frame << std::endl;
        // std::cout << m_player->tag() << std::endl;
        // std::cout << m_player->c_input->up << std::endl;
        // std::cout << m_player->c_transform->pos.y << std::endl;
    }
    m_windows.close();
}

void Game::set_pause(bool paused) {
    m_paused = paused;
}

void Game::spawn_player() {
    //create a entity and get the return type
    auto entity = m_entities.add_entity("player");
    //give the entity a transform
    // entity->c_transform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);
    entity->c_transform = std::make_shared<CTransform>(
        Vec2(m_windows.get_size().x/2.0f, m_windows.get_size().y/2.0f), Vec2(1.0f, 1.0f), 0.0f
    );
    //add a shape
    entity->c_shape = std::make_shared<CShape>(32.0f, 8, RED, BLUE, 4.0f);
    //add input component
    entity->c_input = std::make_shared<CInput>();
    //against entitymanager paradigm, but we use player so much, so its worth it
    m_player = entity;
}

void Game::spawn_enemy() {
    auto enemy = m_entities.add_entity("enemy");
    //give the entity a transform
    // entity->c_transform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);
    enemy->c_transform = std::make_shared<CTransform>(
        Vec2(
            rand() % static_cast<int>(m_windows.get_size().x), 
            rand() % static_cast<int>(m_windows.get_size().y)
        ),
        Vec2(5.0f, 5.0f), 0.0f
    );
    //add a shape
    enemy->c_shape = std::make_shared<CShape>(rand() % (32 - 24) + 24, rand() % (10 - 3) + 3, BLUE, RED, 4.0f);
    // enemy->c_shape = std::make_shared<CShape>(32.0f, 3, BLUE, RED, 4.0f);
    //add input component
    enemy->c_input = std::make_shared<CInput>();

    m_last_enemy_spawn_time = m_current_frame;
}

void Game::spawn_bullet(std::shared_ptr<Entity> entity, const Vec2 & mouse_pos) {
    auto bullet = m_entities.add_entity("bullet");
    bullet->c_transform = std::make_shared<CTransform>(mouse_pos, Vec2(0,0), 0.0f);
    bullet->c_shape = std::make_shared<CShape>(10, 8, ORANGE, GREEN, 2);
}

void Game::s_enemy_spawner() {
    size_t seconds = 5;
    size_t wait_time = m_windows.get_framerate_limit() * seconds;
    bool is_time_to_spawn = m_current_frame % wait_time == 0;
    
    if (is_time_to_spawn) {
        spawn_enemy();
    }

    m_current_frame -= m_last_enemy_spawn_time;
}

void Game::s_collision() {
    for (auto b : m_entities.get_entities("bullet")) {
        for (auto e : m_entities.get_entities("enemy")) {}
    }
}

void Game::s_render() {
    BeginDrawing();
    ClearBackground(BLACK);
    // DrawCircle(m_player->c_transform->pos.x, m_player->c_transform->pos.y, m_player->c_shape->circle.get_radius(), m_player->c_shape->circle.get_fill_color());
    // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    
    // DrawPoly(m_player->c_transform->pos, m_player->c_shape->circle.get_point_count(), m_player->c_shape->circle.get_radius(), m_player->c_shape->circle.get_rotation(), m_player->c_shape->circle.get_fill_color());
    // DrawPolyLinesEx(m_player->c_transform->pos, m_player->c_shape->circle.get_point_count(), m_player->c_shape->circle.get_radius(), m_player->c_shape->circle.get_rotation(), m_player->c_shape->circle.get_outline_thickness(), m_player->c_shape->circle.get_outline_color());

    for (auto e : m_entities.get_entities()) {
        DrawPoly(e->c_transform->pos, 
                e->c_shape->circle.get_point_count(), 
                e->c_shape->circle.get_radius(), 
                e->c_shape->circle.get_rotation(), 
                e->c_shape->circle.get_fill_color());
        DrawPolyLinesEx(e->c_transform->pos, 
                e->c_shape->circle.get_point_count(), 
                e->c_shape->circle.get_radius(), 
                e->c_shape->circle.get_rotation(), 
                e->c_shape->circle.get_outline_thickness(), 
                e->c_shape->circle.get_outline_color());
    }
    EndDrawing();
}

void Game::s_user_input() {
    if(!m_windows.is_open()) {
        m_running = false;
    }

    // if (IsKeyDown(KEY_S)) {
    //     std::cout << "S Key Pressed" << std::endl;
    //     m_player->c_input->down = true;
    // } else if(IsKeyDown(KEY_W)) { 
    //     std::cout << "W Key Pressed" << std::endl;
    //     m_player->c_input->up = true;
    // } else {
    //     m_player->c_input->down = false;
    //     m_player->c_input->up = false;
    // }
    // if (IsKeyDown(KEY_D)) {
    //     std::cout << "D Key Pressed" << std::endl;
    //     m_player->c_input->left = true;
    // } else if (IsKeyDown(KEY_A)) {
    //     std::cout << "A Key Pressed" << std::endl;
    //     m_player->c_input->right = true;
    // } else {
    //     m_player->c_input->left = false;
    //     m_player->c_input->right = false;
    // }
    
    //Pressed
    if (IsKeyPressed(KEY_S)) {
        std::cout << "S Key Pressed" << std::endl;
        m_player->c_input->down = true;
    } 
    if(IsKeyPressed(KEY_W)) { 
        std::cout << "W Key Pressed" << std::endl;
        m_player->c_input->up = true;
    }
    if (IsKeyPressed(KEY_D)) {
        std::cout << "D Key Pressed" << std::endl;
        m_player->c_input->left = true;
    } 
    if (IsKeyPressed(KEY_A)) {
        std::cout << "A Key Pressed" << std::endl;
        m_player->c_input->right = true;
    }
    //Releassed
    if (IsKeyReleased(KEY_S)) {
        std::cout << "S Key Released" << std::endl;
        m_player->c_input->down = false;
    } 
    if(IsKeyReleased(KEY_W)) { 
        std::cout << "W Key Released" << std::endl;
        m_player->c_input->up = false;
    }
    if (IsKeyReleased(KEY_D)) {
        std::cout << "D Key Released" << std::endl;
        m_player->c_input->left = false;
    } 
    if (IsKeyReleased(KEY_A)) {
        std::cout << "A Key Released" << std::endl;
        m_player->c_input->right = false;
    }
    
    if (IsKeyPressed(KEY_SPACE)) {
        std::cout << "SPACE Key Released" << std::endl;
        set_pause(!m_paused);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        std::cout << "MOUSE_BUTTON_LEFT Key Pressed";
        std::cout << " at (" << GetMouseX() << "," << GetMouseY() << ")" << std::endl;
        spawn_bullet(m_player, Vec2(GetMouseX(), GetMouseY()));
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        std::cout << "MOUSE_BUTTON_RIGHT Key Pressed";
        std::cout << " at (" << GetMouseX() << "," << GetMouseY() << ")" << std::endl;   
    }
    // if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    //     std::cout << "MOUSE_BUTTON_LEFT Key Released" << std::endl;
    // }
    // if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
    //     std::cout << "MOUSE_BUTTON_RIGHT Key Released" << std::endl;
    // }
    
    // if (m_direction.x != 0 && m_direction.y != 0) {
    //     m_direction = Vector2Normalize(m_direction);
    // }
}

void Game::s_movement() {
    // m_player->c_shape->circle.set_position(m_player->c_transform->pos.x, m_player->c_transform->pos.y);
    m_player->c_transform->angle += 5.0f;
    m_player->c_shape->circle.set_rotation(m_player->c_transform->angle);
    // if (m_player->c_transform->pos.x > GetScreenWidth() || m_player->c_transform->pos.x < 0) {
    //     m_player->c_transform->velocity *= -1;    
    // }
    // if (m_player->c_transform->pos.y > GetScreenHeight() || m_player->c_transform->pos.y <= 0) {
    //     m_player->c_transform->velocity *= -1;    
    // }
    // m_player->c_transform->pos += m_player->c_transform->velocity;

    // if (m_player->c_input->up) {
    //     m_player->c_transform->pos.y -= m_player->c_transform->velocity.y;
    // }
    // if (m_player->c_input->down) {
    //     m_player->c_transform->pos.y += m_player->c_transform->velocity.y;
    // }
    // if (m_player->c_input->right) {
    //     m_player->c_transform->pos.x -= m_player->c_transform->velocity.x;
    // }
    // if (m_player->c_input->left) {
    //     m_player->c_transform->pos.x += m_player->c_transform->velocity.x;
    // }

    // m_player->c_transform->velocity = { 0, 0 };

    // if (m_player->c_input->up) {
    //     m_player->c_transform->velocity.y = -5;
    // }
    // if (m_player->c_input->down) {
    //     m_player->c_transform->velocity.y = 5;
    // }
    // if (m_player->c_input->right) {
    //     m_player->c_transform->velocity.x = -5;
    // }
    // if (m_player->c_input->left) {
    //     m_player->c_transform->velocity.x = 5;
    // }

    // m_player->c_transform->pos.x += m_player->c_transform->velocity.x;
    // m_player->c_transform->pos.y += m_player->c_transform->velocity.y;

    // m_player->c_transform->velocity.normalize();

    for (auto p : m_entities.get_entities("player")) {
        p->c_transform->velocity = { 0, 0 };

        if (p->c_input->up) {
            p->c_transform->velocity.y = -7;
        }
        if (p->c_input->down) {
            p->c_transform->velocity.y = 7;
        }
        if (p->c_input->right) {
            p->c_transform->velocity.x = -7;
        }
        if (p->c_input->left) {
            p->c_transform->velocity.x = 7;
        }

        p->c_transform->pos.x += p->c_transform->velocity.x;
        p->c_transform->pos.y += p->c_transform->velocity.y;
    }
    for (auto e : m_entities.get_entities("enemy")) {
        e->c_transform->angle += 3.0f;
        e->c_shape->circle.set_rotation(e->c_transform->angle);
        if (e->c_transform->pos.x > GetScreenWidth() || e->c_transform->pos.x < 0) {
            e->c_transform->velocity.x *= -1;
        }
        if (e->c_transform->pos.y > GetScreenHeight() || e->c_transform->pos.y <= 0) {
            e->c_transform->velocity.y *= -1;
        }
        // e->c_transform->pos += e->c_transform->velocity;
        e->c_transform->pos.x += e->c_transform->velocity.x;
        e->c_transform->pos.y += e->c_transform->velocity.y;
    }
}
