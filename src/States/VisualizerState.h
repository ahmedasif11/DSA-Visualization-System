#pragma once

#include "../Core/State/State.h"
#include "../Core/State/StateID.h"
#include "../DSA/Array/Array.h"
#include "../DSA/Algorithms/AlgorithmExecutor.h"
#include "../DSA/Algorithms/Sorting/SorterBase.h"
#include "../Visual/VisualizationRenderer.h"
#include "../Visual/Components/BarComponent.h"
#include "../Visual/Components/AnnotationRenderer.h"
#include "../Visual/Components/LegendComponent.h"
#include "../UI/Components/Button.h"
#include "../UI/Components/Label.h"
#include "../UI/Components/Slider.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

namespace DSA {

class VisualizerState : public State {
public:
    explicit VisualizerState(StateContext& context);
    virtual ~VisualizerState() = default;
    void handleInput(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderTarget& target) override;
    void onEnter() override;
    void onExit() override;
    void setArray(const Array& array);
    void setSorter(std::unique_ptr<SorterBase> sorter);

private:
    Array m_array;
    std::unique_ptr<SorterBase> m_sorter;
    AlgorithmExecutor m_executor;
    Visual::VisualizationRenderer m_renderer;
    
    UI::Label m_titleLabel;
    UI::Label m_statusLabel;
    UI::Label m_stepLabel;
    UI::Button m_playPauseButton;
    UI::Button m_resetButton;
    UI::Button m_backButton;
    UI::Slider m_speedSlider;
    
    sf::RectangleShape m_background;
    sf::RectangleShape m_infoPanel;
    
    bool m_initialized;
    
    void initializeUI();
    void updateUI();
    void onPlayPauseClicked();
    void onResetClicked();
    void onBackClicked();
    void generateDefaultArray();
    std::unique_ptr<SorterBase> createSorterCopy(const SorterBase& sorter);
};

}
