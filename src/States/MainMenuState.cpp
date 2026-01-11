

#include "MainMenuState.h"
#include "../Core/State/StateContext.h"
#include "../Core/State/StateManager.h"
#include "../Core/State/StateID.h"
#include "../Core/Events/EventTypes.h"
#include "../Core/Events/Event.h"
#include "../Core/Events/EventBus.h"
#include "../UI/Theme/ThemeManager.h"
#include "../App/Config.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

namespace DSA {

MainMenuState::MainMenuState(StateContext& context)
    : State(context)
    , m_selectedButtonIndex(0)
{
}

void MainMenuState::onEnter() {
    try {

        UI::ThemeManager& tm = UI::ThemeManager::getInstance();
        tm.loadFonts();
        
        sf::Vector2u windowSize = m_context.getWindow().getSize();
        const UI::Theme& theme = tm.getTheme();

        m_background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
        m_background.setFillColor(theme.backgroundColor);

        m_titleLabel.setText("DSA Visualization System");
        m_titleLabel.setFontSize(theme.fontSizeTitle);
        m_titleLabel.setColor(theme.primaryColor);

        sf::FloatRect titleBounds = m_titleLabel.getLocalBounds();
        m_titleLabel.setPosition(sf::Vector2f(
            (windowSize.x - titleBounds.size.x) / 2.0f,
            100.0f
        ));

        setupButtons();
        
        std::cout << "MainMenuState entered" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing MainMenuState: " << e.what() << std::endl;
    }
}

void MainMenuState::setupButtons() {
    m_buttons.clear();
    m_selectedButtonIndex = 0;
    
    sf::Vector2u windowSize = m_context.getWindow().getSize();
    const UI::Theme& theme = UI::ThemeManager::getInstance().getTheme();
    
    float buttonWidth = 400.0f;
    float buttonHeight = theme.buttonHeight;
    float buttonSpacing = 20.0f;
    float startY = windowSize.y / 2.0f - 100.0f;
    float centerX = (windowSize.x - buttonWidth) / 2.0f;

    auto algorithmsBtn = std::make_unique<UI::Button>(
        sf::Vector2f(centerX, startY),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Algorithms"
    );
    algorithmsBtn->setCallback([this]() { onAlgorithmsClicked(); });
    m_buttons.push_back(std::move(algorithmsBtn));

    auto dataStructuresBtn = std::make_unique<UI::Button>(
        sf::Vector2f(centerX, startY + buttonHeight + buttonSpacing),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Data Structures [LOCKED]"
    );
    dataStructuresBtn->setEnabled(false);
    m_buttons.push_back(std::move(dataStructuresBtn));

    auto exitBtn = std::make_unique<UI::Button>(
        sf::Vector2f(centerX, startY + 2 * (buttonHeight + buttonSpacing)),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Exit"
    );
    exitBtn->setCallback([this]() { onExitClicked(); });
    m_buttons.push_back(std::move(exitBtn));
}

void MainMenuState::onAlgorithmsClicked() {
    std::cout << "Algorithms clicked" << std::endl;

    EventBus& eventBus = m_context.getEventBus();
    Event algorithmMenuEvent(EventType::StateChanged);
    algorithmMenuEvent.setData(StateID::AlgorithmMenu);
    eventBus.publish(algorithmMenuEvent);
}

void MainMenuState::onExitClicked() {
    Event closeEvent(EventType::WindowClosed);
    m_context.getEventBus().publish(closeEvent);
}

void MainMenuState::handleInput(const sf::Event& event) {

    sf::Vector2f mousePos;
    if (event.is<sf::Event::MouseMoved>()) {
        auto mouseData = event.getIf<sf::Event::MouseMoved>();
        if (mouseData) {
            mousePos = sf::Vector2f(mouseData->position.x, mouseData->position.y);
        }
    } else if (event.is<sf::Event::MouseButtonPressed>()) {
        auto mouseData = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseData) {
            mousePos = sf::Vector2f(mouseData->position.x, mouseData->position.y);
        }
    } else if (event.is<sf::Event::MouseButtonReleased>()) {
        auto mouseData = event.getIf<sf::Event::MouseButtonReleased>();
        if (mouseData) {
            mousePos = sf::Vector2f(mouseData->position.x, mouseData->position.y);
        }
    } else {

        sf::Vector2i mousePosI = sf::Mouse::getPosition(m_context.getWindow());
        mousePos = sf::Vector2f(mousePosI.x, mousePosI.y);
    }

    for (auto& button : m_buttons) {
        if (button) {
            button->handleInput(event, mousePos);
        }
    }

    if (event.is<sf::Event::KeyPressed>()) {
        auto keyData = event.getIf<sf::Event::KeyPressed>();
        if (keyData && keyData->code == sf::Keyboard::Key::Escape) {
            onExitClicked();
        }
    }
}

void MainMenuState::update(float deltaTime) {
    sf::Vector2i mousePosI = sf::Mouse::getPosition(m_context.getWindow());
    sf::Vector2f mousePos = sf::Vector2f(mousePosI.x, mousePosI.y);
    
    for (auto& button : m_buttons) {
        if (button) {
            button->update(mousePos);
        }
    }
    
    (void)deltaTime;
}

void MainMenuState::render(sf::RenderTarget& target) {
    target.draw(m_background);
    m_titleLabel.render(target);
    
    for (auto& button : m_buttons) {
        if (button) {
            button->render(target);
        }
    }
}

} 
