#include <vector>
#include <map>
#include "Entity.h"
#include <algorithm>

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