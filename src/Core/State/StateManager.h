

#pragma once

#include "State.h"
#include "StateID.h"
#include "StateContext.h"
#include <unordered_map>
#include <stack>
#include <memory>

namespace DSA {


class StateManager {
public:
    
    explicit StateManager(StateContext& context);
    
    
    ~StateManager();
    
    
    void registerState(StateID id, std::unique_ptr<State> state);
    
    
    void pushState(StateID id);
    
    
    void popState();
    
    
    void changeState(StateID id);
    
    
    State* getCurrentState();
    
    
    const State* getCurrentState() const;
    
    
    bool hasState() const;
    
    
    void update(float deltaTime);
    
    
    void handleInput(const sf::Event& event);
    
    
    void render(sf::RenderTarget& target);
    
    
    void clear();

private:
    
    void cleanupStates();
    
    StateContext& m_context;
    std::unordered_map<StateID, std::unique_ptr<State>> m_states;
    std::stack<StateID> m_stateStack;
    StateID m_currentStateID = StateID::None;
};

} 
