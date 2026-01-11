#pragma once

#include "IVisualizationComponent.h"
#include "UI/Components/Label.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <memory>
#include <string>

namespace DSA {
namespace Visual {

class LegendComponent : public IVisualizationComponent {
public:
    LegendComponent();
    ~LegendComponent() = default;
    
    void updateLayout(const sf::FloatRect& bounds) override;
    void render(sf::RenderTarget& target, const DSA::SortStep* step) const override;

private:
    float m_panelX;
    float m_panelY;
    float m_panelWidth;
    float m_panelHeight;
    mutable sf::RectangleShape m_background;
    mutable std::vector<std::unique_ptr<UI::Label>> m_labels;
    mutable std::vector<sf::RectangleShape> m_colorBoxes;
    
    void createLegendItems() const;
    sf::Color getLegendColor(const std::string& role) const;
    std::string getLegendText(const std::string& role) const;
};

}
}
