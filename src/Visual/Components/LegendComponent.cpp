#include "LegendComponent.h"
#include "App/Config.h"
#include "UI/Theme/ThemeManager.h"
#include "Core/Resources/ResourceManager.h"

namespace DSA {
namespace Visual {

LegendComponent::LegendComponent()
    : m_panelX(0.0f)
    , m_panelY(0.0f)
    , m_panelWidth(220.0f)
    , m_panelHeight(0.0f)
{
    m_background.setFillColor(sf::Color(30, 30, 30, 240));
    m_background.setOutlineColor(sf::Color(100, 100, 100));
    m_background.setOutlineThickness(2.0f);
}

void LegendComponent::updateLayout(const sf::FloatRect& bounds) {
    m_panelX = bounds.position.x + bounds.size.x - m_panelWidth - 20.0f;
    m_panelY = bounds.position.y + bounds.size.y - 280.0f;
    m_panelHeight = 250.0f;
    
    m_background.setSize(sf::Vector2f(m_panelWidth, m_panelHeight));
    m_background.setPosition(sf::Vector2f(m_panelX, m_panelY));
}

void LegendComponent::render(sf::RenderTarget& target, const DSA::SortStep* step) const {
    createLegendItems();
    
    target.draw(m_background);
    
    float currentY = m_panelY + 15.0f;
    float spacing = 28.0f;
    float boxSize = 20.0f;
    float boxX = m_panelX + 15.0f;
    float textX = m_panelX + 45.0f;
    
    for (std::size_t i = 0; i < m_colorBoxes.size() && i < m_labels.size(); ++i) {
        m_colorBoxes[i].setPosition(sf::Vector2f(boxX, currentY));
        m_colorBoxes[i].setSize(sf::Vector2f(boxSize, boxSize));
        target.draw(m_colorBoxes[i]);
        
        if (m_labels[i]) {
            m_labels[i]->setPosition(sf::Vector2f(textX, currentY + 2.0f));
            m_labels[i]->render(target);
        }
        
        currentY += spacing;
    }
}

void LegendComponent::createLegendItems() const {
    m_labels.clear();
    m_colorBoxes.clear();
    
    try {
        UI::ThemeManager& tm = UI::ThemeManager::getInstance();
        tm.loadFonts();
        const sf::Font& font = tm.getMainFont();
        
        std::vector<std::string> roles = {
            "default", "key", "minimum", "pivot", "sorted", "compared", "swapped"
        };
        
        for (const auto& role : roles) {
            sf::Color color = getLegendColor(role);
            std::string text = getLegendText(role);
            
            auto label = std::make_unique<UI::Label>(sf::Vector2f(0, 0), text);
            label->setColor(sf::Color::White);
            label->setFontSize(14);
            m_labels.push_back(std::move(label));
            
            sf::RectangleShape box;
            box.setFillColor(color);
            box.setOutlineColor(sf::Color(200, 200, 200));
            box.setOutlineThickness(1.0f);
            m_colorBoxes.push_back(box);
        }
    } catch (...) {
    }
}

sf::Color LegendComponent::getLegendColor(const std::string& role) const {
    if (role == "key") {
        return sf::Color(Config::Colors::KEY_R, Config::Colors::KEY_G, Config::Colors::KEY_B);
    } else if (role == "minimum") {
        return sf::Color(Config::Colors::MINIMUM_R, Config::Colors::MINIMUM_G, Config::Colors::MINIMUM_B);
    } else if (role == "pivot") {
        return sf::Color(Config::Colors::PIVOT_R, Config::Colors::PIVOT_G, Config::Colors::PIVOT_B);
    } else if (role == "sorted") {
        return sf::Color(Config::Colors::SUCCESS_R, Config::Colors::SUCCESS_G, Config::Colors::SUCCESS_B);
    } else if (role == "compared") {
        return sf::Color(Config::Colors::WARNING_R, Config::Colors::WARNING_G, Config::Colors::WARNING_B);
    } else if (role == "swapped") {
        return sf::Color(Config::Colors::ACCENT_R, Config::Colors::ACCENT_G, Config::Colors::ACCENT_B);
    }
    return sf::Color(Config::Colors::SECONDARY_R, Config::Colors::SECONDARY_G, Config::Colors::SECONDARY_B);
}

std::string LegendComponent::getLegendText(const std::string& role) const {
    if (role == "key") return "Key Element";
    if (role == "minimum") return "Minimum";
    if (role == "pivot") return "Pivot";
    if (role == "sorted") return "Sorted";
    if (role == "compared") return "Comparing";
    if (role == "swapped") return "Swapped";
    return "Default";
}

}
}
