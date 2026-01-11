

#pragma once

#include "../Core/State/State.h"
#include "../Core/State/StateID.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <string>
#include <optional>

namespace DSA {


class TestState : public State {
public:
    
    explicit TestState(StateContext& context, const std::string& message = "Test State");
    
    
    virtual ~TestState() = default;
    
    
    void handleInput(const sf::Event& event) override;
    
    
    void update(float deltaTime) override;
    
    
    void render(sf::RenderTarget& target) override;
    
    
    void onEnter() override;

private:
    std::string m_message;
    std::optional<sf::Text> m_text;
    sf::RectangleShape m_background;
    bool m_initialized;
};

} 
