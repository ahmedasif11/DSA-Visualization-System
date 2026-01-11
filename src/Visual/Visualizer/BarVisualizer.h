/**
 * @file BarVisualizer.h
 * @brief Bar chart renderer for array visualization
 */

#pragma once

#include "../../DSA/Array/Array.h"
#include "../../DSA/Algorithms/Sorting/SortStep.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cstddef>

namespace DSA {
namespace Visual {

/**
 * @class BarVisualizer
 * @brief Renders an array as a bar chart with highlighting support
 * 
 * Displays array elements as vertical bars with different colors
 * based on the current sorting step (compare, swap, highlight, etc.)
 */
class BarVisualizer {
public:
    /**
     * @brief Default constructor
     */
    BarVisualizer();
    
    /**
     * @brief Destructor
     */
    ~BarVisualizer() = default;
    
    /**
     * @brief Set the array to visualize
     * @param array Reference to the array
     */
    void setArray(const Array& array);
    
    /**
     * @brief Update layout based on available bounds
     * @param bounds Available rendering area
     */
    void updateLayout(const sf::FloatRect& bounds);
    
    /**
     * @brief Render the array as bars
     * @param target Render target (window)
     * @param step Current sorting step (nullptr for no highlighting)
     */
    void render(sf::RenderTarget& target, const SortStep* step = nullptr) const;

private:
    const Array* m_array;      ///< Pointer to the array being visualized
    float m_barWidth;          ///< Width of each bar
    float m_spacing;           ///< Spacing between bars
    float m_baseY;             ///< Y position of bar base
    float m_startX;            ///< X position where bars start
    float m_maxHeight;          ///< Maximum bar height
    int m_maxValue;            ///< Maximum value in array (for scaling)
    
    /**
     * @brief Calculate bar height for a given value
     * @param value Array element value
     * @return Height of the bar in pixels
     */
    float calculateBarHeight(int value) const;
    
    /**
     * @brief Get color for a bar at a specific index
     * @param index Index of the bar
     * @param step Current sorting step
     * @return Color for the bar
     */
    sf::Color getBarColor(std::size_t index, const SortStep* step) const;
    
    /**
     * @brief Find maximum value in array
     * @return Maximum value
     */
    int findMaxValue() const;
};

} // namespace Visual
} // namespace DSA
