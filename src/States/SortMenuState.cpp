

#include "SortMenuState.h"
#include "../Core/State/StateContext.h"
#include "../Core/Events/EventBus.h"
#include "../Core/Events/EventTypes.h"
#include "../Core/Events/Event.h"
#include "../Core/State/StateID.h"
#include "../DSA/Algorithms/Sorting/BubbleSort.h"
#include "../DSA/Algorithms/Sorting/InsertionSort.h"
#include "../DSA/Algorithms/Sorting/SelectionSort.h"
#include "../UI/Theme/ThemeManager.h"
#include "../App/Config.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

namespace DSA {

SortMenuState::SortMenuState(StateContext& context)
    : State(context)
    , m_background()
    , m_selectedButtonIndex(0)
{
}

void SortMenuState::onEnter() {
    setupButtons();

    sf::Vector2u windowSize = m_context.getWindow().getSize();
    m_background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    m_background.setFillColor(sf::Color(
        Config::Colors::BACKGROUND_R,
        Config::Colors::BACKGROUND_G,
        Config::Colors::BACKGROUND_B
    ));

    m_titleLabel.setText("Sorting Algorithms");
    m_titleLabel.setPosition(sf::Vector2f(20, 20));
    
    std::cout << "SortMenuState entered" << std::endl;
}

void SortMenuState::setupButtons() {
    m_buttons.clear();
    
    sf::Vector2u windowSize = m_context.getWindow().getSize();
    float centerX = static_cast<float>(windowSize.x) / 2.0f;
    float startY = 150.0f;
    float buttonWidth = 300.0f;
    float buttonHeight = 60.0f;
    float buttonSpacing = 20.0f;

    auto bubbleSortBtn = std::make_unique<UI::Button>(
        sf::Vector2f(centerX - buttonWidth / 2.0f, startY),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Bubble Sort"
    );
    bubbleSortBtn->setCallback([this]() { onBubbleSortClicked(); });
    m_buttons.push_back(std::move(bubbleSortBtn));

    auto insertionSortBtn = std::make_unique<UI::Button>(
        sf::Vector2f(centerX - buttonWidth / 2.0f, startY + buttonHeight + buttonSpacing),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Insertion Sort"
    );
    insertionSortBtn->setCallback([this]() { onInsertionSortClicked(); });
    m_buttons.push_back(std::move(insertionSortBtn));

    auto selectionSortBtn = std::make_unique<UI::Button>(
        sf::Vector2f(centerX - buttonWidth / 2.0f, startY + 2 * (buttonHeight + buttonSpacing)),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Selection Sort"
    );
    selectionSortBtn->setCallback([this]() { onSelectionSortClicked(); });
    m_buttons.push_back(std::move(selectionSortBtn));

    auto backBtn = std::make_unique<UI::Button>(
        sf::Vector2f(centerX - buttonWidth / 2.0f, startY + 3 * (buttonHeight + buttonSpacing)),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Back"
    );
    backBtn->setCallback([this]() { onBackClicked(); });
    m_buttons.push_back(std::move(backBtn));
}

void SortMenuState::handleInput(const sf::Event& event) {

    if (event.is<sf::Event::KeyPressed>()) {
        const auto* keyData = event.getIf<sf::Event::KeyPressed>();
        if (keyData) {
            if (keyData->code == sf::Keyboard::Key::Escape) {
                onBackClicked();
            }
            else if (keyData->code == sf::Keyboard::Key::Up) {
                if (m_selectedButtonIndex > 0) {
                    --m_selectedButtonIndex;
                }
            }
            else if (keyData->code == sf::Keyboard::Key::Down) {
                if (m_selectedButtonIndex < static_cast<int>(m_buttons.size()) - 1) {
                    ++m_selectedButtonIndex;
                }
            }
            else if (keyData->code == sf::Keyboard::Key::Enter || keyData->code == sf::Keyboard::Key::Space) {
                if (m_selectedButtonIndex >= 0 && m_selectedButtonIndex < static_cast<int>(m_buttons.size())) {
                    m_buttons[m_selectedButtonIndex]->trigger();
                }
            }
        }
    }

    if (event.is<sf::Event::MouseButtonPressed>()) {
        const auto* mouseData = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseData && mouseData->button == sf::Mouse::Button::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_context.getWindow());
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            
            for (auto& button : m_buttons) {
                if (button->contains(mousePosF)) {
                    button->trigger();
                    break;
                }
            }
        }
    }

    if (event.is<sf::Event::MouseMoved>()) {
        const auto* mouseData = event.getIf<sf::Event::MouseMoved>();
        if (mouseData) {
            sf::Vector2f mousePos(static_cast<float>(mouseData->position.x), 
                                 static_cast<float>(mouseData->position.y));
            
            for (std::size_t i = 0; i < m_buttons.size(); ++i) {
                if (m_buttons[i]->contains(mousePos)) {
                    m_selectedButtonIndex = static_cast<int>(i);
                    break;
                }
            }
        }
    }
}

void SortMenuState::update(float deltaTime) {

    sf::Vector2i mousePosI = sf::Mouse::getPosition(m_context.getWindow());
    sf::Vector2f mousePos = sf::Vector2f(mousePosI.x, mousePosI.y);
    
    for (std::size_t i = 0; i < m_buttons.size(); ++i) {
        if (m_buttons[i]) {
            m_buttons[i]->update(mousePos);
        }
    }
    
    (void)deltaTime;
}

void SortMenuState::render(sf::RenderTarget& target) {
    target.draw(m_background);
    m_titleLabel.render(target);
    
    for (auto& button : m_buttons) {
        button->render(target);
    }
}

void SortMenuState::setAlgorithmCallback(AlgorithmCallback callback) {
    m_algorithmCallback = callback;
}

void SortMenuState::onBubbleSortClicked() {
    m_context.setSelectedSorter(std::make_unique<BubbleSort>());
    
    if (m_algorithmCallback) {
        m_algorithmCallback(std::make_unique<BubbleSort>());
    }
    
    EventBus& eventBus = m_context.getEventBus();
    Event visualizerEvent(EventType::StateChanged);
    visualizerEvent.setData(StateID::Visualizer);
    eventBus.publish(visualizerEvent);
}

void SortMenuState::onInsertionSortClicked() {
    m_context.setSelectedSorter(std::make_unique<InsertionSort>());
    
    if (m_algorithmCallback) {
        m_algorithmCallback(std::make_unique<InsertionSort>());
    }
    
    EventBus& eventBus = m_context.getEventBus();
    Event visualizerEvent(EventType::StateChanged);
    visualizerEvent.setData(StateID::Visualizer);
    eventBus.publish(visualizerEvent);
}

void SortMenuState::onSelectionSortClicked() {
    m_context.setSelectedSorter(std::make_unique<SelectionSort>());
    
    if (m_algorithmCallback) {
        m_algorithmCallback(std::make_unique<SelectionSort>());
    }
    
    EventBus& eventBus = m_context.getEventBus();
    Event visualizerEvent(EventType::StateChanged);
    visualizerEvent.setData(StateID::Visualizer);
    eventBus.publish(visualizerEvent);
}

void SortMenuState::onBackClicked() {

    EventBus& eventBus = m_context.getEventBus();
    Event backEvent(EventType::StateChanged);
    backEvent.setData(StateID::MainMenu);
    eventBus.publish(backEvent);
}

} 
