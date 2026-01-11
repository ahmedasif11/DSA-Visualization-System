

#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

namespace DSA {

class StateContext;


class State {
public:
    
    explicit State(StateContext& context);
    
    
    virtual ~State() = default;
    
    
    virtual void handleInput(const sf::Event& event) = 0;
    
    
    virtual void update(float deltaTime) = 0;
    
    
    virtual void render(sf::RenderTarget& target) = 0;
    
    
    virtual void onEnter() {}
    
    
    virtual void onExit() {}
    
    
    virtual void pause();
    
    
    virtual void resume();
    
    
    bool isPaused() const noexcept { return m_isPaused; }
    
    
    StateContext& getContext() { return m_context; }
    
    
    const StateContext& getContext() const { return m_context; }

protected:
    StateContext& m_context;
    bool m_isPaused = false;
};

} 
