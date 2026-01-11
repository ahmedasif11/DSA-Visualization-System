#include "VisualizerState.h"
#include "../Core/State/StateContext.h"
#include "../Core/Events/EventBus.h"
#include "../Core/Events/EventTypes.h"
#include "../Core/Events/Event.h"
#include "../Core/State/StateID.h"
#include "../App/Config.h"
#include "../DSA/Algorithms/Sorting/BubbleSort.h"
#include "../DSA/Algorithms/Sorting/InsertionSort.h"
#include "../DSA/Algorithms/Sorting/SelectionSort.h"
#include "../UI/Components/Slider.h"
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
    , m_renderer()
    , m_titleLabel(sf::Vector2f(0, 0))
    , m_statusLabel(sf::Vector2f(0, 0))
    , m_stepLabel(sf::Vector2f(0, 0))
    , m_playPauseButton(sf::Vector2f(0, 0), sf::Vector2f(120, 40), "Play")
    , m_resetButton(sf::Vector2f(0, 0), sf::Vector2f(120, 40), "Reset")
    , m_backButton(sf::Vector2f(0, 0), sf::Vector2f(120, 40), "Back")
    , m_speedSlider(sf::Vector2f(0, 0), 200.0f, Config::ANIMATION_MIN_SPEED, Config::ANIMATION_MAX_SPEED, Config::ANIMATION_DEFAULT_SPEED)
    , m_initialized(false)
{
    m_renderer.addComponent(std::make_unique<Visual::BarComponent>());
    m_renderer.addComponent(std::make_unique<Visual::AnnotationComponent>());
    m_renderer.addComponent(std::make_unique<Visual::LegendComponent>());
}

void VisualizerState::onEnter() {
    try {

        if (m_array.isEmpty()) {
            generateDefaultArray();
        }
        
        std::unique_ptr<SorterBase> selectedSorter = m_context.takeSelectedSorter();
        if (selectedSorter) {
            m_sorter = std::move(selectedSorter);
        }
        
        if (!m_sorter) {
            m_sorter = std::make_unique<BubbleSort>();
        }
        
        std::unique_ptr<SorterBase> executorSorter = createSorterCopy(*m_sorter);
        m_executor.setSorter(std::move(executorSorter));
        m_executor.setArray(m_array);
        
        m_renderer.setData(&m_array);
        
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

    if (event.is<sf::Event::KeyPressed>()) {
        const auto* keyData = event.getIf<sf::Event::KeyPressed>();
        if (keyData) {
            if (keyData->code == sf::Keyboard::Key::Escape) {

                EventBus& eventBus = m_context.getEventBus();
                Event pauseEvent(EventType::StatePushed);
                pauseEvent.setData(StateID::PauseMenu);
                eventBus.publish(pauseEvent);
            }
            else if (keyData->code == sf::Keyboard::Key::Space) {

                onPlayPauseClicked();
            }
            else if (keyData->code == sf::Keyboard::Key::R) {

                onResetClicked();
            }
        }
    }

    sf::Vector2i mousePosI = sf::Mouse::getPosition(m_context.getWindow());
    sf::Vector2f mousePos = sf::Vector2f(static_cast<float>(mousePosI.x), static_cast<float>(mousePosI.y));
    
    if (m_speedSlider.handleInput(event, mousePos)) {
        return;
    }
    
    if (event.is<sf::Event::MouseButtonPressed>()) {
        const auto* mouseData = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseData && mouseData->button == sf::Mouse::Button::Left) {
            if (m_playPauseButton.contains(mousePos)) {
                onPlayPauseClicked();
            }
            else if (m_resetButton.contains(mousePos)) {
                onResetClicked();
            }
            else if (m_backButton.contains(mousePos)) {
                onBackClicked();
            }
        }
    }
}

void VisualizerState::update(float deltaTime) {
    if (!m_initialized) {
        return;
    }

    m_executor.update(deltaTime);

    sf::Vector2i mousePosI = sf::Mouse::getPosition(m_context.getWindow());
    sf::Vector2f mousePos = sf::Vector2f(mousePosI.x, mousePosI.y);
    m_playPauseButton.update(mousePos);
    m_resetButton.update(mousePos);
    m_backButton.update(mousePos);
    m_speedSlider.update(mousePos);

    updateUI();

    sf::Vector2u windowSize = m_context.getWindow().getSize();
    sf::FloatRect bounds(
        sf::Vector2f(50.0f, 150.0f),
        sf::Vector2f(static_cast<float>(windowSize.x) - 100.0f,
                     static_cast<float>(windowSize.y) - 250.0f)
    );
    m_renderer.updateLayout(bounds);
}

void VisualizerState::render(sf::RenderTarget& target) {
    if (!m_initialized) {
        return;
    }

    target.draw(m_background);

    target.draw(m_infoPanel);

    m_titleLabel.render(target);
    m_statusLabel.render(target);
    m_stepLabel.render(target);

    m_playPauseButton.render(target);
    m_resetButton.render(target);
    m_backButton.render(target);
    m_speedSlider.render(target);
    
    const SortStep* currentStep = m_executor.getCurrentStep();
    m_renderer.render(target, currentStep);
}

void VisualizerState::setArray(const Array& array) {
    m_array = array;
    if (m_initialized) {
        m_executor.setArray(m_array);
        m_renderer.setData(&m_array);
    }
}

