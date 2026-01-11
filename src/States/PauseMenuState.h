

#pragma once

#include "../Core/State/State.h"
#include "../Core/State/StateID.h"
#include "../UI/Components/Button.h"
#include "../UI/Components/Label.h"
#include <vector>
#include <memory>

namespace DSA {


class PauseMenuState : public State {
public:
    
    explicit PauseMenuState(StateContext& context);
    
    
    virtual ~PauseMenuState() = default;
    
    
    void handleInput(const sf::Event& event) override;
    
    
    void update(float deltaTime) override;
    
    
    void render(sf::RenderTarget& target) override;
    
    
    void onEnter() override;

private:
    
    void setupButtons();
    
    
    void onResumeClicked();
    void onMainMenuClicked();
    void onExitClicked();

    UI::Label m_titleLabel;
    std::vector<std::unique_ptr<UI::Button>> m_buttons;
    sf::RectangleShape m_overlay;
    sf::RectangleShape m_menuBackground;
    int m_selectedButtonIndex = 0;
};

} 
