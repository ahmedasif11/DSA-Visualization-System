/**
 * @file TestState.cpp
 * @brief Implementation of TestState
 */

#include "TestState.h"
#include "../Core/State/StateContext.h"
#include "../Core/Resources/ResourceManager.h"
#include "../Core/Resources/ResourceIDs.h"
#include "../App/Config.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

namespace DSA {

TestState::TestState(StateContext& context, const std::string& message)
    : State(context)
    , m_message(message)
    , m_initialized(false)
{
    // SFML 3.0 requires font in Text constructor, but we'll set it properly in onEnter()
    // Initialize with a temporary font or leave it uninitialized - we'll handle it in onEnter
    // Note: This is a workaround - ideally we'd have a default font available
}

void TestState::onEnter() {
    try {
        // Try to load default font
        ResourceManager& rm = m_context.getResourceManager();
        if (!rm.hasFont(FontID::Main)) {
            // Font not loaded, we can't create text in SFML 3.0
            std::cout << "Warning: Font not loaded, text will not be displayed" << std::endl;
            m_initialized = false;
            return;
        }
        
        const sf::Font& font = rm.getFont(FontID::Main);
        
        // Create text with font (required in SFML 3.0)
        m_text.emplace(font, m_message, 48);
        m_text->setFillColor(sf::Color(
            Config::Colors::TEXT_R,
            Config::Colors::TEXT_G,
            Config::Colors::TEXT_B
        ));
        
        // Center text
        sf::FloatRect textBounds = m_text->getLocalBounds();
        sf::Vector2u windowSize = m_context.getWindow().getSize();
        m_text->setPosition(sf::Vector2f(
            (windowSize.x - textBounds.size.x) / 2.0f,
            (windowSize.y - textBounds.size.y) / 2.0f
        ));
        
        // Create background
        m_background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
        m_background.setFillColor(sf::Color(
            Config::Colors::BACKGROUND_R,
            Config::Colors::BACKGROUND_G,
            Config::Colors::BACKGROUND_B
        ));
        
        m_initialized = true;
        std::cout << "TestState entered: " << m_message << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing TestState: " << e.what() << std::endl;
        m_initialized = false;
    }
}

void TestState::handleInput(const sf::Event& event) {
    (void)event;
}

void TestState::update(float deltaTime) {
    (void)deltaTime;
}

void TestState::render(sf::RenderTarget& target) {
    if (m_initialized) {
        target.draw(m_background);
        // Only draw text if it was initialized
        if (m_text.has_value()) {
            target.draw(*m_text);
        }
    }
}

} // namespace DSA
