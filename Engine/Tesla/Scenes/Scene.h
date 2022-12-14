#pragma once
#include "string"
#include "../ECS/Component.h"
#include "../ECS/Entity.h"
#include "../ECS/System.h"

namespace TESLA
{
    class Scene 
    {
    public:
        virtual ~Scene() = default;
        Scene(std::string name) : m_name(name)
        {
            m_lastEntityId = 0;
        }
        
        virtual void Disable()
        {
            m_entities.clear();
            m_components.clear();
            
            for(TESLA::System* system : m_systems)
            {
                system->Disable();
            }
        }
        virtual void Update(float deltaTime)
        {
            for (TESLA::System* system : m_systems)
            {
                system->Update(deltaTime);
            }
        }
        virtual void Awake()
        {
            for (TESLA::System* system : m_systems)
            {
                system->Awake();
            }
        }
        virtual void Render()
        {
            for (TESLA::System* system : m_systems)
            {
                system->Render();
            }
        }

        void RegisterSystem(TESLA::System* system){m_systems.push_back(system);}
    
        std::string GetName(){return m_name;}
        void CreateEntity(TESLA::Entity* entity);
        TESLA::Component* CreateComponent(Component* component, int entityId);
        Component* GetComponent(std::vector<TESLA_ENUMS::ComponentEnum> indices, int entityId);
        
        std::vector<Component*>& GetComponents(TESLA_ENUMS::ComponentEnum index)
        {
            if(index < m_components.size())
            {
                return m_components[index];
            }
            else
            {
                return m_components[0];
            }
        }
    public:
        TESLA::Entity* mainCamera;
    private:
        const std::string m_name;
        std::vector<Entity*> m_entities;
        std::vector<std::vector<Component*>> m_components;
        std::vector<TESLA::System*> m_systems;
        int m_lastEntityId;
    };
}
