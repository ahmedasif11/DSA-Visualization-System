/**
 * @file StateContext.h
 * @brief Shared context for all states (window, managers, etc.)
 */

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace DSA {

// Forward declarations
class EventBus;
class ResourceManager;

/**
 * @class StateContext
 * @brief Shared context passed to all states
 * 
 * Contains references to shared resources like window,
 * event bus, resource manager, etc.
 */
class StateContext {
public:
    /**
     * @brief Construct a new StateContext
     * @param window Reference to the main render window
     * @param eventBus Reference to the event bus
     * @param resourceManager Reference to the resource manager
     */
    StateContext(sf::RenderWindow& window, EventBus& eventBus, ResourceManager& resourceManager)
        : m_window(window)
        , m_eventBus(eventBus)
        , m_resourceManager(resourceManager)
    {}
    
    /**
     * @brief Get the render window
     * @return Reference to the render window
     */
    sf::RenderWindow& getWindow() { return m_window; }
    
    /**
     * @brief Get the render window (const)
     * @return Const reference to the render window
     */
    const sf::RenderWindow& getWindow() const { return m_window; }
    
    /**
     * @brief Get the event bus
     * @return Reference to the event bus
     */
    EventBus& getEventBus() { return m_eventBus; }
    
    /**
     * @brief Get the event bus (const)
     * @return Const reference to the event bus
     */
    const EventBus& getEventBus() const { return m_eventBus; }
    
    /**
     * @brief Get the resource manager
     * @return Reference to the resource manager
     */
    ResourceManager& getResourceManager() { return m_resourceManager; }
    
    /**
     * @brief Get the resource manager (const)
     * @return Const reference to the resource manager
     */
    const ResourceManager& getResourceManager() const { return m_resourceManager; }

private:
    sf::RenderWindow& m_window;              ///< Main render window
    EventBus& m_eventBus;                    ///< Event bus
    ResourceManager& m_resourceManager;      ///< Resource manager
};

} // namespace DSA
