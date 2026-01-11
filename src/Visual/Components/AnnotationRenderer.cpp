#include "AnnotationRenderer.h"
#include "App/Config.h"
#include "Core/Resources/ResourceManager.h"
#include "Core/Resources/ResourceIDs.h"
#include "UI/Theme/ThemeManager.h"
#include <sstream>

namespace DSA {
namespace Visual {

AnnotationComponent::AnnotationComponent()
    : m_panelX(0.0f)
    , m_panelY(0.0f)
    , m_panelWidth(220.0f)
    , m_panelSpacing(8.0f)
{
    m_background.setFillColor(sf::Color(25, 25, 35, 250));
    m_background.setOutlineColor(sf::Color(120, 120, 160));
    m_background.setOutlineThickness(2.0f);
}

void AnnotationComponent::updateLayout(const sf::FloatRect& bounds) {
    m_panelX = bounds.position.x + bounds.size.x - m_panelWidth - 20.0f;
    m_panelY = bounds.position.y + 120.0f;
}

void AnnotationComponent::render(sf::RenderTarget& target, const DSA::SortStep* step) const {
    if (!step) {
        return;
    }
    
    createAnnotationLabels(step);
    
    if (m_annotationLabels.empty() && !m_titleLabel) {
        return;
    }
    
    float titleHeight = 0.0f;
    if (m_titleLabel) {
        titleHeight = 35.0f;
    }
    
    float contentHeight = titleHeight;
    for (const auto& label : m_annotationLabels) {
        if (label) {
            contentHeight += label->getLocalBounds().size.y + m_panelSpacing;
        }
    }
    contentHeight += 20.0f;
    
    m_background.setSize(sf::Vector2f(m_panelWidth, contentHeight));
    m_background.setPosition(sf::Vector2f(m_panelX, m_panelY));
    target.draw(m_background);
    
    float currentY = m_panelY + 18.0f;
    
    if (m_titleLabel) {
        m_titleLabel->setPosition(sf::Vector2f(m_panelX + 18.0f, currentY));
        m_titleLabel->render(target);
        currentY += titleHeight + 5.0f;
    }
    
    for (auto& label : m_annotationLabels) {
        if (label) {
            label->setPosition(sf::Vector2f(m_panelX + 18.0f, currentY));
            label->render(target);
            currentY += label->getLocalBounds().size.y + m_panelSpacing;
        }
    }
}

void AnnotationComponent::createAnnotationLabels(const DSA::SortStep* step) const {
    m_annotationLabels.clear();
    
    bool hasKey = false;
    bool hasMin = false;
    bool hasMax = false;
    
    for (const auto& [idx, role] : step->roles) {
        if (idx < step->arrayState.size()) {
            int value = step->arrayState[idx];
            
            if (role == DSA::ElementRole::Key && !hasKey) {
                std::string labelText = getAnnotationLabel("key", std::to_string(value));
                auto label = std::make_unique<UI::Label>(sf::Vector2f(0, 0), labelText);
                label->setColor(getAnnotationColor("key"));
                label->setFontSize(22);
                m_annotationLabels.push_back(std::move(label));
                hasKey = true;
            } else if (role == DSA::ElementRole::Minimum && !hasMin) {
                std::string labelText = getAnnotationLabel("minimum", std::to_string(value));
                auto label = std::make_unique<UI::Label>(sf::Vector2f(0, 0), labelText);
                label->setColor(getAnnotationColor("minimum"));
                label->setFontSize(22);
                m_annotationLabels.push_back(std::move(label));
                hasMin = true;
            } else if (role == DSA::ElementRole::Maximum && !hasMax) {
                std::string labelText = getAnnotationLabel("maximum", std::to_string(value));
                auto label = std::make_unique<UI::Label>(sf::Vector2f(0, 0), labelText);
                label->setColor(getAnnotationColor("maximum"));
                label->setFontSize(22);
                m_annotationLabels.push_back(std::move(label));
                hasMax = true;
            }
        }
    }
    
    if (step->hasAnnotation("key") && !hasKey) {
        std::string labelText = getAnnotationLabel("key", step->getAnnotation("key"));
        auto label = std::make_unique<UI::Label>(sf::Vector2f(0, 0), labelText);
        label->setColor(getAnnotationColor("key"));
        label->setFontSize(22);
        m_annotationLabels.push_back(std::move(label));
    }
    
    if (step->hasAnnotation("minimum") && !hasMin) {
        std::string labelText = getAnnotationLabel("minimum", step->getAnnotation("minimum"));
        auto label = std::make_unique<UI::Label>(sf::Vector2f(0, 0), labelText);
        label->setColor(getAnnotationColor("minimum"));
        label->setFontSize(22);
        m_annotationLabels.push_back(std::move(label));
    }
    
    if (step->hasAnnotation("maximum") && !hasMax) {
        std::string labelText = getAnnotationLabel("maximum", step->getAnnotation("maximum"));
        auto label = std::make_unique<UI::Label>(sf::Vector2f(0, 0), labelText);
        label->setColor(getAnnotationColor("maximum"));
        label->setFontSize(22);
        m_annotationLabels.push_back(std::move(label));
    }
}

std::string AnnotationComponent::getAnnotationLabel(const std::string& key, const std::string& value) const {
    if (key == "key") {
        return "Key: " + value;
    } else if (key == "minimum") {
        return "Minimum: " + value;
    } else if (key == "maximum") {
        return "Maximum: " + value;
    }
    return key + ": " + value;
}

std::string AnnotationComponent::getAnnotationTitle(const DSA::SortStep* step) const {
    for (const auto& [idx, role] : step->roles) {
        if (role == DSA::ElementRole::Key) {
            return "Current Key";
        } else if (role == DSA::ElementRole::Minimum) {
            return "Current Minimum";
        } else if (role == DSA::ElementRole::Maximum) {
            return "Current Maximum";
        }
    }
    
    if (step->hasAnnotation("key")) {
        return "Current Key";
    } else if (step->hasAnnotation("minimum")) {
        return "Current Minimum";
    } else if (step->hasAnnotation("maximum")) {
        return "Current Maximum";
    }
    
    return "";
}

sf::Color AnnotationComponent::getAnnotationColor(const std::string& key) const {
    if (key == "key") {
        return sf::Color(Config::Colors::KEY_R, Config::Colors::KEY_G, Config::Colors::KEY_B);
    } else if (key == "minimum") {
        return sf::Color(Config::Colors::MINIMUM_R, Config::Colors::MINIMUM_G, Config::Colors::MINIMUM_B);
    } else if (key == "maximum") {
        return sf::Color(Config::Colors::MINIMUM_R, Config::Colors::MINIMUM_G, Config::Colors::MINIMUM_B);
    }
    return sf::Color::White;
}

}
}