void VisualizerState::setSorter(std::unique_ptr<SorterBase> sorter) {
    m_sorter = std::move(sorter);
    if (m_initialized && m_sorter) {
        std::unique_ptr<SorterBase> executorSorter = createSorterCopy(*m_sorter);
        m_executor.setSorter(std::move(executorSorter));
        m_executor.setArray(m_array);
        m_renderer.setData(&m_array);
    }
}

void VisualizerState::initializeUI() {
    sf::Vector2u windowSize = m_context.getWindow().getSize();

    m_background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    m_background.setFillColor(sf::Color(
        Config::Colors::BACKGROUND_R,
        Config::Colors::BACKGROUND_G,
        Config::Colors::BACKGROUND_B
    ));

    m_infoPanel.setSize(sf::Vector2f(windowSize.x, 100.0f));
    m_infoPanel.setPosition(sf::Vector2f(0, 0));
    m_infoPanel.setFillColor(sf::Color(
        Config::Colors::PRIMARY_R,
        Config::Colors::PRIMARY_G,
        Config::Colors::PRIMARY_B,
        240
    ));

    m_titleLabel.setText("Bubble Sort");
    m_titleLabel.setPosition(sf::Vector2f(static_cast<float>(windowSize.x) / 2.0f - 100.0f, 20.0f));
    m_titleLabel.setFontSize(32);
    m_titleLabel.setColor(sf::Color::White);

    m_statusLabel.setText("Ready");
    m_statusLabel.setPosition(sf::Vector2f(20, 75));
    m_statusLabel.setColor(sf::Color(200, 220, 255));
    m_statusLabel.setFontSize(18);

    m_stepLabel.setText("Step: 0 / 0");
    m_stepLabel.setPosition(sf::Vector2f(static_cast<float>(windowSize.x) - 200.0f, 60.0f));
    m_stepLabel.setColor(sf::Color::White);

    m_speedSlider.setPosition(sf::Vector2f(500.0f, static_cast<float>(windowSize.y) - 50.0f));
    m_speedSlider.setCallback([this](float speed) {
        m_executor.setSpeed(speed);
    });

    float buttonY = static_cast<float>(windowSize.y) - 60.0f;
    m_playPauseButton.setPosition(sf::Vector2f(50.0f, buttonY));
    m_playPauseButton.setCallback([this]() { onPlayPauseClicked(); });
    
    m_resetButton.setPosition(sf::Vector2f(180.0f, buttonY));
    m_resetButton.setCallback([this]() { onResetClicked(); });
    
    m_backButton.setPosition(sf::Vector2f(310.0f, buttonY));
    m_backButton.setCallback([this]() { onBackClicked(); });

    sf::FloatRect bounds(
        sf::Vector2f(50.0f, 150.0f),
        sf::Vector2f(static_cast<float>(windowSize.x) - 100.0f,
                     static_cast<float>(windowSize.y) - 250.0f)
    );
    m_renderer.updateLayout(bounds);
}

void VisualizerState::updateUI() {

    std::string algorithmName = m_executor.getAlgorithmName();
    if (!algorithmName.empty()) {
        m_titleLabel.setText(algorithmName);
        sf::Vector2u windowSize = m_context.getWindow().getSize();
        sf::FloatRect titleBounds = m_titleLabel.getLocalBounds();
        m_titleLabel.setPosition(sf::Vector2f(
            (static_cast<float>(windowSize.x) - titleBounds.size.x) / 2.0f,
            15.0f
        ));
        m_titleLabel.setFontSize(42);
        m_titleLabel.setColor(sf::Color(255, 255, 100));
    }

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
    m_statusLabel.setPosition(sf::Vector2f(20, 75));
    m_statusLabel.setColor(sf::Color(200, 220, 255));
    m_statusLabel.setFontSize(18);

    std::ostringstream stepText;
    stepText << "Step: " << (m_executor.getCurrentStepIndex() + 1) 
             << " / " << m_executor.getTotalSteps();
    m_stepLabel.setText(stepText.str());
    sf::Vector2u windowSize = m_context.getWindow().getSize();
    sf::FloatRect stepBounds = m_stepLabel.getLocalBounds();
    m_stepLabel.setPosition(sf::Vector2f(static_cast<float>(windowSize.x) - stepBounds.size.x - 20.0f, 75.0f));
    m_stepLabel.setColor(sf::Color(200, 220, 255));
    m_stepLabel.setFontSize(18);

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

        m_executor.start();
    }
}

void VisualizerState::onResetClicked() {
    m_executor.reset();
    updateUI();
}

void VisualizerState::onBackClicked() {

    EventBus& eventBus = m_context.getEventBus();
    Event backEvent(EventType::StateChanged);
    backEvent.setData(StateID::MainMenu);
    eventBus.publish(backEvent);
}

void VisualizerState::generateDefaultArray() {
    m_array.generateRandom(Config::ARRAY_DEFAULT_SIZE,
                          Config::ARRAY_MIN_VALUE,
                          Config::ARRAY_MAX_VALUE);
}

std::unique_ptr<SorterBase> VisualizerState::createSorterCopy(const SorterBase& sorter) {
    std::string name = sorter.getName();
    if (name == "Bubble Sort") {
        return std::make_unique<BubbleSort>();
    } else if (name == "Insertion Sort") {
        return std::make_unique<InsertionSort>();
    } else if (name == "Selection Sort") {
        return std::make_unique<SelectionSort>();
    }
    return std::make_unique<BubbleSort>();
}

} 
