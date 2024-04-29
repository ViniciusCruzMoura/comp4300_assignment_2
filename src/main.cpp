#include "raylib.h"
#include <string>
#include <map>
#include <memory>
#include "raymath.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#define TILE_SIZE 32
#define TILEMAP_SIZE_W 16
#define TILEMAP_SIZE_H 15
#define WIN_RES_W (TILE_SIZE * TILEMAP_SIZE_W)
#define WIN_RES_H (TILE_SIZE * TILEMAP_SIZE_H)
#define TILE_NULL -1
#define TILE_GRASS_ID 1
#define TILE_GRASS_PATH "../assets/textures/tile_1.png"
#define TILE_DIRT_ID 0
#define TILE_DIRT_PATH "../assets/textures/tile_0.png"
#define SPRITE_PLAYER_PATH "../assets/textures/player.png"
#define TILEMAP_PATH "../assets/map/map1.csv"

// typedef enum Tile { 
//     GRASS = 1, 
//     DIRT = 2
// } Tile;

// typedef struct Player {
//     Vector2 position;
//     Vector2 direction;
//     Rectangle collision;
//     int speed;
//     Texture2D sprite;
// } Player;

std::vector<std::vector<std::string>> map1;

class Player { 
    public:
        Vector2 m_position;
        Vector2 m_direction;
        Rectangle m_hitbox;
        int m_speed;
        Texture2D m_sprite;

        void init(int px, int py);
        void update();
    private:
        void input();
        void move();
        void check_collision_with_map(std::vector<std::vector<std::string>> collision_map, std::string dir);
};

void Player::init(int px, int py) {
    m_position = (Vector2){ .x = px, .y = py };
    m_hitbox = (Rectangle){ 
        .x = px, 
        .y = py, 
        .width = TILE_SIZE, 
        .height = TILE_SIZE
    };
    m_direction = (Vector2){ .x = 0, .y = 0 };
    m_speed = 5;
    m_sprite = LoadTexture(SPRITE_PLAYER_PATH);
}

void Player::input() {
    if (IsKeyDown(KEY_S)) {
        m_direction.y = 1;
    } else if(IsKeyDown(KEY_W)) { 
        m_direction.y = -1;
    } else {
        m_direction.y = 0;
    }
    if (IsKeyDown(KEY_D)) {
        m_direction.x = 1;
    } else if (IsKeyDown(KEY_A)) {
        m_direction.x = -1;
    } else {
        m_direction.x = 0;
    }
    if (m_direction.x != 0 && m_direction.y != 0) {
        m_direction = Vector2Normalize(m_direction);
    }
}

void Player::move() {
    // if (!check_collision_with_map(map1)) {
    //     m_position = Vector2Add(m_position, Vector2Scale(m_direction, m_speed));
    //     m_hitbox.x = m_position.x;
    //     m_hitbox.y = m_position.y;
    // }
    Vector2 pos = Vector2Add(m_position, Vector2Scale(m_direction, m_speed));
    
    m_hitbox.x = pos.x;
    check_collision_with_map(map1, "horizontal");
    m_position.x = m_hitbox.x;

    m_hitbox.y = pos.y;
    check_collision_with_map(map1, "vertical");
    m_position.y = m_hitbox.y;
}

