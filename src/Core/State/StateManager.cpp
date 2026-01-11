/**
 * @file StateManager.cpp
 * @brief Implementation of the StateManager class
 */

#include "StateManager.h"
#include "State.h"
#include "StateID.h"
#include <stdexcept>

namespace DSA {

StateManager::StateManager(StateContext& context)
    : m_context(context)
{
}

StateManager::~StateManager() {
    clear();
}

void StateManager::registerState(StateID id, std::unique_ptr<State> state) {
    if (state) {
        m_states[id] = std::move(state);
    }
}

void StateManager::pushState(StateID id) {
    // Pause current state if exists
    if (m_currentStateID != StateID::None) {
        State* currentState = getCurrentState();
        if (currentState) {
            currentState->pause();
        }
    }
    
    // Push current state onto stack
    if (m_currentStateID != StateID::None) {
        m_stateStack.push(m_currentStateID);
    }
    
    // Set new state
    m_currentStateID = id;
    State* newState = getCurrentState();
    if (newState) {
        newState->onEnter();
    }
}

void StateManager::popState() {
    if (m_currentStateID == StateID::None) {
        return; // No state to pop
    }
    
    // Exit current state
    State* currentState = getCurrentState();
    if (currentState) {
        currentState->onExit();
    }
    
    // Pop from stack
    if (!m_stateStack.empty()) {
        m_currentStateID = m_stateStack.top();
        m_stateStack.pop();
        
        // Resume previous state
        State* previousState = getCurrentState();
        if (previousState) {
            previousState->resume();
        }
    } else {
        m_currentStateID = StateID::None;
    }
}

void StateManager::changeState(StateID id) {
    // Exit current state
    if (m_currentStateID != StateID::None) {
        State* currentState = getCurrentState();
        if (currentState) {
            currentState->onExit();
        }
    }
    
    // Clear stack for new state
    while (!m_stateStack.empty()) {
        m_stateStack.pop();
    }
    
    // Set new state
    m_currentStateID = id;
    State* newState = getCurrentState();
    if (newState) {
        newState->onEnter();
    }
}

State* StateManager::getCurrentState() {
    if (m_currentStateID == StateID::None) {
        return nullptr;
    }
    
    auto it = m_states.find(m_currentStateID);
    if (it == m_states.end()) {
        return nullptr;
    }
    
    return it->second.get();
}

const State* StateManager::getCurrentState() const {
    if (m_currentStateID == StateID::None) {
        return nullptr;
    }
    
    auto it = m_states.find(m_currentStateID);
    if (it == m_states.end()) {
        return nullptr;
    }
    
    return it->second.get();
}

bool StateManager::hasState() const {
    return m_currentStateID != StateID::None;
}

void StateManager::update(float deltaTime) {
    State* currentState = getCurrentState();
    if (currentState && !currentState->isPaused()) {
        currentState->update(deltaTime);
    }
}

void StateManager::handleInput(const sf::Event& event) {
    State* currentState = getCurrentState();
    if (currentState) {
        currentState->handleInput(event);
    }
}

void StateManager::render(sf::RenderTarget& target) {
    State* currentState = getCurrentState();
    if (currentState) {
        currentState->render(target);
    }
}

void StateManager::clear() {
    // Exit current state
    if (m_currentStateID != StateID::None) {
        State* currentState = getCurrentState();
        if (currentState) {
            currentState->onExit();
        }
    }
    
    // Clear stack
    while (!m_stateStack.empty()) {
        m_stateStack.pop();
    }
    
    // Clear states
    m_states.clear();
    m_currentStateID = StateID::None;
}

} // namespace DSA
