/**
 * @file BarVisualizer.cpp
 * @brief Implementation of BarVisualizer
 */

#include "BarVisualizer.h"
#include "../../App/Config.h"
#include <cmath>

namespace DSA {
namespace Visual {

BarVisualizer::BarVisualizer()
    : m_array(nullptr)
    , m_barWidth(20.0f)
    , m_spacing(5.0f)
    , m_baseY(600.0f)
    , m_startX(50.0f)
    , m_maxHeight(500.0f)
    , m_maxValue(100)
{
}

void BarVisualizer::setArray(const Array& array) {
    m_array = &array;
    m_maxValue = findMaxValue();
}

void BarVisualizer::updateLayout(const sf::FloatRect& bounds) {
    if (!m_array || m_array->isEmpty()) {
        return;
    }
    
    std::size_t arraySize = m_array->size();
    
    // Calculate bar width and spacing to fit in bounds
    // bounds.size.x already represents the available width (margins are handled by the caller)
    float availableWidth = bounds.size.x;
    float totalSpacing = (arraySize - 1) * m_spacing;
    m_barWidth = (availableWidth - totalSpacing) / static_cast<float>(arraySize);
    
    // Ensure minimum and maximum bar width
    if (m_barWidth < 5.0f) {
        m_barWidth = 5.0f;
    }
    if (m_barWidth > 50.0f) {
        m_barWidth = 50.0f;
    }
    
    // Update positions
    m_startX = bounds.position.x;
    m_baseY = bounds.position.y + bounds.size.y - 20.0f; // Leave 20px margin at bottom
    m_maxHeight = bounds.size.y - 40.0f; // Leave margins top and bottom
}

void BarVisualizer::render(sf::RenderTarget& target, const SortStep* step) const {
    if (!m_array || m_array->isEmpty()) {
        return;
    }
    
    std::size_t size = m_array->size();
    const Array& arrayToRender = step ? step->arrayState : *m_array;
    
    for (std::size_t i = 0; i < size; ++i) {
        int value = arrayToRender[i];
        float height = calculateBarHeight(value);
        float x = m_startX + static_cast<float>(i) * (m_barWidth + m_spacing);
        float y = m_baseY - height;
        
        // Create bar rectangle
        sf::RectangleShape bar(sf::Vector2f(m_barWidth, height));
        bar.setPosition(sf::Vector2f(x, y));
        bar.setFillColor(getBarColor(i, step));
        
        // Add outline for better visibility
        bar.setOutlineColor(sf::Color(Config::Colors::TEXT_R, 
                                      Config::Colors::TEXT_G, 
                                      Config::Colors::TEXT_B));
        bar.setOutlineThickness(1.0f);
        
        target.draw(bar);
    }
}

float BarVisualizer::calculateBarHeight(int value) const {
    if (m_maxValue == 0) {
        return 0.0f;
    }
    
    // Scale value to height (0 to m_maxHeight)
    float ratio = static_cast<float>(value) / static_cast<float>(m_maxValue);
    return ratio * m_maxHeight;
}

sf::Color BarVisualizer::getBarColor(std::size_t index, const SortStep* step) const {
    if (!step) {
        // Default color - primary blue
        return sf::Color(Config::Colors::SECONDARY_R,
                        Config::Colors::SECONDARY_G,
                        Config::Colors::SECONDARY_B);
    }
    
    // Check if this index is involved in the current step
    bool isInvolved = false;
    for (std::size_t idx : step->indices) {
        if (idx == index) {
            isInvolved = true;
            break;
        }
    }
    
    // Color based on step type
    switch (step->type) {
        case StepType::Compare:
            if (isInvolved) {
                // Highlight compared elements in yellow
                return sf::Color(Config::Colors::WARNING_R,
                               Config::Colors::WARNING_G,
                               Config::Colors::WARNING_B);
            }
            break;
            
        case StepType::Swap:
            if (isInvolved) {
                // Highlight swapped elements in red
                return sf::Color(Config::Colors::ACCENT_R,
                               Config::Colors::ACCENT_G,
                               Config::Colors::ACCENT_B);
            }
            break;
            
        case StepType::Highlight:
            if (isInvolved) {
                // Highlight in green (final position)
                return sf::Color(Config::Colors::SUCCESS_R,
                               Config::Colors::SUCCESS_G,
                               Config::Colors::SUCCESS_B);
            }
            break;
            
        case StepType::Complete:
            // All elements in green when complete
            return sf::Color(Config::Colors::SUCCESS_R,
                           Config::Colors::SUCCESS_G,
                           Config::Colors::SUCCESS_B);
            
        default:
            break;
    }
    
    // Default color for non-involved elements
    return sf::Color(Config::Colors::SECONDARY_R,
                    Config::Colors::SECONDARY_G,
                    Config::Colors::SECONDARY_B);
}

int BarVisualizer::findMaxValue() const {
    if (!m_array || m_array->isEmpty()) {
        return 1;
    }
    
    int maxVal = (*m_array)[0];
    for (std::size_t i = 1; i < m_array->size(); ++i) {
        if ((*m_array)[i] > maxVal) {
            maxVal = (*m_array)[i];
        }
    }
    
    // Ensure at least 1 to avoid division by zero
    return maxVal > 0 ? maxVal : 1;
}

} // namespace Visual
} // namespace DSA