void Player::check_collision_with_map(std::vector<std::vector<std::string>> collision_map, std::string dir) {
    if (m_direction.x == 0 && m_direction.y == 0) {
        return;
    }
    // Vector2 hitbox = {m_hitbox.x, m_hitbox.y};
    // int player_map_pos_x = hitbox.x / TILE_SIZE;
    Rectangle tile;
    // std::cout << "player_map_pos_x_min: " << player_map_pos_x_min << " player_map_pos_x_max: " << player_map_pos_x_max << " player_map_pos_y_min: " << player_map_pos_y_min << " player_map_pos_y_max: " << player_map_pos_y_max << std::endl;
    for (size_t i = 0; i < collision_map.size(); i++) {
        for (size_t j = 0; j < collision_map[i].size(); j++) {
            // std::cout << "i: " << i << " j: " << j << std::endl;
            tile = {TILE_SIZE * j, TILE_SIZE * i, TILE_SIZE, TILE_SIZE};
            switch (std::stoi(collision_map[i][j])) {
                case TILE_GRASS_ID:
                case TILE_NULL:
                // std::cout << "x: " << m_hitbox.x << " y: " << m_hitbox.y << " tile_id: " << collision_map[i][j] << std::endl;
                    if (CheckCollisionRecs(m_hitbox, tile)) {
                        if (dir == "horizontal") {
                            if (m_direction.x > 0) {
                                m_hitbox.x = tile.x - tile.width;
                                m_position.x = tile.x - tile.width;
                            }
                            if (m_direction.x < 0) {
                                m_hitbox.x = tile.x + tile.width;
                                m_position.x = tile.x + tile.width;
                            }
                        }
                        if (dir == "vertical") {
                            if (m_direction.y > 0) {
                                m_hitbox.y = tile.y - tile.height;
                                m_position.y = tile.y - tile.height;
                            }
                            if (m_direction.y < 0) {
                                m_hitbox.y = tile.y + tile.height;
                                m_position.y = tile.y + tile.height;
                            }
                        }
                    }
                    break;
            }
        }
    }

    // if (m_direction.x > 0) {
    //     // player_map_pos_x = round(player_map_pos_x + 0.5f);
    //     player_map_pos_x += 1;   
    // }
    // if (m_direction.y > 0) {
    //     // player_map_pos_y = round(player_map_pos_y + 0.5f);
    //     player_map_pos_y += 1;
    // } else if (m_direction.y < 0) {
    //     player_map_pos_x = round(hitbox.x / TILE_SIZE);
    // }
    // switch (std::stoi(collision_map[player_map_pos_y][player_map_pos_x])) {
    //     case TILE_GRASS_ID:
    //     case TILE_NULL:
    //         std::cout << "x: " << m_hitbox.x << " y: " << m_hitbox.y << " tile_id: " << collision_map[player_map_pos_y][player_map_pos_x] << std::endl;
    //         return true;
    // }
    // std::cout << collision_map[player_map_pos_y][player_map_pos_x] << std::endl;
    // if (target_tile_x >= 0 && target_tile_x < TILEMAP_SIZE_W && target_tile_y >= 0 && target_tile_y < TILEMAP_SIZE_H) {
    //     switch (std::stoi(collision_map[target_tile_y][target_tile_x])) {
    //         case TILE_GRASS_ID:
    //         case TILE_NULL:
    //             std::cout << tile.x << std::endl;
    //             std::cout << hbox.x << std::endl;
    //             return true;
    //     }       
    // }
}

void Player::update() {
    input();
    move();
}

Texture2D grass;
Texture2D dirt;

Player player;

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::vector<std::string>> load_csv(const std::string path)
{
    // Open the .csv file
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        std::vector<std::vector<std::string>> err;
        return err;
    }

    // Read the .csv file line by line
    std::vector<std::vector<std::string>> data;
    std::string line;
    while (std::getline(file, line)) {
        // Split each line by comma and store it in the 2D vector
        std::vector<std::string> row = split(line, ',');
        data.push_back(row);
    }

    // Display the data (optional)
    // std::cout << "CSV Data." << std::endl;
    // for (const auto& row : data) {
    //     for (const auto& value : row) {
    //         std::cout << value << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // Close the file
    file.close();

    return data;

    // // Check if the dimensions of data match the dimensions of map
    // if (data.size() != TILEMAP_SIZE_H || (data.size() > 0 && data[0].size() != TILEMAP_SIZE_W)) {
    //     std::cerr << "Vector dimensions do not match array dimensions\n";
    //     return;
    // }

    // // Convert to 2D array
    // for (int i = 0; i < TILEMAP_SIZE_H; ++i) {
    //     for (int j = 0; j < TILEMAP_SIZE_W; ++j) {
    //         map[i][j] = std::stoi(data[i][j]);
    //     }
    // }
}

// int main(void) {
//     InitWindow(WIN_RES_W, WIN_RES_H, "raylib example - tilemap");
//     SetTargetFPS(30);

//     grass = LoadTexture(TILE_GRASS_PATH);
//     dirt = LoadTexture(TILE_DIRT_PATH);

//     player.init(200, 200);

//     map1 = load_csv(TILEMAP_PATH);

//     while (!WindowShouldClose()) {
//         player.update();

//         BeginDrawing();
//             // ClearBackground(RAYWHITE);

