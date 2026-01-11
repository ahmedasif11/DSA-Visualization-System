#pragma once

#include "IVisualizationComponent.h"
#include "UI/Components/Label.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <memory>

namespace DSA {
namespace Visual {

class AnnotationComponent : public IVisualizationComponent {
public:
    AnnotationComponent();
    ~AnnotationComponent() = default;
    
    void updateLayout(const sf::FloatRect& bounds) override;
    void render(sf::RenderTarget& target, const DSA::SortStep* step) const override;

private:
    float m_panelX;
    float m_panelY;
    float m_panelWidth;
    float m_panelSpacing;
    mutable sf::RectangleShape m_background;
    mutable std::unique_ptr<UI::Label> m_titleLabel;
    mutable std::vector<std::unique_ptr<UI::Label>> m_annotationLabels;
    
    void createAnnotationLabels(const DSA::SortStep* step) const;
    std::string getAnnotationLabel(const std::string& key, const std::string& value) const;
    sf::Color getAnnotationColor(const std::string& key) const;
    std::string getAnnotationTitle(const DSA::SortStep* step) const;
};

using AnnotationRenderer = AnnotationComponent;

}
}

