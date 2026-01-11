

#pragma once

#include "../Core/State/State.h"
#include "../Core/State/StateID.h"
#include "../UI/Components/Label.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>

namespace DSA {


class EntryState : public State {
public:
    
    explicit EntryState(StateContext& context);
    
    
    virtual ~EntryState() = default;
    
    
    void handleInput(const sf::Event& event) override;
    
    
    void update(float deltaTime) override;
    
    
    void render(sf::RenderTarget& target) override;
    
    
    void onEnter() override;

private:
    
    void transitionToMainMenu();

    UI::Label m_titleLabel;
    UI::Label m_pressKeyLabel;
    sf::RectangleShape m_background;
    sf::Clock m_clock;
    float m_elapsedTime = 0.0f;
    bool m_pressKeyVisible = true;
    static constexpr float AUTO_ADVANCE_TIME = 3.0f;
    static constexpr float BLINK_INTERVAL = 0.5f;
};

} 
