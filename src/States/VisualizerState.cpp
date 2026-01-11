/**
 * @file VisualizerState.cpp
 * @brief Implementation of VisualizerState
 */

#include "VisualizerState.h"
#include "../Core/State/StateContext.h"
#include "../Core/Events/EventBus.h"
#include "../Core/Events/EventTypes.h"
#include "../Core/Events/Event.h"
#include "../Core/State/StateID.h"
#include "../App/Config.h"
#include "../DSA/Algorithms/Sorting/BubbleSort.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <sstream>
#include <iostream>

namespace DSA {

VisualizerState::VisualizerState(StateContext& context)
    : State(context)
    , m_array()
    , m_sorter(nullptr)
    , m_executor()
    , m_visualizer()
    , m_titleLabel(sf::Vector2f(0, 0))
    , m_statusLabel(sf::Vector2f(0, 0))
    , m_stepLabel(sf::Vector2f(0, 0))
    , m_playPauseButton(sf::Vector2f(0, 0), sf::Vector2f(120, 40), "Play")
    , m_resetButton(sf::Vector2f(0, 0), sf::Vector2f(120, 40), "Reset")
    , m_backButton(sf::Vector2f(0, 0), sf::Vector2f(120, 40), "Back")
    , m_initialized(false)
{
}

void VisualizerState::onEnter() {
    try {
        // Generate default array if none set
        if (m_array.isEmpty()) {
            generateDefaultArray();
        }
        
        // Set default sorter if none set
        if (!m_sorter) {
            m_sorter = std::make_unique<BubbleSort>();
        }
        
        // Setup executor
        m_executor.setSorter(std::make_unique<BubbleSort>());
        m_executor.setArray(m_array);
        
        // Setup visualizer
        m_visualizer.setArray(m_array);
        
        // Initialize UI
        initializeUI();
        
        m_initialized = true;
        std::cout << "VisualizerState entered" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing VisualizerState: " << e.what() << std::endl;
        m_initialized = false;
    }
}

void VisualizerState::onExit() {
    m_executor.reset();
    m_initialized = false;
}

void VisualizerState::handleInput(const sf::Event& event) {
    if (!m_initialized) {
        return;
    }
    
    // Handle keyboard input
    if (event.is<sf::Event::KeyPressed>()) {
        const auto* keyData = event.getIf<sf::Event::KeyPressed>();
        if (keyData) {
            if (keyData->code == sf::Keyboard::Key::Escape) {
                // Pause menu
                EventBus& eventBus = m_context.getEventBus();
                Event pauseEvent(EventType::StatePushed);
                pauseEvent.setData(StateID::PauseMenu);
                eventBus.publish(pauseEvent);
            }
            else if (keyData->code == sf::Keyboard::Key::Space) {
                // Toggle play/pause
                onPlayPauseClicked();
            }
            else if (keyData->code == sf::Keyboard::Key::R) {
                // Reset
                onResetClicked();
            }
        }
    }
    
    // Handle mouse input for buttons
    if (event.is<sf::Event::MouseButtonPressed>()) {
        const auto* mouseData = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseData && mouseData->button == sf::Mouse::Button::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_context.getWindow());
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            
            if (m_playPauseButton.contains(mousePosF)) {
                onPlayPauseClicked();
            }
            else if (m_resetButton.contains(mousePosF)) {
                onResetClicked();
            }
            else if (m_backButton.contains(mousePosF)) {
                onBackClicked();
            }
        }
    }
}

void VisualizerState::update(float deltaTime) {
    if (!m_initialized) {
        return;
    }
    
    // Update executor
    m_executor.update(deltaTime);
    
    // Update button hover states
    sf::Vector2i mousePosI = sf::Mouse::getPosition(m_context.getWindow());
    sf::Vector2f mousePos = sf::Vector2f(mousePosI.x, mousePosI.y);
    m_playPauseButton.update(mousePos);
    m_resetButton.update(mousePos);
    m_backButton.update(mousePos);
    
    // Update UI
    updateUI();
    
    // Update visualizer layout if window size changed
    sf::Vector2u windowSize = m_context.getWindow().getSize();
    sf::FloatRect bounds(
        sf::Vector2f(50.0f, 150.0f),
        sf::Vector2f(static_cast<float>(windowSize.x) - 100.0f,
                     static_cast<float>(windowSize.y) - 250.0f)
    );
    m_visualizer.updateLayout(bounds);
}

void VisualizerState::render(sf::RenderTarget& target) {
    if (!m_initialized) {
        return;
    }
    
    // Draw background
    target.draw(m_background);
    
    // Draw info panel
    target.draw(m_infoPanel);
    
    // Draw labels
    m_titleLabel.render(target);
    m_statusLabel.render(target);
    m_stepLabel.render(target);
    
    // Draw buttons
    m_playPauseButton.render(target);
    m_resetButton.render(target);
    m_backButton.render(target);
    
    // Draw visualization
    const SortStep* currentStep = m_executor.getCurrentStep();
    m_visualizer.render(target, currentStep);
}

void VisualizerState::setArray(const Array& array) {
    m_array = array;
    if (m_initialized) {
        m_executor.setArray(m_array);
        m_visualizer.setArray(m_array);
    }
}

