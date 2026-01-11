#pragma once

#include "DSA/Algorithms/Sorting/SortStep.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace DSA {
namespace Visual {

class IVisualizationComponent {
public:
    virtual ~IVisualizationComponent() = default;
    
    virtual void updateLayout(const sf::FloatRect& bounds) = 0;
    virtual void render(sf::RenderTarget& target, const DSA::SortStep* step) const = 0;
    
    virtual void setData(const void* data) { (void)data; }
    virtual bool requiresData() const { return false; }
};

}
}
