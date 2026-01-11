#include "Application.h"
#include "Config.h"
#include "../Core/State/StateManager.h"
#include "../Core/State/StateContext.h"
#include "../Core/State/StateID.h"
#include "../Core/Events/EventBus.h"
#include "../Core/Resources/ResourceManager.h"
#include "../Core/Events/EventTypes.h"
#include "../Core/Events/Event.h"
#include "../States/EntryState.h"
#include "../States/MainMenuState.h"
#include "../States/AlgorithmMenuState.h"
#include "../States/SortMenuState.h"
#include "../States/VisualizerState.h"
#include "../States/PauseMenuState.h"
#include "../UI/Theme/ThemeManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <any>
#include <optional>

namespace DSA {

Application::Application()
    : m_window(sf::VideoMode(sf::Vector2u(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT)), Config::WINDOW_TITLE)
{
    m_window.setFramerateLimit(Config::FPS_LIMIT);
    m_window.setVerticalSyncEnabled(Config::VSYNC_ENABLED);
}

Application::~Application() {
    cleanup();
}

bool Application::initialize() {
    try {
        EventBus& eventBus = EventBus::getInstance();
        ResourceManager& resourceManager = ResourceManager::getInstance();
        
        UI::ThemeManager& themeManager = UI::ThemeManager::getInstance();
        themeManager.loadFonts();
        
        resourceManager.setBasePath(Config::ASSETS_BASE_PATH);
        
        m_context = std::make_unique<StateContext>(
            m_window,
            eventBus,
            resourceManager
        );
        
        m_stateManager = std::make_unique<StateManager>(*m_context);
        
        registerStates();
        
        eventBus.subscribe(EventType::WindowClosed, [this](const Event&) {
            quit();
        });
        
        eventBus.subscribe(EventType::StateChanged, [this](const Event& event) {
            if (event.hasData()) {
                try {
                    StateID newStateID = std::any_cast<StateID>(event.getData());
                    m_stateManager->changeState(newStateID);
                } catch (const std::bad_any_cast& e) {
                    std::cerr << "Error casting state change event data: " << e.what() << std::endl;
                }
            }
        });
        
        eventBus.subscribe(EventType::StatePushed, [this](const Event& event) {
            if (event.hasData()) {
                try {
                    StateID newStateID = std::any_cast<StateID>(event.getData());
                    m_stateManager->pushState(newStateID);
                } catch (const std::bad_any_cast& e) {
                    std::cerr << "Error casting state push event data: " << e.what() << std::endl;
                }
            }
        });
        
        eventBus.subscribe(EventType::StatePopped, [this](const Event&) {
            m_stateManager->popState();
        });
        
        m_stateManager->changeState(StateID::Entry);
        
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to initialize application: " << e.what() << std::endl;
        return false;
    }
}

void Application::registerStates() {
    m_stateManager->registerState(
        StateID::Entry,
        std::make_unique<EntryState>(*m_context)
    );
    
    m_stateManager->registerState(
        StateID::MainMenu,
        std::make_unique<MainMenuState>(*m_context)
    );
    
    m_stateManager->registerState(
        StateID::AlgorithmMenu,
        std::make_unique<AlgorithmMenuState>(*m_context)
    );
    
    m_stateManager->registerState(
        StateID::SortMenu,
        std::make_unique<SortMenuState>(*m_context)
    );
    
    m_stateManager->registerState(
        StateID::Visualizer,
        std::make_unique<VisualizerState>(*m_context)
    );
    
    m_stateManager->registerState(
        StateID::PauseMenu,
        std::make_unique<PauseMenuState>(*m_context)
    );
}

void Application::run() {
    if (!initialize()) {
        std::cerr << "Initialization failed. Exiting." << std::endl;
        return;
    }
    
    m_running = true;
    m_clock.restart();
    
    while (m_running && m_window.isOpen()) {
        handleEvents();
        update();
        render();
    }
    
    cleanup();
}

void Application::quit() {
    m_running = false;
}

void Application::handleEvents() {
    while (std::optional<sf::Event> optionalEvent = m_window.pollEvent()) {
        sf::Event event = *optionalEvent;
        
        if (event.is<sf::Event::Closed>()) {
            EventBus::getInstance().publish(Event(EventType::WindowClosed));
            m_running = false;
            continue;
        }
        
        if (event.is<sf::Event::Resized>()) {
            Event resizeEvent(EventType::WindowResized);
            resizeEvent.setData(event.getIf<sf::Event::Resized>());
            EventBus::getInstance().publish(resizeEvent);
        }
        
        if (event.is<sf::Event::KeyPressed>()) {
            Event keyEvent(EventType::KeyPressed);
            keyEvent.setData(event.getIf<sf::Event::KeyPressed>());
            EventBus::getInstance().publish(keyEvent);
        }
        
        if (event.is<sf::Event::KeyReleased>()) {
            Event keyEvent(EventType::KeyReleased);
            keyEvent.setData(event.getIf<sf::Event::KeyReleased>());
            EventBus::getInstance().publish(keyEvent);
        }
        
        if (event.is<sf::Event::MouseButtonPressed>()) {
            Event mouseEvent(EventType::MouseButtonPressed);
            mouseEvent.setData(event.getIf<sf::Event::MouseButtonPressed>());
            EventBus::getInstance().publish(mouseEvent);
        }
        
        if (event.is<sf::Event::MouseButtonReleased>()) {
            Event mouseEvent(EventType::MouseButtonReleased);
            mouseEvent.setData(event.getIf<sf::Event::MouseButtonReleased>());
            EventBus::getInstance().publish(mouseEvent);
        }
        
        if (event.is<sf::Event::MouseMoved>()) {
            Event mouseEvent(EventType::MouseMoved);
            mouseEvent.setData(event.getIf<sf::Event::MouseMoved>());
            EventBus::getInstance().publish(mouseEvent);
        }
        
        m_stateManager->handleInput(event);
    }
    
    EventBus::getInstance().processEvents();
}

void Application::update() {
    float deltaTime = m_clock.restart().asSeconds();
    m_stateManager->update(deltaTime);
}

void Application::render() {
    m_window.clear(sf::Color(
        Config::Colors::BACKGROUND_R,
        Config::Colors::BACKGROUND_G,
        Config::Colors::BACKGROUND_B
    ));
    
    m_stateManager->render(m_window);
    
    m_window.display();
}

void Application::cleanup() {
    if (m_stateManager) {
        m_stateManager->clear();
    }
    
    EventBus::getInstance().clear();
    
    m_stateManager.reset();
    m_context.reset();
}

}
