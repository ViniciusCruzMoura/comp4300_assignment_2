#include "EntityManager.h"

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