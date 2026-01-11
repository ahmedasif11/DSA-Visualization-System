#pragma once

#include "DSA/Array/Array.h"
#include "DSA/Algorithms/Sorting/SortStep.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cstddef>

namespace DSA {
namespace Visual {

class BarVisualizer {
public:
    BarVisualizer();
    ~BarVisualizer() = default;
    void setArray(const Array& array);
    void updateLayout(const sf::FloatRect& bounds);
    void render(sf::RenderTarget& target, const SortStep* step = nullptr) const;

private:
    const Array* m_array;
    float m_barWidth;
    float m_spacing;
    float m_baseY;
    float m_startX;
    float m_maxHeight;
    int m_maxValue;
    
    float calculateBarHeight(int value) const;
    sf::Color getBarColor(std::size_t index, const SortStep* step) const;
    int findMaxValue() const;
};

}
}