//             for (size_t i = 0; i < map1.size(); i++) {
//                 for (size_t j = 0; j < map1[i].size(); j++) {
//                     switch (std::stoi(map1[i][j])) {
//                         case TILE_GRASS_ID: 
//                             DrawTextureV(grass, (Vector2){.x = 0 + 32 * j, .y = 0 + 32 * i}, WHITE);
//                             break;
//                         case TILE_DIRT_ID: 
//                             DrawTextureV(dirt, (Vector2){.x = 0 + 32 * j, .y = 0 + 32 * i}, WHITE);
//                             break;
//                         default:
//                             DrawRectangleV(
//                                 (Vector2){.x = 0 + 32 * j, .y = 0 + 32 * i}, 
//                                 (Vector2){.x = 32, .y = 32}, 
//                                 BLACK
//                             );
//                             break;
//                     }
//                 }
//             }

//             DrawTextureV(player.m_sprite, player.m_position, WHITE);
//             DrawRectangleLinesEx(player.m_hitbox, 3.0f, PURPLE);

//             DrawText("demo_test", 0, 0, 20, WHITE);
//             DrawText(std::to_string(player.m_direction.x).c_str(), 0, 32, 20, WHITE);
//             DrawText(std::to_string(player.m_direction.y).c_str(), 0, 64, 20, WHITE);
            
//             // DrawTextureV(grass, (Vector2){.x = 0, .y = 0}, WHITE);
//             // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
//         EndDrawing();
//     }
//     CloseWindow();

//     return 0;
// }

class Text {
    std::string m_text;
    Font m_font;
    size_t m_size;
    public:
        Text() {}
        Text(std::string t, Font f, size_t s)
            : m_text(t), m_font(f), m_size(s) {}
};

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

Vec2::Vec2() {}

Vec2::Vec2(float xin, float yin) {
    x = xin;
    y = yin;
}

bool Vec2::operator == (const Vec2 & rhs) const {
    return (x == rhs.x && y == rhs.y);
}
bool Vec2::operator != (const Vec2 & rhs) const {
    return (x != rhs.x || y != rhs.y);
}
Vec2 Vec2::operator + (const Vec2 & rhs) const {
    return Vec2(x+rhs.x, y+rhs.y);
}
Vec2 Vec2::operator - (const Vec2 & rhs) const {
    return Vec2(x-rhs.x, y-rhs.y);
}
Vec2 Vec2::operator / (const float val) const {
    return Vec2(x/val, y/val);
}
Vec2 Vec2::operator * (const float val) const {
    return Vec2(x*val, y*val);
}
void Vec2::operator += (const Vec2 & rhs) {
    x = x+rhs.x;
    y = y+rhs.y;
}
void Vec2::operator -= (const Vec2 & rhs) {}
void Vec2::operator /= (const float val) {}
void Vec2::operator *= (const float val) {
    x = x*val;
    y = y*val;
}

void Vec2::normalize() {
    Vector2 vec = Vector2Normalize({x,y});
    x = vec.x;
    y = vec.y;
};

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

class Entity {
    friend class EntityManager;
    friend class Game;

    bool m_active = true;
    size_t m_id = 0;
    std::string m_tag = "default";    

    Entity(const size_t id, const std::string & tag);

    //component pointers
    std::shared_ptr<CTransform> c_transform;
    std::shared_ptr<CShape> c_shape;
    std::shared_ptr<CCollision> c_collision;
    std::shared_ptr<CScore> c_score;
    std::shared_ptr<CLifespan> c_lifespan;
    std::shared_ptr<CInput> c_input;

    public:        
        bool is_active() const;
        const std::string & tag() const;
        const size_t id() const;
        void destroy();
};

Entity::Entity(const size_t id, const std::string & tag) {
    m_id = id;
    m_tag = tag;
};

bool Entity::is_active() const {
    return m_active;
};
const std::string & Entity::tag() const {
    return m_tag;
};
const size_t Entity::id() const {
    return m_id;
}

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager {
    EntityVec m_entities;    
    EntityVec m_entities_to_add;
    EntityMap m_entities_map;
    size_t m_total_entities = 0;
    
    // void init();
    void remove_dead_entities(EntityVec & vec);
    
    public:
        EntityManager();
        
        void update();
        
        std::shared_ptr<Entity> add_entity(const std::string & tag);
        
        const EntityVec & get_entities();
        const EntityVec & get_entities(const std::string tag);
};

