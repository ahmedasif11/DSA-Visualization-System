

#pragma once

#include "../Core/State/State.h"
#include "../Core/State/StateID.h"
#include "../UI/Components/Button.h"
#include "../UI/Components/Label.h"
#include "../DSA/Algorithms/Sorting/SorterBase.h"
#include <vector>
#include <memory>
#include <functional>

namespace DSA {


class SortMenuState : public State {
public:
    
    using AlgorithmCallback = std::function<void(std::unique_ptr<SorterBase>)>;
    
    
    explicit SortMenuState(StateContext& context);
    
    
    virtual ~SortMenuState() = default;
    
    
    void handleInput(const sf::Event& event) override;
    
    
    void update(float deltaTime) override;
    
    
    void render(sf::RenderTarget& target) override;
    
    
    void onEnter() override;
    
    
    void setAlgorithmCallback(AlgorithmCallback callback);

private:
    
    void setupButtons();
    
    
    void onBubbleSortClicked();
    void onInsertionSortClicked();
    void onSelectionSortClicked();
    void onBackClicked();

    UI::Label m_titleLabel;
    std::vector<std::unique_ptr<UI::Button>> m_buttons;
    sf::RectangleShape m_background;
    AlgorithmCallback m_algorithmCallback;
    int m_selectedButtonIndex = 0;
};

} 
