#include "VisualizationRenderer.h"
#include "DSA/Algorithms/Sorting/SortStep.h"

namespace DSA {
namespace Visual {

VisualizationRenderer::VisualizationRenderer() {
}

void VisualizationRenderer::addComponent(std::unique_ptr<IVisualizationComponent> component) {
    if (component) {
        m_components.push_back(std::move(component));
    }
}

void VisualizationRenderer::clearComponents() {
    m_components.clear();
}

void VisualizationRenderer::updateLayout(const sf::FloatRect& bounds) {
    for (auto& component : m_components) {
        if (component) {
            component->updateLayout(bounds);
        }
    }
}

void VisualizationRenderer::render(sf::RenderTarget& target, const DSA::SortStep* step) const {
    for (const auto& component : m_components) {
        if (component) {
            component->render(target, step);
        }
    }
}

void VisualizationRenderer::setData(const void* data) {
    for (auto& component : m_components) {
        if (component && component->requiresData()) {
            component->setData(data);
        }
    }
}

}
}