void VisualizerState::setSorter(std::unique_ptr<SorterBase> sorter) {
    m_sorter = std::move(sorter);
    if (m_initialized && m_sorter) {
        // Create a copy for executor
        // Note: This is a simplified approach - in a full implementation,
        // we'd clone the sorter properly
        m_executor.setSorter(std::make_unique<BubbleSort>());
    }
}

void VisualizerState::initializeUI() {
    sf::Vector2u windowSize = m_context.getWindow().getSize();
    
    // Setup background
    m_background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    m_background.setFillColor(sf::Color(
        Config::Colors::BACKGROUND_R,
        Config::Colors::BACKGROUND_G,
        Config::Colors::BACKGROUND_B
    ));
    
    // Setup info panel
    m_infoPanel.setSize(sf::Vector2f(windowSize.x, 100.0f));
    m_infoPanel.setPosition(sf::Vector2f(0, 0));
    m_infoPanel.setFillColor(sf::Color(
        Config::Colors::PRIMARY_R,
        Config::Colors::PRIMARY_G,
        Config::Colors::PRIMARY_B,
        240 // Less transparent for better visibility
    ));
    
    // Setup title label (algorithm name) - center it
    m_titleLabel.setText("Bubble Sort"); // Will be updated when algorithm is set
    m_titleLabel.setPosition(sf::Vector2f(static_cast<float>(windowSize.x) / 2.0f - 100.0f, 20.0f));
    m_titleLabel.setFontSize(32);
    m_titleLabel.setColor(sf::Color::White);
    
    // Setup status label
    m_statusLabel.setText("Ready");
    m_statusLabel.setPosition(sf::Vector2f(20, 60));
    m_statusLabel.setColor(sf::Color::White);
    
    // Setup step label
    m_stepLabel.setText("Step: 0 / 0");
    m_stepLabel.setPosition(sf::Vector2f(static_cast<float>(windowSize.x) - 200.0f, 60.0f));
    m_stepLabel.setColor(sf::Color::White);
    
    // Setup buttons
    float buttonY = static_cast<float>(windowSize.y) - 60.0f;
    m_playPauseButton.setPosition(sf::Vector2f(50.0f, buttonY));
    m_playPauseButton.setCallback([this]() { onPlayPauseClicked(); });
    
    m_resetButton.setPosition(sf::Vector2f(180.0f, buttonY));
    m_resetButton.setCallback([this]() { onResetClicked(); });
    
    m_backButton.setPosition(sf::Vector2f(310.0f, buttonY));
    m_backButton.setCallback([this]() { onBackClicked(); });
    
    // Setup visualizer layout
    sf::FloatRect bounds(
        sf::Vector2f(50.0f, 150.0f),
        sf::Vector2f(static_cast<float>(windowSize.x) - 100.0f,
                     static_cast<float>(windowSize.y) - 250.0f)
    );
    m_visualizer.updateLayout(bounds);
}

void VisualizerState::updateUI() {
    // Update algorithm name in title
    std::string algorithmName = m_executor.getAlgorithmName();
    if (!algorithmName.empty()) {
        m_titleLabel.setText(algorithmName);
        // Center the title
        sf::Vector2u windowSize = m_context.getWindow().getSize();
        sf::FloatRect titleBounds = m_titleLabel.getLocalBounds();
        m_titleLabel.setPosition(sf::Vector2f(
            (static_cast<float>(windowSize.x) - titleBounds.size.x) / 2.0f,
            20.0f
        ));
    }
    
    // Update status label
    std::string statusText;
    switch (m_executor.getState()) {
        case AlgorithmExecutor::State::Idle:
            statusText = "Ready";
            break;
        case AlgorithmExecutor::State::Running:
            statusText = "Running";
            break;
        case AlgorithmExecutor::State::Paused:
            statusText = "Paused";
            break;
        case AlgorithmExecutor::State::Completed:
            statusText = "Completed!";
            break;
    }
    m_statusLabel.setText(statusText);
    
    // Update step counter
    std::ostringstream stepText;
    stepText << "Step: " << (m_executor.getCurrentStepIndex() + 1) 
             << " / " << m_executor.getTotalSteps();
    m_stepLabel.setText(stepText.str());
    
    // Update play/pause button text
    if (m_executor.getState() == AlgorithmExecutor::State::Running) {
        m_playPauseButton.setText("Pause");
    } else {
        m_playPauseButton.setText("Play");
    }
}

void VisualizerState::onPlayPauseClicked() {
    if (m_executor.getState() == AlgorithmExecutor::State::Running) {
        m_executor.pause();
    } else if (m_executor.getState() == AlgorithmExecutor::State::Paused) {
        m_executor.resume();
    } else {
        // Start from beginning or resume
        m_executor.start();
    }
}

void VisualizerState::onResetClicked() {
    m_executor.reset();
    updateUI();
}

void VisualizerState::onBackClicked() {
    // Publish state change event to return to main menu
    EventBus& eventBus = m_context.getEventBus();
    Event backEvent(EventType::StateChanged);
    backEvent.setData(StateID::MainMenu);
    eventBus.publish(backEvent);
}

void VisualizerState::generateDefaultArray() {
    // Generate a default random array
    m_array.generateRandom(Config::ARRAY_DEFAULT_SIZE,
                          Config::ARRAY_MIN_VALUE,
                          Config::ARRAY_MAX_VALUE);
}

} // namespace DSA
