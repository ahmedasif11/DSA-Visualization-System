

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "../../DSA/Algorithms/Sorting/SorterBase.h"

namespace DSA {

class EventBus;
class ResourceManager;


class StateContext {
public:
    
    StateContext(sf::RenderWindow& window, EventBus& eventBus, ResourceManager& resourceManager)
        : m_window(window)
        , m_eventBus(eventBus)
        , m_resourceManager(resourceManager)
    {}
    
    
    sf::RenderWindow& getWindow() { return m_window; }
    
    
    const sf::RenderWindow& getWindow() const { return m_window; }
    
    
    EventBus& getEventBus() { return m_eventBus; }
    
    
    const EventBus& getEventBus() const { return m_eventBus; }
    
    
    ResourceManager& getResourceManager() { return m_resourceManager; }
    
    
    const ResourceManager& getResourceManager() const { return m_resourceManager; }
    
    
    void setSelectedSorter(std::unique_ptr<SorterBase> sorter);
    
    
    std::unique_ptr<SorterBase> takeSelectedSorter();

private:
    sf::RenderWindow& m_window;
    EventBus& m_eventBus;
    ResourceManager& m_resourceManager;
    std::unique_ptr<SorterBase> m_selectedSorter;
};

inline void StateContext::setSelectedSorter(std::unique_ptr<SorterBase> sorter) {
    m_selectedSorter = std::move(sorter);
}

inline std::unique_ptr<SorterBase> StateContext::takeSelectedSorter() {
    return std::move(m_selectedSorter);
}

} 
