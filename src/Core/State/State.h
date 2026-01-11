/**
 * @file State.h
 * @brief Base state class interface
 */

#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

namespace DSA {

// Forward declarations
class StateContext;

/**
 * @class State
 * @brief Base class for all application states
 * 
 * All states must implement handleInput, update, and render methods.
 * States can be paused and resumed.
 */
class State {
public:
    /**
     * @brief Construct a new State
     * @param context Shared context (window, managers, etc.)
     */
    explicit State(StateContext& context);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~State() = default;
    
    /**
     * @brief Handle input events
     * @param event The SFML event to process
     */
    virtual void handleInput(const sf::Event& event) = 0;
    
    /**
     * @brief Update state logic
     * @param deltaTime Time elapsed since last frame (in seconds)
     */
    virtual void update(float deltaTime) = 0;
    
    /**
     * @brief Render state to target
     * @param target The render target (window)
     */
    virtual void render(sf::RenderTarget& target) = 0;
    
    /**
     * @brief Called when state is entered
     * Override to perform initialization
     */
    virtual void onEnter() {}
    
    /**
     * @brief Called when state is exited
     * Override to perform cleanup
     */
    virtual void onExit() {}
    
    /**
     * @brief Pause the state
     */
    virtual void pause();
    
    /**
     * @brief Resume the state
     */
    virtual void resume();
    
    /**
     * @brief Check if state is paused
     * @return true if state is paused
     */
    bool isPaused() const noexcept { return m_isPaused; }
    
    /**
     * @brief Get the state context
     * @return Reference to the state context
     */
    StateContext& getContext() { return m_context; }
    
    /**
     * @brief Get the state context (const)
     * @return Const reference to the state context
     */
    const StateContext& getContext() const { return m_context; }

protected:
    StateContext& m_context;  ///< Shared state context
    bool m_isPaused = false;  ///< Pause flag
};

} // namespace DSA
