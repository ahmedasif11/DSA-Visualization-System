

#pragma once

#include "../Core/State/State.h"
#include "../Core/State/StateID.h"
#include "../UI/Components/Button.h"
#include "../UI/Components/Label.h"
#include <vector>
#include <memory>

namespace DSA {


class MainMenuState : public State {
public:
    
    explicit MainMenuState(StateContext& context);
    
    
    virtual ~MainMenuState() = default;
    
    
    void handleInput(const sf::Event& event) override;
    
    
    void update(float deltaTime) override;
    
    
    void render(sf::RenderTarget& target) override;
    
    
    void onEnter() override;

private:
    
    void setupButtons();
    
    
    void onAlgorithmsClicked();
    void onExitClicked();

    UI::Label m_titleLabel;
    std::vector<std::unique_ptr<UI::Button>> m_buttons;
    sf::RectangleShape m_background;
    int m_selectedButtonIndex = 0;
};

} 
