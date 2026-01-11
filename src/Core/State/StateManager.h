/**
 * @file StateManager.h
 * @brief State manager for state lifecycle and transitions
 */

#pragma once

#include "State.h"
#include "StateID.h"
#include "StateContext.h"
#include <unordered_map>
#include <stack>
#include <memory>

namespace DSA {

/**
 * @class StateManager
 * @brief Manages application states and state transitions
 * 
 * Handles state registration, pushing, popping, and changing states.
 * Maintains a state stack for navigation history.
 */
class StateManager {
public:
    /**
     * @brief Construct a new StateManager
     * @param context Shared state context
     */
    explicit StateManager(StateContext& context);
    
    /**
     * @brief Destructor
     */
    ~StateManager();
    
    /**
     * @brief Register a state with an ID
     * @param id The state identifier
     * @param state Unique pointer to the state (takes ownership)
     */
    void registerState(StateID id, std::unique_ptr<State> state);
    
    /**
     * @brief Push a state onto the stack (pauses current state)
     * @param id The state identifier to push
     */
    void pushState(StateID id);
    
    /**
     * @brief Pop the current state from the stack
     */
    void popState();
    
    /**
     * @brief Change to a new state (replaces current state)
     * @param id The state identifier to change to
     */
    void changeState(StateID id);
    
    /**
     * @brief Get the current state
     * @return Pointer to the current state (nullptr if no state)
     */
    State* getCurrentState();
    
    /**
     * @brief Get the current state (const)
     * @return Const pointer to the current state (nullptr if no state)
     */
    const State* getCurrentState() const;
    
    /**
     * @brief Check if there is a current state
     * @return true if there is a current state
     */
    bool hasState() const;
    
    /**
     * @brief Update the current state
     * @param deltaTime Time elapsed since last frame (in seconds)
     */
    void update(float deltaTime);
    
    /**
     * @brief Handle input for the current state
     * @param event The SFML event to process
     */
    void handleInput(const sf::Event& event);
    
    /**
     * @brief Render the current state
     * @param target The render target (window)
     */
    void render(sf::RenderTarget& target);
    
    /**
     * @brief Clear all states
     */
    void clear();

private:
    /**
     * @brief Cleanup and remove states marked for removal
     */
    void cleanupStates();
    
    StateContext& m_context;                                              ///< Shared state context
    std::unordered_map<StateID, std::unique_ptr<State>> m_states;        ///< Registered states
    std::stack<StateID> m_stateStack;                                     ///< State stack for navigation
    StateID m_currentStateID = StateID::None;                            ///< Current state ID
};

} // namespace DSA