EntityManager::EntityManager() {}

void EntityManager::update() {
    // std::cout << m_entities_map.size() << "\n";
    for (auto e : m_entities_to_add) {
        m_entities.push_back(e);
        
        // m_entities_map[e->tag()].swap(m_entities_to_add);
        // m_entities_map.insert(std::pair<std::string,EntityVec>(e->tag(), m_entities_to_add));
        // m_entities_map.find(e->tag())->second.push_back(e);
        // if (e->tag() == "bullet") {
        //     m_entities_map["bullet"].push_back(e);
        // }

        m_entities_map[e->tag()].push_back(e);

    }
    // std::cout << "bullet_size: " << m_entities_map["bullet"].size() << "\n";
    // std::cout << "enemy_size: " << m_entities_map["enemy"].size() << "\n";

    // std::cout << "bullet_size: " << m_entities_map.find("bullet")->second.size() << "\n";
    // std::cout << "enemy_size: " << m_entities_map.find("enemy")->second.size() << "\n";
    // for (auto e : m_entities_map.at("bullet")) {        
    //     std::cout << e->id() << " " << e->tag() << "\n";
    // }
    // m_entities_map.insert(make_pair("aaa", m_entities_to_add));
    m_entities_to_add.clear();
    remove_dead_entities(m_entities);
    for (auto & [tag, entityVec] : m_entities_map) {
        remove_dead_entities(entityVec);
    }
}

void EntityManager::remove_dead_entities(EntityVec & vec) {
    // for (auto e : vec) {
    //     if (e->is_active()) {
    //         continue;
    //     }
    //     //remove from vec;
    // }
    vec.erase(
        std::remove_if(vec.begin(), 
        vec.end(), 
        [](const std::shared_ptr<Entity> & o) { return !o->is_active(); }), 
        vec.end()
    );
}

std::shared_ptr<Entity> EntityManager::add_entity(const std::string & tag) {
    auto entity = std::shared_ptr<Entity>(new Entity(m_total_entities++, tag));
    m_entities_to_add.push_back(entity);
    return entity;
}

const EntityVec & EntityManager::get_entities() {
    return m_entities;
}

const EntityVec & EntityManager::get_entities(const std::string tag) {
    return m_entities_map[tag];
    // return m_entities_map.at(tag);
    //TODO: this is wrong, return the vector from the map by tag    
    // return m_entities;
}

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
        Vec2(1.0f, 1.0f), 0.0f
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
        DrawPoly(e->c_transform->pos, e->c_shape->circle.get_point_count(), e->c_shape->circle.get_radius(), e->c_shape->circle.get_rotation(), e->c_shape->circle.get_fill_color());
        DrawPolyLinesEx(e->c_transform->pos, e->c_shape->circle.get_point_count(), e->c_shape->circle.get_radius(), e->c_shape->circle.get_rotation(), e->c_shape->circle.get_outline_thickness(), e->c_shape->circle.get_outline_color());    
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

    // if (IsKeyPressed(KEY_SPACE)) {
    //     std::cout << "SPACE Key Pressed" << std::endl;
    //     set_pause(!m_paused);
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
    m_player->c_transform->angle += 1.0f;
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
            p->c_transform->velocity.y = -5;
        }
        if (p->c_input->down) {
            p->c_transform->velocity.y = 5;
        }
        if (p->c_input->right) {
            p->c_transform->velocity.x = -5;
        }
        if (p->c_input->left) {
            p->c_transform->velocity.x = 5;
        }

        p->c_transform->pos.x += p->c_transform->velocity.x;
        p->c_transform->pos.y += p->c_transform->velocity.y;
    }
    for (auto e : m_entities.get_entities("enemy")) {
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


int main(void) {
    // InitWindow(800, 450, "raylib example - tilemap");
    // SetTargetFPS(30);

    // Vec2 v1(100, 200);
    // Vec2 v2(300, 100);
    // Vec2 v3;
    // v3 = v1 - v2;
    // std::cout << v3.x << " - " << v3.y << std::endl;

    Game g("config.txt");
    g.run();

    // while (!WindowShouldClose()) {
    //     BeginDrawing();
    //         DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    //     EndDrawing();
    // }
    // CloseWindow();

    return 0;
}