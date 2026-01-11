#pragma once

#include "IVisualizationComponent.h"
#include "DSA/Array/Array.h"
#include "UI/Components/Label.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cstddef>
#include <vector>
#include <memory>

namespace DSA {
namespace Visual {

class BarComponent : public IVisualizationComponent {
public:
    BarComponent();
    ~BarComponent() = default;
    
    void updateLayout(const sf::FloatRect& bounds) override;
    void render(sf::RenderTarget& target, const DSA::SortStep* step) const override;
    
    void setData(const void* data) override;
    bool requiresData() const override { return true; }

private:
    const Array* m_array;
    float m_barWidth;
    float m_spacing;
    float m_baseY;
    float m_startX;
    float m_maxHeight;
    int m_maxValue;
    
    float calculateBarHeight(int value) const;
    sf::Color getBarColor(std::size_t index, const DSA::SortStep* step) const;
    int findMaxValue() const;
    
    mutable std::vector<std::unique_ptr<UI::Label>> m_valueLabels;
};

}
} 
