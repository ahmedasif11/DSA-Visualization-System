#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>

namespace DSA {

class StateManager;
class StateContext;
class EventBus;
class ResourceManager;

class Application {
public:
    Application();
    ~Application();
    void run();
    void quit();

private:
    bool initialize();
    void registerStates();
    void handleEvents();
    void update();
    void render();
    void cleanup();

    sf::RenderWindow m_window;
    sf::Clock m_clock;
    bool m_running = false;
    std::unique_ptr<StateContext> m_context;
    std::unique_ptr<StateManager> m_stateManager;
};

}
