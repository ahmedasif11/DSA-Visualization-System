/**
 * @file EntryState.cpp
 * @brief Implementation of EntryState
 */

#include "EntryState.h"
#include "../Core/State/StateContext.h"
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

EntryState::EntryState(StateContext& context)
    : State(context)
{
}

void EntryState::onEnter() {
    try {
        // Initialize theme and fonts
        UI::ThemeManager& tm = UI::ThemeManager::getInstance();
        tm.loadFonts();
        
        sf::Vector2u windowSize = m_context.getWindow().getSize();
        
        // Setup background
        m_background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
        const UI::Theme& theme = tm.getTheme();
        m_background.setFillColor(theme.backgroundColor);
        
        // Setup title label
        m_titleLabel.setText("DSA Visualization System");
        m_titleLabel.setFontSize(theme.fontSizeTitle);
        m_titleLabel.setColor(theme.primaryColor);
        
        // Center title
        sf::FloatRect titleBounds = m_titleLabel.getLocalBounds();
        m_titleLabel.setPosition(sf::Vector2f(
            (windowSize.x - titleBounds.size.x) / 2.0f,
            windowSize.y / 3.0f
        ));
        
        // Setup "Press any key" label
        m_pressKeyLabel.setText("Press any key to continue...");
        m_pressKeyLabel.setFontSize(theme.fontSizeNormal);
        m_pressKeyLabel.setColor(theme.textColor);
        
        // Center press key label
        sf::FloatRect pressKeyBounds = m_pressKeyLabel.getLocalBounds();
        m_pressKeyLabel.setPosition(sf::Vector2f(
            (windowSize.x - pressKeyBounds.size.x) / 2.0f,
            windowSize.y * 2.0f / 3.0f
        ));
        
        m_clock.restart();
        m_elapsedTime = 0.0f;
        m_pressKeyVisible = true;
        
        std::cout << "EntryState entered" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing EntryState: " << e.what() << std::endl;
    }
}

void EntryState::handleInput(const sf::Event& event) {
    // Handle any key press or mouse click
    if (event.is<sf::Event::KeyPressed>()) {
        auto keyData = event.getIf<sf::Event::KeyPressed>();
        if (keyData) {
            transitionToMainMenu();
            return;
        }
    }
    
    if (event.is<sf::Event::MouseButtonPressed>()) {
        auto mouseData = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseData) {
            transitionToMainMenu();
            return;
        }
    }
}

void EntryState::update(float deltaTime) {
    m_elapsedTime += deltaTime;
    
    // Auto-advance after timeout
    if (m_elapsedTime >= AUTO_ADVANCE_TIME) {
        transitionToMainMenu();
        return;
    }
    
    // Blink "Press any key" text
    int blinkCount = static_cast<int>(m_elapsedTime / BLINK_INTERVAL);
    m_pressKeyVisible = (blinkCount % 2 == 0);
}

void EntryState::render(sf::RenderTarget& target) {
    target.draw(m_background);
    m_titleLabel.render(target);
    
    if (m_pressKeyVisible) {
        m_pressKeyLabel.render(target);
    }
}

void EntryState::transitionToMainMenu() {
    // Emit state change event - Application will handle the actual transition
    DSA::Event stateChangeEvent(EventType::StateChanged);
    // Store StateID in event data
    stateChangeEvent.setData(StateID::MainMenu);
    m_context.getEventBus().publish(stateChangeEvent);
}

} // namespace DSA
