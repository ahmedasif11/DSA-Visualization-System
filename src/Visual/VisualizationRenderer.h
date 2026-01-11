#pragma once

#include "Components/IVisualizationComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <memory>

namespace DSA {

struct SortStep;

namespace Visual {

class VisualizationRenderer {
public:
    VisualizationRenderer();
    ~VisualizationRenderer() = default;
    
    void addComponent(std::unique_ptr<IVisualizationComponent> component);
    void clearComponents();
    
    void updateLayout(const sf::FloatRect& bounds);
    void render(sf::RenderTarget& target, const DSA::SortStep* step) const;
    
    void setData(const void* data);

private:
    std::vector<std::unique_ptr<IVisualizationComponent>> m_components;
};

}
}
