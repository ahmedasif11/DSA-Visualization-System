#include "BarComponent.h"
#include "App/Config.h"
#include "UI/Theme/ThemeManager.h"
#include "Core/Resources/ResourceManager.h"
#include <cmath>
#include <sstream>

namespace DSA {
namespace Visual {

BarComponent::BarComponent()
    : m_array(nullptr)
    , m_barWidth(20.0f)
    , m_spacing(5.0f)
    , m_baseY(600.0f)
    , m_startX(50.0f)
    , m_maxHeight(500.0f)
    , m_maxValue(100)
{
}

void BarComponent::setData(const void* data) {
    m_array = static_cast<const Array*>(data);
    if (m_array) {
        m_maxValue = findMaxValue();
    }
}

void BarComponent::updateLayout(const sf::FloatRect& bounds) {
    if (!m_array || m_array->isEmpty()) {
        return;
    }
    
    std::size_t arraySize = m_array->size();
    float availableWidth = bounds.size.x;
    float totalSpacing = (arraySize - 1) * m_spacing;
    m_barWidth = (availableWidth - totalSpacing) / static_cast<float>(arraySize);
    
    if (m_barWidth < 5.0f) {
        m_barWidth = 5.0f;
    }
    if (m_barWidth > 50.0f) {
        m_barWidth = 50.0f;
    }
    
    m_startX = bounds.position.x;
    m_baseY = bounds.position.y + bounds.size.y - 20.0f;
    m_maxHeight = bounds.size.y - 40.0f;
}

void BarComponent::render(sf::RenderTarget& target, const DSA::SortStep* step) const {
    if (!m_array || m_array->isEmpty()) {
        return;
    }
    
    std::size_t size = m_array->size();
    const Array& arrayToRender = step ? step->arrayState : *m_array;
    
    m_valueLabels.clear();
    m_valueLabels.reserve(size);
    
    try {
        UI::ThemeManager& tm = UI::ThemeManager::getInstance();
        tm.loadFonts();
        const sf::Font& font = tm.getMainFont();
        
        for (std::size_t i = 0; i < size; ++i) {
            int value = arrayToRender[i];
            float height = calculateBarHeight(value);
            float x = m_startX + static_cast<float>(i) * (m_barWidth + m_spacing);
            float y = m_baseY - height;
            
            sf::RectangleShape bar(sf::Vector2f(m_barWidth, height));
            bar.setPosition(sf::Vector2f(x, y));
            bar.setFillColor(getBarColor(i, step));
            
            bar.setOutlineColor(sf::Color(Config::Colors::TEXT_R, 
                                          Config::Colors::TEXT_G, 
                                          Config::Colors::TEXT_B));
            bar.setOutlineThickness(1.0f);
            
            target.draw(bar);
            
            std::string valueStr = std::to_string(value);
            auto label = std::make_unique<UI::Label>(sf::Vector2f(0, 0), valueStr);
            label->setColor(sf::Color::White);
            unsigned int fontSize = static_cast<unsigned int>(std::max(10.0f, std::min(14.0f, m_barWidth * 0.6f)));
            label->setFontSize(fontSize);
            m_valueLabels.push_back(std::move(label));
            
            sf::FloatRect textBounds = m_valueLabels.back()->getLocalBounds();
            float textX = x + (m_barWidth - textBounds.size.x) / 2.0f;
            float textY;
            
            if (height < 20.0f) {
                textY = y - textBounds.size.y - 2.0f;
            } else {
                textY = y + (height - textBounds.size.y) / 2.0f - textBounds.position.y;
            }
            
            m_valueLabels.back()->setPosition(sf::Vector2f(textX, textY));
            m_valueLabels.back()->render(target);
        }
    } catch (...) {
    }
}

float BarComponent::calculateBarHeight(int value) const {
    if (m_maxValue == 0) {
        return 0.0f;
    }
    
    float ratio = static_cast<float>(value) / static_cast<float>(m_maxValue);
    return ratio * m_maxHeight;
}

sf::Color BarComponent::getBarColor(std::size_t index, const DSA::SortStep* step) const {
    if (!step) {
        return sf::Color(Config::Colors::SECONDARY_R,
                        Config::Colors::SECONDARY_G,
                        Config::Colors::SECONDARY_B);
    }
    
    if (step->type == DSA::StepType::Complete) {
        return sf::Color(Config::Colors::SUCCESS_R,
                        Config::Colors::SUCCESS_G,
                        Config::Colors::SUCCESS_B);
    }
    
    DSA::ElementRole role = step->getRole(index);
    if (role != DSA::ElementRole::None) {
        switch (role) {
            case DSA::ElementRole::Key:
                return sf::Color(Config::Colors::KEY_R,
                               Config::Colors::KEY_G,
                               Config::Colors::KEY_B);
            case DSA::ElementRole::Minimum:
                return sf::Color(Config::Colors::MINIMUM_R,
                               Config::Colors::MINIMUM_G,
                               Config::Colors::MINIMUM_B);
            case DSA::ElementRole::Maximum:
                return sf::Color(Config::Colors::MINIMUM_R,
                               Config::Colors::MINIMUM_G,
                               Config::Colors::MINIMUM_B);
            case DSA::ElementRole::Pivot:
                return sf::Color(Config::Colors::PIVOT_R,
                               Config::Colors::PIVOT_G,
                               Config::Colors::PIVOT_B);
            case DSA::ElementRole::Sorted:
                return sf::Color(Config::Colors::SUCCESS_R,
                               Config::Colors::SUCCESS_G,
                               Config::Colors::SUCCESS_B);
            case DSA::ElementRole::Compared:
                return sf::Color(Config::Colors::WARNING_R,
                               Config::Colors::WARNING_G,
                               Config::Colors::WARNING_B);
            case DSA::ElementRole::Swapped:
                return sf::Color(Config::Colors::ACCENT_R,
                               Config::Colors::ACCENT_G,
                               Config::Colors::ACCENT_B);
            default:
                break;
        }
    }
    
    bool isInvolved = false;
    for (std::size_t idx : step->indices) {
        if (idx == index) {
            isInvolved = true;
            break;
        }
    }
    
    if (!isInvolved) {
        return sf::Color(Config::Colors::SECONDARY_R,
                        Config::Colors::SECONDARY_G,
                        Config::Colors::SECONDARY_B);
    }
    
    switch (step->type) {
        case DSA::StepType::Compare:
            return sf::Color(Config::Colors::WARNING_R,
                           Config::Colors::WARNING_G,
                           Config::Colors::WARNING_B);
        case DSA::StepType::Swap:
            return sf::Color(Config::Colors::ACCENT_R,
                           Config::Colors::ACCENT_G,
                           Config::Colors::ACCENT_B);
        case DSA::StepType::Highlight:
            return sf::Color(Config::Colors::SUCCESS_R,
                           Config::Colors::SUCCESS_G,
                           Config::Colors::SUCCESS_B);
        default:
            break;
    }
    
    return sf::Color(Config::Colors::SECONDARY_R,
                    Config::Colors::SECONDARY_G,
                    Config::Colors::SECONDARY_B);
}

int BarComponent::findMaxValue() const {
    if (!m_array || m_array->isEmpty()) {
        return 1;
    }
    
    int maxVal = (*m_array)[0];
    for (std::size_t i = 1; i < m_array->size(); ++i) {
        if ((*m_array)[i] > maxVal) {
            maxVal = (*m_array)[i];
        }
    }
    
    return maxVal > 0 ? maxVal : 1;
}

}
}
